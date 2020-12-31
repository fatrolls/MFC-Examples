#if !defined(AFX_MESSAGEDLG_H__3F95F853_296F_11D3_B75F_00203596449E__INCLUDED_)
#define AFX_MESSAGEDLG_H__3F95F853_296F_11D3_B75F_00203596449E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg dialog
#pragma warning ( disable : 4511 4512 )

class CMessageDlg : public CDialog
{
// Construction
public:
	CMessageDlg(CWnd* pParent, long lUID, CUT_IMAP4Client&);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessageDlg)
	enum { IDD = IDD_MESSAGE };
	CListBox	m_listHeaders;
	CComboBox	m_comboAttachments;
	CString	m_sMessageBody;
	//}}AFX_DATA

private:
	long m_lUID;
	CUT_IMAP4Client& m_imapc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	void LoadMessage();



// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMessageSaveAttachment();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 )

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEDLG_H__3F95F853_296F_11D3_B75F_00203596449E__INCLUDED_)
