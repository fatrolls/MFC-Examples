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
// mrcanima.cpp : implementation file
//
// $Date:   04 Feb 1997 10:41:00  $
// $Revision:   1.0  $
// $Author:   MRC  $
    


#include "mrcstafx.h"
#include <mmsystem.h>		
#include <digitalv.h>		
#include "mrcext.h"

#ifdef LINK_TO_WINMM
// link to the DLL
#pragma comment(lib, "winmm.lib")

#else 	// load the DLL dynamically

typedef MCIERROR (APIENTRY * pftmciSendCommand) (MCIDEVICEID mciId, UINT uMsg, DWORD dwP1, DWORD dwP2);
static pftmciSendCommand pfmciSendCommand;
typedef BOOL (APIENTRY * pftPlaySound)(LPCTSTR lpszName, HANDLE hModule, DWORD fdwSound);	
static pftPlaySound pfPlaySound;
typedef BOOL (APIENTRY * pftsndPlaySound)(LPCTSTR lpszName, UINT options);
static pftsndPlaySound pfsndPlaySound;

static HINSTANCE hinstWinMM;
#undef mciSendCommand
#define mciSendCommand pfmciSendCommand
#undef sndPlaySound
#define sndPlaySound pfsndPlaySound
#undef PlaySound
#define PlaySound pfPlaySound
#endif

BOOL CMRCAnimateCtrl::m_bInitialized = FALSE;

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


//--------------------------------------------------------------------------------
void CenterWindowWithinParent(CWnd * pWnd, CWnd * pAlternate)
//--------------------------------------------------------------------------------
{
	CWnd * pOwner = pWnd->GetParent();		// owner rectangle - needed for positioning
	CWnd * pCenterWnd;
	if (pAlternate != NULL)
		pCenterWnd = pAlternate;
	else
		pCenterWnd = pOwner;

	CRect Rect, ParRect;
	pWnd->GetWindowRect(&Rect);
	pCenterWnd->GetWindowRect(&ParRect);
	Rect.left = (ParRect.right + ParRect.left - Rect.Width()) / 2; 
	Rect.top  = (ParRect.bottom + ParRect.top - Rect.Height()) / 2; 
	pOwner->ScreenToClient(&(Rect.TopLeft()));
	
	pWnd->SetWindowPos(NULL, Rect.left, Rect.top, 0, 0,
					SWP_NOZORDER | SWP_NOSIZE);
}


#define AVI_VIDEO "avivideo"
#define REPEAT_TIMER_ID	1099
/////////////////////////////////////////////////////////////////////////////
// CMRCAnimateCtrl

//--------------------------------------------------------------------------------
CMRCAnimateCtrl::CMRCAnimateCtrl()
//--------------------------------------------------------------------------------
{
	m_bFileOpen = FALSE;
	m_nFrom = 0;
	m_nTo = -1;
	m_nRepeatDelay = 0;
	m_dwPlayFlags = 0;
}


CMRCAnimateCtrl::~CMRCAnimateCtrl()
{
	Close();
}


BEGIN_MESSAGE_MAP(CMRCAnimateCtrl, CWnd)
	//{{AFX_MSG_MAP(CMRCAnimateCtrl)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(MM_MCINOTIFY, OnMCINotify)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMRCAnimateCtrl message handlers



//---------------------------------------------------------------------------
BOOL CMRCAnimateCtrl::Init() 
//---------------------------------------------------------------------------
{
	if (m_bInitialized)
		return TRUE;

	m_bInitialized = TRUE;
#ifndef LINK_TO_WINMM
	hinstWinMM = LoadLibrary("winmm.dll");
	if (hinstWinMM == NULL)
		return FALSE;
	pfmciSendCommand = (pftmciSendCommand) GetProcAddress(hinstWinMM, "mciSendCommandA");	
	if (pfmciSendCommand == NULL)
		return FALSE;	
	if (!(pfPlaySound = (pftPlaySound) GetProcAddress(hinstWinMM, "PlaySoundA")))	
		return FALSE;
	if (!(pfsndPlaySound = (pftsndPlaySound) GetProcAddress(hinstWinMM, "sndPlaySoundA")))	
		return FALSE;


#endif
	return TRUE;
}


//---------------------------------------------------------------------------
BOOL CMRCAnimateCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
//---------------------------------------------------------------------------
{
	// if first create, attempt to load the DLL. If this fails then video is
	// not available
	if (Init() == FALSE)
		return FALSE;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


//---------------------------------------------------------------------------
BOOL CMRCAnimateCtrl::Open(LPCTSTR pFilename) 			// open an AVI file
//---------------------------------------------------------------------------
{
	MCI_DGV_OPEN_PARMS	mciOpen;
	MCI_DGV_WINDOW_PARMS	mciWindow;
	// MCI_DGV_STATUS_PARMS	mciStatus;

	// we have a .AVI movie to open, use MCI 
	// set up the open parameters 
	mciOpen.dwCallback = 0L;
	mciOpen.wDeviceID = 0;
	mciOpen.lpstrDeviceType = NULL;
	mciOpen.lpstrElementName = (char *)pFilename;
	mciOpen.lpstrAlias = NULL;
	mciOpen.dwStyle = WS_CHILD;
	mciOpen.hWndParent = m_hWnd;

	// try to open the file - creates a suitable child window
	if (mciSendCommand(0, MCI_OPEN, (DWORD)MCI_OPEN_ELEMENT, (DWORD)&mciOpen) != 0)
		return FALSE;
	
	m_MCIDeviceID = mciOpen.wDeviceID;	/* save ID */
	mciWindow.hWnd = m_hWnd;
	m_strFilename = pFilename;
	if (mciSendCommand(m_MCIDeviceID, MCI_WINDOW, MCI_DGV_WINDOW_HWND, (DWORD) &mciWindow) != 0)
	{
		Close();
	 	return FALSE;
	}
	m_bFileOpen = TRUE;
	CRect rect;
	GetMovieRect(&rect); 
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
				 SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;
}


//---------------------------------------------------------------------------
BOOL CMRCAnimateCtrl::Close()
//---------------------------------------------------------------------------
{
	if (m_bFileOpen == FALSE)
		return FALSE;

	// unshow the window
	MCI_DGV_WINDOW_PARMS mciWindow;
	mciWindow.nCmdShow = SW_HIDE;
	mciSendCommand(m_MCIDeviceID, MCI_WINDOW, (DWORD)MCI_DGV_WINDOW_STATE, (DWORD)&mciWindow);

	
	m_bFileOpen = FALSE;
	MCI_GENERIC_PARMS  mciGeneric;

	mciSendCommand(m_MCIDeviceID, MCI_CLOSE, 0L, (DWORD)&mciGeneric);

	
	// cause a total repaint to occur 
	InvalidateRect(NULL, TRUE);
	UpdateWindow();
	return TRUE;
}


//---------------------------------------------------------------------------
BOOL CMRCAnimateCtrl::Play(DWORD dwFlags, int nFrom, int nTo, int nRepeatDelay)
//---------------------------------------------------------------------------
{ 
	MCI_DGV_PLAY_PARMS	mciPlay;
		
	m_dwPlayFlags = dwFlags;
	m_nFrom = nFrom;
	m_nTo = nTo;
	m_nRepeatDelay = nRepeatDelay;

	// init to play all 
	mciPlay.dwCallback = (DWORD)m_hWnd;
	mciPlay.dwFrom = mciPlay.dwTo = 0;
	dwFlags = 0;
	//if (m_nDirection == IDM_RPLAY)
	//	dwFlags |= MCI_DGV_PLAY_REVERSE;
	
	if (m_nFrom >= 0)
	{
		mciPlay.dwFrom = m_nFrom;
		dwFlags |= MCI_FROM;
	}
	
	if (m_nTo >= 0)
	{
		mciPlay.dwTo = m_nTo;
		dwFlags |= MCI_TO;
	}
	
	if (m_dwPlayFlags & ACF_REPEAT)
		if (m_nRepeatDelay == 0)
			dwFlags |= MCI_DGV_PLAY_REPEAT;
		else
			dwFlags |= MCI_NOTIFY;
	
	if (mciSendCommand(m_MCIDeviceID, MCI_PLAY, dwFlags, (DWORD)&mciPlay) != 0)
		return FALSE;

	return TRUE;
}


//---------------------------------------------------------------------------
BOOL CMRCAnimateCtrl::Pause()
//---------------------------------------------------------------------------
{
	MCI_DGV_PAUSE_PARMS	mciPause;
	
	// tell it to pause 
	mciSendCommand(m_MCIDeviceID,MCI_PAUSE,0L,
                     (DWORD)(LPMCI_DGV_PAUSE_PARMS)&mciPause);

	return TRUE;
}



//---------------------------------------------------------------------------
BOOL CMRCAnimateCtrl::InitAVI()
//---------------------------------------------------------------------------
{
	MCI_DGV_OPEN_PARMS	mciOpen;
		
	/* set up the open parameters */
	mciOpen.dwCallback 		= 0L;
	mciOpen.wDeviceID 		= 0;
	mciOpen.lpstrDeviceType 	= AVI_VIDEO;
	mciOpen.lpstrElementName 	= NULL;
	mciOpen.lpstrAlias 		= NULL;
	mciOpen.dwStyle 		= 0;
	mciOpen.hWndParent 		= NULL;
		
	/* try to open the driver */
	return (mciSendCommand(0, MCI_OPEN, (DWORD)(MCI_OPEN_TYPE),
                          (DWORD)(LPMCI_DGV_OPEN_PARMS)&mciOpen) == 0);
}


//---------------------------------------------------------------------------
void CMRCAnimateCtrl::Rewind()
//---------------------------------------------------------------------------
{
	MCI_SEEK_PARMS mciSeek;
	mciSeek.dwCallback = (DWORD)m_hWnd;
	mciSeek.dwTo = 0;

	if(mciSendCommand(m_MCIDeviceID, MCI_SEEK, MCI_NOTIFY | MCI_SEEK_TO_START,
			(DWORD)&mciSeek))
		TRACE("CMRCAnimateCtrl:Error executing SEEK\n");

	TRACE("CMRCAnimateCtrl:MCI Sent Rewind\n");
}


//---------------------------------------------------------------------------
void CMRCAnimateCtrl::GetMovieRect(RECT * pRect)
// returns rectangle containing size of th
//---------------------------------------------------------------------------
{
	MCI_DGV_RECT_PARMS	mciRect;

	// get the original size of the movie 
	mciSendCommand(m_MCIDeviceID, MCI_WHERE,
                  (DWORD)(MCI_DGV_WHERE_SOURCE),
                  (DWORD)&mciRect);
	
	CopyRect(pRect, &mciRect.rc );	// get it in the movie bounds rect 

}




//---------------------------------------------------------------------------
afx_msg LONG CMRCAnimateCtrl::OnMCINotify(WPARAM wParam, LPARAM lParam)
//---------------------------------------------------------------------------
{

	switch (wParam)
	{
	case MCI_NOTIFY_SUCCESSFUL:
		SetTimer(REPEAT_TIMER_ID, m_nRepeatDelay, NULL);
		break;
	
	case MCI_NOTIFY_ABORTED:
		break;
	case MCI_NOTIFY_SUPERSEDED:
		break;
	case MCI_NOTIFY_FAILURE:
		break;
	default:
		break;
	}

	return 0;	
}


//--------------------------------------------------------------------------
void CMRCAnimateCtrl::OnTimer(UINT nIDEvent) 
// Timer event to kick start replaying the video again
//--------------------------------------------------------------------------
{
	ASSERT(nIDEvent == REPEAT_TIMER_ID);
	KillTimer(nIDEvent);
	Rewind();
	Play(m_dwPlayFlags, m_nFrom, m_nTo, m_nRepeatDelay);   

	CWnd::OnTimer(nIDEvent);
}


//--------------------------------------------------------------------------
void CMRCAnimateCtrl::PostNcDestroy()
// auto-delete
//--------------------------------------------------------------------------
{
	delete this;

}


//--------------------------------------------------------------------------
void CMRCAnimateCtrl::OnDestroy()
// auto-delete
//--------------------------------------------------------------------------
{
	Close();
}


