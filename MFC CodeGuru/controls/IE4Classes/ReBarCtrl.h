#ifndef __RBCTL_H__
#define __RBCTL_H__

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

#ifndef __AFXDISP_H__
  #include <afxdisp.h>
#endif

/////////////////////////////////////////////////////////////////////////////

  class CImageList;
  class CToolTipCtrl;

/////////////////////////////////////////////////////////////////////////////
// CReBarCtrl

class CReBarCtrl : public CWnd
{
  DECLARE_DYNAMIC(CReBarCtrl)

// Construction
public:
  CReBarCtrl();
  BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
  
// Attributes
public:
  UINT GetBandCount() const
  { ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, RB_GETBANDCOUNT, 0, 0L); }
  BOOL GetBandInfo(UINT uBand, REBARBANDINFO* prbbi) const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_GETBANDINFO, uBand, (LPARAM)prbbi); }
  UINT GetBarHeight() const
  { ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, RB_GETBARHEIGHT, 0, 0L); }
  BOOL GetBarInfo(REBARINFO* prbi) const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_GETBARINFO, 0, (LPARAM)prbi); }
  COLORREF GetBkColor() const
  { ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, RB_GETBKCOLOR, 0, 0L); }
  IDropTarget* GetDropTarget() const
  { ASSERT(::IsWindow(m_hWnd)); IDropTarget* pdt; ::SendMessage(m_hWnd, RB_GETDROPTARGET, 0, (LPARAM)&pdt); return pdt; }
  BOOL GetRect(UINT uBand, LPRECT prc) const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_GETRECT, uBand, (LPARAM)prc); }
  UINT GetRowCount() const
  { ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, RB_GETROWCOUNT, 0, 0L); }
  UINT GetRowHeight(UINT uRow) const
  { ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, RB_GETROWHEIGHT, uRow, 0L); }
  COLORREF GetTextColor() const
  { ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, RB_GETTEXTCOLOR, 0, 0L); }
  CToolTipCtrl* GetToolTips() const
  { ASSERT(::IsWindow(m_hWnd)); return (CToolTipCtrl*)CWnd::FromHandle((HWND)::SendMessage(m_hWnd, RB_GETTOOLTIPS, 0, 0L)); }
  int IDToIndex(UINT uBandID) const
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, RB_IDTOINDEX, uBandID, 0L); }
  BOOL SetBandInfo(UINT uBand, REBARBANDINFO* prbbi)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_SETBANDINFO, uBand, (LPARAM)prbbi); }
  BOOL SetBarInfo(REBARINFO* prbi)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_SETBARINFO, 0, (LPARAM)prbi); }
  COLORREF SetBkColor(COLORREF clr)
  { ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, RB_SETBKCOLOR, 0, (LPARAM)clr); }
  CWnd* SetOwner(CWnd* pWnd)
  { ASSERT(::IsWindow(m_hWnd)); return CWnd::FromHandle((HWND)::SendMessage(m_hWnd, RB_SETPARENT, (WPARAM)pWnd->m_hWnd, 0L)); }
  COLORREF SetTextColor(COLORREF clr)
  { ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, RB_SETTEXTCOLOR, 0, (LPARAM)clr); }
  void SetToolTips(CToolTipCtrl* pToolTip)
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_SETTOOLTIPS, (WPARAM)pToolTip->m_hWnd, 0L); }
  CImageList* GetImageList() const;
  BOOL SetImageList(CImageList* pImageList);
  void GetBandBorders(UINT uBand, LPRECT prc) const
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_GETBANDBORDERS, uBand, (LPARAM)prc); }
  CPalette* GetPalette() const
  { ASSERT(::IsWindow(m_hWnd)); return CPalette::FromHandle((HPALETTE)::SendMessage(m_hWnd, RB_GETPALETTE, 0, 0L)); }
  CPalette* SetPalette(HPALETTE hPal)
  { ASSERT(::IsWindow(m_hWnd)); return CPalette::FromHandle((HPALETTE)::SendMessage(m_hWnd, RB_SETPALETTE, 0, (LPARAM)hPal)); }
  BOOL GetColorScheme(COLORSCHEME* lpcs);
  void SetColorScheme(const COLORSCHEME* lpcs);
  
// Operations
public:
  void BeginDrag(UINT uBand, DWORD dwPos = (DWORD)-1)
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_BEGINDRAG, uBand, dwPos); }
  BOOL DeleteBand(UINT uBand)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_DELETEBAND, uBand, 0L); }
  void DragMove(DWORD dwPos = (DWORD)-1)
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_DRAGMOVE, 0, dwPos); }
  void EndDrag()
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_ENDDRAG, 0, 0L); }
  int HitTest(RBHITTESTINFO* prbht)
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, RB_HITTEST, 0, (LPARAM)prbht); }
  BOOL InsertBand(UINT uIndex, REBARBANDINFO* prbbi)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_INSERTBAND, uIndex, (LPARAM)prbbi); }
  void MaximizeBand(UINT uBand)
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_MAXIMIZEBAND, uBand, 0L); }
  void MinimizeBand(UINT uBand)
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_MINIMIZEBAND, uBand, 0L); }
  BOOL ShowBand(UINT uBand, BOOL fShow = TRUE)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_SHOWBAND, uBand, fShow); }
  BOOL SizeToRect(CRect& rect)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_SIZETORECT, 0, (LPARAM)&rect); }
  BOOL MoveBand(UINT uFrom, UINT uTo)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_MOVEBAND, uFrom, uTo); }
};

#endif //__RBCTL_H__

/////////////////////////////////////////////////////////////////////////////

