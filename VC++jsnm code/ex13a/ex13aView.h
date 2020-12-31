// ex13aView.h : interface of the CEx13aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX13AVIEW_H__DFF9FC2B_7188_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
#define AFX_EX13AVIEW_H__DFF9FC2B_7188_11D0_8FDA_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx13aView : public CView
{
protected: // create from serialization only
	CEx13aView();
	DECLARE_DYNCREATE(CEx13aView)

// Attributes
public:
	CEx13aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx13aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx13aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx13aView)
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnDrawPattern();
	afx_msg void OnUpdateDrawPattern(CCmdUI* pCmdUI);
	afx_msg void OnDrawSquare();
	afx_msg void OnUpdateDrawSquare(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect m_rect;
	BOOL m_bCircle;
	BOOL m_bPattern;
};

#ifndef _DEBUG  // debug version in ex13aView.cpp
inline CEx13aDoc* CEx13aView::GetDocument()
   { return (CEx13aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX13AVIEW_H__DFF9FC2B_7188_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
