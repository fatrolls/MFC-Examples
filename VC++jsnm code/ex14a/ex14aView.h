// ex14aView.h : interface of the CEx14aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX14AVIEW_H__1B96E47B_771D_11D0_8FDE_00C04FC2A0C2__INCLUDED_)
#define AFX_EX14AVIEW_H__1B96E47B_771D_11D0_8FDE_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx14aView : public CView
{
protected: // create from serialization only
	CEx14aView();
	DECLARE_DYNCREATE(CEx14aView)

// Attributes
public:
	CEx14aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx14aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx14aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx14aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex14aView.cpp
inline CEx14aDoc* CEx14aView::GetDocument()
   { return (CEx14aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX14AVIEW_H__1B96E47B_771D_11D0_8FDE_00C04FC2A0C2__INCLUDED_)
