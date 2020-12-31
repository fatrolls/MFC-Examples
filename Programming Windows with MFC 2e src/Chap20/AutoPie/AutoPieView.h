// AutoPieView.h : interface of the CAutoPieView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOPIEVIEW_H__3B5BA314_3B72_11D2_AC82_006008A8274D__INCLUDED_)
#define AFX_AUTOPIEVIEW_H__3B5BA314_3B72_11D2_AC82_006008A8274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PI 3.1415926

class CAutoPieView : public CView
{
protected: // create from serialization only
	CAutoPieView();
	DECLARE_DYNCREATE(CAutoPieView)

// Attributes
public:
	CAutoPieDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPieView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoPieView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoPieView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AutoPieView.cpp
inline CAutoPieDoc* CAutoPieView::GetDocument()
   { return (CAutoPieDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPIEVIEW_H__3B5BA314_3B72_11D2_AC82_006008A8274D__INCLUDED_)
