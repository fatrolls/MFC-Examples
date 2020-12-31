/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1997 by Joerg Koenig
// All rights reserved
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_TOOLBAREX_H__1E0F37F5_4020_11D1_9FB1_444553540000__INCLUDED_)
#define AFX_TOOLBAREX_H__1E0F37F5_4020_11D1_9FB1_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ToolBarEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx window

class CToolBarEx : public CToolBar
{
	DECLARE_DYNAMIC(CToolBarEx)

// data members
private:
	BOOL		m_bFlatLook;
	CSize		m_sizeOffset;		// real starting point of the image
	COLORREF	m_clrBtnFace;
	COLORREF	m_clrBtnHilight;
	COLORREF	m_clrBtnShadow;
	COLORREF	m_clrBtnLight;
	int			m_nLastBtn;			// index of last formed button
	UINT		m_uTimerEvent;
	CUIntArray	m_Styles;
	HWND		m_hwndParent;		// "real" parent (even in floating mode)
	BOOL		m_bDeleteImgList;	// remember the way we've built the image list
	CFont		m_GuiFont;

// Construction
public:
	CToolBarEx();

// Attributes
public:
	void	SetFlatLook( BOOL bFlat = TRUE ) {
				if( bFlat != m_bFlatLook ) {
					m_bFlatLook = bFlat;
					if( ::IsWindow(GetSafeHwnd()) ) {
						// force a repaint of all buttons
						Invalidate();
						// erase/draw the gripper
						OnNcPaint();
					}
				}
			}

	BOOL	IsFlatLook() const {
				return m_bFlatLook;
			}

	// This function I've missed in CToolBar for more than one time ...
	void	GetSizes( CSize & szBtn, CSize & szImg ) const {
				szBtn = m_sizeButton;
				szImg = m_sizeImage;
			}

	// Get the window to which the toolbar initially was docked. This
	// is not necessarily the window returned by CWnd::GetParent() or
	// CControlBar::GetDockingFrame(). Both these functions don't
	// return the expected window, if the toolbar is floating ...
	CWnd *	GetParentFrame() const {
				return ::IsWindow(m_hwndParent) ? CWnd::FromHandle(m_hwndParent) : 0;
			}

	BOOL	HasButtonText() const {
				return m_pStringMap != 0 && !m_pStringMap->IsEmpty();
			}

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarEx)
	//}}AFX_VIRTUAL

protected:
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );

// Implementation
public:
	virtual ~CToolBarEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarEx)
	afx_msg void OnPaint();
	afx_msg void OnSysColorChange();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	afx_msg LRESULT		OnSetButtonSize(WPARAM, LPARAM);
	afx_msg LRESULT		OnSetBitmapSize(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()


private:
	// Recalculate the starting point of the button's image.
	void	CalculateOffset() {
				if( HasButtonText() ) {
					// there are strings assigned to at least one button
					// center the image horizontal
					m_sizeOffset.cx = (m_sizeButton.cx-m_sizeImage.cx)/2;
					m_sizeOffset.cy = m_cyTopBorder;
				} else {
					// no button has text assigned: center the image on the button
					m_sizeOffset.cx = (m_sizeButton.cx-m_sizeImage.cx)/2;
					m_sizeOffset.cy = (m_sizeButton.cy-m_sizeImage.cy)/2;
				}
			}

	// some special drawing functions:
	void	DrawDisabledButton( CDC &, const CRect & ) const;
	void	DrawSeparator( CDC &, CRect & ) const;
	void	DrawGripper( CDC & ) const;

	HIMAGELIST	GetImageList();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.


// There is a bug in the patch of VC++ 4.2b: The commctrl.h, which already
// contains NM_CUSTOMDRAW is replaced with one version that doesn't.
// Thanks to Todd C. Wilson for the code below.
#if _MFC_VER >= 0x0420  &&  ! defined(NM_CUSTOMDRAW)

#define NM_CUSTOMDRAW           (NM_FIRST-12)
#define NM_HOVER                (NM_FIRST-13)

#define TB_SETIMAGELIST         (WM_USER + 48)
#define TB_GETIMAGELIST         (WM_USER + 49)
#define TB_LOADIMAGES           (WM_USER + 50)
#define TB_GETRECT              (WM_USER + 51) // wParam is the Cmd instead of index
#define TB_SETHOTIMAGELIST      (WM_USER + 52)
#define TB_GETHOTIMAGELIST      (WM_USER + 53)
#define TB_SETDISABLEDIMAGELIST (WM_USER + 54)
#define TB_GETDISABLEDIMAGELIST (WM_USER + 55)
#define TB_SETSTYLE             (WM_USER + 56)
#define TB_GETSTYLE             (WM_USER + 57)
#define TB_GETBUTTONSIZE        (WM_USER + 58)

//==================== CUSTOM DRAW ==========================================

// custom draw return flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
#define CDRF_DODEFAULT          0x00000000
#define CDRF_NEWFONT            0x00000002
#define CDRF_SKIPDEFAULT        0x00000004

#define CDRF_NOTIFYPOSTPAINT    0x00000010
#define CDRF_NOTIFYITEMDRAW     0x00000020

// drawstage flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
#define CDDS_PREPAINT           0x000000001
#define CDDS_POSTPAINT          0x000000002
// the 0x000010000 bit means it's individual item specific
#define CDDS_ITEM               0x000010000
#define CDDS_ITEMPREPAINT       (CDDS_ITEM | CDDS_PREPAINT)
#define CDDS_ITEMPOSTPAINT      (CDDS_ITEM | CDDS_POSTPAINT)

// itemState flags
#define CDIS_SELECTED    0x0001
#define CDIS_GRAYED      0x0002
#define CDIS_DISABLED    0x0004
#define CDIS_CHECKED     0x0008
#define CDIS_FOCUS       0x0010
#define CDIS_DEFAULT     0x0020

typedef struct tagNMCUSTOMDRAWINFO
{
    NMHDR hdr;
    DWORD dwDrawStage;
    HDC hdc;
    RECT rc;
    DWORD dwItemSpec;  // this is control specific, but it's how to specify an item.  valid only with CDDS_ITEM bit set
    UINT  uItemState;
    LPARAM lItemlParam;
} NMCUSTOMDRAW, FAR * LPNMCUSTOMDRAW;

// for tooltips

typedef struct tagNMTTCUSTOMDRAW
{
    NMCUSTOMDRAW nmcd;
    UINT uDrawFlags;
} NMTTCUSTOMDRAW, FAR * LPNMTTCUSTOMDRAW;

#endif  // _MFC_VER >= 4.2 && ! defined(NM_CUSTOMDRAW)

#endif // !defined(AFX_TOOLBAREX_H__1E0F37F5_4020_11D1_9FB1_444553540000__INCLUDED_)
