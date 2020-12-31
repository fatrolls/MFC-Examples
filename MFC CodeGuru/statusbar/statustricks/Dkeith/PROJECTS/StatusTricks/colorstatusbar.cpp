// ColorStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "ColorStatusBar.h"
#include "MainFrm.h"
#include "StatusTricks.h"
#include "StatusBarProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StatusPaneInfo
CStatusPaneInfo::CStatusPaneInfo(COLORREF bcolor, COLORREF tcolor,
							   CFont *font, BOOL clear, BOOL transparent)
{
	p_bcolor = bcolor;
	p_tcolor = tcolor;
	p_font = font;
	b_clearback = clear;
	b_transparent = transparent;
	b_vScroll = FALSE;
	b_hScroll = FALSE;
	pt_lastTop = CPoint(0, 0);
}

CStatusPaneInfo::~CStatusPaneInfo()
{
	// if we were given a font - kill it
	if (p_font)
	{
		delete p_font;
	}
}

/////////////////////////////////////////////////////////////////////////////
// ColorStatusBar
CColorStatusBar::CColorStatusBar()
{
	// create the default font just in case any panes are using it
	defont.CreateFont(-8, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, TMPF_TRUETYPE | FF_SWISS, "MS Sans Serif");

	// indicate the status bar banner is not drawn
	b_showBanner = FALSE;

	// indicate we're not handling the timer
	b_timer = FALSE;
}

CColorStatusBar::~CColorStatusBar()
{
	// kill the status bar information objects
	while (!panelist.IsEmpty())
	{
		delete panelist.RemoveHead();
	}
}

BEGIN_MESSAGE_MAP(CColorStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(ColorStatusBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ColorStatusBar message handlers

void CColorStatusBar::OnPaint() 
{
		CPaintDC		 dc(this);		// device context for painting
		CDC				 dcimage;		// dc for bitmap image
		CDC				 memDC;			// dc for drawing the status bar
		CPen			*graypen;		// dark gray pen
		CPen			*oldpen;		// pen already in dc
		CString			 text;			// pane text to display
		CRect			 pane;			// window pane to paint in
		CRect			 rect;			// general rect for clipping
		CRect			 client;		// rect binding the client area
		POSITION		 pos;			// current position in object list
		CStatusPaneInfo	*info;			// pane information
		UINT			 paneid;		// pane identifier
		UINT			 panestyle;		// style bits for current pane
		int				 i;				// general index
		int				 panewidth;		// width of the current pane
		COLORREF		 oldback;		// background color already in dc
		BITMAP			 bm;			// bitmap object
		CBrush			 brush;			// brush needed to erase background
		CBitmap			 bmp;			// object holding actual bitmap data
		CBitmap			 memBmp;		// bitmap just like what's on active dc
		CBitmap			*oldbmp;		// bitmap already in dc
		CBitmap			*oldmemBmp;		// bitmap already in memory dc

	// grab a couple of memory dc
	dcimage.CreateCompatibleDC(&dc);
	memDC.CreateCompatibleDC(&dc);

	// grab the rectangle bounding the status bar
	GetClientRect(client);

	// create a bitmap for the memory dc and select it
	memBmp.CreateCompatibleBitmap(&dc, client.Width(), client.Height());
	oldmemBmp = (CBitmap *)memDC.SelectObject(&memBmp);

	// clear the memory dc in preparation for drawing the status bar
	brush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
	memDC.FillRect(client, &brush);
	brush.DeleteObject();

	// keep record of current background color
	oldback = dc.GetBkColor();

	// if we can tile the bitmap over the status bar
	if (b_showBanner && bmp.LoadBitmap(IDB_STATUSBARBANNER))
	{
		bmp.GetBitmap(&bm);
		oldbmp = (CBitmap *)dcimage.SelectObject(&bmp);
		for (i = 0; i <= client.Width() / bm.bmWidth + 1; i++)
		{
			memDC.BitBlt(client.left + bm.bmWidth * i,
				client.top,
				client.left + bm.bmWidth * (i + 1),
				client.Height(),
				&dcimage,
				0, 0, SRCCOPY);
		}
		dcimage.SelectObject(oldbmp);
	}

	// for each pane in the status bar
	for (i = 0, pos = panelist.GetHeadPosition(); i < GetCount() && pos; i++)
	{
		// grab a reference to the current window pane's information
		info = (CStatusPaneInfo *)panelist.GetNext(pos);

		// set the current background color
		memDC.SetBkColor(info->GetBackColor());

		// grab the rectangle bounding the window pane and the pane information
		GetItemRect(i, pane);
		GetPaneInfo(i, paneid, panestyle, panewidth);

		// if there is supposed to be an inset border around this pane
		if (!(panestyle & SBPS_NOBORDERS))
		{
			// bring the bottom of the pane up a pixel
			pane.bottom--;

			// draw a 3d inset border around the pane
			graypen = new CPen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW));
			oldpen = memDC.SelectObject(graypen);
			memDC.MoveTo(pane.left, pane.top);
			memDC.LineTo(pane.left, pane.bottom);
			memDC.MoveTo(pane.left, pane.top);
			memDC.LineTo(pane.right, pane.top);
			memDC.SelectObject(oldpen);
			delete graypen;
			graypen = new CPen(PS_SOLID, 1, GetSysColor(COLOR_BTNHIGHLIGHT));
			oldpen = memDC.SelectObject(graypen);
			memDC.SelectStockObject(WHITE_PEN);
			memDC.MoveTo(pane.left, pane.bottom);
			memDC.LineTo(pane.right, pane.bottom);
			memDC.LineTo(pane.right, pane.top);
			memDC.SelectObject(oldpen);
			delete graypen;
		}

		// else if there is supposed to be an outset border around this pane
		else if (panestyle & SBPS_POPOUT)
		{
			// bring the bottom of the pane up a pixel
			pane.bottom--;

			// draw a 3d outset border around the pane
			graypen = new CPen(PS_SOLID, 1, GetSysColor(COLOR_BTNHIGHLIGHT));
			oldpen = memDC.SelectObject(graypen);
			memDC.MoveTo(pane.left, pane.top);
			memDC.LineTo(pane.left, pane.bottom);
			memDC.MoveTo(pane.left, pane.top);
			memDC.LineTo(pane.right, pane.top);
			memDC.SelectObject(oldpen);
			delete graypen;
			graypen = new CPen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW));
			oldpen = memDC.SelectObject(graypen);
			memDC.MoveTo(pane.left, pane.bottom);
			memDC.LineTo(pane.right, pane.bottom);
			memDC.LineTo(pane.right, pane.top);
			memDC.SelectObject(oldpen);
			delete graypen;
		}

		// shrink the rectangle by a pixel on each side (for the boundary)
		pane.InflateRect(-1, -1);
		DrawPane(i, &memDC);
	}

	// if the mainframe isn't maximized
	if (!GetParent()->IsZoomed())
	{
		// grab the rectangle bounding the status bar
		GetWindowRect(&pane);
		pane.OffsetRect(-pane.left, -pane.top);

		// create the thinner pen of the two lines
		graypen = new CPen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		oldpen = memDC.SelectObject(graypen);
		memDC.MoveTo(pane.right - 15, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 15);
		memDC.MoveTo(pane.right - 11, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 11);
		memDC.MoveTo(pane.right - 7, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 7);
		memDC.MoveTo(pane.right - 3, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 3);

		// restore the dc
		dc.SelectObject(oldpen);
		delete graypen;

		// create the thicker pen of the two lines
		graypen = new CPen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		oldpen = memDC.SelectObject(graypen);
		memDC.MoveTo(pane.right - 14, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 14);
		memDC.MoveTo(pane.right - 10, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 10);
		memDC.MoveTo(pane.right - 6, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 6);
		memDC.MoveTo(pane.right - 2, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 2);
		memDC.MoveTo(pane.right - 13, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 13);
		memDC.MoveTo(pane.right - 9, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 9);
		memDC.MoveTo(pane.right - 5, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 5);
		memDC.MoveTo(pane.right - 1, pane.bottom);
		memDC.LineTo(pane.right, pane.bottom - 1);

		// restore the dc
		memDC.SelectObject(oldpen);
		delete graypen;
	}

	// copy the status bar painting to the active dc
	dc.BitBlt(0, 0, client.Width(), client.Height(), &memDC, 0, 0, SRCCOPY);

	// restore the dc
	memDC.SelectObject(oldmemBmp);
	memDC.SetBkColor(oldback);
}

void CColorStatusBar::DrawPane(int index, CDC *dc)
{
		CDC				 memDC;		// dc for double-buffered drawing
		CFont			*oldFont;	// font already in dc
		CBrush			 pBrush;	// brush to paint background of pane with
		CBitmap			 memBmp;	// bmp for double-buffered drawing
		CBitmap			*oldBmp;	// bmp already in memory dc
		CRect			 pane;		// pane we need to paint
		CRect			 rect;		// pane rect offset so left,top = 0,0
		CString			 str;		// string to paint in this pane
		CStatusPaneInfo	*info;		// information about the pane we're painting
		UINT			 paneid;	// pane identifier
		UINT			 panestyle;	// style bits for current pane
		int				 panewidth;	// width of the current pane

	// pick up some information about the specified pane
	info = (CStatusPaneInfo *)panelist.GetAt(panelist.FindIndex(index));
	GetItemRect(index, pane);
	pane.DeflateRect(1, 1);
	GetPaneInfo(index, paneid, panestyle, panewidth);

	// build the rect we wanna paint in
	rect = pane;
	rect.OffsetRect(-rect.left, -rect.top);

	// build the offscreen dc for drawing
	memDC.CreateCompatibleDC(dc);
	memBmp.CreateCompatibleBitmap(dc, pane.Width(), pane.Height());
	oldBmp = memDC.SelectObject(&memBmp);

	// if we're displaying the banner
	if (b_showBanner)
	{
		// copy the dc over (it might have the banner across it)
		memDC.BitBlt(0, 0, pane.Width(), pane.Height(), dc, pane.left, pane.top,
			SRCCOPY);
	}
	
	// else we aren't showing the banner
	else
	{
		// create the brush to clear the background with
		pBrush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));

		// erase the background
		memDC.FillRect(rect, &pBrush);
		pBrush.DeleteObject();
	}

	// if we're supposed to clear the pane
	if (info->GetClear())
	{
		// create the brush to clear the background with
		pBrush.CreateSolidBrush(info->GetBackColor());

		// erase the background
		memDC.FillRect(rect, &pBrush);
		pBrush.DeleteObject();
	}

	// pick up the text we're supposed to paint in
	str = GetPaneText(index);

	// set the appropriate font for this pane
	if (info->GetFont())
	{
		oldFont = memDC.SelectObject(info->GetFont());
	}
	else
	{
		oldFont = memDC.SelectObject(&defont);
	}

	// prepare the dc to print the text in the requested color
	if (info->GetTransparent())
	{
		memDC.SetBkMode(TRANSPARENT);
	}
	else
	{
		memDC.SetBkMode(OPAQUE);
	}

	// if the text is disabled - force it to darkgray
	if (panestyle & SBPS_DISABLED)
	{
		memDC.SetTextColor(RGB(0x80, 0x80, 0x80));
	}
	
	// else set the color as required by pane information
	else
	{
		memDC.SetTextColor(info->GetTextColor());
	}

	// offset the rect according to scrolling
	if (info->GetVScroll())
	{
		// offset to the new vertical position
		rect.OffsetRect(0, info->pt_lastTop.y);
		info->pt_lastTop.y--;

		// if the text won't show up
		if (rect.bottom <= pane.top)
		{
			// set the new position of the text
			rect.top = pane.bottom;
			rect.bottom = pane.bottom + pane.Height();
			info->pt_lastTop.y = pane.bottom;
		}
	}
	if (info->GetHScroll())
	{
		// offset the text rect
		rect.OffsetRect(info->pt_lastTop.x, 0);
		info->pt_lastTop.x--;

		// if we don't have any visible text
		if (rect.right < 0)
		{
			rect.left = pane.Width();
			rect.right = rect.left + pane.Width();
			info->pt_lastTop.x = rect.left;
		}
	}

	// stick the text in the pane
	memDC.DrawText(str, rect, DT_LEFT);

	// blit the pane to the status bar
	dc->BitBlt(pane.left, pane.top, pane.Width(), pane.Height(), &memDC, 0, 0,
		SRCCOPY);
	
	// restore the dc
	memDC.SelectObject(oldFont);
	memDC.SelectObject(oldBmp);
}

CStatusPaneInfo *CColorStatusBar::GetColorPaneInfo(int paneindex)
{
		CStatusPaneInfo		*info;		// object to return to caller

	// if the index is valid - retrieve the requested object
	if (0 <= paneindex && paneindex <= panelist.GetCount())
	{
		info = (CStatusPaneInfo *)panelist.GetAt(panelist.FindIndex(paneindex));
	}

	// else the index is invalid - return NULL
	else
	{
		info = NULL;
	}
	return info;
}

void CColorStatusBar::SetColorPaneInfo(int paneindex, CStatusPaneInfo *paneinfo)
{
		CStatusPaneInfo		*info;		// object to be modified
		CStatusPaneInfo		 definfo;	// default information to be copied

	// if the index is valid
	if (0 <= paneindex && paneindex <= panelist.GetCount())
	{
		// grab a reference to the requested object
		info = (CStatusPaneInfo *)panelist.GetAt(panelist.FindIndex(paneindex));

		// if caller sent a valid information structure
		if (paneinfo)
		{
			// copy the information as sent
			info->SetBackColor(paneinfo->GetBackColor());
			info->SetTextColor(paneinfo->GetTextColor());
			info->SetFont(paneinfo->GetFont());
		}
		
		// else default the information
		else
		{
			info->SetBackColor(definfo.GetBackColor());
			info->SetTextColor(definfo.GetTextColor());
		}
	}
}

void CColorStatusBar::SetColorPaneText(int index, CString str, CStatusPaneInfo &paneinfo)
{
	// set the pane information
	SetColorPaneInfo(index, &paneinfo);

	// set the pane text
	SetPaneText(index, str);
	Invalidate(FALSE);
}

void CColorStatusBar::OnLButtonDblClk(UINT nFlags, CPoint point)
{
		CRect					 rPane;		// rect binding the current pane
		CStatusBarProperties	*dlg;		// dialog to change pane properties
		CStatusPaneInfo			*info;		// status pane information
		BOOL					 scroll;	// indicates if any panes are scrolling
		int						 i;			// general index

	// for each pane in the status bar
	for (i = 0; i < panelist.GetCount(); i++)
	{
		// pick up the rect binding this pane
		GetItemRect(i, rPane);

		// if user clicked in this pane
		if (rPane.PtInRect(point))
		{
			// grab the pane properties user clicked on
			info = (CStatusPaneInfo *)panelist.GetAt(panelist.FindIndex(i));

			// display the properties for this pane
			dlg = new CStatusBarProperties(info, b_showBanner, this);

			// if user changes the settings
			if (dlg->DoModal() == IDOK)
			{
				// remember the checkbox states
				info->SetClear(dlg->m_bClearBackground);
				info->SetTransparent(dlg->m_bTransparentText);
				info->SetVScroll(dlg->m_bVerticalScrolling);
				info->SetHScroll(dlg->m_bHorizontalScrolling);
				b_showBanner = dlg->m_bShowBanner;

				// if we're supposed to scroll something
				if (info->GetVScroll() || info->GetHScroll())
				{
					// if we're not already scrolling
					if (!b_timer)
					{
						// set up the timer
						SetTimer(IDC_STATUSBARTIMER, 100, NULL);
						b_timer = TRUE;
					}
				}

				// else we're not supposed to scroll this pane
				else
				{
					// for each pane
					for (i = 0, scroll = FALSE; i < GetCount() && !scroll; i++)
					{
						// pick up this pane's information
						info = (CStatusPaneInfo *)panelist.GetAt(
							panelist.FindIndex(i));

						// if this pane is scrolling anything
						if (info->GetHScroll() || info->GetVScroll())
						{
							// indicate we're finished
							scroll = TRUE;
						}
					}

					// if we don't need to handle the timer
					if (!scroll)
					{
						// kill the timer
						KillTimer(IDC_STATUSBARTIMER);
						b_timer = FALSE;
					}
				}

				// repaint this pane
				Invalidate(FALSE);
			}

			// kill the dialog
			delete dlg;
		}
	}

	// default processing
	CStatusBar::OnLButtonDblClk(nFlags, point);
}

void CColorStatusBar::OnTimer(UINT nIDEvent)
{
	// if this timer belongs to the status bar
	if (nIDEvent == IDC_STATUSBARTIMER)
	{
		// force a repaint
		Invalidate(FALSE);
		UpdateWindow();
	}
}

BOOL CColorStatusBar::DestroyWindow()
{
	// if we're doing the timer
	if (b_timer)
	{
		// kill the timer
		KillTimer(IDC_STATUSBARTIMER);
		b_timer = FALSE;
	}

	// default processing
	return CStatusBar::DestroyWindow();
}

void CColorStatusBar::OnSize(UINT uFlags, int cx, int cy)
{
	CStatusBar::OnSize(uFlags, cx, cy);
}
