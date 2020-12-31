// CustomizeManagerView.h : interface of the CCustomizeManagerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMIZEMANAGERVIEW_H__F7F2B4D2_A8E3_4676_8DA3_45B0DAECB502__INCLUDED_)
#define AFX_CUSTOMIZEMANAGERVIEW_H__F7F2B4D2_A8E3_4676_8DA3_45B0DAECB502__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXSkinnedView.h"

class CCustomizeManagerView : public COXSkinnedView<CView>
{
protected: // create from serialization only
	CCustomizeManagerView();
	DECLARE_DYNCREATE(CCustomizeManagerView)

// Attributes
public:
	CCustomizeManagerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeManagerView)
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
	virtual ~CCustomizeManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomizeManagerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CustomizeManagerView.cpp
inline CCustomizeManagerDoc* CCustomizeManagerView::GetDocument()
   { return (CCustomizeManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZEMANAGERVIEW_H__F7F2B4D2_A8E3_4676_8DA3_45B0DAECB502__INCLUDED_)
