// ex30aView.cpp : implementation of the CEx30aView class
//

#include "stdafx.h"
#include "ex30a.h"
#include "mainfrm.h"

#include "ex30aDoc.h"
#include "ex30aView.h"
#include "Utility.h"
#include "SheetConfig.h"
#include "BlockSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBlockingSocket g_sListen;

/////////////////////////////////////////////////////////////////////////////
// CEx30aView

IMPLEMENT_DYNCREATE(CEx30aView, CEditView)

BEGIN_MESSAGE_MAP(CEx30aView, CEditView)
	//{{AFX_MSG_MAP(CEx30aView)
	ON_COMMAND(ID_INTERNET_START_SERVER, OnInternetStartServer)
	ON_UPDATE_COMMAND_UI(ID_INTERNET_START_SERVER, OnUpdateInternetStartServer)
	ON_COMMAND(ID_INTERNET_REQUEST_SOCK, OnInternetRequestSocket)
	ON_COMMAND(ID_INTERNET_REQUEST_INET, OnInternetRequestWininet)
	ON_COMMAND(ID_INTERNET_STOP_SERVER, OnInternetStopServer)
	ON_UPDATE_COMMAND_UI(ID_INTERNET_STOP_SERVER, OnUpdateInternetStopServer)
	ON_COMMAND(ID_INTERNET_CONFIGURATION, OnInternetConfiguration)
	ON_UPDATE_COMMAND_UI(ID_INTERNET_CONFIGURATION, OnUpdateInternetConfiguration)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(IDC_REQUEST, OnRequest)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx30aView construction/destruction

CEx30aView::CEx30aView()
{
	// TODO: add construction code here

}

CEx30aView::~CEx30aView()
{
}

BOOL CEx30aView::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
	cs.style |= ES_READONLY;
	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CEx30aView drawing

void CEx30aView::OnDraw(CDC* pDC)
{
	CEx30aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx30aView printing

BOOL CEx30aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CEx30aView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CEx30aView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CEx30aView diagnostics

#ifdef _DEBUG
void CEx30aView::AssertValid() const
{
	CEditView::AssertValid();
}

void CEx30aView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CEx30aDoc* CEx30aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx30aDoc)));
	return (CEx30aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx30aView message handlers

void CEx30aView::OnInternetStartServer() 
{
	try {
		CSockAddr saServer;
		if(g_strIPServer.IsEmpty()) { // first or only IP
			saServer = CSockAddr(INADDR_ANY, (USHORT) g_nPortServer);
		}
		else {	// if our computer has multiple IP addresses...
			saServer = CSockAddr(g_strIPServer, (USHORT) g_nPortServer);
		}
		g_sListen.Create();
		g_sListen.Bind(saServer);
		g_sListen.Listen();// start listening
		g_bListening = TRUE;
		g_nConnection = 0;
		AfxBeginThread(ServerThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}
	catch(CBlockingSocketException* e) {
		g_sListen.Cleanup();
		LogBlockingSocketException(GetSafeHwnd(), "VIEW:", e);
		e->Delete();
	}
}

void CEx30aView::OnUpdateInternetStartServer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!g_bListening);
}

void CEx30aView::OnInternetRequestSocket() 
{
	AfxBeginThread(ClientSocketThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

void CEx30aView::OnInternetRequestWininet() 
{
	AfxBeginThread(ClientWinInetThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

void CEx30aView::OnInternetStopServer() 
{
	try {
		if(g_bListening) {
			g_sListen.Close();
		}
	}
	catch(CBlockingSocketException* e) {
		LogBlockingSocketException(GetSafeHwnd(), "VIEW:", e);
		e->Delete();
	}
}

void CEx30aView::OnUpdateInternetStopServer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(g_bListening);
}


void CEx30aView::OnInternetConfiguration() 
{
	CSheetConfig sh("Configuration");
	sh.m_pageServer.m_strDirect = g_strDirect;
	sh.m_pageServer.m_strDefault = g_strDefault;
	sh.m_pageServer.m_nPortServer = g_nPortServer;
	sh.m_pageClient.m_strServerIP = g_strServerIP;
	sh.m_pageClient.m_nPort = g_nPort;
	sh.m_pageClient.m_strServerName = g_strServerName;
	sh.m_pageClient.m_strFile = g_strFile;
	sh.m_pageClient.m_strProxy = g_strProxy;
	sh.m_pageClient.m_bUseProxy = g_bUseProxy;
	sh.m_pageAdv.m_strIPClient = g_strIPClient;
	sh.m_pageAdv.m_strIPServer = g_strIPServer;
	if(sh.DoModal() == IDOK) {
		g_strDirect = sh.m_pageServer.m_strDirect;
		g_strDefault = sh.m_pageServer.m_strDefault;
		g_nPortServer = sh.m_pageServer.m_nPortServer;
		g_strServerIP = sh.m_pageClient.m_strServerIP;
		g_nPort = sh.m_pageClient.m_nPort;
		g_strServerName = sh.m_pageClient.m_strServerName;
		if(sh.m_pageClient.m_strFile.IsEmpty()) {
			g_strFile = "/";
		}
		else {
			g_strFile = sh.m_pageClient.m_strFile;
		}
		g_strProxy = sh.m_pageClient.m_strProxy;
		g_bUseProxy = sh.m_pageClient.m_bUseProxy;
		g_strIPClient = sh.m_pageAdv.m_strIPClient;
		g_strIPServer = sh.m_pageAdv.m_strIPServer;
		if(!g_strIPClient.IsEmpty() && g_bUseProxy) {
			AfxMessageBox("Warning: you can't assign a client IP address if "
				"you are using a proxy server");
		}
		if(!g_strServerIP.IsEmpty() && g_bUseProxy) {
			AfxMessageBox("Warning: you must specify the server by name if "
				"you are using a proxy server");
		}
		if(g_strServerIP.IsEmpty() && g_strServerName.IsEmpty()) {
			AfxMessageBox("Warning: you must specify either a server name or "
				"a server IP address");
		}
		if(!g_strServerIP.IsEmpty() && !g_strServerName.IsEmpty()) {
			AfxMessageBox("Warning: you cannot specify both a server name "
				"and a server IP address");
		}
		::SetCurrentDirectory(g_strDirect);
	}
}

void CEx30aView::OnUpdateInternetConfiguration(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!g_bListening);
}

void CEx30aView::OnEditClearAll() 
{
	SetWindowText("");
}

void CEx30aView::OnRequest() 
{
	CWnd& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndDialogBar;
	// g_strURL: thread sync?
	rBar.GetDlgItemText(IDC_URL, g_strURL);
	TRACE("CEx30aView::OnRequest -- URL = %s\n", (const char*) g_strURL);
	AfxBeginThread(ClientUrlThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

void CEx30aView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// clear-all menu activated on right button
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXT_MENU);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, this);
}
