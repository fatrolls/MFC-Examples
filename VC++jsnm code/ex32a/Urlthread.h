// urlthread.h

extern CString g_strURL;
extern volatile BOOL g_bThreadStarted;
extern CEvent g_eKill;

extern UINT UrlThreadProc(LPVOID pParam);
extern void LogInternetException(LPVOID pParam, CInternetException* pe);
