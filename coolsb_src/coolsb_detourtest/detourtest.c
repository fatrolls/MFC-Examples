#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>

#include "resource.h"
#include "..\coolsb\coolscroll.h"
#include "..\coolsb_detours\coolsb_detours.h"

#pragma comment (lib, "detours.lib")


void PopulateItem( HWND hTree, HTREEITEM hParent, int childs, int depth )
{
    int i;
    char szText[32];
    TV_INSERTSTRUCT tvis;

	for(i = 0; i < childs; i++)
	{
        wsprintf(szText, "Item %d - %d", depth, i);
                            
        tvis.hParent = hParent;
        tvis.hInsertAfter = TVI_LAST;
        tvis.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_STATE;
        tvis.item.pszText = (LPTSTR) szText;
        tvis.item.iImage = 0;
        tvis.item.iSelectedImage = 0;
        tvis.item.state = 0;
        tvis.item.stateMask = 0;
        tvis.item.lParam = i;

        if ( depth > 0 )
            PopulateItem(hTree, TreeView_InsertItem(hTree, &tvis), childs, depth-1);
    }

    TreeView_Expand(hTree, hParent, TVE_EXPAND);
}



BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndCtrl;
	LVCOLUMN lvcol;

	int i;
	char szText[32];

	switch(msg)
	{
	case WM_INITDIALOG:

		//
		//	Apply Cool Scrollbars to EDIT control
		//
		hwndCtrl = GetDlgItem(hwnd, IDC_EDIT1);
	
		InitializeCoolSB(hwndCtrl);
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_HOTTRACKED);

		//
		//	Apply Cool Scrollbars to LISTBOX control
		//
		hwndCtrl = GetDlgItem(hwnd, IDC_LIST1);
		
		InitializeCoolSB(hwndCtrl);
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_HOTTRACKED);

		for(i = 0; i < 50; i++)
		{
			wsprintf(szText, "Line %d", i);
			SendMessage(hwndCtrl, LB_ADDSTRING, 0, (LONG)szText);
		}


		//
		//	Apply Cool Scrollbars to LISTVIEW control
		//
		hwndCtrl = GetDlgItem(hwnd, IDC_LIST2);

		lvcol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT;
		lvcol.cx   = 64;
		lvcol.iSubItem = 0;
		lvcol.pszText = "Name";
		ListView_InsertColumn(hwndCtrl, 0, &lvcol);
		
		lvcol.pszText = "Size";
		lvcol.cx   = 64;
		lvcol.fmt  = LVCFMT_RIGHT;
		ListView_InsertColumn(hwndCtrl, 1, &lvcol);

		for(i = 0; i < 50; i++)
		{
			LVITEM lvitem;

			lvitem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
			lvitem.iSubItem = 0;
			lvitem.pszText = "item";
			lvitem.iItem = i;
			lvitem.state = 0;
			lvitem.stateMask = 0;

			ListView_InsertItem(hwndCtrl, &lvitem);
	
			wsprintf(szText, "%d", i);
			ListView_SetItemText(hwndCtrl, i, 1, szText);
		}

        InitializeCoolSB(hwndCtrl);
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_HOTTRACKED);
        
        //
		//	Apply Cool Scrollbars to a TREEVIEW control!
		//
		hwndCtrl = GetDlgItem(hwnd, IDC_TREE);
        PopulateItem( hwndCtrl, TVI_ROOT, 2, 10 );

        InitializeCoolSB(hwndCtrl);
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_HOTTRACKED);

		return TRUE;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK: case IDCANCEL:
			EndDialog(hwnd, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nShowCmd)
{
	CoolSB_InitializeApp();
	
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	CoolSB_UninitializeApp();

	return 0;
}
/*
#include <windows.h>
#include <commctrl.h>

#include "resource.h"
#include "..\coolsb\coolscroll.h"
#include "..\coolsb_detours\coolsb_detours.h"

#pragma comment (lib, "..\\coolsb_detours\\detours.lib")

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndCtrl;
	LVCOLUMN lvcol;

	int i;
	char szText[32];

	switch(msg)
	{
	case WM_INITDIALOG:

		//
		//	Apply Cool Scrollbars to EDIT control
		//
		hwndCtrl = GetDlgItem(hwnd, IDC_EDIT1);
	
		InitializeCoolSB(hwndCtrl);
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_HOTTRACKED);

		//
		//	Apply Cool Scrollbars to LISTBOX control
		//
		hwndCtrl = GetDlgItem(hwnd, IDC_LIST1);
		
		InitializeCoolSB(hwndCtrl);
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_HOTTRACKED);

		for(i = 0; i < 50; i++)
		{
			wsprintf(szText, "Line %d", i);
			SendMessage(hwndCtrl, LB_ADDSTRING, 0, (LONG)szText);
		}


		//
		//	Apply Cool Scrollbars to LISTVIEW control
		//
		hwndCtrl = GetDlgItem(hwnd, IDC_LIST2);

		lvcol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT;
		lvcol.cx   = 64;
		lvcol.iSubItem = 0;
		lvcol.pszText = "Name";
		ListView_InsertColumn(hwndCtrl, 0, &lvcol);
		
		lvcol.pszText = "Size";
		lvcol.cx   = 64;
		lvcol.fmt  = LVCFMT_RIGHT;
		ListView_InsertColumn(hwndCtrl, 1, &lvcol);

		for(i = 0; i < 50; i++)
		{
			LVITEM lvitem;

			lvitem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
			lvitem.iSubItem = 0;
			lvitem.pszText = "item";
			lvitem.iItem = i;
			lvitem.state = 0;
			lvitem.stateMask = 0;

			ListView_InsertItem(hwndCtrl, &lvitem);
	
			wsprintf(szText, "%d", i);
			ListView_SetItemText(hwndCtrl, i, 1, szText);
		}

		InitializeCoolSB(hwndCtrl);
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_HOTTRACKED);

		return TRUE;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK: case IDCANCEL:
			EndDialog(hwnd, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nShowCmd)
{
	CoolSB_InitializeApp();
	
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	CoolSB_UninitializeApp();

	return 0;
}*/