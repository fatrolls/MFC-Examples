// utility.h
#define WM_CALLBACK WM_USER + 5
extern volatile int g_nConnection;
extern CString g_strServerName; // used by both winsock and wininet code
extern CString g_strServerIP; // used by both winsock and wininet code
extern CString g_strFile;
extern char g_pchStatus[];
extern HWND g_hMainWnd;
extern CCriticalSection g_csStatus;
extern CString g_strIPClient;
extern volatile UINT g_nPort;
extern CString g_strProxy;
extern BOOL g_bUseProxy;
extern volatile BOOL g_bListening;
extern CString g_strDirect;
extern CString g_strIPServer;
extern volatile UINT g_nPortServer;
extern CString g_strURL;
extern CString g_strDefault;

extern UINT ClientUrlThreadProc(LPVOID pParam);
extern UINT ServerThreadProc(LPVOID pParam);
extern UINT ClientWinInetThreadProc(LPVOID pParam);
extern UINT ClientSocketThreadProc(LPVOID pParam);

extern void LogInternetException(LPVOID pParam, CInternetException* pe);

class CCallbackInternetSession : public CInternetSession
{
public:
	CCallbackInternetSession( LPCTSTR pstrAgent = NULL, DWORD dwContext = 1,
		DWORD dwAccessType = PRE_CONFIG_INTERNET_ACCESS, LPCTSTR pstrProxyName = NULL,
		LPCTSTR pstrProxyBypass = NULL, DWORD dwFlags = 0 );
protected:
	virtual void OnStatusCallback(DWORD dwContext, DWORD dwInternalStatus,
		LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);
};
