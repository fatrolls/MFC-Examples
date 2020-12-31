// IOCPClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOCPClient.h"
#include "IOCPClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIOCPClientDlg dialog

CIOCPClientDlg::CIOCPClientDlg(CWnd* pParent /*=NULL*/)
: CDialog(CIOCPClientDlg::IDD, pParent)
, m_sDownloadFilePath(_T(""))
, m_iPort(0)
{
	//{{AFX_DATA_INIT(CIOCPClientDlg)
	m_Adress = 	"127.0.0.1";
	m_sReceivedTxt = _T("");
	m_sSendTxt = _T("ABCDEFGHIKLMNOPQRST1234567890");
	m_bFlood = FALSE;
	m_MsgPerSec = 0;
	m_iPort=999;
	m_bAutoReconnect = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIOCPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIOCPClientDlg)
	DDX_Control(pDX, IDC_LOGG, m_CtrlLogg);
	DDX_Control(pDX, IDC_CLIENTLIST, m_CtrlClientList);
	DDX_Text(pDX, IDC_ADRESS, m_Adress);
	DDX_Text(pDX, IDC_RECEIVEDTXT, m_sReceivedTxt);
	DDV_MaxChars(pDX, m_sReceivedTxt, 1020);
	DDX_Text(pDX, IDC_SENDTXT, m_sSendTxt);
	DDV_MaxChars(pDX, m_sSendTxt, 1020);
	DDX_Check(pDX, IDC_FLOOD, m_bFlood);
	DDX_Text(pDX, IDC_MSGPERSEC, m_MsgPerSec);
	DDX_Text(pDX, IDC_DOWNLOADPATH, m_sDownloadFilePath);
	DDX_Text(pDX, IDC_PORT, m_iPort);
	DDX_Check(pDX, IDC_AUTORECONNECT, m_bAutoReconnect);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIOCPClientDlg, CDialog)
//{{AFX_MSG_MAP(CIOCPClientDlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_CONNECT, OnConnect)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_DISCONNECTALL, OnDisconnectall)
ON_BN_CLICKED(IDC_SEND, OnSend)
ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
ON_NOTIFY(NM_CLICK, IDC_CLIENTLIST, OnClickClientlist)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_FLOOD, OnFlood)
ON_BN_CLICKED(IDC_STOPSTART, OnStopstart)
ON_BN_CLICKED(IDC_Settings, OnSettings)
ON_MESSAGE(WM_LOGG_APPEND, OnAppendLog)
ON_MESSAGE(WM_NEW_CONNECTION, OnNewClient)
ON_MESSAGE(WM_CLIENTDISCONNECTED, OnClientDisconnected)
ON_BN_CLICKED(IDC_AUTORECONNECT, OnAutoreconnect)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIOCPClientDlg message handlers

BOOL CIOCPClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_CtrlClientList.init();
	
	
	/*
	ITEMINFO* pItem=new ITEMINFO;
	pItem->m_ClientAddress="Test test";
	pItem->m_ID="ID1";
	
	  ITEMINFO* pItem2=new ITEMINFO;
	  pItem2->m_ClientAddress="Test test2";
	  pItem2->m_ID="ID1";
	  
		m_CtrlClientList.AddItemToList(0,0,pItem);
		m_CtrlClientList.AddItemToList(1,0,pItem2);
	*/
	
	
	
	
	StartTheSystem();
	
	// Start The timer.. 
	m_ihTimer=SetTimer(0,500,NULL);
	
	EnableClientPanel();
	
	
	
	CString sFilePath="";		
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	CString strTemp;
	CString strApplName;
	GetModuleFileName(NULL,strTemp.GetBuffer(MAX_PATH),MAX_PATH);
	strTemp.ReleaseBuffer();
	_splitpath( strTemp, drive, dir, fname, ext );
	sFilePath=drive; //Drive
	sFilePath+=dir; //dir
	
	m_sDownloadFilePath=sFilePath;
	UpdateData(FALSE);
	//DisableClientPanel();
	
	// TODO: Add extra initialization here
	OnConnect();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIOCPClientDlg::OnPaint() 
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
HCURSOR CIOCPClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CIOCPClientDlg::OnOK() 
{
	
	CDialog::OnOK();
}

void CIOCPClientDlg::OnConnect() 
{
	UpdateData();
	if(!m_iocp.Connect(m_Adress,m_iPort))
		AfxMessageBox("Connection Failed");
	else
	{
		UpdateList();
		UpdateClientData();
		m_CtrlClientList.SetFocus();
	}
	
	
}

/*
* Updates, the client specefik data.   
*
*
*/


void CIOCPClientDlg::UpdateClientData()
{
	
	   ClientContext* pContext=NULL;
	   // to be sure that pContext Suddenly does not dissapear.. 
	   m_iocp.m_ContextMapLock.Lock();
	   pContext=m_iocp.FindClient(m_iCurrentClientID);
	   if(pContext!=NULL)
	   {
		   pContext->m_ContextLock.Lock();
		   m_sReceivedTxt=pContext->m_sReceived;
		   pContext->m_ContextLock.Unlock();
	   }
	   m_iocp.m_ContextMapLock.Unlock();
	   UpdateData(FALSE);
	   
	   if(!m_iocp.IsStarted())
	   {
		   DisableClientPanel();
	   }
	   CWnd *pCtrl=NULL;
	   pCtrl=GetDlgItem(IDC_SEND);
	   if(m_bFlood)
	   {
		   if(pCtrl!=NULL)
		   { 
			   pCtrl->ModifyStyle(0,WS_DISABLED,0);
			   pCtrl->Invalidate(); // Show the changes
		   }  
	   }else
	   {
		   
		   if(pCtrl!=NULL&&m_iocp.IsStarted())
		   { 
			   pCtrl->ModifyStyle(WS_DISABLED,0,0);
			   pCtrl->Invalidate(); // Show the changes
		   }  
	   }
	   
	   
	   
}


void CIOCPClientDlg::UpdateList()
{
	BOOL bRepaint=FALSE;
	ClientContext *pContext=NULL;
	ITEMINFO* pItem=NULL;
	BOOL bStatusChanged=FALSE;
	m_GUIListLock.Lock();
	m_iocp.m_ContextMapLock.Lock();
	int nCount= m_CtrlClientList.GetItemCount();	
	for(int i=0; i<nCount;i++)
	{   
		pItem=(ITEMINFO*)m_CtrlClientList.GetItemData(i);
		if(pItem!=NULL)
		{
			
			pContext=NULL;
			pContext=m_iocp.m_ContextMap[pItem->m_ID];
			if(pContext==NULL)
			{
				m_CtrlClientList.FreeItem(i);
				nCount= m_CtrlClientList.GetItemCount();	
				bRepaint=TRUE;
			}else // Update data. 
			{
				pContext->m_ContextLock.Lock();
				
				bStatusChanged=FALSE;
				
				if(pContext->m_bUpdate)
				{
					bStatusChanged=TRUE;
					pItem->m_iNumberOfReceivedMsg=pContext->m_iNumberOfReceivedMsg;
#ifdef TRANSFERFILEFUNCTIONALITY	
					pItem->m_iMaxFileBytes=pContext->m_iMaxFileBytes;
					pItem->m_iFileBytes=pContext->m_iFileBytes;
					pItem->m_bFileReceivedMode=pContext->m_bFileReceivedMode;
					pItem->m_bFileSendMode=pContext->m_bFileSendMode;
#else
					pItem->m_iMaxFileBytes=-1;
					pItem->m_iFileBytes=-1;
					pItem->m_bFileReceivedMode=FALSE;
					pItem->m_bFileSendMode=FALSE;
#endif
				}
				if(bStatusChanged)
					m_CtrlClientList.Update(i);
				pContext->m_ContextLock.Unlock();
			}	
		}
		
	}
	m_iocp.m_ContextMapLock.Unlock();
	m_GUIListLock.Unlock();
	
	if(bRepaint)
	{
		//m_CtrlClientList.Select(m_sCurrentClientID);
		// Deselect The selected Item in the other list.
		int SItem=m_CtrlClientList.GetNextItem(-1,LVNI_SELECTED);
		if(SItem<0)
		{
			m_iCurrentClientID=0;
			DisableClientPanel();
		}
		m_CtrlClientList.SetFocus();
		
		m_CtrlClientList.ReSort();
	}
	
}

void CIOCPClientDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(m_ihTimer);
	m_CtrlClientList.FreeListItems();	
}

void CIOCPClientDlg::OnDisconnectall() 
{
	m_iocp.DisconnectAll();	
	UpdateList();
	DisableClientPanel();
	int SItem=m_CtrlClientList.GetNextItem(-1,LVNI_SELECTED);
	if(SItem!=-1)
		m_CtrlClientList.SetItemState(SItem,LVNI_ALL, LVIF_TEXT | LVIF_IMAGE | LVIF_STATE);
	m_CtrlClientList.SetFocus();
}

void CIOCPClientDlg::OnSend() 
{
	
	CString test;
	test.LoadString(IDS_TEST);
	
	if(m_iCurrentClientID>0)
	{
		
		UpdateData(TRUE);
		
		//for(int i=0;i<50;i++)
		//m_iocp.ASend(m_sCurrentClientID,m_sSendTxt);
		
		if(!m_iocp.BuildPackageAndSend(m_iCurrentClientID,m_sSendTxt))
		{
			DisableClientPanel();
			int SItem=m_CtrlClientList.GetNextItem(-1,LVNI_SELECTED);
			if(SItem!=-1)
				m_CtrlClientList.SetItemState(SItem,LVNI_ALL, LVIF_TEXT | LVIF_IMAGE | LVIF_STATE);
			m_CtrlClientList.SetFocus();
			AfxMessageBox("Send not successfull.!");
		}else
		{
			UpdateClientData();
			m_CtrlClientList.SetFocus();
		}
	}
	
}

void CIOCPClientDlg::OnDisconnect() 
{
	
	
	if(m_iCurrentClientID>0)
	{
		
		UpdateData(TRUE);
		m_iocp.DisconnectClient(m_iCurrentClientID);
		UpdateList();
		m_iCurrentClientID=0;
		DisableClientPanel();
		// Deselect The selected Item in the other list.
		int SItem=m_CtrlClientList.GetNextItem(-1,LVNI_SELECTED);
		if(SItem!=-1)
			m_CtrlClientList.SetItemState(SItem,LVNI_ALL, LVIF_TEXT | LVIF_IMAGE | LVIF_STATE);
		m_CtrlClientList.SetFocus();
	}
	
	
	
}


void CIOCPClientDlg::OnClickClientlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	ITEMINFO* pItem=NULL;
	pItem=m_CtrlClientList.GetSelectedItem();
	if(pItem!=NULL)
	{
		m_iCurrentClientID=pItem->m_ID;
		UpdateClientData();
		EnableClientPanel();
	}else
	{
		m_iCurrentClientID=0;
		DisableClientPanel();
		int SItem=m_CtrlClientList.GetNextItem(-1,LVNI_SELECTED);
		if(SItem!=-1)
			m_CtrlClientList.SetItemState(SItem,LVNI_ALL, LVIF_TEXT | LVIF_IMAGE | LVIF_STATE);
	}
	
	*pResult = 0;
}

void CIOCPClientDlg::OnTimer(UINT nIDEvent) 
{
	UpdateData();
	UpdateClientData();
	UpdateList();
	m_iocp.m_StatusLock.Lock();
	m_MsgPerSec=m_iocp.m_iNumberOfMsg*2;
	m_iocp.m_iNumberOfMsg=0;
	m_iocp.m_StatusLock.Unlock();
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}


LRESULT CIOCPClientDlg::OnNewClient(WPARAM wParam, LPARAM lParam)
{
	unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
	//nessesary ? 
	m_GUIListLock.Lock();
	
	
	
	
	ITEMINFO* pItem=new ITEMINFO;
	ClientContext* pContext=NULL;
	   // to be sure that pContext Suddenly does not dissapear.. 
	   m_iocp.m_ContextMapLock.Lock();
	   pContext=m_iocp.FindClient(*piID);
	   if(pContext!=NULL)
	   {
		   pContext->m_ContextLock.Lock();
		   pItem->m_ClientAddress=m_iocp.GetHostAddress(pContext->m_Socket);
		   pItem->m_ID=pContext->m_Socket;
		   pItem->m_iNumberOfReceivedMsg=0;
#ifdef TRANSFERFILEFUNCTIONALITY	
		   pItem->m_iMaxFileBytes=pContext->m_iMaxFileBytes;
		   pItem->m_iFileBytes=pContext->m_iFileBytes;
		   pItem->m_bFileReceivedMode=pContext->m_bFileReceivedMode;
		   pItem->m_bFileSendMode=pContext->m_bFileSendMode;
#else
		   pItem->m_iMaxFileBytes=-1;
		   pItem->m_iFileBytes=-1;
		   pItem->m_bFileReceivedMode=FALSE;
		   pItem->m_bFileSendMode=FALSE;
#endif
		   pContext->m_ContextLock.Unlock();
	   }
	   m_iocp.m_ContextMapLock.Unlock();	
	   
	   
	   
	   // Add the new client to the list. 
	   
	   
	   m_CtrlClientList.AddItemToList(pItem);
	   UpdateData(TRUE);
	   
	   
	   
	   if(m_bFlood)
	   {
		   
		   if(!m_iocp.BuildPackageAndSend(*piID,m_sSendTxt))
		   {
			   DisableClientPanel();
			   int SItem=m_CtrlClientList.GetNextItem(-1,LVNI_SELECTED);
			   if(SItem!=-1)
				   m_CtrlClientList.SetItemState(SItem,LVNI_ALL, LVIF_TEXT | LVIF_IMAGE | LVIF_STATE);
			   m_CtrlClientList.SetFocus();
			   // AfxMessageBox("Send not successfull.!");
		   }
		   UpdateClientData();
	   }
	   m_CtrlClientList.SetFocus();
	   m_CtrlClientList.ReSort();
	   m_GUIListLock.Unlock();
	   UpdateData(FALSE);
	   delete piID;
	   
	   
	   return 0;
}

LRESULT CIOCPClientDlg::OnClientDisconnected(WPARAM wParam, LPARAM lParam)
{
	unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
	BOOL bRepaint=FALSE;
	ClientContext *pContext=NULL;
	ITEMINFO* pItem=NULL;
	
	m_GUIListLock.Lock();	
	int nCount= m_CtrlClientList.GetItemCount();	
	for(int i=0; i<nCount;i++)
	{   
		pItem=(ITEMINFO*)m_CtrlClientList.GetItemData(i);
		if(pItem!=NULL)
		{
			// Disconnected 
			if(pItem->m_ID==*piID)
			{
				m_CtrlClientList.FreeItem(i);
				nCount= m_CtrlClientList.GetItemCount();	
				bRepaint=TRUE;
			}
		}	
	}
	m_GUIListLock.Unlock();
	if(bRepaint)
	{
		//m_CtrlClientList.Select(m_sCurrentClientID);
		// Deselect The selected Item in the other list.
		int SItem=m_CtrlClientList.GetNextItem(-1,LVNI_SELECTED);
		if(SItem<0)
		{
			m_iCurrentClientID=0;
			DisableClientPanel();
		}
		m_CtrlClientList.SetFocus();
		
		m_CtrlClientList.ReSort();
	}
	UpdateData(FALSE);
	if(piID!=NULL)
		delete piID;
	   
	   
	   return 0;
}

LRESULT CIOCPClientDlg::OnAppendLog(WPARAM wParam, LPARAM lParam)
{
	char* msg = reinterpret_cast<char*>(lParam);
	if(msg!=NULL)
	{
		
		m_CtrlLogg.AppendString(msg);
	}
	delete[] msg;
	return 0;
}


void CIOCPClientDlg::DisableClientPanel()
{
	CWnd *pCtrl=NULL;
	CEdit *peCtrl=NULL;
	
	peCtrl=(CEdit*)GetDlgItem(IDC_SENDTXT);
	
	
	if(peCtrl!=NULL)
	{ 
		peCtrl->SetReadOnly();
		peCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_SEND);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(0,WS_DISABLED,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	
	pCtrl=GetDlgItem(IDC_DISCONNECT);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(0,WS_DISABLED,0);
		pCtrl->Invalidate(); // Show the changes
	}
				
	pCtrl=GetDlgItem(IDC_SENDTXT);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(0,WS_DISABLED,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
}

void CIOCPClientDlg::EnableClientPanel()
{
	
	CWnd *pCtrl=NULL;
	CEdit *peCtrl=NULL;
	
	peCtrl=(CEdit*)GetDlgItem(IDC_SENDTXT);
	
	
	if(peCtrl!=NULL)
	{ 
		peCtrl->SetReadOnly(FALSE);
		peCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_SEND);
	
	if(pCtrl!=NULL&&!m_bFlood)
	{ 
		pCtrl->ModifyStyle(WS_DISABLED,0,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_DISCONNECT);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(WS_DISABLED,0,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	
	pCtrl=GetDlgItem(IDC_SENDTXT);	
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(WS_DISABLED,0,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
}


void CIOCPClientDlg::EnableAllPanels()
{
	CWnd *pCtrl=NULL;
	CEdit *peCtrl=NULL;
	
	peCtrl=(CEdit*)GetDlgItem(IDC_SENDTXT);
	
	
	if(peCtrl!=NULL)
	{ 
		peCtrl->SetReadOnly(FALSE);
		peCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_SEND);
	
	if(pCtrl!=NULL&&!m_bFlood)
	{ 
		pCtrl->ModifyStyle(WS_DISABLED,0,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_DISCONNECT);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(WS_DISABLED,0,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_DISCONNECTALL);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(WS_DISABLED,0,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_CONNECT);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(WS_DISABLED,0,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_SEND);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(WS_DISABLED,0,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_SENDTXT);	
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(WS_DISABLED,0,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
}

void CIOCPClientDlg::DisableAllPanels()
{
	CWnd *pCtrl=NULL;
	CEdit *peCtrl=NULL;
	
	peCtrl=(CEdit*)GetDlgItem(IDC_SENDTXT);
	
	
	if(peCtrl!=NULL)
	{ 
		peCtrl->SetReadOnly();
		peCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_SEND);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(0,WS_DISABLED,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	
	pCtrl=GetDlgItem(IDC_DISCONNECT);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(0,WS_DISABLED,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	pCtrl=GetDlgItem(IDC_DISCONNECTALL);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(0,WS_DISABLED,0);
		pCtrl->Invalidate(); // Show the changes
	}
	pCtrl=GetDlgItem(IDC_CONNECT);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(0,WS_DISABLED,0);
		pCtrl->Invalidate(); // Show the changes
	}
	
	
				
	pCtrl=GetDlgItem(IDC_SENDTXT);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(0,WS_DISABLED,0);
		pCtrl->Invalidate(); // Show the changes
	}
}



void CIOCPClientDlg::OnFlood() 
{
	UpdateData(TRUE);
	// Set the flood mode of the server. 
	m_iocp.m_StatusLock.Lock();
	m_iocp.m_sSendText=m_sSendTxt;
	m_iocp.m_bFlood=m_bFlood;
	m_iocp.m_StatusLock.Unlock();
	
	if(m_bFlood)
	{
		m_iocp.BuildPackageAndSendToAll(m_sSendTxt);
		UpdateClientData();
		m_CtrlClientList.SetFocus();
	}
	
}

void CIOCPClientDlg::OnAutoreconnect() 
{
	UpdateData(TRUE);
	// Set the flood mode of the server. 
	m_iocp.m_StatusLock.Lock();
	m_iocp.m_bAutoReconnect=m_bAutoReconnect;
	m_iocp.m_sAutoReconnect=m_Adress;
	m_iocp.m_iAutoReconnect=m_iPort;
	m_iocp.m_StatusLock.Unlock();
	
}


void CIOCPClientDlg::OnStopstart() 
{
	
	CButton *pBCtrl=NULL;
	
	CButton *pBCtrl2=NULL;
	
	pBCtrl=(CButton*)GetDlgItem(IDC_STOPSTART);
	pBCtrl2=(CButton*)GetDlgItem(IDC_Settings);
	if(pBCtrl!=NULL&&pBCtrl2!=NULL)
	{
		if(m_iocp.IsStarted())
		{
			m_iocp.ShutDown();
			pBCtrl->SetWindowText("Start");
			pBCtrl2->EnableWindow(TRUE);
			DisableAllPanels();	
			
		}else
		{
			StartTheSystem();
			pBCtrl->SetWindowText("Stop");
			pBCtrl2->EnableWindow(FALSE);	
			EnableAllPanels();
			
			
		}
		
		
	}
	
}

void CIOCPClientDlg::StartTheSystem()
{
	m_iocp.m_StatusLock.Lock();
	m_iocp.m_hWnd=m_hWnd;
	m_iocp.m_sSendText=m_sSendTxt;
	m_iocp.m_bFlood=m_bFlood;
	m_iocp.m_StatusLock.Unlock();
	
	if(!m_iocp.Start(m_ConfigDlg.m_iPortNr,
		m_ConfigDlg.m_iMaxNumberOfConnections,
		m_ConfigDlg.m_iNrOfIOWorkers,
		m_ConfigDlg.m_iNrOfLogicalWorkers,
		m_ConfigDlg.m_iMaxNrOfFreeBuff,
		m_ConfigDlg.m_iMaxNrOfFreeContext,
		m_ConfigDlg.m_iSendInOrder,
		m_ConfigDlg.m_bReadInOrder,
		m_ConfigDlg.m_iNrPendlingReads))
		AfxMessageBox("Error could not start the Client");
}

void CIOCPClientDlg::OnSettings() 
{
	m_ConfigDlg.DoModal();
}


