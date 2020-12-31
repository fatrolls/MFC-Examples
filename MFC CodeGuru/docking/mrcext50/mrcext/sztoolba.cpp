// MRCEXT: Micro Focus Extension DLL for MFC 2.1+
// Copyright (C)1994-5	Micro Focus Inc, 2465 East Bayshore Rd, Palo Alto, CA 94303.
// 
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation. In addition, you may also charge for any
//  application	using MRCEXT, and are under no obligation to supply source
//  code. You must accredit Micro Focus Inc in the "About Box", or banner
//  of your application. 
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should also have received a copy of the GNU General Public License with this
//  software, also indicating additional rights you have when using MRCEXT.  
//
//
// sztoolba.cpp : implementation file
// $Date:   12 Jan 1998 17:33:32  $
// $Author:   MRC  $
// 
//
// classes in this file
// CMRCSizeToolBar - a sizeable toolbar. A sizeable control bar containing a CToolBarCtrl object.
//				  which responds to tooltips/command enabling through the normal MFC architecture
//
// CToolCmdUI   - CCmdUI private class.

#include "mrcstafx.h"
#include "mrcresrc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMRCSizeToolBar

IMPLEMENT_DYNAMIC(CMRCSizeToolBar, CMRCSizeControlBar);

CMRCSizeToolBar::CMRCSizeToolBar(int nStyle) : CMRCSizeControlBar(nStyle)
{
	// top and bottom borders are 1 larger than default for ease of grabbing
	m_cyTopBorder = 3;
	m_cyBottomBorder = 3;
    
	// default image/button sizes
    m_sizeImage.cx = 16;
	m_sizeImage.cy = 15;
	m_sizeButton.cx = 23;
	m_sizeButton.cy = 22;
	m_pBitmapIds = NULL;
	m_nBitmapButtons = 0;
}


CMRCSizeToolBar::~CMRCSizeToolBar()
{
}



BEGIN_MESSAGE_MAP(CMRCSizeToolBar, CMRCSizeControlBar)
	//{{AFX_MSG_MAP(CMRCSizeToolBar)
	ON_WM_NCCREATE()
	ON_WM_PAINT()
    ON_WM_NCCALCSIZE()
    ON_WM_NCPAINT()
    //}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TBN_QUERYINSERT, OnTBNQueryInsert)
	ON_NOTIFY_REFLECT(TBN_QUERYDELETE, OnTBNQueryDelete)
	ON_NOTIFY_REFLECT(TBN_BEGINADJUST, OnTBNBeginAdjust)
	ON_NOTIFY_REFLECT(TBN_TOOLBARCHANGE, OnTBNToolBarChange)
  	ON_NOTIFY_REFLECT(TBN_GETBUTTONINFO, OnTBNGetButtonInfo)
    ON_COMMAND(ID_MRC_CUSTOMIZE, Customize)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMRCSizeToolBar message handlers


#define DOCKED_HORZ_BORDER 6
#define DOCKED_VERT_BORDER 4

//-------------------------------------------------------------------
void CMRCSizeToolBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
//-------------------------------------------------------------------
{
	GetToolBarCtrl().AutoSize();        // autosize the toolbar
    Invalidate();                       // ensure buttons redraw...
}


//-----------------------------------------------------------------------------
BOOL CMRCSizeToolBar::Create(CWnd * pParent, DWORD dwStyle, UINT nID, LPRECT pRect)
//-----------------------------------------------------------------------------
{
	// if no rectangle supplied, then what is hopefully as sensible default.
	// ie a single row of buttons
	CRect rect;
	if (pRect != NULL)
		rect.CopyRect(pRect);
	else
	{
		pParent->GetClientRect(&rect);
		rect.left = 0;
		rect.top = 0;
		rect.bottom = m_sizeImage.cy + 18;
		rect.right -= 8;
	}
    // the rectangle specifies the default floating size.
   	m_FloatSize = rect.Size();
	m_HorzDockSize = m_FloatSize;
    m_VertDockSize.cy = m_HorzDockSize.cx;
    m_VertDockSize.cx = m_HorzDockSize.cy;
	
	// save the style
	m_dwStyle = dwStyle;
	if (nID == AFX_IDW_TOOLBAR)
		m_dwStyle |= CBRS_HIDE_INPLACE;

	dwStyle &= ~CBRS_ALL;
	dwStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE
                    | TBSTYLE_WRAPABLE;

	// If there a list of bitmap id's, then let the user configure the toolbar
	if (m_pBitmapIds != NULL)
		dwStyle |= CCS_ADJUSTABLE;

    // initialize common controls
	InitCommonControls();

	// create the HWND
	if (!CWnd::Create(TOOLBARCLASSNAME, NULL, dwStyle, rect, pParent, nID))
		return FALSE;

	return TRUE;
}


//-----------------------------------------------------------------------------
BOOL CMRCSizeToolBar::OnNcCreate(LPCREATESTRUCT lpCS)
//-----------------------------------------------------------------------------
{
	if (!CControlBar::OnNcCreate(lpCS))
		return FALSE;

	// if the owner was set before the toolbar was created, set it now
	if (m_hWndOwner != NULL)
		DefWindowProc(TB_SETPARENT, (WPARAM)m_hWndOwner, 0);

	DefWindowProc(TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	return TRUE;
}


// These are functions designed as 1-1 replacements for older VC2.x CToolBar functions.
// Note that LoadToolBar() is not supported

//-----------------------------------------------------------------------------
BOOL CMRCSizeToolBar::LoadBitmap(LPCTSTR lpszResourceName)
//-----------------------------------------------------------------------------
{
	ASSERT_VALID(this);
	ASSERT(lpszResourceName != NULL);

	// determine location of the bitmap in resource fork
	HINSTANCE hInstImageWell = AfxFindResourceHandle(lpszResourceName, RT_BITMAP);
	HRSRC hRsrcImageWell = ::FindResource(hInstImageWell, lpszResourceName, RT_BITMAP);
	if (hRsrcImageWell == NULL)
		return FALSE;

	// load the bitmap
	HBITMAP hbmImageWell;
#ifndef _MAC
	hbmImageWell = AfxLoadSysColorBitmap(hInstImageWell, hRsrcImageWell);
#else
	hbmImageWell = AfxLoadSysColorBitmap(hInstImageWell, hRsrcImageWell, m_bMonochrome);
#endif

	CSize sizeImage(16, 15);
	CSize sizeButton(16 + 7, 15 + 7);
	SetSizes(sizeButton, m_sizeImage);

	BITMAP bitmap;
	VERIFY(::GetObject(hbmImageWell, sizeof(BITMAP), &bitmap));
	
    TBADDBITMAP addBitmap;
	addBitmap.hInst = NULL; // makes TBADDBITMAP::nID behave a HBITMAP
	addBitmap.nID = (UINT)hbmImageWell;
	DWORD bResult =  DefWindowProc(TB_ADDBITMAP,
	            bitmap.bmWidth / m_sizeImage.cx, (LPARAM)&addBitmap) == 0;

	return TRUE;
}

    
    
    


//-----------------------------------------------------------------------------
void CMRCSizeToolBar::SetSizes(SIZE sizeButton, SIZE sizeImage)
//-----------------------------------------------------------------------------
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));

	// sizes must be non-zero and positive
	ASSERT(sizeButton.cx > 0 && sizeButton.cy > 0);
	ASSERT(sizeImage.cx > 0 && sizeImage.cy > 0);

	// button must be big enough to hold image
	//   + 7 pixels on x
	//   + 6 pixels on y
	ASSERT(sizeButton.cx >= sizeImage.cx + 7);
	ASSERT(sizeButton.cy >= sizeImage.cy + 6);

	// set the sizes via TB_SETBITMAPSIZE and TB_SETBUTTONSIZE
	VERIFY(SendMessage(TB_SETBITMAPSIZE, 0, MAKELONG(sizeImage.cx, sizeImage.cy)));
	VERIFY(SendMessage(TB_SETBUTTONSIZE, 0, MAKELONG(sizeButton.cx, sizeButton.cy)));

	Invalidate();   // just to be nice if called when toolbar is visible
}


//-----------------------------------------------------------------------------
void CMRCSizeToolBar::SetBitmapIds(UINT * pIds, int nButtons)
//-----------------------------------------------------------------------------
{
	m_pBitmapIds = pIds;
	m_nBitmapButtons = nButtons;
}


//-----------------------------------------------------------------------------
int CMRCSizeToolBar::FindBitmapIndex(UINT nID)
//-----------------------------------------------------------------------------
{
	ASSERT(m_pBitmapIds != NULL);
	for (int i = 0; i < m_nBitmapButtons ; i++)
	{
		if (m_pBitmapIds[i] == (int)nID)
			return i;
	}
	return -1;
}



//-----------------------------------------------------------------------------
BOOL CMRCSizeToolBar::SetButtons(UINT * lpIDArray, int nIDCount)
// emulate CToolBar::SetButtons()
//-----------------------------------------------------------------------------
{
    ASSERT_VALID(this);
	ASSERT(nIDCount >= 1);  // must be at least one of them
	ASSERT(lpIDArray == NULL ||
		AfxIsValidAddress(lpIDArray, sizeof(UINT) * nIDCount, FALSE));

    // delete all existing buttons
	int nCount = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
	while (nCount--)
		VERIFY(DefWindowProc(TB_DELETEBUTTON, 0, 0));

	if (lpIDArray != NULL)
	{
		// add new buttons to the common control
		TBBUTTON button;
        memset(&button, 0, sizeof(TBBUTTON));
		int iImage = 0;
		for (int i = 0; i < nIDCount; i++)
		{
			button.fsState = TBSTATE_ENABLED;
			if ((button.idCommand = *lpIDArray++) == 0)
			{
				// separator
				button.fsStyle = TBSTYLE_SEP;
				// width of separator includes 8 pixel overlap
				button.iBitmap = 8;
			}
			else
			{
				// a command button with image
				button.fsStyle = TBSTYLE_BUTTON;
				button.iBitmap = FindBitmapIndex(button.idCommand);
			}
            if (!DefWindowProc(TB_ADDBUTTONS, 1, (LPARAM)&button))
				return FALSE;
		}
	}
	else
	{
		// add 'blank' buttons
		TBBUTTON button; memset(&button, 0, sizeof(TBBUTTON));
		button.fsState = TBSTATE_ENABLED;
		for (int i = 0; i < nIDCount; i++)
		{
			ASSERT(button.fsStyle == TBSTYLE_BUTTON);
			if (!DefWindowProc(TB_ADDBUTTONS, 1, (LPARAM)&button))
				return FALSE;
		}
	}

	return TRUE;
}	




//-----------------------------------------------------------------------------
afx_msg void CMRCSizeToolBar::OnTBNBeginAdjust(NMHDR *pNMHDR, LRESULT * pResult)
//-----------------------------------------------------------------------------
{
}


//-----------------------------------------------------------------------------
afx_msg void CMRCSizeToolBar::OnTBNQueryInsert(NMHDR *pNMHDR, LRESULT * pResult)
//-----------------------------------------------------------------------------
{
	*pResult = TRUE;		// always allow buttons to be inserted
}


//-----------------------------------------------------------------------------
afx_msg void CMRCSizeToolBar::OnTBNQueryDelete(NMHDR *pNMHDR, LRESULT * pResult)
//-----------------------------------------------------------------------------
{
	*pResult = TRUE;		// always allow buttons to be deleted
}

//-----------------------------------------------------------------------------
afx_msg void CMRCSizeToolBar::OnTBNToolBarChange(NMHDR *pNMHDR, LRESULT * pResult)
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
afx_msg void CMRCSizeToolBar::OnTBNGetButtonInfo(NMHDR *pNMHDR, LRESULT * pResult)
// Return information for bitmap indexes in the toolbar
//-----------------------------------------------------------------------------
{
	TBNOTIFY * pTBN = (TBNOTIFY *)pNMHDR;
	
	int nIndex = pTBN->iItem;
	if (nIndex < m_nBitmapButtons)
	{
		*pResult = TRUE;

 	    UINT nButtonId = m_pBitmapIds[nIndex];
 	    pTBN->tbButton.iBitmap = nIndex;
 	    pTBN->tbButton.idCommand = nButtonId;
		pTBN->tbButton.fsState = TBSTATE_ENABLED;
		pTBN->tbButton.fsStyle = TBSTYLE_BUTTON;
		pTBN->tbButton.iString = 0;		
		if (pTBN->pszText != NULL)
		{		
			CString strText;
			if (strText.LoadString(nButtonId))
			{
				char * pTipText = strchr(strText, '\n');   // tool tip is after "\n" in the string
				if (pTipText != NULL)
				{	
					strncpy(pTBN->pszText, pTipText + 1, pTBN->cchText);
           			return;
				}
			}
			TRACE("CMRCSizeToolBar:No Tooltip prompt for ID=%d\n", nButtonId);
			strncpy(pTBN->pszText, "???", pTBN->cchText);
		}
	}
	else 
		*pResult = FALSE;
}


//-----------------------------------------------------------------------------
void CMRCSizeToolBar::Customize()
//-----------------------------------------------------------------------------
{
    GetToolBarCtrl().Customize();
}


//--------------------------------------------------------------------------
LONG CMRCSizeToolBar::OnAddContextMenuItems(WPARAM wParam, LPARAM lParam)
// add "customise" option to menu
//--------------------------------------------------------------------------
{
    CMRCSizeControlBar::OnAddContextMenuItems(wParam, lParam);
    
    if (GetStyle() & CCS_ADJUSTABLE)
    {
        HMENU hMenu = (HMENU)lParam;		// handle of menu.
		CString strMenu;
        VERIFY(strMenu.LoadString(ID_MRC_CUSTOMIZE));
        ::AppendMenu(hMenu, MF_STRING, ID_MRC_CUSTOMIZE, strMenu);
	}
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CToolBar idle update through CToolCmdUI class. 

class CToolCmdUI : public CCmdUI        // class private to this file !
{
public: // re-implementations only
	virtual void Enable(BOOL bOn);
	virtual void SetCheck(int nCheck);
	virtual void SetText(LPCTSTR lpszText);
};

//-----------------------------------------------------------------------------
void CToolCmdUI::Enable(BOOL bOn)
//-----------------------------------------------------------------------------
{
	m_bEnableChanged = TRUE;
	CMRCSizeToolBar* pSizeToolBar = (CMRCSizeToolBar *)m_pOther;
	CToolBarCtrl & rToolBar = pSizeToolBar->GetToolBarCtrl();

	ASSERT(m_nIndex < m_nIndexMax);

	// Get toolbar button state
	TBBUTTON TB;
	rToolBar.GetButton(m_nIndex, &TB);
	UINT nNewState = TB.fsState & ~TBSTATE_ENABLED;
	if (bOn)
		nNewState |= TBSTATE_ENABLED;
	if (nNewState != TB.fsState)
		rToolBar.SetState(m_nID, nNewState);
}


//-----------------------------------------------------------------------------
void CToolCmdUI::SetCheck(int nCheck)
//-----------------------------------------------------------------------------
{
	ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
	CMRCSizeToolBar* pSizeToolBar = (CMRCSizeToolBar *)m_pOther;
	CToolBarCtrl & rToolBar = pSizeToolBar->GetToolBarCtrl();

	ASSERT(m_nIndex < m_nIndexMax);

	// Get toolbar button state
	TBBUTTON TB;
	rToolBar.GetButton(m_nIndex, &TB);
	UINT nNewState = TB.fsState & ~ (TBSTATE_CHECKED | TBSTATE_INDETERMINATE);
	
	if (nCheck == 1)
		nNewState |= TBSTATE_CHECKED;
	else
		if (nCheck == 2)
			nNewState |= TBSTATE_INDETERMINATE;
	
	if (nNewState != TB.fsState)
		rToolBar.SetState(m_nID, nNewState);

   // should we set the button style too ?
   //	pToolBar->_SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX); */
}


//-----------------------------------------------------------------------------
void CToolCmdUI::SetText(LPCTSTR)
//-----------------------------------------------------------------------------
{
	// ignore it
}


//-----------------------------------------------------------------------------
void CMRCSizeToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
//-----------------------------------------------------------------------------
{
	CToolCmdUI state;
	state.m_pOther = this;

	state.m_nIndexMax = GetToolBarCtrl().GetButtonCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		TBBUTTON TB;
		GetToolBarCtrl().GetButton(state.m_nIndex, &TB);
		if (!(TB.fsStyle & TBSTYLE_SEP))
		{
			state.m_nID = TB.idCommand;
			state.DoUpdate(pTarget, bDisableIfNoHndler);
		}
	}
	// update any dialog controls added to the toolbar (probably unlikely in this case)
	UpdateDialogControls(pTarget, bDisableIfNoHndler);

}


//-----------------------------------------------------------------------------
CToolBarCtrl & CMRCSizeToolBar::GetToolBarCtrl() const
//-----------------------------------------------------------------------------
{
	return *(CToolBarCtrl*)this; 
}


//-----------------------------------------------------------------------------
void CMRCSizeToolBar::OnPaint()
//-----------------------------------------------------------------------------
{
    Default();
}


//-----------------------------------------------------------------------------
void CMRCSizeToolBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
//-----------------------------------------------------------------------------
{
	// calculate border space (will add to top/bottom, subtract from right/bottom)
	CRect rect; rect.SetRectEmpty();
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	CControlBar::CalcInsideRect(rect, bHorz);
	ASSERT(rect.top >= 2);

	// adjust non-client area for border space
	lpncsp->rgrc[0].left += rect.left;
	lpncsp->rgrc[0].top += rect.top - 2;
	lpncsp->rgrc[0].right += rect.right;
	lpncsp->rgrc[0].bottom += rect.bottom;
}


//-----------------------------------------------------------------------------
void CMRCSizeToolBar::OnNcPaint()
//-----------------------------------------------------------------------------
{
	EraseNonClient();
}


//-----------------------------------------------------------------------------
int CMRCSizeToolBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
//-----------------------------------------------------------------------------
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));

	// check child windows first by calling CControlBar
	int nHit = CControlBar::OnToolHitTest(point, pTI);
	if (nHit != -1)
		return nHit;

	// now hit test against CToolBar buttons
	CMRCSizeToolBar * pBar = (CMRCSizeToolBar *) this;  // cast as this function is const
    
    int nButtons = (int)pBar->DefWindowProc(TB_BUTTONCOUNT, 0, 0);
	for (int i = 0; i < nButtons; i++)
	{
		CRect rect;
		TBBUTTON button;
		if (pBar->DefWindowProc(TB_GETITEMRECT, i, (LPARAM)&rect) &&
			rect.PtInRect(point) &&
			pBar->DefWindowProc(TB_GETBUTTON, i, (LPARAM)&button) &&
			!(button.fsStyle & TBSTYLE_SEP))
		{
			int nHit = button.idCommand;
			if (pTI != NULL)
			{
				pTI->hwnd = m_hWnd;
				pTI->rect = rect;
				pTI->uId = nHit;
				pTI->lpszText = LPSTR_TEXTCALLBACK;
			}
			// found matching rect, return the ID of the button
			return nHit != 0 ? nHit : -1;
		}
	}
	return -1;
}
