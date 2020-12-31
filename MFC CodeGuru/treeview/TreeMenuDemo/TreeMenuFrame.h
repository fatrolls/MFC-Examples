#if !defined(_TREEMENUFRAME_H_)
#define _TREEMENUFRAME_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TreeMenuFrame.h : header file
//

#include "TreeMenu.h"


/////////////////////////////////////////////////////////////////////////////
// CTreeMenuFrame window

#define IDC_CAPTION					(5100)
#define IDC_BEVEL					(5101)
#define IDC_BEVELL					(5102)
#define IDC_BEVELR					(5103)
#define IDC_LINE					(5104)
#define IDC_BTN_HIDE				(5105)
#define TMFN_HIDE					WM_USER + 1001
#define TMFN_CAPTIONDRAG			WM_USER + 1002
#define TREEMENUCTRL_CLASSNAME		_T("TreeMenuControl")



class CFlatBtn : public CButton
{
	// Construction

public:
	CFlatBtn();

	BOOL m_bLBtnDown;
	COLORREF m_clrHotText;
	
	//{{AFX_VIRTUAL(CFlatBtn)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL	

// Implementation
protected:
		COLORREF m_clrFace;
		COLORREF m_clrText;
		CString strText;
		CRect m_rect;

public:
	virtual ~CFlatBtn();
		// Generated message map functions

protected:
	//{{AFX_MSG(CFlatBtn)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



class CDragCaption : public CStatic {
public:
	DECLARE_DYNAMIC(CDragCaption)
	CDragCaption(LPCTSTR lpText = NULL, BOOL bDeleteOnDestroy=FALSE);
	~CDragCaption() { }

	
	BOOL SubclassDlgItem(UINT nID, CWnd* pParent) {
		return CStatic::SubclassDlgItem(nID, pParent);
	}

	COLORREF		m_color;

protected:
	CFont			m_font;			
	BOOL			m_bDeleteOnDestroy;	// delete object when window destroyed?

	virtual void PostNcDestroy();

	// message handlers
	DECLARE_MESSAGE_MAP()
	afx_msg UINT	OnNcHitTest(CPoint point);
	afx_msg HBRUSH 	CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
};



class CTreeMenuFrame : public CWnd
{
// Construction
public:
	CTreeMenuFrame();
	DECLARE_DYNCREATE(CTreeMenuFrame)

// Attributes
public:
	CDragCaption m_stcCaption;
	CFont		m_captionFont;
	CStatic		m_stcBevel;
	CStatic		m_stcBevelLeft;
	CStatic		m_stcBevelRight;
	CStatic     m_stcLine;
	CTreeMenu	m_tree;
	CFlatBtn	m_btn;


// Operations
private:
	void Initialize();

public:
	void RegisterClass();
	BOOL Create(const RECT& rect, CWnd* parent, UINT nID,
                DWORD dwStyle = WS_CHILD | WS_TABSTOP | WS_VISIBLE);

	BOOL SubclassDlgItem(UINT nID, CWnd* parent); // use in CDialog/CFormView

	CTreeMenu* GetTreeMenuCtrl() {	return &m_tree;}

	void Hide(BOOL hide = TRUE);

	void ShowSideBevels(BOOL SideBevels = TRUE) { bSideBevels = SideBevels;}

	void ShowFrameBevel(BOOL FrameBevel = TRUE) { bFrameBevel = FrameBevel;}

	void CalcLayout(BOOL bParent = FALSE);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeMenuFrame)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeMenuFrame();

	// Generated message map functions
protected:
	BOOL bSideBevels;
	BOOL bFrameBevel;
	CToolTipCtrl m_ToolTip;
	
	//{{AFX_MSG(CTreeMenuFrame)
	afx_msg void OnButtonHide();
	afx_msg void OnCaptionDrag();
    afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_TREEMENUFRAME_H_)
