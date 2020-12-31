#include <windows.h>
#include <commctrl.h>
#include "..\coolsb\coolscroll.h"

UINT CALLBACK CoolSB_DrawProc(HDC hdc, UINT uCmdId, UINT uButflags, RECT *rect);
extern HWND hwndScroll;

extern BOOL fCustomDraw  ;
extern BOOL fButtons     ;
extern BOOL fThumbAlways ;
extern HDC hdcSkin;

HPEN hpen, oldpen;
HPEN whitepen;
HFONT hfont;
HENHMETAFILE hemf=0;

typedef struct 
{
	int x, y;
	int width, height;
} CustomDrawTable;

//
//	Define a set of structures which describe
//	where-abouts the source "textures" are in the
//	custom draw bitmap. We need to know x, y, width and height
//	for each scrollbar segment.
//

CustomDrawTable cdt_horz_normal[] = 
{
	{ 0,  0,  18, 18 },	//left arrow  NORMAL
	{ 0,  19, 18, 18 }, //right arrow NORMAL
	{ 0,  83, 1,  18 }, //page left   NORMAL
	{ 0,  83, 1,  18 }, //page right  NORMAL
	
	{ -1, -1, -1, -1 },	//padding

	{ 54, 0,  9,  18 }, //horz thumb (left)
	{ 54+9, 0, 1, 18 }, //horz thumb (middle)
	{ 54+9, 0, 9, 18 }, //horz thumb (right)
};

CustomDrawTable cdt_horz_hot[] = 
{
	{ 18, 0,  18, 18 }, //left arrow  ACTIVE
	{ 18, 19, 18, 18 }, //right arrow ACTIVE
	{ 4,  83, 1,  18 }, //page left   ACTIVE
	{ 4,  83, 1,  18 }, //page right  ACTIVE

	{ -1, -1, -1, -1 },	//padding

	{ 54,   19, 9, 18 }, //horz thumb (left)
	{ 54+9, 19, 1, 18 }, //horz thumb (middle)
	{ 54+9, 19, 9, 18 }, //horz thumb (right)
};

CustomDrawTable cdt_horz_active[] = 
{
	{ 36, 0,  18, 18 }, //left arrow  ACTIVE
	{ 36, 19, 18, 18 }, //right arrow ACTIVE
	{ 4,  83, 1,  18 }, //page left   ACTIVE
	{ 4,  83, 1,  18 }, //page right  ACTIVE

	{ -1, -1, -1, -1 },	//padding

	{ 54,   38, 9, 18 }, //horz thumb (left)
	{ 54+9, 38, 1, 18 }, //horz thumb (middle)
	{ 54+9, 38, 9, 18 }, //horz thumb (right)
};

CustomDrawTable cdt_vert_normal[] = 
{
	{ 72, 0,  18, 18 }, //up arrow   NORMAL
	{ 72, 19, 18, 18 }, //down arrow NORMAL
	{ 0,  112, 18, 1 }, //page up	 NORMAL
	{ 0,  112, 18, 1 }, //page down  NORMAL

	{ -1, -1, -1, -1 },	//padding

	{ 126, 0,  18, 9  }, //vert thumb (left)
	{ 126, 9,  18, 1  }, //vert thumb (middle)
	{ 126, 9,  18, 9  }, //vert thumb (right)
};

CustomDrawTable cdt_vert_hot[] = 
{
	{ 90, 0,  18, 18 }, //up arrow   ACTIVE
	{ 90, 19, 18, 18 }, //down arrow ACTIVE
	{ 4,  83, 18, 1  }, //page up	 ACTIVE
	{ 4,  83, 18, 1  }, //page down  ACTIVE

	{ -1, -1, -1, -1 },	//padding

	{ 126, 19,  18, 9  }, //vert thumb (left)
	{ 126, 28,  18, 1  }, //vert thumb (middle)
	{ 126, 28,  18, 9  }, //vert thumb (right)
};

CustomDrawTable cdt_vert_active[] = 
{
	{ 108, 0,  18, 18 }, //up arrow   ACTIVE
	{ 108, 19, 18, 18 }, //down arrow ACTIVE
	{ 4,  83, 18, 1  }, //page up	 ACTIVE
	{ 4,  83, 18, 1  }, //page down  ACTIVE

	{ -1, -1, -1, -1 },	//padding

	{ 126, 38,  18, 9  }, //vert thumb (left)
	{ 126, 47,  18, 1  }, //vert thumb (middle)
	{ 126, 47,  18, 9  }, //vert thumb (right)
};

LRESULT HandleCustomDraw(UINT ctrlid, NMCSBCUSTOMDRAW *nm)
{
	RECT *rc;
	CustomDrawTable *cdt;
	UINT code = NM_CUSTOMDRAW;

	UNREFERENCED_PARAMETER(ctrlid);

	// inserted buttons do not use PREPAINT etc..
	if(nm->nBar == SB_INSBUT)
	{
		CoolSB_DrawProc(nm->hdc, nm->uItem, nm->uState, &nm->rect);
		return CDRF_SKIPDEFAULT;
	}

	if(!fCustomDraw) return CDRF_DODEFAULT;

	if(nm->dwDrawStage == CDDS_PREPAINT)
	{
		if(fCustomDraw)
			return CDRF_SKIPDEFAULT;
		else
			return CDRF_DODEFAULT;
	}

	if(nm->dwDrawStage == CDDS_POSTPAINT)
	{
		
	}

	//the sizing gripper in the bottom-right corner
	if(nm->nBar == SB_BOTH)	
	{
		RECT *rc = &nm->rect;
		
		StretchBlt(nm->hdc, rc->left, rc->top, rc->right-rc->left, rc->bottom-rc->top,
			hdcSkin, 100, 100, 18, 18, SRCCOPY);
				
		return CDRF_SKIPDEFAULT;
	}
	else if(nm->nBar == SB_HORZ)
	{
		rc = &nm->rect;

		if(nm->uState == CDIS_HOT)	
			cdt = &cdt_horz_hot[nm->uItem];
		else if(nm->uState == CDIS_SELECTED) 
			cdt = &cdt_horz_active[nm->uItem];
		else				   
			cdt = &cdt_horz_normal[nm->uItem];
		
		if(nm->uItem == HTSCROLL_THUMB)
		{
			StretchBlt(nm->hdc, rc->left,   rc->top, 9, rc->bottom-rc->top, hdcSkin, cdt->x, cdt->y, cdt->width, cdt->height, SRCCOPY);
			cdt++;
			StretchBlt(nm->hdc, rc->left+9, rc->top, (rc->right-rc->left)-18, rc->bottom-rc->top, hdcSkin, cdt->x, cdt->y, cdt->width, cdt->height, SRCCOPY);
			cdt++;
			StretchBlt(nm->hdc, rc->left+(rc->right-rc->left)-9, rc->top, 9, rc->bottom-rc->top, hdcSkin, cdt->x, cdt->y, cdt->width, cdt->height, SRCCOPY);
			return CDRF_SKIPDEFAULT;
		}

	}
	else if(nm->nBar == SB_VERT)
	{
		rc = &nm->rect;

		if(nm->uState == CDIS_HOT)		
			cdt = &cdt_vert_hot[nm->uItem];
		else if(nm->uState == CDIS_SELECTED)  
			cdt = &cdt_vert_active[nm->uItem];
		else				    
			cdt = &cdt_vert_normal[nm->uItem];

		if(nm->uItem == HTSCROLL_THUMB)
		{
			StretchBlt(nm->hdc, rc->left, rc->top,   rc->right-rc->left, 9, hdcSkin, cdt->x, cdt->y, cdt->width, cdt->height, SRCCOPY);
			cdt++;
			StretchBlt(nm->hdc, rc->left, rc->top+9, rc->right-rc->left, (rc->bottom-rc->top)-18, hdcSkin, cdt->x, cdt->y, cdt->width, cdt->height, SRCCOPY);
			cdt++;			
			StretchBlt(nm->hdc, rc->left, rc->top+(rc->bottom-rc->top)-9, rc->right-rc->left, 9,hdcSkin, cdt->x, cdt->y, cdt->width, cdt->height, SRCCOPY);
			return CDRF_SKIPDEFAULT;
		}
	}
	//INSERTED BUTTONS are handled here...
	else if(nm->nBar == SB_INSBUT)
	{
		CoolSB_DrawProc(nm->hdc, nm->uItem, nm->uState, &nm->rect);
		return CDRF_SKIPDEFAULT;
	}
	else
	{
		return CDRF_DODEFAULT;
	}

	//normal bitmaps, use same code for HORZ and VERT
	StretchBlt(nm->hdc, rc->left, rc->top, rc->right-rc->left, rc->bottom-rc->top,
		hdcSkin, cdt->x, cdt->y, cdt->width, cdt->height, SRCCOPY);

	return CDRF_SKIPDEFAULT;

}

void DrawTab(HDC hdcEMF, int x, int tabwidth, int tabheight, int xslope, BOOL active)
{
	POINT pts[4];

	pts[0].x = x + 0;
	pts[0].y = 0;
	pts[1].x = x + xslope;
	pts[1].y = tabheight;
	pts[2].x = x + tabwidth - xslope;
	pts[2].y = tabheight;
	pts[3].x = x + tabwidth;
	pts[3].y = 0;

	if(active)
		SelectObject(hdcEMF, GetStockObject(WHITE_BRUSH));
	else
		SelectObject(hdcEMF, GetSysColorBrush(COLOR_3DFACE));

	Polygon(hdcEMF, pts, 4);

	oldpen = SelectObject(hdcEMF, hpen);
	
	MoveToEx(hdcEMF, pts[1].x+1, pts[1].y, 0);
	LineTo(hdcEMF, pts[2].x, pts[2].y);
	
	if(active)
		SelectObject(hdcEMF, whitepen);

	MoveToEx(hdcEMF, pts[3].x - 1, pts[3].y, 0);
	LineTo(hdcEMF, pts[0].x, pts[0].y);

	
	SelectObject(hdcEMF, oldpen);

}

//
//	Draw a series of "tabs" into a meta-file,
//	which we will use to custom-draw one of the inserted
//  scrollbar buttons
//
void InitMetaFile(void)
{
	HDC hdcEMF;
	RECT rect;
	int totalwidth = 120;
	int width = 110, height = GetSystemMetrics(SM_CYHSCROLL);
	LOGFONT lf;

	POINT pts[4];

	int tabwidth = 40, tabxslope = 5;

	pts[0].x = 0;
	pts[0].y = 0;
	pts[1].x = tabxslope;
	pts[1].y = height - 1;
	pts[2].x = tabwidth - tabxslope;
	pts[2].y = height - 1;
	pts[3].x = tabwidth;
	pts[3].y = 0;

	hpen = CreatePen(PS_SOLID,0,GetSysColor(COLOR_3DSHADOW));
	whitepen = CreatePen(PS_INSIDEFRAME,0,RGB(0xff,0xff,0xff));

	SetRect(&rect, 0, 0, totalwidth, height+1);
	
	hdcEMF = CreateEnhMetaFile(NULL, NULL, NULL, NULL);
	
	ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = -MulDiv(7, GetDeviceCaps(hdcEMF, LOGPIXELSY), 72);
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	lf.lfCharSet = ANSI_CHARSET;
	lstrcpy(lf.lfFaceName, "Arial");//Small fonts");
	hfont = CreateFontIndirect(&lf);

	pts[0].x = 0;
	pts[0].y = 0;
	pts[1].x = tabxslope;
	pts[1].y = height - 1;
	pts[2].x = tabwidth - tabxslope;
	pts[2].y = height - 1;
	pts[3].x = tabwidth;
	pts[3].y = 0;
	
	FillRect  (hdcEMF, &rect, GetSysColorBrush(COLOR_3DFACE));//GetStockObject(WHITE_BRUSH);

	//fit as many lines in as space permits

	SelectObject(hdcEMF, GetSysColorBrush(COLOR_3DFACE));

	DrawTab(hdcEMF, width-tabwidth, tabwidth, height - 1, tabxslope, FALSE);
	DrawTab(hdcEMF, width-tabwidth-tabwidth+tabxslope, tabwidth, height - 1, tabxslope, FALSE);
	DrawTab(hdcEMF, 0, tabwidth, height - 1, tabxslope, TRUE);
	
	SelectObject(hdcEMF, hpen);
	MoveToEx(hdcEMF, 110, 0, 0);
	LineTo(hdcEMF, totalwidth, 0);


	SelectObject(hdcEMF, hfont);
	SetBkMode(hdcEMF, TRANSPARENT);
	TextOut(hdcEMF, 10,1, "Build", 5);

	TextOut(hdcEMF, 42,1, "Debug", 5);
	TextOut(hdcEMF, 78,1, "Result", 6);

	SelectObject(hdcEMF, oldpen);
	DeleteObject(hpen);
	DeleteObject(whitepen);
	hemf  = CloseEnhMetaFile(hdcEMF);
}

//
//	function for drawing the custom-draw inserted buttons
//	Called from the WM_NOTIFY handler (HandleCustomDraw)
//
UINT CALLBACK CoolSB_DrawProc(HDC hdc, UINT uCmdId, UINT uButflags, RECT *rect)
{
	RECT rc;
	POINT pt;
	HPEN hpen, hold;

	HBITMAP hbm, oldbm;
	HDC hdcmem;

	if(hemf == 0)
		InitMetaFile();

	SetRect(&rc, 0, 0, 120, rect->bottom-rect->top);

	hdcmem = CreateCompatibleDC(hdc);
	hbm = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	oldbm = SelectObject(hdcmem, hbm);

	SetWindowOrgEx(hdc, -rect->left, -rect->top, &pt);
	PlayEnhMetaFile(hdcmem, hemf, &rc);
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcmem, 0, 0, SRCCOPY);
	
	SetRect(&rc, 120, 0, rect->right-rect->left, rect->bottom-rect->top);
	FillRect(hdc, &rc, GetSysColorBrush(COLOR_3DFACE));
	
	hpen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DSHADOW));
	hold = SelectObject(hdc, hpen);
	MoveToEx(hdc, 120, 0, 0);
	LineTo(hdc, rect->right-rect->left, 0);
	
	SetWindowOrgEx(hdc, pt.x, pt.y, 0);		

	
	SelectObject(hdc, hold);
	SelectObject(hdcmem, oldbm);
	DeleteObject(hbm);
	DeleteDC(hdcmem);
	DeleteObject(hpen);
	
	UNREFERENCED_PARAMETER(uButflags);
	UNREFERENCED_PARAMETER(uCmdId);
	return 0;
}

