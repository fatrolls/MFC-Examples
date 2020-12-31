// EZPrintView.h : interface of the CEZPrintView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EZPRINTVIEW_H__3A83FDED_A3E6_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_EZPRINTVIEW_H__3A83FDED_A3E6_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEZPrintView : public CView
{
protected: // create from serialization only
	CEZPrintView();
	DECLARE_DYNCREATE(CEZPrintView)

// Attributes
public:
	CEZPrintDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZPrintView)
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
	virtual ~CEZPrintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEZPrintView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in EZPrintView.cpp
inline CEZPrintDoc* CEZPrintView::GetDocument()
   { return (CEZPrintDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EZPRINTVIEW_H__3A83FDED_A3E6_11D2_8E53_006008A82731__INCLUDED_)
