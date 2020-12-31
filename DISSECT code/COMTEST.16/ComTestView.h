// ComTestView.h : interface of the CComTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMTESTVIEW_H__AD9CD870_B103_11D0_968D_444553540000__INCLUDED_)
#define AFX_COMTESTVIEW_H__AD9CD870_B103_11D0_968D_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CComTestView : public CView
{
protected: // create from serialization only
	CComTestView();
	DECLARE_DYNCREATE(CComTestView)

// Attributes
public:
	CComTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComTestView)
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
	virtual ~CComTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CComTestView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ComTestView.cpp
inline CComTestDoc* CComTestView::GetDocument()
   { return (CComTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMTESTVIEW_H__AD9CD870_B103_11D0_968D_444553540000__INCLUDED_)
