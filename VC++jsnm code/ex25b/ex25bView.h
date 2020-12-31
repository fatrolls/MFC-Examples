// ex25bView.h : interface of the CEx25bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25BVIEW_H__9C8ABB5F_98B3_11D0_85CF_9992596EDB70__INCLUDED_)
#define AFX_EX25BVIEW_H__9C8ABB5F_98B3_11D0_85CF_9992596EDB70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx25bView : public CScrollView
{
// for tracking
    CRectTracker m_tracker;
    CRect m_rectTracker;
// for drag-and-drop
    CRect m_rectTrackerEnter; // original logical coords
    COleDropTarget m_dropTarget;
    CSize m_dragOffset; // device coords

    CSize m_sizeTotal;  // document size
protected: // create from serialization only
	CEx25bView();
	DECLARE_DYNCREATE(CEx25bView)

// Attributes
public:
	CEx25bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual void OnDragLeave();
    virtual BOOL OnDrop( COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx25bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx25bView)
    afx_msg void OnEditCopy();
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
    afx_msg void OnEditCopyto();
    afx_msg void OnEditCut();
    afx_msg void OnEditPaste();
    afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
    afx_msg void OnEditPastefrom();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    BOOL DoPasteDib(COleDataObject* pDataObject);
    COleDataSource* SaveDib();
    void MoveTrackRect(CPoint point);
};

#ifndef _DEBUG  // debug version in ex25bView.cpp
inline CEx25bDoc* CEx25bView::GetDocument()
   { return (CEx25bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25BVIEW_H__9C8ABB5F_98B3_11D0_85CF_9992596EDB70__INCLUDED_)
