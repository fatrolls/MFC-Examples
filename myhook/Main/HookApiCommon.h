#ifndef __HOOKAPI_COMMON_H__
#define __HOOKAPI_COMMON_H__

/////////////////////////////////////////////////////////////////////////////
// CShareMemory command target
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class CShareMemory : public CCmdTarget
{
	DECLARE_DYNCREATE(CShareMemory)
public:
	CShareMemory(const char * pszMapName = NULL, int nFileSize = 0, BOOL bServer = TRUE);           // protected constructor used by dynamic creation
    virtual ~CShareMemory();
// Attributes


// Operations
public:
	LPVOID GetBuffer() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShareMemory)
	//}}AFX_VIRTUAL

// Implementation
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CShareMemory)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	LPVOID m_pBuffer;
	HANDLE m_hMap;
};

struct CMessageData
{
	DWORD dwThreadID;
	SOCKET socket;
	char szExeName[MAX_PATH];
	int nDataLen;
	TCHAR* data()
	{
		return (TCHAR*)(this+1);
	}
};

enum HOOK_MESSAGE
{
	HM_RECEIVE = WM_USER + 1000,
	HM_SEND	
};

#endif