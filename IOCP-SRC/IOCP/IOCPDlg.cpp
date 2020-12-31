// IOCPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOCP.h"
#include "IOCPDlg.h"
#include ".\iocpdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIOCPDlg dialog

CIOCPDlg::CIOCPDlg(CWnd* pParent /*=NULL*/)
: CDialog(CIOCPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIOCPDlg)
	m_Adress = 	"";
	m_sReceivedTxt = _T("");
	m_sSendTxt = _T("ABCDEFGHIKLMNOPQRST1234567890");
	m_bFlood = TRUE;
	m_MsgPerSec = 0;
	m_bRandomConnect = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIOCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIOCPDlg)
	DDX_Control(pDX, IDC_LOGG, m_CtrlLogg);
	DDX_Control(pDX, IDC_CLIENTLIST, m_CtrlClientList);
	DDX_Text(pDX, IDC_ADRESS, m_Adress);
	DDX_Text(pDX, IDC_RECEIVEDTXT, m_sReceivedTxt);
	DDV_MaxChars(pDX, m_sReceivedTxt, 1020);
	DDX_Text(pDX, IDC_SENDTXT, m_sSendTxt);
	DDV_MaxChars(pDX, m_sSendTxt, 1020);
	DDX_Check(pDX, IDC_FLOOD, m_bFlood);
	DDX_Text(pDX, IDC_MSGPERSEC, m_MsgPerSec);
	DDX_Check(pDX, IDC_RANDOMDISCONNECT, m_bRandomConnect);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SENDFILE, m_CtrlSendBtn);
}

BEGIN_MESSAGE_MAP(CIOCPDlg, CDialog)
//{{AFX_MSG_MAP(CIOCPDlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
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
ON_BN_CLICKED(IDC_RANDOMDISCONNECT, OnRandomdisconnect)
//}}AFX_MSG_MAP
ON_BN_CLICKED(IDC_SENDFILE, OnBnClickedSendfile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIOCPDlg message handlers

BOOL CIOCPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_CtrlClientList.init();
	
	

	
	
	StartTheSystem();
	// Fungerar inte som du vill. 
	m_Adress=m_iocp.GetHostIP();
	// Start The timer.. 
	m_ihTimer=SetTimer(0,500,NULL);
	
	//EnableClientPanel();
	DisableClientPanel();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIOCPDlg::OnPaint() 
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
HCURSOR CIOCPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CIOCPDlg::OnOK() 
{
	
	CDialog::OnOK();
}



/*
* Updates, the client specefik data.   
*
*
*/


void CIOCPDlg::UpdateClientData()
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


void CIOCPDlg::UpdateList()
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
				if(m_bRandomConnect&&rand()%10==0)
					m_iocp.DisconnectClient(pContext->m_Socket);
				else
				{
					
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
					#endif

					}
					if(bStatusChanged)
						m_CtrlClientList.Update(i);
				}
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
void CIOCPDlg::OnDestroy() 
{
	KillTimer(m_ihTimer);
	m_CtrlClientList.FreeListItems();	
	CDialog::OnDestroy();
}

void CIOCPDlg::OnDisconnectall() 
{
	m_iocp.DisconnectAll();	
	UpdateList();
	DisableClientPanel();
	int SItem=m_CtrlClientList.GetNextItem(-1,LVNI_SELECTED);
	if(SItem!=-1)
		m_CtrlClientList.SetItemState(SItem,LVNI_ALL, LVIF_TEXT | LVIF_IMAGE | LVIF_STATE);
	m_CtrlClientList.SetFocus();
}

void CIOCPDlg::OnSend() 
{
	
	
	if(m_iCurrentClientID>0)
	{
		UpdateData(TRUE);	
		for(int i=0;i<20;i++)
		{
			m_sSendTxt.Format("%iCDEFGHIKLMNOPQRST1234567890",i);
			if(!m_iocp.BuildPackageAndSend(m_iCurrentClientID,m_sSendTxt))
				AfxMessageBox("Error send failed!");
		}
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

void CIOCPDlg::OnDisconnect() 
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


void CIOCPDlg::OnClickClientlist(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CIOCPDlg::OnTimer(UINT nIDEvent) 
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


LRESULT CIOCPDlg::OnNewClient(WPARAM wParam, LPARAM lParam)
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
		   pItem->m_bFileSendMode=FALSE;
			pItem->m_bFileReceivedMode=FALSE;
			pItem->m_iMaxFileBytes=-1;
#ifdef TRANSFERFILEFUNCTIONALITY	   
		   pItem->m_bFileSendMode=pContext->m_bFileSendMode;
		   pItem->m_bFileReceivedMode=pContext->m_bFileReceivedMode;
		   pItem->m_iMaxFileBytes=pContext->m_iMaxFileBytes;
#endif
		   pContext->m_ContextLock.Unlock();
	   }
	   m_iocp.m_ContextMapLock.Unlock();	
	   
	   
	   // Add the new client to the list. 
	   
	   
	  if(!m_CtrlClientList.AddItemToList(pItem))
		  AfxMessageBox("FATAL ERROR");
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
			   //AfxMessageBox("Send not successfull.!");
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
LRESULT CIOCPDlg::OnClientDisconnected(WPARAM wParam, LPARAM lParam)
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

LRESULT CIOCPDlg::OnAppendLog(WPARAM wParam, LPARAM lParam)
{
	char* msg = reinterpret_cast<char*>(lParam);
	if(msg!=NULL)
	{
		
		m_CtrlLogg.AppendString(msg);
	}
	delete[] msg;
	return 0;
}


void CIOCPDlg::DisableClientPanel()
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
	
	pCtrl=GetDlgItem(IDC_SENDFILE);
	
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

void CIOCPDlg::EnableClientPanel()
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
	
	pCtrl=GetDlgItem(IDC_SENDFILE);
	if(pCtrl!=NULL)
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


void CIOCPDlg::EnableAllPanels()
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
	pCtrl=GetDlgItem(IDC_SENDFILE);
	
	if(pCtrl!=NULL)
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

void CIOCPDlg::DisableAllPanels()
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
	
	pCtrl=GetDlgItem(IDC_SENDFILE);
	
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
	
	
				
	pCtrl=GetDlgItem(IDC_SENDTXT);
	
	if(pCtrl!=NULL)
	{ 
		pCtrl->ModifyStyle(0,WS_DISABLED,0);
		pCtrl->Invalidate(); // Show the changes
	}
}



void CIOCPDlg::OnFlood() 
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


void CIOCPDlg::OnRandomdisconnect() 
{
	srand((unsigned)time( NULL ) );
	
}



void CIOCPDlg::OnStopstart() 
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

void CIOCPDlg::StartTheSystem()
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
		//-1, // No buffer reuse
		m_ConfigDlg.m_iMaxNrOfFreeBuff,
		//-1, // No context reuse. 
		m_ConfigDlg.m_iMaxNrOfFreeContext,
		m_ConfigDlg.m_iSendInOrder,
		m_ConfigDlg.m_bReadInOrder,
		m_ConfigDlg.m_iNrOfPendlingReads))
		AfxMessageBox("Error could not start the Client");
}

void CIOCPDlg::OnSettings() 
{
	m_ConfigDlg.DoModal();
}


void CIOCPDlg::OnBnClickedSendfile()
{
#ifdef TRANSFERFILEFUNCTIONALITY
	CFileDialog dlg( TRUE,_T("*.*"),_T("*.*"),
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER,
		_T("All kind of files"));
	
	if( dlg.DoModal()==IDOK )
	{
		CString sPath="";
		CString sFilename="";
		
		sPath=dlg.GetPathName();
		sFilename=dlg.GetFileName();
		//sPath+=sFilename;
		if(m_iocp.BuildFilePackageAndSend(m_iCurrentClientID,sFilename))
		{
			AfxMessageBox("Sending transfer info to the client");
		}else
		{

			m_iocp.DisableSendFile(m_iCurrentClientID);
			AfxMessageBox("Error could not send");
		}
		
		
	}
#else
	AfxMessageBox("FileTransfer is Disabled. Define TRANSFERFILEFUNCTIONALITY and recompile.");
#endif
}

