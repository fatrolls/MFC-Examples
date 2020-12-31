// ToolbarMenuDemoMDIView.h : interface of the CToolbarMenuDemoMDIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBARMENUDEMOMDIVIEW_H__38474A5E_9DC0_11D1_8BAD_0000B43382FE__INCLUDED_)
#define AFX_TOOLBARMENUDEMOMDIVIEW_H__38474A5E_9DC0_11D1_8BAD_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// COOLMENU SUPPORT
class CMenuSpawn;
// END COOLMENU SUPPORT


class CToolbarMenuDemoMDIView : public CEditView
{
protected: // create from serialization only
	CToolbarMenuDemoMDIView();
	DECLARE_DYNCREATE(CToolbarMenuDemoMDIView)

// Attributes
public:
	CToolbarMenuDemoMDIDoc* GetDocument();

// COOLMENU SUPPORT
	CMenuSpawn * pSpawn;
// END COOLMENU SUPPORT

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarMenuDemoMDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolbarMenuDemoMDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolbarMenuDemoMDIView)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ToolbarMenuDemoMDIView.cpp
inline CToolbarMenuDemoMDIDoc* CToolbarMenuDemoMDIView::GetDocument()
   { return (CToolbarMenuDemoMDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARMENUDEMOMDIVIEW_H__38474A5E_9DC0_11D1_8BAD_0000B43382FE__INCLUDED_)
