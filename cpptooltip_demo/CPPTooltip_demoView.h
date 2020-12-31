// CPPTooltip_demoView.h : interface of the CPPTooltip_demoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPPTOOLTIP_DEMOVIEW_H__DB5A64D6_EC98_45F9_826E_6CBCE051176E__INCLUDED_)
#define AFX_CPPTOOLTIP_DEMOVIEW_H__DB5A64D6_EC98_45F9_826E_6CBCE051176E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PPTooltip.h"
#include "TrayIconPosition.h"

class CPPTooltip_demoView : public CScrollView
{
protected: // create from serialization only
	CPPToolTip m_tooltip;
	CPPToolTip m_traytip;
	CPPTooltip_demoView();
	DECLARE_DYNCREATE(CPPTooltip_demoView)

// Attributes
public:
	CPPTooltip_demoDoc* GetDocument();

// Operations
public:
	typedef struct structCITY_RECT
	{
		CRect rect;
		CString strText;
	} structCITY_RECT;
	typedef std::vector<structCITY_RECT>	arCity;
	arCity m_Cities;

	CBitmap m_map;
	CRect m_rect [5];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPTooltip_demoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPPTooltip_demoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void AddCity(int x1, int y1, int x2, int y2, CString strText);
	CButton m_pButton1;
	CButton m_pButton2;
	CButton m_pButton3;
	CButton m_pButton4;

	CTrayIconPosition m_tray_pos;


// Generated message map functions
protected:
	//{{AFX_MSG(CPPTooltip_demoView)
	afx_msg void OnDestroy();
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSubMenu);
    afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	afx_msg void OnShowIconInTray();
	afx_msg void OnRemoveIconFromTray();
	afx_msg void OnShowHelpTooltip();
	afx_msg void OnHideHelpTooltip();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CPPTooltip_demoView.cpp
inline CPPTooltip_demoDoc* CPPTooltip_demoView::GetDocument()
   { return (CPPTooltip_demoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPTOOLTIP_DEMOVIEW_H__DB5A64D6_EC98_45F9_826E_6CBCE051176E__INCLUDED_)
