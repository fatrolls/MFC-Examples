// VistaView.h : interface of the CVistaView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISTAVIEW_H__3597FEAD_A70E_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_VISTAVIEW_H__3597FEAD_A70E_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVistaView : public CScrollView
{
protected: // create from serialization only
	CVistaView();
	DECLARE_DYNCREATE(CVistaView)

// Attributes
public:
	CVistaDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVistaView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVistaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVistaView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VistaView.cpp
inline CVistaDoc* CVistaView::GetDocument()
   { return (CVistaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISTAVIEW_H__3597FEAD_A70E_11D2_8E53_006008A82731__INCLUDED_)
