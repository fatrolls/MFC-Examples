// ==========================================================================
//				Class Implementation : CNetBrowseDlg
// ==========================================================================

// Source file : NetBrowseDlg.cpp

//==================  Dundas Software ======================================			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetBrowse.h"
#include "NetBrowseDlg.h"
#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
// Data members -------------------------------------------------------------
// protected:
// private:

// Member functions ---------------------------------------------------------
// public:

BEGIN_MESSAGE_MAP(CNetBrowseDlg, CDialog)
	//{{AFX_MSG_MAP(CNetBrowseDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_NET_TREE, OnSelchangedNetTree)
	ON_BN_CLICKED(IDC_REINITIALIZE, OnReinitialize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CNetBrowseDlg::CNetBrowseDlg(CWnd* pParent /*=NULL*/)
: 
CDialog(CNetBrowseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetBrowseDlg)
	m_sComment = _T("");
	m_sDisplayType = _T("");
	m_sProvider = _T("");
	m_sRemoteName = _T("");
	m_sScope = _T("");
	m_sType = _T("");
	m_sUsage = _T("");
	m_sLocalName = _T("");
	m_bShowDisks = TRUE;
	m_bShowCommentNames = TRUE;
	m_nExpandLevel = 0;
	m_bShowPrinters = FALSE;
	m_bReportErrors = TRUE;
	m_nScopeList = 1;
	m_nMaxLevels = 10;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CNetBrowseDlg::~CNetBrowseDlg()
{
}

void CNetBrowseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetBrowseDlg)
	DDX_Control(pDX, IDC_MAX_LEVELS_SPIN, m_wndMaxLevelsSpin);
	DDX_Control(pDX, IDC_SCOPE_LIST, m_wndScopeList);
	DDX_Control(pDX, IDC_EXPAND_LEVEL_SPIN, m_wndExpandLevelSpin);
	DDX_Control(pDX, IDC_NET_TREE, m_wndNetBrowseTree);
	DDX_Text(pDX, IDC_COMMENT, m_sComment);
	DDX_Text(pDX, IDC_DISPLAY_TYPE, m_sDisplayType);
	DDX_Text(pDX, IDC_PROVIDER, m_sProvider);
	DDX_Text(pDX, IDC_REMOTE_NAME, m_sRemoteName);
	DDX_Text(pDX, IDC_SCOPE, m_sScope);
	DDX_Text(pDX, IDC_TYPE, m_sType);
	DDX_Text(pDX, IDC_USAGE, m_sUsage);
	DDX_Text(pDX, IDC_LOCAL_NAME, m_sLocalName);
	DDX_Check(pDX, IDC_DISKS, m_bShowDisks);
	DDX_Check(pDX, IDC_COMMENT_NAMES, m_bShowCommentNames);
	DDX_Text(pDX, IDC_EXPAND_LEVEL, m_nExpandLevel);
	DDX_Check(pDX, IDC_PRINTERS, m_bShowPrinters);
	DDX_Check(pDX, IDC_REPORT, m_bReportErrors);
	DDX_CBIndex(pDX, IDC_SCOPE_LIST, m_nScopeList);
	DDX_Text(pDX, IDC_MAX_LEVELS, m_nMaxLevels);
	//}}AFX_DATA_MAP
}

BOOL CNetBrowseDlg::OnInitDialog()
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

	// Fill combo box with values
	m_wndScopeList.AddString(_T("Connected Resources"));
	m_wndScopeList.AddString(_T("Global Resources"));
	m_wndScopeList.AddString(_T("Persistent Connections"));
	m_wndScopeList.AddString(_T("Recent Connections (Win4)"));
	m_wndScopeList.AddString(_T("Current Context Resources (Win4)"));
	// ... Net scope is 1-based, index in combo is 0-based
	m_wndScopeList.SetCurSel(4);
	m_nScopeList=4;

	// Set the spin ranges
	m_wndMaxLevelsSpin.SetRange(0, 100);
	m_wndExpandLevelSpin.SetRange(0, 10);

	// Set initial values of the net browse control
	SetTreeInitSettings();

	// ... Set the tree as the focussed control
	m_wndNetBrowseTree.SetFocus();
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CNetBrowseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetBrowseDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetBrowseDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNetBrowseDlg::OnSelchangedNetTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UNREFERENCED_PARAMETER(pNMHDR);
	//	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// SHow the information about the currently selected resource
	const NETRESOURCE* pNetResource = m_wndNetBrowseTree.GetCurrentNetResource();
	if (pNetResource != NULL)
	{
		m_sScope.Format(_T("%i"), pNetResource->dwScope);
		m_sScope += _T(" ") + GetScopeName(pNetResource);
		m_sType.Format(_T("%i"), pNetResource->dwType); 
		m_sType += _T(" ") + GetTypeName(pNetResource);
		m_sDisplayType.Format(_T("%i"), pNetResource->dwDisplayType); 
		m_sDisplayType += _T(" ") + GetDisplayTypeName(pNetResource);
		m_sUsage.Format(_T("0x%X"), pNetResource->dwUsage); 
		m_sUsage += _T(" ") + GetUsageName(pNetResource);
		m_sLocalName = pNetResource->lpLocalName; 
		m_sRemoteName = pNetResource->lpRemoteName; 
		m_sComment = pNetResource->lpComment; 
		m_sProvider = pNetResource->lpProvider; 
	}
	else
	{
		m_sScope.Empty();
		m_sType.Empty();
		m_sDisplayType.Empty();
		m_sUsage.Empty();
		m_sLocalName.Empty();
		m_sRemoteName.Empty();
		m_sComment.Empty();
		m_sProvider.Empty();
	}
	UpdateData(FALSE);

	*pResult = 0;
}

CString CNetBrowseDlg::GetScopeName(const NETRESOURCE* pNetResource) const
{
	ASSERT(pNetResource != NULL);
	CString sScopeName;
	switch (pNetResource->dwScope)
	{
	case RESOURCE_CONNECTED:
		sScopeName = _T("(Connected resources)");
		break;
	case RESOURCE_GLOBALNET:
		sScopeName = _T("(Global resources)");
		break;
	case RESOURCE_REMEMBERED:
		sScopeName = _T("(Persistent connections)");
		break;
	case RESOURCE_RECENT:
		sScopeName = _T("(Recent connections)");
		break;
	case RESOURCE_CONTEXT:
		sScopeName = _T("(Current context resources)");
		break;
	default:
		// Let string stay empty
		break;
	}
	return sScopeName;
}

CString CNetBrowseDlg::GetTypeName(const NETRESOURCE* pNetResource) const
{
	ASSERT(pNetResource != NULL);
	CString sTypeName;
	switch (pNetResource->dwType)
	{
	case RESOURCETYPE_ANY:
		sTypeName = _T("(Any resource)");
		break;
	case RESOURCETYPE_DISK:
		sTypeName = _T("(Disk resource)");
		break;
	case RESOURCETYPE_PRINT:
		sTypeName = _T("(Print resource)");
		break;
	case RESOURCETYPE_RESERVED:
		sTypeName = _T("(Reserved resource)");
		break;
	case RESOURCETYPE_UNKNOWN:
		sTypeName = _T("(Unknown resource)");
		break;
	default:
		// Let string stay empty
		break;
	}
	return sTypeName;
}

CString CNetBrowseDlg::GetDisplayTypeName(const NETRESOURCE* pNetResource) const
{
	ASSERT(pNetResource != NULL);
	CString sDisplayTypeName;
	switch (pNetResource->dwDisplayType)
	{
	case RESOURCEDISPLAYTYPE_GENERIC:
		sDisplayTypeName = _T("(Unspecified)");
		break;
	case RESOURCEDISPLAYTYPE_DOMAIN:
		sDisplayTypeName = _T("(Domain)");
		break;
	case RESOURCEDISPLAYTYPE_SERVER:
		sDisplayTypeName = _T("(Server)");
		break;
	case RESOURCEDISPLAYTYPE_SHARE:
		sDisplayTypeName = _T("(Share)");
		break;
	case RESOURCEDISPLAYTYPE_FILE:
		sDisplayTypeName = _T("(file)");
		break;
	case RESOURCEDISPLAYTYPE_GROUP:
		sDisplayTypeName = _T("(Broup)");
		break;
	case RESOURCEDISPLAYTYPE_NETWORK:
		sDisplayTypeName = _T("(Network)");
		break;
	case RESOURCEDISPLAYTYPE_ROOT:
		sDisplayTypeName = _T("(Network Root)");
		break;
	case RESOURCEDISPLAYTYPE_SHAREADMIN:
		sDisplayTypeName = _T("(Administrative Share)");
		break;
	case RESOURCEDISPLAYTYPE_DIRECTORY:
		sDisplayTypeName = _T("(Directory)");
		break;
	case RESOURCEDISPLAYTYPE_TREE:
		sDisplayTypeName = _T("(Tree)");
		break;
	default:
		// Let string stay empty
		break;
	}
	return sDisplayTypeName;
}

CString CNetBrowseDlg::GetUsageName(const NETRESOURCE* pNetResource) const
{
	ASSERT(pNetResource != NULL);
	CString sUsageName;
	if (pNetResource->dwScope == RESOURCE_GLOBALNET)
	{
		if ((pNetResource->dwUsage & RESOURCEUSAGE_CONNECTABLE) == RESOURCEUSAGE_CONNECTABLE)
			sUsageName += _T("Connectable - ");
		if ((pNetResource->dwUsage & RESOURCEUSAGE_CONTAINER) == RESOURCEUSAGE_CONTAINER)
			sUsageName += _T("Container - ");
		if ((pNetResource->dwUsage & RESOURCEUSAGE_NOLOCALDEVICE) == RESOURCEUSAGE_NOLOCALDEVICE)
			sUsageName += _T("Local not needed - ");
		if ((pNetResource->dwUsage & RESOURCEUSAGE_SIBLING) == RESOURCEUSAGE_SIBLING)
			sUsageName += _T("Sibling - ");
		if ((pNetResource->dwUsage & RESOURCEUSAGE_RESERVED) == RESOURCEUSAGE_RESERVED)
			sUsageName += _T("Reserved - ");
		if (!sUsageName.IsEmpty())
		{
			// ... Remove trailing hyphen
			sUsageName = sUsageName.Left(sUsageName.GetLength() - 3);
			// ... Add parentheses
			sUsageName = _T("(") + sUsageName + _T(")");
		}
	}
	return sUsageName;
}


void CNetBrowseDlg::OnReinitialize() 
{
	// Get the data from the GUI
	if (!UpdateData(TRUE))
	{
		// ... Data validation failed, user already warned, so just return
		return;
	}

	// Clear the info controls
	m_sScope.Empty();
	m_sType.Empty();
	m_sDisplayType.Empty();
	m_sUsage.Empty();
	m_sLocalName.Empty();
	m_sRemoteName.Empty();
	m_sComment.Empty();
	m_sProvider.Empty();
	UpdateData(FALSE);

	// ... Set new initial values
	SetTreeInitSettings();
	// ... Build the contents of the tree again
	m_wndNetBrowseTree.BuildTreeContents();
	// ... Select the root if (it exists)
	m_wndNetBrowseTree.SelectItem(m_wndNetBrowseTree.GetRootItem());
}

void CNetBrowseDlg::SetTreeInitSettings()
{
	// Set initial values of the net browse control
	m_wndNetBrowseTree.ShowCommentName(m_bShowCommentNames);
	m_wndNetBrowseTree.ShowDisks(m_bShowDisks);
	m_wndNetBrowseTree.ShowPrinters(m_bShowPrinters);
	// ... Net scope is 1-based, index in combo is 0-based
	m_wndNetBrowseTree.SetResourceScope(m_nScopeList + 1);
	m_wndNetBrowseTree.SetMaxNumLevels(m_nMaxLevels);
	m_wndNetBrowseTree.SetInitialExpandLevel(m_nExpandLevel);
	m_wndNetBrowseTree.ReportErrors(m_bReportErrors);
}

