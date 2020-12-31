// clipexamView.h : interface of the CClipExamView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPEXAMVIEW_H__DBF687F5_868E_11D1_B99D_00A0C9763A0A__INCLUDED_)
#define AFX_CLIPEXAMVIEW_H__DBF687F5_868E_11D1_B99D_00A0C9763A0A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CClipExamView : public CView
{
protected: // create from serialization only
	CClipExamView();
	DECLARE_DYNCREATE(CClipExamView)

// Attributes
public:
	CClipExamDoc* GetDocument();
	COleDropTarget	m_DropTarget;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipExamView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClipExamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClipExamView)
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in clipexamView.cpp
inline CClipExamDoc* CClipExamView::GetDocument()
   { return (CClipExamDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPEXAMVIEW_H__DBF687F5_868E_11D1_B99D_00A0C9763A0A__INCLUDED_)
