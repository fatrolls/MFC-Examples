// ex11bView.h : interface of the CEx11bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX11BVIEW_H__7D11C144_6C0B_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX11BVIEW_H__7D11C144_6C0B_11D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx11bView : public CView
{
protected: // create from serialization only
	CEx11bView();
	DECLARE_DYNCREATE(CEx11bView)

// Attributes
public:
	CEx11bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx11bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex11bView.cpp
inline CEx11bDoc* CEx11bView::GetDocument()
   { return (CEx11bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11BVIEW_H__7D11C144_6C0B_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
