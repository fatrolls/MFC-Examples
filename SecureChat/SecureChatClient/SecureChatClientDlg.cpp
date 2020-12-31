// SecureChatClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SecureChatClient.h"
#include "SecureChatClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecureChatClientDlg dialog

CSecureChatClientDlg::CSecureChatClientDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSecureChatClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSecureChatClientDlg)
	m_sIP = _T("127.0.0.1");
	m_sMessage = _T("");
	m_sName = _T("Alice");
	m_nKeySize = 32;
	m_nPort = 999;
	m_bUseSavedPubKey = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_pPublicKey=NULL;
	m_nSizePublicKey=0;
	
}

void CSecureChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSecureChatClientDlg)
	DDX_Control(pDX, IDC_CONNECT, m_cBtnConnect);
	DDX_Control(pDX, IDC_LOGG, m_cLogg);
	DDX_Text(pDX, IDC_IP, m_sIP);
	DDX_Text(pDX, IDC_MESSAGE, m_sMessage);
	DDX_Text(pDX, IDC_NAME, m_sName);
	DDX_Text(pDX, IDC_PKEYSIZE, m_nKeySize);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDX_Check(pDX, IDC_USESAVEDPUBLICKEY, m_bUseSavedPubKey);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSecureChatClientDlg, CDialog)
//{{AFX_MSG_MAP(CSecureChatClientDlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_CONNECT, OnConnect)
ON_COMMAND(ID_SEND_MESSAGE, OnSend)
ON_MESSAGE(WM_LOGG_APPEND, OnAppendLog)
ON_MESSAGE(WM_NEW_CONNECTION, OnNewClient)
ON_MESSAGE(WM_DISCONNECT_CLIENT, OnClientDisconnected)
ON_BN_CLICKED(IDC_SEND, OnSend)
ON_BN_CLICKED(IDC_CLEARWINDOW, OnClearwindow)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecureChatClientDlg message handlers



LRESULT CSecureChatClientDlg::OnNewClient(WPARAM wParam, LPARAM lParam)
{
	unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
	m_cLogg.AppendString("\r\n---------------------------------");
	UpdateData(FALSE);
	if(piID!=NULL)
		delete piID; 
	   return 0;
}


LRESULT CSecureChatClientDlg::OnClientDisconnected(WPARAM wParam, LPARAM lParam)
{
	unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
	SetGuiConnectedMode(FALSE);
	AfxMessageBox("Disconnected..");
	UpdateData(FALSE);
	if(piID!=NULL)
		delete piID; 
	   return 0;
}

LRESULT CSecureChatClientDlg::OnAppendLog(WPARAM wParam, LPARAM lParam)
{
	char* msg = reinterpret_cast<char*>(lParam);
	if(msg!=NULL)
	{
		
		m_cLogg.AppendString(msg);
	}
	delete[] msg;
	return 0;
}

BOOL CSecureChatClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_cLogg.AllowSelection(TRUE);
	// 
	// Start the IOCP 
	// 
	
	m_iocp.m_StatusLock.Lock();
	m_iocp.m_hWnd=m_hWnd;
	m_iocp.m_StatusLock.Unlock();
	if( !m_iocp.Start(-1) )
		AfxMessageBox("Error could not start the Server");
	
	SetGuiConnectedMode(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSecureChatClientDlg::OnPaint() 
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
HCURSOR CSecureChatClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSecureChatClientDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CSecureChatClientDlg::OnDestroy() 
{
	
	
	m_iocp.m_StatusLock.Lock();
	m_iocp.m_hWnd=NULL;
	m_iocp.m_StatusLock.Unlock();
	
	// Delete the m_pBublicKey 
	if ( m_pPublicKey )
	{
		m_iocp.m_StatusLock.Lock();
		m_iocp.m_pPublicKeyP=NULL;
		m_iocp.m_nSizePublicKey=0;
		m_iocp.m_StatusLock.Unlock();
		delete[] m_pPublicKey;
		m_pPublicKey =NULL;
		m_nSizePublicKey=0;
	}
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CSecureChatClientDlg::OnConnect() 
{
	UpdateData(TRUE);
	// Disconnect if connected. 
	if ( m_iocp.IsConnected() )
	{
		
		m_iocp.DisconnectAll();
		
	}
	else  // connect to remote server. 
	{
		
		if ( m_sIP.IsEmpty() )
		{
			AfxMessageBox("Please enter a IP nr..");
			return;
		}
		
		if ( m_nPort <=0 )
		{
			AfxMessageBox("Please enter a valid port nr.");
			return;
		}
		
		if ( m_sName.IsEmpty() )
		{
			AfxMessageBox("Please enter a username.");
			return;
		}
		
		
		BOOL bConnect=TRUE;
		if( !m_bUseSavedPubKey || !m_pPublicKey )
		{
			bConnect=m_RandomDlg.DoModal()==IDOK;
		}
		
		// Launch the connect thread. 
		if ( bConnect )
		{
			m_cBtnConnect.EnableWindow(FALSE);
			AfxBeginThread(CSecureChatClientDlg::ThreadWrapperConnect, (void*)this,
				THREAD_PRIORITY_NORMAL);
		}
	}
	
}

UINT CSecureChatClientDlg::ThreadWrapperConnect(LPVOID pParam)
{
	CSecureChatClientDlg* pThis=NULL;
	pThis = reinterpret_cast<CSecureChatClientDlg*>(pParam);
	if(pThis)
	{
		pThis->MakeConnection();
		
	}
	return 0;
}

/*
* This function connects to the remote server, and also 
* Generates a prime nr. 
*
*/

void CSecureChatClientDlg::MakeConnection()
{
	m_cLogg.Clear();
	m_cBtnConnect.EnableWindow(FALSE);
	
	MyCryptLib cCryptLib;
	CString sTemp="";
	
	// Generate a new Public key if you did not have it or whant to use the old one. 
	if ( !m_bUseSavedPubKey || !m_pPublicKey)
	{
		// Delete the m_pBublicKey 
		if ( m_pPublicKey )
		{
			m_iocp.m_StatusLock.Lock();
			m_iocp.m_pPublicKeyP=NULL;
			m_iocp.m_nSizePublicKey=0;
			m_iocp.m_StatusLock.Unlock();
			delete[] m_pPublicKey;
			m_pPublicKey =NULL;
			m_nSizePublicKey=0;
		}
		
		m_cLogg.AppendString("Generating public key P, this may take a while.. ");
		m_pPublicKey = new DWORD[m_nKeySize];
		
		// be safe. 
		if ( !m_pPublicKey )
		{
			m_cLogg.AppendString("Error not enough memory.. ");
			return;
		}
		
		UINT nSize=cCryptLib.BNMakePrime(m_pPublicKey,m_nKeySize,m_RandomDlg.m_raw_pool,_POOL_SIZE_);
		
		if ( nSize > 0 )
		{
			sTemp.Format("Successfully generated a %i bit prime nr.",nSize);
			m_cLogg.AppendString(sTemp);
			m_nSizePublicKey=m_nKeySize;
			m_bUseSavedPubKey=TRUE;
			
		}else
		{
			m_cLogg.AppendString("Faild to Generate Prime nr, Please retry..");
			delete[] m_pPublicKey;
			m_pPublicKey =NULL;
			m_nSizePublicKey=0;
		}
	}
	
	// Set the Public key   
	m_iocp.m_StatusLock.Lock();
	m_iocp.m_pPublicKeyP=m_pPublicKey;
	m_iocp.m_nSizePublicKey=m_nKeySize;
	m_iocp.m_sUserName=m_sName;
	m_iocp.m_StatusLock.Unlock();
	
	sTemp.Format("Connecting to %s:%i...",m_sIP,m_nPort);
	m_cLogg.AppendString(sTemp);
	
	if( !m_iocp.Connect(m_sIP,m_nPort) )
	{
		m_cLogg.AppendString("Connection failed..");
		SetGuiConnectedMode(FALSE);
	}else
	{
		m_cLogg.AppendString("Connection successfull..");
		SetGuiConnectedMode();
	}
	
	m_cBtnConnect.EnableWindow(TRUE);
	
}




void CSecureChatClientDlg::OnSend() 
{
	UpdateData(TRUE);
	if ( !m_sMessage.IsEmpty() && m_iocp.IsStarted() && m_iocp.IsConnected() )
	{
		m_iocp.SendTextMessage(m_sMessage);
		m_sMessage="";
		UpdateData(FALSE);
	}	
}


/*
*	Helper Function Shows/hide an Ctrl. 
*/
inline void CSecureChatClientDlg::EnableCtrl(int nCtrlID,BOOL bShow)
{
	CWnd *pCtrl=NULL;
	pCtrl=GetDlgItem(nCtrlID);
	if(pCtrl!=NULL)
		pCtrl->EnableWindow(bShow);
}

/*
*	Changes the GUI (the buttons, etc) to reflekt 
*  The state of the connection. 
*
*/
void CSecureChatClientDlg::SetGuiConnectedMode(BOOL bConnected)
{
	m_cBtnConnect.EnableWindow(TRUE);
	m_cBtnConnect.SetWindowText(bConnected ? "Disconnect" : "Connect" );
	EnableCtrl(IDC_MESSAGE,bConnected);
	EnableCtrl(IDC_SEND,bConnected);
	EnableCtrl(IDC_IP,!bConnected);
	EnableCtrl(IDC_PORT,!bConnected);
	EnableCtrl(IDC_PKEYSIZE,!bConnected);
	EnableCtrl(IDC_USESAVEDPUBLICKEY,!bConnected);
	EnableCtrl(IDC_NAME,!bConnected);
}


void CSecureChatClientDlg::OnClearwindow() 
{
	m_cLogg.Clear();	
}
