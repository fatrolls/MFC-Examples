/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klasse:			CConstraintDlg
 * Files:			ConstraintDlg.Cpp, ConstraintDlg.H
 * Beschreibung:	Dialog zum Testen der Funktionalität der XConstraint-
 *					Klasse.
 * Funktionen:		DoDataExchange(), OnSysCommand(), OnInitDialog(), 
 *					OnSize(), OnConstraint(), 
 *
 ****************************************************************************/

#include "stdafx.h"
#include "Constraint.h"
#include "ConstraintDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

volatile static char jrrcid[] = "%J%";

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

//****************************************************************************
//****************************************************************************
//****************************************************************************

CConstraintDlg::CConstraintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConstraintDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstraintDlg)
	m_left = 0;
	m_right = 0;
	m_top = 0;
	m_bottom = 0;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConstraintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstraintDlg)
	DDX_Radio(pDX, IDC_LEFT, m_left);
	DDX_Radio(pDX, IDC_RIGHT, m_right);
	DDX_Radio(pDX, IDC_TOP, m_top);
	DDX_Radio(pDX, IDC_BOTTOM, m_bottom);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConstraintDlg, CDialog)
	//{{AFX_MSG_MAP(CConstraintDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_LEFT, OnConstraint)
	ON_BN_CLICKED(IDC_RIGHT, OnConstraint)
	ON_BN_CLICKED(IDC_TOP, OnConstraint)
	ON_BN_CLICKED(IDC_BOTTOM, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO2, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO3, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO4, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO5, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO6, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO7, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO8, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO9, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO10, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO11, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO12, OnConstraint)
	ON_BN_CLICKED(IDC_RADIO13, OnConstraint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CConstraintDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)		{ CAboutDlg dlgAbout; dlgAbout.DoModal(); }
	else									{ CDialog::OnSysCommand(nID, lParam); }
}

BOOL CConstraintDlg::OnInitDialog()
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

	//************************************************************************
	cs.Set(this);
	cs.Add(IDC_ICON1,	CS_LEFT,	CS_LEFT,	CS_TOP,		CS_TOP);
	cs.Add(IDC_ICON2,	CS_RIGHT,	CS_RIGHT,	CS_TOP,		CS_TOP);
	cs.Add(IDC_ICON3,	CS_RIGHT,	CS_RIGHT,	CS_BOTTOM,	CS_BOTTOM);
	cs.Add(IDC_ICON4,	CS_LEFT,	CS_LEFT,	CS_BOTTOM,	CS_BOTTOM);
	cs.Add(IDC_LINE,	CS_LEFT,	CS_RIGHT,	CS_TOP,		CS_TOP);

	OnConstraint();

	//************************************************************************
	
	return TRUE;
}

void CConstraintDlg::OnSize(UINT nType, int cx, int cy) 
{
	aktSize = CSize(cx, cy);
	cs.Resize(cx, cy);
}

void CConstraintDlg::OnConstraint()
{
	UpdateData(TRUE);

	int left, right, top, bottom;
	switch (m_left)
	{
	case 0:	left = CS_LEFT;			break;
	case 1:	left = CS_RIGHT;		break;
	case 2:	left = CS_POSITION;		break;
	case 3:	left = CS_FIXWIDTH;		break;
	}

	switch (m_right)
	{
	case 0:	right = CS_LEFT;		break;
	case 1:	right = CS_RIGHT;		break;
	case 2:	right = CS_POSITION;	break;
	case 3:	right = CS_FIXWIDTH;	break;
	}

	switch (m_top)
	{
	case 0:	top = CS_TOP;			break;
	case 1:	top = CS_BOTTOM;		break;
	case 2:	top = CS_POSITION;		break;
	case 3:	top = CS_FIXHEIGHT;		break;
	}

	switch (m_bottom)
	{
	case 0:	bottom = CS_TOP;		break;
	case 1:	bottom = CS_BOTTOM;		break;
	case 2:	bottom = CS_POSITION;	break;
	case 3:	bottom = CS_FIXHEIGHT;	break;
	}

	cs.Add(IDC_BUTTON, left, right, top, bottom);
	OnSize(0, aktSize.cx, aktSize.cy);
}
