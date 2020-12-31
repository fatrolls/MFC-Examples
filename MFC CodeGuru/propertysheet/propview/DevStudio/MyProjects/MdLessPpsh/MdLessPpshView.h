// MdLessPpshView.h : interface of the CMdLessPpshView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDLESSPPSHVIEW_H__D1BCD704_F032_11D1_A7E2_E88B6FC70000__INCLUDED_)
#define AFX_MDLESSPPSHVIEW_H__D1BCD704_F032_11D1_A7E2_E88B6FC70000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMdLessPpshView : public CView
{
protected: // create from serialization only
	CMdLessPpshView();
	DECLARE_DYNCREATE(CMdLessPpshView)

// Attributes
public:
	CMdLessPpshDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdLessPpshView)
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
	virtual ~CMdLessPpshView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMdLessPpshView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MdLessPpshView.cpp
inline CMdLessPpshDoc* CMdLessPpshView::GetDocument()
   { return (CMdLessPpshDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDLESSPPSHVIEW_H__D1BCD704_F032_11D1_A7E2_E88B6FC70000__INCLUDED_)
