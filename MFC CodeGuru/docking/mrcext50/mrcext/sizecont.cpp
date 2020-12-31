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
// SIZECONT.CPP
// $Date:   23 Oct 1997 13:03:16  $
// $Revision:   1.2  $
// $Author:   MRC  $
// sizecont.cpp : implementation file
// Sizeable Control Bar

#include "mrcstafx.h"
#include "mrcext.h"
#include "mrcpriv.h"
#include "mrcresrc.h"

extern MRC_AUX_DATA afxData;

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMRCSizeControlBar, CControlBar)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CMRCSizeControlBar


CObArray * CMRCSizeControlBar::m_parrAllocBars;	

void CMRCSizeControlBar::TidyUp()
{
// just need to delete the contents of the array - the destructor will remove the element
// from the array. 
	if (m_parrAllocBars != NULL)
	{
		for (int i = m_parrAllocBars->GetUpperBound(); i >= 0; i--)
		{
			ASSERT((*m_parrAllocBars)[i]->IsKindOf(RUNTIME_CLASS(CMRCSizeControlBar)));
			delete ((*m_parrAllocBars)[i]);
		}
		delete m_parrAllocBars;
		m_parrAllocBars = NULL;
	}
}


CMRCSizeControlBar::CMRCSizeControlBar(int nStyle)
{
	m_Style = nStyle;						
    m_PrevSize.cx = 0xffff;         // dummy values so WindowPosChanged will respond correctly
    m_bPrevFloating = 3;            // neither TRUE not FALSE;

	m_FloatingPosition  = CPoint(0,0);	
	m_dwAllowDockingState = 0;
	if (nStyle & SZBARF_AUTOTIDY)
	{
		if (m_parrAllocBars == NULL)
			m_parrAllocBars = new CObArray;
		
		m_parrAllocBars->Add(this);
	}
}


CMRCSizeControlBar::~CMRCSizeControlBar()
{
	// if the bar was created with this flag, then ensure it is deleted with it also.
	if (m_Style & SZBARF_AUTOTIDY)
	{
		int i;
		for (i = m_parrAllocBars->GetUpperBound(); i >= 0; i--)
			if ((*m_parrAllocBars)[i] == this)	
			{
				m_parrAllocBars->RemoveAt(i);
				break;
			}
		ASSERT(i >= 0);			// means we didn't delete this item from the list
	}

	// This loop of debug code checks that we don;t have any other references in the array.
	// This happens if we changed the auto delete flag during the lifetime of the control bar.
#ifdef _DEBUG
	if (m_parrAllocBars != NULL)
	{
		for (int i = m_parrAllocBars->GetUpperBound(); i >= 0; i--)
			ASSERT ((*m_parrAllocBars)[i] != this);	
	}
#endif

    // delete the dock context here - in an attempt to call the correct destructor
    delete (CDragDockContext *) m_pDockContext;
    m_pDockContext = NULL;
}


BEGIN_MESSAGE_MAP(CMRCSizeControlBar, CControlBar)
        //{{AFX_MSG_MAP(CMRCSizeControlBar)
    ON_WM_WINDOWPOSCHANGED()
    ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
    ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_MRC_HIDE, OnHide)
	ON_COMMAND(ID_MRC_ALLOWDOCKING, OnToggleAllowDocking)
	ON_COMMAND(ID_MRC_MDIFLOAT,	OnFloatAsMDI)
	ON_MESSAGE(WM_ADDCONTEXTMENUITEMS, OnAddContextMenuItems)
	ON_MESSAGE(WM_USER_AFTERFLOAT_MSG, OnAfterFloatMessage)
	ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMRCSizeControlBar message handlers
CSize CMRCSizeControlBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
#ifdef _VERBOSE_TRACE
	CString strTitle;
	GetWindowText(strTitle);
	TRACE("CalcFixedLayout: '%s' Horz(%d,%d)\n", LPCTSTR(strTitle), 
				m_HorzDockSize.cx, m_HorzDockSize.cy);
#endif	
	CControlBar::CalcFixedLayout(bStretch, bHorz);
    if (IsFloating())
		return m_FloatSize;

    if (bHorz)
		return m_HorzDockSize;
	else
		return m_VertDockSize;
}


//-----------------------------------------------------------------------------------------
void CMRCSizeControlBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
//-----------------------------------------------------------------------------------------
{
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}


//-----------------------------------------------------------------------------------------
BOOL CMRCSizeControlBar::Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
							DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
// CWnd-style create - need ability to specific window class in order to prevent flicker
// during resizing. 
//-----------------------------------------------------------------------------------------
{
    ASSERT(pParentWnd != NULL);

    // have to set the style here
    m_dwStyle = dwStyle;

    CRect Rectx;
    Rectx = rect;

    // calculate a sensible default rectangle if that's what the user wanted...
    if (memcmp(&rect, &CFrameWnd::rectDefault, sizeof(RECT)) == 0)
    {
        pParentWnd->GetClientRect(&Rectx);
        CSize def;
        def.cx = Rectx.right / 2;
        def.cy = Rectx.bottom  / 4;
        Rectx.left = Rectx.right - def.cx;
        Rectx.top  = Rectx.bottom - def.cy;
	}

   	// the rectangle specifies the default floating size.
   	m_FloatSize = Rectx.Size();
	
	// set default values for the docked sizes, based on this size.
	m_HorzDockSize.cx = m_FloatSize.cx;
	m_HorzDockSize.cy = m_FloatSize.cy / 2;	

	m_VertDockSize.cx = m_HorzDockSize.cy * 3 / 2;
	m_VertDockSize.cy = m_HorzDockSize.cx * 2 / 3;
        
    return CControlBar::Create(lpszClassName, lpszWindowName, dwStyle, Rectx, pParentWnd, nID, pContext);
}


//-----------------------------------------------------------------------------------------
BOOL CMRCSizeControlBar::Create(CWnd * pParentWnd, LPCTSTR lpszWindowName, UINT nID,
								DWORD dwStyle, const RECT & rect)
//-----------------------------------------------------------------------------------------
{
	return Create(NULL, lpszWindowName, dwStyle, rect, pParentWnd, nID);
}


//--------------------------------------------------------------------------
void CMRCSizeControlBar::SetSizeDockStyle(DWORD dwStyle)
//--------------------------------------------------------------------------
{
	m_Style = dwStyle;
}


//------------------------------------------------------------------------------------
void CMRCSizeControlBar::EnableDocking(DWORD dwDockStyle)
// Largely a copy of CControlBar::EnableDocking() - but uses a different class for the
// m_pDockContext, to give us different (hopefully you'll think better) dragging 
// behaviour.
//------------------------------------------------------------------------------------
{
	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
    ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

    m_dwDockStyle = dwDockStyle;
    if (m_pDockContext == NULL)
    	m_pDockContext = new CDragDockContext(this);
	
    // permanently wire the bar's owner to its current parent
	if (m_hWndOwner == NULL)
    	m_hWndOwner = ::GetParent(m_hWnd);
}


//--------------------------------------------------------------------------
afx_msg LONG CMRCSizeControlBar::OnAfterFloatMessage(UINT wParam, LONG lParam)
// message handler. Force the parent of the control bar to update it's style
// after floating, otherwise we'll wait till an WM_NCHITTEST.
//--------------------------------------------------------------------------
{
	CWnd * pFrame = GetParentFrame();
	if (pFrame != NULL && pFrame->IsKindOf(RUNTIME_CLASS(CSizableMiniDockFrameWnd)))
		((CSizableMiniDockFrameWnd *) pFrame)->GetContainedBarType();
	
	return TRUE;			// message handled.
}


//--------------------------------------------------------------------------
BOOL CMRCSizeControlBar::OnEraseBkgnd(CDC* pDC)
// paint the background of the window - probably want a style flag to turn this
// off as for many control bars it won't be required.
//--------------------------------------------------------------------------
{
	CRect rect;
    pDC->GetClipBox(&rect);
    pDC->FillSolidRect(&rect, afxData.clrBtnFace); 
    return TRUE;
}




//------------------------------------------------------------------
void CMRCSizeControlBar::OnWindowPosChanged(WINDOWPOS * lpwndpos)
// This handler is used to notify sizeable bars if their size has
// changed, or if they are docked/undocked.
//------------------------------------------------------------------
{
    CControlBar::OnWindowPosChanged(lpwndpos);

    CSize NewSize(lpwndpos->cx, lpwndpos->cy);
    
	// This is meant to return "floating" if we're not docked yet...
    BOOL bFloating = IsProbablyFloating();
    
    int Flags = (NewSize == m_PrevSize ? 0 : 1);
    Flags |= (bFloating == m_bPrevFloating ? 0 : 2);
    if (Flags != 0)
    {
		m_PrevSize = NewSize;
        m_bPrevFloating = bFloating;
        OnSizedOrDocked(NewSize.cx, NewSize.cy, bFloating, Flags);
	}
}


//------------------------------------------------------------------
void CMRCSizeControlBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// override this function to respond to a redraw as a result of a
// resize or docked/undocked notification
//------------------------------------------------------------------
{
}


//------------------------------------------------------------------
BOOL CMRCSizeControlBar::IsProbablyFloating()
//------------------------------------------------------------------
{ 
	// used to check the dock bar status, but this has problems when we 
	// docking/undocking - so check the actual bar style instread
	return (m_pDockBar == NULL || (GetBarStyle() & CBRS_FLOATING));
}	


//--------------------------------------------------------------------------
LONG CMRCSizeControlBar::OnAddContextMenuItems(WPARAM wParam, LPARAM lParam)
//--------------------------------------------------------------------------
{
	HMENU hMenu = (HMENU)lParam;		// handle of menu.
	CMenu Menu;
	Menu.Attach(hMenu);

	DWORD dwDockStyle = m_dwDockStyle & CBRS_ALIGN_ANY;
	DWORD style;
	CString strMenu;

	BOOL bMDIFloating = FALSE;
	CFrameWnd *pParentFrame = GetParentFrame();
	if (IsFloating())
	{
		if (pParentFrame != NULL && pParentFrame->IsKindOf(RUNTIME_CLASS(CMRCMDIFloatWnd)))
		{
			bMDIFloating = TRUE;
		}
	}
	style = (bMDIFloating ? MF_STRING | MF_CHECKED : MF_STRING);
	
	// if allowed - add the float as MDI floating window
	if (m_Style & SZBARF_ALLOW_MDI_FLOAT)
	{	
		VERIFY(strMenu.LoadString(ID_MRC_MDIFLOAT));
		Menu.AppendMenu(style, ID_MRC_MDIFLOAT, strMenu);
	}
	
	if (!bMDIFloating && (dwDockStyle != 0 || m_dwAllowDockingState != 0))	// ie docking is actually allowed ...
	{
		DWORD style = (dwDockStyle != 0 ? MF_STRING | MF_CHECKED : MF_STRING);
		VERIFY(strMenu.LoadString(ID_MRC_ALLOWDOCKING));
		Menu.AppendMenu(style, ID_MRC_ALLOWDOCKING, strMenu);
	}
	VERIFY(strMenu.LoadString(ID_MRC_HIDE));
	Menu.AppendMenu(MF_STRING, ID_MRC_HIDE, strMenu);

	Menu.Detach();	// detatch MFC object
	return TRUE;
}


//------------------------------------------------------------------
void CMRCSizeControlBar::OnHide()
//------------------------------------------------------------------
{
	CFrameWnd * pFrameWnd = GetParentFrame();
	pFrameWnd->ShowControlBar(this, FALSE, FALSE);
}


//------------------------------------------------------------------
void CMRCSizeControlBar::OnToggleAllowDocking()
//------------------------------------------------------------------
{
	CFrameWnd *pParentFrame = GetParentFrame();
	if ((m_dwDockStyle & CBRS_ALIGN_ANY) != 0)
	{											   // docking currently allowed - disable it
		m_dwAllowDockingState = m_dwDockStyle & CBRS_ALIGN_ANY;	// save previous state
		if (!IsFloating())
		{	
			ASSERT(m_pDockContext != NULL);
			m_pDockContext->ToggleDocking();
		}
		EnableDocking(0);				// disable docking
	}
	else
	{
		EnableDocking (m_dwAllowDockingState);	// re-enable docking...
	}
}

//------------------------------------------------------------------
void CMRCSizeControlBar::OnFloatAsMDI()
//------------------------------------------------------------------
{
	ASSERT(m_Style & SZBARF_ALLOW_MDI_FLOAT);		// must have specified this

	CMRCMDIFrameWndSizeDock * pFrame = (CMRCMDIFrameWndSizeDock *) AfxGetMainWnd();
	ASSERT(pFrame != NULL);
	ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CMRCMDIFrameWndSizeDock)));

	CFrameWnd *pParentFrame = GetParentFrame();
	BOOL bMDIFloating = (IsFloating() && pParentFrame != NULL && pParentFrame->IsKindOf(RUNTIME_CLASS(CMRCMDIFloatWnd)));
	
	ASSERT(m_pDockContext != NULL);
	
	if (bMDIFloating)
	{
		pFrame->UnFloatInMDIChild(this, m_pDockContext->m_ptMRUFloatPos);
	}
	else
	{
		pFrame->FloatControlBarInMDIChild(this, m_pDockContext->m_ptMRUFloatPos);
	}		
}

 
//----------------------------------------------------------------------------------
void CMRCSizeControlBar::OnContextMenu(CWnd* pWnd, CPoint point) 
// Now run off WM_CONTEXTMENU: if user wants standard handling, then let him have it
//----------------------------------------------------------------------------------
{
	if (m_Style & SZBARF_STDMOUSECLICKS)
	{
		CMenu menu;
		if (menu.CreatePopupMenu())
		{
			OnAddContextMenuItems(0, (LPARAM)menu.m_hMenu);
			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

		}
	} 
	else
		CControlBar::OnContextMenu(pWnd, point);
}


//----------------------------------------------------------------------------------
void CMRCSizeControlBar::OnSetFocus( CWnd* pOldWnd )
// if the control bar gains focus - bring to top of Z-order...
//----------------------------------------------------------------------------------
{
	if (IsFloating())
	{
		CFrameWnd * pFrame = GetParentFrame();
		if (pFrame != NULL)
		{
			pFrame->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}
	}
	
	CControlBar::OnSetFocus(pOldWnd);
}



//--------------------------------------------------------------------------
LONG CMRCSizeControlBar::OnSetMessageString(WPARAM wParam, LPARAM lParam)
// route any WM_SETMESSAGESTRING request thru to the owner of this control bar
// Prime reason for this is for flyby tooltip text for controlbars embedded
// on control bars. The embedded CControlBar sends the message to it's owner,
// which is a control bar and doesn't have code to update the status bar.
//--------------------------------------------------------------------------
{
	CWnd * pOwner = GetOwner();
	if (pOwner != NULL)
		return pOwner->SendMessage(WM_SETMESSAGESTRING, wParam, lParam);
	else
		return FALSE;
}