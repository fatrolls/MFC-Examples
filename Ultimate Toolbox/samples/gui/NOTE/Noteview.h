// noteView.h : interface of the CNoteView class
//
/////////////////////////////////////////////////////////////////////////////

#include "notewnd.h"

class CNoteView : public CView
{
private:
//	CNoteWnd* m_pNoteWnd;
	CArray<CNoteWnd*, CNoteWnd*> m_arrNoteWnd;

protected: // create from serialization only
	CNoteView();
	DECLARE_DYNCREATE(CNoteView)

// Attributes
public:
	CNoteDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNoteView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNoteView)
	afx_msg void OnStickyNoteShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in noteView.cpp
inline CNoteDoc* CNoteView::GetDocument()
   { return (CNoteDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
