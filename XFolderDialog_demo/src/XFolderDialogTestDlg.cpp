// XFolderDialogTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XFolderDialogTest.h"
#include "XFolderDialogTestDlg.h"
#include "XFolderDialog.h"
#include "about.h"
#include "xwinver.h"
#include "XTrace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//=============================================================================
// arrays used to fill combo box
//=============================================================================

const CXFolderDialogTestDlg::LIST_VIEW_MODES CXFolderDialogTestDlg::m_XpModes[] =
{
	{ _T("Default (read from registry)"),	XLVM_XP_UNDEFINED },
	{ _T("No persistence"),					XLVM_XP_DO_NOT_PERSIST },
	{ _T("Thumbnails"),						XLVM_XP_THUMBNAILS },
	{ _T("Tiles"),							XLVM_XP_TILES },
	{ _T("Icons"),							XLVM_XP_ICONS },
	{ _T("List"),							XLVM_XP_LIST },
	{ _T("Details"),						XLVM_XP_DETAILS },
	{ NULL,									0 }
};

const CXFolderDialogTestDlg::LIST_VIEW_MODES CXFolderDialogTestDlg::m_VistaModes[] =
{
	{ _T("Default (read from registry)"),	XLVM_VISTA_UNDEFINED },
	{ _T("No persistence"),					XLVM_VISTA_DO_NOT_PERSIST },
	{ _T("Extra large icons"),				XLVM_VISTA_EXTRA_LARGE_ICONS },
	{ _T("Large icons"),					XLVM_VISTA_LARGE_ICONS },
	{ _T("Medium icons"),					XLVM_VISTA_MEDIUM_ICONS },
	{ _T("Small icons"),					XLVM_VISTA_SMALL_ICONS },
	{ _T("List"),							XLVM_VISTA_LIST },
	{ _T("Details"),						XLVM_VISTA_DETAILS },
	{ _T("Tiles"),							XLVM_VISTA_TILES },
	{ NULL,									0 }
};


//=============================================================================
BEGIN_MESSAGE_MAP(CXFolderDialogTestDlg, CDialog)
//=============================================================================
	//{{AFX_MSG_MAP(CXFolderDialogTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnCXFolderDialog)
	ON_BN_CLICKED(IDC_BUTTON2, OnCFileDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//=============================================================================
CXFolderDialogTestDlg::CXFolderDialogTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXFolderDialogTestDlg::IDD, pParent)
{
//=============================================================================
	TRACE(_T("in CXFolderDialogTestDlg::CXFolderDialogTestDlg\n"));
	//{{AFX_DATA_INIT(CXFolderDialogTestDlg)
	m_nOsVersion = 0;
	m_nListViewModeIndex = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_strInitialFolder = _T("C:\\");
	m_bUseRegistry = TRUE;	// FALSE if not XP or Vista
	m_bPersist = TRUE;		// FALSE if not XP or Vista
	m_hGray  = NULL;
	m_hGreen = NULL;
	m_hRed   = NULL;
}

//=============================================================================
CXFolderDialogTestDlg::~CXFolderDialogTestDlg()
//=============================================================================
{
	if (m_hGray)
		::DestroyIcon(m_hGreen);
	if (m_hGreen)
		::DestroyIcon(m_hGreen);
	if (m_hRed)
		::DestroyIcon(m_hRed);
}

//=============================================================================
void CXFolderDialogTestDlg::DoDataExchange(CDataExchange* pDX)
//=============================================================================
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXFolderDialogTestDlg)
	DDX_Control(pDX, IDC_ICON_XP, m_IconXp);
	DDX_Control(pDX, IDC_ICON_VISTA, m_IconVista);
	DDX_Control(pDX, IDC_ICON_OTHER, m_IconOther);
	DDX_Control(pDX, IDC_COMBO_LIST_VIEW_MODE, m_comboListViewMode);
	DDX_Control(pDX, IDC_PATH, m_Path);
	DDX_Radio(pDX, IDC_AUTO_DETECT, m_nOsVersion);
	DDX_CBIndex(pDX, IDC_COMBO_LIST_VIEW_MODE, m_nListViewModeIndex);
	//}}AFX_DATA_MAP
}

//=============================================================================
BOOL CXFolderDialogTestDlg::OnInitDialog()
//=============================================================================
{
	TRACE(_T("in CXFolderDialogTestDlg::OnInitDialog\n"));
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// load combo box for view mode
	int i = 0;
	if (IsXP())
	{
		for (i = 0; m_XpModes[i].pszMode != NULL; i++)
		{
			m_comboListViewMode.AddString(m_XpModes[i].pszMode);
		}
	}
	else if (IsVista())
	{
		for (i = 0; m_VistaModes[i].pszMode != NULL; i++)
		{
			m_comboListViewMode.AddString(m_VistaModes[i].pszMode);
		}
	}

	m_comboListViewMode.SetCurSel(0);

	// load icons
	m_hGray  = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_GRAY),
							IMAGE_ICON,16,16, LR_DEFAULTCOLOR);
	m_hGreen = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_GREEN),
							IMAGE_ICON,16,16, LR_DEFAULTCOLOR);
	m_hRed   = (HICON)LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_RED),
							IMAGE_ICON,16,16, LR_DEFAULTCOLOR);

	m_IconXp.SetIcon(m_hGray);
	m_IconVista.SetIcon(m_hGray);
	m_IconOther.SetIcon(m_hGray);

	if (IsXP())
	{
		m_IconXp.SetIcon(m_hGreen);
	}
	else if (IsVista())
	{
		m_IconVista.SetIcon(m_hGreen);
	}
	else
	{
		m_IconOther.SetIcon(m_hRed);
		m_comboListViewMode.EnableWindow(FALSE);
		m_bUseRegistry = FALSE;
		m_bPersist = FALSE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//=============================================================================
void CXFolderDialogTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
//=============================================================================
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

//=============================================================================
void CXFolderDialogTestDlg::OnPaint()
//=============================================================================
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

//=============================================================================
HCURSOR CXFolderDialogTestDlg::OnQueryDragIcon()
//=============================================================================
{
	return (HCURSOR) m_hIcon;
}

//=============================================================================
void CXFolderDialogTestDlg::OnCXFolderDialog()
//=============================================================================
{
	TRACE(_T("in CXFolderDialogTestDlg::OnCXFolderDialog\n"));
	m_Path.SetWindowText(_T(""));

	UpdateData(TRUE);

	CXFolderDialog dlg(m_strInitialFolder);

	dlg.SetOsVersion((CXFolderDialog::XFILEDIALOG_OS_VERSION) m_nOsVersion);
	CXFolderDialog::XFILEDIALOG_OS_VERSION eVer = dlg.GetOsVersion();
	ASSERT(eVer == m_nOsVersion);

	// set initial list view mode
	int nListViewMode = 0;

	if (IsXP())
	{
		nListViewMode = m_XpModes[m_nListViewModeIndex].nMode;
	}
	else if (IsVista())
	{
		nListViewMode = m_VistaModes[m_nListViewModeIndex].nMode;
	}
	else
	{
		nListViewMode = -1;		// no persistence on other OS
		dlg.EnableRegistry(FALSE);
	}

	if ((nListViewMode == 0) && m_bUseRegistry)
		dlg.EnableRegistry(TRUE);

	dlg.SetViewMode(nListViewMode);

	//dlg.SetTitle(_T("Select Folder"));	// defaults to "Select Folder"
	if (dlg.DoModal() == IDOK)
	{
		TRACE(_T("IDOK returned from CXFolderDialog\n"));
		m_Path.SetWindowText(dlg.GetPath());
		m_strInitialFolder = dlg.GetPath();

		if (m_bPersist && (nListViewMode != -1))
		{
			// set combo to whatever user chose

			nListViewMode = dlg.GetViewMode();
			TRACE(_T("nListViewMode=0x%X\n"), nListViewMode);

			int i = 0;
			m_nListViewModeIndex = 0;

			if (IsXP())
			{
				for (i = 0; m_XpModes[i].pszMode != NULL; i++)
				{
					if (m_XpModes[i].nMode == nListViewMode)
					{
						m_nListViewModeIndex = i;
						break;
					}
				}
			}
			else if (IsVista())
			{
				for (i = 0; m_VistaModes[i].pszMode != NULL; i++)
				{
					if (m_VistaModes[i].nMode == nListViewMode)
					{
						m_nListViewModeIndex = i;
						break;
					}
				}
			}

			UpdateData(FALSE);
		}
	}
}

//=============================================================================
void CXFolderDialogTestDlg::OnCFileDialog()
//=============================================================================
{
	TRACE(_T("in CXFolderDialogTestDlg::OnCFileDialog\n"));
	m_Path.SetWindowText(_T(""));
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_Path.SetWindowText(_T("N/A"));
	}
}
