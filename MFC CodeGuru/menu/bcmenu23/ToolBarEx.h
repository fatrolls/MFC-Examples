/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1997,'98 by Joerg Koenig
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

// last revised: $Date: 10.05.98 17:45 $ $Revision: 2 $



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
	friend class CToolBarMgr;
	friend class CToolDockBar;

	DECLARE_DYNAMIC(CToolBarEx)

// data members
protected:
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
	CObList *	m_pControls;		// list of custom controls (if any)
	BOOL		m_bReal3DBorder;	// TRUE, if you're using FrameEnableDocking() instead
									// of CFrameWnd::EnableDocking(). That enables you to
									// draw a "real" 3D frame around the toolbar
	// ALT-drag implementation:
	static HCURSOR		m_hOrigCursor;
	static HCURSOR		m_hDragCursor;
	static HCURSOR		m_hNoDragCursor;
	static BOOL			m_bDragging;
	static BOOL			m_bDragCursor;
	static int			m_nDragButton;
	static CToolBarEx *	m_pDropBar;
	static CPoint		m_ptDrop;
	BOOL				m_bDragChild;

// Construction
public:
	CToolBarEx();

// Attributes
public:
	void	SetFlatLook( BOOL bFlat = TRUE );

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

	// enhancements start here:
	
	// determine whether this toolbar has text-buttons
	BOOL	HasButtonText() const {
				return m_pStringMap != 0 && !m_pStringMap->IsEmpty();
			}

	// invalidate the button with the given index
	void	InvalidateButton(int nIndex);

	// Check whether the button with index <idx> is a "real" separator.
	// Thus it is *not* a control.
	BOOL	IsSeparator(int idx) const;

	// Check whether this button is a control in real life
	BOOL	IsControl(int idx) const;

	// Get the control that is associated with the given index
	// The CWnd * returned may be temporary (if you don't use
	// MFC to add a control to the toolbar)
	CWnd *	GetControl(int idx, BOOL IdxIsID = FALSE) const;

	// Retrieve the bitmap associated with the button with ID <ID>.
	// The background of the bitmap is the current setting for
	// COLOR_BTNFACE.
	// Don't forget to destroy the bitmap, if it is not longer needed!
	HBITMAP	GetBitmap(int ID);

	// Replace the button with ID <id> with a custom control
	// of type <pClass>. The custom control gets the ID <id>.
	// <rc> gives width & height of the control.
	// The stylebits WS_CHILD and WS_VISIBLE will be added automatically.
	// to <dwStyle>.
	// The control shall support the DECLARE_DYNCREATE! (except
	// CComboBox and CEdit which are handled separatly)
	// You must not "delete" the return-value !
	CWnd *	CtrlReplace(
				CRuntimeClass * pClass,
				CRect & rc,
				UINT id,
				DWORD dwStyle = 0
			);

	// Insert a custom control before the button with index <before>.
	// if <before> == -1, then the control is appended behind the last
	// button.
	// For more information see CtrlReplace() above.
	CWnd *	CtrlInsert(
				CRuntimeClass * pClass,
				CRect & rc,
				UINT id,
				int before = 0,
				DWORD dwStyle = 0
			);

	// call "RepositionControls()" if you have added one or more controls
	// and want to add more buttons/controls.
	// This function will automatically be called for controls when calling
	// CtrlReplace() and CtrlInsert().
	void	RepositionControls();

	// Recalculate the size of the toolbar and recalculate the
	// layout of its parent.
	void	RecalcLayout();

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarEx)
	//}}AFX_VIRTUAL

protected:
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );
	virtual BOOL PreTranslateMessage(MSG * pMsg);

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	afx_msg LRESULT		OnSetButtonSize(WPARAM, LPARAM);
	afx_msg LRESULT		OnSetBitmapSize(WPARAM, LPARAM);
	afx_msg LRESULT		OnAddBitmap(WPARAM, LPARAM);
	afx_msg LRESULT		OnDeleteButton(WPARAM, LPARAM);
#ifdef _MEMDC_H_
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
#endif

	DECLARE_MESSAGE_MAP()


protected:
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
	virtual void	DrawDisabledButton( CDC &, const CRect & ) const;
	virtual void	DrawSeparator( CDC &, CRect & ) const;
	virtual void	DrawGripper( CDC & ) const;
	virtual void	Draw3DBorders( CDC *, CRect &);

	HIMAGELIST	GetImageList();

	// Create the user control. This is a helper function for
	// CtrlReplace() and CtrlInsert() above.
	CWnd *	CreateControl(
				CRuntimeClass * pClass,
				CRect & rc,
				UINT ID,
				DWORD dwStyle
			);
	
	// Retrieve the bitmap with index <Index> and resize it to fit to <sizeBitmap>.
	HBITMAP	GetBitmap(int Index, const CSize & sizeBitmap);

	// Alt-drag implementation
	BOOL	BeginDrag();
	void	DragMove();
	void	EndDrag(BOOL bDoMove = TRUE);
	BOOL	IsValidDropTarget(const CWnd *) const;
	void	CheckMoveControl( CToolBarEx * pToolBar, const TBBUTTON & tbButton );
	void	RemoveTrailingSeparators();
	int		FindDropButton(const CPoint & point);
	void	GetMarkerRect(int nButton, CRect & rc);
	void	ShowMarker(const CRect & rcMarker, CBitmap & bmpArea);
	void	RestoreMarker( const CRect & rcArea, CBitmap & bmpArea );
	void	SetMarker(CToolBarEx *, const CPoint &);
	BOOL	QueryDeleteInsert(TBBUTTON & tbButton, BOOL bQueryDelete, int BtnIndex);
	BOOL	DoQueryDelete(int nButton);
	BOOL	DoQueryInsert(TBBUTTON & tbButton, int nIndex) {
				return QueryDeleteInsert(tbButton, FALSE, nIndex);
			}
};

// This is a replacement function for CFrameWnd::EnableDocking(). This function
// enables the "real" 3D look of the bar itself (as in Office or DevStudio).
// Change the call to "EnableDocking()" in your CMainFrames's OnCreate() to
// "FrameEnableDocking()".
void FrameEnableDocking(CFrameWnd * Frame, DWORD DockStyle);


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
