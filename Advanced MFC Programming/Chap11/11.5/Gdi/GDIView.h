#if !defined(AFX_GDIVIEW_H__1010F3AC_28F5_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIVIEW_H__1010F3AC_28F5_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIDoc;

class CGDIView : public CScrollView
{
protected:
	CBrush m_brGrid;
	CBitmap m_bmpDraw;
	CBitmap m_bmpBackup;
	CBitmap m_bmpSelBackup;
	CBitmap *m_pBmpOld;
	CDC m_dcMem;
	CRectTracker m_trackerSel;
	CPalette *m_pPalOld;
	CPoint m_ptMouseDown;
	CGDIView();
	DECLARE_DYNCREATE(CGDIView)

public:
	CGDIDoc* GetDocument();
	void LoadBitmap(HGLOBAL);
	void CleanUp();
	void UpdateScrollSizes();
	void DrawPoint(CPoint);
	void BackupCurrentBmp();
	void StretchCopySelection();
	void BackupSelection();
	void ResumeBackupBmp();
	void DrawLine(CPoint, CPoint);
	void ResetTracker();
	CPoint NormalizePtPosition(CPoint);
	CRect NormalizeTrackerRect(CRect);
	BOOL MouseWithinBitmap();

	//{{AFX_VIRTUAL(CGDIView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CGDIView)
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CGDIDoc* CGDIView::GetDocument()
   { return (CGDIDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIVIEW_H__1010F3AC_28F5_11D1_9C9A_444553540000__INCLUDED_)
