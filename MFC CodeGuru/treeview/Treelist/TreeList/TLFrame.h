#if !defined(AFX_TLFRAME_H__99EB040C_4FA1_11D1_980A_004095E0DEFA__INCLUDED_)
#define AFX_TLFRAME_H__99EB040C_4FA1_11D1_980A_004095E0DEFA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TLFrame.h : header file
//

#include "NewTreeListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CTLFrame window

class CTLFrame : public CWnd
{
// Construction
public:
	CTLFrame();

// Attributes
public:
	CFont m_headerFont;
	CNewTreeListCtrl m_tree;
	CScrollBar m_horScrollBar;

// Operations
private:
	static LONG FAR PASCAL DummyWndProc(HWND, UINT, WPARAM, LPARAM);
	void Initialize();

public:
	static void RegisterClass();
	BOOL SubclassDlgItem(UINT nID, CWnd* parent); // use in CDialog/CFormView

	void SortTree(int nCol, BOOL bAscending, HTREEITEM hParent);
	void ResetScrollBar();

	BOOL VerticalScrollVisible();
	BOOL HorizontalScrollVisible();

	int StretchWidth(int m_nWidth, int m_nMeasure);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTLFrame)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTLFrame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTLFrame)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TLFRAME_H__99EB040C_4FA1_11D1_980A_004095E0DEFA__INCLUDED_)
