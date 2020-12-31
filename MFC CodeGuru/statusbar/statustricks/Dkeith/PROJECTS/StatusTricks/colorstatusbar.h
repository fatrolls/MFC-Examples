// ColorStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatusPaneInfo class
/////////////////////////////////////////////////////////////////////////////
// Created 29 August 1996
// Douglas W. Keith
// This class contains information required to set personalized status bar
// window pane information for each pane in the status bar.
#ifndef	__STATUSPANEINFO__
#define	__STATUSPANEINFO__

class CStatusPaneInfo : public CObject
{
protected:
	COLORREF	 p_bcolor;		// pane background color
	COLORREF	 p_tcolor;		// pane text color
	CFont		*p_font;		// pane font
	BOOL		 b_clearback;	// indicates if background should be cleared
	BOOL		 b_transparent;	// indicates if text is transparent
	BOOL		 b_vScroll;		// indicates if text is vertically scrolling
	BOOL		 b_hScroll;		// indicates if text is horizontally scrolling

public:
				 CStatusPaneInfo(COLORREF bcolor = GetSysColor(COLOR_MENU),
								COLORREF tcolor = GetSysColor(COLOR_MENUTEXT),
								CFont *font = NULL,
								BOOL clear = FALSE,
								BOOL transparent = FALSE);
				~CStatusPaneInfo();
	void		 SetBackColor(COLORREF bcolor) {p_bcolor = bcolor;}
	void		 SetTextColor(COLORREF tcolor) {p_tcolor = tcolor;}
	void		 SetFont(CFont *font) {p_font = font;}
	void		 SetClear(BOOL clear) {b_clearback = clear;}
	void		 SetTransparent(BOOL transparent) {b_transparent = transparent;}
	void		 SetVScroll(BOOL s) {b_vScroll = s;}
	void		 SetHScroll(BOOL s) {b_hScroll = s;}
	COLORREF	 GetBackColor() {return p_bcolor;}
	COLORREF	 GetTextColor() {return p_tcolor;}
	CFont		*GetFont() {return p_font;}
	BOOL		 GetClear() {return b_clearback;}
	BOOL		 GetTransparent() {return b_transparent;}
	BOOL		 GetVScroll() {return b_vScroll;}
	BOOL		 GetHScroll() {return b_hScroll;}

public:
	CPoint		 pt_lastTop;	// top point where this text was last printed
};

/////////////////////////////////////////////////////////////////////////////
// ColorStatusBar window

class CColorStatusBar : public CStatusBar
{
public:
					 CColorStatusBar();
	virtual			~CColorStatusBar();
	CStatusPaneInfo	*GetColorPaneInfo(int paneindex);
	void			 SetColorPaneInfo(int paneindex, CStatusPaneInfo *paneinfo);
	void			 SetColorPaneText(int index, CString str,
						CStatusPaneInfo &paneinfo);
	BOOL			 GetBanner() {return b_showBanner;}
	void			 SetBanner(BOOL b) {b_showBanner = b;}
	virtual BOOL	 DestroyWindow();
	void			 DrawPane(int index, CDC *dc);

public:
	CObList			 panelist;		// list of status pane information objects
	CFont			 defont;		// default font for any defaulted panes
	BOOL			 b_showBanner;	// indicates if the banner is painted
	BOOL			 b_timer;		// indicates if the timer is going

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColorStatusBar)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(ColorStatusBar)
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT uFlags, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
