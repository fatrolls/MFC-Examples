// ex04aView.h : interface of the CEx04aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX04AVIEW_H__B188BE41_6377_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX04AVIEW_H__B188BE41_6377_11D0_8FD4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx04aView : public CView
{
protected: // create from serialization only
	CEx04aView();
	DECLARE_DYNCREATE(CEx04aView)

// Attributes
public:
	CEx04aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx04aView)
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
	virtual ~CEx04aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx04aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nColor;
	CRect m_rectEllipse;
};

#ifndef _DEBUG  // debug version in ex04aView.cpp
inline CEx04aDoc* CEx04aView::GetDocument()
   { return (CEx04aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX04AVIEW_H__B188BE41_6377_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
