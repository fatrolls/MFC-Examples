#if !defined(AFX_SKINNEDBUTTON_H__62420D79_448B_43AA_BF22_32355FE79B70__INCLUDED_)
#define AFX_SKINNEDBUTTON_H__62420D79_448B_43AA_BF22_32355FE79B70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinnedButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkinnedButton window


#include "SkinControl.h"

class CSkinnedButton : public CWnd, public CSkinControl
{
// Construction
public:
	CSkinnedButton();
	BOOL m_bIsSliderParent;
	int UpdateMemoryDC();

// Attributes
public:

// Attributes
private:
	long m_lTextAlign;
	BOOL m_bFindEdges;
	void BltEx();
	
	BOOL NotifyCommandToParent();
	BOOL m_bIsDragging;
	long m_lButtonType;
	BOOL m_bPressed;

	HBITMAP m_hBitmap;
	HRGN m_hRgn, m_hRgnWindow;

// Operations
public:
	BOOL CreateSkinControl(LPCTSTR lpszWindowName, 
						LPRECT lpRect, 
						CWnd *pParentWnd, 
						UINT nControlID, 
						long lFlags=FL_BUTTON_TYPE_NORMAL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinnedButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	CDC* GetControlDC();
	long GetTextalignment();
	void SetTextAlignment(int nAlignment);
	void SetToggleButtonState(int nState);
	void SetShapedFlag(BOOL bShaped);
	void SetEnabled(BOOL bEnabled);
	void SetButtonText(LPTSTR lpszText);
	long GetButtonType();
	long SetButtonType(long lButtonType);
	void MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags=0);
	void MoveWindowEng(int nLeft, int nTop, BOOL bRedraw, long lFlags=0);
	virtual ~CSkinnedButton();

// Generated message map functions
protected:
	//{{AFX_MSG(CSkinnedButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINNEDBUTTON_H__62420D79_448B_43AA_BF22_32355FE79B70__INCLUDED_)
