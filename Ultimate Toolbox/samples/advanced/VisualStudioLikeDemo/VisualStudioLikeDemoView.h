// VisualStudioLikeDemoView.h : interface of the CVisualStudioLikeDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALSTUDIOLIKEDEMOVIEW_H__73A06A43_E209_11D2_A7ED_525400DAF3CE__INCLUDED_)
#define AFX_VISUALSTUDIOLIKEDEMOVIEW_H__73A06A43_E209_11D2_A7ED_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVisualStudioLikeDemoView : public CEditView
{
protected: // create from serialization only
	CVisualStudioLikeDemoView();
	DECLARE_DYNCREATE(CVisualStudioLikeDemoView)

// Attributes
public:
	CVisualStudioLikeDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualStudioLikeDemoView)
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
	virtual ~CVisualStudioLikeDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisualStudioLikeDemoView)
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditFindInFiles(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VisualStudioLikeDemoView.cpp
inline CVisualStudioLikeDemoDoc* CVisualStudioLikeDemoView::GetDocument()
   { return (CVisualStudioLikeDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALSTUDIOLIKEDEMOVIEW_H__73A06A43_E209_11D2_A7ED_525400DAF3CE__INCLUDED_)
