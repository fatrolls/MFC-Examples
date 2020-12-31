// SkinCtrls.h : header file
//
#if !defined(AFX_SKINCTRLS_H__3F8CA7F2_28BE_4C6F_A2B7_CB0B6E679C5B__INCLUDED_)
#define AFX_SKINCTRLS_H__3F8CA7F2_28BE_4C6F_A2B7_CB0B6E679C5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "skinctrl.h"
#include <afxcmn.h>
#include <afxdtctl.h>

///////////////////////////////////////////////////////////////////////////////////
// derived types

// button styles
enum
{
	SKBS_CLIPLEFT =		0x0001,
	SKBS_CLIPRIGHT =	0x0002,
	SKBS_CLIPBOTH =		0x0003,
};

////////////////////////////////////////////////////////////////////////////////////

class CSkinButton : public CSkinCtrl
{
public:
	static CSkinButton* NewButton(DWORD dwBtnStyle);

protected:
	CSkinButton() : CSkinCtrl()
		{ m_dwBaseStyle = SKCS_CTLCOLOR; }

	BOOL AttachWindow(CWnd* pCtrl);
	CButton* GetButton() { return (CButton*)GetCtrl(); }
	UINT GetTextAlignment();
	CRect GetCheckRect();
	LRESULT OnMsg(UINT msg, WPARAM wp, LPARAM lp);

	BOOL m_nButtonType;
};

class CSkinButtonPush : public CSkinButton
{
public:
	CSkinButtonPush() : CSkinButton() 
		{ m_dwBaseStyle = SKCS_BTNEDGE | SKCS_PAINT; }

protected:
	BOOL AttachWindow(CWnd* pCtrl);
	virtual BOOL OnPaint(CDC* pDC); // return FALSE to allow default painting
	COLORREF GetBkgndColor();
	void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest);
	virtual BOOL OnDrawItem(LPDRAWITEMSTRUCT lpDIS);

	// helper
	void Draw(CDC* pDC, LPRECT pRect, int nState, BOOL bFocus, BOOL bOwnerdraw);
};

class CSkinButtonGroup : public CSkinButton
{
public:
	CSkinButtonGroup() : CSkinButton() 
		{ m_dwBaseStyle = SKCS_CTLCOLOR | SKCS_NOEDGE | SKCS_PAINT; }

protected:
	BOOL OnPaint(CDC* pDC);
	COLORREF GetBkgndColor();
};

class CSkinButtonCheck : public CSkinButton
{
public:
	CSkinButtonCheck() : CSkinButton() 
		{ m_dwBaseStyle = SKCS_CTLCOLOR | SKCS_NOEDGE | SKCS_PAINT; }

protected:
	virtual BOOL OnPaint(CDC* pDC); // return FALSE to allow default painting
	COLORREF GetBkgndColor();
	void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest);
};

class CSkinButtonRadio : public CSkinButton
{
public:
	CSkinButtonRadio() : CSkinButton() 
		{ m_dwBaseStyle = SKCS_CTLCOLOR | SKCS_NOEDGE | SKCS_PAINT; }

protected:
	virtual BOOL OnPaint(CDC* pDC); // return FALSE to allow default painting
	COLORREF GetBkgndColor();
	void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest);
};

////////////////////////////////////////////////////////////////////////////////////

class CSkinStatic : public CSkinCtrl
{
public:
	CSkinStatic() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_CTLCOLOR | SKCS_NCPAINT; } // rest of styles applied in AttachWindow()

protected:
	COLORREF GetBkgndColor(); // controls background color
	BOOL OnPaint(CDC* pDC);
	BOOL AttachWindow(CWnd* pCtrl);
	void OnNcCalcSize(LPRECT pClient) {}
	void OnNcPaint(CDC* pDC);
	virtual LRESULT OnMsg(UINT msg, WPARAM wp, LPARAM lp); 
};

class CSkinEdit : public CSkinCtrl
{
public:
	CSkinEdit() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_CTLCOLOR | SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }

protected:
	COLORREF GetBkgndColor(); // controls background color
	BOOL AttachWindow(CWnd* pCtrl);
	void OnNotifyReflect(UINT uNotify, LRESULT lrParent);
	virtual LRESULT OnMsg(UINT msg, WPARAM wp, LPARAM lp); 
};

class CSkinCombobox : public CSkinCtrl
{
public:
	CSkinCombobox() : CSkinCtrl() 
		{ m_bIsOwnerdraw = FALSE; m_dwBaseStyle = SKCS_PAINT | SKCS_NCPAINT | SKCS_NOBASENCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }

protected:
	void OnNcPaint(CDC* pDC);
	void OnNcCalcSize(LPRECT pClient);
	BOOL OnPaint(CDC* pDC);
	BOOL OnEraseBkgnd(CDC* pDC);
	CComboBox* GetCombo() { return (CComboBox*)GetCtrl(); }
	void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest);
	void OnNotifyReflect(UINT uNotify, LRESULT lrParent);
	void DrawDropButton(CDC* pDC, CRect& rClient, LPPOINT ptCursor = NULL);
	void OnSetFocus(BOOL bSet);
	BOOL AttachWindow(CWnd* pCtrl);
	COLORREF GetBkgndColor(); // controls background color

	BOOL m_bIsOwnerdraw;
};

class CSkinListbox : public CSkinCtrl
{
public:
	CSkinListbox() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_NCPAINT | SKCS_CTLCOLOR | SKCS_CLIENTEDGE; }

protected:
	BOOL AttachWindow(CWnd* pCtrl);
};

class CSkinCombolbox : public CSkinListbox
{
public:
	CSkinCombolbox() : CSkinListbox() { }

protected:
	void OnNcPaint(CDC* pDC);
	void OnNcCalcSize(LPRECT pClient);
	COLORREF GetParentBkgndColor();
	void DrawScrollbars(CDC* pDC, CRect rect, int nBar = SB_BOTH);
};

class CSkinScrollbar : public CSkinCtrl
{
public:
	CSkinScrollbar() : CSkinCtrl() 
		{ m_dwBaseStyle = 0; }

protected:
	BOOL AttachWindow(CWnd* pCtrl);
	virtual BOOL OnPaint(CDC* pDC);
	virtual void OnNcPaint(CDC* pDC);
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
};

class CSkinToolbar : public CSkinCtrl
{
public:
	CSkinToolbar() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_ERASEBKGND; }

protected:
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
};

class CSkinUpdown : public CSkinCtrl
{
public:
	CSkinUpdown() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_PAINT | SKCS_BTNEDGE; }

protected:
	BOOL OnPaint(CDC* pDC);
	void OnNcPaint(CDC* pDC);
	BOOL OnEraseBkgnd(CDC* pDC) { return TRUE; }
	void OnNcCalcSize(LPRECT pClient) {}
	void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest);
};

class CSkinProgress : public CSkinCtrl
{
public:
	CSkinProgress() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_PAINT | SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }

protected:
	BOOL OnPaint(CDC* pDC);
	CProgressCtrl* GetProgress() { return (CProgressCtrl*)GetCtrl(); }
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
};

class CSkinTrackbar : public CSkinCtrl
{
public:
	CSkinTrackbar() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_PAINT | SKCS_CUSTOMDRAW | SKCS_CTLCOLOR; }

protected:
	virtual LRESULT OnCustomDraw(NMCUSTOMDRAW* pNMCD, DWORD dwStage);
	void Refresh(BOOL bUpdateWindow = FALSE) { SendMessage(WM_SETFOCUS); }
	void OnNcCalcSize(LPRECT pClient) {}
	void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest);
	CSliderCtrl* GetSlider() { return (CSliderCtrl*)GetCtrl(); }
	void OnScroll(UINT nSBCode, UINT nPos, BOOL bHorz);
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
};

class CSkinHotkey : public CSkinCtrl
{
public:
	CSkinHotkey() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_NCPAINT | SKCS_PAINT | SKCS_CLIENTEDGE; }

protected:
	BOOL OnPaint(CDC* pDC);
};

class CSkinListview : public CSkinCtrl
{
public:
	CSkinListview() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_NCPAINT/* | SKCS_ERASEBKGND*/ | SKCS_CUSTOMDRAW | SKCS_CLIENTEDGE; }

protected:
	LRESULT OnCustomDraw(NMCUSTOMDRAW* pNMCD, DWORD dwStage);
	BOOL AttachWindow(CWnd* pCtrl);
	void OnStyleChanged(BOOL bExStyle, DWORD dwOldStyle, DWORD dwNewStyle);
	CListCtrl* GetList() { return (CListCtrl*)GetCtrl(); }
	void OnSetIni();
};

class CSkinTreeview : public CSkinCtrl
{
public:
	CSkinTreeview() : CSkinCtrl() 
		{ m_dwBaseStyle = /*SKCS_PAINT | */SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CUSTOMDRAW | SKCS_CLIENTEDGE; }

protected:
	BOOL AttachWindow(CWnd* pCtrl);
	LRESULT OnCustomDraw(NMCUSTOMDRAW* pNMCD, DWORD dwStage);
	CTreeCtrl* GetTree() { return (CTreeCtrl*)GetCtrl(); }
	void OnSetIni();
/*
	CRect GetItemButtonRect(HTREEITEM htItem, int nIndent, CImageList* pILNormal, CImageList* pILState);
	BOOL OnPaint(CDC* pDC);
	void DrawItemButton(CDC* pDC, CRect rButton, BOOL bPlus);
*/
};

class CSkinTabcontrol : public CSkinCtrl
{
public:
	CSkinTabcontrol() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_PAINT | SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_BTNEDGE; }

protected:
	BOOL OnPaint(CDC* pDC);
	void OnNcPaint(CDC* pDC);
	BOOL OnEraseBkgnd(CDC* pDC);
	CTabCtrl* GetTab() { return (CTabCtrl*)GetCtrl(); }
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
	virtual void DrawItem(CDC* pDC, int nItem, LPRECT pRect, BOOL bSelected = FALSE);
	virtual void DrawItemBorder(CDC* pDC, int nItem, LPRECT pRect, int nSelItem);
	void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest);
	BOOL IsHot(LPRECT pRect = NULL); // is mouse over rect. if pRect == NULL, window rect
};

class CSkinAnimate : public CSkinCtrl
{
public:
	CSkinAnimate() : CSkinCtrl() 
		{ m_dwBaseStyle = /*SKCS_PAINT | */SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }
};

class CSkinRichedit : public CSkinEdit
{
public:
	CSkinRichedit() : CSkinEdit() {}

protected:
	BOOL AttachWindow(CWnd* pCtrl);
	virtual LRESULT OnMsg(UINT msg, WPARAM wp, LPARAM lp); 
	CRichEditCtrl* GetRichEdit() { return (CRichEditCtrl*)GetCtrl(); }
	void OnSetIni();
};

class CSkinDatetimepick : public CSkinCtrl
{
public:
	CSkinDatetimepick() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_NOTIFY | SKCS_PAINT | SKCS_NOBASENCPAINT | SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }

protected:
	BOOL OnPaint(CDC* pDC);
	void OnNcPaint(CDC* pDC);
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnNcCalcSize(LPRECT pClient);
	CDateTimeCtrl* GetPicker() { return (CDateTimeCtrl*)GetCtrl(); }
	LRESULT OnNotifyReflect(NMHDR* pNMHDR, LRESULT lrParent);
	void OnTimer(UINT nIDEvent);
	void DrawDropButton(CDC* pDC, CRect& rClient, LPPOINT ptCursor = NULL);
	void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest);
	void OnSetFocus(BOOL bSet);

	static BOOL s_bDropDown;
};

class CSkinMonthcal : public CSkinCtrl
{
public:
	CSkinMonthcal() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }

protected:
	BOOL AttachWindow(CWnd* pCtrl);
	void OnNcCalcSize(LPRECT pClient);
};

class CSkinIPaddress : public CSkinCtrl
{
public:
	CSkinIPaddress() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_PAINT | SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }

protected:
	BOOL OnPaint(CDC* pDC);
};

class CSkinPager : public CSkinCtrl
{
public:
	CSkinPager() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }

protected:
};

class CSkinComboboxex : public CSkinCombobox
{
public:
	CSkinComboboxex() : CSkinCombobox() {}

protected:
};

class CSkinStatusbar : public CSkinCtrl
{
public:
	CSkinStatusbar() : CSkinCtrl() 
		{ m_dwBaseStyle = /*SKCS_PAINT | */SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }

protected:
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
};

class CSkinRebar : public CSkinCtrl
{
public:
	CSkinRebar() : CSkinCtrl() 
		{ m_dwBaseStyle = /*SKCS_PAINT | */SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CUSTOMDRAW; }

protected:
	LRESULT OnCustomDraw(NMCUSTOMDRAW* pNMCD, DWORD dwStage);
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
};

class CSkinHeader : public CSkinCtrl
{
public:
	CSkinHeader() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_PAINT | SKCS_ERASEBKGND | SKCS_NCPAINT | SKCS_BTNEDGE; }

protected:
	void OnNcPaint(CDC* pDC) {}
	BOOL OnEraseBkgnd(CDC* pDC) { return TRUE; }
	BOOL OnPaint(CDC* pDC);
	CHeaderCtrl* GetHeader() { return (CHeaderCtrl*)GetCtrl(); }
	LRESULT OnNotifyReflect(NMHDR* pNMHDR, LRESULT lrParent);
	void OnNcCalcSize(LPRECT pClient) { /* do nothing*/ }
	BOOL OnSize(int cx, int cy) { GetHeader()->Invalidate(); return FALSE; }
	void OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest);
	int HitTest(POINT ptClient);
};

class CSkinDialog : public CSkinCtrl
{
public:
	CSkinDialog() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_PAINT | SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CUSTOMDRAW; }

protected:
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
};

class CSkinTooltip : public CSkinCtrl
{
public:
	CSkinTooltip() : CSkinCtrl() {}

protected:
	BOOL AttachWindow(CWnd* pCtrl);
};

class CSkinSHDLLDefView : public CSkinCtrl
{
public:
	CSkinSHDLLDefView() : CSkinCtrl() {}

protected:
	virtual LRESULT OnMsg(UINT msg, WPARAM wp, LPARAM lp); 
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
};

class CSkinOther : public CSkinCtrl
{
public:
	CSkinOther(DWORD dwStyle = SKCS_ERASEBKGND) : CSkinCtrl() 
		{ m_dwBaseStyle = dwStyle; }

protected:
	BOOL AttachWindow(CWnd* pCtrl);
	COLORREF GetBkgndColor() { return GetColor(COLOR_WINDOW); } // controls background color
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnNcPaint(CDC* pDC);
};

class CSkinControlbar : public CSkinCtrl
{
public:
	CSkinControlbar() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_ERASEBKGND; }

protected:
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
};

class CSkinView : public CSkinCtrl
{
public:
	CSkinView() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_NCPAINT | SKCS_ERASEBKGND | SKCS_CLIENTEDGE; }

protected:
	COLORREF GetBkgndColor() { return GetColor(COLOR_WINDOW); } // controls background color
	int GetFrameThickness() { return 5; }
	BOOL OnEraseBkgnd(CDC* pDC) { return TRUE; }
};

class CSkinSplitter : public CSkinCtrl
{
public:
	CSkinSplitter() : CSkinCtrl() 
		{ m_dwBaseStyle = SKCS_PAINT | SKCS_ERASEBKGND; }

protected:
	COLORREF GetBkgndColor() { return GetParentBkgndColor(); } // controls background color
	BOOL OnPaint(CDC* pDC) { return TRUE; }
	BOOL OnEraseBkgnd(CDC* pDC) { ClipChildren(pDC); return CSkinCtrl::OnEraseBkgnd(pDC); }
};

#endif // !defined(AFX_SKINCTRLS_H__3F8CA7F2_28BE_4C6F_A2B7_CB0B6E679C5B__INCLUDED_)
