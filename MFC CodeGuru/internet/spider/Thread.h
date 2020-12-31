// InetThread.h : header file
//
/******************************************************************
Pre-emptive Multithreading Web Spider

************************************************************/
#if !defined _Thread_H
#define _Thread_H

#include <afxtempl.h>

class CEntry : public CObject
{
public:

	CString m_URL;
	CString m_URLPage;
	CString m_StatusString;
	CString m_LastModified;
	CString m_ContentType;
	CString m_ContentLength;
	DWORD	m_Status;
	 
};


class CriticalSectionLock
{
public:
    CriticalSectionLock()
	{

		InitializeCriticalSection(&m_CritSect);
		EnterCriticalSection(&m_CritSect);

	}

    ~CriticalSectionLock()
	{
		LeaveCriticalSection(&m_CritSect);
		DeleteCriticalSection(&m_CritSect);
	}

private:
    CRITICAL_SECTION m_CritSect; 
};





extern 	UINT g_nEntries;
extern CArray<CEntry*, CEntry*> g_entry;

int LookUpEntry(LPCTSTR pszURL);
int AddEntry(URLStatus * lpEntry);

/////////////////////////////////////////////////////////////////////////////
// CSpiderThread thread


class CMyInternetSession : public CInternetSession
{
public:
	CMyInternetSession(LPCTSTR pstrAgent = NULL, DWORD dwContext = 1, DWORD dwAccessType = INTERNET_OPEN_TYPE_PRECONFIG, LPCTSTR pstrProxyName = NULL, LPCTSTR pstrProxyBypass = NULL, DWORD dwFlags = 0 ) 
		: CInternetSession(pstrAgent, dwContext, dwAccessType,
		pstrProxyName, pstrProxyBypass, dwFlags) 
		{ 	m_pMainWnd = NULL;	};

// Attributes
public:
	HWND m_pMainWnd;  // pointer to parent window
	CString m_strHttpSite;  // current URL 
// Operations
public:

	virtual void OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus,
		LPVOID lpvStatusInfomration, DWORD dwStatusInformationLen);

};


class CSpiderThread : public CWinThread
{
public:
	CSpiderThread(AFX_THREADPROC pfnThreadProc,ThreadParams *pThreadParams);     
	virtual ~CSpiderThread();

	static UINT ThreadFunc(LPVOID lparam);

	BOOL ThreadRun(ThreadParams *pThreadParams);
	BOOL m_bDone;

	void KillThread();

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CSpiderThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	
	CMyInternetSession* m_pSession;
	CHttpConnection* m_pServer;
	CHttpFile* m_pFile;
	CString m_strCurrentServer;
	BOOL CleanUp();
	BOOL InitServer();

	BOOL PrintLine(ThreadParams *pThreadParams,LPCSTR line);
	BOOL PrintFile(ThreadParams *pThreadParams,
				LPCSTR line);
	BOOL PrintStatus(ThreadParams *pThreadParams,
				LPCSTR line);
	BOOL GetStatus(ThreadParams *pThreadParams,UINT ntype,LPCSTR line);
	BOOL GetNewFile(ThreadParams *pThreadParams,UINT ntype,LPCSTR line);

	int GetServerList(LPCTSTR pszURL,CStringList& list,CString& lpSub);

	DWORD NewConnection(LPCTSTR ServerName,LPCTSTR strObject);
	BOOL ParseURL(ThreadParams *pThreadParams);


	DWORD GetHttpStatus(LPCTSTR lpServerName,LPCTSTR strObject);
	BOOL GetServerHeader(LPCTSTR ServerName,LPCTSTR strObject, ThreadParams *pThreadParams);

	BOOL GetHttpFile(LPCTSTR ServerName,LPCTSTR strObject,ThreadParams *pThreadParams,BOOL ViewFile =TRUE);

	BOOL CheckURL(LPCTSTR ServerName,LPCTSTR strObject, ThreadParams *pThreadParams);

	BOOL CheckAllURLs(LPCTSTR ServerName,ThreadParams *pThreadParams);



};

#endif

/////////////////////////////////////////////////////////////////////////////
