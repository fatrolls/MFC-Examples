// SkinnedSliderCtrl.h: interface for the CSkinnedSliderCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINNEDSLIDERCTRL_H__6F04BA14_89E7_4ADA_840E_7D3E961E5191__INCLUDED_)
#define AFX_SKINNEDSLIDERCTRL_H__6F04BA14_89E7_4ADA_840E_7D3E961E5191__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinControl.h"
#include "SkinnedButton.h"
#include "..\\GlobalConstants.h"

#define ID_SLIDER_BUTTON	1800

class CSkinnedSliderCtrl : 
	public CWnd, 
	public CSkinControl  
{
//Operations
private:
	HBITMAP m_hBitmap;
	long m_lPreviousPos;
	int m_nTicksLength;
	COLORREF m_crTicksForegroundColor;
	BOOL m_bDisplayTicks;
	int m_nSliderButtonHeight;
	int m_nSliderButtonWidth;
	int m_nSliderButtonDisabledID;
	int m_nSliderButtonPressedID;
	int m_nSliderButtonNormalID;
	int m_nSliderButtonHoverID;
	BOOL m_bFindEdges;
	int UpdateMemoryDC();
	void BltEx();
	int m_nMaxRange;
	int m_nMinRange;
	BOOL NotifyCommandToParent();
	CSkinnedButton *m_pcsbtnSliderButton;
	long m_lFlags;
	HRGN m_hRgn;

//Operations
public:
	int GetPosInPixels();
	void SetTicksLength(int nLength);
	void SetTicksColor(COLORREF crTicksColor);
	void ShowTicks(BOOL nShow);
	void SetShapedFlag(BOOL bShaped);
	void SetEnabled(BOOL bEnabled);
	void PositionSliderButtonVertically(int nTop);
	void PositionSliderButtonHorizontally(int nLeft);
	void SetSliderButtonDimensions(int nWidth, int nHeight);
	void SetSliderButtonImageResource(int nNormalID=-1, int nPressedID=-1, int nHoverID=-1, int nDisabledID=-1);
	void SetPos(long lValue);
	void GetRange(int &nMin, int &nMax);
	void SetRange(int nMin, int nMax, BOOL bRedraw = TRUE);
	int GetPos();
	int GetRangeMin();
	int GetRangeMax();
	int SetRangeMin(int nMin, BOOL bRedraw = TRUE);
	int SetRangeMax(int nMax, BOOL bRedraw = TRUE);
	CSkinnedSliderCtrl();
	virtual ~CSkinnedSliderCtrl();

	BOOL CreateSkinControl(LPCTSTR lpszWindowName, 
						LPRECT lpRect, 
						CWnd *pParentWnd, 
						UINT nControlID, 
						long nFlags=FL_SLIDER_HORIZONTAL);
	void MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags=0);
	void MoveWindowEng(int nLeft, int nTop, BOOL bRedraw, long lFlags=0);
	void MoveWindowEng(HWND hWnd, LPRECT lpRect, BOOL bRedraw, long lFlags=0);
	void MoveWindowEng(HWND hWnd, int nLeft, int nTop, BOOL bRedraw, long lFlags=0);	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinnedSliderCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	void MoveSliderButtonHorizontally(short nXPosition);
	void MoveSliderButtonVertically(short nXPosition);
	//{{AFX_MSG(CSkinnedSliderCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_SKINNEDSLIDERCTRL_H__6F04BA14_89E7_4ADA_840E_7D3E961E5191__INCLUDED_)
