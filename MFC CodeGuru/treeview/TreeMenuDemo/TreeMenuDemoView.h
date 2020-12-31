// TreeMenuDemoView.h : interface of the CTreeMenuDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREEMENUDEMOVIEW_H__96C46D90_E5C6_11D1_92D4_0080C882060B__INCLUDED_)
#define AFX_TREEMENUDEMOVIEW_H__96C46D90_E5C6_11D1_92D4_0080C882060B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTreeMenuDemoView : public CView
{
protected: // create from serialization only
	CTreeMenuDemoView();
	DECLARE_DYNCREATE(CTreeMenuDemoView)

// Attributes
public:
	CTreeMenuDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeMenuDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeMenuDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTreeMenuDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TreeMenuDemoView.cpp
inline CTreeMenuDemoDoc* CTreeMenuDemoView::GetDocument()
   { return (CTreeMenuDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEMENUDEMOVIEW_H__96C46D90_E5C6_11D1_92D4_0080C882060B__INCLUDED_)
