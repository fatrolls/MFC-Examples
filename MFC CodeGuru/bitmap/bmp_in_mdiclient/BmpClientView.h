// BmpClientView.h : interface of the CBmpClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPCLIENTVIEW_H__BAF706BF_89CB_11D1_A17A_000000000000__INCLUDED_)
#define AFX_BMPCLIENTVIEW_H__BAF706BF_89CB_11D1_A17A_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CBmpClientView : public CView
{
protected: // create from serialization only
	CBmpClientView();
	DECLARE_DYNCREATE(CBmpClientView)

// Attributes
public:
	CBmpClientDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpClientView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBmpClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBmpClientView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BmpClientView.cpp
inline CBmpClientDoc* CBmpClientView::GetDocument()
   { return (CBmpClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPCLIENTVIEW_H__BAF706BF_89CB_11D1_A17A_000000000000__INCLUDED_)
