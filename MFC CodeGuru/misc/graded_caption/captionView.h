// captionView.h : interface of the CCaptionView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAPTIONVIEW_H__A536239E_6034_11D1_B4DF_006097608B1F__INCLUDED_)
#define AFX_CAPTIONVIEW_H__A536239E_6034_11D1_B4DF_006097608B1F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCaptionView : public CView
{
protected: // create from serialization only
	CCaptionView();
	DECLARE_DYNCREATE(CCaptionView)

// Attributes
public:
	CCaptionDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptionView)
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
	virtual ~CCaptionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCaptionView)
	afx_msg void OnSetModified();
	afx_msg void OnSettext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in captionView.cpp
inline CCaptionDoc* CCaptionView::GetDocument()
   { return (CCaptionDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTIONVIEW_H__A536239E_6034_11D1_B4DF_006097608B1F__INCLUDED_)
