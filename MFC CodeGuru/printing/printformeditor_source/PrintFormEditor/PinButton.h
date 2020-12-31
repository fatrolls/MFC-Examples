#if !defined(AFX_PINBUTTON_H__F90B2D04_C3FB_11D1_865D_000000000000__INCLUDED_)
#define AFX_PINBUTTON_H__F90B2D04_C3FB_11D1_865D_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PinButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPinButton window

class CPinButton : public CButton
{
// Construction
public:
	CPinButton();

// Attributes
public:
	CBitmap *	pBmp, * pCheckBmp, * pCheckBmpPressed;
	bool		bCheckMode;
	bool		bCheckStatus;
	CRect		rcImage;

	bool		bLBtnDown;
	bool		bHighlight;
	bool		bCloseLock;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPinButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool IsDlgButtonChecked();
	void EnableCheckMode(const bool bCheck = true);
	bool SetBitmap(int resId, COLORREF * rmp = NULL, const bool bIsCheck = false);
	bool SetBitmapCheckPress(int resId, COLORREF * rmp = NULL);
	virtual ~CPinButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPinButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PINBUTTON_H__F90B2D04_C3FB_11D1_865D_000000000000__INCLUDED_)
