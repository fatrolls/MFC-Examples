// VarSplitView.h : interface of the CVarSplitView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARSPLITVIEW_H__233727CF_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
#define AFX_VARSPLITVIEW_H__233727CF_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CVarSplitView : public CView
{
protected: // create from serialization only
	CVarSplitView();
	DECLARE_DYNCREATE(CVarSplitView)

// Attributes
public:
	CVarSplitDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVarSplitView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVarSplitView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVarSplitView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VarSplitView.cpp
inline CVarSplitDoc* CVarSplitView::GetDocument()
   { return (CVarSplitDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARSPLITVIEW_H__233727CF_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
