// ex05bView.h : interface of the CEx05bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX05BVIEW_H__2AEF65F3_6C01_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX05BVIEW_H__2AEF65F3_6C01_11D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx05bView : public CView
{
private:
	void TraceMetrics(CDC* pDC);

protected: // create from serialization only
	CEx05bView();
	DECLARE_DYNCREATE(CEx05bView)

// Attributes
public:
	CEx05bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx05bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx05bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx05bView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex05bView.cpp
inline CEx05bDoc* CEx05bView::GetDocument()
   { return (CEx05bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX05BVIEW_H__2AEF65F3_6C01_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
