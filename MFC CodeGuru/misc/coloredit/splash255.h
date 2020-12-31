#if !defined(AFX_MYSPLASHWND_H__08C608F3_1FB3_11D1_830E_58A47E000000__INCLUDED_)
#define AFX_MYSPLASHWND_H__08C608F3_1FB3_11D1_830E_58A47E000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MySplashWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplash255Wnd window

class CSplash255Wnd : public CWnd
{
// Construction
public:
    CSplash255Wnd(UINT nBitmapID, UINT nDuration = 2500);

// Attributes
public:
    BOOL Create();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplash255Wnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplash255Wnd)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL GetBitmapAndPalette(UINT nIDResource, CBitmap &bitmap, CPalette &pal);

protected:
	UINT m_nBitmapID;
	UINT m_nDuration;
	UINT m_nTimerID;
	CBitmap m_bitmap;
	CPalette m_pal;
	CWnd m_wndInvisible;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPLASHWND_H__08C608F3_1FB3_11D1_830E_58A47E000000__INCLUDED_)