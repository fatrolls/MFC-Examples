// InstanceManagerDemoDlg.cpp : implementation file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#include "stdafx.h"
#include "utsampleabout.h"
#include "InstanceManagerDemo.h"
#include "InstanceManagerDemoDlg.h"
#include "OXInstanceManager.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

extern COXInstanceManager instanceManager;


/////////////////////////////////////////////////////////////////////////////
// CInstanceManagerDemoDlg dialog

CInstanceManagerDemoDlg::CInstanceManagerDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CInstanceManagerDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInstanceManagerDemoDlg)
	m_sTitle = _T("");
	m_nMaxNumber = 2;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInstanceManagerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstanceManagerDemoDlg)
	DDX_Control(pDX, IDC_MAX_NUMBER_SPIN, m_wndMaxNumberSpin);
	DDX_Text(pDX, IDC_TITLE, m_sTitle);
	DDX_Text(pDX, IDC_MAX_NUMBER, m_nMaxNumber);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInstanceManagerDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CInstanceManagerDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLOSE_ALL, OnCloseAll)
	ON_BN_CLICKED(IDC_SET_TITLE, OnSetTitle)
	ON_EN_CHANGE(IDC_MAX_NUMBER, OnChangeMaxNumber)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SETTEXT, OnSetText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstanceManagerDemoDlg message handlers

BOOL CInstanceManagerDemoDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	// ... Set the range of the spincontrol
	m_wndMaxNumberSpin.SetRange(0, 100);
	// ... Initialize the text and allowed number of instances
	SendMessage(WM_SETTEXT);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInstanceManagerDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CInstanceManagerDemoDlg::OnPaint() 
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
HCURSOR CInstanceManagerDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInstanceManagerDemoDlg::OnCloseAll() 
{
	instanceManager.SetMaxAllowedInstances(0);
}

void CInstanceManagerDemoDlg::OnSetTitle() 
{
	if (!UpdateData(TRUE))
		return;

	// Put the string in the shared data
	// ... Lock our additional data before modifying it
	CSingleLock sharedDataLock(&instanceManager.GetAdditionalDataMutex(), TRUE);

	DWORD nMaxSize = instanceManager.GetAdditionalDataSize();
	LPTSTR pszSharedTitle = (LPTSTR)instanceManager.GetAdditionalData();
	if (pszSharedTitle == NULL)
	{
		TRACE0("CInstanceManagerDemoDlg::OnSetTitle : Could not get the additional shared data\n");
		return;
	}

	UTBStr::tcsncpy(pszSharedTitle, nMaxSize, m_sTitle, nMaxSize / sizeof(TCHAR));
	pszSharedTitle[nMaxSize / sizeof(TCHAR) - 1] = _T('\0');

	// ... Unlock the shared data
	pszSharedTitle = NULL;
	sharedDataLock.Unlock();

	// Warn all the other applications that the title has changed
	CDWordArray instanceColl;
	if (instanceManager.GetInstanceCollection(instanceColl))
	{
		int nInstanceIndex = 0;
		DWORD nInstanceID = 0;
		HWND hMainWnd = NULL;
		for (nInstanceIndex = 0; nInstanceIndex  < instanceColl.GetSize(); nInstanceIndex++)
		{
			nInstanceID = instanceColl.GetAt(nInstanceIndex);
			hMainWnd = COXInstanceManager::GetMainWindow(nInstanceID);
			if (hMainWnd != NULL)
				::SendMessage(hMainWnd, WM_SETTEXT, 0, 0);
		}
	}
}

LRESULT CInstanceManagerDemoDlg::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT result = TRUE;
	if ((wParam != 0) && (lParam != 0))
		// ... Normal situation, call base class implementation
		result = DefWindowProc(WM_SETTEXT, wParam, lParam);
	else
	{
		// Received a notification from a sister instances

		// Get the string from the shared data
		// ... Lock our additional data before querying it
		CSingleLock sharedDataLock(&instanceManager.GetAdditionalDataMutex(), TRUE);

//		DWORD nMaxSize = instanceManager.GetAdditionalDataSize();
		LPCTSTR pszSharedTitle = (LPTSTR)instanceManager.GetAdditionalData();

		// Set the new window text
		if (pszSharedTitle != NULL)
			result = DefWindowProc(WM_SETTEXT, 0, (LPARAM)pszSharedTitle);

		// And set the new number
		m_nMaxNumber = instanceManager.GetMaxAllowedInstances();
		UpdateData(FALSE);
	}

	return result;
}

void CInstanceManagerDemoDlg::OnChangeMaxNumber() 
{
	if (m_wndMaxNumberSpin.m_hWnd == NULL)
		// ... Controls not linked yet
		return;

	if (!UpdateData(TRUE))
		return;

	// ... Set the new maximum (may close some instances)
	instanceManager.SetMaxAllowedInstances(m_nMaxNumber);

	// Warn all the other applications that the number has changed
	CDWordArray instanceColl;
	if (instanceManager.GetInstanceCollection(instanceColl))
	{
		int nInstanceIndex = 0;
		DWORD nInstanceID = 0;
		HWND hMainWnd = NULL;
		for (nInstanceIndex = 0; nInstanceIndex  < instanceColl.GetSize(); nInstanceIndex++)
		{
			nInstanceID = instanceColl.GetAt(nInstanceIndex);
			hMainWnd = COXInstanceManager::GetMainWindow(nInstanceID);
			if (hMainWnd != NULL)
				::SendMessage(hMainWnd, WM_SETTEXT, 0, 0);
		}
	}
}

