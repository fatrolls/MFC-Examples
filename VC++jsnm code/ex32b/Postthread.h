// PostThread.h

#define WM_POSTCOMPLETE WM_USER + 6

extern CString g_strFile;
extern CString g_strServerName;
extern CString g_strParameters;

UINT PostThreadProc(LPVOID pParam);

