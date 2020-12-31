// dockdemoView.h : interface of the CDockdemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCKDEMOVIEW_H__10B67B9A_85D7_11D1_BAA0_006097DA5345__INCLUDED_)
#define AFX_DOCKDEMOVIEW_H__10B67B9A_85D7_11D1_BAA0_006097DA5345__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDockdemoView : public CView
{
protected: // create from serialization only
	CDockdemoView();
	DECLARE_DYNCREATE(CDockdemoView)

// Attributes
public:
	CDockdemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockdemoView)
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
	virtual ~CDockdemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDockdemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in dockdemoView.cpp
inline CDockdemoDoc* CDockdemoView::GetDocument()
   { return (CDockdemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCKDEMOVIEW_H__10B67B9A_85D7_11D1_BAA0_006097DA5345__INCLUDED_)
