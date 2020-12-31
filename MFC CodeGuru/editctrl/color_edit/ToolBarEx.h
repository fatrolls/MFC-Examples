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
				if( m_pStringMap != 0 && !m_pStringMap->IsEmpty() ) {
					// there are strings assigned to at least one button
					// center the image horizontal
					m_sizeOffset.cx = (m_sizeButton.cx-m_sizeImage.cx)/2;
					// the following value calculates as follows:
					// The button must be big enough to hold the image:
					//	+ 7 pixels on x
					//	+ 6 pixels on y
					// So the y-offset is "min" (6) / 2 == 3
					m_sizeOffset.cy = 3;
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

#endif // !defined(AFX_TOOLBAREX_H__1E0F37F5_4020_11D1_9FB1_444553540000__INCLUDED_)
