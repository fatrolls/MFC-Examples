// MetaFileView.h : interface of the CMetaFileView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_METAFILEVIEW_H__A1E5FA50_C54E_11D1_97F8_00000E7CC122__INCLUDED_)
#define AFX_METAFILEVIEW_H__A1E5FA50_C54E_11D1_97F8_00000E7CC122__INCLUDED_

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
	afx_msg BOOL OnAlignment(UINT nID);
	afx_msg void OnUpdateAlignment(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	METAALIGNMENT m_align;
};

#ifndef _DEBUG  // debug version in MetaFileView.cpp
inline CMetaFileDoc* CMetaFileView::GetDocument()
   { return (CMetaFileDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METAFILEVIEW_H__A1E5FA50_C54E_11D1_97F8_00000E7CC122__INCLUDED_)
