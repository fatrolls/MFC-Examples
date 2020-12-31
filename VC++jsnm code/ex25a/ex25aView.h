// ex25aView.h : interface of the CEx25aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25AVIEW_H__C4B91635_98AE_11D0_85CF_9992596EDB70__INCLUDED_)
#define AFX_EX25AVIEW_H__C4B91635_98AE_11D0_85CF_9992596EDB70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define WM_VIEWPALETTECHANGED	WM_USER + 5

class CEx25aView : public CScrollView
{
    // for tracking
    CRectTracker m_tracker;
    CRect m_rectTracker; // logical coordinates
    CSize m_sizeTotal;   // document size
protected: // Create from serialization only
	CEx25aView();
	DECLARE_DYNCREATE(CEx25aView)

// Attributes
public:
	CEx25aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx25aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// generated message map functions
protected:
	//{{AFX_MSG(CEx25aView)
    afx_msg void OnEditCopy();
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
    afx_msg void OnEditCopyto();
    afx_msg void OnEditCut();
    afx_msg void OnEditPaste();
    afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
    afx_msg void OnEditPastefrom();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LONG OnViewPaletteChanged(UINT wParam, LONG lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    BOOL DoPasteDib(COleDataObject* pDataObject);
    COleDataSource* SaveDib();
};

#ifndef _DEBUG  // debug version in ex25aView.cpp
inline CEx25aDoc* CEx25aView::GetDocument()
    { return (CEx25aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25AVIEW_H__C4B91635_98AE_11D0_85CF_9992596EDB70__INCLUDED_)
