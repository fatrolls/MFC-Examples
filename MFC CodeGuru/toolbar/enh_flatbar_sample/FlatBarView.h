// FlatBarView.h : interface of the CFlatBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLATBARVIEW_H__1E0F37ED_4020_11D1_9FB1_444553540000__INCLUDED_)
#define AFX_FLATBARVIEW_H__1E0F37ED_4020_11D1_9FB1_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFlatBarView : public CView
{
protected: // create from serialization only
	CFlatBarView();
	DECLARE_DYNCREATE(CFlatBarView)

// Attributes
public:
	CFlatBarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatBarView)
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
	virtual ~CFlatBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlatBarView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FlatBarView.cpp
inline CFlatBarDoc* CFlatBarView::GetDocument()
   { return (CFlatBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATBARVIEW_H__1E0F37ED_4020_11D1_9FB1_444553540000__INCLUDED_)
