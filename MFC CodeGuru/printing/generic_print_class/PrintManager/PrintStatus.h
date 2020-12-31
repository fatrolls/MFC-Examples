#if !defined(AFX_PRINTSTATUS_H__7EADD892_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
#define AFX_PRINTSTATUS_H__7EADD892_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrintStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintStatus dialog

class CPrintStatus : public CDialog
{
// Construction
public:
	CPrintStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintStatus)
	enum { IDD = IDD_PRINT_STATUS };
	CProgressCtrl	wndProg;
	CAnimateCtrl	wndAnima;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintStatus)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTSTATUS_H__7EADD892_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
