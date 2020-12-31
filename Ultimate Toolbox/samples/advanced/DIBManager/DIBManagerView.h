// DIBManagerView.h : interface of the CDIBManagerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBMANAGERVIEW_H__D2552D18_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_DIBMANAGERVIEW_H__D2552D18_7143_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXZoomVw.h" // Should be REMARKED IF USING OXClass.h in stdafx.h
//#include "OXScrollTipOwner.h"

class CDIBManagerView : public COXZoomView
{
protected: // create from serialization only
	CDIBManagerView();
	DECLARE_DYNCREATE(CDIBManagerView)

// Attributes
public:
	CDIBManagerDoc* GetDocument();

// Operations
public:
	void NormalToScaled(CRect* pRect);
	void NormalToScaled(CPoint* pPoint);
	void ScaledToNormal(CRect* pRect);
	void ScaledToNormal(CPoint* pPoint);
	void NormalToPrinted(CDC* pDC, CRect* pRect);
	void NormalToPrinted(CDC* pDC, CPoint* pPoint);
	void PrintedToNormal(CDC* pDC, CRect* pRect);
	void PrintedToNormal(CDC* pDC, CPoint* pPoint);

	void SetSmoothScrolling(BOOL bSmoothScrolling=TRUE) { 
		m_bSmoothScrolling=bSmoothScrolling; }

	BOOL IsSmoothScrolling() { return m_bSmoothScrolling; }

	void SetSmoothEnvironment(int nLineSlices=12, int nPageSlices=4,
		DWORD dwWaitingTime=10) 
	{ 
		m_nLineSlices=nLineSlices;
		m_nPageSlices=nPageSlices;
		m_dwWaitingTime=dwWaitingTime; 
	}
			
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBManagerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDIBManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	BOOL m_bSmoothScrolling;
	int m_nLineSlices;
	int m_nPageSlices;
	DWORD m_dwWaitingTime;


protected:
	void NotifyZoomChanged();
	UINT DoRealizePalette(BOOL bRedraw=TRUE, BOOL bForeground=TRUE);
	void PrintPage(CDC* pDC, CPrintInfo* pInfo);
	BOOL DrawDIB(CDC* pDC, CRect& rectDest, CRect& rectSrc);

// Generated message map functions
protected:
	//{{AFX_MSG(CDIBManagerView)
	afx_msg void OnViewZoomIn();
	afx_msg void OnUpdateViewZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomOut();
	afx_msg void OnUpdateViewZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomTo100();
	afx_msg void OnUpdateViewZoomTo100(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomToWindow();
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParameters(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnFileExport();
	afx_msg void OnUpdateFileProtected(CCmdUI* pCmdUI);
	afx_msg void OnFileProtected();
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnViewZoomLevelDlg();
	afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnPaletteChanged(CWnd*);
	afx_msg void OnViewImageInfo();
	afx_msg void OnViewResampleImage();
	//}}AFX_MSG
	afx_msg BOOL OnRollupMessage(CWnd* pWndRollup,UINT message,UINT rollupID);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DIBManagerView.cpp
inline CDIBManagerDoc* CDIBManagerView::GetDocument()
   { return (CDIBManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBMANAGERVIEW_H__D2552D18_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
