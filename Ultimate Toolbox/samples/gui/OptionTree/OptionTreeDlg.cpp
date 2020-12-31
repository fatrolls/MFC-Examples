// OptionTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OptionTree.h"
#include "OptionTreeDlg.h"
#include "utsampleabout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionTreeDlg dialog

COptionTreeDlg::COptionTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionTreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COptionTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionTreeDlg)
	DDX_Control(pDX, IDC_UPDATE_INFO, m_staticUpdateInfo);
	DDX_Control(pDX, IDC_SEPARATOR2, m_separator2);
	DDX_Control(pDX, IDC_SEPARATOR1, m_separator1);
	DDX_Control(pDX, IDC_TREE_OPTION, m_treeOption);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptionTreeDlg, CDialog)
	//{{AFX_MSG_MAP(COptionTreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(OTN_OPTIONCHANGED, IDC_TREE_OPTION, OnOptionChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionTreeDlg message handlers

BOOL COptionTreeDlg::OnInitDialog()
{
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
	
	// TODO: Add extra initialization here
	
    // add data
	int nFolderImageIndex=m_treeOption.AddImage(IDB_FOLDER,RGB(255,255,255));
	ASSERT(nFolderImageIndex!=-1);
	HTREEITEM hFilesFolder=m_treeOption.AddControlGroup(_T("Files and Folders"),
		NULL,TRUE,nFolderImageIndex,nFolderImageIndex);
	m_treeOption.AddCheckBox(1100,
		_T("Show popup descriptions for folder and desktop items"), hFilesFolder);
	m_treeOption.AddCheckBox(1101,
		_T("Display the full path in title bar"), hFilesFolder);
	m_treeOption.AddCheckBox(1102,
		_T("Display compressed files and folders with alternate color"), hFilesFolder);
	m_treeOption.AddCheckBox(1103,
		_T("Show file attributes in Detail View"), hFilesFolder);
	m_treeOption.AddCheckBox(1104,
		_T("Show Map Network Drive button in toolbar"), hFilesFolder);
	m_treeOption.AddCheckBox(1105,
		_T("Hide file extensions for known file types"), hFilesFolder);

	HTREEITEM  hHiddenFiles=m_treeOption.AddControlGroup(_T("Hidden Files"),
		hFilesFolder,TRUE,nFolderImageIndex,nFolderImageIndex);
	m_treeOption.AddRadioButton(1000,_T("Show all files"),hHiddenFiles);
	m_treeOption.AddRadioButton(1001,
		_T("Do not show system or hidden files"),hHiddenFiles,TRUE);
	m_treeOption.AddRadioButton(1002,_T("Do not show hidden files"),hHiddenFiles);
	
	m_treeOption.AddCheckBox(1106,
		_T("Allow all uppercase names"), hFilesFolder);
	m_treeOption.AddCheckBox(1107,
		_T("Remember each folder's view settings"), hFilesFolder);
	
	int nVisualImageIndex=m_treeOption.AddImage(IDB_VISUAL,RGB(255,255,255));
	ASSERT(nVisualImageIndex!=-1);
	HTREEITEM hVisualSettings=m_treeOption.AddControlGroup(_T("Visual Settings"),
		NULL,TRUE,nVisualImageIndex,nVisualImageIndex);
	m_treeOption.AddCheckBox(1200,
		_T("Hide icons when desktop is viewed as Web page"), hVisualSettings);
	m_treeOption.AddCheckBox(1201,
		_T("Smooth edges of screen fonts"), hVisualSettings);
	m_treeOption.AddCheckBox(1202,
		_T("Show window contents while dragging"), hVisualSettings);

	m_treeOption.LoadState(_T("OptionTree"),_T("Folder Options"));

	m_staticUpdateInfo.SetWindowText(_T("Information about changes in the option states"));
	m_staticUpdateInfo.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	m_staticUpdateInfo.SetTextColor(RGB(0,0,128));
	CSize szGap=CSize(150,0);
	m_staticUpdateInfo.SetGapSize(szGap);
	m_staticUpdateInfo.SetHorzAlignment(OX_ALIGNHORZ_RIGHT);
	m_staticUpdateInfo.SetVertAlignment(OX_ALIGNVERT_CENTER);
	m_staticUpdateInfo.SetScrollDirection(180);
	m_staticUpdateInfo.SetScrollSpeed(90);
	m_staticUpdateInfo.StartScrolling(TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COptionTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COptionTreeDlg::OnPaint() 
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
HCURSOR COptionTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void COptionTreeDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_treeOption.SaveState(_T("OptionTree"),_T("Folder Options"));
	CDialog::OnCancel();
}

void COptionTreeDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_treeOption.SaveState(_T("OptionTree"),_T("Folder Options"));
	CDialog::OnOK();
}

void COptionTreeDlg::OnOptionChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMOPTIONTREE* pNMOptionTree=(NMOPTIONTREE*)pNMHDR;
	// TODO: Add your control notification handler code here

	HTREEITEM hItem=pNMOptionTree->hItem;
	CString sNewText=_T("Option <")+m_treeOption.GetItemText(hItem)+_T("> has been ");
	sNewText+=(pNMOptionTree->nNewCheck==OTITEM_CHECKED ? 
		_T("Checked") : _T("Unchecked"));
	m_staticUpdateInfo.SetWindowText(sNewText,TRUE);
	
	*pResult = 0;
}
