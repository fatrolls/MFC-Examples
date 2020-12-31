// SinusDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "Sinus.h"
#include "SinusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSinusDlg Dialogfeld

CSinusDlg::CSinusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSinusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSinusDlg)
	m_strText = _T("");
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSinusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSinusDlg)
	DDX_Control(pDX, IDC_SPEED_SLIDER, m_ctrlSpeed);
	DDX_Control(pDX, IDC_STATIC_SINUS, m_ctrlSinus);
	DDX_Text(pDX, IDC_TEXT_EDIT, m_strText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSinusDlg, CDialog)
	//{{AFX_MSG_MAP(CSinusDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_TEXT_EDIT, OnChangeTextEdit)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_SET_FONT, OnBtnSetFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSinusDlg Nachrichten-Handler

BOOL CSinusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	VERIFY(m_font.CreatePointFont(220, "Arial Black"));
	m_strText = "_______________________________!___________________________"
					"Yeah, this is a MFC-SINUSTEXT-CONTROL."
					"© Copyright 1998 by Jens Kreiensiek. ________________________________"
					"If you have any comments or questions, write to "
					"sharky@tekkno.teuto.de c ya!";

	m_ctrlSpeed.SetRange(-10, 10);
	m_ctrlSpeed.SetPos(6);
	m_ctrlSpeed.SetLineSize(1);
	m_ctrlSpeed.SetPageSize(5);

	// Initialize Sinus-Control...
	m_ctrlSinus.SetText(m_strText);
	m_ctrlSinus.SetFont(&m_font);
	m_ctrlSinus.SetSinusSpeed(6);
	m_ctrlSinus.Start();

	UpdateData(false);
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CSinusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CSinusDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CSinusDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSinusDlg::OnChangeTextEdit() 
{
	UpdateData();
	
	if(m_strText.GetLength() > 0)
		m_ctrlSinus.SetText(m_strText);
}

void CSinusDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nNewPos = 0;
	
	switch(nSBCode)
	{
	case SB_LEFT: //   Scroll to far left.
		nNewPos = m_ctrlSpeed.GetRangeMin();
		break;

	case SB_ENDSCROLL: //   End scroll.
		return;

	case SB_LINELEFT: //   Scroll left.
		nNewPos = m_ctrlSpeed.GetPos() - m_ctrlSpeed.GetLineSize();
		break;

	case SB_LINERIGHT: //   Scroll right.
		nNewPos = m_ctrlSpeed.GetPos() + m_ctrlSpeed.GetLineSize();
		break;

	case SB_PAGELEFT: //   Scroll one page left.
		nNewPos = m_ctrlSpeed.GetPos() - m_ctrlSpeed.GetPageSize();
		break;

	case SB_PAGERIGHT: //   Scroll one page right.
		nNewPos = m_ctrlSpeed.GetPos() + m_ctrlSpeed.GetPageSize();
		break;

	case SB_RIGHT: //   Scroll to far right.
		nNewPos = m_ctrlSpeed.GetRangeMax();
		break;

	case SB_THUMBPOSITION: //   Scroll to absolute position. The current position is specified by the nPos parameter.
		nNewPos = nPos;
		break;

	case SB_THUMBTRACK: //   Drag scroll box to specified position. The current position is specified by the 
		nNewPos = nPos;
		break;
	}
	
	nNewPos = max(nNewPos, m_ctrlSpeed.GetRangeMin());
	nNewPos = min(nNewPos, m_ctrlSpeed.GetRangeMax());
	
	m_ctrlSinus.SetSinusSpeed(nNewPos);
	m_ctrlSpeed.SetPos(nNewPos);
}

void CSinusDlg::OnBtnSetFont() 
{
	LOGFONT lf;
	m_font.GetLogFont(&lf);
	
	CFontDialog	dlg(&lf);
	if(dlg.DoModal()==IDOK)
	{
		dlg.GetCurrentFont(&lf);
		m_font.DeleteObject();
		VERIFY(m_font.CreateFontIndirect(&lf));
		m_ctrlSinus.SetFont(&m_font);
	}
}
