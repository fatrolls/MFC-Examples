#if !defined(AFX_TURBODRAGDLG_H__169E9590_E62E_4412_B717_1BAE7E0DFCFD__INCLUDED_)
#define AFX_TURBODRAGDLG_H__169E9590_E62E_4412_B717_1BAE7E0DFCFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TurboDragDlg.h : header file
//

#include "MyTreeListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CTurboDragDlg dialog

class CTurboDragDlg : public CDialog
{
// Construction
public:
	CTurboDragDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTurboDragDlg)
	enum { IDD = IDD_TURBODRAG_DIALOG };
	//}}AFX_DATA
	CImageList	m_ImageList;
	CMyTreeListCtrl	m_tree1;
	CMyTreeListCtrl m_tree2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTurboDragDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTurboDragDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TURBODRAGDLG_H__169E9590_E62E_4412_B717_1BAE7E0DFCFD__INCLUDED_)
