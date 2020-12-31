#if !defined(AFX_PROPPAGE2_H__91A4B004_0AB6_11D2_8412_0000B43382FE__INCLUDED_)
#define AFX_PROPPAGE2_H__91A4B004_0AB6_11D2_8412_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPage2 dialog
class Doc;
class View;

class CPropPage2 : public CDialog
{
// Construction
public:
	CPropPage2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropPage2)
	enum { IDD = IDD_PROP_PAGE2 };
	CComboBox	wndCbId2;
	CComboBox	wndCbId;
	CComboBox	wndCbCond;
	CComboBox	wndCbVAlign;
	CComboBox	wndCbHAlign;
	CString	csCond;
	CString	csId;
	CString	csId2;
	//}}AFX_DATA

	Doc * pDoc;
	View * pView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropPage2)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelendokCbCond();
	afx_msg void OnSelendokCbHalign();
	afx_msg void OnSelendokCbId();
	afx_msg void OnSelendokCbId2();
	afx_msg void OnSelendokCbValign();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGE2_H__91A4B004_0AB6_11D2_8412_0000B43382FE__INCLUDED_)
