/******************************************************************************
// This sample demo demonstrates the NNTP protocol implementation as presented in 
// Ultimate TCP/IP vrsion 3.0
// For additional information please see RFC 977
// This sample program enables you to connect to a NNTP server and read and download the 
// available articles in each newsgroup
// 
// Downloading news group is done in two ways 
//	1 ) Directly from the server. This process may take along time to 
//		finish since there is virtually new
//	    newsgroup added every moment. To save you time, after a successful 
//		connection you can 
//		save the newsgroups list to a file where you may load to the CUT_NNTPClient 
//		class before you even make the connection as in the next case
//	2 ) The second option is to load the list of newsgroups from a file where you
//		 have already saved the servers list of newsgroups this list can be updated 
//		 when everb you wish latter
//		
// Article, the same process as outlined above, you can down load articles and 
//		save alist of them fro the next connection for each group however, for the
//		 purpose of simplicity we have not demonstrated this option since the Article
//		 lists are changing more frequently  than the list of newsgroups
//	Articles message parts 
//		For each article the CUT_NNTPClient class retrives a summary of information before it is downloaded
//		this information is included in the UT_ARTICLEINFO structure which is used in this demonstration program to populate the 
//		ListControl IDC_ARTICLES_LIST 
//	Articles decoding and attachments
//		When a message is encoded in MIME the CUT_Msg is used to decode and parse the body of the message 
//		The decoded message body is what we display on the Rich edit control  IDC_RICHTEXTCTRL1
//		if the message contains an attachmnet other than the message body (YES!, The message bosy is still considered 
//		an attachment if it is encoded in MIME ) if the message contains other attachments the name of these attachments 
//	    will be displayed in the ComboBox IDC_COMBO1
// ===================================================================
//	 Ultimate TCP/IP 3.0 
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================
*******************************************************************************/
#include "stdafx.h"
#include <process.h>
#include "NNTPclient.h"
#include "NNTPclientDlg.h"
#include "utmime.h"
#include "utuuencode.h"
#include "PostDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////// /////////////////////////////////////////////////////////////
///   Headers of the Article List Control										  ///////
#define NUM_COLUMNS		6														  ///////
_TCHAR *szColumns[] = {_T("ID") , _T("Subject"), _T("Author"), _T("Date"),_T("References"),_T("Lines")};  //////
////////////////////////////////////////////////////////////////////////////////////////


// Since we are going to attempt to access some of the dialog class memebers from the static function 
// we need to declare a global pointer to the class
// CNNTPclientDlg *g_ThisClass;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#pragma warning ( disable : 4511 4512 )

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
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 )

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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNNTPclientDlg dialog

CNNTPclientDlg::CNNTPclientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNNTPclientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNNTPclientDlg)
	m_bLoadFromFile = FALSE;
	m_strGroupFileName = _T("");
	m_strServerName = _T("");
	m_strSelecteGroup = _T("");
	m_strAttachment = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pMapFileDataSource = NULL;
}

CNNTPclientDlg::~CNNTPclientDlg()
{
	if (m_pMapFileDataSource != NULL)
		delete m_pMapFileDataSource;
}

void CNNTPclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNNTPclientDlg)
	DDX_Control(pDX, IDC_SAVE, m_saveAttachBtn);
	DDX_Control(pDX, IDC_CHECK1, m_chkLoadBtn);
	DDX_Control(pDX, IDC_COMBO1, m_CBattachments);
	DDX_Control(pDX, IDC_STATUC_STATIC, m_staticWindow);
	DDX_Control(pDX, IDC_ANIMATE, m_animateWnd);
	DDX_Control(pDX, IDC_SERVERS_COMBO, m_serversCombo);
	DDX_Control(pDX, IDC_GROUP_LIST, m_listGroup);
	DDX_Control(pDX, IDC_ARTICLES_LIST, m_articlesList);
	DDX_Check(pDX, IDC_CHECK1, m_bLoadFromFile);
	DDX_Text(pDX, IDC_GroupFileName, m_strGroupFileName);
	DDX_CBString(pDX, IDC_SERVERS_COMBO, m_strServerName);
	DDX_LBString(pDX, IDC_GROUP_LIST, m_strSelecteGroup);
	DDX_Control(pDX, IDC_RICHTEXTCTRL1, m_richText);
	DDX_CBString(pDX, IDC_COMBO1, m_strAttachment);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNNTPclientDlg, CDialog)
	//{{AFX_MSG_MAP(CNNTPclientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_LBN_DBLCLK(IDC_GROUP_LIST, OnDblclkGroupList)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDOK, OnOK)
	ON_NOTIFY(LVN_INSERTITEM, IDC_ARTICLES_LIST, OnInsertitemArticlesList)
	ON_NOTIFY(NM_DBLCLK, IDC_ARTICLES_LIST, OnDblclkArticlesList)
	ON_NOTIFY(NM_CLICK, IDC_ARTICLES_LIST, OnClickArticlesList)
	ON_BN_CLICKED(IDC_SAVE_NEWS_GROUPS, OnSaveNewsGroups)
	ON_CBN_SELCHANGE(IDC_SERVERS_COMBO, OnSelchangeServersCombo)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_POST_NEW, OnPostNew)
	ON_BN_CLICKED(IDC_DLETE, OnDlete)
	ON_BN_CLICKED(IDC_REPLY, OnReply)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNNTPclientDlg message handlers
/****************************************************************************
Function name	: CNNTPclientDlg::OnInitDialog
Return type		: BOOL 
Description	    : 
	make sure buttons dependent on other operations are disabled 
	Set this dialog as the parent window of our derived NNTP class
	put an anchor for the thread handle 
	Get ready with the list control to show the articles
	initialize the columns you will need.
	Initialize the LV_COLUMN structure.
	The mask specifies that the fmt, width, pszText, and subitem members
	of the structure are valid.
***************************************************************************/
BOOL CNNTPclientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
// v4.2 conditional expression is constant... 
#pragma warning ( disable : 4127 )
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
#pragma warning ( default : 4127 )

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

	// Lets make sure buttons dependent on other operations are disabled 
	CWnd * pWnd = GetDlgItem(IDC_GroupFileName);	
	pWnd->EnableWindow (FALSE);
	pWnd = GetDlgItem(IDC_SAVE_NEWS_GROUPS);
	pWnd->EnableWindow (FALSE);
	m_saveAttachBtn.EnableWindow(FALSE);

	// initialize the pointer to this class
	// Set this dialog as the parent window of our derived NNTP class
	m_nntpClient.SetParentWindow ((CNNTPclientDlg *)this);
	
	// put an anchor for the thread handle 
	m_ThreadHandle = NULL; 
	m_bisAborted = FALSE;
	
	LV_COLUMN lvC;      		// list view column structure
	int index;
	
	// Get ready with the list control to show the articles
	// Now initialize the columns you will need.
	// Initialize the LV_COLUMN structure.
	// The mask specifies that the fmt, width, pszText, and subitem members
	// of the structure are valid.

	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align column
	lvC.cx = 75;            // width of column in pixels

	// Add the columns. headers
	for (index = 0; index < NUM_COLUMNS; index++)
			{
			lvC.iSubItem = index;
			lvC.pszText = szColumns[index];
		
			if (m_articlesList.InsertColumn(index, &lvC) == -1)
				return FALSE;
			}
	m_articlesList.EnableWindow (FALSE);
	m_listGroup.EnableWindow (FALSE);

	m_icounter = 0;
 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNNTPclientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNNTPclientDlg::OnPaint() 
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
HCURSOR CNNTPclientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/*****************************************************

// Function name	: CNNTPclientDlg::OnConnect
// Return type		: void 
// Description	    : 
  User clicked on the Connect button
******************************************************/

void CNNTPclientDlg::OnConnect() 
{
	unsigned threadID;

	m_bisAborted = FALSE;
	// read the data from all the controls
	UpdateData();
	if (m_strServerName.GetLength () < 3)
		MessageBox(_T("Please specify a news server"),_T("Error"),MB_OK|MB_ICONINFORMATION);
	else{
		// make sure there is no other thread going on 
		if (m_ThreadHandle != NULL) 
			MessageBox(_T("Another operation is already in progress; please wait."));
		else
		{
			m_listGroup.ResetContent ();
			m_ThreadHandle = (HANDLE) _beginthreadex(NULL,0,ThreadProc,
				reinterpret_cast<void*>(this),
				0,&threadID);
			m_animateWnd.ShowWindow (SW_SHOW);
		}
	}

}
/*****************************************************


// Function name	: CNNTPclientDlg::ThreadProc
// Return type		: unsigned __stdcall 
// Argument         : LPVOID pThis
// Description	    : 
	Perform the conmnection inside a thread so we can do 
	other operations while we are attempting to connect	
	If the user selected to load the groups from a file 
		then first 	load the files Update the newsGroups list box 	
			and then 
		attempt to connect to the server 
	OTHERWISE, 
		Connect to the server and then download the newsgroups
		in this case the list control is updated from within our
		derived Class CMyNntpClass See OnNGetNewsGroupList(LPCSTR newsGroupTitle) in MyNntpClass.cpp 
****************************************************/
unsigned __stdcall CNNTPclientDlg::ThreadProc( LPVOID pThis){
	
	int rt = UTE_SUCCESS;// error code 

		// we need access to our class since this function is a static function 
	CNNTPclientDlg *dlg = static_cast<CNNTPclientDlg*> (pThis);

		// a temporary string buffer to push our status message on
	CString statusMessage;
	dlg->m_listGroup.EnableWindow (FALSE);
	dlg->m_articlesList.EnableWindow (FALSE);
	CWnd *SaveBtn = dlg->GetDlgItem(IDC_SAVE_NEWS_GROUPS);
	// start loading the news groups
	//if the user have selected to load news groups from a disk file 
	if (dlg->m_bLoadFromFile)
	{
		//in the files distributed with this sample we have not selected the only groups that we are 
		//intersetd in so the reloading of the news groups may also take time 
		// my suggestion is to have two files for each news server 
		// the first file would be the one that includes all the news groups available 
		// for this severer 
		// THe other file would  include only the news groups the suer is intersted in subscribing to
		dlg->m_animateWnd.Open (IDR_COPY_AVI);
		statusMessage += _T("Read archive file for news groups,\r\n this may take a few minutes");
		dlg->m_staticWindow.SetWindowText(statusMessage);
		// load the news groups from the file  specified by the user
		rt = dlg->m_nntpClient.NLoadNewsGroupList (dlg->m_strGroupFileName);
		if (rt != UTE_SUCCESS)
		{
			statusMessage = CUT_ERR::GetErrorString (rt);
			dlg->m_staticWindow.SetWindowText(statusMessage);
			dlg->m_animateWnd.Stop ();
			dlg->m_animateWnd.ShowWindow (SW_HIDE);
			dlg->m_ThreadHandle = NULL;
			SaveBtn->EnableWindow (FALSE);
			dlg->m_articlesList.EnableWindow (FALSE);
			return 2;
		}
		long count = dlg->m_nntpClient.NGetNewsGroupCount ();
		for (long loop = 0; (loop < count ) ; loop ++)
		{
			// v4.2 should probably use overload of NGetNewsGroupTitle
			dlg->AddGroup (dlg->m_nntpClient.NGetNewsGroupTitle (loop));
			if (dlg->m_bisAborted )
			{ 
			dlg->m_animateWnd.Stop ();
			dlg->m_animateWnd.ShowWindow (SW_HIDE);
			dlg->m_ThreadHandle = NULL;
			dlg->m_articlesList.EnableWindow (FALSE);
			return 0;
			}
		}
		SaveBtn->EnableWindow (TRUE);
		
		//  now that we have read the news groups from a file then 
		// lets connect to the server
	}
	dlg->m_animateWnd.Open (IDR_CONNECT_AVI);
	statusMessage = _T("Attempting to connect to ") +dlg->m_strServerName;
	dlg->m_staticWindow.SetWindowText(statusMessage);
	// attaempt a connection to the server specified by the user
	rt = dlg->m_nntpClient.NConnect(dlg->m_strServerName);
	if (rt == UTE_SUCCESS)
	{
		dlg->m_animateWnd.Open (IDR_COPY_AVI);
			statusMessage = CUT_ERR::GetErrorString (rt);
		
		if (!dlg->m_bLoadFromFile)
			// if the user did not load the news groups from an archived file then attempt to download
			// the groups from the server
			// contact the server for the list of news groups 
		{
			statusMessage += _T("Now attempting to download newsGroups \r\nthis may take a few minutes");
			dlg->m_staticWindow.SetWindowText(statusMessage);
			// Now we ask the server to send us a list of the groups available on it
			// The list control is upodated from within our derived Class CMyNntpClass
			// See OnNGetNewsGroupList(LPCSTR newsGroupTitle) in MyNntpClass.cpp 

			rt = dlg->m_nntpClient.NGetNewsGroupList (0);
			if (rt == UTE_SUCCESS){
				SaveBtn->EnableWindow (TRUE);
				dlg->m_listGroup.EnableWindow (TRUE);
				}
			else // well if we don't have news groups so why the button is enabled
			{
				SaveBtn->EnableWindow (FALSE);
				dlg->m_articlesList.EnableWindow (FALSE);
			}
		}
		else
		{
			dlg->m_listGroup.EnableWindow (TRUE);
		}
		statusMessage = CUT_ERR::GetErrorString (rt);
		dlg->m_staticWindow.SetWindowText(statusMessage);
		
	}
	else{
		statusMessage = CUT_ERR::GetErrorString (rt);
		dlg->MessageBox(statusMessage);
		// well if we don't have news groups so why the button is enabled
		SaveBtn->EnableWindow (FALSE);
		dlg->m_listGroup.EnableWindow (FALSE);
	}
	
	// make sure we set it back so other threads can start
	dlg->m_animateWnd.Stop ();
	dlg->m_animateWnd.ShowWindow (SW_HIDE);
	dlg->m_ThreadHandle = NULL;
	return 0;
	
}
/************************************************


// Function name	: CNNTPclientDlg::OnDblclkGroupList
// Return type		: void 	
// Description	    : 
	the user double clicks on the news groups list to 
	subscribe to it. so lets spin off a thread to download 
	the summary information for each article 

*************************************************/
void CNNTPclientDlg::OnDblclkGroupList() 
{
	unsigned threadID;

	m_bisAborted = FALSE;
	
	UpdateData();
	if (m_ThreadHandle != NULL) 
			MessageBox(_T("Another operation is in progress"));
		else
		{
			m_articlesList.EnableWindow (FALSE);
			m_staticWindow.SetWindowText(_T("Attempting to download articles list from the server"));
			m_ThreadHandle = (HANDLE) _beginthreadex(NULL,0,ArticlsThreadProc,
				reinterpret_cast<void*>(this),
				0,&threadID);
			m_animateWnd.Open (IDR_COPY_AVI);
			m_animateWnd.ShowWindow (SW_SHOW);
				m_articlesList.DeleteAllItems();

			m_currentSelectedMsg.ClearHeader();
			m_richText.SetWindowText(_T(""));
		}
		
}
/************************************************


// Function name	: CNNTPclientDlg::OnCheck1
// Return type		: void 
// Description	    : 
  The user checks the (Load News groups from file)
	check box so lets invoke the OpenFile Dialog to 
	allow him/her 	to browse their pc and get the 
	full path of the file to load the newsgroups from

************************************************/
void CNNTPclientDlg::OnCheck1() 
{
	CWnd * load_file = GetDlgItem(IDC_GroupFileName);
	if 	(m_bLoadFromFile )
	{
		load_file->EnableWindow(FALSE);
		m_bLoadFromFile = FALSE;
	}
	else{
		CString filename;
		filename = _T("msnews.txt");
		CFileDialog fileDlg(TRUE, NULL, filename,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ,_T("Text Files (*.txt)|*.txt||"),this) ;
		if(fileDlg.DoModal() ==IDOK){
			//save here
			load_file->SetWindowText( fileDlg.GetPathName());
			UpdateData();
			m_bLoadFromFile = TRUE;
			}
		else
		{ // the user did not enter a file name so lets uncheck this button
			m_bLoadFromFile = FALSE;			//
			CheckDlgButton (IDC_CHECK1,0);
		}

	}
}
/*********************************************************************


// Function name	: CNNTPclientDlg::ArticlsThreadProc
// Return type		: unsigned __stdcall 
// Argument         : LPVOID pThis	
// Description	    : 
	  The user have double clicked on a selection from the Newsroups list box,
	and	this function was called through the beginthread from 
	So lets find the list of newsArticles and lets add them to our ListControl
	This function is static function so to access the class non static members
	we need a pointer to the class which is what we pass it in the LPVOID parameter

*********************************************************************/
unsigned __stdcall CNNTPclientDlg::ArticlsThreadProc( LPVOID pThis){
	CNNTPclientDlg *dlg = static_cast<CNNTPclientDlg*> (pThis);
	CString statusMessage,temp;
	int rt = dlg->m_nntpClient.NSelectNewsGroup (dlg->m_strSelecteGroup);
	if (rt == UTE_SUCCESS)
	{
		// we succeded in selecting the news group so lets attempt to populate the 
		// list control  with the list of articles
		dlg->BeginWaitCursor ();
		dlg->m_icounter = 0;
		dlg->m_nntpClient.NGetArticleList(0);
		dlg->EndWaitCursor ();
		dlg->m_articlesList.EnableWindow (TRUE);

	}
	statusMessage = CUT_ERR::GetErrorString (rt);
	dlg->m_staticWindow.SetWindowText(statusMessage);
	dlg->m_animateWnd.ShowWindow (SW_HIDE);
	dlg->m_ThreadHandle = NULL;
	return 0;
}
/*************************************************************************
	// Description	    : 
	  When the user wishes to Abort the thread that already started so lets
	tell our threads about the user intention 
	The m_bisAborted Boolean value is tested in the IsAborted function of 
	our derived class See MyNntpClass.cpp in this project 

*************************************************************************/
void CNNTPclientDlg::OnCancel() 
{
	m_bisAborted = 	TRUE;
	
}
/************************************************************************


// Function name	: CNNTPclientDlg::OnOK
// Return type		: void 
// Description	    : 
	The user clicked on the exit button so lets make sure that we terminate 
	any thread that could have already started
*************************************************************************/
void CNNTPclientDlg::OnOK() 
{
	m_bisAborted = TRUE;
	DWORD exitCode = 0;
	if (m_ThreadHandle != NULL){
		m_staticWindow.SetWindowText(_T("Please Wait..."));
		WaitForSingleObject(m_ThreadHandle, m_nntpClient.GetReceiveTimeOut ()/1000);
		TerminateThread(m_ThreadHandle,exitCode);
		m_nntpClient.NClose ();
		CloseHandle(m_ThreadHandle);
	}

	CDialog::OnOK ();
}
/***************************************************************************


// Function name	: CNNTPclientDlg::OnInsertitemArticlesList
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
// Description	    : 
	When we insert one main item Insert the rest of the
	Sub items for the other columns in the List Control
	It would be alot easier for you to use the MFC Grid from Ultimate Grid or
	the Extended tree control from  Ultimate Tool box of The Ultimate Toolbox Tools
****************************************************************************/
void CNNTPclientDlg::OnInsertitemArticlesList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CString temp;
	m_articlesList.SetItemText(pNMListView-> iItem,1,m_strSubject );
	m_articlesList.SetItemText( pNMListView-> iItem,2,m_strAuthor );
	m_articlesList.SetItemText(pNMListView-> iItem,3,m_strDate );
	m_articlesList.SetItemText(pNMListView-> iItem,4,m_strRefrence );
	m_articlesList.SetItemText(pNMListView-> iItem,5,m_strNumberOfLines );
	*pResult = 0;	
}
/*************************************************************************
	

// Function name	: CNNTPclientDlg::OnDblclkArticlesList
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
// Description	    : 
	  The user Double clicked on the first cell of the Article list control

*************************************************************************/
void CNNTPclientDlg::OnDblclkArticlesList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_saveAttachBtn.EnableWindow(FALSE);
	
	if (m_nntpClient.IsConnected())
	{
		// clear the edit control
		m_richText.SetWindowText (_T(""));
		
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		
		UT_ARTICLEINFO *art;
		art = m_nntpClient.NGetArticleInfo (pNMListView->iItem);
		if (art != NULL)
		{
			m_CBattachments.ResetContent();
			
			// free the previous data source object (if any)
			if (m_pMapFileDataSource != NULL)
			{
				delete m_pMapFileDataSource;
				m_pMapFileDataSource = NULL;
			}
			
			CUT_Msg msg;
			m_pMapFileDataSource = new CUT_MapFileDataSource(0, art->nByteCount);
			CUT_MapFileDataSource& msgBody = *m_pMapFileDataSource;
			
			BeginWaitCursor();
			
			// Get the article from the server (this article is identified by the
			// unique ID in the leftmost column of the list control)
			CString sCurrentArticleID = m_articlesList.GetItemText(pNMListView->iItem, 0);
			int ret = m_nntpClient.NGetArticle(sCurrentArticleID, msgBody);
			if (ret == UTE_SUCCESS)
			{
				msg.LoadMessage(msgBody);
				m_currentSelectedMsg.ClearHeader();
				m_currentSelectedMsg.LoadMessage(msgBody);
				// v4.2 CString can take either char or wchar, but could use overload of GetMessageBody
				CString str = msg.GetMessageBody();
				m_richText.SetWindowText(str);
				int numAttach;
				if ((numAttach = msg.GetAttachmentNumber()) > 0)
				{
					_TCHAR name[MAX_PATH];
					_TCHAR type[MAX_PATH];
					
					m_saveAttachBtn.EnableWindow(TRUE);
					for (int ii = 0 ; ii < numAttach; ii++)
					{
						msg.GetAttachmentInfo (ii,name,MAX_PATH,type,MAX_PATH);
						if (_tcslen(name))
							m_CBattachments.InsertString (m_CBattachments.GetCount() ,name );
						else
							m_CBattachments.InsertString (m_CBattachments.GetCount() ,type );
					}
				}

				SetDlgItemInt(IDC_ATTACH_NUM, numAttach);
			}
			
			EndWaitCursor();
			m_staticWindow.SetWindowText(CUT_ERR::GetErrorString (ret));
		}
	}
	else
	{
		m_staticWindow.SetWindowText(_T("Error: no connection"));
	}
	
	*pResult = 0;
}

/*************************************************************************
	

// Function name	: CNNTPclientDlg::OnClickArticlesList
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
// Description	    : 
	  The user clicked on the first cell of the Article list control

*************************************************************************/
void CNNTPclientDlg::OnClickArticlesList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnDblclkArticlesList(pNMHDR, pResult);
}

/*******************************************************
// Function name	: CNNTPclientDlg::OnSaveNewsGroups
// Return type		: void 
// Description	    : 
  The user clicked on the save NewsGroups Button

*******************************************************/
void CNNTPclientDlg::OnSaveNewsGroups() 
{
	CString filename;
	filename = "test.txt";
	CFileDialog fileDlg(FALSE, NULL, filename,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("Text Files (*.txt)|*.txt||"),this) ;
	if(fileDlg.DoModal() ==IDOK){
		//save here
		CString path = fileDlg.GetPathName();
		int ret = m_nntpClient.NSaveNewsGroupList (path);
		m_staticWindow.SetWindowText(CUT_ERR::GetErrorString (ret));
	}			
}
/******************************************************
// Function name	: CNNTPclientDlg::OnSelchangeServersCombo

// Return type		: void 
// Description	    : 
	The user have selected another server so make sure we 
	are not reading rom the same newsgroups file for old servers

*******************************************************/
void CNNTPclientDlg::OnSelchangeServersCombo() 
{
		m_bLoadFromFile = FALSE;			//
			CheckDlgButton (IDC_CHECK1,0);
	
}

/******************************************************
// Function name	: CNNTPclientDlg::OnSave

// Return type		: void 
// Description	    : 
	When the user clicks on this button there is two senarios
	the first
		is where the user had already selected the save
		when download the article so the file already exist on the 
		directory he has specified
		So we don't need to contact the server to download the article 
		to download it so we just open the file using the CUT_Msg object 
		and decode it to the file specified by the user.
	The second senario 
		is where the article is not available on the client machine so we need to 
		ask the server for it. We don't realy need to use file oriented datasource BUT
		the limitation is the stack memeory. So we better store it to a file. However, this
		approach is left for the programmer. Since, we need to makle things simple. and 
		the Steps are almost the same
******************************************************/
void CNNTPclientDlg::OnSave() 
{
// v4.2 conditional expression is constant... 
#pragma warning ( disable : 4127 )
	ASSERT(m_pMapFileDataSource != NULL);
#pragma warning ( default : 4127 )


	UpdateData();
	
	CUT_Msg msgBody;
	int ret = msgBody.LoadMessage(*m_pMapFileDataSource);
	if (ret == UTE_SUCCESS)
	{
		if (msgBody.GetAttachmentNumber() > 0) 
		{ 
			// get the index of the chosen file 
			int ii = m_CBattachments.GetCurSel ();
			if (ii == CB_ERR || m_strAttachment.IsEmpty())
			{

				MessageBox(_T("ComboBox error.\n\nYou must select a substring from the combo box then click the \"Save attachment\" button."));
			}
			else
			{
				m_CBattachments.FindString (ii,m_strAttachment);
				m_strAttachment.Replace (_T("/"),_T("."));
				// prompt user for the path and name of the file to save as
				CFileDialog fileDlg(FALSE, NULL, m_strAttachment, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files (*.*)|*.*||"), this);
				if(fileDlg.DoModal() ==IDOK)
				{
					CString path = fileDlg.GetPathName();
					int ret = 0;
					ret = msgBody.Decode(ii, path);
					m_staticWindow.SetWindowText(CUT_ERR::GetErrorString(ret));
				}			
			}
		}
	}
	else
	{
		m_staticWindow.SetWindowText(CUT_ERR::GetErrorString(ret));
	}
}

/***********************************************************
	Post a new article on the selected newsgroup
	The prefered way of doing so is to use CUT_Msg class 
	however you may post the message with the three headers (Subject, From, Newsgroups)
	and the article body.
	The process of sending the message was not included in a thread by itself 
	since the process is already demnstrated on the above functions.

	We want to show the "News reader", "Orgainzation" and other headers  too 
	so we will be using the CUT_Msg Class
***********************************************************/
void CNNTPclientDlg::OnPostNew() 
{
	CPostDlg postDlg;
	int rt = UTE_SUCCESS;
	CUT_Msg msg;
	UpdateData();
	if (postDlg.DoModal () == IDOK)
	{
		// lets make sure we are connected 
		if (!m_nntpClient.IsConnected ())
		{
			if (( rt = m_nntpClient.NConnect (m_strServerName)) != UTE_SUCCESS)
			{
				MessageBox(CUT_ERR::GetErrorString (rt),_T("Error: connection failed"));
				return ;
			}
		}
		// we can do this and get on with it but we want to be able to show the 
		//rt = m_nntpClient.NPostArticle(postDlg.m_strTargetNewsGroups ,postDlg.m_strFrom ,postDlg.m_strSubject ,postDlg.m_strArtBody );
		msg.AddHeaderField (postDlg.m_strTargetNewsGroups,UTM_NEWSGROUPS);
		msg.AddHeaderField (postDlg.m_strFrom ,UTM_FROM);
		msg.AddHeaderField (_T("Ultimate TCP/IP News Reader Demo"),UTM_XNEWS_READER);
		msg.AddHeaderField (postDlg.m_strSubject,UTM_SUBJECT);
		
		// Add the attachment, if specified
		if (!postDlg.m_sAttachment.IsEmpty())
			msg.AddAttachment (postDlg.m_sAttachment, NULL);

		msg.SetMessageBody (postDlg.m_strArtBody);
		rt = m_nntpClient.NPostArticle (msg);
		
		MessageBox(CUT_ERR::GetErrorString (rt));

		if(rt == UTE_SUCCESS)
			OnDblclkGroupList();
	}

}
/*************************************************
	In the following function we will atempt to delete 
	the selected article from the server
	This function only works if the the server allows us to do so
	and we are the people who have posted this message 

  The process of sending the delete request is accomplished by sending 
  a  "Control: Cancel <msgId>


***************************************u*********/
void CNNTPclientDlg::OnDlete() 
{
	CUT_Msg CancelMsg;
	char buf[MAX_PATH];
	int rt = UTE_SUCCESS;
	m_currentSelectedMsg.GetHeaderByType (UTM_MESSAGE_ID,buf,MAX_PATH-1);
	CString strControl = _T("Cancel");
	strControl +=(LPCSTR) buf;
	// we add the control header first
	CancelMsg.AddHeaderField (strControl,UTM_CUSTOM_FIELD,_T("Control:"));
	// now lets read the headers we are intersted in to make sure we are posting to the correct news group(s)
	// that the message was posted to	
	
	// news group
	m_currentSelectedMsg.GetHeaderByType(UTM_NEWSGROUPS,buf,MAX_PATH-1);
	CancelMsg.AddHeaderField (buf,UTM_NEWSGROUPS);
	// From
	m_currentSelectedMsg.GetHeaderByType(UTM_FROM,buf,MAX_PATH-1);
	CancelMsg.AddHeaderField (buf,UTM_FROM);
	// News reader
	CancelMsg.AddHeaderField (_T("The Ultimate Toolbox news reader demo"),UTM_XNEWS_READER);
	// Subject
	m_currentSelectedMsg.GetHeaderByType(UTM_SUBJECT,buf,MAX_PATH-1);
	CancelMsg.AddHeaderField (buf,UTM_SUBJECT);
	//	body 
	CancelMsg.SetMessageBody (_T("Please cancel the message above \r\n Ultimate TCP/IP"));

	rt = m_nntpClient.NPostArticle (CancelMsg);
	MessageBox(CUT_ERR::GetErrorString (rt));

	if(rt == UTE_SUCCESS)
		OnDblclkGroupList();
	
}
/***********************************************************************
	The process of replying to a message is done through adding the 
	message id to the REFRENCES header of the message 
	We will be calling our post message dialog with the subjuct from the 
	current message and we will add the body of the message as a reply too

***********************************************************************/
void CNNTPclientDlg::OnReply() 
{
	CUT_Msg ReplyMsg;
	CString msgBody;
	CPostDlg postDlg;
	
	char buf[MAX_PATH];
	int rt = UTE_SUCCESS;
	m_currentSelectedMsg.GetHeaderByType (UTM_MESSAGE_ID,buf,MAX_PATH-1);
	// we add the refrence header first
	ReplyMsg.AddHeaderField (buf,UTM_REFERENCES);
	// now lets read the headers we are intersted in to make sure we are posting to the correct news group(s)
	// that the message was posted to	
	// news group
	m_currentSelectedMsg.GetHeaderByType(UTM_NEWSGROUPS,buf,MAX_PATH-1);
	postDlg.m_strTargetNewsGroups = (LPCSTR) buf;
	// From
	m_currentSelectedMsg.GetHeaderByType(UTM_FROM,buf,MAX_PATH-1);
	postDlg.m_strArtBody = (LPCSTR)buf ;
	postDlg.m_strArtBody += _T(" Wrote: ---->>>> ");
	postDlg.m_strArtBody += _T("\r\n");
	postDlg.m_strArtBody+=  (LPCSTR)m_currentSelectedMsg.GetMessageBody ();
	// News reader
	
	ReplyMsg.AddHeaderField (_T("Ghazi /Ultimate TCP/IP news reader demo"),UTM_XNEWS_READER);

	m_currentSelectedMsg.GetHeaderByType(UTM_SUBJECT,buf,MAX_PATH-1);
	postDlg.m_strSubject = "RE: ";
	postDlg.m_strSubject += (LPCSTR)buf;	
	if (postDlg.DoModal () == IDOK)
	{
		// lets make sure we are connected 
		if (!m_nntpClient.IsConnected ())
		{
			if (( rt = m_nntpClient.NConnect (m_strServerName)) != UTE_SUCCESS)
			{
				MessageBox(CUT_ERR::GetErrorString (rt),_T("Connection Failed"));
				return ;
			}
		}
	
	ReplyMsg.AddHeaderField (postDlg.m_strTargetNewsGroups,UTM_NEWSGROUPS);
	ReplyMsg.AddHeaderField (postDlg.m_strFrom ,UTM_FROM);
	ReplyMsg.AddHeaderField (postDlg.m_strSubject,UTM_SUBJECT);
	ReplyMsg.SetMessageBody (postDlg.m_strArtBody);
	
	rt = m_nntpClient.NPostArticle (ReplyMsg);
	MessageBox(CUT_ERR::GetErrorString (rt));
	}
}

void CNNTPclientDlg::AddGroup(LPCSTR groupName) {
	// add group to the group list, converting to widechar
	m_listGroup.AddString(WC(groupName));
	m_staticWindow.SetWindowText(WC(groupName));

}
