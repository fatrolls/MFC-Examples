// TabViewsView.h : interface of the CTabViewsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABVIEWSVIEW_H__14C16332_675D_11D2_A753_525400DAF3CE__INCLUDED_)
#define AFX_TABVIEWSVIEW_H__14C16332_675D_11D2_A753_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//class CTabViewsView : public COXTabViewPage<CEditView>
class CTabViewsView : public CEditView
{
protected: // create from serialization only
	CTabViewsView();
	DECLARE_DYNCREATE(CTabViewsView)

// Attributes
public:
	CTabViewsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabViewsView)
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
	virtual ~CTabViewsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabViewsView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TabViewsView.cpp
inline CTabViewsDoc* CTabViewsView::GetDocument()
   { return (CTabViewsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABVIEWSVIEW_H__14C16332_675D_11D2_A753_525400DAF3CE__INCLUDED_)
