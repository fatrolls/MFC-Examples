// ZapMailDlg.h : header file
//

#if !defined(AFX_ZAPMAILDLG_H__333BA6D4_F593_11D1_870E_444553540001__INCLUDED_)
#define AFX_ZAPMAILDLG_H__333BA6D4_F593_11D1_870E_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CZapMailDlg dialog

class CZapMailDlg : public CDialog
{
// Construction
public:
	CZapMailDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CZapMailDlg)
	enum { IDD = IDD_ZAPMAIL_DIALOG };
	CEdit	m_ctlTo;
	CString	m_sBody;
	CString	m_sFrom;
	CString	m_sServer;
	CString	m_sSubject;
	CString	m_sTo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZapMailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZapMailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAttachments();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CStringArray m_Files;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZAPMAILDLG_H__333BA6D4_F593_11D1_870E_444553540001__INCLUDED_)
