// MainFrm.cpp : implementation of the CMainFrame class
//
/****************************************************************
Pre-emptive Multithreading Web Spider
Copyright (c) 1998 by Sim Ayers.
**************************************************************/

#include "stdafx.h"
#include "Spider.h"
#include "ThreadParams.h"
#include "Thread.h"

#include "MainFrm.h"
#include "SpiderDoc.h"
#include "SpiderView.h"
#include "SpiderList.h"
#include "utily.h"
#include "UrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE hConnection;
long lThreadCount = 0;
long lURLCount = 0;
int  nCurrentlThreadCount = 0;


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOWS_CLOSEALL, OnWindowsCloseall)
	ON_WM_CLOSE()
	ON_COMMAND(ID_TOOLS_GETURL, OnToolsGetURL)
	ON_COMMAND(ID_TOOLS_KILLTHREAD, OnToolsKillthread)
	ON_WM_DESTROY()
	ON_COMMAND(ID_TOOL_BROKENURLS, OnToolCheckURLs)
	ON_COMMAND(ID_TOOLS_GETHEADER, OnToolsGetServerHeader)
	ON_COMMAND(ID_TOOLS_LIST, OnToolsViewURLList)
	ON_COMMAND(ID_TOOLS_NOT_FOUND, OnToolsURLsNotFound)
	ON_COMMAND(ID_TOOLS_STOP, OnToolsThreadsStop)
	ON_COMMAND(ID_WINDOWS_CLOSEALL, OnWindowsCloseall)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_KILLTHREAD, OnUpdateToolsKillthread)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_STOP, OnUpdateToolsThreadsStop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_THREAD_FILE,OnDocNew)
	ON_MESSAGE(WM_USER_THREAD_PRINT,OnDocUpdate)
	ON_MESSAGE(WM_USER_THREAD_DONE,OnThreadDone)
	ON_MESSAGE(WM_USER_THREAD_STATUS,OnThreadStatus)
	ON_MESSAGE(WM_USER_THREAD_GETSTATUS,OnNewThread)
	ON_MESSAGE(WM_USER_THREAD_GETNEWFILE,OnGetNewFiles)
	ON_MESSAGE(WM_USER_SERVER_STATUS,OnServerStatus)
	ON_MESSAGE(WM_USER_URL_STATUS,OnURLStatus)


END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    m_lCurThreads = 0;
	m_lMaxThreads = MAXIMUM_WAIT_OBJECTS;  //64
	hConnection = CreateSemaphore( NULL,m_lCurThreads,m_lMaxThreads,NULL);
	InitializeCriticalSection(&m_CritSect);

}

CMainFrame::~CMainFrame()
{
	int nRemoveEntry = 0;
	while (g_nEntries > 0)
	{
		delete g_entry[nRemoveEntry];
		g_nEntries--;
		nRemoveEntry++;
	}
	g_nEntries = 0;
	g_entry.RemoveAll();
	CloseHandle(hConnection);
	DeleteCriticalSection(&m_CritSect);

}



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

    static UINT nIndicators[] = {
        ID_SEPARATOR,
        ID_SEPARATOR,
    };

    if (!m_wndStatusBar.Create (this))
        return -1;

    m_wndStatusBar.SetIndicators (nIndicators, 4);

    TEXTMETRIC tm;
    CClientDC dc (this);
    CFont* pFont = m_wndStatusBar.GetFont ();
    CFont* pOldFont = dc.SelectObject (pFont);
    dc.GetTextMetrics (&tm);
    dc.SelectObject (pOldFont);

    int cxWidth;
    UINT nID, nStyle;
    m_wndStatusBar.GetPaneInfo (1, nID, nStyle, cxWidth);
    m_wndStatusBar.SetPaneInfo (1, nID, nStyle, tm.tmAveCharWidth * 40);
    m_wndStatusBar.SetPaneInfo (2, nID, nStyle, tm.tmAveCharWidth * 12);
    m_wndStatusBar.SetPaneInfo (3, nID, nStyle, tm.tmAveCharWidth * 12);

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnWindowsCloseall() 
{
    CWnd *activeWnd;

    // Send a Close command to every open document
    while ( (activeWnd = MDIGetActive()) != 0) {
        // has the document been modified?
        CDocument *activeDoc = ((CFrameWnd *) activeWnd)->GetActiveDocument();
    	activeDoc->SetModifiedFlag(FALSE);

        activeWnd->SendMessage(WM_COMMAND, ID_FILE_CLOSE);
    }
	
}
LRESULT CMainFrame::OnDocNew(WPARAM wParam,LPARAM lParam) 
{
	EnterCriticalSection(&m_CritSect);
	ThreadParams *lpThreadParams = NULL;
	lpThreadParams = (ThreadParams*)lParam;
	
	if(lpThreadParams != NULL)
	{

		lpThreadParams = (ThreadParams*)lParam;
		CSpiderApp *pApp = (CSpiderApp*) AfxGetApp();
		CString lpFileName = lpThreadParams->m_pszURL;
		CString urlPage= "Error in file tranfer";
		if(!lpThreadParams->m_Contents.IsEmpty())
			urlPage = lpThreadParams->m_Contents;

		pApp->ShowURL(lpFileName,urlPage); 
	}		

	LeaveCriticalSection(&m_CritSect);
		

	return 0;
}

LRESULT CMainFrame::OnThreadDone(WPARAM wParam,LPARAM lParam) 
{
	EnterCriticalSection(&m_CritSect);
	
	CString string;
	ThreadParams *lpThreadParams = NULL;
	lpThreadParams = (ThreadParams*)lParam;
	POSITION pos= NULL;

	::InterlockedDecrement(&lThreadCount);
	if(lThreadCount < 0) lThreadCount = 0;
	if(lThreadCount == 0)
	{
		string = "Ready!";
		m_wndStatusBar.SetPaneText (0, (LPCTSTR) string, TRUE);
		string = "Connection Closed";
		m_wndStatusBar.SetPaneText (1, (LPCTSTR) string, TRUE);

	}

	int nThreadsLeft = m_threadList.GetCount();

	if(lpThreadParams != NULL )
	{
		
		for(int i=0; i<nThreadsLeft; i++)
		{
			if((pos = m_threadList.FindIndex(i))!= NULL )
			{				
				CSpiderThread* pThread = m_threadList.GetAt(pos);
				if(pThread != NULL)
				{
					if(lpThreadParams->m_threadID==pThread->m_nThreadID)
					{
						//A thread object is deleted when the last handle to the thread 
						//is closed. 
						m_threadList.RemoveAt(pos);
						

					 delete  lpThreadParams;
	 				if(lThreadCount < MAXIMUM_WAIT_OBJECTS) 
						ReleaseSemaphore(hConnection,1,NULL);
					
					string.Format ("Threads:%d",lThreadCount );
					m_wndStatusBar.SetPaneText (2, (LPCSTR) string, TRUE);
				
						break;
					}
				}

			}
		}

	}

	LeaveCriticalSection(&m_CritSect);


	return 0;
}



LRESULT CMainFrame::OnDocUpdate(WPARAM wParam,LPARAM lParam) 
{
	EnterCriticalSection(&m_CritSect);

	ThreadParams *lpThreadParams = NULL;
	lpThreadParams = (ThreadParams*)lParam;
	CString string = "";

	if(lpThreadParams != NULL)
	{
			if(!lpThreadParams->m_string.IsEmpty())
				string.Format("%s",(LPCTSTR)lpThreadParams->m_string);
			LPCSTR lpstring = string;
			
			if(lpThreadParams->m_hwndNotifyView != NULL)
				::SendMessage(lpThreadParams->m_hwndNotifyView,WM_USER_CHECK_DONE, 0, (LPARAM)lpstring);
			else
			{
				CSpiderView* pActiveView = NULL;
				pActiveView = CSpiderView::GetView();
				if(pActiveView)
					pActiveView->UpdateString(string);

			}
	}
	LeaveCriticalSection(&m_CritSect);

	return 0;
}

LRESULT CMainFrame::OnThreadStatus(WPARAM wParam,LPARAM lParam) 
{
	EnterCriticalSection(&m_CritSect);

	LPCSTR prtline;;
	prtline = (LPCSTR)lParam;
    CString string;
    string.Format ("%s",prtline );
    m_wndStatusBar.SetPaneText (0, (LPCSTR) string, TRUE);
	LeaveCriticalSection(&m_CritSect);
	
	return 0;
}
LRESULT CMainFrame::OnURLStatus(WPARAM wParam,LPARAM lParam) 
{
	EnterCriticalSection(&m_CritSect);

	long nCount = lParam;
    CString string;
    string.Format ("URLs:%d",nCount );
    m_wndStatusBar.SetPaneText (3, (LPCSTR) string, TRUE);

	LeaveCriticalSection(&m_CritSect);

	return 0;
}


LRESULT CMainFrame::OnServerStatus(WPARAM wParam,LPARAM lParam) 
{
	EnterCriticalSection(&m_CritSect);

	LPCSTR prtline;;
	prtline = (LPCSTR)lParam;
    CString string;
    string.Format ("%s",prtline );
    m_wndStatusBar.SetPaneText (1, (LPCSTR) string, TRUE);
	LeaveCriticalSection(&m_CritSect);

	return 0;
}


LRESULT CMainFrame::OnNewThread(WPARAM wParam,LPARAM lParam) 
{
	EnterCriticalSection(&m_CritSect);

	ThreadParams *lpThreadParams = NULL;
	lpThreadParams = (ThreadParams*)lParam;
	UINT ntype = (UINT)wParam;
	CString pszURL = "";
	CString string;
	URLStatus lpEntry;

	if(lpThreadParams != NULL)
	{
		if(!lpThreadParams->m_checkURLName.IsEmpty())	pszURL.Format("%s",(LPCTSTR)lpThreadParams->m_checkURLName);

		BOOL Result= GetURL(pszURL,lpThreadParams->m_hwndNotifyView,(int) ntype,lpThreadParams->m_RootLinks);//	HTTP_CHECK_URL);

	   if(!Result)
	   {
		   string.Format("Error in creating NEW thread ");
			AfxMessageBox(string, MB_OK);
			
	   }
		
	}
	
	LeaveCriticalSection(&m_CritSect);

	return 0;
}

LRESULT CMainFrame::OnGetNewFiles(WPARAM wParam,LPARAM lParam) 
{
	
	EnterCriticalSection(&m_CritSect);

	LPCSTR prtline;;
	UINT type = (UINT)wParam;
	prtline = (LPCSTR)lParam;
	CString pszURL;
	pszURL.Format("%s",(LPCTSTR)prtline);
	
		BOOL Result= GetURL(pszURL,NULL,(int)type);

		   if(!Result)
		   {
			   CString str;
				str.Format("Error in creating NEW thread ");
				AfxMessageBox(str, MB_OK);
			
		   }
	
	LeaveCriticalSection(&m_CritSect);

	return 0;
}





void CMainFrame::OnClose() 
{
	CMDIFrameWnd::OnClose();
}

/******************************************
Create the Thread and process the desired URL action 
*******************************************/

BOOL CMainFrame::GetURL(LPCTSTR lpFileName,	HWND lphwndNotifyView,	
						int lptype,BOOL lpRoot)
{


	if(lpFileName == NULL) return FALSE;
	if(lptype< HTTP_GET_FILE || lptype > HTTP_GET_ENTRY) lptype = 0;

    ThreadParams* pThreadParams = new ThreadParams;
	if(!pThreadParams) return FALSE;


	pThreadParams->m_pszURL.Format("%s",lpFileName);
	pThreadParams->m_type = lptype;
	pThreadParams->m_Status = 0;
	pThreadParams->m_RootLinks = lpRoot;

	pThreadParams->m_hwndNotifyProgress = 
			AfxGetMainWnd()->m_hWnd;
	
	if(lphwndNotifyView != NULL)
	  pThreadParams->m_hwndNotifyView = lphwndNotifyView;
	else
	  pThreadParams->m_hwndNotifyView = NULL;


	CSpiderThread* pThread;
	pThread = NULL;
	pThread = new CSpiderThread(CSpiderThread::ThreadFunc,pThreadParams); // create a new CSpiderThread object

	if (pThread == NULL)
	{
		AfxMessageBox("Cannot Start New Thread");
		delete pThreadParams;
		return FALSE;
	}    


	if (!pThread->CreateThread())   //  Starts execution of a CWinThread object
	{
		AfxMessageBox("Cannot Start New Thread");
		delete pThread;
		pThread = NULL;
		delete pThreadParams;
		return FALSE;
	}    

	pThreadParams->m_threadID = pThread->m_nThreadID;


	// since everything is successful, add the thread to our list

	m_threadList.AddTail(pThread);
	CString string;
	::InterlockedIncrement(&lThreadCount);
	string.Format ("Threads:%d",lThreadCount);
	m_wndStatusBar.SetPaneText (2, (LPCTSTR) string, TRUE);



	return TRUE;


}

void CMainFrame::OnDestroy() 
{
	
	OnToolsKillthread();

	CMDIFrameWnd::OnDestroy();

	
}
void CMainFrame::GetConnected()
{
	DWORD 
dwConnectionTypes = INTERNET_CONNECTION_LAN |
                          INTERNET_CONNECTION_MODEM |
                          INTERNET_CONNECTION_PROXY;
 if (!InternetGetConnectedState(&dwConnectionTypes, 0))
 {
     InternetAutodial(INTERNET_AUTODIAL_FORCE_UNATTENDED,
                    0);
 } 

}

/*************************************
*     Get a File from a URL Location
**************************************/
void CMainFrame::OnToolsGetURL()  

{
	CUrlDlg	 dlg;
	CString str;
	CSpiderApp *pApp = (CSpiderApp*) AfxGetApp();

	char* pFileName = "Urls.log";
	char lpFileName[MAX_PATH];
	strcpy(lpFileName,pApp->m_HomeDir);
	strcat(lpFileName,"\\");
	strcat(lpFileName,pFileName);


	dlg.LoadFile(lpFileName);


	if(dlg.DoModal() != IDOK) return;

	dlg.SaveFile(lpFileName);

	if(!dlg.m_WebFileName.IsEmpty())
	{
		
		BOOL Result= GetURL(dlg.m_WebFileName,NULL,HTTP_GET_FILE,FALSE);

		   if(!Result)
		   {
				str.Format("Error in thread file transfer");
				AfxMessageBox(str, MB_OK);

		   }
	}

	
}



/*************************************
*  Check Broken URLs in a HTML file on the Web
**************************************/
void CMainFrame::OnToolCheckURLs() 
{
	CUrlDlg	 dlg;
	CSpiderApp *pApp = (CSpiderApp*) AfxGetApp();
	HWND hwndNotifyView = NULL;

	char* pFileName = "Urls.log";
	char lpFileName[MAX_PATH];
	strcpy(lpFileName,pApp->m_HomeDir);
	strcat(lpFileName,"\\");
	strcat(lpFileName,pFileName);


	dlg.LoadFile(lpFileName);


	if(dlg.DoModal() != IDOK) return;

	dlg.SaveFile(lpFileName);

	CString str ="";

	if(!dlg.m_WebFileName.IsEmpty())
	{
		if(RobotCheck(dlg.m_WebFileName))
		{
			AfxMessageBox("Robot exclusion text file found.\nGoing to bail out, before we get caught.");
			return;
		}

		CSpiderApp *pApp = (CSpiderApp*) AfxGetApp();
		pApp->ShowURL(dlg.m_WebFileName,str); 
		CMDIChildWnd * pChild =
        ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
 

		::SendMessage(pChild->m_hWnd,WM_USER_LIST, 1, 0);

		CSpiderList* pActiveView = NULL;
		pActiveView = CSpiderList::GetView();
		if(pActiveView)
		hwndNotifyView = pActiveView->m_hWnd;


		BOOL Result= GetURL(dlg.m_WebFileName,hwndNotifyView,HTTP_CHECK_URL_ROOT,dlg.m_root);

		   if(!Result)
		   {
				str.Format("Error in thread ");
				AfxMessageBox(str, MB_OK);
				return;
		   }

	}
	
	lURLCount = 0;
	str ="URLs:0";
	m_wndStatusBar.SetPaneText (3, (LPCTSTR) str, TRUE);
}

/******************************************
Get a Server Response Header for a given URL
*******************************************/

void CMainFrame::OnToolsGetServerHeader() 
{
	CUrlDlg	 dlg;
	CSpiderApp *pApp = (CSpiderApp*) AfxGetApp();

	char* pFileName = "Urls.log";
	char lpFileName[MAX_PATH];
	strcpy(lpFileName,pApp->m_HomeDir);
	strcat(lpFileName,"\\");
	strcat(lpFileName,pFileName);


	dlg.LoadFile(lpFileName);


	if(dlg.DoModal() != IDOK) return;

	dlg.SaveFile(lpFileName);

	CString str ="";

	if(!dlg.m_WebFileName.IsEmpty())
	{
		CSpiderApp *pApp = (CSpiderApp*) AfxGetApp();
		pApp->ShowURL(dlg.m_WebFileName,str); 


		BOOL Result= GetURL(dlg.m_WebFileName,NULL,HTTP_GET_HEADER,FALSE);

		   if(!Result)
		   {
				str.Format("Error in thread ");
				AfxMessageBox(str, MB_OK);
				return;
		   }

	}
	
}

/******************************************
View the list of URLS that did NOT checked out OK
*******************************************/

void CMainFrame::OnToolsURLsNotFound() 
{
	if(g_nEntries == 0)
	{
		AfxMessageBox("No URL's checked yet!");
		return;
	}

	CString string="";
	CSpiderApp *pApp = (CSpiderApp*) AfxGetApp();
	pApp->ShowURL("Not_Found",string); 
	CSpiderDoc *PDoc = NULL;
	PDoc =CSpiderDoc::GetDoc();

	for (UINT i = 0; i < g_nEntries; i ++)
	{
		if(g_entry[i]->m_Status != 200)
		{
			string.Format("%d...%s...%s",i+1,g_entry[i]->m_URL,g_entry[i]->m_StatusString);
			
			if (PDoc)
				PDoc->CheckURLUpdate(string); 	
		}
	}

}
/******************************************
View the list of all URLS that were checked
*******************************************/
void CMainFrame::OnToolsViewURLList() 
{
	if(g_nEntries == 0)
	{
		AfxMessageBox("No URL's checked yet!");
		return;
	}

	CString string="";
	CSpiderApp *pApp = (CSpiderApp*) AfxGetApp();
	pApp->ShowURL("URL_LIST",string); 
	CSpiderDoc *PDoc = NULL;
	PDoc =CSpiderDoc::GetDoc();

	for (UINT i = 0; i < g_nEntries; i ++)
	{
			string.Format("%d...%s...%s",i+1,g_entry[i]->m_URL,g_entry[i]->m_StatusString);
			
			if (PDoc)
				PDoc->CheckURLUpdate(string); 	
		
	}


}

/***********************************
* Let All the threads  stop,  without crashing the program
************************************/
void CMainFrame::OnToolsThreadsStop() 
{
	int nCount = 0;
	POSITION pos= NULL;
	int nThreadsLeft = m_threadList.GetCount();

	for(int i=0; i<nThreadsLeft; i++)
	{
		if((pos = m_threadList.FindIndex(i))!= NULL )
		{				
			CSpiderThread* pThread = m_threadList.GetAt(pos);
			if(pThread->m_hThread != NULL)
			{
				nCount++;
				pThread->KillThread();
				
			}
		}
	}
		
	CString string;
	string.Format ("Threads:%d",nCount);
	m_wndStatusBar.SetPaneText (2, (LPCTSTR) string, TRUE);


	if(nCount > 0)
	{
		string.Format ("Number of Threads %d \nStill Active ",nCount );
		AfxMessageBox(string);
	}
	
}

void CMainFrame::OnUpdateToolsThreadsStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(lThreadCount!=0);
	
}


/***********************************
* Kill off All threads, might lock the program up at times
************************************/

void CMainFrame::OnToolsKillthread() 
{

	int nCount,tCount,i;
	int nThreadsLeft;
	POSITION pos= NULL;
	DWORD dwStatus;

	nCount = 0,tCount=0;
	nThreadsLeft = m_threadList.GetCount();

		for(i=0; i<nThreadsLeft; i++)
		{
			if((pos = m_threadList.FindIndex(i))!= NULL )
			{				
				CSpiderThread* pThread = m_threadList.GetAt(pos);
				if(pThread->m_hThread != NULL)
					pThread->KillThread();

			}
		}
		
		Sleep(200);
		nThreadsLeft = m_threadList.GetCount();

		for(i=0; i<nThreadsLeft; i++)
		{
			if((pos = m_threadList.FindIndex(i))!= NULL )
			{				
				CSpiderThread* pThread = m_threadList.GetAt(pos);
					if(pThread->m_hThread != NULL)
					{
						tCount++;
						pThread->KillThread();

						::GetExitCodeThread(pThread->m_hThread, &dwStatus);
						if (dwStatus == STILL_ACTIVE)
							nCount++;
						else 
							m_threadList.RemoveAt(pos);
						

					}
			}
		}
	
	CString string;
	string.Format ("Threads:%d",nCount);
	m_wndStatusBar.SetPaneText (2, (LPCTSTR) string, TRUE);

	if(nCount > 0)
	{
		string.Format ("Number of Threads %d \nStill Active %d",tCount,nCount );
		AfxMessageBox(string);
	}
	
}

void CMainFrame::OnUpdateToolsKillthread(CCmdUI* pCmdUI) 
{
	int nThreadsLeft = m_threadList.GetCount();

	pCmdUI->Enable(nThreadsLeft != 0);
	
}

/***************************
* for robot exclusion
* will return true if the server has a robots.txt file.
**************************/

BOOL CMainFrame::RobotCheck(LPCTSTR pszURL)
{
	DWORD dwRet = 0;
	BOOL bRet = FALSE;
	CString strServerName;
	CString strObject;
	DWORD   dwServiceType;
	INTERNET_PORT  nPort;
	CMyInternetSession* pSession = NULL;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;

	try
	{
		AfxParseURL(pszURL,dwServiceType,strServerName,strObject,nPort);

	pSession = new CMyInternetSession("Robot",1);
	pSession->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,30000);
		
		/* The delay value in milliseconds to wait between connection retries.*/
	pSession->SetOption(INTERNET_OPTION_CONNECT_BACKOFF,1000);
		
	
	/* The retry count to use for Internet connection requests. If a connection 
	attempt still fails after the specified number of tries, the request is canceled.
	The default is five. */
	pSession->SetOption(INTERNET_OPTION_CONNECT_RETRIES,2);
    pSession->EnableStatusCallback(TRUE);
	pSession->m_pMainWnd = 	AfxGetMainWnd()->m_hWnd;
	pSession->m_strHttpSite.Format("%s",pszURL);

	pServer = pSession->GetHttpConnection(strServerName,nPort);
	pFile = pServer->OpenRequest(_T("GET"),"/robots.txt");
	pFile->SendRequest();
	if(pFile != NULL)
		pFile->QueryInfoStatusCode(dwRet);
	if(dwRet== 200)
		bRet = TRUE;


		if(pFile != NULL)
		{	pFile->Close();
			delete pFile;
			pFile= NULL;
		}

		

		if (pServer!= NULL)
		{
			pServer->Close();
			delete pServer;
			pServer = NULL;
		
		}


		if (pSession != NULL)
		{
			pSession->Close();
			delete pSession;
			pSession = NULL;
		}

	}
	catch (CInternetException* pEx)
	{
		// catch errors from WinINet
		//pEx->ReportError();
		pEx->Delete();
		bRet = FALSE;
	}

	return bRet;
}