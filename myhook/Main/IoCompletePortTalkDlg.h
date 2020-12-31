#if !defined(AFX_IOCOMPLETEPORTTALKDLG_H__45BDCD49_8CFF_485E_A48C_FB90D87F7750__INCLUDED_)
#define AFX_IOCOMPLETEPORTTALKDLG_H__45BDCD49_8CFF_485E_A48C_FB90D87F7750__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IoCompletePortTalkDlg.h : header file
//
#include "RootDlg.h"
#include "IoCompletePortSocket.h"
/////////////////////////////////////////////////////////////////////////////
// CIoCompletePortTalkDlg dialog

class CIoCompletePortTalkDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CIoCompletePortTalkDlg)
// Construction
public:
	CIoCompletePortTalkDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIoCompletePortTalkDlg)
	enum { IDD = IDD_IOCOMPLETEPORT_TALK_DLG };
	CListBox	m_lstUsers;
	CListBox	m_lstRecord;
	CEdit	m_edtSendMsg;
	CString	m_strSendMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIoCompletePortTalkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIoCompletePortTalkDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CIoCompletePortSocket* m_sSocket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOCOMPLETEPORTTALKDLG_H__45BDCD49_8CFF_485E_A48C_FB90D87F7750__INCLUDED_)
