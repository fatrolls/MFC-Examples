/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klasse:			CCalcDlg
 * Files:			CalcDlg.cpp, CalcDlg.h
 * Beschreibung:	Hier wird der eigentliche Anzeigedialog verwaltet. In
 *					einer ComboBox wird ein Rechenauftrag eingegeben, während
 *					in einem linken Ausgaberechteck alle Variablen und in
 *					einem rechten Ausgaberechteck eine Liste aller Ergebnisse
 *					aufgelistet werden.
 * Funktionen:		DoDataExchange(), OnInitDialog(), OnOK(), OnPaint(),
 *					OnQueryDragIcon(), OnSysCommand(), Variable(),
 *
 ****************************************************************************/

#include "stdafx.h"
#include "Calc.h"
#include "CalcDlg.h"

#include "XEvaluate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_beschreibung;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	XString info = Evaluate("?");
	info.ReplaceAll("\t", "&");
	info.ReplaceAll("&&", "\t");

	//{{AFX_DATA_INIT(CAboutDlg)
	m_beschreibung = info;
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_KURZBESCHREIBUNG, m_beschreibung);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//****************************************************************************
//****************************************************************************
//****************************************************************************

CCalcDlg::CCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalcDlg)
	m_eingabe = _T("");
	m_status = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	XString::SetSeparator('\n');
}

/*****************************************************************************
 * Klasse:		CCalcDlg
 * Funktion:	DoDataExchange
 * Parameter:	CDataExchange
 * Return:		-
 *
 * Führt den Austausch zwischen den internen Variablen und dem Dialog durch.
 ****************************************************************************/
void CCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalcDlg)
	DDX_Control(pDX, IDC_ERGEBNIS, m_ergCtrl);
	DDX_Control(pDX, IDC_VARIABLE, m_varCtrl);
	DDX_Control(pDX, IDC_EINGABE, m_eingabeCtrl);
	DDX_CBString(pDX, IDC_EINGABE, m_eingabe);
	DDX_Text(pDX, IDC_STATUS, m_status);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalcDlg, CDialog)
	//{{AFX_MSG_MAP(CCalcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*****************************************************************************
 * Klasse:		CCalcDlg
 * Funktion:	OnInitDialog
 * Parameter:	-
 * Return:		True
 *
 * Initialisiert den Dialog und gibt die (vordefinierte) Variablenliste aus.
 ****************************************************************************/
BOOL CCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	Variable();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*****************************************************************************
 * Klasse:		CCalcDlg
 * Funktion:	OnSysCommand
 * Parameter:	nID
 *				lParam
 * Return:		-
 *
 * Führt eine Systemmenu-Funktion aus. Hier wird nur der About-Dialog ver-
 * waltet.
 ****************************************************************************/
void CCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

/*****************************************************************************
 * Klasse:		CCalcDlg
 * Funktion:	OnPaint
 * Parameter:	-
 * Return:		-
 *
 * Zeichnet den Dialog bzw. das dazugehörige Icon.
 ****************************************************************************/
void CCalcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

/*****************************************************************************
 * Klasse:		CCalcDlg
 * Funktion:	OnQueryDragIcon
 * Parameter:	-
 * Return:		HCURSOR
 *
 * Gibt das zur Applikation gehörende Icon zurück.
 ****************************************************************************/
HCURSOR CCalcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*****************************************************************************
 * Klasse:		CCalcDlg
 * Funktion:	Variable
 * Parameter:	-
 * Return:		-
 *
 * Gibt die Variablenliste im linken Ausgaberechteck aus. Da das Ausgabe-
 * rechteck eine Edit-Box ist, und die Evaluate-Funktion die Variablen durch
 * "\n" getrennt ausgibt, müssen diese durch "\r\n" ersetzt werden. Die
 * Trennung zwischen dem Variablennamen und dem eigentlichen Variablenwert
 * erfolgt durch " = ", das hier jedoch durch "\t" ersetzt wird.
 ****************************************************************************/
void CCalcDlg::Variable()
{
	XString var = Evaluate("$"), hilf;
	var.ReplaceAll("\t", " = ");

	m_varCtrl.ResetContent();
	for (int i = 0; !!(hilf = var(i)); i++)
		m_varCtrl.AddString(hilf);

	m_status = Evaluate("§");

	UpdateData(FALSE);
}

/*****************************************************************************
 * Klasse:		CCalcDlg
 * Funktion:	OnOK
 * Parameter:	-
 * Return:		-
 *
 * Durch das Drücken der Eingabetaste nach der Eingabe des Rechenauftrags
 * wird die OK-Taste aktiviert und der Rechenauftrag durchgeführt. Auch hier
 * müssen verschiedene Trennzeichen für die Ergebnisliste ersetzt werden.
 ****************************************************************************/
void CCalcDlg::OnOK()
{
	UpdateData(TRUE);

	if (!m_eingabe.IsEmpty()) m_eingabeCtrl.InsertString(0, m_eingabe);

	XString erg = Evaluate(m_eingabe), hilf; 
	if (m_eingabe != "?") erg.ReplaceAll("\t", " = ");
	if (m_eingabe == "#") m_ergCtrl.ResetContent();

	for (int i = erg.Count('\n'); i >= 0; i--)
		m_ergCtrl.InsertString(0, erg(i));

	Variable();
}
