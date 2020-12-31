// IE4ControlsDemoView.h : interface of the CIE4ControlsDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IE4CONTROLSDEMOVIEW_H__6754292C_A55F_11D1_B231_444553540000__INCLUDED_)
#define AFX_IE4CONTROLSDEMOVIEW_H__6754292C_A55F_11D1_B231_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CIE4ControlsDemoView : public CView
{
protected: // create from serialization only
	CIE4ControlsDemoView();
	DECLARE_DYNCREATE(CIE4ControlsDemoView)

// Attributes
public:
	CIE4ControlsDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIE4ControlsDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIE4ControlsDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIE4ControlsDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IE4ControlsDemoView.cpp
inline CIE4ControlsDemoDoc* CIE4ControlsDemoView::GetDocument()
   { return (CIE4ControlsDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IE4CONTROLSDEMOVIEW_H__6754292C_A55F_11D1_B231_444553540000__INCLUDED_)
