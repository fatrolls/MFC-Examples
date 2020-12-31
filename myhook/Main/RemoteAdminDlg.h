#if !defined(AFX_REMOTEADMINDLG_H__B2D2775C_5A54_47C7_9B68_0BCA9BDD244F__INCLUDED_)
#define AFX_REMOTEADMINDLG_H__B2D2775C_5A54_47C7_9B68_0BCA9BDD244F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RemoteAdminDlg.h : header file
//
#include "RootDlg.h"
#include "PPTooltip.h"
#include <afxtempl.h>
#include <TLHELP32.H>
#include "AFXCVIEW.H"

struct ProcessInfo;
//进程列表
typedef CTypedPtrList<CPtrList, ProcessInfo*>  ProcessInfoList;
//链接的主机Pending列表
typedef CTypedPtrList<CPtrList, CString*>      ConnectionPendingList;
class CRemoteAdministrator;
class CMachineInfo;
//已经链接上的主机列表
typedef CTypedPtrList<CPtrList, CMachineInfo*> MachineInfoList;

//服务名称
#define  REMOTE_ADMIN_SERVICE              _T("RemoteAdminService")
#define  SERVICENAME                       _T("RemoteAdminService")
#define  LONGSERVICENAME                   _T("RemoteAdminService")
//服务程序名称
#define  REMOTE_ADMIN_SERVICE_EXE          _T("RemoteAdminService.exe")
//服务管道名称
#define  REMOTE_ADMIN_SERVICE_PIPE         _T("RemoteAdminServivePipe")
//程序用的主Pipe
#define  REMOTE_ADMIN_PIPE                 _T("RemoteAdminPipe")
//获取远程主机进程列表的Pipe
#define  REMOTE_ADMIN_PROCESS_INFO_PIPE    _T("RemoteAdminProcessInfoPipe")
//在远程主机上执行程序的Pipe
#define  REMOTE_ADMIN_PROCESS_EXECUTE_PIPE _T("RemoteAdminProcessExecutePipe")
//杀远程主机进程的Pipe
#define  REMOTE_ADMIN_PROCESS_KILL_PIPE    _T("RemoteAdminProcessKillPipe")
//关机的Pipe
#define  REMOTE_ADMIN_SYS_SHUTDOWN_PIPE    _T("RemoteAdminSysShutDownPipe")

//访问系统桌面的权限
#define DESKTOP_ALL (DESKTOP_READOBJECTS | DESKTOP_CREATEWINDOW | DESKTOP_CREATEMENU |DESKTOP_HOOKCONTROL  \
                    | DESKTOP_JOURNALRECORD | DESKTOP_JOURNALPLAYBACK |DESKTOP_WRITEOBJECTS | DESKTOP_SWITCHDESKTOP \
					| STANDARD_RIGHTS_REQUIRED )
//访问windows操作系统的权限
#define WINSTA_ALL (WINSTA_ENUMDESKTOPS | WINSTA_READATTRIBUTES | WINSTA_ACCESSCLIPBOARD | WINSTA_CREATEDESKTOP \
                    | WINSTA_WRITEATTRIBUTES | WINSTA_ACCESSGLOBALATOMS | WINSTA_EXITWINDOWS | WINSTA_ENUMERATE \
					| WINSTA_READSCREEN | STANDARD_RIGHTS_REQUIRED )
//对文件的访问权限
#define GENERIC_ACCESS (GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE | GENERIC_ALL)

struct ThreadExitCommand 
{
    BOOL bThreadExit; 
};

struct ProcessInfo
{
	PROCESSENTRY32 ProcessEntry;
	SIZE_T nMemUsage;
};

struct SysShutDownInfo
{
    BOOL bShutDown;   // TRUE if you want to shutdown,FALSE if want to cancel shutdown
    BOOL bReboot;     // Reboot if TRUE, else HALT if FALSE
    UINT iTimeToShutDown; // Time given to user before shutdown in secs
};

struct ExecuteCommand
{
    TCHAR szProcessPath[_MAX_PATH]; // Process to start 
    TCHAR szUsername[_MAX_PATH];    // client to log on
    TCHAR szDomain[_MAX_PATH];      // domain of client's account
    TCHAR szPassword[_MAX_PATH];    // client's password
	TCHAR szCmdLine[_MAX_PATH];
};

class CMachineInfo : public CObject 
{
	DECLARE_SERIAL(CMachineInfo)
public:
	CMachineInfo();
	virtual ~CMachineInfo();
	
	ProcessInfoList* GetProcessInfoList();
	void SendEndThreadMessage();
	void ClosePipe();
	void RefreshProcessList(ProcessInfoList& lst);
	BOOL operator == (CMachineInfo& miMachineInfo);
	CMachineInfo& operator=(CMachineInfo &that);
	HANDLE GetSysShutdownPipe();
	HANDLE GetProcessKillPipe();
	HANDLE GetProcessExecutePipe();
	HANDLE GetProcessInfoPipe();
	HANDLE GetPipe();
	CString GetUserName();
	CString GetPassword();
	CString GetIP();
	void SetIP(CString strIP);
	void SetPassword(CString strPwd);
	void SetUserName(CString strUserName);
	void SetPipe(HANDLE handle);
	void SetProcessInfoPipe(HANDLE handle);
	void SetProcessExecutePipe(HANDLE handle);
	void SetProcessKillPipe(HANDLE handle);
	void SetSysShutDownPipe(HANDLE handle);
	virtual void Serialize(CArchive& ar);
protected:
	CString m_strIP;
	CString m_strPwd;
	CString m_strUserName;
    ProcessInfoList m_procInfoList;
	HANDLE m_hPipe;
	HANDLE m_hProcessInfoPipe;
	HANDLE m_hProcessExecutePipe;
	HANDLE m_hProcessKillPipe;
    HANDLE m_hRemoteAdminPipe;
    HANDLE m_hSysShutDownPipe;
public:
	
	CCriticalSection m_csProcessInfoList;
};

class CRemoteAdministrator  
{
public:
	CCriticalSection m_cs;

	CRemoteAdministrator();
	virtual ~CRemoteAdministrator();

	void DisconnectAHost(CString strIP);
	void DisconnectAllHosts();
	bool CopyServiceExeToHost(CString strIP);
	bool ConnectRemoteService(CString strIP, DWORD dwRetry, DWORD dwTimeout);
	bool IsMachineConnected(CString strIP);
	void AddPendingMachine(CString strIP);
	void AddConnectedMachine(CMachineInfo* pInfo);
	CString GetHostIPFromName(CString strName);
	CString GetHostName(CString strIP);
	void GetConnectHostIP(CStringArray& aHosts);
	int GetPendingConnectionCount();
	ProcessInfoList* GetProcessInfoList(CString strIP);
	HANDLE GetProcessInfoPipe(CString strIP);
	HANDLE GetProcessExecutePipe(CString strIP);
	HANDLE GetProcessKillPipe(CString strIP);
	HANDLE GetRemoteAdminPipe(CString strIP);
	HANDLE GetSysShutDownPipe(CString strIP);
	int GetConnectMachineCount();
	bool InstallAndStartService(CString strIP);
	bool IsConnectionPending(CString strIP);
	CMachineInfo* GetMachineInfo(CString strIP);
	bool RefreshProcessList(CString strIP, ProcessInfoList& lst);
	bool DeleteFromPendingList(CString strIP);
	BOOL EstablishAllConnections(CString strRemoteMachineIP, CString strUserName, CString strPwd, BOOL bEstablish);
	
protected:
	MachineInfoList m_ConnectedMachineList;
    ConnectionPendingList m_PendingConnectionList;
    HANDLE m_hCmdPipe; 

	BOOL EstablishAdminConnection(CString strRemoteMachineIP, CString strUserName, CString strPwd, BOOL bEstablish);
    BOOL EstablishIPCConnection(CString strRemoteMachineIP, CString strUserName, CString strPwd, BOOL bEstablish);
    BOOL EstablishConnection(CString strResource, CString strLogon, CString strRemoteMachineIP, CString strPwd, BOOL bEstablish);
};

/////////////////////////////////////////////////////////////////////////////
// CRemoteAdminDlg frame
#define WM_SET_STATUSBAR_TEXT WM_USER + 100

class CRemoteAdminFrame : public CFrameWnd
{
	friend class CAppSysIcon;
	friend class CMachineDoc;
	friend class CMainDlg;
	friend class CMachineView;
	DECLARE_DYNCREATE(CRemoteAdminFrame)
protected:
	CRemoteAdminFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void ShowToolTip(CRect rc, CString strTip);
    CPPToolTip* GetToolTip()
	{
         return &m_tooltip;
	}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteAdminFrame)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRemoteAdminFrame();

	// Generated message map functions
	//{{AFX_MSG(CRemoteAdminFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSettingsTimers();
	afx_msg void OnClose();
	afx_msg void OnSettingsWindowAlwaysontop();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnSetStatusBarText(WPARAM, LPARAM lParam);
	afx_msg void OnChangeRightViewStyle(UINT nID);
	DECLARE_MESSAGE_MAP()
protected:
	CPPToolTip      m_tooltip; 
	CSplitterWnd m_wndSplitter;
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
	CRect       m_rcSplitterWnd;
	CRect       m_rcStatusBar;
	BOOL m_bUpdateProcessList;
    UINT m_iUpdateProcessDelay;  // in milli secs
    UINT m_iShutdownDelay; // in milli secs
	bool m_bTopMost;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRemoteControlDlg dialog
class CMachineView;
class CRemoteControlDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CRemoteControlDlg)
// Construction
public:
	CRemoteControlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRemoteControlDlg)
	enum { IDD = IDD_REMOTEADMIN_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRemoteControlDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CRemoteAdminFrame* m_pFrame;
	CMachineView* m_pMachineView;
};
/////////////////////////////////////////////////////////////////////////////
// CMachineView view
const int MACHINE_IMAGE_ON_NETWORK = 0;
const int MACHINE_IMAGE            = 1;

class CRemoteAdminView;

class CMachineView : public CTreeView
{
	friend class CRemoteAdminView;

	DECLARE_DYNCREATE(CMachineView)
protected:
	CMachineView();           // protected constructor used by dynamic creation
	

// Attributes
public:

// Operations
public:
	BOOL AddMachine(CString strIP, CString strUserName, CString strPassword, CMachineDoc* pRemoteAdminDoc, CRemoteAdminView* pRemoteAdminView);
    HTREEITEM ShowNewMachine(CString strTextToBeShown, CMachineInfo* pMachineInfo);
	HTREEITEM GetTreeItemForText(CString strText);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMachineView)
	public:
	virtual BOOL DestroyWindow();
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMachineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	
	//{{AFX_MSG(CMachineView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnFileAddMachine();
	afx_msg void OnFileDeleteMachine();
	afx_msg void OnUpdateFileDeleteMachine(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnFileShutdownHalt();
	afx_msg void OnUpdateFileShutdownHalt(CCmdUI* pCmdUI);
	afx_msg void OnFileShutdownReboot();
	afx_msg void OnUpdateFileShutdownReboot(CCmdUI* pCmdUI);
	afx_msg void OnFileshutdownAbortshutdown();
	afx_msg void OnUpdateFileshutdownAbortshutdown(CCmdUI* pCmdUI);
	afx_msg void OnFileExecuteProcess();
	afx_msg void OnUpdateFileExecuteProcess(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileAddMachine(CCmdUI* pCmdUI);
	afx_msg void OnFileRefreshprocess();
	afx_msg void OnUpdateFileRefreshprocess(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	LPARAM GetSelectedItemParam();
	CString GetSelectText();
	void DeleteMachine(CString strIP, CRemoteAdminView* pAdminView);
	bool m_bMouseIn;
	HTREEITEM m_hMachineViewRoot;
	CImageList  m_imglst;
	CFont m_font;
private:
	void EnableContextMenu(CMenu* pMenu, bool bHost, int iShutDownMenuIndex = 2);
public:
	void SetMenuState(CMenu* pMenu, int iShutDownMenuIndex = 2);
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CMachineDoc document
class CProgressThread;
class CMachineView;
class CRemoteAdminView;

class CMachineDoc : public CDocument
{
	DECLARE_DYNCREATE(CMachineDoc)
protected:
	CMachineDoc();           // protected constructor used by dynamic creation
	BOOL ConnectToRemoteService(CString strIP, CString strUserName, CString strPwd, CMachineView* pMachineView, CRemoteAdminView* pRemoteAdminView);
	void DisconnectAndReconnectToRemoteService(CString strIP, CMachineView* pMachineView, CRemoteAdminView* pRemoteAdminView);
	void ReceiveProcessFromRemoteMachine(HANDLE hProcessInfoPipe, ProcessInfoList& pilProcessInfo, CString strIP, UINT iProcessCount, UINT iCounter);
// Attributes
public:

// Operations
public:
	void CreateVisualThread();
	static UINT ConnectToMachine(void* pParam);
	static UINT UpdateProcessListForAllMachines(LPVOID pParam);
   virtual ~CMachineDoc();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMachineDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void OnCloseDocument();
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	
	//{{AFX_MSG(CMachineDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL EstablishAllConnections(CString strRemoteMachineIP,  CString strUserName, CString strPwd, BOOL bEstablish, CMachineView* pMachineView, CRemoteAdminView* pRemoteAdminView);
	void SetProgressThread(CProgressThread* pThread);
	
	CRemoteAdministrator m_RemoteAdministrator;
    MachineInfoList* m_ConnectedHostList;
	CWinThread* m_pUpdateThread;
	CProgressThread* m_pVisualProgressThread;
};
/////////////////////////////////////////////////////////////////////////////
// CRemoteAdminView view

class CRemoteAdminView : public CListView
{
protected:
	CRemoteAdminView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRemoteAdminView)

// Attributes
public:

// Operations
public:
	void SetMenuState(CMenu* pMenu);
    void RefreshProcesses(CMachineDoc* pDoc, CString strRemoteMachineIP);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteAdminView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRemoteAdminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRemoteAdminView)
	afx_msg void OnFileKillProcess();
	afx_msg void OnUpdateFileKillProcess(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteallitems(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CString m_strProcessID;
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CRemoteControlTimeSettingDlg dialog

class CRemoteControlTimeSettingDlg : public CDialog
{
// Construction
public:
	CRemoteControlTimeSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRemoteControlTimeSettingDlg)
	enum { IDD = IDD_TIME_SETTINGS };
	UINT	m_nProcessRefreshTime;
	int		m_nShutDownDelayTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteControlTimeSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRemoteControlTimeSettingDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CRemoteControlDocTemplate : public CSingleDocTemplate
{
	DECLARE_DYNAMIC(CRemoteControlDocTemplate)
public:
	CRemoteControlDocTemplate();
};


/////////////////////////////////////////////////////////////////////////////
// CProgressThread thread

class CProgressThread : public CWinThread
{
	DECLARE_DYNCREATE(CProgressThread)
protected:
	CProgressThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void SetDocument(CMachineDoc* pDoc);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProgressThread();

	// Generated message map functions
	//{{AFX_MSG(CProgressThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	CMachineDoc* m_pDoc;
};

struct ConnectInfo
{
    CMachineDoc*      pDoc;
    CRemoteAdminView* pAdminView;
    CMachineView*     pMachineView;
    CString           strIP;
    CString           strPwd;
	CString           strUserName;
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CRemoteLogOnDlg dialog

class CRemoteLogOnDlg : public CDialog
{
// Construction
public:
	CRemoteLogOnDlg(CWnd* pParent = NULL);   // standard constructor

	DWORD m_dwIP;
// Dialog Data
	//{{AFX_DATA(CRemoteLogOnDlg)
	enum { IDD = IDD_REMOTE_LOGON };
	CIPAddressCtrl	m_wndIP;
	CString	m_strUserName;
	CString	m_strPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteLogOnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRemoteLogOnDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CExecuteRemoteProcessDlg dialog

class CExecuteRemoteProcessDlg : public CDialog
{
// Construction
public:
	CExecuteRemoteProcessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExecuteRemoteProcessDlg)
	enum { IDD = IDD_EXECUTE_PROCESS };
	CString	m_strCmdLine;
	CString	m_strDomain;
	CString	m_strPassword;
	CString	m_strExePath;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExecuteRemoteProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExecuteRemoteProcessDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

class CProgressDlg : public CDialog
{
// Construction
public:
	void SetDocument(CMachineDoc* pDoc);
	CProgressDlg(CWnd* pParent = NULL);   // standard constructor
   
// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESS_DLG };
	CProgressCtrl	m_wndProgress;
	CString	m_strPrompt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CMachineDoc* m_pDoc;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMOTEADMINDLG_H__B2D2775C_5A54_47C7_9B68_0BCA9BDD244F__INCLUDED_)
