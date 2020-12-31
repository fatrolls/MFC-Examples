// SecureChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SecureChat.h"
#include "SecureChatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecureChatDlg dialog

CSecureChatDlg::CSecureChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSecureChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSecureChatDlg)
	m_iKeyLength = 32;
	m_sAdress = _T("");
	m_sAddress = _T("");
	m_iPort = 999;
	m_iNrOfIOWorkers = 2;
	m_iMaximumNrOfConnections = 1201;
	m_sMessage = _T("Welcome to the secure chat server.");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iCurrenClientID=-1;
}

void CSecureChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSecureChatDlg)
	DDX_Control(pDX, IDC_DISCONNECT, m_cBtnDisconnect);
	DDX_Control(pDX, IDC_STARTSTOPSERVER, m_cStartStopBtn);
	DDX_Control(pDX, IDC_PORTNR, m_cPortNr);
	DDX_Control(pDX, IDC_NROFIO, m_cNrOfIOWorkers);
	DDX_Control(pDX, IDC_MAXCONNECT, m_cMaxNrOConnection);
	DDX_Control(pDX, IDC_USERLIST, m_cUserList);
	DDX_Control(pDX, IDC_TOPTAP, m_cTab);
	DDX_Control(pDX, IDC_TXTOUT, m_cLogg);
	DDX_Text(pDX, IDC_KEYSIZE, m_iKeyLength);
	DDX_Text(pDX, IDC_ADDRESS, m_sAddress);
	DDX_Text(pDX, IDC_PORTNR, m_iPort);
	DDX_Text(pDX, IDC_NROFIO, m_iNrOfIOWorkers);
	DDX_Text(pDX, IDC_MAXCONNECT, m_iMaximumNrOfConnections);
	DDX_Text(pDX, IDC_TEXT, m_sMessage);
	DDV_MaxChars(pDX, m_sMessage, 400);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSecureChatDlg, CDialog)
	//{{AFX_MSG_MAP(CSecureChatDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SIMPLELIBTEST, OnSimplelibtest)
	ON_BN_CLICKED(IDC_RSATEST, OnRsatest)
	ON_BN_CLICKED(IDC_GENERATEKEY, OnGeneratekey)
	ON_BN_CLICKED(IDC_DHTEST, OnDhtest)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TOPTAP, OnSelchangeToptap)
	ON_BN_CLICKED(IDC_STARTSTOPSERVER, OnStartstopserver)
	ON_NOTIFY(NM_CLICK, IDC_USERLIST, OnClickUserlist)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_DISCONNECTALL, OnDisconnectall)
	ON_BN_CLICKED(IDC_SENDTXT, OnSendtxt)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_LOGG_APPEND, OnAppendLog)
	ON_MESSAGE(WM_NEW_CONNECTION, OnNewClient)
	ON_MESSAGE(WM_DISCONNECT_CLIENT, OnClientDisconnected)
	ON_BN_CLICKED(IDC_CLEARLOG, OnClearlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecureChatDlg message handlers


LRESULT CSecureChatDlg::OnNewClient(WPARAM wParam, LPARAM lParam)
{
	unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
	
	ITEMINFO* pItem=new ITEMINFO;
	ClientContext* pContext=NULL;
	
	// to be sure that pContext Suddenly does not dissapear.. 
	m_iocp.m_ContextMapLock.Lock();
	pContext=m_iocp.FindClient(*piID);
	if ( pContext!=NULL )
	{
		pContext->m_ContextLock.Lock();
		pItem->m_sClientAddress=m_iocp.GetHostAddress(pContext->m_Socket);
		pItem->m_ID=pContext->m_Socket;
		pItem->m_sName="??????";
		pContext->m_ContextLock.Unlock();
	}
	m_iocp.m_ContextMapLock.Unlock();	
	
	if (! m_cUserList.AddItemToList(pItem) )
	{
		AfxMessageBox("FATAL ERROR - AddItemToList failed.");
	}
	
	if(piID!=NULL)
		delete piID; 
	   return 0;
}


LRESULT CSecureChatDlg::OnClientDisconnected(WPARAM wParam, LPARAM lParam)
{
	unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
	BOOL bRepaint=FALSE;
	ClientContext *pContext=NULL;
	ITEMINFO* pItem=NULL;
	
	//	m_GUIListLock.Lock();	
	int nCount= m_cUserList.GetItemCount();	
	for(int i=0; i<nCount;i++)
	{   
		pItem=(ITEMINFO*)m_cUserList.GetItemData(i);
		if(pItem!=NULL)
		{
			// Disconnected 
			if(pItem->m_ID==*piID)
			{
				m_cUserList.FreeItem(i);
				nCount= m_cUserList.GetItemCount();	
				bRepaint=TRUE;
			}
		}	
	}


	if(bRepaint)
	{
		
		// Deselect The selected Item in the other list.
		int SItem=m_cUserList.GetNextItem(-1,LVNI_SELECTED);
		if( SItem<0 )
		{
			m_iCurrenClientID=-1;
			m_cBtnDisconnect.EnableWindow(FALSE);
		}
		m_cUserList.SetFocus();
		
		m_cUserList.ReSort();
	}
	UpdateData(FALSE);
	
	   
	if(piID!=NULL)
		delete piID; 
	   return 0;
}

LRESULT CSecureChatDlg::OnAppendLog(WPARAM wParam, LPARAM lParam)
{
	char* msg = reinterpret_cast<char*>(lParam);
	if(msg!=NULL)
	{
		
		m_cLogg.AppendString(msg);
	}
	delete[] msg;
	return 0;
}


BOOL CSecureChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//
	// Add Tab data. 
	//
	
	// Set the titles for each tab
	TCITEM tabItem;
	tabItem.mask = TCIF_TEXT;
	tabItem.pszText = _T("Secure chat server");

	m_cTab.InsertItem(0, &tabItem);
	
	tabItem.pszText = _T("Crypto Demo/Key Generation");
	m_cTab.InsertItem(1, &tabItem);
	
	m_cTab.SetCurSel(0);
	

	//
	// Init the list 
	//
	m_cUserList.init();
	
	SetDemoMode(FALSE);
	m_sAddress=m_iocp.GetHostIP();
	UpdateData(FALSE);
	
		
	OnStartstopserver();


	m_ihTimer=SetTimer(0,500,NULL);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CSecureChatDlg::StartTheServer()
{
	m_iocp.m_StatusLock.Lock();
	m_iocp.m_hWnd=m_hWnd;
	m_iocp.m_StatusLock.Unlock();
	if( !m_iocp.Start(m_iPort,m_iMaximumNrOfConnections, m_iNrOfIOWorkers) )
		AfxMessageBox("Error could not start the Server");
	else
	{
		m_cMaxNrOConnection.SetReadOnly(TRUE);
		m_cNrOfIOWorkers.SetReadOnly(TRUE);
		m_cPortNr.SetReadOnly(TRUE);
	}
}

void CSecureChatDlg::StopTheServer()
{
	m_iocp.ShutDown();
	m_cMaxNrOConnection.SetReadOnly(FALSE);
	m_cNrOfIOWorkers.SetReadOnly(FALSE);
	m_cPortNr.SetReadOnly(FALSE);
	
}

void CSecureChatDlg::SetDemoMode(BOOL bDemoMode)
{
	
	ShowCtrl(IDC_KEYSIZE,bDemoMode);
	ShowCtrl(IDC_KEYSIZETXT,bDemoMode);
	ShowCtrl(IDC_SIMPLELIBTEST,bDemoMode);
	ShowCtrl(IDC_RSATEST,bDemoMode);
	ShowCtrl(IDC_DHTEST,bDemoMode);
	ShowCtrl(IDC_CLEARLOG,bDemoMode);
	ShowCtrl(IDC_GENERATEKEY,bDemoMode);
	ShowCtrl(IDC_USERLIST,!bDemoMode);
	ShowCtrl(IDC_STARTSTOPSERVER,!bDemoMode);
	ShowCtrl(IDC_ADDRESS,!bDemoMode);
	ShowCtrl(IDC_PORTNR,!bDemoMode);
	ShowCtrl(IDC_NROFIO,!bDemoMode);
	ShowCtrl(IDC_MAXCONNECT,!bDemoMode);
	ShowCtrl(IDC_DISCONNECTALL,!bDemoMode);
	ShowCtrl(IDC_DISCONNECT,!bDemoMode);
	ShowCtrl(IDC_PORTTXT,!bDemoMode);
	ShowCtrl(IDC_TXTNROFIOWORKER,!bDemoMode);
	ShowCtrl(IDC_TXTMAXCONNECT,!bDemoMode);
	ShowCtrl(IDC_TEXT,!bDemoMode);	
	ShowCtrl(IDC_SENDTXT,!bDemoMode);
	ShowCtrl(IDC_SERVERADRESSTXT,!bDemoMode);
	
	if( bDemoMode )
	{
		// Move the logg into place.. 
		RelocateTo(&m_cLogg,IDC_BIGLOGG);
		RelocateTo(&m_cUserList,IDC_SMALLLOGG);
		m_cLogg.AppendString("Press any Button to run the demo..");

	}else
	{
		// Move it to bottom 
		RelocateTo(&m_cLogg,IDC_SMALLLOGG);
		RelocateTo(&m_cUserList,IDC_LISTPLACEHOLDER);
	}
}

/*
 * Moves/rezise an Ctrl/window to placeholder with ID n	
 * Return TRUE if sucessfull. 
 */
BOOL CSecureChatDlg::RelocateTo(CWnd *pCtrl, int nDestID)
{
	if ( !pCtrl )
		return FALSE;
	
	CRect rc;
	CWnd* pCtrlDest=NULL;
	pCtrlDest=GetDlgItem(nDestID);
	
	if ( pCtrlDest!=NULL )
	{
		pCtrlDest->GetWindowRect(rc);
	}
	else
	{
	 
		return FALSE;
	
	}
	ScreenToClient(&rc);
    // Move. 
	pCtrl->MoveWindow(rc);
	return TRUE;

}

/*
 *	Helper Function Shows/hide an Ctrl. 
 */
inline void CSecureChatDlg::ShowCtrl(int nCtrlID,BOOL bShow)
{
	CWnd *pCtrl=NULL;
	pCtrl=GetDlgItem(nCtrlID);
	if(pCtrl!=NULL)
		pCtrl->ShowWindow(bShow ? SW_SHOW :SW_HIDE);

}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSecureChatDlg::OnPaint() 
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
HCURSOR CSecureChatDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSecureChatDlg::OnOK() 
{
	// TODO: Add extra validation here

}

void CSecureChatDlg::OnSimplelibtest() 
{

	AfxBeginThread(CSecureChatDlg::ThreadWrapperLibTestDemo, (void*)this,
		THREAD_PRIORITY_NORMAL);
}

void CSecureChatDlg::OnRsatest() 
{
	UpdateData();
	m_iKeyByteSize=m_iKeyLength;
 AfxBeginThread(CSecureChatDlg::ThreadWrapperRSAdemo, (void*)this,
		THREAD_PRIORITY_NORMAL);

}

void CSecureChatDlg::OnDhtest() 
{
	UpdateData();
	m_iKeyByteSize=m_iKeyLength;
	AfxBeginThread(CSecureChatDlg::ThreadWrapperDHdemo, (void*)this,
		THREAD_PRIORITY_NORMAL);	
	
}

void CSecureChatDlg::OnGeneratekey() 
{
	UpdateData();
	m_iKeyByteSize=m_iKeyLength;
	if ( m_RandomDlg.DoModal()==IDOK )
	{
	  AfxBeginThread(CSecureChatDlg::ThreadWrapperDSAdemo, (void*)this,
		THREAD_PRIORITY_NORMAL);
	}
}


UINT CSecureChatDlg::ThreadWrapperRSAdemo(LPVOID pParam)
{
	CSecureChatDlg* pThis=NULL;
	pThis = reinterpret_cast<CSecureChatDlg*>(pParam);
	if(pThis)
	{
		pThis->PerformRSATest();
	
	}
	return 0;
}


UINT CSecureChatDlg::ThreadWrapperDHdemo(LPVOID pParam)
{
	CSecureChatDlg* pThis=NULL;
	pThis = reinterpret_cast<CSecureChatDlg*>(pParam);
	if(pThis)
	{
		pThis->PerformDHTest();
		
	}
	return 0;
}

UINT CSecureChatDlg::ThreadWrapperDSAdemo(LPVOID pParam)
{
	CSecureChatDlg* pThis=NULL;
	pThis = reinterpret_cast<CSecureChatDlg*>(pParam);
	if(pThis)
	{
		pThis->PerformDSATest();
		
	}
	return 0;
}

UINT CSecureChatDlg::ThreadWrapperLibTestDemo(LPVOID pParam)
{
	CSecureChatDlg* pThis=NULL;
	pThis = reinterpret_cast<CSecureChatDlg*>(pParam);
	if(pThis)
	{
		pThis->PerformSimpleLibTest();
		
	}
	return 0;
}


void CSecureChatDlg::PerformRSATest()
{
	m_cProcessLock.Lock();
	m_cLogg.Clear();
	MyCryptLib c;
	c.DemoRSA(&m_cLogg,m_iKeyByteSize);
	m_cProcessLock.Unlock();
	
}

void CSecureChatDlg::PerformSimpleLibTest()
{
	m_cProcessLock.Lock();
	m_cLogg.Clear();
	MyCryptLib c;
	c.DemoSimpleTest(&m_cLogg);
	m_cProcessLock.Unlock();
	
}

void CSecureChatDlg::PerformDSATest()
{
	m_cProcessLock.Lock();
	m_cLogg.Clear();
	MyCryptLib c;
	c.DemoDSA(&m_cLogg,	m_iKeyByteSize,m_RandomDlg.m_raw_pool,_POOL_SIZE_);
	m_cProcessLock.Unlock();
}


void CSecureChatDlg::PerformDHTest()
{
	m_cProcessLock.Lock();
	m_cLogg.Clear();
	MyCryptLib c;
	c.DemoDiffieHellman(&m_cLogg,m_iKeyByteSize);
	m_cProcessLock.Unlock();	
}

void CSecureChatDlg::OnSelchangeToptap(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SetDemoMode(m_cTab.GetCurFocus()==1);	
	*pResult = 0;
}

void CSecureChatDlg::OnStartstopserver() 
{
	UpdateData(TRUE);
	if(m_iocp.IsStarted())
	{
		m_cStartStopBtn.SetWindowText("Start");
		StopTheServer();
		m_cUserList.EnableWindow(FALSE);
	}else
	{
		m_cStartStopBtn.SetWindowText("Stop");
		StartTheServer();
		m_cUserList.EnableWindow();
	}	
}

void CSecureChatDlg::OnClickUserlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ITEMINFO* pItem=NULL;
	
	pItem=m_cUserList.GetSelectedItem();
	
	if ( pItem!=NULL) 
	{ 
		m_iCurrenClientID=pItem->m_ID;
		m_cBtnDisconnect.EnableWindow();

	
	}else
	{
		//m_iCurrentClientID=0;
		int SItem=m_cUserList.GetNextItem(-1,LVNI_SELECTED);
		if ( SItem!=-1 )
			m_cUserList.SetItemState(SItem,LVNI_ALL, LVIF_TEXT | LVIF_IMAGE | LVIF_STATE);
		
		m_cBtnDisconnect.EnableWindow(FALSE);
	}
	*pResult = 0;
}

void CSecureChatDlg::OnDisconnect() 
{
	
	if ( m_iCurrenClientID>0 )
	{
		
		UpdateData(TRUE);
		m_iocp.DisconnectClient(m_iCurrenClientID);
		
		// Deselect The selected Item in the other list.
		int SItem=m_cUserList.GetNextItem(-1,LVNI_SELECTED);
		if ( SItem!=-1 )
		{
			m_cUserList.SetItemState(SItem,LVNI_ALL, LVIF_TEXT | LVIF_IMAGE | LVIF_STATE);
		}
		m_cUserList.SetFocus();
		m_cBtnDisconnect.EnableWindow(FALSE);
		
	}

	
}

void CSecureChatDlg::OnDisconnectall() 
{
	UpdateData(TRUE);
	m_iocp.DisconnectAll();	
	// Deselect The selected Item in the other list.
	int SItem=m_cUserList.GetNextItem(-1,LVNI_SELECTED);
	if ( SItem!=-1 )
		m_cUserList.SetItemState(SItem,LVNI_ALL, LVIF_TEXT | LVIF_IMAGE | LVIF_STATE);
	m_cUserList.SetFocus();
}

void CSecureChatDlg::OnSendtxt() 
{
	UpdateData(TRUE);
	m_iocp.SendTextMessage(m_sMessage);
}

void CSecureChatDlg::OnClearlog() 
{
	m_cLogg.Clear();
}


/*
 * Used to Update the content in the Userlist with an interval of 	
 * 500 ms. 
 *
 */

void CSecureChatDlg::UpdateList()
{

	ClientContext *pContext=NULL;
	ITEMINFO* pItem=NULL;
	BOOL bStatusChanged=FALSE;

	// m_cUserList.SetFocus();	
	// Select all of the items that are completely visible.
	int n = m_cUserList.GetTopIndex();
	int nLast = min((n + m_cUserList.GetCountPerPage()+1),m_cUserList.GetItemCount()) ; // To also get partial stuff.  
	for (;n < nLast;n++)
	{
		
		pItem=(ITEMINFO*)m_cUserList.GetItemData(n);
		if(pItem!=NULL)
		{
		  	m_iocp.m_ContextMapLock.Lock();
			pContext=NULL;
			pContext=m_iocp.m_ContextMap[pItem->m_ID];
			if ( pContext!=NULL && pContext->m_bUpdateList )
			{
				pContext->m_bUpdateList=FALSE;
				pItem->m_sName=pContext->m_sUsername;
				m_cUserList.Update(n);
				TRACE("%i (%i) \r\n",n,pItem->m_ID);
			}
			m_iocp.m_ContextMapLock.Unlock();
		} 	
	}	
}



void CSecureChatDlg::OnTimer(UINT nIDEvent) 
{
	UpdateList();
	CDialog::OnTimer(nIDEvent);
}

void CSecureChatDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(m_ihTimer);
	m_iocp.m_StatusLock.Lock();
	m_iocp.m_hWnd=NULL;
	m_iocp.m_StatusLock.Unlock();
}

