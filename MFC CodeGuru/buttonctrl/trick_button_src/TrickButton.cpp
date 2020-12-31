// TrickButton.cpp : implementation file
//
// TrickButton is a drop-in pushbutton control that cannot
// be pressed. As soon as the user moves the mouse over the 
// the button will scurry away out of reach. Check out the 
// header file or the accompanying HTML doc file for details.
//
// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to your
// computer, causes your pet cat to fall ill, increases baldness or
// makes you car start emitting strange noises when you start it up.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 

#include "stdafx.h"
#include "TrickButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrickButton

CTrickButton::CTrickButton()
{
    m_nJumpDistance = 10;
}

CTrickButton::~CTrickButton()
{
}


BEGIN_MESSAGE_MAP(CTrickButton, CButton)
	//{{AFX_MSG_MAP(CTrickButton)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrickButton message handlers

void CTrickButton::OnMouseMove(UINT nFlags, CPoint point) 
{
    CWnd* pParent = GetParent();
    if (!pParent) pParent = GetDesktopWindow();

    CRect ParentRect;                                   // Parent client area (Parent coords)
    pParent->GetClientRect(ParentRect);

    ClientToScreen(&point);                             // Convert point to parent coords
    pParent->ScreenToClient(&point);

    CRect ButtonRect;                                   // Button Dimensions (Parent coords)
    GetWindowRect(ButtonRect);  
    pParent->ScreenToClient(ButtonRect);
    CPoint Center = ButtonRect.CenterPoint();           // Center of button (parent coords)

    CSize CriticalSize(ButtonRect.Width()/6, ButtonRect.Height()/6);


    CRect NewButtonRect = ButtonRect;                    // New position (parent coords)

    if (point.x - CriticalSize.cx > Center.x)            // Mouse is right of center
    {
        if (ButtonRect.left > ParentRect.left + ButtonRect.Width() + m_nJumpDistance)
            NewButtonRect -= CSize(ButtonRect.right - point.x + m_nJumpDistance, 0);
        else
            NewButtonRect += CSize(point.x - ButtonRect.left + m_nJumpDistance, 0);
    }
    else if (point.x + CriticalSize.cx < Center.x)      // Mouse is left of center
    {
        if (ButtonRect.right < ParentRect.right - ButtonRect.Width() - m_nJumpDistance)
            NewButtonRect += CSize(point.x - ButtonRect.left + m_nJumpDistance, 0);
        else
            NewButtonRect -= CSize(ButtonRect.right - point.x + m_nJumpDistance, 0);
    }

    if (point.y - CriticalSize.cy > Center.y)           // Mouse is below center
    {
        if (ButtonRect.top > ParentRect.top + ButtonRect.Height() + m_nJumpDistance)
            NewButtonRect -= CSize(0, ButtonRect.bottom - point.y + m_nJumpDistance);
        else
            NewButtonRect += CSize(0, point.y - ButtonRect.top + m_nJumpDistance);
    }
    else if (point.y + CriticalSize.cy < Center.y)      // Mouse is above center
    {
        if (ButtonRect.bottom < ParentRect.bottom - ButtonRect.Height() - m_nJumpDistance)
            NewButtonRect += CSize(0, point.y - ButtonRect.top + m_nJumpDistance);
        else
            NewButtonRect -= CSize(0, ButtonRect.bottom - point.y + m_nJumpDistance);
    }

    MoveWindow(NewButtonRect);
    RedrawWindow();
    
	CButton::OnMouseMove(nFlags, point);
}
