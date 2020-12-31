// dragView.h : interface of the CDragView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAGVIEW_H__36079C8E_1AF5_11D1_A856_0060977B4134__INCLUDED_)
#define AFX_DRAGVIEW_H__36079C8E_1AF5_11D1_A856_0060977B4134__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDragView : public CTreeView
{
protected: // create from serialization only
	CDragView();
	DECLARE_DYNCREATE(CDragView)

// Attributes
public:
	CDragDoc* GetDocument();

protected:
	CImageList* m_pDragImage;
	HTREEITEM   m_htiDrag, m_htiDrop, m_htiOldDrop;
	bool        m_bLDragging;
	UINT		m_idTimer;

// Operations
public:
	HTREEITEM CopyBranch( HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST );
	HTREEITEM CopyItem( HTREEITEM hti, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDragView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDragView)
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in dragView.cpp
inline CDragDoc* CDragView::GetDocument()
   { return (CDragDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGVIEW_H__36079C8E_1AF5_11D1_A856_0060977B4134__INCLUDED_)
