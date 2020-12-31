// SkinCtrlTestDlg.h : header file
//

#if !defined(AFX_SKINCTRLTESTDLG_H__CE0AB787_1D5C_4A32_B69A_7CD0D4C7FDA3__INCLUDED_)
#define AFX_SKINCTRLTESTDLG_H__CE0AB787_1D5C_4A32_B69A_7CD0D4C7FDA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\skinwindows\skinctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSkinCtrlTestDlg dialog

class CSkinCtrlTestDlg : public CDialog, protected ISkinCtrlRender
{
// Construction
public:
	CSkinCtrlTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSkinCtrlTestDlg)
	enum { IDD = IDD_SKINCTRLTEST_DIALOG };
	CButton	m_btn3;
	CButton	m_btn4;
	CProgressCtrl	m_progressV;
	CComboBox	m_combo;
	CProgressCtrl	m_progressH;
	CScrollBar	m_scrollbar;
	CListBox	m_listbox;
	CTabCtrl	m_tab;
	CTreeCtrl	m_tree;
	CListCtrl	m_listctrl;
	int		m_nSkinOption;
	CString	m_sEdit2;
	CString	m_sRichedit;
	//}}AFX_DATA
	COLORREF m_crBkgnd;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinCtrlTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSkinCtrlTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	afx_msg void OnChangeSkin();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	afx_msg void OnCheck3();
	afx_msg void OnSetcolor();
	afx_msg void OnPropsheet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// render callbacks
	virtual BOOL Draw3dEdge(CDC* pDC, LPRECT pRect, int nEdge, int nState, int nClipping = ISKCR_CLIPNONE);
	virtual BOOL Draw3dRect(CDC* pDC, LPRECT pRect, int nEdge, int nState, COLORREF crBkgnd, int nClipping = ISKCR_CLIPNONE);
	virtual BOOL Draw3dRoundEdge(CDC* pDC, LPRECT pRect, int nEdge, int nState);

	//	virtual BOOL DrawScrollbarButton(CDC* pDC, LPRECT pRect, int nState);
//	virtual BOOL DrawScrollbarButtonArrow(CDC* pDC, LPRECT pRect, int nBar, BOOL bBack, int nState);
//	virtual BOOL DrawSpinButton(CDC* pDC, LPRECT pRect, int nState);
//	virtual BOOL DrawSpinButtonArrow(CDC* pDC, LPRECT pRect, int nBar, BOOL bBack, int nState);

//	virtual BOOL DrawPushButton(CDC* pDC, LPRECT pRect, int nState, BOOL bClipLeft, BOOL bClipRight);
//	virtual BOOL DrawPushButtonText(CDC* pDC, LPRECT pRect, int nState);
//	virtual BOOL DrawRadioButton(CDC* pDC, LPRECT pRect, int nCheckState, int nState);
//	virtual BOOL DrawCheckButton(CDC* pDC, LPRECT pRect, int nCheckState, int nState);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINCTRLTESTDLG_H__CE0AB787_1D5C_4A32_B69A_7CD0D4C7FDA3__INCLUDED_)
