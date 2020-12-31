#if !defined(AFX_LISTCTRLEX_H_INCLUDED)
#define AFX_LISTCTRLEX_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx definitions

#ifndef NOLISTVIEWEX

#define LVIS_ACTIVATING         0x0020

#define LVS_EX_FLATSB           0x00000100
#define LVS_EX_REGIONAL         0x00000200
#define LVS_EX_INFOTIP          0x00000400
#define LVS_EX_UNDERLINEHOT     0x00000800
#define LVS_EX_UNDERLINECOLD    0x00001000
#define LVS_EX_MULTIWORKAREAS   0x00002000

#define LV_MAX_WORKAREAS         16                          
#define LVM_SETWORKAREAS         (LVM_FIRST + 65)
#define ListView_SetWorkAreas(hwnd, nWorkAreas, prc) \
    (BOOL)SNDMSG((hwnd), LVM_SETWORKAREAS, (WPARAM)(int)nWorkAreas, (LPARAM)(RECT FAR*)(prc))

#define LVM_GETWORKAREAS        (LVM_FIRST + 70)
#define ListView_GetWorkAreas(hwnd, nWorkAreas, prc) \
    (BOOL)SNDMSG((hwnd), LVM_GETWORKAREAS, (WPARAM)(int)nWorkAreas, (LPARAM)(RECT FAR*)(prc))

#define LVM_GETNUMBEROFWORKAREAS  (LVM_FIRST + 73)
#define ListView_GetNumberOfWorkAreas(hwnd, pnWorkAreas) \
    (BOOL)SNDMSG((hwnd), LVM_GETNUMBEROFWORKAREAS, 0, (LPARAM)(UINT *)(pnWorkAreas))

#define LVM_GETSELECTIONMARK    (LVM_FIRST + 66)
#define ListView_GetSelectionMark(hwnd) \
    (int)SNDMSG((hwnd), LVM_GETSELECTIONMARK, 0, 0)

#define LVM_SETSELECTIONMARK    (LVM_FIRST + 67)
#define ListView_SetSelectionMark(hwnd, i) \
    (int)SNDMSG((hwnd), LVM_SETSELECTIONMARK, 0, (LPARAM)i)

#define LVM_SETHOVERTIME        (LVM_FIRST + 71)
#define ListView_SetHoverTime(hwndLV, dwHoverTimeMs)\
        (DWORD)SendMessage((hwndLV), LVM_SETHOVERTIME, 0, dwHoverTimeMs)

#define LVM_GETHOVERTIME        (LVM_FIRST + 72)
#define ListView_GetHoverTime(hwndLV)\
        (DWORD)SendMessage((hwndLV), LVM_GETHOVERTIME, 0, 0)

#define LVM_SETTOOLTIPS       (LVM_FIRST + 74)
#define ListView_SetToolTips(hwndLV, hwndNewHwnd)\
        (HWND)SendMessage((hwndLV), LVM_SETTOOLTIPS, hwndNewHwnd, 0)

#define LVM_GETTOOLTIPS       (LVM_FIRST + 78)
#define ListView_GetToolTips(hwndLV)\
        (HWND)SendMessage((hwndLV), LVM_GETTOOLTIPS, 0, 0)

typedef struct tagLVBKIMAGEA
{
    ULONG ulFlags;
    HBITMAP hbm;
    LPSTR pszImage;
    UINT cchImageMax;
    int xOffsetPercent;
    int yOffsetPercent;
} LVBKIMAGEA, FAR *LPLVBKIMAGEA;
typedef struct tagLVBKIMAGEW
{
    ULONG ulFlags;
    HBITMAP hbm;
    LPWSTR pszImage;
    UINT cchImageMax;
    int xOffsetPercent;
    int yOffsetPercent;
} LVBKIMAGEW, FAR *LPLVBKIMAGEW;

#define LVBKIF_SOURCE_NONE      0x00000000
#define LVBKIF_SOURCE_HBITMAP   0x00000001
#define LVBKIF_SOURCE_URL       0x00000002
#define LVBKIF_SOURCE_MASK      0x00000003
#define LVBKIF_STYLE_NORMAL     0x00000000
#define LVBKIF_STYLE_TILE       0x00000010
#define LVBKIF_STYLE_MASK       0x00000010

#define LVM_SETBKIMAGEA         (LVM_FIRST + 68)
#define LVM_SETBKIMAGEW         (LVM_FIRST + 138)
#define LVM_GETBKIMAGEA         (LVM_FIRST + 69)
#define LVM_GETBKIMAGEW         (LVM_FIRST + 139)

#ifdef UNICODE
#define LVBKIMAGE               LVBKIMAGEW
#define LPLVBKIMAGE             LPLVBKIMAGEW
#define LVM_SETBKIMAGE          LVM_SETBKIMAGEW
#define LVM_GETBKIMAGE          LVM_GETBKIMAGEW
#else
#define LVBKIMAGE               LVBKIMAGEA
#define LPLVBKIMAGE             LPLVBKIMAGEA
#define LVM_SETBKIMAGE          LVM_SETBKIMAGEA
#define LVM_GETBKIMAGE          LVM_GETBKIMAGEA
#endif

#define ListView_SetBkImage(hwnd, plvbki) \
    (BOOL)SNDMSG((hwnd), LVM_SETBKIMAGE, 0, (LPARAM)plvbki)

#define ListView_GetBkImage(hwnd, plvbki) \
    (BOOL)SNDMSG((hwnd), LVM_GETBKIMAGE, 0, (LPARAM)plvbki)

typedef struct tagNMITEMACTIVATE
{
    NMHDR   hdr;
    int     iItem;
    int     iSubItem;
    UINT    uNewState;
    UINT    uOldState;
    UINT    uChanged;
    POINT   ptAction;
    LPARAM  lParam;
    UINT    uKeyFlags;
} NMITEMACTIVATE, FAR *LPNMITEMACTIVATE;

#define LVKF_ALT       0x0001
#define LVKF_CONTROL   0x0002
#define LVKF_SHIFT     0x0004

#define LVN_HOTTRACK            (LVN_FIRST-21)

typedef struct tagNMLVGETINFOTIPA
{
    NMHDR hdr;
    DWORD dwFlags;
    LPSTR pszText;
    int cchTextMax;
    int iItem;
    int iSubItem;
    LPARAM lParam;
} NMLVGETINFOTIPA, *LPNMLVGETINFOTIPA;

typedef struct tagNMLVGETINFOTIPW
{
    NMHDR hdr;
    DWORD dwFlags;
    LPWSTR pszText;
    int cchTextMax;
    int iItem;
    int iSubItem;
    LPARAM lParam;
} NMLVGETINFOTIPW, *LPNMLVGETINFOTIPW;

#define LVGIT_UNFOLDED  0x0001

#define LVN_GETINFOTIPA          (LVN_FIRST-57)
#define LVN_GETINFOTIPW          (LVN_FIRST-58)

#ifdef UNICODE
#define LVN_GETINFOTIP          LVN_GETINFOTIPW
#define NMLVGETINFOTIP          NMLVGETINFOTIPW
#define LPNMLVGETINFOTIP        LPNMLVGETINFOTIPW
#else
#define LVN_GETINFOTIP          LVN_GETINFOTIPA
#define NMLVGETINFOTIP          NMLVGETINFOTIPA
#define LPNMLVGETINFOTIP        LPNMLVGETINFOTIPA
#endif

#endif // NOLISTVIEWEX

// ListCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window

class CListCtrlEx : public CListCtrl
{
// Construction

// Attributes
public:
	int AddItem(LPCTSTR strItem, int nItem, int nSubItem = 0, UINT nState = -1, int nImageIndex = -1, long nParam = -1);
	DWORD GetViewStyle() const;
	DWORD SetViewStyle(DWORD dwNewView);


	// Available with IE4 Dll => commctl.dll v4.71.1712.3
#ifndef NOLISTVIEWEX
	POSITION GetFirstSelectedItemPosition() const;
	int GetNextSelectedItem(POSITION &pos) const;
	BOOL GetColumnOrderArray(LPINT pnArray, int nCount = -1) const;
	BOOL SetColumnOrderArray(int nCount, LPINT pnArray);	
	CSize SetIconSpacing(CSize size);
	CSize SetIconSpacing(int cx, int cy);
	CHeaderCtrl* GetHeaderCtrl() const;
	HCURSOR GetHotCursor() const;
	HCURSOR SetHotCursor(HCURSOR hc);
	BOOL GetSubItemRect(int nItem, int nSubItem, int nArea, CRect& rcRef) const;
	int GetHotItem() const;
	int SetHotItem(int nIndex);
	int GetSelectionMark() const;
	int SetSelectionMark(int nIndex);
	DWORD GetExtendedStyle() const;
	DWORD SetExtendedStyle(DWORD dwNewStyle);
	int SubItemHitTest(LPLVHITTESTINFO lpInfo);
	UINT GetNumberOfWorkAreas() const;
	void GetWorkAreas(int nWorkAreas, LPRECT lpRect) const;
	void SetWorkAreas(int nWorkAreas, LPRECT lpRect);
	BOOL SetItemCountEx(int iCount, DWORD dwFlags = LVSICF_NOINVALIDATEALL);	
	CSize ApproximateViewRect(CSize size = CSize(-1, -1), int nCount = -1) const;
	BOOL GetBkImage(LVBKIMAGE* plvbkImage) const;		
	BOOL SetBkImage(HBITMAP hbm, BOOL bTile = TRUE, int xOffsetPercent = 0, int yOffsetPercent = 0);
	BOOL SetBkImage(LPTSTR pszUrl, BOOL bTile = TRUE, int xOffsetPercent = 0, int yOffsetPercent = 0);
	BOOL SetBkImage(LVBKIMAGE* plvbkImage);
	DWORD GetHoverTime() const;
	DWORD SetHoverTime(DWORD dwHoverTime = -1);
	BOOL GetCheck(int nItem) const;
	BOOL SetCheck(int nItem, BOOL bCheck);
#endif // NOLISTVIEWEX

// Operations

// Overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CListCtrlEx)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_LISTCTRLEX_H_INCLUDED)
