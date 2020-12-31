// SpwView.h : interface of the CSpwView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPWVIEW_H__D3F202DA_FC3A_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_SPWVIEW_H__D3F202DA_FC3A_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSpwView : public CView
{
protected: // create from serialization only
	CSpwView();
	DECLARE_DYNCREATE(CSpwView)

// Attributes
public:
	CSpwDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpwView)
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
	virtual ~CSpwView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpwView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SpwView.cpp
inline CSpwDoc* CSpwView::GetDocument()
   { return (CSpwDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPWVIEW_H__D3F202DA_FC3A_11D0_9C9A_444553540000__INCLUDED_)
