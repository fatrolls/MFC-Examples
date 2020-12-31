// WidgetView.h : interface of the CWidgetView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIDGETVIEW_H__02909A4D_3F5C_11D2_AC89_006008A8274D__INCLUDED_)
#define AFX_WIDGETVIEW_H__02909A4D_3F5C_11D2_AC89_006008A8274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagWIDGETINFO {
	int x;				// x coordinate of widget's upper left corner
	int y;				// y coordinate of widget's upper left corner
	int cx;				// Horizontal drag offset
	int cy;				// Vertical drag offset
	COLORREF color;		// The widget's color
} WIDGETINFO;

class CWidgetView : public CScrollView
{
protected: // create from serialization only
	CWidgetView();
	DECLARE_DYNCREATE(CWidgetView)

// Attributes
public:
	CWidgetDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWidgetView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWidgetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CWidget* m_pTempWidget;
	CSize m_offset;
	CPoint m_pointLastImage;
	CPoint m_pointLastMsg;
	int m_nSel;
	COleDropTarget m_oleDropTarget;

// Generated message map functions
protected:
	//{{AFX_MSG(CWidgetView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WidgetView.cpp
inline CWidgetDoc* CWidgetView::GetDocument()
   { return (CWidgetDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIDGETVIEW_H__02909A4D_3F5C_11D2_AC89_006008A8274D__INCLUDED_)
