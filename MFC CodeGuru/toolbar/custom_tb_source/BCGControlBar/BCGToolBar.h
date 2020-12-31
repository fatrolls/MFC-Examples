//
// bcgtoolbar.h : definition of CBCGToolBar
//
// This code is based on the Microsoft Visual C++ sample file
// TOOLBAR.C from the OLDBARS example
//

#ifndef _TOOLBAR_H_
#define _TOOLBAR_H_

#include "BCGToolbarDropTarget.h"
#include "BCGToolbarDropSource.h"

//----------------------------------
// BCGToolbar notification messages:
//----------------------------------
AFX_EXT_CLASS extern UINT BCGM_TOOLBARMENU;
AFX_EXT_CLASS extern UINT BCGM_CUSTOMIZETOOLBAR;

class CBCGToolbarButton;
class CBCGToolBarImages;

class AFX_EXT_CLASS CBCGToolBar : public CControlBar
{
	friend class CBCGToolbarDropTarget;
	friend class CToolbarsPage;

	DECLARE_SERIAL(CBCGToolBar)

	//--------------
	// Construction:
	//--------------
public:
	CBCGToolBar();
	BOOL Create(CWnd* pParentWnd,
			DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
			UINT nID = AFX_IDW_TOOLBAR);

	//----------------------------------------------------------------
	// Set toolbar buttons image resources.
	// You should use SINGLE CBCGToolBarImages for ALL your toolbars!
	//----------------------------------------------------------------
	BOOL SetImages (CBCGToolBarImages* pImages,
					CBCGToolBarImages* pUserImages = NULL);

	//--------------------------------
	// Dimension manipulation methods:
	//--------------------------------
	void SetSize (SIZE sizeButton);
	void SetHeight (int cyHeight);

	//------------------------------------------------------------
	// For the compatibility issues only! uiResID should be equal
	// to the CBCGToolBarImages resource ID (see above):
	//------------------------------------------------------------
	BOOL LoadToolBar (UINT uiResID);

	//----------------------------
	// Toolbar buttons add/remove:
	//----------------------------
	BOOL SetButtons(const UINT* lpIDArray, int nIDCount);

	int InsertButton (const CBCGToolbarButton& button, int iInsertAt = -1);
	int InsertSeparator (int iInsertAt = -1);
	
	BOOL RemoveButton (int iIndex);
	void RemoveAllButtons ();

	//------------
	// Attributes:
	//------------
public: 

	// standard control bar things
	int CommandToIndex(UINT nIDFind) const;
	UINT GetItemID(int nIndex) const;
	virtual void GetItemRect(int nIndex, LPRECT lpRect) const;
	UINT GetButtonStyle(int nIndex) const;
	void SetButtonStyle(int nIndex, UINT nStyle);

	int GetCount () const;
	int ButtonToIndex(const CBCGToolbarButton* pButton) const;
	inline CBCGToolbarButton* GetButton (int iIndex) const;

	// Find all buttons specified by the given command ID from the all
	// toolbars:
	static int GetCommandButtons (UINT uiCmd, CObList& listButtons);
	
	static BOOL SetCustomizeMode (BOOL bSet = TRUE);
	static CBCGToolBar* FromHandlePermanent (HWND hwnd);

public:
	// for changing button info
	void GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage) const;
	void SetButtonInfo(int nIndex, UINT nID, UINT nStyle, int iImage);

	// Save/load toobar state + buttons:
	void Serialize (CArchive& ar);
	BOOL LoadState (LPCTSTR lpszProfileName, int nIndex);
	BOOL SaveState (LPCTSTR lpszProfileName, int nIndex);

// Implementation
public:
	virtual ~CBCGToolBar();

protected:
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout (int nLength, DWORD dwMode);
	CSize CalcLayout (DWORD dwMode, int nLength = -1);
	CSize CalcSize ();
	int WrapToolBar (int nWidth);
	void  SizeToolBar (int nLength, BOOL bVert = FALSE);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int InsertButton (CBCGToolbarButton* pButton, int iInsertAt = -1);
	void InvalidateButton(int nIndex);
	void UpdateButton(int nIndex);

	BOOL DrawButton (CDC* pDC, CBCGToolbarButton* pButton, BOOL bHighlighted);
	void DrawGripper (CDC* pDC);
	void DrawDragMarker (CDC* pDC);

protected:
	CBCGToolBarImages*	m_pImages;
	CBCGToolBarImages*	m_pUserImages;

	CSize m_sizeButton;         // size of button
	CSize m_sizeImage;          // size of glyph
	int m_iButtonCapture;       // index of button with capture (-1 => none)
	int m_iHighlighted;			// highlighted button index
	int m_iSelected;			// selected button index

	CObList	m_Buttons;
	CBCGToolbarDropTarget	m_DropTarget;
	CBCGToolbarDropSource	m_DropSource;

	static BOOL m_bCustomizeMode;

	DROPEFFECT	m_prevDropEffect;
	int			m_iDragIndex;
	CRect		m_rectDrag;
	CPen		m_penDrag;
	CBCGToolbarButton* m_pDragButton;
	CPoint		m_ptStartDrag;

	CFont		m_fontVert;

	BOOL		m_bStretchButton;
	CRect		m_rectTrack;

	HCURSOR	m_hcurStretch;
	HCURSOR	m_hcurDelete;

	static BOOL m_bShowTooltips;

	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);

	virtual void DoPaint(CDC* pDC);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual int HitTest(CPoint point);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual DWORD RecalcDelayShow(AFX_SIZEPARENTPARAMS* lpLayout);

	int FindDropIndex (const CPoint point, CRect& rectDrag) const;
	void AdjustLocations ();
	void AddRemoveSeparator (const CBCGToolbarButton* pButton,
						const CPoint& ptStart, const CPoint& ptDrop);

	//{{AFX_MSG(CBCGToolBar)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnSysColorChange();
	afx_msg void OnMove(int x, int y);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnToolbarAppearance();
	afx_msg void OnToolbarDelete();
	afx_msg void OnToolbarImage();
	afx_msg void OnToolbarImageAndText();
	afx_msg void OnToolbarStartGroup();
	afx_msg void OnToolbarText();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#endif //!_TOOLBAR_H_
