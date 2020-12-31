#ifndef __HooksClient_H__
#define __HooksClient_H__

#include "..\HooksServer\HooksServer.h"

/*
** Forward declarations
*/

class CHooksClientThread;
class CHooksClientWnd;

/* 
** ****************
** * CHooksClient *
** ****************
*/

class CHooksClient
{
public:
	// Constructor and destructor
	CHooksClient(BOOL = TRUE);
	virtual ~CHooksClient();

	// Information retrival
	virtual BOOL IsServerLoaded();
	
	// Client initialization
	virtual void InstallWindowHook(HWND);
	virtual void InstallSystemHook();

	// Client un-initialization
	virtual void UninstallWindowHook(HWND);
	virtual void UninstallSystemHook();

	// Client clean-up
	virtual void UninstallAllHooks();

	// Pure virtual function for clients to derive
	virtual void ProcessHookMessage(HWND hwnd, UINT nMessage, WPARAM wParam, LPARAM lParam) = 0;

protected:
	// Thread creation and destruction
	virtual void CreateClientThread();
	virtual void DestroyClientThread();
	// Hooks server DLL management
	virtual void LoadHooksServer();
	virtual void FreeHooksServer();
	// Hook installation helpers
	virtual BOOL GetGlobalHook(DWORD &);
	virtual void InstallHookEx(DWORD);
	virtual void UninstallHookEx(DWORD);

private:
	HINSTANCE m_hHooksServer;
	CMap<DWORD, DWORD &, DWORD, DWORD &> m_oHandles;
	CHooksClientThread *m_pClientThread;

	friend class CHooksClientThread;
};

/*
** **********************
** * CHooksClientThread *
** **********************
*/

class CHooksClientThread : public CWinThread
{
	DECLARE_DYNCREATE(CHooksClientThread)

public:
	CHooksClientThread(CHooksClient * = NULL);
	virtual ~CHooksClientThread();

	virtual void SetClient(CHooksClient *);
	virtual void PrepareToClose();

	void operator delete(void* p);

	//{{AFX_VIRTUAL(CHooksClientThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CHooksClientThread)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	static HANDLE m_hEventHooksClientThreadKilled;
	static HANDLE m_hEventHooksClientWindowCreated;

private:
	CHooksClient *m_pClient;
	CHooksClientWnd *m_pClientWnd;

	friend class CHooksClient;
};

/*
** *******************
** * CHooksClientWnd *
** *******************
*/

class CHooksClientWnd : public CWnd
{
public:
	CHooksClientWnd(CHooksClient * = NULL);
	virtual ~CHooksClientWnd();

	virtual void SetClient(CHooksClient *);

	virtual LRESULT OnFixedCopyData(WPARAM wParam, LPARAM lParam);
	
	//{{AFX_VIRTUAL(CHooksClientWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CHooksClientWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CHooksClient *m_pClient;
};


//{{AFX_INSERT_LOCATION}}

#endif

