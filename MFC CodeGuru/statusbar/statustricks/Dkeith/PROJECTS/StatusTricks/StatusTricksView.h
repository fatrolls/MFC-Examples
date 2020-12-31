// StatusTricksView.h : interface of the CStatusTricksView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSTRICKSVIEW_H__9823BE38_4C57_11D1_B853_0020AF6F26D6__INCLUDED_)
#define AFX_STATUSTRICKSVIEW_H__9823BE38_4C57_11D1_B853_0020AF6F26D6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DkHeaderCtrl.h"

class CStatusTricksView : public CView
{
protected:
						 CStatusTricksView();
						 DECLARE_DYNCREATE(CStatusTricksView)

protected:
	CDkHeaderCtrl		 m_hdrCtrl;		// header control

public:
	CStatusTricksDoc	*GetDocument();
	virtual				~CStatusTricksView();
#ifdef _DEBUG
	virtual void		 AssertValid() const;
	virtual void		 Dump(CDumpContext& dc) const;
#endif

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusTricksView)
	public:
	virtual void		 OnDraw(CDC* pDC);
	virtual BOOL		 PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL		 OnPreparePrinting(CPrintInfo* pInfo);
	virtual void		 OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void		 OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CStatusTricksView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StatusTricksView.cpp
inline CStatusTricksDoc* CStatusTricksView::GetDocument()
   { return (CStatusTricksDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSTRICKSVIEW_H__9823BE38_4C57_11D1_B853_0020AF6F26D6__INCLUDED_)
