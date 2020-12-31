#if !defined(AFX_INPUTDIALOG_H__2C2725E5_00EC_11D1_8126_EC9404C10000__INCLUDED_)
#define AFX_INPUTDIALOG_H__2C2725E5_00EC_11D1_8126_EC9404C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InputDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputDialog dialog

class CInputDialog : public CDialog
{
// Construction
public:
	CInputDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputDialog)
	enum { IDD = IDD_INPUTDIALOG };
	CEdit	m_InputCtrl1;
	CEdit	m_InputCtrl2;
	CEdit	m_InputCtrl3;
	CEdit	m_InputCtrl4;
	CEdit	m_InputCtrl5;
	CEdit	m_InputCtrl6;
	CEdit	m_InputCtrl7;
	CEdit	m_InputCtrl8;
	CString	m_InputLine1;
	CString	m_InputLine2;
	CString	m_InputLine3;
	CString	m_InputLine4;
	CString	m_InputLine5;
	CString	m_InputLine6;
	CString	m_InputLine7;
	CString	m_InputLine8;
	CString	m_Prompt1;
	CString	m_Prompt2;
	CString	m_Prompt3;
	CString	m_Prompt4;
	CString	m_Prompt5;
	CString	m_Prompt6;
	CString	m_Prompt7;
	CString	m_Prompt8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputDialog)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDIALOG_H__2C2725E5_00EC_11D1_8126_EC9404C10000__INCLUDED_)
