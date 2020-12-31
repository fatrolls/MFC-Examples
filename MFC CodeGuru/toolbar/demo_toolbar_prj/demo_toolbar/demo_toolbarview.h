// demo_toolbarView.h : interface of the CDemo_toolbarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO_TOOLBARVIEW_H__6F831B2F_0710_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_DEMO_TOOLBARVIEW_H__6F831B2F_0710_11D2_AB9F_441100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDemo_toolbarView : public CEditView
{
protected: // create from serialization only
	CDemo_toolbarView();
	DECLARE_DYNCREATE(CDemo_toolbarView)

// Attributes
public:
	CDemo_toolbarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_toolbarView)
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
	virtual ~CDemo_toolbarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo_toolbarView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in demo_toolbarView.cpp
inline CDemo_toolbarDoc* CDemo_toolbarView::GetDocument()
   { return (CDemo_toolbarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_TOOLBARVIEW_H__6F831B2F_0710_11D2_AB9F_441100C10000__INCLUDED_)
