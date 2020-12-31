#if !defined(AFX_SKINNEDSCROLLBAR_H__A556371C_A48F_4FDE_B043_6ACC3E49C57A__INCLUDED_)
#define AFX_SKINNEDSCROLLBAR_H__A556371C_A48F_4FDE_B043_6ACC3E49C57A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinnedScrollBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkinnedScrollBar window

#include "SkinControl.h"
#include "SkinnedButton.h"

#define ID_SCROLLUP_BUTTON		1700
#define ID_SCROLLDOWN_BUTTON	1701
#define ID_SCROLL_BUTTON		1702

class CSkinnedScrollBar : public CWnd, public CSkinControl
{
// Construction
public:
	CSkinnedScrollBar();

// Attributes
public:

private:
	int m_nScrollButtonHeight;
	int m_nScrollButtonWidth;
	int m_nScrollButtonDisabledID;
	int m_nScrollButtonPressedID;
	int m_nScrollButtonNormalID;
	int m_nScrollButtonHoverID;

	int m_nScrollUpButtonHeight;
	int m_nScrollUpButtonWidth;
	int m_nScrollUpButtonDisabledID;
	int m_nScrollUpButtonPressedID;
	int m_nScrollUpButtonNormalID;
	int m_nScrollUpButtonHoverID;

	int m_nScrollDownButtonHeight;
	int m_nScrollDownButtonWidth;
	int m_nScrollDownButtonDisabledID;
	int m_nScrollDownButtonPressedID;
	int m_nScrollDownButtonNormalID;
	int m_nScrollDownButtonHoverID;
	
	BOOL m_bFindEdges;
	int UpdateMemoryDC();

	HRGN m_hRgn;

protected:
	int m_nMaxRange;
	int m_nMinRange;
	BOOL NotifyCommandToParent();
	CSkinnedButton *m_pcsbtnScrollButton;
	CSkinnedButton *m_pcsbtnScrollUpButton;
	CSkinnedButton *m_pcsbtnScrollDownButton;
	

// Operations
public:
	void GetRange(int &nMin, int &nMax);
	void SetRange(int nMin, int nMax, BOOL bRedraw = TRUE);
	int GetPos();
	int GetRangeMin();
	int GetRangeMax();
	int SetRangeMin(int nMin, BOOL bRedraw = TRUE);
	int SetRangeMax(int nMax, BOOL bRedraw = TRUE);
	void BltEx();

	BOOL CreateSkinControl(LPCTSTR lpszWindowName,
						LPRECT lpRect, 
						CWnd *pParentWnd, 
						UINT nControlID, 
						long lFlags=1L);

	void MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags=0L);

	void SetScrollButtonImageResource(int nNormalID=-1, int nPressedID=-1, int nHoverID=-1, int nDisabledID=-1);
	void SetScrollUpButtonImageResource(int nNormalID=-1, int nPressedID=-1, int nHoverID=-1, int nDisabledID=-1);
	void SetScrollDownButtonImageResource(int nNormalID=-1, int nPressedID=-1, int nHoverID=-1, int nDisabledID=-1);
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinnedScrollBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetPos(int nPos);
	virtual ~CSkinnedScrollBar();

	// Generated message map functions
protected:
	void MoveScrollButton(short nYPosition);
	//{{AFX_MSG(CSkinnedScrollBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINNEDSCROLLBAR_H__A556371C_A48F_4FDE_B043_6ACC3E49C57A__INCLUDED_)
