#if !defined(AFX_EDITDLG_H__EE03A544_57BC_47A5_9368_753A107949C1__INCLUDED_)
#define AFX_EDITDLG_H__EE03A544_57BC_47A5_9368_753A107949C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : header file
//

#include "..\..\Common\UIClasses\SkinnedEdit.h"

#define ID_EDIT	6800
/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog

class CEditDlg : public CDialog
{
// Construction
public:
	void SetEditControlType(UINT nType);
	CEditDlg(CWnd* pParent = NULL);   // standard constructor
	void SetEditControlProperties(CSkinnedEdit& SkinnedEditControl);

// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_EDIT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_csEditText;
	CSkinnedEdit m_Edit;

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__EE03A544_57BC_47A5_9368_753A107949C1__INCLUDED_)
