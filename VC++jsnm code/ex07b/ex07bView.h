// ex07bView.h : interface of the CEx07bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX07BVIEW_H__1096E32F_5958_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
#define AFX_EX07BVIEW_H__1096E32F_5958_11D0_8FCF_00C04FC2A0C2__INCLUDED_

class CEx07bView : public CView
{
protected: // create from serialization only
	CEx07bView();
	DECLARE_DYNCREATE(CEx07bView)

// Attributes
public:
	CEx07bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx07bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx07bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx07bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex07bView.cpp
inline CEx07bDoc* CEx07bView::GetDocument()
   { return (CEx07bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX07BVIEW_H__1096E32F_5958_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
