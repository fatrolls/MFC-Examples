////////////////////////////////////////////////////////////////
// CoolMenu 1997 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#include "StdAfx.h"
#include "PixLib.h"
#include "CoolMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// if you want to see extra TRACE diagnostics, set below to TRUE
BOOL CCoolMenuManager::bTRACE = FALSE;

#ifdef _DEBUG
#define CMTRACEFN			\
	CTraceFn __fooble;	\
	if (bTRACE)				\
		TRACE
#define CMTRACE			\
	if (bTRACE)				\
		TRACE
#else
#define CMTRACEFN TRACE
#define CMTRACE   TRACE
#endif

// constants used for drawing
const CXGAP = 1;				// num pixels between button and text
const CXTEXTMARGIN = 2;		// num pixels after hilite to start text
const CXBUTTONMARGIN = 2;	// num pixels wider button is than bitmap
const CYBUTTONMARGIN = 2;	// ditto for height

// DrawText flags
const DT_MYSTANDARD = DT_SINGLELINE|DT_LEFT|DT_VCENTER;

// identifies owner-draw data as mine
const LONG MYITEMID = MAKELONG(MAKEWORD('m','i'),MAKEWORD('d','0'));

// private struct: one of these for each owner-draw menu item
struct CMyItemData
{
	long				magicNum;		// magic number identifying me
	CString				text;			// item text
	UINT				fType;			// original item type flags
	int					iButton;		// index of button image in image list
	CMyItemData()		{ magicNum = MYITEMID; }
	BOOL IsMyItemData()	{ return magicNum == MYITEMID; }
};

IMPLEMENT_DYNAMIC(CCoolMenuManager, CSubclassWnd)

CCoolMenuManager::CCoolMenuManager():
	m_szBitmap(0,0),
	m_szButton(0,0),					// will compute later
	m_bShowButtons(TRUE),				// show buttons by default
	m_bAutoAccel(FALSE),					// auto accelerators by default
	m_hAccel(NULL),						// no accelerators loaded yet
	m_pAccel(NULL),						// no accelerators loaded yet
	m_bUseDrawState(FALSE),				// use DrawEmbossed by default
	m_bDrawDisabledButtonsInColor(TRUE),// use color for disabled buttons
	m_CheckSelected((UINT)-1),				// bitmaps ids for checkmarks
	m_CheckUnselected((UINT)-1)				// if id == -1 no bitmap
{
	FixMFCDotBitmap();
//Vytukas
	CBitmap	*bitmap = CBitmap::FromHandle(PxLib::CreateDitherBitmap());
	if (bitmap != NULL)
	{
		m_DitherBrush.CreatePatternBrush(bitmap);
		bitmap->DeleteObject();
	}
//Vytukas
}

CCoolMenuManager::~CCoolMenuManager()
{
	Destroy();
}

//////////////////
// Destroy everything. Called from destructor and Refresh.
//
void CCoolMenuManager::Destroy()
{
	m_ilButtons.DeleteImageList();
	m_mapIDtoImage.RemoveAll();
	m_szBitmap = m_szButton = CSize(0,0);
	m_arToolbarID.RemoveAll();
	m_fontMenu.DeleteObject();
	DestroyAccel();
	m_DitherBrush.DeleteObject();
}

/////////////////
// Destroy accelerators
//
void CCoolMenuManager::DestroyAccel()
{
	m_mapIDtoAccel.RemoveAll();		// delete ACCEL entries in map
	delete m_pAccel;				// delete current accelerators
	m_pAccel = NULL;				// ...
}

//////////////////
// Call this to install the menu manager. Install(NULL) to un-install.
//
void CCoolMenuManager::Install(CFrameWnd* pFrame)
{
	ASSERT_VALID(pFrame);
	m_pFrame = pFrame;
	HookWindow(pFrame);   // install message hook
}

//////////////////
// Load array of toolbar IDs.
//
BOOL CCoolMenuManager::LoadToolbars(const UINT* arID, int n)
{
	ASSERT(arID);
	BOOL bRet = TRUE;

	for (int i=0; i<n; i++)
		bRet |= LoadToolbar(arID[i]);

	return bRet;
}

// structure of RT_TOOLBAR resource
struct TOOLBARDATA
{
	WORD wVersion;		// version # should be 1
	WORD wWidth;		// width of one bitmap
	WORD wHeight;		// height of one bitmap
	WORD wItemCount;	// number of items
	WORD items[1];		// array of command IDs, actual size is wItemCount
};

//////////////////
// Load one toolbar. Assumes bg color is gray.
// 
//  * add toolbar bitmap to image list
//	 * add each button ID to button map
//
BOOL CCoolMenuManager::LoadToolbar(UINT nIDToolbar)
{
	// load bitmap
	HBITMAP hbmToolbar = PxLib::LoadSysColorBitmap(nIDToolbar);
	if (!hbmToolbar)
	{
		TRACE(_T("*** Can't load bitmap for toolbar %d!\n"), nIDToolbar);
		return FALSE;
	}
	CBitmap bmToolbar;
	bmToolbar.Attach(hbmToolbar); // destructor will detach & destroy

	// load toolbar
	LPTSTR lpResName = MAKEINTRESOURCE(nIDToolbar);
	HINSTANCE hInst;
	HRSRC hRsrc;
	TOOLBARDATA* ptbd;
	if ((hInst= AfxFindResourceHandle(lpResName, RT_TOOLBAR)) == NULL ||
		 (hRsrc= FindResource(hInst, lpResName, RT_TOOLBAR))   == NULL ||
		 (ptbd = (TOOLBARDATA*)LoadResource(hInst, hRsrc))     == NULL)
	{

		TRACE(_T("*** Can't load toolbar %d!\n"), nIDToolbar);
		return FALSE;
	}
	ASSERT(ptbd->wVersion==1);
		
	// OK, I have the bitmap and toolbar. 

	CSize sz(ptbd->wWidth, ptbd->wHeight);
	if (m_szBitmap.cx==0)
	{
		// First toolbar: initialized bitmap/button sizes and create image list.
		m_szBitmap = sz;
		m_szButton = sz + CSize(CXBUTTONMARGIN<<1, CYBUTTONMARGIN<<1);
		VERIFY(m_ilButtons.Create(sz.cx, sz.cy, ILC_MASK, 0, 10));

	}
	else
	{
		if (m_szBitmap != sz)
		{
			// button sizes different -- oops
			TRACE(_T("*** Toolbar %d button size differs!\n"), nIDToolbar);
			return FALSE;
		}
	}
	
	// I have a good toolbar: now add bitmap to the image list, and each
	// command ID to m_mapIDtoImage array. Note that LoadSysColorBitmap will
	// change gray -> COLOR_3DFACE, so use that for image list background.
	//
	int iNextImage = m_ilButtons.GetImageCount();
	m_ilButtons.Add(&bmToolbar, GetSysColor(COLOR_3DFACE));
	for (int i = 0; i < ptbd->wItemCount; i++)
	{
		WORD nID = ptbd->items[i];
		if (nID > 0)
		{
			if (GetButtonIndex(nID) >= 0)
				TRACE(_T("*** Duplicate button ID %d ignored\n"), nID);
			else
				m_mapIDtoImage.SetAt(nID, (void*)iNextImage++);
		}
	}
	m_arToolbarID.Add(nIDToolbar);  // remember toolbar ID for Refresh
	bmToolbar.Detach();
	return TRUE; // success!
}

//////////////////
// Virtual CSubclassWnd window proc. All messages come here before frame
// window. Isn't it cool? Just like in the old days!
//
LRESULT CCoolMenuManager::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	switch(msg)
	{
	case WM_SYSCOLORCHANGE:
	case WM_SETTINGCHANGE:
		Refresh();
		break;

	case WM_MEASUREITEM:
		if (OnMeasureItem((MEASUREITEMSTRUCT*)lp))
			return TRUE; // handled
		break;

	case WM_DRAWITEM:
		if (OnDrawItem((DRAWITEMSTRUCT*)lp))
			return TRUE; // handled
		break;

	case WM_INITMENUPOPUP:
		// Very important: must let frame window handle it first!
		// Because if someone calls CCmdUI::SetText, MFC will change item to
		// MFT_STRING, so I must change back to MFT_OWNERDRAW.
		//
		CSubclassWnd::WindowProc(msg, wp, lp);
		OnInitMenuPopup(CMenu::FromHandle((HMENU)wp),
			(UINT)LOWORD(lp), (BOOL)HIWORD(lp));
		return 0;

	case WM_MENUSELECT:
		OnMenuSelect((UINT)LOWORD(wp), (UINT)HIWORD(wp), (HMENU)lp);
		break;

	case WM_MENUCHAR:
		LRESULT lr = OnMenuChar((TCHAR)LOWORD(wp), (UINT)HIWORD(wp),
			CMenu::FromHandle((HMENU)lp));
		if (lr!=0)
			return lr;
		break;
	}
	return CSubclassWnd::WindowProc(msg, wp, lp);
}

//////////////////
// Refresh all colors, fonts, etc. For WM_SETTINGCHANGE, WM_SYSCOLORCHANGE.
//
void CCoolMenuManager::Refresh()
{
	// first copy list (array) of toolbar IDs now loaded.
	CUIntArray arToolbarID;
	arToolbarID.Copy(m_arToolbarID);

	// destroy everything
	Destroy();

	// re-load toolbars.
	int nToolbars = arToolbarID.GetSize();
	for (int i = 0; i < nToolbars; i++)
		LoadToolbar(arToolbarID[i]);
//Vytukas
	CBitmap	*bitmap = CBitmap::FromHandle(PxLib::CreateDitherBitmap());
	if (bitmap != NULL)
	{
		m_DitherBrush.CreatePatternBrush(bitmap);
		bitmap->DeleteObject();
	}
//Vytukas
}

//////////////////
// Get menu font, creating if needed
//
CFont* CCoolMenuManager::GetMenuFont()
{
	if (!(HFONT)m_fontMenu)
	{
		NONCLIENTMETRICS info;
		info.cbSize = sizeof(info);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
		VERIFY(m_fontMenu.CreateFontIndirect(&info.lfMenuFont));
	}
	return &m_fontMenu;
}

//////////////////
// Handle WM_MEASUREITEM on behalf of frame: compute menu item size.
//
BOOL CCoolMenuManager::OnMeasureItem(LPMEASUREITEMSTRUCT lpms)
{
	ASSERT(lpms);
	CMyItemData* pmd = (CMyItemData*)lpms->itemData;
//	TRACE("pmd == NULL\n");		//pmd == NULL by Vytukas
	if (lpms->CtlType != ODT_MENU || pmd == NULL || !pmd->IsMyItemData())
		return FALSE; // not handled by me

	if (pmd->fType & MFT_SEPARATOR)
	{
		// separator: use half system height and zero width
		lpms->itemHeight = GetSystemMetrics(SM_CYMENU)>>1;
		lpms->itemWidth  = 0;

	}
	else
	{
		// compute size of text: use DrawText with DT_CALCRECT

		CWindowDC dc(NULL);	// screen DC--I won't actually draw on it
		CRect rcText(0,0,0,0);
		CFont* pOldFont = dc.SelectObject(GetMenuFont());
		dc.DrawText(pmd->text, rcText, DT_MYSTANDARD|DT_CALCRECT);
		dc.SelectObject(pOldFont);

		// height of item is just height of a standard menu item
		lpms->itemHeight= max(GetSystemMetrics(SM_CYMENU), rcText.Height());

		// width is width of text plus a bunch of stuff
		int cx = rcText.Width();	// text width 
		cx += CXTEXTMARGIN<<1;		// L/R margin for readability
		cx += CXGAP;					// space between button and menu text
		cx += m_szButton.cx<<1;		// button width (L=button; R=empty margin)

		// whatever value I return in lpms->itemWidth, Windows will add the
		// width of a menu checkmark, so I must subtract to defeat Windows. Argh.
		//
		cx -= GetSystemMetrics(SM_CXMENUCHECK)-1;
		lpms->itemWidth = cx;		// done deal

		CMTRACE(_T("OnMeasureItem for '%s':\tw=%d h=%d\n"), (LPCTSTR)pmd->text,
			lpms->itemWidth, lpms->itemHeight);
	}
	return TRUE; // handled
}

/////////////////
// Handle WM_DRAWITEM on behalf of frame. Note: in all that goes
// below, can't assume rcItem.left=0 because of multi-column menus!
//
BOOL CCoolMenuManager::OnDrawItem(LPDRAWITEMSTRUCT lpds)
{
	ASSERT(lpds);
	CMyItemData* pmd = (CMyItemData*)lpds->itemData;
//	TRACE("pmd == NULL\n");		//pmd == NULL by Vytukas
	if (lpds->CtlType != ODT_MENU || pmd == NULL || !pmd->IsMyItemData())
		return FALSE; // not handled by me

	ASSERT(lpds->itemAction != ODA_FOCUS);
	ASSERT(lpds->hDC);
	CDC dc;
	dc.Attach(lpds->hDC);

	const CRect& rcItem = lpds->rcItem;
	if (pmd->fType & MFT_SEPARATOR)
	{
		// draw separator
		CRect rc = rcItem;								// copy rect
		rc.top += rc.Height()>>1;						// vertical center
		dc.DrawEdge(&rc, EDGE_ETCHED, BF_TOP);		// draw separator line

	}
	else
	{													// not a separator

		CMTRACE(_T("OnDrawItem for '%s':\tw=%d h=%d\n"), (LPCTSTR)pmd->text,
			rcItem.Width(), rcItem.Height());

		BOOL bDisabled = lpds->itemState & ODS_GRAYED;
		BOOL bSelected = lpds->itemState & ODS_SELECTED;
		BOOL bChecked  = lpds->itemState & ODS_CHECKED;
		BOOL bHaveButn=FALSE;

		// Paint button, or blank if none
		CRect rcButn(rcItem.TopLeft(), m_szButton);	// button rect
		rcButn += CPoint(0, (rcItem.Height() - rcButn.Height())>>1 );// center vertically

		int iButton = pmd->iButton;
		if (iButton >= 0)
		{
			// this item has a button!
			bHaveButn = TRUE;

			// compute point to start drawing
			CSize sz = rcButn.Size() - m_szBitmap;
			sz.cx >>= 1;
			sz.cy >>= 1;
			CPoint p(rcButn.TopLeft() + sz);

			// draw disabled or normal
			if (!bDisabled)
			{
				if(bChecked && !bSelected)
					PxLib::FillRect(dc, rcButn, &m_DitherBrush);	//Vytukas
				else
					// normal: fill BG depending on state
					PxLib::FillRect(dc, rcButn, GetSysColor(
						(bChecked && !bSelected) ? COLOR_3DLIGHT : COLOR_MENU));

				// draw pushed-in or popped-out edge
				if (bSelected || bChecked)
				{
					CRect rc2 = rcButn;
					dc.DrawEdge(rc2, bChecked ? BDR_SUNKENOUTER : BDR_RAISEDINNER,
						BF_RECT);
				}
				// draw the button!
				m_ilButtons.Draw(&dc, iButton, p, ILD_TRANSPARENT);

			} 
			else 
			{
				if (m_bUseDrawState)
				{
					// use DrawState to draw disabled button: must convert to icon
					HICON hIcon=m_ilButtons.ExtractIcon(iButton);
					ASSERT(hIcon);
					dc.DrawState(p, CSize(0,0), hIcon, DSS_DISABLED, (HBRUSH)NULL);
					DestroyIcon(hIcon);
				}
				else
				{
					// use DrawEmbossed to draw disabeld button, w/color flag
					PxLib::DrawEmbossed(dc, m_ilButtons, iButton, p,
						m_bDrawDisabledButtonsInColor);
				}
			}
		}
		else
		{
			// no button: look for custom checked/unchecked bitmaps
			CMenuItemInfo info;
			info.fMask = MIIM_CHECKMARKS;
			GetMenuItemInfo((HMENU)lpds->hwndItem, lpds->itemID, MF_BYCOMMAND, &info);
			if (bChecked || info.hbmpUnchecked)
			{
				bHaveButn = Draw3DCheckmark(dc, rcButn, bSelected,
					bChecked ? info.hbmpChecked : info.hbmpUnchecked);
			}
		}

		// Done with button, now paint text. First do background if needed.
		int cxButn = m_szButton.cx;				// width of button
		COLORREF colorBG = GetSysColor(bSelected ? COLOR_HIGHLIGHT : COLOR_MENU);
		if (bSelected || lpds->itemAction==ODA_SELECT)
		{
			// selected or selection state changed: paint text background
			CRect rcBG = rcItem;							// whole rectangle
			if (bHaveButn)									// if there's a button:
				rcBG.left += cxButn + CXGAP;			//  don't paint over it!
			PxLib::FillRect(dc, rcBG, colorBG);	// paint it!
		}

		// compute text rectangle and colors
		CRect rcText = rcItem;				 // start w/whole item
		rcText.left += cxButn + CXGAP + CXTEXTMARGIN; // left margin
		rcText.right -= cxButn;				 // right margin
		dc.SetBkMode(TRANSPARENT);			 // paint transparent text
		COLORREF colorText = GetSysColor(bDisabled ?  COLOR_GRAYTEXT :
			bSelected ? COLOR_HIGHLIGHTTEXT : COLOR_MENUTEXT);

		// Now paint menu item text.	No need to select font,
		// because windows sets it up before sending WM_DRAWITEM
		//
		if(bDisabled && bSelected && colorText == colorBG)
		{
			colorText = GetSysColor(COLOR_3DLIGHT);
		}

		if (bDisabled && (!bSelected || colorText == colorBG))
		{
			// disabled: draw hilite text shifted southeast 1 pixel for embossed
			// look. Don't do it if item is selected, tho--unless text color same
			// as menu highlight color. Got it?
			//
			DrawMenuText(dc, rcText + CPoint(1,1), pmd->text,
				GetSysColor(COLOR_3DHILIGHT));
		}
		DrawMenuText(dc, rcText, pmd->text, colorText); // finally!
	}
	dc.Detach();

	return TRUE; // handled
}

/////////////////
// Helper function to draw justified menu text. If the text contains a TAB,
// draw everything after the tab right-aligned
//
void CCoolMenuManager::DrawMenuText(CDC& dc, CRect rc, CString text,
	COLORREF color)
{
	CString left = text;
	CString right;
	int iTabPos = left.Find('\t');
	if (iTabPos >= 0)
	{
		right = left.Right(left.GetLength() - iTabPos - 1);
		left  = left.Left(iTabPos);
	}
	dc.SetTextColor(color);
	dc.DrawText(left, &rc, DT_MYSTANDARD);
	if (iTabPos > 0)
		dc.DrawText(right, &rc, DT_MYSTANDARD|DT_RIGHT);
}

#ifndef OBM_CHECK
#define OBM_CHECK 32760 // from winuser.h
#endif

//////////////////
// Draw 3D checkmark
//
//		dc				device context to draw in
//		rc				rectangle to center bitmap in
//		bSelected		TRUE if button is also selected
//		hbmCheck		Checkmark bitmap to use, or NULL for default
//
BOOL CCoolMenuManager::Draw3DCheckmark(CDC& dc, const CRect& rc,
	BOOL bSelected, HBITMAP hbmCheck)
{
	// get checkmark bitmap if none, use Windows standard or loaded checkmarks
	if (!hbmCheck)
	{
		CBitmap bm;
		//Vytukas additions
		if(bSelected)
		{
			if(m_CheckSelected != -1)
				VERIFY(bm.LoadBitmap(m_CheckSelected));
		}
		else
		{
			if(m_CheckUnselected != -1)
				VERIFY(bm.LoadBitmap(m_CheckUnselected));
		}

		if(!(HBITMAP)bm)
			VERIFY(bm.LoadOEMBitmap(OBM_CHECK));

		hbmCheck = (HBITMAP)bm.Detach();
		ASSERT(hbmCheck);
	}
	
	// center bitmap in caller's rectangle
	BITMAP bm;
	::GetObject(hbmCheck, sizeof(bm), &bm);
	int cx = bm.bmWidth;
	int cy = bm.bmHeight;
	CRect rcDest = rc;
	CPoint p(0,0);
	CSize delta(CPoint((rc.Width() - cx)/2, (rc.Height() - cy)/2));
	if (rc.Width() > cx)
		rcDest = CRect(rc.TopLeft() + delta, CSize(cx, cy));
	else
		p -= delta;

	// select checkmark into memory DC
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	HBITMAP hOldBM = (HBITMAP)::SelectObject(memdc, hbmCheck);

	// set BG color based on selected state
	COLORREF colorOld =
		dc.SetBkColor(GetSysColor(bSelected ? COLOR_MENU : COLOR_3DLIGHT));
	dc.BitBlt(rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
		&memdc, p.x, p.y, MERGECOPY);
	dc.SetBkColor(colorOld);

	::SelectObject(memdc, hOldBM); // restore

	// draw pushed-in hilight.
	if (rc.Width() > cx)			// if room:
		rcDest.InflateRect(1,1);	// inflate checkmark by one pixel all around
	dc.DrawEdge(&rcDest, BDR_SUNKENOUTER, BF_RECT);

	return TRUE;
}

//////////////////
// Handle WM_INITMENUPOPUP on behalf of frame.
//
void CCoolMenuManager::OnInitMenuPopup(CMenu* pMenu,
	UINT nIndex, BOOL bSysMenu)
{
	if (m_bAutoAccel)
	{
		// check for new accels. If ASSERT bombs, you forgot to call Install.
		ASSERT_VALID(m_pFrame);
		HACCEL hAccel = m_pFrame->GetDefaultAccelerator();
		if (hAccel != m_hAccel)
			LoadAccel(hAccel);
	}
	ConvertMenu(pMenu, nIndex, bSysMenu, m_bShowButtons);
}

//////////////////
// Set the accelerator table used to generate automatic key
// names in menus. Delete previous table if any.
//
void CCoolMenuManager::LoadAccel(HACCEL hAccel)
{
	DestroyAccel();
	int nAccel;
	if (hAccel && (nAccel = CopyAcceleratorTable(hAccel, NULL, 0)) > 0)
	{
		m_pAccel = new ACCEL [nAccel];
		ASSERT(m_pAccel);
		CopyAcceleratorTable(hAccel, m_pAccel, nAccel);

		// Now I have the accelerators. Look over list, linking each command
		// ID with its ACCEL structure--i.e., m_mapIDtoAccel[nID] = ACCEL for
		// that ID. If more than one ACCEL for a given command (command has more
		// than one shortcut), fix up so ACCEL.cmd is offset of prev ACCEL
		// 
		for (int i=0; i<nAccel; i++)
		{
			ACCEL& ac = m_pAccel[i];
			ACCEL* pAccel = GetAccel(ac.cmd);
			m_mapIDtoAccel.SetAt(ac.cmd, &ac);
			// ac.cmd = offset of prev, or 0
			ac.cmd = 0;
			if(pAccel)
			{
				ac.cmd = (WORD)(&ac - pAccel);
			}
		}
	}
}

//////////////////
// This rather gnarly function is used both to convert the menu from strings to
// owner-draw and vice versa. In either case, it also appends automagic
// accelerator key names to the menu items, if m_bAutoAccel is TRUE.
//
void CCoolMenuManager::ConvertMenu(CMenu* pMenu,
	UINT nIndex, BOOL bSysMenu, BOOL bShowButtons)
{
	ASSERT_VALID(pMenu);

	CString sItemName;

	UINT nItem = pMenu->GetMenuItemCount();
	for (UINT i = 0; i < nItem; i++) 
	{	// loop over each item in menu
		// get menu item info
		char itemname[256];
		CMenuItemInfo info;
		info.fMask = MIIM_SUBMENU | MIIM_DATA | MIIM_ID | MIIM_TYPE;
		info.dwTypeData = itemname;
		info.cch = sizeof(itemname);
		::GetMenuItemInfo(*pMenu, i, TRUE, &info);
		CMyItemData* pmd = (CMyItemData*)info.dwItemData;

		if (pmd && !pmd->IsMyItemData())
		{
			CMTRACE(_T("CCoolMenuManager: ignoring foreign owner-draw item\n"));
			continue; // owner-draw menu item isn't mine--leave it alone
		}

		if (bSysMenu && info.wID >= 0xF000)
		{
			CMTRACE(_T("CCoolMenuManager: ignoring sys menu item\n"));
			continue; // don't do for system menu commands
		}
	
		// now that I have the info, I will modify it
		info.fMask = 0;	// assume nothing to change

		if (bShowButtons)
		{
			// I'm showing buttons: convert to owner-draw
			if (!(info.fType & MFT_OWNERDRAW)) 
			{
				// If not already owner-draw, make it so. NOTE: If app calls
				// pCmdUI->SetText to change the text of a menu item, MFC will
				// turn the item to MFT_STRING. So I must set it back to
				// MFT_OWNERDRAW again. In this case, the menu item data (pmd)
				// will still be there.
				// 
				info.fType |= MFT_OWNERDRAW;
				info.fMask |= MIIM_TYPE;
				if (!pmd)
				{									// if no item data:
					pmd = new CMyItemData;				//   create one
					ASSERT(pmd);							//   (I hope)
					pmd->fType = info.fType;			//   handy when drawing
					pmd->iButton = GetButtonIndex((WORD)info.wID);
					info.dwItemData = (DWORD)pmd;		//   set in menu item data
					info.fMask |= MIIM_DATA;			//   set item data
				}
				pmd->text = info.dwTypeData;			// copy menu item string
			}

			// now add the menu to list of "converted" menus
			HMENU hmenu = pMenu->GetSafeHmenu();
			ASSERT(hmenu);
			if (!m_menuList.Find(hmenu))
				m_menuList.AddHead(hmenu);

			// append accelerators to menu item name
			if (m_pAccel && m_bAutoAccel)
				AppendAccelName(pmd->text, info.wID);
		}
		else
		{
			// no buttons -- I'm converting to strings
			if (info.fType & MFT_OWNERDRAW)
			{										// if ownerdraw:
				info.fType &= ~MFT_OWNERDRAW;		//   turn it off
				info.fMask |= MIIM_TYPE;			//   change item type
				ASSERT(pmd);							//   sanity check
				sItemName = pmd->text;				//   save name before deleting pmd
			}
			else										// otherwise:
				sItemName = info.dwTypeData;		//   use name from MENUITEMINFO

			if (pmd)
			{
				// NOTE: pmd (item data) could still be left hanging around even
				// if MFT_OWNERDRAW is not set, in case mentioned above where app
				// calls pCmdUI->SetText to set text of item and MFC sets the type
				// to MFT_STRING.
				//
				info.dwItemData = NULL;				// item data is NULL
				info.fMask |= MIIM_DATA;			// change it
				delete pmd;								// and item data too
			}

			// possibly add accelerator name
			if (m_pAccel  && m_bAutoAccel && AppendAccelName(sItemName, info.wID))
				info.fMask |= MIIM_TYPE;			//  change item type (string)
				
			if (info.fMask & MIIM_TYPE)
			{
				// if setting name, copy name from CString to buffer and set cch
				strncpy(itemname, sItemName, sizeof(itemname));
				info.dwTypeData = itemname;
				info.cch = sItemName.GetLength();
			}
		}

		// if after all the above, there is anything to change, change it
		if (info.fMask)
		{
			CMTRACE(_T("Converting '%s' to %s\n"), itemname,
				(info.fType & MFT_OWNERDRAW) ? _T("OWNERDRAW") : _T("STRING"));
			SetMenuItemInfo(*pMenu, i, TRUE, &info);
		}
	}
	nIndex;
}

//////////////////
// User typed a char into menu. Look for item with & preceeding the char typed.
//
LRESULT CCoolMenuManager::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu)
{
	ASSERT_VALID(pMenu);

	UINT iCurrentItem = (UINT)-1; // guaranteed higher than any command ID
	CUIntArray arItemsMatched;		// items that match the character typed

	UINT nItem = pMenu->GetMenuItemCount();
	for (UINT i=0; i< nItem; i++)
	{
		// get menu info
		CMenuItemInfo info;
		info.fMask = MIIM_DATA | MIIM_TYPE | MIIM_STATE;
		::GetMenuItemInfo(*pMenu, i, TRUE, &info);

		CMyItemData* pmd = (CMyItemData*)info.dwItemData;
		if ((info.fType & MFT_OWNERDRAW) && pmd && pmd->IsMyItemData())
		{
			CString& text = pmd->text;
			int iAmpersand = text.Find('&');
			if (iAmpersand >=0 && toupper(nChar)==toupper(text[iAmpersand+1]))
				arItemsMatched.Add(i);
		}
		if (info.fState & MFS_HILITE)
			iCurrentItem = i; // note index of current item
	}

	// arItemsMatched now contains indexes of items that match the char typed.
	//
	//   * if none: beep
	//   * if one:  execute it
	//   * if more than one: hilite next
	//
	UINT nFound = arItemsMatched.GetSize();
	if (nFound == 0)
		return 0;

	else if (nFound==1)
		return MAKELONG(arItemsMatched[0], MNC_EXECUTE);

	// more than one found--return 1st one past current selected item;
	UINT iSelect = 0;
	for (i=0; i < nFound; i++)
	{
		if (arItemsMatched[i] > iCurrentItem)
		{
			iSelect = i;
			break;
		}
	}

	nFlags;
	return MAKELONG(arItemsMatched[iSelect], MNC_SELECT);
}

//////////////////
// Handle WM_MENUSELECT: check for menu closed
//
void CCoolMenuManager::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	if (hSysMenu==NULL && nFlags==0xFFFF)
	{
		// Windows has closed the menu: restore all menus to original state
		while (!m_menuList.IsEmpty())
		{
			ConvertMenu(CMenu::FromHandle((HMENU)m_menuList.RemoveHead()),
				0, FALSE, FALSE);
		}
	}
	nItemID;
}

//////////////////
// Append the name of accelerator for given command ID to menu string.
// sItemName is menu item name, which will have the accelerator appended.
// For example, might call with sItemName = "File &Open" and return with
// sItemName = "File &Open\tCtrl-O". Returns BOOL = whether string changed.
//
BOOL CCoolMenuManager::AppendAccelName(CString& sItemName, UINT nID)
{
	int iTabPos = sItemName.Find('\t');
	if (iTabPos > 0)
		sItemName = sItemName.Left(iTabPos);

	BOOL bFound = FALSE;
	for (ACCEL* pa = GetAccel((WORD)nID); pa; pa -= pa->cmd)
	{
		sItemName += bFound ? _T(", ") : _T("\t");
		if (pa->fVirt & FALT)
			sItemName += _T("Alt+");
		if (pa->fVirt & FCONTROL)
			sItemName += _T("Ctrl+");
		if (pa->fVirt & FSHIFT)	
			sItemName += _T("Shift+");
		if (pa->fVirt & FVIRTKEY)
		{
			TCHAR keyname[64];
			UINT vkey = MapVirtualKey(pa->key, 0)<<16;
			GetKeyNameText(vkey, keyname, sizeof(keyname));
			sItemName += keyname;
		}
		else
			sItemName += (char)pa->key;

		bFound = TRUE;
		if (pa->cmd == 0)
			break;
	}
	return bFound;
}

//////////////////
// This function fixes MFC's diseased dot bitmap used for
// "radio-style" menu items (CCmdUI->SetRadio), which is completely
// wrong if the menu font is large. 
//
void CCoolMenuManager::FixMFCDotBitmap()
{
	HBITMAP hbmDot = GetMFCDotBitmap();
	if (hbmDot)
	{
		// Draw a centered dot of appropriate size
		BITMAP bm;
		::GetObject(hbmDot, sizeof(bm), &bm);
		CRect rcDot(0,0, bm.bmWidth, bm.bmHeight);
		rcDot.DeflateRect((bm.bmWidth>>1)-2, (bm.bmHeight>>1)-2);

		CWindowDC dcScreen(NULL);
		CDC memdc;
		memdc.CreateCompatibleDC(&dcScreen);
		int nSave = memdc.SaveDC();
		memdc.SelectStockObject(BLACK_PEN);
		memdc.SelectStockObject(BLACK_BRUSH);
		memdc.SelectObject((HGDIOBJ)hbmDot);
		memdc.PatBlt(0, 0, bm.bmWidth, bm.bmHeight, WHITENESS);
		memdc.Ellipse(&rcDot);
		memdc.RestoreDC(nSave);
	}
}

//////////////////
// This function gets MFC's dot bitmap.
//
HBITMAP CCoolMenuManager::GetMFCDotBitmap()
{
	// The bitmap is stored in afxData.hbmMenuDot, but afxData is MFC-private,
	// so the only way to get it is create a menu, set the radio check,
	// and then see what bitmap MFC set in the menu item.
	CMenu menu;
	VERIFY(menu.CreateMenu());
	VERIFY(menu.AppendMenu(MFT_STRING, 0, (LPCTSTR)NULL));
	CCmdUI cui;
	cui.m_pMenu = &menu;
	cui.m_nIndex = 0;
	cui.m_nIndexMax = 1;
	cui.SetRadio(TRUE);
	CMenuItemInfo info;
	info.fMask = MIIM_CHECKMARKS;
	GetMenuItemInfo(menu, 0, MF_BYPOSITION, &info);
	HBITMAP hbmDot = info.hbmpChecked;
	menu.DestroyMenu();
	return hbmDot;
}
