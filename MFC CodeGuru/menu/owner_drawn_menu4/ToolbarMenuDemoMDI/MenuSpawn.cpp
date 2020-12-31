// MenuSpawn.cpp: implementation of the CMenuSpawn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToolbarMenuDemoMDI.h"
#include "MenuSpawn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuSpawn::CMenuSpawn()
{
	Init();
}

CMenuSpawn::CMenuSpawn(const bool _IsPopup)
{
	Init();
	bIsPopup = _IsPopup;
}

CMenuSpawn::~CMenuSpawn()
{
	if (iSpawnItem > 0)
	{
		for (int t = 0; t < iSpawnItem; t++)
			if (pSpawnItem[t]) delete pSpawnItem[t];

		GlobalFree((HGLOBAL) pSpawnItem);
	}
	if (iImageItem > 0)
	{
		GlobalFree((HGLOBAL) pImageItem);
	}
	if (hMenuFont) ::DeleteObject((HGDIOBJ)hMenuFont);
//	if (hGuiFont) ::DeleteObject((HGDIOBJ)hGuiFont);
}

void CMenuSpawn::TransparentBlt(CDC * pDestDc, int x, int y, int w, int h, CBitmap * pBmp, int sx, int sy, COLORREF crTransparent)
{
	CDC memDC, maskDC, tempDC;
	maskDC.CreateCompatibleDC(pDestDc);
	CBitmap maskBitmap;
	
	//add these to store return of SelectObject() calls
	CBitmap* pOldMemBmp = NULL;
	CBitmap* pOldMaskBmp = NULL;
	
	memDC.CreateCompatibleDC(pDestDc);
	tempDC.CreateCompatibleDC(pDestDc);
	CBitmap bmpImage;
	bmpImage.CreateCompatibleBitmap( pDestDc, w, h);
	pOldMemBmp = memDC.SelectObject( &bmpImage );

	CBitmap * oldBmp = tempDC.SelectObject(pBmp);
	
	memDC.BitBlt( 0,0,w, h, &tempDC, sx, sy, SRCCOPY );
	
	// Create monochrome bitmap for the mask
	maskBitmap.CreateBitmap(w, h, 1, 1, NULL);
	pOldMaskBmp = maskDC.SelectObject( &maskBitmap );
	memDC.SetBkColor(crTransparent);
	
	// Create the mask from the memory DC
	maskDC.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
	
	memDC.SetBkColor(RGB(0,0,0));
	memDC.SetTextColor(RGB(255,255,255));
	memDC.BitBlt(0, 0, w, h, &maskDC, 0, 0, SRCAND);
	
	// Set the foreground to black. See comment above.
	pDestDc->SetBkColor(RGB(255,255,255));
	pDestDc->SetTextColor(RGB(0,0,0));
	pDestDc->BitBlt(x, y, w, h, &maskDC, 0, 0, SRCAND);
	
	// Combine the foreground with the background
	pDestDc->BitBlt(x, y, w, h, &memDC, 0, 0, SRCPAINT);
	
	tempDC.SelectObject(oldBmp);
	if (pOldMaskBmp) maskDC.SelectObject( pOldMaskBmp );
	if (pOldMemBmp)  memDC.SelectObject( pOldMemBmp );
}



void CMenuSpawn::Init()
{
	crMenuText = GetSysColor(COLOR_MENUTEXT);
	crMenuTextSel = GetSysColor(COLOR_HIGHLIGHTTEXT);

	cr3dFace = GetSysColor(COLOR_3DFACE);
	crMenu = GetSysColor(COLOR_MENU);
	crHighlight = GetSysColor(COLOR_HIGHLIGHT);
	cr3dHilight = GetSysColor(COLOR_3DHILIGHT);
	cr3dShadow = GetSysColor(COLOR_3DSHADOW);
	crGrayText = GetSysColor(COLOR_GRAYTEXT);

	m_clrBtnFace = GetSysColor(COLOR_BTNFACE);
	m_clrBtnHilight = GetSysColor(COLOR_BTNHILIGHT);
	m_clrBtnShadow = GetSysColor(COLOR_BTNSHADOW);

	iSpawnItem = 0;
	pSpawnItem = NULL;

	iImageItem = 0;
	pImageItem = NULL;

	szImage = CSize(20,20);

	hMenuFont = NULL;
	COLORMAP cMap[3] = { 
		{ RGB(128,128,128), cr3dShadow }, 
		{ RGB(192,192,192), cr3dFace }, 
		{ RGB(255,255,255), cr3dHilight }
	};
	CBitmap bmp;
	bmp.LoadMappedBitmap(IDB_MENUCHK, 0, cMap, 3);
	ilOther.Create(19, 19, ILC_COLOR4|ILC_MASK, 1, 0);
	ilOther.Add(&bmp, cr3dFace);
	bmp.DeleteObject();

	NONCLIENTMETRICS ncm;
	memset(&ncm, 0, sizeof(ncm));
	ncm.cbSize = sizeof(ncm);

	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, (PVOID) &ncm, 0);

	hGuiFont = ::CreateFontIndirect(&ncm.lfMenuFont);

	bIsPopup = false;
	bBackBitmap = false;
}

bool CMenuSpawn::AddToolBarResource(unsigned int resId)
{
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(resId), RT_TOOLBAR);
	if (hRsrc == NULL) return false;

	HGLOBAL hGlb = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hGlb == NULL) return false;

	ToolBarData* pTBData = (ToolBarData*) ::LockResource(hGlb);
	if (pTBData == NULL) return false;
	
	ASSERT(pTBData->wVersion == 1);

	CBitmap bmp;
	bmp.LoadBitmap(resId);
	int nBmpItems = ilList.Add(&bmp, RGB(192,192,192));
	bmp.DeleteObject();

	WORD* pItem = (WORD*)(pTBData+1);
	
	for(int i=0; i<pTBData->wItemCount; i++, pItem++)
	{
		if(*pItem != ID_SEPARATOR)
			AddImageItem(nBmpItems++, (WORD) *pItem);
	}
// ** it seem that Windows doesn't free these resource (from Heitor Tome)
    ::UnlockResource(hGlb);
    ::FreeResource(hGlb);
// **
	return true;
}

bool CMenuSpawn::LoadToolBarResource(unsigned int resId)
{
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(resId), RT_TOOLBAR);
	if (hRsrc == NULL) return false;

	HGLOBAL hGlb = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hGlb == NULL) return false;

	ToolBarData* pTBData = (ToolBarData*) ::LockResource(hGlb);
	if (pTBData == NULL) return false;
	
	ASSERT(pTBData->wVersion == 1);

	szImage.cx = (int) pTBData->wWidth;
	szImage.cy = (int) pTBData->wHeight;

	if (ilList.Create(szImage.cx, szImage.cy, ILC_COLOR4|ILC_MASK, pTBData->wItemCount, 0) == false)
		return false;

	ilList.SetBkColor(cr3dFace);

	CBitmap bmp;
	bmp.LoadBitmap(resId);
	ilList.Add(&bmp, RGB(192,192,192));
	bmp.DeleteObject();

	WORD* pItem = (WORD*)(pTBData+1);
	int nBmpItems = 0;
	for(int i=0; i<pTBData->wItemCount; i++, pItem++)
	{
		if(*pItem != ID_SEPARATOR)
			AddImageItem(nBmpItems++, (WORD) *pItem);
	}
// ** it seem that Windows doesn't free these resource (from Heitor Tome)
    ::UnlockResource(hGlb);
    ::FreeResource(hGlb);
// **
	return true;
}

void CMenuSpawn::AddImageItem(const int idx, WORD cmd)
{
	if (iImageItem == 0)
		pImageItem = (ImageItem *) GlobalAlloc(GPTR, sizeof(ImageItem));
	else
		pImageItem = (ImageItem *) GlobalReAlloc((HGLOBAL) pImageItem, sizeof(ImageItem) * (iImageItem + 1), GMEM_MOVEABLE|GMEM_ZEROINIT);
	
	ASSERT(pImageItem);
	pImageItem[iImageItem].iCmd = (int) cmd;
	pImageItem[iImageItem].iImageIdx = idx;
	iImageItem ++;
}

void CMenuSpawn::RemapMenu(CMenu * pMenu)
{
	static int iRecurse = 0;
	iRecurse ++;

	ASSERT(pMenu);
	int nItem = pMenu->GetMenuItemCount();
	while ((--nItem)>=0)
	{
		UINT itemId = pMenu->GetMenuItemID(nItem);
		if (itemId == (UINT) -1)
		{
			CMenu *pops = pMenu->GetSubMenu(nItem);
			if (pops) RemapMenu(pops);
			if (bIsPopup || iRecurse > 0)
			{
				CString cs;
				pMenu->GetMenuString(nItem, cs, MF_BYPOSITION);
				if (cs != "")
				{
					SpawnItem * sp = AddSpawnItem(cs, (!bIsPopup && iRecurse == 1) ? -4 : -2);
					pMenu->ModifyMenu(nItem,MF_BYPOSITION|MF_OWNERDRAW, (UINT) -1, (LPCTSTR)sp);
				}
			}
		}
		else
		{
			if (itemId != 0)
			{
				UINT oldState = pMenu->GetMenuState(nItem,MF_BYPOSITION);
				if (!(oldState&MF_OWNERDRAW) && !(oldState&MF_BITMAP))
				{
					ASSERT(oldState != (UINT)-1);
					CString cs;
					pMenu->GetMenuString(nItem, cs, MF_BYPOSITION);
					SpawnItem * sp = AddSpawnItem(cs, itemId);
					pMenu->ModifyMenu(nItem,MF_BYPOSITION|MF_OWNERDRAW|oldState, (LPARAM)itemId, (LPCTSTR)sp);
				}
			}
			else
			{
				UINT oldState = pMenu->GetMenuState(nItem,MF_BYPOSITION);
				if (!(oldState&MF_OWNERDRAW) && !(oldState&MF_BITMAP))
				{
					ASSERT(oldState != (UINT)-1);
					SpawnItem * sp = AddSpawnItem("--", -3);
					pMenu->ModifyMenu(nItem,MF_BYPOSITION|MF_OWNERDRAW|oldState, (LPARAM)itemId, (LPCTSTR)sp);
				}
			}
		}
	}
	iRecurse --;
}

CMenuSpawn::SpawnItem * CMenuSpawn::AddSpawnItem(const char * txt, const int cmd)
{
	if (iSpawnItem == 0)
		pSpawnItem = (SpawnItem **) GlobalAlloc(GPTR, sizeof(SpawnItem));
	else
		pSpawnItem = (SpawnItem **) GlobalReAlloc((HGLOBAL) pSpawnItem, sizeof(SpawnItem) * (iSpawnItem + 1), GMEM_MOVEABLE|GMEM_ZEROINIT);

	ASSERT(pSpawnItem);

	SpawnItem * p = new SpawnItem;
	ASSERT(p);
	pSpawnItem[iSpawnItem] = p;
	lstrcpy(p->cText, txt);
	p->iCmd = cmd;

	if (cmd >= 0) p->iImageIdx = FindImageItem(cmd);
	else p->iImageIdx = cmd;

	iSpawnItem ++;
	return p;
}

int CMenuSpawn::FindImageItem(const int cmd)
{
	for (int t = 0; t < iImageItem; t++)
		if (pImageItem[t].iCmd == cmd) return pImageItem[t].iImageIdx;

	return -1;
}

bool CMenuSpawn::DrawItem(LPDRAWITEMSTRUCT lp)
{
	bool res = false;
	if (lp->CtlType == ODT_MENU)
	{
		UINT id = lp->itemID;
		UINT state = lp->itemState;
		bool bEnab = !(state & ODS_DISABLED);
		bool bSelect = (state & ODS_SELECTED) ? true : false;
		bool bChecked = (state & ODS_CHECKED) ? true : false;

		SpawnItem * pItem = (SpawnItem *) lp->itemData;
		if (pItem)
		{
			CDC * pDC = CDC::FromHandle(lp->hDC);
			CFont * pft = CFont::FromHandle((HFONT) hMenuFont ? hMenuFont : hGuiFont);
			CFont * of = pDC->SelectObject(pft);
			CRect rc(lp->rcItem);
			CRect rcImage(rc), rcText(rc);
			rcImage.right = rcImage.left + rc.Height();
			rcImage.bottom = rc.bottom;

			if (bBackBitmap) 
			{
				CDC tempDC;
				tempDC.CreateCompatibleDC(pDC);
				tempDC.FillSolidRect(rc, crMenu);
				CBitmap * ob = tempDC.SelectObject(&bmpBack);
				pDC->FillSolidRect(rc, crMenu);
				pDC->BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &tempDC, rc.left, rc.top, SRCCOPY );
			}

			if (pItem->iCmd == -3) // is a separator
			{
				CPen pnDk(PS_SOLID,1,cr3dShadow);
				CPen pnLt(PS_SOLID,1,cr3dHilight);
				CPen * opn = pDC->SelectObject(&pnDk);
				pDC->MoveTo(rc.left + 2, rc.top + 2);
				pDC->LineTo(rc.right - 2, rc.top + 2);
				pDC->SelectObject(&pnLt);
				pDC->MoveTo(rc.left + 2, rc.top + 3);
				pDC->LineTo(rc.right - 2, rc.top + 3);
				pDC->SelectObject(opn);
			}
			else if (pItem->iCmd == -4) // is a title item
			{
				CString cs(pItem->cText), cs1;
				CRect rcBdr(rcText);

				if (bSelect && bEnab)
				{
					rcText.top ++;
					rcText.left += 2;
				}
				pDC->FillSolidRect(rcText, crMenu);
				pDC->DrawText(cs, rcText, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
				if (bSelect && bEnab) pDC->Draw3dRect(rcBdr,cr3dShadow,cr3dHilight);
			}
			else
			{
				rcText.left += rcImage.right + 1;

				int obk = pDC->SetBkMode(TRANSPARENT);
				
				COLORREF ocr;
				if (bSelect)
				{
					if (pItem->iImageIdx >= 0 || (state & ODS_CHECKED))
						pDC->FillSolidRect(rcText, crHighlight);
					else
						pDC->FillSolidRect(rc, crHighlight);

					ocr = pDC->SetTextColor(crMenuTextSel);
				}
				else
				{
					if (!bBackBitmap) 
					{
						if (pItem->iImageIdx >= 0 || (state & ODS_CHECKED))
							pDC->FillSolidRect(rcText, crMenu);
						else
							pDC->FillSolidRect(rc/*rcText*/, crMenu);
					}
					ocr = pDC->SetTextColor(crMenuText);
				}

				if (pItem->iImageIdx >= 0)
				{
					int ay = (rcImage.Height() - szImage.cy) / 2;
					int ax = (rcImage.Width()  - szImage.cx) / 2;

					if (bSelect && bEnab)
						pDC->Draw3dRect(rcImage,cr3dHilight,cr3dShadow);
					else
					{
						if (!bBackBitmap) pDC->Draw3dRect(rcImage,crMenu,crMenu);
					}


					if (bEnab)
					{
						ilList.Draw(pDC, pItem->iImageIdx, CPoint(rcImage.left + ax, rcImage.top +ay), ILD_NORMAL);
					}
					else
					{
						HICON hIcon = ilList.ExtractIcon( pItem->iImageIdx );
						pDC->DrawState( CPoint(rcImage.left + ax, rcImage.top + ay ), szImage, (HICON)hIcon, DST_ICON | DSS_DISABLED, (CBrush *)NULL );
					}
				}
				else
				{
					if (bChecked)
					{
						int ay = (rcImage.Height() - szImage.cy) / 2;
						int ax = (rcImage.Width()  - szImage.cx) / 2;

						ilOther.Draw(pDC, 0, CPoint(rcImage.left + ax, rcImage.top + ay - 2), ILD_NORMAL);
					}
				}

				CString cs(pItem->cText), cs1;
				CSize sz;
				sz = pDC->GetTextExtent(cs);
				int ay1 = (rcText.Height() - sz.cy) / 2;
				rcText.top += ay1;
				rcText.left += 2;
				rcText.right -= 15;

				int tf = cs.Find('\t');
				if (tf >= 0)
				{
					cs1 = cs.Right(cs.GetLength() - tf - 1);
					cs = cs.Left(tf);
					if (!bEnab)
					{
						if (!bSelect)
						{
							CRect rcText1(rcText);
							rcText1.InflateRect(-1,-1);
							pDC->SetTextColor(cr3dHilight);
							pDC->DrawText(cs, rcText1, DT_VCENTER|DT_LEFT);
							pDC->DrawText(cs1, rcText1, DT_VCENTER|DT_RIGHT);
							pDC->SetTextColor(crGrayText);
							pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT);
							pDC->DrawText(cs1, rcText, DT_VCENTER|DT_RIGHT);
						}
						else
						{
							pDC->SetTextColor(crMenu);
							pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT);
							pDC->DrawText(cs1, rcText, DT_VCENTER|DT_RIGHT);
						}
					}
					else
					{
						pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT);
						pDC->DrawText(cs1, rcText, DT_VCENTER|DT_RIGHT);
					}
				}
				else 
				{
					if (!bEnab)
					{
						if (!bSelect)
						{
							CRect rcText1(rcText);
							rcText1.InflateRect(-1,-1);
							pDC->SetTextColor(cr3dHilight);
							pDC->DrawText(cs, rcText1, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
							pDC->SetTextColor(crGrayText);
							pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
						}
						else
						{
							pDC->SetTextColor(crMenu);
							pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
						}
					}
					else
						pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
				}
				pDC->SetTextColor(ocr);
				pDC->SetBkMode(obk);
			}

			pDC->SelectObject(of);
		}
		res = true;
	}
	return res;
}

bool CMenuSpawn::MeasureItem(LPMEASUREITEMSTRUCT lpm)
{
	bool res = false;
	if (lpm->CtlType == ODT_MENU)
	{
		UINT id = lpm->itemID;

		SpawnItem * pItem = (SpawnItem *) lpm->itemData;
		if (pItem)
		{
			if (pItem->iCmd == -3) // is a separator
			{
				lpm->itemWidth  = 10;
				lpm->itemHeight = 6;
			}
			else
			{
				CString cs(pItem->cText);
				if (cs != "")
				{
					CClientDC dc(AfxGetMainWnd());
					CFont * pft = CFont::FromHandle(hMenuFont ? hMenuFont : hGuiFont);
					CFont * of = dc.SelectObject(pft);
					CSize osz = dc.GetOutputTabbedTextExtent(cs,0,NULL);
					if (pItem->iCmd == -4)
					{
						CRect rci(0,0,0,0);
						dc.DrawText(cs, rci, DT_CALCRECT|DT_TOP|DT_VCENTER|DT_SINGLELINE);
						lpm->itemHeight = rci.Height();
						lpm->itemWidth = rci.Width();
					}
					else
					{
						lpm->itemHeight = szImage.cy + 5;
						if (osz.cy > (int) lpm->itemHeight) lpm->itemHeight = (int) osz.cy;
						lpm->itemWidth  = osz.cx + 2 + 15;
						lpm->itemWidth += lpm->itemHeight > (UINT) szImage.cx ? (UINT) lpm->itemHeight : (UINT) szImage.cx;
					}
					dc.SelectObject(of);
				}
				else
				{
					lpm->itemHeight = szImage.cy + 5;
					lpm->itemWidth  = 100;
				}
			}
		}
		res = true;
	}
	return res;
}

void CMenuSpawn::EnableMenuItems(CMenu * pMenu, CWnd * pParent)
{
	ASSERT(pMenu);
	ASSERT(pParent);

	int nItem = pMenu->GetMenuItemCount();
	CCmdUI state;
	state.m_pMenu = pMenu;
	state.m_nIndex = nItem-1;
	state.m_nIndexMax = nItem;

	while ((--nItem)>=0)
	{
		UINT itemId = pMenu->GetMenuItemID(nItem);
		if (itemId == (UINT) -1)
		{
			CMenu *pops = pMenu->GetSubMenu(nItem);
			if (pops) EnableMenuItems(pops, pParent);
		}
		else
		{
			if (itemId != 0)
			{
				state.m_nID = itemId;
				pParent->OnCmdMsg(itemId, CN_UPDATE_COMMAND_UI, &state, NULL);
				state.DoUpdate(pParent, true);
			}
		}
		state.m_nIndex = nItem-1;
	}
}


bool CMenuSpawn::SetFont(LOGFONT * lf)
{
	ASSERT(lf);
	if (hMenuFont) ::DeleteObject((HGDIOBJ)hMenuFont);
	hMenuFont = CreateFontIndirect(lf);
	return hMenuFont != NULL ? true : false;
}

bool CMenuSpawn::FindKeyboardShortcut(UINT nChar, UINT nFlags, CMenu * pMenu, LRESULT & lRes)
{
	ASSERT(pMenu);
	int nItem = pMenu->GetMenuItemCount();
	CString csChar((CHAR) nChar);
	csChar.MakeLower();
	while ((--nItem)>=0)
	{
		UINT itemId = pMenu->GetMenuItemID(nItem);
		if (itemId != 0)
		{
			MENUITEMINFO lpmi;
			ZeroMemory(&lpmi, sizeof(MENUITEMINFO));
			lpmi.cbSize = sizeof(MENUITEMINFO);
			lpmi.fMask = MIIM_DATA|MIIM_TYPE;
			ASSERT(pMenu->GetSafeHmenu());
			if (GetMenuItemInfo(pMenu->GetSafeHmenu(), nItem, TRUE, &lpmi))
			{
				if (lpmi.fType&MFT_OWNERDRAW)
				{
					SpawnItem * si = (SpawnItem *) lpmi.dwItemData;
					if (si)
					{
						CString csItem(si->cText);
						csItem.MakeLower();
						int iAmperIdx = csItem.Find('&');
						if (iAmperIdx >= 0)
						{
							csItem = csItem.Mid(iAmperIdx + 1, 1);
							if (csItem == csChar)
							{
								lRes = MAKELONG((WORD)nItem, 2);
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void CMenuSpawn::SetTextColor(const COLORREF crNormal, const COLORREF crSelected)
{
	crMenuText = crNormal;
	crMenuTextSel = crSelected;
}

void CMenuSpawn::SetBackBitmap(const int iRes)
{
	if (bmpBack.GetSafeHandle()) bmpBack.DeleteObject();
	bmpBack.LoadBitmap(iRes);
	bBackBitmap = true;
}

void CMenuSpawn::SetBackBitmap(const int iRes, COLORREF crBackColor)
{
	if (bmpBack.GetSafeHandle()) bmpBack.DeleteObject();
	COLORMAP cMap1 = { crBackColor, cr3dFace };
	bmpBack.LoadMappedBitmap(iRes, 0, &cMap1, 1);
	bBackBitmap = true;
}

bool CMenuSpawn::GetMenuItemText(CString &csText, CMenu * pMenu, const int cmd, bool bByPos)
{
	ASSERT(pMenu);

	UINT itemId = bByPos ? pMenu->GetMenuItemID(cmd) : cmd;
	if (itemId != 0)
	{
		MENUITEMINFO lpmi;
		ZeroMemory(&lpmi, sizeof(MENUITEMINFO));
		lpmi.cbSize = sizeof(MENUITEMINFO);
		lpmi.fMask = MIIM_DATA|MIIM_TYPE;
		ASSERT(pMenu->GetSafeHmenu());
		if (GetMenuItemInfo(pMenu->GetSafeHmenu(), cmd, bByPos, &lpmi))
		{
			if (lpmi.fType&MFT_OWNERDRAW)
			{
				SpawnItem * si = (SpawnItem *) lpmi.dwItemData;
				if (si)
				{
					csText = si->cText;
					return true;
				}
			}
			else
			{
				return pMenu->GetMenuString(cmd, csText, bByPos ? MF_BYPOSITION : MF_BYCOMMAND) > 0;
			}
		}
	}
	return false;
}

bool CMenuSpawn::IsSpawnMenu(CMenu * pMenu, const int iItem, const bool bByPos)
{
	ASSERT(pMenu);

	UINT itemId = bByPos ? pMenu->GetMenuItemID(iItem) : iItem;
	if (itemId != 0)
	{
		MENUITEMINFO lpmi;
		ZeroMemory(&lpmi, sizeof(MENUITEMINFO));
		lpmi.cbSize = sizeof(MENUITEMINFO);
		lpmi.fMask = MIIM_DATA|MIIM_TYPE;
		ASSERT(pMenu->GetSafeHmenu());
		if (GetMenuItemInfo(pMenu->GetSafeHmenu(), iItem, bByPos, &lpmi))
		{
			if (lpmi.fType&MFT_OWNERDRAW)
			{
				SpawnItem * si = (SpawnItem *) lpmi.dwItemData;
				if (si) return true;
			}
		}
	}
	return false;
}
