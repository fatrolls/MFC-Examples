// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include <snmp.h>
#include "pingparmlist.h"
#include "inetthreadparms.h"
#include "PingThread.h"
#include "inetthread.h"

class CMainFrame : public CFrameWnd
{
public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	
	CPingThreadParmList m_PingThreadInfo;
	CInetThreadParms m_InetThreadInfo;
	CPingThread* m_pPingWorkerThread;
	CInetThread* m_pInetWorkerThread;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CString m_save_hostname;
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CListBox    m_wndListBox;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCommandsPing();
	afx_msg void OnCommandsNetstat();
	afx_msg void OnFileNew();
	afx_msg void OnUpdateCommandsPing(CCmdUI* pCmdUI);
	afx_msg void OnCommandsStopPing();
	afx_msg void OnUpdateCommandsStopPing(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandsNetstat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandsStopstat(CCmdUI* pCmdUI);
	afx_msg void OnCommandsStopstat();
	afx_msg void OnClose();
	//}}AFX_MSG
	LRESULT OnPingDone(WPARAM wParam,LPARAM lParam);
	LRESULT OnPingPrint(WPARAM wParam,LPARAM lParam);
	LRESULT OnInetDone(WPARAM wParam,LPARAM lParam);
	LRESULT OnInetPrint(WPARAM wParam,LPARAM lParam);
	LRESULT OnInetTabs(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()



private:
//	CCriticalSection m_CritWinLb;
	BOOL m_Ping_ButtEnabled;
	BOOL m_PingStop_ButtEnabled;
	BOOL m_Inet_ButtEnabled;
	BOOL m_InetStop_ButtEnabled;
};

/////////////////////////////////////////////////////////////////////////////
