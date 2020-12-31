// EditList1Dlg.h : header file
//

#if !defined(AFX_EDITLIST1DLG_H__6A3783BE_8679_11D1_A4E2_0020359647BF__INCLUDED_)
#define AFX_EDITLIST1DLG_H__6A3783BE_8679_11D1_A4E2_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "OXEditList.h"
/////////////////////////////////////////////////////////////////////////////
// CEditList1Dlg dialog

class CEditList1Dlg : public CDialog
{
// Construction
public:
	CEditList1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEditList1Dlg)
	enum { IDD = IDD_EDITLIST1_DIALOG };
	COXEditList	m_EditListCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditList1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	CString	m_EditListCont;

	CImageList m_ContextImageSmall;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEditList1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
			afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLIST1DLG_H__6A3783BE_8679_11D1_A4E2_0020359647BF__INCLUDED_)
