#if !defined(SIZECBAR_H_INCLUDED)
#define SIZECBAR_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// sizecbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSizingControlBar control bar

class CSizingControlBar : public CControlBar
{
// Construction / destruction
public:
    CSizingControlBar();

// Attributes
public:
    BOOL IsHorz() const;

// Operations
public:

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSizingControlBar)
    public:
    virtual BOOL Create(CWnd* pParentWnd, CSize sizeDefault, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP);
    virtual CSize CalcFixedLayout( BOOL bStretch, BOOL bHorz );
    virtual CSize CalcDynamicLayout( int nLength, DWORD dwMode );
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CSizingControlBar();
    void StartTracking();
    void StopTracking(BOOL bAccept);
	void OnInvertTracker(const CRect& rect);

	//<raip
	BOOL ShowPane(BOOL bShow = TRUE);
	BOOL PaneIsVisible() {	return IsHorz() ? (m_sizeHorz.cy > 0) : (m_sizeVert.cx > 0); }
    // raip>

    // implementation helpers
    CPoint& ClientToWnd(CPoint& point);

protected:
    CSize       m_sizeMin;
    CSize       m_sizeHorz;
    CSize       m_sizeVert;
    CSize       m_sizeFloat;
	CSize		m_sizeStoreHorz;
	CSize		m_sizeStoreVert;
    CRect       m_rectBorder;
    CRect       m_rectTracker;
    UINT        m_nDockBarID;
    CPoint      m_ptOld;
    BOOL        m_bTracking;
    BOOL        m_bInRecalcNC;
    int         m_cxEdge;

// Generated message map functions
protected:
    //{{AFX_MSG(CSizingControlBar)
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnWindowPosChanging(LPWINDOWPOS lpwp);
    afx_msg void OnWindowPosChanged(LPWINDOWPOS lpwp);
    afx_msg void OnNcPaint();
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg UINT OnNcHitTest(CPoint point);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(SIZECBAR_H_INCLUDED)

