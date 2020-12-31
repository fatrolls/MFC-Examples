// InetThread.cpp : implementation file
//
/*******************************************
Pre-emptive Multithreading Web Spider
Copyright (c) 1998 by Sim Ayers.
*******************************************************************/

#include "stdafx.h"
#include "Spider.h"
#include "ThreadParams.h"
#include "Thread.h"
#include "utily.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern 	HANDLE hConnection;
UINT g_nEntries = 0;
CArray<CEntry*, CEntry*> g_entry;
extern long lThreadCount;
extern long lURLCount;

static const TCHAR szHeaders[] = _T("Accept: text/*\r\n");

static const TCHAR AgentName[] = _T("XYZ Spider");

static DWORD dwHttpRequestFlags =	INTERNET_FLAG_EXISTING_CONNECT |  INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE ; 

static DWORD dwHttpRequestFlags2 =	INTERNET_FLAG_EXISTING_CONNECT |  INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE |INTERNET_FLAG_NO_AUTO_REDIRECT;


void CMyInternetSession::OnStatusCallback(DWORD  dwContext , DWORD dwInternetStatus,
	LPVOID  lpvStatusInformation , DWORD  dwStatusInformationLen )
{
	
	CString strStatus= "";
	
	switch(dwInternetStatus)
	{
	case INTERNET_STATUS_STATE_CHANGE:	
		strStatus="Busy";
		break;

	case INTERNET_STATUS_REQUEST_COMPLETE:
		strStatus="request complete";
		break;
	case INTERNET_STATUS_CONNECTING_TO_SERVER:
		strStatus="Connecting to server...";
		break;

	case INTERNET_STATUS_RESOLVING_NAME:
		strStatus.Format("resolving name for %s", lpvStatusInformation);
		break;
	case INTERNET_STATUS_NAME_RESOLVED:	
		strStatus.Format("resolved name for %s!", lpvStatusInformation);
		break;
	case INTERNET_STATUS_CONNECTED_TO_SERVER:
		strStatus="Connected to server!";
		break;
	case INTERNET_STATUS_SENDING_REQUEST:	
		strStatus="Sending request...";
		break;
	case INTERNET_STATUS_REQUEST_SENT:	
		strStatus="Request sent";
		break;
	case INTERNET_STATUS_RECEIVING_RESPONSE:
		strStatus="Receiving response...";
		break;
	case INTERNET_STATUS_RESPONSE_RECEIVED:	
		strStatus="Response received!";
		break;
	case INTERNET_STATUS_CLOSING_CONNECTION:
		strStatus="Closing connection...";
		break;
	case INTERNET_STATUS_CONNECTION_CLOSED:	
		strStatus="Connection close!";
		break;
	case INTERNET_STATUS_HANDLE_CLOSING:
		strStatus="Closing Connection...";
	case INTERNET_STATUS_HANDLE_CREATED:
		strStatus="Connection created!";
		break;
	case INTERNET_STATUS_REDIRECT:
		strStatus ="Redirected to URL";
		break;

	case INTERNET_STATUS_CTL_RESPONSE_RECEIVED:
	default:
		strStatus.Format("Unknown status: %d", dwInternetStatus);
		break;
	}

	LPCSTR line = strStatus;

	if(m_pMainWnd !=NULL)
	{
		::SendMessage (m_pMainWnd,WM_USER_SERVER_STATUS, 0,(LPARAM)line);
		LPCSTR lpstr = m_strHttpSite;
		::SendMessage (m_pMainWnd,WM_USER_THREAD_STATUS, 0,(LPARAM)lpstr);

	}

}

// simple worker thread Proc function
UINT CSpiderThread::ThreadFunc(LPVOID pParam)
{
	ThreadParams * lpThreadParams = (ThreadParams*) pParam;
	CSpiderThread* lpThread = (CSpiderThread*) lpThreadParams->m_pThread;
	
	lpThread->ThreadRun(lpThreadParams);

	// Use  SendMessage instead of PostMessage here to keep the current thread count
	// Synchronizied. If the number of threads is greater than MAXIMUM_WAIT_OBJECTS (64)
	// the program will be come	 unresponsive to user input

	::SendMessage(lpThreadParams->m_hwndNotifyProgress,
		WM_USER_THREAD_DONE, 0, (LPARAM)lpThreadParams);  // deletes lpThreadParams and decrements the thread count

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CSpiderThread


CSpiderThread::CSpiderThread(AFX_THREADPROC pfnThreadProc,ThreadParams *pThreadParams)
	:CWinThread(pfnThreadProc,pThreadParams)
{
	
	m_pSession = NULL;
	m_pServer =NULL;
	m_pFile= NULL;
	m_strCurrentServer = "";
	m_bDone = FALSE;
	pThreadParams->m_pThread = this;


}

CSpiderThread::~CSpiderThread()
{
	CleanUp();

}


void CSpiderThread::KillThread()
{
	// Note: this function is called in the context of other threads,
	//	not the thread itself.
	m_bDone = TRUE;
	CleanUp();
}



BOOL CSpiderThread::InitServer()
{
	
	try{
		m_pSession = new CMyInternetSession(AgentName,m_nThreadID);
		int ntimeOut = 30;  // very important, can cause a Server time-out if set to low
							// or hang the thread if set to high.
		/*
		The time-out value in milliseconds to use for Internet connection requests. 
		If a connection request takes longer than this timeout, the request is canceled.
		The default timeout is infinite. */
		m_pSession->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,1000* ntimeOut);
		
		/* The delay value in milliseconds to wait between connection retries.*/
		m_pSession->SetOption(INTERNET_OPTION_CONNECT_BACKOFF,1000);
		

		/* The retry count to use for Internet connection requests. If a connection 
		attempt still fails after the specified number of tries, the request is canceled.
		The default is five. */
		m_pSession->SetOption(INTERNET_OPTION_CONNECT_RETRIES,1);
        m_pSession->EnableStatusCallback(TRUE);

		}
		catch (CInternetException* pEx)
		{
			// catch errors from WinINet
			//pEx->ReportError();
			m_pSession = NULL;
			pEx->Delete();

			return FALSE ;
		}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CSpiderThread, CWinThread)
	//{{AFX_MSG_MAP(CSpiderThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSpiderThread message handlers


BOOL CSpiderThread::ThreadRun(ThreadParams *pThreadParams)
{
	
	CString str;

	BOOL bRun = FALSE;
	
	bRun = InitServer();
	if (!bRun)
		return bRun;

	if(pThreadParams->m_pszURL.IsEmpty()) return FALSE;
	if (m_bDone)
		return 0;

	m_pSession->m_pMainWnd = pThreadParams->m_hwndNotifyProgress;

	if(!ParseURL(pThreadParams)) return FALSE;
	
	PrintStatus(pThreadParams,pThreadParams->m_pszURL);

	switch(pThreadParams->m_type)
	{

	case HTTP_GET_FILE:

	if(!GetHttpFile(pThreadParams->m_strServerName, 
    pThreadParams->m_strObject,pThreadParams))
	{
		str.Format("Error in getting %s",(LPCTSTR)pThreadParams->m_pszURL);
		AfxMessageBox(str, MB_OK);
	}

	break;

	case HTTP_CHECK_URL_ROOT:

	if(GetHttpFile(pThreadParams->m_strServerName,pThreadParams->m_strObject, pThreadParams,FALSE))
	{
		if (m_bDone)
			return 0;

		CheckAllURLs(pThreadParams->m_strServerName,pThreadParams);

	}

	break;


	case HTTP_CHECK_URL:

	CheckURL(pThreadParams->m_strServerName, pThreadParams->m_strObject,pThreadParams);
	
	break;


	case HTTP_GET_HEADER:

	if(!GetServerHeader(pThreadParams->m_strServerName,pThreadParams->m_strObject,pThreadParams))
	{
		str.Format("Error in getting Server Response Header for\n%s",(LPCTSTR)pThreadParams->m_pszURL);
		AfxMessageBox(str, MB_OK);

	}

	break;

	}

	return TRUE;

}


BOOL CSpiderThread::GetServerHeader(LPCTSTR ServerName, LPCTSTR strObject,ThreadParams *pThreadParams)
{

	if(ServerName == NULL || strObject == NULL) return 0;

	DWORD dwRet = GetHttpStatus(ServerName, strObject);

	pThreadParams->m_Status = dwRet;

	if (m_bDone)
		return 0;
	
	if(dwRet <200  || dwRet > 400) return FALSE;

	if(m_pFile != NULL && m_pServer != NULL && m_pSession != NULL)
	{

			CString rString;
			m_pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF,rString);
			PrintLine(pThreadParams,rString);

	}
	
  return TRUE;

}

BOOL CSpiderThread::GetHttpFile(LPCTSTR ServerName,LPCTSTR strObject,ThreadParams *pThreadParams,BOOL ViewFile)
{

	CString rString;
	LPCTSTR lpsz;
	LPCTSTR lpszStop;
	int pdest,j=0;
	TCHAR sz[4096];
	memset(sz,'\0',sizeof(sz));
	pThreadParams->m_Contents = "";		

	if(strObject  == NULL) return FALSE;


	if(GetHttpStatus(ServerName, strObject)!= 200)
		return FALSE;
	if(m_pFile != NULL && m_pServer != NULL)
	{
		m_pFile->QueryInfo(HTTP_QUERY_CONTENT_TYPE,rString);
	
		pdest = rString.Find("text");
		if(pdest < 0 ) return FALSE;
	}

	if(m_pFile != NULL && m_pServer != NULL && m_pSession != NULL)
	{
		try
		{
			while (m_pFile->ReadString(sz, 4095))
			{
					rString = "";		
					lpsz = sz;
					if(lpsz != NULL)
					{
						lpszStop = sz + lstrlen(sz);
						j=0;
						while (lpsz < lpszStop)
						{
							if(*lpsz =='\n')	rString += "\r\n";

							else rString += sz[j];

							++lpsz;
							j++;

						}

						pThreadParams->m_Contents += rString;
					}
			}

		}

		catch (CInternetException* pEx)
		{
			// catch errors from WinINet
			//pEx->ReportError();
			m_pFile= NULL;
			pEx->Delete();
			return 0;
		}


		
	}

		
	if(ViewFile)
		::SendMessage(pThreadParams->m_hwndNotifyProgress,
				WM_USER_THREAD_FILE, pThreadParams->m_threadID, (LPARAM)pThreadParams);

	return TRUE;
}

int LookUpEntry(LPCTSTR pszURL)
{

	if(pszURL == NULL) return -1;
	
	CriticalSectionLock  plock;
	
	CString URL,strTemp;
	URL.Format("%s",(LPCTSTR)pszURL);
	int pdest = URL.Find(":");
	if(pdest>0)
		strTemp = URL.Right(URL.GetLength()-1 - pdest - 2);
	else
		strTemp = URL;

	int nRet = -1;
	for (UINT i = 0; i < g_nEntries; i ++)
	{
		if(strTemp.CompareNoCase(g_entry[i]->m_URL)==0)
		{
			nRet = i;
			break;
		}
	}


	return nRet;
}
int AddEntry(URLStatus * lpEntry)
{
	

	CriticalSectionLock  plock;
	
	if(lpEntry->m_URL.IsEmpty())
	{
	
		return -1;
	}
		
	for (UINT i = 0; i < g_nEntries; i ++)	{	// only add entry once
		if(lpEntry->m_URL.Compare(g_entry[i]->m_URL)==0)
		{
			
			return -1;
		}
	}

	CEntry* newEntry = new CEntry;

	newEntry->m_URL = lpEntry->m_URL;
	newEntry->m_URLPage = lpEntry->m_URLPage;

	newEntry->m_Status = lpEntry->m_Status;
	newEntry->m_StatusString = lpEntry->m_StatusString;
	newEntry->m_LastModified = lpEntry->m_LastModified;
	newEntry->m_ContentType = lpEntry->m_ContentType;
	newEntry->m_ContentLength = lpEntry->m_ContentLength;

	g_nEntries++;

	// store in the array and get retVal to pass to the view for updating
	int retVal = g_entry.Add(newEntry);

	return retVal;
}


BOOL CSpiderThread::CheckURL(LPCTSTR ServerName, LPCTSTR strObject,ThreadParams *pThreadParams)
{
	if(ServerName == NULL || strObject==NULL) return FALSE;
	DWORD dwRet;
	CString rString = "";
	rString.Format("%s%s",ServerName,strObject);

	int npos = LookUpEntry((LPCTSTR)rString);
	if (m_bDone)	return 0;

	if(npos >= 0  && g_entry[npos]->m_Status != ERROR_INTERNET_TIMEOUT) // just print the status out to the view window if we have already visited the web page in question
	{
		pThreadParams->m_pStatus.m_URL = rString;
		pThreadParams->m_pStatus.m_URLPage = pThreadParams->m_pszURL;
		pThreadParams->m_pStatus.m_Status = g_entry[npos]->m_Status;
		pThreadParams->m_pStatus.m_ContentType = g_entry[npos]->m_ContentType;
		pThreadParams->m_pStatus.m_ContentLength = g_entry[npos]->m_ContentLength;
		pThreadParams->m_pStatus.m_LastModified = g_entry[npos]->m_LastModified;
		pThreadParams->m_pStatus.m_StatusString = g_entry[npos]->m_StatusString;
	}

	else
	{
	
		dwRet = GetHttpStatus(ServerName, strObject);
		pThreadParams->m_Status = dwRet;

		pThreadParams->m_pStatus.m_URL = rString;
		pThreadParams->m_pStatus.m_URLPage = pThreadParams->m_pszURL;
		pThreadParams->m_pStatus.m_Status = dwRet;
		pThreadParams->m_pStatus.m_ContentType ="";
		pThreadParams->m_pStatus.m_ContentLength = "";
		pThreadParams->m_pStatus.m_LastModified ="";
		if (m_bDone)	return 0;

		if(m_pFile != NULL && m_pServer != NULL)
		{
			m_pFile->QueryInfo(HTTP_QUERY_CONTENT_TYPE,pThreadParams->m_pStatus.m_ContentType);
			m_pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,pThreadParams->m_pStatus.m_ContentLength);
			m_pFile->QueryInfo(HTTP_QUERY_LAST_MODIFIED,pThreadParams->m_pStatus.m_LastModified);
		}
		if (m_bDone)	return 0;

		switch(dwRet)
		{
		case 200:
				pThreadParams->m_pStatus.m_StatusString = _T("ok");
				break;
		case 301:
				pThreadParams->m_pStatus.m_StatusString = _T("redirected to a new URL");
				break;
		case 302:
				pThreadParams->m_pStatus.m_StatusString = _T("resides under a different URL");
				break;
		case 401:
				pThreadParams->m_pStatus.m_StatusString = _T("auth required");
				break;
		case 402:
				pThreadParams->m_pStatus.m_StatusString = _T("payment required");
				break;
		case 403:
				pThreadParams->m_pStatus.m_StatusString = _T("forbidden");
				break;
		case 404:
				pThreadParams->m_pStatus.m_StatusString = _T("not found");
				break;
		case 400:
				pThreadParams->m_pStatus.m_StatusString = _T("Unintelligble request");
				break;
		case 405:
				pThreadParams->m_pStatus.m_StatusString = _T("requested method not supported");
				break;
		case 500:
				pThreadParams->m_pStatus.m_StatusString = _T("Unknown server error");
				break;
		case 501:
				pThreadParams->m_pStatus.m_StatusString = _T("Not implemented on Server");
				break;
		case 502:
				pThreadParams->m_pStatus.m_StatusString = _T("Server temporarily overloaded,busy");
				break;
		case 503:
				pThreadParams->m_pStatus.m_StatusString = _T("Server capacity reached, busy");
				break;
		case ERROR_INTERNET_TIMEOUT:
				pThreadParams->m_pStatus.m_StatusString = _T("Connection timed out");
				break;
		case ERROR_INTERNET_INVALID_URL:
				pThreadParams->m_pStatus.m_StatusString = _T("URL is invalid");
				break;
		case ERROR_INTERNET_NAME_NOT_RESOLVED:
		case 12029: // this seems to be the error for unresolved host names
				pThreadParams->m_pStatus.m_StatusString = _T("Could not resolve host name. Check it, and try again");
				break;
		case ERROR_INTERNET_SHUTDOWN:
				pThreadParams->m_pStatus.m_StatusString = _T("Win32 internet functions have been shut down");
				break;
		case ERROR_INTERNET_CONNECTION_ABORTED:
				pThreadParams->m_pStatus.m_StatusString = _T("Connection was aborted prematurely");
				break;
		
		case 0:
		case 1:
		case 2:
		default:
				pThreadParams->m_pStatus.m_StatusString = _T("no connection");
				break;
		}
	}
	
	AddEntry(&pThreadParams->m_pStatus);
	if (m_bDone)	return 0;

		if(pThreadParams->m_hwndNotifyView != NULL)
			::SendMessage(pThreadParams->m_hwndNotifyView,WM_USER_CHECK_DONE, 0, (LPARAM) &pThreadParams->m_pStatus);

	
	if(dwRet != 200) return FALSE;

	
	return TRUE;
}
DWORD CSpiderThread::NewConnection(LPCTSTR ServerName,LPCTSTR strObject)
{

	if(ServerName  == NULL || strObject == NULL) return 0;
	DWORD dwRet =  HTTP_STATUS_OK;
   INTERNET_PORT nPort = INTERNET_DEFAULT_HTTP_PORT;

   try{
		m_pSession = new CMyInternetSession(ServerName,m_nThreadID);
		
		int ntimeOut = 30;
		/*
		The time-out value in milliseconds to use for Internet connection requests. 
		If a connection request takes longer than this timeout, the request is canceled.
		The default timeout is infinite. */
		m_pSession->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,1000* ntimeOut);
		
		/* The delay value in milliseconds to wait between connection retries.*/
		m_pSession->SetOption(INTERNET_OPTION_CONNECT_BACKOFF,1000);
		
		/* The retry count to use for Internet connection requests. If a connection 
		attempt still fails after the specified number of tries, the request is canceled.
		The default is five. */
		m_pSession->SetOption(INTERNET_OPTION_CONNECT_RETRIES,2);

     m_pSession->EnableStatusCallback(TRUE);
	m_pSession->m_strHttpSite.Format("%s%s",ServerName,strObject);


	}
	catch (CInternetException* pEx)
	{
		// catch errors from WinINet
		dwRet = pEx->m_dwError;
		m_pSession=NULL;
		pEx->Delete();
		return  dwRet;

	}

	try
	{

		m_pServer = m_pSession->GetHttpConnection(ServerName,nPort);
	}

	catch (CInternetException* pEx)
	{
		// catch errors from WinINet
		dwRet = pEx->m_dwError;
		m_pServer = NULL;
		pEx->Delete();
		CleanUp();
		return   dwRet;
	}

	m_strCurrentServer = ServerName;

	try
	{

		// This can never return NULL. The call may have failed, but it can
		// never be null.
		m_pFile = m_pServer->OpenRequest(_T("GET"),strObject,NULL, m_nThreadID, NULL, NULL, dwHttpRequestFlags);
		m_pFile->SendRequest();

	}

	catch (CInternetException* pEx)
	{
		// catch errors from WinINet
		dwRet = pEx->m_dwError;
		m_pFile = NULL;
		pEx->Delete();
		CleanUp();
		return dwRet;
	}

	return dwRet;
}


DWORD CSpiderThread::GetHttpStatus(LPCTSTR lpServerName,LPCTSTR strObject)
{

	if(lpServerName  == NULL || strObject == NULL)return 0;

	INTERNET_PORT nPort = INTERNET_DEFAULT_HTTP_PORT;
	DWORD dwRet =  1;

	if (m_pSession == NULL) return dwRet;

	m_pSession->m_strHttpSite.Format("%s%s",lpServerName,strObject);

	dwRet =  2;

	if(m_pFile != NULL)
	{
		m_pFile->Close();
		delete m_pFile;
		m_pFile=NULL;

	}
	
	if (m_bDone)	return 0;

	if (m_strCurrentServer != lpServerName)
	{
		// Picked a new server, close out connection and make a new one:
		if (m_pServer != NULL)
		{
			m_pServer->Close ();
			delete m_pServer;
			m_pServer = NULL;
		}
	}

	if (m_pServer == NULL)
	{
		try
		{

			m_pServer = m_pSession->GetHttpConnection(lpServerName,nPort);
		}

		catch (CInternetException* pEx)
		{
			// catch errors from WinINet
			//pEx->ReportError();
			dwRet = pEx->m_dwError;
			m_pServer = NULL;
			pEx->Delete();
			if(!CleanUp()) return FALSE;
			return dwRet;
		}
		if (m_bDone)	return 0;


		m_strCurrentServer = lpServerName;
	}


	if (m_bDone)
		return 0;
	if (m_pServer == NULL) return dwRet;
  
	try
	{

	// This can never return NULL. The call may have failed, but it can
	// never be null.
	m_pFile = m_pServer->OpenRequest(_T("GET"),strObject,NULL, m_nThreadID, NULL, NULL, dwHttpRequestFlags);
	m_pFile->SendRequest();
	
	}

	catch (CInternetException* pEx)
	{
		// catch errors from WinINet
		//pEx->ReportError();
		dwRet = pEx->m_dwError;
		m_pFile = NULL;
		pEx->Delete();
		if(!CleanUp()) return FALSE;
		if(dwRet == ERROR_INTERNET_TIMEOUT ) Sleep(1000);  // Connection timed out, try again on new connection
		dwRet = NewConnection(lpServerName,strObject);
		if(dwRet != HTTP_STATUS_OK) return dwRet;
	}

	if (m_bDone)	return 0;

	if(m_pFile != NULL)
		m_pFile->QueryInfoStatusCode(dwRet);

  return dwRet;


}

BOOL CSpiderThread::CheckAllURLs(LPCTSTR ServerName,ThreadParams *pThreadParams)

{    
	if(ServerName == NULL) return FALSE;
	if(pThreadParams->m_pszURL.IsEmpty()) return FALSE;

	CString strMainURL = pThreadParams->m_pszURL;

	CStringList list;
	POSITION pos=NULL;
	CString strObject,strSub;
	CString strServer,strURL,strTemp;
	DWORD dwServiceType;
	INTERNET_PORT nPort;
	LPCTSTR lpszText =     pThreadParams->m_Contents.LockBuffer();
	if(lpszText == NULL) return FALSE;

	if(!GetHref(lpszText,_T("href"),list))
		return FALSE;

	pThreadParams->m_Contents.UnlockBuffer();
	if (m_bDone)
		return 0;


	int count = GetServerList(pThreadParams->m_pszURL,list,strSub);
	
	int pdest;
	int i;
	
	CriticalSectionLock  plock;
	
	
	lURLCount += count;
	
	::SendMessage(pThreadParams->m_hwndNotifyProgress,
				WM_USER_URL_STATUS, 0, (LONG)lURLCount);
	
	if (m_bDone)	return 0;

	if(count>0)
	{


		for(i=0; i<count; i++)		
		{
			if( ( pos = list.FindIndex( i)) != NULL )
			{
				strObject = list.GetAt( pos );

				pdest = strObject.Find(ServerName);   // external link check
				
				if( pdest < 0 )
				    GetStatus(pThreadParams,HTTP_CHECK_URL,strObject);		// create new threads for each URL
				
				if (m_bDone)	return 0;
				if(lThreadCount >= MAXIMUM_WAIT_OBJECTS) 
						WaitForSingleObject(hConnection,INFINITE);
			
								
			}
		}

		for(i=0; i<count; i++)
		{
			if( ( pos = list.FindIndex( i)) != NULL )
			{
				strObject = list.GetAt( pos );

				pdest = strObject.Find(ServerName);  
				
				if( pdest > 0 )
				{
					if(AfxParseURL(strObject,dwServiceType,strServer,strURL,nPort))
					{
						if(!strURL.IsEmpty())
							CheckURL(ServerName,strURL,pThreadParams);  // check root links in the current file
					}
				}

				if (m_bDone)	return 0;

			}
		}

		if(pThreadParams->m_RootLinks)
		{
			for(i=0; i<count; i++)
			{
				if( ( pos = list.FindIndex( i)) != NULL )
				{
					strObject = list.GetAt( pos );
					pdest = strObject.Find(ServerName);  // get root files and check the links in those files 
					if ( pdest > 0)
					{
						pdest = strObject.Find(strSub);

						if(( pdest > 0 ) && (strMainURL.Compare(strObject)!=0))
							GetStatus(pThreadParams,HTTP_CHECK_URL_ROOT,strObject);  // create new thread

					}
					
					if (m_bDone)	return 0;

					if(lThreadCount >= MAXIMUM_WAIT_OBJECTS) 
						WaitForSingleObject(hConnection,INFINITE);
					

				}
			}
		}

	}

	return TRUE;
}




BOOL CSpiderThread::PrintLine(ThreadParams *pThreadParams,LPCSTR line)
{
	pThreadParams->m_string = line;
	::SendMessage(pThreadParams->m_hwndNotifyProgress,
				WM_USER_THREAD_PRINT, 0, (LPARAM)pThreadParams);

	return TRUE;
}

BOOL CSpiderThread::PrintFile(ThreadParams *pThreadParams,
							LPCSTR line)
{
	::SendMessage(pThreadParams->m_hwndNotifyProgress,
				WM_USER_THREAD_FILE, 0, (LPARAM)line);

	return TRUE;
}
BOOL CSpiderThread::PrintStatus(ThreadParams *pThreadParams,
							LPCSTR line)
{
	::SendMessage(pThreadParams->m_hwndNotifyProgress,
				WM_USER_THREAD_STATUS, 0, (LPARAM)line);

	return TRUE;
}

BOOL CSpiderThread::GetStatus(ThreadParams *pThreadParams,UINT ntype,LPCSTR line)
{
	pThreadParams->m_checkURLName.Format("%s",(LPCSTR)line);
	::SendMessage(pThreadParams->m_hwndNotifyProgress,
				WM_USER_THREAD_GETSTATUS, (UINT)ntype, (LPARAM)pThreadParams);

	return TRUE;
}

BOOL CSpiderThread::GetNewFile(ThreadParams *pThreadParams,UINT ntype,LPCSTR line)
{
	pThreadParams->m_checkURLName.Format("%s",(LPCSTR)line);
	::SendMessage(pThreadParams->m_hwndNotifyProgress,
				WM_USER_THREAD_GETNEWFILE, (UINT)ntype, (LPARAM)pThreadParams);

	return TRUE;
}

BOOL CSpiderThread::CleanUp()
{
	m_strCurrentServer.Empty();

	try
	{
		if(m_pFile != NULL)
		{	m_pFile->Close();
			delete m_pFile;
			m_pFile= NULL;
		}

		

		if (m_pServer!= NULL)
		{
			m_pServer->Close();
			delete m_pServer;
			m_pServer = NULL;
		
		}


		if (m_pSession != NULL)
		{
			m_pSession->Close();
			delete m_pSession;
			m_pSession = NULL;
		}
		
	}
	catch (CInternetException* pEx)
	{
		// catch errors from WinINet
		pEx->Delete();
		return FALSE;
	}
	
	if (m_bDone)	return 0;

	return TRUE;


}


BOOL CSpiderThread::ParseURL(ThreadParams *pThreadParams)
{
	BOOL bRet = FALSE;
	if(pThreadParams->m_pszURL.IsEmpty()) return bRet;

	LPCTSTR lpsz = pThreadParams->m_pszURL;
	if(lpsz  == NULL) return bRet;

	int nLen = lstrlen(lpsz);
	int i=0;
	while (nLen)
	{
		if( *lpsz == '/')	i++;
		++lpsz;
		nLen--;
		
	}
	if( i< 3) pThreadParams->m_pszURL += "/";


	try
	{
		AfxParseURL(pThreadParams->m_pszURL,pThreadParams->m_dwServiceType,pThreadParams->m_strServerName,pThreadParams->m_strObject,pThreadParams->m_nPort);

	}
	catch (CInternetException* pEx)
	{
		// catch errors from WinINet
		//pEx->ReportError();
		pEx->Delete();
		return bRet;
	}

	
	lpsz = pThreadParams->m_strObject;
	if(lpsz  == NULL) return bRet;
	bRet = TRUE;
	nLen = lstrlen(lpsz);

	BOOL bdot = FALSE;
	while (nLen)
	{
		if( *lpsz == '.') bdot = TRUE;
		++lpsz;
		nLen--;
		
	}
	if(pThreadParams->m_strObject.GetLength()-1 > 0)
	{
	if( bdot == FALSE && pThreadParams->m_strObject[pThreadParams->m_strObject.GetLength()-1] != '/')
		pThreadParams->m_strObject += "/";
	}

	return bRet;
}



int CSpiderThread::GetServerList(LPCTSTR pszURL,CStringList& list, CString& lpSub)
{
	if(pszURL  == NULL) return FALSE;

	CStringList Tlist;
	CString strObject,strTemp,str="";
	CString strSub,strServer,strURL,strServerName;
	POSITION pos=NULL;
	POSITION Tpos=NULL;
	LPCTSTR lpsz;
	int nLen;
	int count = 0;
	int pdest2;

	count = list.GetCount();
	int Tcount,i,ti,pdest,j,k;

	for(i=0; i<count; i++)
	{
		if( ( pos = list.FindIndex( i)) != NULL )
		{
			strObject = list.GetAt( pos );
			if(strObject.GetLength() -1 > 0)
			{
				k=0; j= 0;
				lpsz = strObject;
				if(lpsz  != NULL)
				{
					nLen = lstrlen(lpsz);
					while (nLen)
					{
						if( *lpsz == ':') k=j;
						++lpsz;
						nLen--;
						j++;
						
					}
				}
				if(k > 6)
				{
					if(strObject[k-4] == 'h' )		
					{
						strURL =  strObject.Right(strObject.GetLength() - k+4 );
						strObject = strURL;
					}
				}
				pdest = strObject.FindOneOf("# %");     // don't check   /index.html#new
				pdest2 = strObject.Find("ftp:");     // don't check   ftp://somefile.zip

				if(pdest<0 &&  pdest2 < 0  &&  strObject[0] != '.')   // don't check      ../somedirectory
				{
					Tcount = Tlist.GetCount();
					for(ti=0; ti<Tcount; ti++)
					{
						if( ( Tpos = Tlist.FindIndex( ti)) != NULL ) // remove duplicate URLs
						{
							strTemp = Tlist.GetAt( Tpos );
							if (strObject.Compare(strTemp) == 0)
								Tlist.RemoveAt(Tpos);
						}
					}
					if(!strObject.IsEmpty()) Tlist.AddTail(strObject);
				}
			}
		}
	}

	list.RemoveAll();

	Tcount = Tlist.GetCount();
	for(ti=0; ti<Tcount; ti++)		// get rid of /  in  /directory/somefile.html
	{
		if( ( Tpos = Tlist.FindIndex( ti)) != NULL )
		{
			strTemp = Tlist.GetAt( Tpos );
					
			
			if(strTemp.GetLength()-1 > 0)
			{
			
				if (strTemp[0] != '/' )
					str = strTemp;
				else
					str = strTemp.Right(strTemp.GetLength()-1);
				
				list.AddTail(str);
			}
		}
	}
		
	strURL = pszURL;
	strSub = "";
	strServer = "";
	strTemp = "";
	CString strDirectory="";
	

	lpsz = pszURL;
	if(lpsz  != NULL)
	{

		nLen = lstrlen(lpsz);
		i=0;
		while (nLen)
		{
			if( *lpsz == '/')	i++;
		
			++lpsz;
			nLen--;
			
		}
		if( i<=2) strURL += "/";
	}

	if(!strURL.IsEmpty()){
		pdest = strURL.Find("//");
		if (pdest >= 0)
		{
			strTemp = strURL.Mid(pdest +2);  // get rid of http://
		}

	}
	if(!strTemp.IsEmpty()){
		pdest = strTemp.Find( '/');
		if (pdest >= 0)
			strServer = strTemp.Left(pdest);  // find server name
	}
	if(!strURL.IsEmpty()){
		pdest = strURL.ReverseFind('/');  // get rid of URL Object
		if (pdest >= 0)
			strSub =  strURL.Left(pdest);
	}
	
	if(!strSub.IsEmpty()){				// find directory on server 
		pdest = strSub.Find(strServer);
		if (pdest >= 0)
			strDirectory =  strSub.Right(strSub.GetLength()-1 - pdest - strServer.GetLength());
	}
	strSub ="";
	if(strDirectory.GetLength()-1 > 0){
		
		if (strDirectory[0] != '/' )
				strSub += "/" + strDirectory;
		else strSub = strDirectory;

		if(strSub.GetLength()-1 > 0){

			if (strDirectory[strDirectory.GetLength()-1] != '/'  &&  strSub[strSub.GetLength()-1] != '/')
				strSub += "/" ;
		}
	}

	if(strSub.IsEmpty()) strSub = "/" ;

	lpSub = strSub;


	Tlist.RemoveAll();
	count = list.GetCount();

		for(i=0; i<count; i++)			//  add the server name and directory to the URL
		{
			if( ( pos = list.FindIndex( i)) != NULL )
			{
				strObject = list.GetAt( pos );
				if(!strObject.IsEmpty())
				{

					pdest = strObject.Find( _T("http"));
				
					if( pdest < 0 )
						strURL = 	_T("http://") + strServer + strSub + strObject;  // need to fix for https
					else
						strURL = strObject;

					Tlist.AddTail(strURL);
				}

			}
		}

	list.RemoveAll();
	count = Tlist.GetCount();			// rewrite the CStringList list 

		for(i=0; i<count; i++)
		{
			if( ( pos = Tlist.FindIndex( i)) != NULL )
			{
				strObject = Tlist.GetAt( pos );
				if(!strObject.IsEmpty())
				{

					pdest = strObject.Find("amp;");     // fix  /index.cgi?&amp;file=....#new
					if(pdest>0)
					{
						strURL = strObject.Left(pdest);
						strTemp =  strObject.Right(strObject.GetLength() - pdest - 1 -3);
						strObject = strURL + strTemp + '\0';

					}

					
					int npos = LookUpEntry((LPCTSTR)strObject);
					if(npos < 0  )
						list.AddTail(strObject);
				}

			}
		}


	return count;

}





