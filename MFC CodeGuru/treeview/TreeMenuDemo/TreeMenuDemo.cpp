// TreeMenuDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TreeMenuDemo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "TreeMenuDemoDoc.h"
#include "TreeMenuDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoApp

BEGIN_MESSAGE_MAP(CTreeMenuDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CTreeMenuDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoApp construction

CTreeMenuDemoApp::CTreeMenuDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTreeMenuDemoApp object

CTreeMenuDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoApp initialization

BOOL CTreeMenuDemoApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_TREEMETYPE,
		RUNTIME_CLASS(CTreeMenuDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CTreeMenuDemoView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg

#define NUM_ITEMS	9
#define NUM_SUB		3

static _TCHAR *_gszItem[NUM_ITEMS] = 
{
	_T("Fifi"),		_T("Babs Bunny"),	_T("Buster Bunny"),
	_T("Concorde"), _T("Cyote"),		_T("Dizzy Devil"), 
	_T("Elmyra"),	_T("Hampton"),		_T("Plucky Duck")
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTreeMenuFrame m_TreeMenu;
	CImageList m_ImageList;

	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonShow();
	//}}AFX_MSG
	afx_msg void OnHide();
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
	ON_BN_CLICKED(IDC_BUTTON_SHOW, OnButtonShow)
	//}}AFX_MSG_MAP
	ON_MESSAGE(TMFN_HIDE, OnHide)
END_MESSAGE_MAP()

// App command to run the dialog
void CTreeMenuDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoApp commands

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	m_TreeMenu.SubclassDlgItem(IDC_CUSTOM, this);

	// set appearence params
    m_TreeMenu.m_tree.SetItemHeight(35);
	m_TreeMenu.m_tree.SetBorder(TVSBF_XBORDER|TVSBF_YBORDER, 2, 0);
	m_TreeMenu.m_tree.SetBkColor(GetSysColor (COLOR_3DDKSHADOW));
	m_TreeMenu.m_tree.SetTextColor(GetSysColor (COLOR_3DHILIGHT));
	m_TreeMenu.m_tree.SetSelBkColor(RGB(0,0,255));
	m_TreeMenu.m_tree.SetSelTextColor(RGB(0,255,255));
	
	// ImageList
	m_ImageList.Create(IDB_TINYTOON, 32, 1, RGB(255,0,255));
    
    // Attach ImageList to TreeView
    if (m_ImageList)
        m_TreeMenu.m_tree.SetImageList((HIMAGELIST)m_ImageList,TVSIL_NORMAL);


	// Fill TreeView with some stuff...
	TVITEM tvi;
	TVINSERTSTRUCT tvis;
	HTREEITEM hPrev;
	
	tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_CHILDREN;
	tvi.hItem = NULL;
	tvi.cchTextMax = 64;     
	tvi.pszText = _T("Tiny Toons");
	tvi.iImage = 0;
	tvi.iSelectedImage = 0;

	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item = tvi;

	hPrev = m_TreeMenu.GetTreeMenuCtrl()->InsertItem(&tvis);
	
	int i;
	for(i = 0; i < NUM_SUB; i++)
	{
		tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvi.cchTextMax = 64; 
		tvi.pszText = _gszItem[i];
		tvi.iImage = i+1;
		tvi.iSelectedImage = i+1;
	
		tvis.hParent = hPrev;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item = tvi;
		m_TreeMenu.m_tree.InsertItem(&tvis);
	}

	tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_CHILDREN;
	tvi.hItem = NULL;
	tvi.pszText = _T("Tiny Toons 2");
	tvi.iImage = 0;
	tvi.iSelectedImage = 0;

	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item = tvi;

	hPrev = m_TreeMenu.GetTreeMenuCtrl()->InsertItem(&tvis);
	

	for(i = 0; i < NUM_SUB; i++)
	{
		tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvi.pszText = _gszItem[3+i];
		tvi.iImage = i+4;
		tvi.iSelectedImage = i+4;
	
		tvis.hParent = hPrev;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item = tvi;
		m_TreeMenu.GetTreeMenuCtrl()->InsertItem(&tvis);
	}

	tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_CHILDREN;
	tvi.hItem = NULL;
	tvi.pszText = _T("Tiny Toons 3");
	tvi.iImage = 0;
	tvi.iSelectedImage = 0;

	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item = tvi;

	hPrev = m_TreeMenu.GetTreeMenuCtrl()->InsertItem(&tvis);
	

	for(i = 0; i < NUM_SUB; i++)
	{
		tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvi.pszText = _gszItem[6+i];
		tvi.iImage = i+7;
		tvi.iSelectedImage = i+7;
	
		tvis.hParent = hPrev;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item = tvi;
		m_TreeMenu.GetTreeMenuCtrl()->InsertItem(&tvis);
	}


	CString s;
	for(i = 0; i < NUM_SUB*2; i++)
	{
		s.Format("Bookmark No: %i", i+1);

		tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvi.pszText = s.GetBuffer(64);
		tvi.hItem = NULL;
		tvi.iImage = i+1;
		tvi.iSelectedImage = i+4;
	
		tvis.hParent = TVI_ROOT;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item = tvi;
		m_TreeMenu.GetTreeMenuCtrl()->InsertItem(&tvis);

		s.ReleaseBuffer();
	}

	m_TreeMenu.ShowFrameBevel();
	m_TreeMenu.CalcLayout();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnHide() 
{
	m_TreeMenu.ShowWindow(SW_HIDE);
}

void CAboutDlg::OnButtonShow() 
{
	m_TreeMenu.ShowWindow(SW_SHOW);	
}
