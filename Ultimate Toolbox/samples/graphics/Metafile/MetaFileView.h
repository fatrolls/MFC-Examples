// MetaFileView.h : interface of the CMetaFileView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_METAFILEVIEW_H__D6580AF2_EA6C_11D1_8856_0080C83F712F__INCLUDED_)
#define AFX_METAFILEVIEW_H__D6580AF2_EA6C_11D1_8856_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMetaFileView : public CView
{
protected: // create from serialization only
	CMetaFileView();
	DECLARE_DYNCREATE(CMetaFileView)

// Attributes
public:
	CMetaFileDoc* GetDocument();

protected:
	BOOL m_bMaintainRatio;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetaFileView)
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
	virtual ~CMetaFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMetaFileView)
	afx_msg void OnViewRatio();
	afx_msg void OnUpdateViewRatio(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MetaFileView.cpp
inline CMetaFileDoc* CMetaFileView::GetDocument()
   { return (CMetaFileDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METAFILEVIEW_H__D6580AF2_EA6C_11D1_8856_0080C83F712F__INCLUDED_)
