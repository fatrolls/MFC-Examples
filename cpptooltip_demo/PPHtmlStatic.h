//
//	Class:		CPPHtmlStatic
//
//	Compiler:	Visual C++
//	Tested on:	Visual C++ 6.0
//				Visual C++ .NET 2003
//
//	Version:	See GetVersionC() or GetVersionI()
//
//	Created:	xx/xxxx/2004
//	Updated:	21/November/2004
//
//	Author:		Eugene Pustovoyt	pustovoyt@mail.ru
//
//	Disclaimer
//	----------
//	THIS SOFTWARE AND THE ACCOMPANYING FILES ARE DISTRIBUTED "AS IS" AND WITHOUT
//	ANY WARRANTIES WHETHER EXPRESSED OR IMPLIED. NO REPONSIBILITIES FOR POSSIBLE
//	DAMAGES OR EVEN FUNCTIONALITY CAN BE TAKEN. THE USER MUST ASSUME THE ENTIRE
//	RISK OF USING THIS SOFTWARE.
//
//	Terms of use
//	------------
//	THIS SOFTWARE IS FREE FOR PERSONAL USE OR FREEWARE APPLICATIONS.
//	IF YOU WISH TO THANK MY WORK, YOU MAY DONATE ANY SUM OF MONEY TO ME 
//  FOR SUPPORT OF DEVELOPMENT OF THIS CLASS.
//	IF YOU USE THIS SOFTWARE IN COMMERCIAL OR SHAREWARE APPLICATIONS YOU
//	ARE GENTLY ASKED TO DONATE ANY SUM OF MONEY TO THE AUTHOR:
//
//--- History ------------------------------ 
// 2004/05/09 *** Releases version 1.0 ***
//------------------------------------------
// 2004/05/18 [ADD] Added a SetBkColor method and a SetBkMode method
// 2004/05/19 [ADD] Added a ClearFrameRate method (thanks to Steve Mayfield)
//			  [FIX] Fixed a minor errors with animation (thanks to Steve Mayfield)
// 2004/05/21 [FIX] Fixed a dirty control when redrawing of the text
// 2004/05/25 [FIX] Enable state of the control wasn't initialized
//------------------------------------------
// 2004/05/25 *** Releases version 1.1 ***
//------------------------------------------
// 2004/06/11 [ADD] Added an using of the control's initialization text
// 2004/06/13 [UPD] Now the control uses the system colors of CStatic and OPAQUE mode 
//				    by default
// 2004/07/14 [FIX] Fixed bug of the animation static destroy.
//			  [ADD] Implemented a border of a static (SetBorder and SetBorderColor methods)
//			  [ADD] Added support a wrap text (SS_LEFTNOWORDWRAP style)
// 2004/08/09 [FIX] Corrected work of OnMouseLeave method
// 2004/10/28 [ADD] Added SetFitOutput method for output by full width of the control
// 2004/11/03 [ADD] Added OnSize method
//------------------------------------------
// 2004/11/11 *** Releases version 1.2 ***
//------------------------------------------
/////////////////////////////////////////////////////////////////////

#ifndef _PPHTMLSTATIC_H
#define _PPHTMLSTATIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPHtmlStatic.h : header file
//
#include "PPHtmlDrawer.h"

#define UDM_TOOLTIP_REPAINT		   (WM_APP + 100)

#define PPHTMLSTATIC_ALIGN_DEFAULT		0x00
#define PPHTMLSTATIC_ALIGN_LEFT    	    0x01
#define PPHTMLSTATIC_ALIGN_RIGHT  		0x02
#define PPHTMLSTATIC_ALIGN_CENTER 		0x03
#define PPHTMLSTATIC_ALIGN_TOP 		    0x04
#define PPHTMLSTATIC_ALIGN_BOTTOM  		0x08
#define PPHTMLSTATIC_ALIGN_VCENTER 		0x0C

/////////////////////////////////////////////////////////////////////////////
// CPPHtmlStatic window

class CPPHtmlStatic : public CStatic
{
// Construction
public:
	CPPHtmlDrawer * GetHtmlDrawer() {return &m_drawer;};

	void SetCallbackHyperlink(UINT nMessage, LPARAM lParam = 0);
	void SetHyperlink(LPCTSTR lpszText, LPCTSTR lpszUrl, BOOL bParentNotify = FALSE);

	void SetIcon(DWORD dwIdIcon, LPSIZE lpSizeItem = NULL);
	void SetIcon(HICON hIcon);
	void SetBitmap(DWORD dwIdBitmap, COLORREF clrMask = RGB(255, 0, 255));
	void SetBitmap(HBITMAP hBitmap, COLORREF clrMask = RGB(255, 0, 255));
	void SetAnimation(DWORD dwIdBitmap, LPSIZE lpSizeItem = NULL, COLORREF clrMask = RGB(255, 0, 255));
	void SetAnimation(HBITMAP hBitmap, LPSIZE lpSizeItem = NULL, COLORREF clrMask = RGB(255, 0, 255));
	void SetImageList(DWORD dwIdBitmap, DWORD dwIndex, LPSIZE lpSizeItem = NULL, COLORREF clrMask = RGB(255, 0, 255));
	void SetImageList(HBITMAP hBitmap, DWORD dwIndex, LPSIZE lpSizeItem = NULL, COLORREF clrMask = RGB(255, 0, 255));

	//Regions
	void SetRgn(HRGN hRgn = NULL); //Sets a region
	void SetRectRgn(); //Creates and sets a rectangle region
	void SetRoundRectRgn(int nWidth, int nHeight); //Creates and sets a rounded rectangle region
	void SetBorder(COLORREF color, int nWidth = 1, int nHeight = 1); //Sets a static's border
	void SetBorder(HBRUSH hbr, int nWidth = 1, int nHeight = 1); //Sets a static's border

	void SetMargins(int nXMargin = 0, int nYMargin = 0); //Sets a text's margins 

	void  SetAlign(DWORD dwAlign = PPHTMLSTATIC_ALIGN_DEFAULT);
	DWORD GetAlign();

	void SetImageZoom(int nWidthPercent = 100, int nHeightPercent = 100);
	void SetImageZoom(int nPercent = 100);
	
	void SetFrameRate(DWORD dwFrameRate = 500);
	void ClearFrameRate();

	void SetHyperlinkStyle(COLORREF clrOrg, BOOL bOrgUnderline, COLORREF clrHover, BOOL bHoverUnderline);

	void SetTextColor(COLORREF clrText);
	void SetBkColor(COLORREF clrBk);
	void SetBkColor(COLORREF clrBegin, COLORREF clrEnd);
	void SetBkColor(COLORREF clrBegin, COLORREF clrMid, COLORREF clrEnd);
	void SetBkMode(int nBkMode = TRANSPARENT);
	void SetBkEffect(DWORD dwEffect, BYTE nGranularity = 5);

//	void SetFitOutput(BOOL bFitOutput = TRUE){m_bIsFitOutput = bFitOutput;};
	void SetWrapText(BOOL bWrapText);

	static short GetVersionI()		{return 0x12;}
	static LPCTSTR GetVersionC()	{return (LPCTSTR)_T("1.2");}

	CPPHtmlStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPHtmlStatic)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPPHtmlStatic();

	// Generated message map functions
protected:
	void SetDefaultFont(HFONT hFont);
	void SetText(LPCTSTR lpszText);
	void UpdateSurface();
	void RepaintWindow(HDC hDC = NULL);
	HRGN CreateRegion();

	void FreeResources();

	HBITMAP m_hBitmapBk;

	HRGN m_hRgn;
	BOOL m_bRectRgn;
	int  m_nRoundX;
	int  m_nRoundY;

	//Border of the tooltip
	HBRUSH m_hbrBorder;
	SIZE m_szBorder;

	SIZE m_szTextMargin;

	CRect m_rcArea;
	CSize m_szOutput;
	CSize m_szImage;

	CPPHtmlDrawer m_drawer;
	DWORD	m_dwAlign;
	CString m_sText;
	CString m_sOrgText; //Original
	int m_nWidthPercent;
	int m_nHeightPercent;
	
	BOOL m_bIsEnabled;
//	BOOL m_bIsFitOutput;

	//Timer
	BOOL m_bIsRunning;
	DWORD m_dwFrameRate;

	BOOL m_bIsImage;
	CString m_sTemplate;

	HFONT m_hFont;

	COLORREF m_clrText;
	COLORREF m_clrBkBegin;
	COLORREF m_clrBkMid;
	COLORREF m_clrBkEnd;
	int m_nBkMode;
	DWORD m_dwBkEffect;
	BYTE m_nGranularity;

	CScrollBar m_pHScroll;
	CScrollBar m_pVScroll;

	//{{AFX_MSG(CPPHtmlStatic)
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
 	afx_msg LRESULT OnGetText(WPARAM, LPARAM);
	afx_msg LRESULT OnSetText(WPARAM, LPARAM);
	afx_msg LRESULT OnSetFont(WPARAM, LPARAM);
	afx_msg LRESULT OnGetFont(WPARAM, LPARAM);
    afx_msg LRESULT OnRepaintWindow(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
