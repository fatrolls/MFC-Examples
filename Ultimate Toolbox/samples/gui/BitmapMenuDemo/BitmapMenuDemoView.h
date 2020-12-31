// BitmapMenuDemoView.h : interface of the CBitmapMenuDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPMENUDEMOVIEW_H__1E4F0C10_88DA_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_BITMAPMENUDEMOVIEW_H__1E4F0C10_88DA_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CBitmapMenuDemoView : public CView
{
protected: // create from serialization only
	CBitmapMenuDemoView();
	DECLARE_DYNCREATE(CBitmapMenuDemoView)

// Attributes
public:
	CBitmapMenuDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapMenuDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBitmapMenuDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBitmapMenuDemoView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BitmapMenuDemoView.cpp
inline CBitmapMenuDemoDoc* CBitmapMenuDemoView::GetDocument()
   { return (CBitmapMenuDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPMENUDEMOVIEW_H__1E4F0C10_88DA_11D1_A3D5_0080C83F712F__INCLUDED_)
