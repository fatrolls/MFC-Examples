// View.h : interface of the View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__17660EB3_0940_11D2_840B_0000B43382FE__INCLUDED_)
#define AFX_VIEW_H__17660EB3_0940_11D2_840B_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "HorizRuler.h"
#include "VertRuler.h"

#include "PropPage1.h"
#include "PropPage2.h"
#include "PropPage3.h"

class View : public CView
{
protected: // create from serialization only
	View();
	DECLARE_DYNCREATE(View)

// Attributes
public:
	Doc* GetDocument();

	CPropPage1	dlgSheet1;
	CPropPage2	dlgSheet2;
	CPropPage3	dlgSheet3;

	int	iGridStep, iDiv;
	bool bSizing;
	int  iSizingHit;
	CRect rcSizing;

	CRectTracker	* pTracker;
	int				  iType;
	CPoint			  ptTrack;

	int			iScx, iScy, iRx, iRy;

	CScrollBar	wndHBar, wndVBar;

	CHorizRuler	wndHRuler;
	CVertRuler	wndVRuler;

	COLORREF	cr3dFace;

	CPen * pGridPen1, * pGridPen2;

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DoSize(int cx, int cy);
	void ScaledPoint(CPoint & pt);
	void RealPoint(CPoint &pt);
	void RealPoint2(CPoint &pt);
	void FixRect(CRect &rc);
	void FixPoint(CPoint &pt);
	void FixPoint2(CPoint &pt);
	void SetPaperRect(const CRect &rc);
	virtual ~View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(View)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnToolArrow();
	afx_msg void OnUpdateToolArrow(CCmdUI* pCmdUI);
	afx_msg void OnToolBorder();
	afx_msg void OnUpdateToolBorder(CCmdUI* pCmdUI);
	afx_msg void OnToolCheck();
	afx_msg void OnUpdateToolCheck(CCmdUI* pCmdUI);
	afx_msg void OnToolEdit();
	afx_msg void OnUpdateToolEdit(CCmdUI* pCmdUI);
	afx_msg void OnToolImage();
	afx_msg void OnUpdateToolImage(CCmdUI* pCmdUI);
	afx_msg void OnToolLine();
	afx_msg void OnUpdateToolLine(CCmdUI* pCmdUI);
	afx_msg void OnToolRadio();
	afx_msg void OnUpdateToolRadio(CCmdUI* pCmdUI);
	afx_msg void OnToolRect();
	afx_msg void OnUpdateToolRect(CCmdUI* pCmdUI);
	afx_msg void OnToolSottoreport();
	afx_msg void OnUpdateToolSottoreport(CCmdUI* pCmdUI);
	afx_msg void OnToolStatic();
	afx_msg void OnUpdateToolStatic(CCmdUI* pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnToolVline();
	afx_msg void OnUpdateToolVline(CCmdUI* pCmdUI);
	afx_msg void OnToolHline();
	afx_msg void OnUpdateToolHline(CCmdUI* pCmdUI);
	afx_msg void OnPaperSize();
	afx_msg void OnProperty();
	afx_msg void OnUpdateProperty(CCmdUI* pCmdUI);
	afx_msg void OnGfxProperty();
	afx_msg void OnUpdateGfxProperty(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnAlignBottom();
	afx_msg void OnUpdateAlignBottom(CCmdUI* pCmdUI);
	afx_msg void OnAlignLeft();
	afx_msg void OnUpdateAlignLeft(CCmdUI* pCmdUI);
	afx_msg void OnAlignRight();
	afx_msg void OnUpdateAlignRight(CCmdUI* pCmdUI);
	afx_msg void OnAlignTop();
	afx_msg void OnUpdateAlignTop(CCmdUI* pCmdUI);
	afx_msg void OnSizeAll();
	afx_msg void OnUpdateSizeAll(CCmdUI* pCmdUI);
	afx_msg void OnSizeHorz();
	afx_msg void OnUpdateSizeHorz(CCmdUI* pCmdUI);
	afx_msg void OnSizeVert();
	afx_msg void OnUpdateSizeVert(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in View.cpp
inline Doc* View::GetDocument()
   { return (Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__17660EB3_0940_11D2_840B_0000B43382FE__INCLUDED_)
