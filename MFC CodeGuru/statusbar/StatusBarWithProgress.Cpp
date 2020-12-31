//---------------------------------------------------------------------------
// Copyright (C) 1997, Interscope Ltd. All rights reserved.
// This software is protected by copyright law. Unauthorised reproduction
// or distribution of this program, or any portion of it, may result in
// severe civil or criminal penalties. For more information, contact:
//
// Interscope Ltd., 5 Culturii St., 5th floor, 4800 Baia Mare, Romania
//    Phone/Fax: +40(62)415023
//    E-mail: office@interscope.ro
//
//   $Author: Levente Farkas $
//     $Date: 11/07/97 11:53p $
//  $Modtime: 11/07/97 11:53p $
// $Revision: 2 $
//  $Archive: /Interscope/Thebe/SetupWizard/StatusBarWithProgress.Cpp $
// $Workfile: StatusBarWithProgress.Cpp $
//---------------------------------------------------------------------------

#include "StdAfx.H"

#include "StatusBarWithProgress.Hpp"


//--- Debugee ---------------------------------------------------------------

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//--- Miscellaneous ---------------------------------------------------------

#define ID_STATUS_PROGRESS  17234


//--- Message map 4 classs CStatusBarWithProgress ---------------------------

IMPLEMENT_DYNCREATE(CStatusBarWithProgress,CStatusBar)

BEGIN_MESSAGE_MAP(CStatusBarWithProgress,CStatusBar)
	//{{AFX_MSG_MAP(CStatusBarWithProgress)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------------------
// Pre     : 
// Post    : 
// Globals : 
// I/O     : 
// Task    : Construct a status bar with a progress control
//---------------------------------------------------------------------------
CStatusBarWithProgress::CStatusBarWithProgress(int nProgressBarWidth):
                        m_nProgressWidth(nProgressBarWidth),
                        m_bProgressVisible(FALSE)
{
}

//---------------------------------------------------------------------------
// Pre     : 
// Post    : 
// Globals : 
// I/O     : 
// Task    : When creating the status bar, also create the progress control,
//           but do not show it yet
//---------------------------------------------------------------------------
BOOL CStatusBarWithProgress::Create(CWnd *pParentWnd, DWORD dwStyle, UINT nID)
{
    // Default creation
    BOOL bCreatedOK =CStatusBar::Create(pParentWnd,dwStyle,nID);
    if(bCreatedOK)
    {
        // Also create the progress bar
        m_Progress.Create(WS_CHILD | WS_EX_STATICEDGE | PBS_SMOOTH,CRect(0,0,m_nProgressWidth,10),this,ID_STATUS_PROGRESS);
    }

    return bCreatedOK;
}

//---------------------------------------------------------------------------
// Pre     : 
// Post    : Return old visible status
// Globals : 
// I/O     : 
// Task    : Show/hide the progress bar
//---------------------------------------------------------------------------
BOOL CStatusBarWithProgress::ShowProgressBar(BOOL bShow)
{
    // Save old visible status
    BOOL bOldVisible =m_bProgressVisible;

    if((bOldVisible != bShow) && ::IsWindow(m_Progress.m_hWnd))
    {
        // Show/hide
        m_Progress.ShowWindow(bShow ? SW_SHOWNA : SW_HIDE);
        m_bProgressVisible =bShow;

        // If just shown, make sure it's in the right position
        if(bShow)
        {
            AdjustProgressBarPosition();
            RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW);
        }
    }

    return bOldVisible;
}

//---------------------------------------------------------------------------
// Pre     : 
// Post    : 
// Globals : 
// I/O     : 
// Task    : Adjust the progress bar's position, so that it comes after the text 
//           in the first pane
//---------------------------------------------------------------------------
void CStatusBarWithProgress::AdjustProgressBarPosition()
{
    // Make sure the progress bar is created
    if(!::IsWindow(m_Progress.m_hWnd))
        return;

    // Find out the size of the text in first pane
    CString str_pane_text;
    CRect   progress_rect;
    GetItemRect(0,progress_rect);
    GetPaneText(0,str_pane_text);
    
    // Measure the size of the text in the first pane
    CClientDC temp(this);
    CFont *pOldFont =temp.SelectObject(GetFont());

    progress_rect.left  =temp.GetTextExtent(str_pane_text).cx + 10;
    progress_rect.right =progress_rect.left + m_nProgressWidth;
    progress_rect.InflateRect(0,-1);

    temp.SelectObject(pOldFont);

    // Now adjust the size of the progrss control
    m_Progress.SetWindowPos(NULL,progress_rect.left,
                                 progress_rect.top,
                                 progress_rect.Width(),
                                 progress_rect.Height(),SWP_NOZORDER | SWP_NOACTIVATE);
}

//---------------------------------------------------------------------------
// Pre     : 
// Post    : 
// Globals : 
// I/O     : 
// Task    : After each sizing, if the progress bar is visible, adjust 
//           its position
//---------------------------------------------------------------------------
void CStatusBarWithProgress::OnSize(UINT nType, int cx, int cy) 
{
    // Default sizing
	CStatusBar::OnSize(nType, cx, cy);
	
    if(m_bProgressVisible)
        AdjustProgressBarPosition();
}
