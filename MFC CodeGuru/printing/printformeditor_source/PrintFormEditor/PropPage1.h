#if !defined(AFX_PROPPAGE1_H__91A4B003_0AB6_11D2_8412_0000B43382FE__INCLUDED_)
#define AFX_PROPPAGE1_H__91A4B003_0AB6_11D2_8412_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPage1 dialog
class Doc;
class View;

class CPropPage1 : public CDialog
{
// Construction
public:
	CPropPage1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropPage1)
	enum { IDD = IDD_PROP_PAGE1 };
	CEdit	wndEditHeight;
	CEdit	wndEditY;
	CEdit	wndEditWidth;
	CEdit	wndEditX;
	BOOL	bBold;
	BOOL	bItalic;
	BOOL	bUnderline;
	CString	csFontName;
	CString	csFontSize;
	//}}AFX_DATA

	Doc * pDoc;
	View * pView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropPage1)
	afx_msg void OnBtFont();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChkBold();
	afx_msg void OnChkItalic();
	afx_msg void OnChkUnderline();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGE1_H__91A4B003_0AB6_11D2_8412_0000B43382FE__INCLUDED_)
