#include <windows.h>
#include "..\coolsb\coolscroll.h"
#include "resource.h"

LRESULT CommandHandler(HWND hwnd, WPARAM wParam, LPARAM lParam);

extern HWND hwndCtrl;

#define VERT_GRIPPER 700
#define GRIPPER 1
#define BUT1	2
#define BUT2	3

HDC			hdcSkin;
HBITMAP		hSkinBmp;

BOOL fCustomDraw  = FALSE;
BOOL fButtons     = FALSE;
BOOL fThumbAlways = FALSE;

BOOL fLeftScroll  = FALSE;
BOOL fEnableCSB   = TRUE;

void InitTest(void)
{
	hdcSkin  = CreateCompatibleDC(0);
	hSkinBmp = (HBITMAP)LoadImage(0, "skin01.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(hdcSkin, hSkinBmp);

//	DeleteEnhMetaFile(hemf);
}

void RedrawNC(HWND hwnd)
{
	SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|
		SWP_FRAMECHANGED|SWP_DRAWFRAME);

}
void ToggleMenuCheck(HMENU menu, UINT menuid)
{
	MENUITEMINFO mii;

	mii.cbSize = sizeof(mii);
	mii.fMask  = MIIM_STATE;
	GetMenuItemInfo(menu, menuid, FALSE, &mii);

	if(mii.fState & MFS_CHECKED)
		CheckMenuItem(menu, menuid, MF_UNCHECKED);
	else
		CheckMenuItem(menu, menuid, MF_CHECKED);
}

void MenuCheckMark (HMENU hmenu, int id, BOOL bCheck)
{
	int iState;
	iState = (bCheck) ? MF_CHECKED : MF_UNCHECKED;
	CheckMenuItem(hmenu, id, iState);
}

void InsertButtons(HWND hwnd)
{
	SCROLLBUT sbut;
	HINSTANCE hInst = GetModuleHandle(0);

	//
	//	Horizontal buttons
	//
	sbut.fMask		= SBBF_ID | SBBF_TYPE | SBBF_SIZE | SBBF_PLACEMENT;// | SBBF_CURSOR;
	sbut.uCmdId		= 0;
	sbut.nSize		= 7;
	sbut.uPlacement = SBBP_LEFT;
	sbut.uButType   = SBBT_FIXED;
//	sbut.hCurs		= LoadCursor(hInst, MAKEINTRESOURCE(IDC_SIZELR));
	
	CoolSB_InsertButton(hwnd, SB_HORZ, (UINT)-1, &sbut);
	
	
	sbut.fMask		= SBBF_ID | SBBF_TYPE | SBBF_SIZE | SBBF_PLACEMENT;
	sbut.uCmdId		= 650;
	sbut.nSize		= -1;
	sbut.uPlacement = SBBP_LEFT;
	sbut.uButType   = SBBT_PUSHBUTTON | SBBM_LEFTARROW;
	CoolSB_InsertButton(hwnd, SB_HORZ, (UINT)-1, &sbut);
	
	
	sbut.fMask		= SBBF_ID | SBBF_TYPE | SBBF_SIZE | SBBF_PLACEMENT;
	sbut.uCmdId		= 651;
	sbut.nSize		= -1;
	sbut.uPlacement = SBBP_LEFT;
	sbut.uButType   = SBBT_PUSHBUTTON | SBBM_RIGHTARROW;
	CoolSB_InsertButton(hwnd, SB_HORZ, (UINT)-1, &sbut);
	
	sbut.fMask		= SBBF_ID | SBBF_TYPE | SBBF_SIZE | SBBF_PLACEMENT ;
	sbut.uCmdId		= 666;
	sbut.nSize		= 120;
	sbut.uPlacement = SBBP_LEFT;
	sbut.uButType   = SBBT_OWNERDRAW | SBBM_RESIZABLE;//SBBT_PUSHBUTTON2;
	sbut.nMinSize	= 0;
	sbut.nMaxSize	= (UINT)-1;
	
	CoolSB_InsertButton(hwnd, SB_HORZ, (UINT)-1, &sbut);
	
	
	sbut.fMask		= SBBF_ID | SBBF_TYPE | SBBF_SIZE | SBBF_PLACEMENT;// | SBBF_CURSOR;
	sbut.uCmdId		= 668;
	sbut.nSize		= 5;
	sbut.uPlacement = SBBP_LEFT;
	sbut.uButType   = SBBT_FIXED;
	//sbut.hCurs		= LoadCursor(hInst, MAKEINTRESOURCE(IDC_SIZELR));
	CoolSB_InsertButton(hwnd, SB_HORZ, (UINT)-1, &sbut);
	
	//
	//	Vertical buttons
	//
	sbut.fMask		= SBBF_ID | SBBF_TYPE | SBBF_SIZE | SBBF_PLACEMENT | SBBF_BITMAP;
	sbut.uCmdId		= 680;
	sbut.nSize		= -1;
	sbut.uPlacement = SBBP_RIGHT;
	sbut.uButType   = SBBT_PUSHBUTTON | SBBM_TYPE2 | SBBM_RECESSED;
	sbut.hBmp		= LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	CoolSB_InsertButton(hwnd, SB_VERT, (UINT)-1, &sbut);
	
	sbut.uCmdId		= 681;
	sbut.nSize		= -1;
	sbut.uPlacement = SBBP_RIGHT;
	sbut.uButType   = SBBT_TOGGLEBUTTON | SBBM_TYPE2 | SBBM_RECESSED;
	CoolSB_InsertButton(hwnd, SB_VERT, (UINT)-1, &sbut);
	
	sbut.fMask		= SBBF_ID | SBBF_TYPE | SBBF_SIZE | SBBF_PLACEMENT;// | SBBF_CURSOR;
	sbut.uCmdId		= VERT_GRIPPER;
	sbut.nSize		= 7;
	sbut.uPlacement = SBBP_LEFT;
	sbut.uButType   = SBBT_FIXED;
	//sbut.hCurs		= LoadCursor(hInst, MAKEINTRESOURCE(IDC_SIZEUD));
	CoolSB_InsertButton(hwnd, SB_VERT, (UINT)-1, &sbut);
	
//	InitMetaFile();		
	
	CoolSB_ModifyButton(hwnd, SB_HORZ, (UINT)-1,0, &sbut);
}

void RemoveButtons(HWND hwnd)
{
	CoolSB_RemoveButton(hwnd, SB_HORZ, 0, FALSE);
	CoolSB_RemoveButton(hwnd, SB_HORZ, 0, FALSE);
	CoolSB_RemoveButton(hwnd, SB_HORZ, 0, FALSE);
	CoolSB_RemoveButton(hwnd, SB_HORZ, 0, FALSE);
	CoolSB_RemoveButton(hwnd, SB_HORZ, 0, FALSE);
	CoolSB_RemoveButton(hwnd, SB_VERT, 0, FALSE);
	CoolSB_RemoveButton(hwnd, SB_VERT, 0, FALSE);
	CoolSB_RemoveButton(hwnd, SB_VERT, 0, FALSE);
}

LRESULT CommandHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	HMENU hmenu = GetMenu(hwnd);

	if(LOWORD(wParam) == VK_ESCAPE)
	{
		EndDialog(hwnd, 0);
		return 0;
	}
	
	switch(LOWORD (wParam))
	{
	case ID_VIEW_NORMAL:
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_NORMAL);
		MenuCheckMark(hmenu, ID_VIEW_NORMAL, TRUE);
		MenuCheckMark(hmenu, ID_VIEW_FLAT, FALSE);
		MenuCheckMark(hmenu, ID_VIEW_HOTTRACKED, FALSE);
		
		return 0;
		
	case ID_VIEW_FLAT:
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_FLAT);
		MenuCheckMark(hmenu, ID_VIEW_NORMAL, FALSE);
		MenuCheckMark(hmenu, ID_VIEW_FLAT, TRUE);
		MenuCheckMark(hmenu, ID_VIEW_HOTTRACKED, FALSE);
		
		return 0;
		
	case ID_VIEW_HOTTRACKED:
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_HOTTRACKED);
		MenuCheckMark(hmenu, ID_VIEW_NORMAL, FALSE);
		MenuCheckMark(hmenu, ID_VIEW_FLAT, FALSE);
		MenuCheckMark(hmenu, ID_VIEW_HOTTRACKED, TRUE);
		
		return 0;
		
	case ID_VIEW_CUSTOMDRAW:
		fCustomDraw = !fCustomDraw;
		ToggleMenuCheck(hmenu, ID_VIEW_CUSTOMDRAW);
		
		if(fCustomDraw)
		{
			CoolSB_SetSize(hwndCtrl, SB_BOTH, 18, 18);
			CoolSB_SetMinThumbSize(hwndCtrl, SB_BOTH, 18);
		}
		else
		{
			CoolSB_SetSize(hwndCtrl, SB_BOTH, SYSTEM_METRIC, SYSTEM_METRIC);
			CoolSB_SetMinThumbSize(hwndCtrl, SB_BOTH, (UINT)-1);
		}
		
		RedrawNC(hwndCtrl);
		return 0;
		
	case ID_VIEW_INSERTEDBUTTONS:
		fButtons = !fButtons;
		ToggleMenuCheck(hmenu, ID_VIEW_INSERTEDBUTTONS);
		
		if(fButtons)
			InsertButtons(hwndCtrl);
		else
			RemoveButtons(hwndCtrl);
		
		RedrawNC(hwndCtrl);
		return 0;
		
	case ID_VIEW_THUMBALWAYS:
		fThumbAlways = !fThumbAlways;
		ToggleMenuCheck(hmenu, ID_VIEW_THUMBALWAYS);
		
		CoolSB_SetThumbAlways(hwndCtrl, SB_BOTH, fThumbAlways);

		RedrawNC(hwndCtrl);
		return 0;
		
	case ID_VIEW_ENABLE:
		fEnableCSB = !fEnableCSB;
		ToggleMenuCheck(hmenu, ID_VIEW_ENABLE);

		if(fEnableCSB)
			InitializeCoolSB(hwndCtrl);
		else
			UninitializeCoolSB(hwndCtrl);

		return 0;

	case ID_VIEW_LEFTSCROLLBAR:
		fLeftScroll = !fLeftScroll;
		ToggleMenuCheck(hmenu, ID_VIEW_LEFTSCROLLBAR);
		
		if(fLeftScroll)
			SetWindowLong(hwndCtrl, GWL_EXSTYLE, WS_EX_CLIENTEDGE |  WS_EX_LEFTSCROLLBAR);
		else
			SetWindowLong(hwndCtrl, GWL_EXSTYLE, WS_EX_CLIENTEDGE & ~WS_EX_LEFTSCROLLBAR);

		return 0;

	case IDM_FILE_ABOUT:
		MessageBox(hwnd, "Cool Scrollbar library\n\rBy J Brown", "CoolScroll Demo", MB_OK | MB_ICONINFORMATION);
		return 0;
		
	case IDCANCEL: 
		EndDialog(hwnd, 0);
		break;
	}

	return 0;
}
