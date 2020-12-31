// LookMaSDIView.h : interface of the CLookMaSDIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOOKMASDIVIEW_H__B5EC0800_CFAB_11D1_AE93_0004AC31E75C__INCLUDED_)
#define AFX_LOOKMASDIVIEW_H__B5EC0800_CFAB_11D1_AE93_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CLookMaSDIView : public CView
{
protected: // create from serialization only
	CLookMaSDIView();
	DECLARE_DYNCREATE(CLookMaSDIView)

// Attributes
public:
	CLookMaSDIDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLookMaSDIView)
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
	virtual ~CLookMaSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLookMaSDIView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LookMaSDIView.cpp
inline CLookMaSDIDoc* CLookMaSDIView::GetDocument()
   { return (CLookMaSDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOOKMASDIVIEW_H__B5EC0800_CFAB_11D1_AE93_0004AC31E75C__INCLUDED_)
