// RoundSliderCtrlDemoDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "RoundSliderCtrlDemo.h"
#include "RoundSliderCtrlDemoDlg.h"
#include "HyperLink.h"	// Hinzugefügt von der Klassenansicht

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
	CHyperLink	m_HyperLink;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
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
	DDX_Control(pDX, IDC_HYPERLINK, m_HyperLink);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoundSliderCtrlDemoDlg Dialogfeld

CRoundSliderCtrlDemoDlg::CRoundSliderCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoundSliderCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoundSliderCtrlDemoDlg)
	m_rscSlider1Val = 42;
	m_rscSlider2Val = 948;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRoundSliderCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoundSliderCtrlDemoDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_rscSlider1);
	DDX_Control(pDX, IDC_SLIDER2, m_rscSlider2);
	DDX_Slider(pDX, IDC_SLIDER1, m_rscSlider1Val);
	DDX_Slider(pDX, IDC_SLIDER2, m_rscSlider2Val);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRoundSliderCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CRoundSliderCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoundSliderCtrlDemoDlg Nachrichten-Handler

BOOL CRoundSliderCtrlDemoDlg::OnInitDialog()
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
	m_rscSlider1.SetRange(-179, 180, FALSE);
	m_rscSlider1.SetPos(42);
	m_rscSlider1.SetZero(90);
	m_rscSlider1.SetInverted();

	m_rscSlider2.SetRange(875, 1080, FALSE);
	m_rscSlider2.SetPos(948);
	m_rscSlider2.SetZero(180);
	m_rscSlider2.SetRadioButtonStyle();

	m_rscSlider1.SetDialColor(RGB(255, 255, 0));
	m_rscSlider1.SetKnobColor(RGB(0, 0, 255));

	m_rscSlider2.SetFontName("Comic Sans MS");
	m_rscSlider2.SetFontSize(14);
	m_rscSlider2.SetFontItalic();
	m_rscSlider2.SetTextColor(RGB(0, 0, 255));

	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CRoundSliderCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRoundSliderCtrlDemoDlg::OnPaint() 
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
HCURSOR CRoundSliderCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRoundSliderCtrlDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(pScrollBar->GetDlgCtrlID() == IDC_SLIDER1)
	{
		TRACE("WM_HSCROLL by CRoundSliderCtrl received. nPos: %ld°, nSBCode: %ld\n", nPos, nSBCode);
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
