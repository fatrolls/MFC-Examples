// DaoMTDemoDlg.h : header file
//

#if !defined(AFX_DAOMTDEMODLG_H__CFCF52F8_AEA9_11D1_9811_00A024DFE858__INCLUDED_)
#define AFX_DAOMTDEMODLG_H__CFCF52F8_AEA9_11D1_9811_00A024DFE858__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDaoMTDemoDlg dialog


enum ThreadTypes  { ADD_THREAD, DELETING_THREAD };

class THREAD_DATA : public CObject
{
public:
	ThreadTypes	byType;
	HANDLE		hThread;
	HANDLE		hTerminateSignal;
	DWORD		nThreadId;
};



class CDaoMTDemoDlg : public CDialog
{
// Construction
public:
	CDaoMTDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDaoMTDemoDlg)
	enum { IDD = IDD_DAOMTDEMO_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoMTDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL	m_bAllowRemovingListItems;
	HICON	m_hIcon;
	CList<THREAD_DATA*, THREAD_DATA*> m_ThreadList;

	LRESULT OnUpdateStatus(WPARAM, LPARAM);
	LRESULT OnThreadTerminating(WPARAM, LPARAM);
	LRESULT OnKickIdle(WPARAM, LPARAM);

	afx_msg void OnUpdateOK(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAbortDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);

	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
							 
	afx_msg void OnUpdateRepairAndCompact(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCompactDb(CCmdUI* pCmdUI);
	// Generated message map functions
	//{{AFX_MSG(CDaoMTDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddStart();
	afx_msg void OnAddStop();
	afx_msg void OnAddStop2();
	afx_msg void OnDestroy();
	afx_msg void OnAddUseTransactions();
	afx_msg void OnClear();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAddClear();
	afx_msg void OnAbortDeletion();
	afx_msg void OnClose();
	afx_msg void OnRepairDb();
	afx_msg void OnCompactDb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAOMTDEMODLG_H__CFCF52F8_AEA9_11D1_9811_00A024DFE858__INCLUDED_)
