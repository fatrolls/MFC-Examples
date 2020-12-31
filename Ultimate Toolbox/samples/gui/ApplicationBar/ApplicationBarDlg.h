// ApplicationBarDlg.h : header file
//

#if !defined(AFX_APPLICATIONBARDLG_H__3F58E76E_C82D_11D3_AC76_0050BAAB46B1__INCLUDED_)
#define AFX_APPLICATIONBARDLG_H__3F58E76E_C82D_11D3_AC76_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXAppBar.h"

/////////////////////////////////////////////////////////////////////////////
// CApplicationBarDlg dialog

class CApplicationBarDlg : public COXAppBar<CDialog>
{
// Construction
public:
	virtual void OnSetEdge(UINT nEdge);
	CMenu m_menu;
	void OnAutoHide();
	CApplicationBarDlg(CWnd* pParent = NULL);	// standard constructor

	virtual void DoPopupMenu();
	virtual ~CApplicationBarDlg();
// Dialog Data
	//{{AFX_DATA(CApplicationBarDlg)
	enum { IDD = IDD_APPLICATIONBAR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApplicationBarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CApplicationBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAlwaysontop();
	afx_msg void OnBottomdock();
	afx_msg void OnFloat();
	afx_msg void OnLeftdock();
	afx_msg void OnRightdock();
	afx_msg void OnTopdock();
	afx_msg void OnUnregister();
	afx_msg void OnRegister();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLICATIONBARDLG_H__3F58E76E_C82D_11D3_AC76_0050BAAB46B1__INCLUDED_)
