#if !defined(AFX_GROUPTALKDLG_H__616EF6C7_8E74_4B0C_861C_EFE675BB1AB8__INCLUDED_)
#define AFX_GROUPTALKDLG_H__616EF6C7_8E74_4B0C_861C_EFE675BB1AB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupTalkDlg.h : header file
//
#include "RootDlg.h"
#include "GroupTalk.h"

/////////////////////////////////////////////////////////////////////////////
// CGroupTalkDlg dialog

class CGroupTalkDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CGroupTalkDlg)
// Construction
public:
	CGroupTalkDlg(CWnd* pParent = NULL);   // standard constructor
    ~CGroupTalkDlg();
// Dialog Data
	//{{AFX_DATA(CGroupTalkDlg)
	enum { IDD = IDD_GROUP_TALK_DLG };
	CComboBox	m_cmbUsers;
	CEdit	m_edtSendMsg;
	CListBox	m_lstRecord;
	CString	m_strSysMsg;
	int		m_iType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupTalkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupTalkDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClear();
	afx_msg void OnSend();
	//}}AFX_MSG
	afx_msg LRESULT OnGroupTalk(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	CGroupTalk* m_pTalk;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPTALKDLG_H__616EF6C7_8E74_4B0C_861C_EFE675BB1AB8__INCLUDED_)
