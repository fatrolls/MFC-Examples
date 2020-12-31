// ThreadParams.h   header file


typedef struct tagURLStatus
{
	CString m_URL;
	CString m_URLPage;
	CString m_StatusString;
	CString m_LastModified;
	CString m_ContentType;
	CString m_ContentLength;
	DWORD	m_Status;
}URLStatus, * PURLStatus;

typedef struct tagThreadParams
{
	HWND m_hwndNotifyProgress;
	HWND m_hwndNotifyView;
	CWinThread* m_pThread;
	CString m_pszURL;
	CString m_Contents;
	CString m_strServerName;
	CString m_strObject;
	CString m_checkURLName;
	CString m_string;
	DWORD m_dwServiceType;
	DWORD  m_threadID;
	DWORD m_Status;
	URLStatus m_pStatus;
	INTERNET_PORT  m_nPort;
	int m_type;
	BOOL m_RootLinks;

}ThreadParams; 



#define WM_USER_THREAD_DONE (WM_USER + 1)
#define WM_USER_THREAD_PRINT (WM_USER + 2)
#define WM_USER_THREAD_FILE (WM_USER + 3)
#define WM_USER_THREAD_STATUS (WM_USER + 4)
#define WM_USER_THREAD_GETSTATUS (WM_USER + 5)
#define WM_USER_THREAD_GETNEWFILE (WM_USER + 6)
#define WM_USER_THREAD_GETENTRY (WM_USER + 7)
#define WM_USER_VIEW_UPDATE (WM_USER + 8)
#define WM_USER_CHECK_DONE (WM_USER + 9)
#define WM_USER_LIST (WM_USER + 10)
#define WM_USER_SERVER_STATUS (WM_USER + 12)
#define WM_USER_URL_STATUS (WM_USER + 14)



#define HTTP_GET_FILE			0
#define HTTP_CHECK_URL_ROOT		1
#define HTTP_CHECK_URL			2
#define HTTP_GET_HEADER			3
#define HTTP_GET_ENTRY			4

