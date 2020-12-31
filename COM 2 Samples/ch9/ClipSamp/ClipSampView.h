// ClipSampView.h : interface of the CClipSampView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPSAMPVIEW_H__1D48F68F_DFF7_11D2_9E78_00104B08CC22__INCLUDED_)
#define AFX_CLIPSAMPVIEW_H__1D48F68F_DFF7_11D2_9E78_00104B08CC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClipSampView : public CScrollView
{
protected: // create from serialization only
	CClipSampView();
	DECLARE_DYNCREATE(CClipSampView)

// Attributes
// for tracking
    CRectTracker m_tracker;
    CRect m_rectTracker;
// for drag-and-drop
    CRect m_rectTrackerEnter; // original logical coords
    COleDropTarget m_dropTarget;
    CSize m_dragOffset; // device coords

    CSize m_sizeTotal;  // document size

private:
    BOOL DoPasteDib(COleDataObject* pDataObject);
    COleDataSource* SaveDib();
    void MoveTrackRect(CPoint point);

public:
	CClipSampDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipSampView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnInitialUpdate(); // called first time after construct
    virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual void OnDragLeave();
    virtual BOOL OnDrop( COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClipSampView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClipSampView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
    afx_msg void OnEditCopy();
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
    afx_msg void OnEditCut();
    afx_msg void OnEditPaste();
    afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ClipSampView.cpp
inline CClipSampDoc* CClipSampView::GetDocument()
   { return (CClipSampDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPSAMPVIEW_H__1D48F68F_DFF7_11D2_9E78_00104B08CC22__INCLUDED_)
