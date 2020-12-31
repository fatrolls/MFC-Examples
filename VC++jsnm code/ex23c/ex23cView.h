// ex23cView.h : interface of the CEx23cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX23CVIEW_H__4F329AFB_5DF1_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX23CVIEW_H__4F329AFB_5DF1_11D0_848F_00400526305B__INCLUDED_

class CEx23cView : public CView
{
protected: // create from serialization only
	CEx23cView();
	DECLARE_DYNCREATE(CEx23cView)

// Attributes
public:
	CEx23cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx23cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx23cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx23cView)
	afx_msg void OnTestSpaceship();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex23cView.cpp
inline CEx23cDoc* CEx23cView::GetDocument()
   { return (CEx23cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX23CVIEW_H__4F329AFB_5DF1_11D0_848F_00400526305B__INCLUDED_)
