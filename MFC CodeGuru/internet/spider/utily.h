// Utily.h : header file 
//

BOOL GetHref(LPCSTR szBuffer,LPCSTR szfind,CStringList& list);
BOOL GetEmail(LPCSTR szBuffer,LPCSTR szfind,CStringList& list);

BOOL FindHref(LPCTSTR lpszFind,LPCTSTR lpszString,CString& lpszResult,UINT nLen);
BOOL GetHTMLTags(LPCSTR szBuffer, CStringList& list);
BOOL GetHTMLText(LPCSTR szBuffer, CStringList& list);

