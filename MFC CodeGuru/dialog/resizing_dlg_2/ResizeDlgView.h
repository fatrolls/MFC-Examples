// ResizeDlgView.h : interface of the CResizeDlgView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIZEDLGVIEW_H__74620F6E_C16B_11D1_A051_0000B435810F__INCLUDED_)
#define AFX_RESIZEDLGVIEW_H__74620F6E_C16B_11D1_A051_0000B435810F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CResizeDlgView : public CView
{
protected: // create from serialization only
	CResizeDlgView();
	DECLARE_DYNCREATE(CResizeDlgView)

// Attributes
public:
	CResizeDlgDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeDlgView)
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
	virtual ~CResizeDlgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CResizeDlgView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ResizeDlgView.cpp
inline CResizeDlgDoc* CResizeDlgView::GetDocument()
   { return (CResizeDlgDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZEDLGVIEW_H__74620F6E_C16B_11D1_A051_0000B435810F__INCLUDED_)
