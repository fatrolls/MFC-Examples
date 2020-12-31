// RfiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRfiDlg dialog

#ifndef _NTRAY_H__
#include "ntray.h"
#endif

#ifndef _LBCTRL_H
#include "lbctrl.h"
#endif

#ifndef _COMPLETESET_H
#include "CompleteSet.h"	// Added by ClassView
#endif

class CRfiDlg : public CDialog
{
// Construction
public:
	CRfiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
private:
	//{{AFX_DATA(CRfiDlg)
	enum { IDD = IDD_RFI_DIALOG };
	CListBoxCtrl	m_lcRepeaterList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRfiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRfiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddRepeaters();
	afx_msg void OnDeleteRepeaters();
	afx_msg void OnDblclkRepeaterList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickRepeaterList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExecuteQuery();
	afx_msg void OnClearQuery();
	afx_msg void OnEditRepeater();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowmain();
	afx_msg void OnHidemain();
	//}}AFX_MSG
	
	afx_msg LRESULT OnTrayNotify ( WPARAM, LPARAM );
	
	DECLARE_MESSAGE_MAP()

public:
protected:
private:
	HICON m_hIcon;
	CTrayNotifyIcon m_classTrayNotifyIcon;
	void OnUpdateShowmain ( CCmdUI* ); 
	void OnUpdateHidemain ( CCmdUI* ); 
	void LoadFilterList ( CString& );
	void LoadList ();
	void LoadSortList ( CString& );
	CImageList m_lgImageList;
	CImageList m_smImageList;
	CCompleteSet m_setComplete;
};
