// SkinCtrl.h: interface for the CSkinCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINCTRL_H__E2EFA8F0_B9CD_41AB_98FD_812C963B7ACC__INCLUDED_)
#define AFX_SKINCTRL_H__E2EFA8F0_B9CD_41AB_98FD_812C963B7ACC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\shared\subclass.h"
#include "..\shared\roundcorner.h"

// base styles
enum
{
	SKCS_NOEDGE =			0x0000,
	SKCS_CLIENTEDGE =		0x0001,
	SKCS_BTNEDGE =			0x0002,
	SKCS_ETCHEDEDGE =		0x0003,
	SKCS_EDGEMASK =			0x0003,
	SKCS_PAINT =			0x0004,
	SKCS_NCPAINT =			0x0008,
	SKCS_ERASEBKGND =		0x0010,
	SKCS_CUSTOMDRAW =		0x0020,
	SKCS_CTLCOLOR =			0x0040,
	SKCS_DRAWITEM =			0x0080,
	SKCS_NOTIFY =			0x0100,
	SKCS_NOBASENCPAINT =	0x0200,
	SKCS_POSTDRAWITEM =		0x0800,
};

class CSkinCtrlMgr;
class CSkinGlobals;

enum
{
	ISKCR_CLIPNONE		= 0x0,
	ISKCR_CLIPLEFT		= 0x1,
	ISKCR_CLIPRIGHT		= 0x2,
	ISKCR_CLIPTOP		= 0x4,
	ISKCR_CLIPBOTTOM	= 0x8,
	ISKCR_CLIPALL		= 0xf,
};

class ISkinCtrlRender
{
public:
	virtual BOOL Draw3dEdge(CDC* pDC, LPRECT pRect, int nEdge, int nState, int nClipping = ISKCR_CLIPNONE) { return FALSE; }
	virtual BOOL Draw3dRoundEdge(CDC* pDC, LPRECT pRect, int nEdge, int nState) { return FALSE; }
	virtual BOOL Draw3dRect(CDC* pDC, LPRECT pRect, int nEdge, int nState, COLORREF crBkgnd, int nClipping = ISKCR_CLIPNONE) { return FALSE; }

//	virtual BOOL DrawScrollbarButton(CDC* pDC, LPRECT pRect, int nState) { return FALSE; }
//	virtual BOOL DrawScrollbarButtonArrow(CDC* pDC, LPRECT pRect, int nBar, BOOL bBack, int nState) { return FALSE; }
//	virtual BOOL DrawSpinButton(CDC* pDC, LPRECT pRect, int nState) { return FALSE; }
//	virtual BOOL DrawSpinButtonArrow(CDC* pDC, LPRECT pRect, int nBar, BOOL bBack, int nState) { return FALSE; }

//	virtual BOOL DrawPushButton(CDC* pDC, LPRECT pRect, int nState, BOOL bClipLeft, BOOL bClipRight) { return FALSE; }
//	virtual BOOL DrawPushButtonText(CDC* pDC, LPRECT pRect, int nState) { return FALSE; }
//	virtual BOOL DrawRadioButton(CDC* pDC, LPRECT pRect, int nCheckState, int nState) { return FALSE; }
//	virtual BOOL DrawCheckButton(CDC* pDC, LPRECT pRect, int nCheckState, int nState) { return FALSE; }
};

class CSkinCtrl : public CSubclassWnd 
{
	friend class CSkinCtrlMgr;

public:
	virtual COLORREF GetBkgndColor();
	virtual COLORREF GetParentBkgndColor();
	CWnd* GetCtrl() { return GetCWnd(); }

protected:
	// only accessible to CSkinCtrlMgr
	CSkinCtrl();
	virtual ~CSkinCtrl();

	void SetGlobals(CSkinGlobals* pGlobals);

	static void SetRenderer(ISkinCtrlRender* pRenderer) { s_pRenderer = pRenderer; }
	static void EnableSkinDraw(BOOL bEnable) { s_bDrawingEnabled = bEnable; }

protected:
	BOOL m_bPreMFCSubclass;
	DWORD m_dwBaseStyle; // basic attributes
	DWORD m_dwCtrlStyle; // control specific attributes
	BOOL m_bDialog;
	DWORD m_dwOrgStyle; // original window styles 
	CSkinGlobals* m_pGlobals; 
	BOOL m_bDragging;

	static CFont s_fontMarlett2;
	static ISkinCtrlRender* s_pRenderer;
	static BOOL s_bDrawingEnabled;

protected:
	virtual BOOL OnPaint(CDC* pDC); // return FALSE to allow default painting
	virtual void OnNcPaint(CDC* pDC);
	virtual BOOL OnEraseBkgnd(CDC* pDC);
	virtual LRESULT OnCustomDraw(NMCUSTOMDRAW* pNMCD, DWORD dwStage) { return CDRF_DODEFAULT; }
	virtual LRESULT OnNotify(NMHDR* pNMHDR) { return 0; }
	virtual void OnNotify(UINT uNotify, UINT uID, CWnd* pCtrl) {}
	virtual LRESULT OnNotifyReflect(NMHDR* pNMHDR, LRESULT lrParent) { return 0; }
	virtual void OnNotifyReflect(UINT uNotify, LRESULT lrParent) {}
	virtual HBRUSH OnCtlColor(CDC* pDC);
	virtual BOOL OnDrawItem(LPDRAWITEMSTRUCT lpDIS) { return FALSE; }
	virtual BOOL OnMeasureItem(LPMEASUREITEMSTRUCT lpDIS) { return FALSE; }
	virtual void OnNcCalcSize(LPRECT pClient);
	virtual BOOL OnSize(int cx, int cy) { return FALSE; }
	virtual BOOL OnMove(int x, int y) { return FALSE; }
	virtual void OnTimer(UINT nIDEvent) {}
	virtual void OnStyleChanged(BOOL bExStyle, DWORD dwOlsStyle, DWORD dwNewStyle) {}
	virtual void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, // cursor pos in window coords
									UINT uOldHitTest, UINT uNewHitTest);
	virtual void OnSetIni() { Refresh(); }
	virtual void OnSetFocus(BOOL bSet) {}
	virtual void OnScroll(UINT nSBCode, UINT nPos, BOOL bHorz);

	virtual LRESULT OnMsg(UINT msg, WPARAM wp, LPARAM lp); 

	BOOL IsValid() { return IsHooked(); } // is it hooked up and ready to go

	virtual BOOL AttachWindow(CWnd* pCtrl);
	virtual BOOL DetachWindow();
	void FillCorners(CDC* pDC, LPRECT pWindow, COLORREF crParentBack, int nCorners = RC_ALL, int nEdgeStyle = -1);
	virtual void GetDrawRect(LPRECT pWindow, LPRECT pClient = NULL, BOOL bExcludeScrollbars = TRUE);
	CWnd* GetChildWnd(LPCTSTR szClass);
	void NcPaint(CDC* pDC, CRect rect);
	void NcPaintBorder(CDC* pDC, CRect rect, COLORREF crParentBack, COLORREF crBack, int nEdgeStyle, BOOL bIsNc = TRUE);
	void EraseBkgnd(CDC* pDC, CRect rect);
	void ClipChildren(CDC* pDC);
	virtual int GetFrameThickness();
	BOOL HasLeftScrollbar();
	virtual BOOL IsScrollbarEnabled(int nBar, BOOL bSpinButton = FALSE);
	void GetCursorPos(LPPOINT pCursor); // in window coords
	void CalcTextRect(CDC* pDC, CString sText, CRect& rText, UINT nAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	BOOL IsChild(CSkinCtrl* pSkin);
	BOOL IsPopup();
	BOOL IsHot(LPRECT pRect = NULL, BOOL bScreenCoords = FALSE); // is mouse over rect. if pRect == NULL, window rect
	virtual void Refresh(BOOL bUpdateWindow = FALSE);
	BOOL ModifyStyle(DWORD dwStylesToRemove, DWORD dwStylesToAdd);

	int GetState(LPRECT pHotRect = NULL); // returns IM_xxx state 

	BOOL WantsDraw(DWORD dwDraw) { return ((m_dwBaseStyle & dwDraw) == dwDraw); }
	int EdgeStyle() { return (m_dwBaseStyle & SKCS_EDGEMASK); }
	BOOL HasCtrlStyle(DWORD dwStyle, DWORD dwMask = -1);
	void SetRedraw(BOOL bRedraw) { ::SendMessage(GetHwnd(), WM_SETREDRAW, bRedraw, 0); }

	// wrapper around CRoundCorner::Draw()
	void Draw3dEdge(CDC* pDC, LPRECT pRect, int nRadius, int nEdge, int nState, int nClipping = ISKCR_CLIPNONE);
//	void Draw3dRect(CDC* pDC, LPRECT pRect, int nRadius, int nEdge, int nState, COLORREF crBkgnd, int nClipping = ISKCR_CLIPNONE);

	virtual void DrawScrollbars(CDC* pDC, CRect rWindow, int nBar = SB_BOTH);
	void DrawScrollbarThumb(CDC* pDC, CRect rScrollbar, int nBar);
	void DrawScrollBar(CDC* pDC, CRect rScrollbar, int nBar, LPPOINT pCursor); // cursor in window coords
	void DrawScrollbarButton(CDC* pDC, CRect rButton, int nBar, BOOL bBack, BOOL bDown, COLORREF crParentBackColor, BOOL bSpinButton = FALSE);
	void DrawDropButton(CDC* pDC, CRect rButton, LPPOINT pCursor, COLORREF crParentBackColor);
	void DrawSpinButton(CDC* pDC, CRect rButton, LPPOINT pCursor, BOOL bVert, COLORREF crParentBackColor);
	void GetScrollbarButtonRects(CRect rect, int nBar, LPRECT pBack, LPRECT pForward);
	void GetScrollbarRects(CRect rWindow, LPRECT pHorz, LPRECT pVert, LPRECT pDeadSpace = NULL);
	HRGN GetScrollTrackRgn();
	void DrawPushButton(CDC* pDCMem, CRect rButton, int nState, int nCorner, COLORREF crParentBackColor = -1, BOOL bClipLeft = FALSE, BOOL bClipRight = FALSE);
	void DrawPushButton(CDC* pDCMem, CRect rButton, CBitmap* pBMLeft, CBitmap* pBMMid, CBitmap* pBMRight, COLORREF crParentBackColor = -1, COLORREF crMask = -1);
	void DrawPushButtonBitmap(CDC* pDCMem, CDC* pDCMem2, CRect rBitmap, CBitmap* pBitmap, BOOL bMid, COLORREF crMask = -1);

	// for redrawing during scrolling
	static LRESULT CALLBACK MsgWndProc(int code, WPARAM wp, LPARAM lp);
	BOOL OnMsgWndProc(MSG& msg);

	// helpers because friend status is not transferable
	static CSkinCtrl* GetSkinCtrl(CWnd* pCtrl);
	static CSkinCtrl* GetSkinCtrl(HWND hCtrl);
	static BOOL Skin(HWND hCtrl);
	static LRESULT DoCustomDraw(HWND hCtrl, NMHDR* pNMHDR);
	static LRESULT DoNotifyReflect(HWND hCtrl, NMHDR* pNMHDR, LRESULT lrParent);
	static void DoNotifyReflect(HWND hCtrl, UINT uNotify, LRESULT lrParent);
	static HBRUSH DoCtlColor(HWND hCtrl, CDC* pDC);
	static void DoScroll(HWND hCtrl, UINT nSBCode, UINT nPos, BOOL bHorz);

	static void AlignRect(CRect& rect, const CRect& rContainer, UINT nAlignment);

	// for redrawing after closeup
	BOOL DelayRedraw(int nDelay = 100);

	// helper wrappers
	COLORREF GetColor(int nColor);
	CBrush* GetColorBrush(int nColor);
	CBrush* GetColorBrush(COLORREF color);
	CPen* GetColorPen(int nColor, int nWidth = 0);
	CPen* GetColorPen(COLORREF color, int nWidth = 0);
	CFont* GetFont(int nFont); // if SBFONT_MARLETT then return our version
	CBitmap* GetControlBitmap(int nItem, int nState = 0, COLORREF* pMask = NULL, int nAltItem = -1);

private:
	LRESULT WindowProc(HWND hRealWnd, UINT msg, WPARAM wp, LPARAM lp); 
};


#endif // !defined(AFX_SKINCTRL_H__E2EFA8F0_B9CD_41AB_98FD_812C963B7ACC__INCLUDED_)
