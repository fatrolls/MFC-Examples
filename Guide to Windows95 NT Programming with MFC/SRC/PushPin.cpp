/*
Module : PUSHPIN.H
Purpose: Implementation of a push pin button 
         (as seen on X-Windows & property dialogs in VC 4)
Created: PJN / DATE/1 / 04-04-1996
History: None

Copyright (c) 1996 by PJ Naughter.  
All rights reserved.
*/


/////////////////////////////////  Includes  //////////////////////////////////
#include "stdafx.h"
#include "win32sup.h"
#include "PushPin.h"




//////////////////////////////////  Macros  ///////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


#ifndef _WINDOWS
#pragma message("This module should be included in builds for Windows only")
#endif


////////////////////////////////// Implementation /////////////////////////////
BEGIN_MESSAGE_MAP(CPushPinButton, CBitmapButton)
  //{{AFX_MSG_MAP(CPushPinButton)
  #ifdef _WIN32
    ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
  #endif
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPushPinButton::CPushPinButton()
{
  m_bPinned = FALSE;
}


CPushPinButton::~CPushPinButton()
{
}


void CPushPinButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
  ASSERT(lpDIS != NULL);
  
  // must have up and down bitmaps loaded before calling DrawItem
  ASSERT(m_bitmap.m_hObject != NULL);     // required
  ASSERT(m_bitmapSel.m_hObject != NULL);  // required

  //select the bitmap
  CBitmap* pBitmap;
  if (m_bPinned)
    pBitmap = &m_bitmapSel;
  else
    pBitmap = &m_bitmap;
  
  // draw the whole button
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CDC memDC;
  memDC.CreateCompatibleDC(pDC);
  CBitmap* pOld = memDC.SelectObject(pBitmap);
  if (pOld == NULL)
    return;     // destructors will clean up

  CRect rect;
  rect.CopyRect(&lpDIS->rcItem);
  pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
    &memDC, 0, 0, SRCCOPY);
  memDC.SelectObject(pOld);
}


void CPushPinButton::OnClicked() 
{
  m_bPinned = !m_bPinned;  //toggle the pin option
  Invalidate();            //force a redraw
}


