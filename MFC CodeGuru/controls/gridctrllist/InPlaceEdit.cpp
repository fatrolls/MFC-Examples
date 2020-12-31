// InPlaceEdit.cpp : implementation file
//
// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
// Copyright (c) 1998.
//
// The code contained in this file is based on the original
// CInPlaceEdit from http://www.codeguru.com/listview/edit_subitems.shtml
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Expect bugs!
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCHAR.h"
#include "InPlaceEdit.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit

CInPlaceEdit::CInPlaceEdit(CWnd* pParent, CRect& rect, DWORD dwStyle,
                           int nRow, int nColumn, CString sInitText, 
                           UINT nFirstChar)
{
    m_sInitText     = sInitText;
    m_nRow          = nRow;
    m_nColumn       = nColumn;
    m_nLastChar     = 0; 
    m_bExitOnArrows = (nFirstChar != VK_LBUTTON);    // If mouse click brought us here,
                                                     // then no exit on arrows

    DWORD dwEditStyle = WS_BORDER|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_MULTILINE | dwStyle;
    if (!Create(dwEditStyle, rect, pParent, IDC_IPEDIT)) return;

    SetFont(pParent->GetFont());

    SetWindowText(sInitText);
    SetFocus();

    switch (nFirstChar){
        case VK_LBUTTON: 
        case VK_RETURN:   SetSel((int)_tcslen(m_sInitText), -1); return;
        case VK_BACK:     SetSel((int)_tcslen(m_sInitText), -1); break;
        case VK_DOWN: 
        case VK_UP:   
        case VK_RIGHT:
        case VK_LEFT:  
        case VK_NEXT:  
        case VK_PRIOR: 
        case VK_HOME:  
        case VK_END:      SetSel(0,-1); return;
        default:          SetSel(0,-1);
    }

    SendMessage(WM_CHAR, nFirstChar);
}

CInPlaceEdit::~CInPlaceEdit()
{
}
 
BEGIN_MESSAGE_MAP(CInPlaceEdit, CEdit)
    //{{AFX_MSG_MAP(CInPlaceEdit)
    ON_WM_KILLFOCUS()
    ON_WM_NCDESTROY()
    ON_WM_CHAR()
    ON_WM_KEYDOWN()
    ON_WM_CREATE()
    ON_WM_KEYUP()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
 
////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit message handlers

// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CInPlaceEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if ((nChar == VK_PRIOR || nChar == VK_NEXT ||
         nChar == VK_DOWN  || nChar == VK_UP   ||
         nChar == VK_RIGHT || nChar == VK_LEFT) &&
        (m_bExitOnArrows || GetKeyState(VK_CONTROL) < 0))
    {
        m_nLastChar = nChar;
        GetParent()->SetFocus();
        return;
    }

    if (nChar == VK_ESCAPE) 
    {
        SetWindowText(m_sInitText);    // restore previous text
        m_nLastChar = nChar;
        GetParent()->SetFocus();
        return;
    }

    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Need to keep a lookout for Tabs, Esc and Returns. These send a 
// "KeyUp" message, but no "KeyDown". That's why I didn't put their
// code in OnKeyDown. (I will never understand windows...)
void CInPlaceEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
    {
        m_nLastChar = nChar;
        GetParent()->SetFocus();    // This will destroy this window
        return;
    }

    CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

// As soon as this edit loses focus, kill it.
void CInPlaceEdit::OnKillFocus(CWnd* pNewWnd)
{
    CEdit::OnKillFocus(pNewWnd);
    EndEdit();
}

void CInPlaceEdit::EndEdit()
{
    CString str;
    GetWindowText(str);
 
    // Send Notification to parent (this was originally designed for listviews,
    // so we use listview structures and messages)

    LV_DISPINFO dispinfo;

    dispinfo.hdr.hwndFrom = GetParent()->GetSafeHwnd();
    dispinfo.hdr.idFrom   = GetDlgCtrlID();
    dispinfo.hdr.code     = LVN_ENDLABELEDIT;
 
    dispinfo.item.mask       = LVIF_TEXT|LVIF_PARAM;
    dispinfo.item.iItem      = m_nRow;
    dispinfo.item.iSubItem   = m_nColumn;
    dispinfo.item.pszText    = LPTSTR((LPCTSTR)str);
    dispinfo.item.cchTextMax = str.GetLength();
    dispinfo.item.lParam     = (LPARAM) m_nLastChar; 
 
    // Send a message to the parent of this edit's parent, telling the parent's parent
    // that the parent of this edit ctrl has recieved a LVN_ENDLABELEDIT message. 
    // Makes perfect sense, no? :)
    GetParent()->GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), 
                                          (LPARAM)&dispinfo );
 
    DestroyWindow();
}
 
void CInPlaceEdit::OnNcDestroy()
{
    CEdit::OnNcDestroy();
    delete this;
}

void CInPlaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
     CEdit::OnChar(nChar, nRepCnt, nFlags);
 
     // Resize edit control if needed
 
     // Get text extent
     CString str;
     GetWindowText( str );

     CWindowDC dc(this);
     CFont *pFontDC = dc.SelectObject(GetFont());
     CSize size = dc.GetTextExtent( str );
     dc.SelectObject( pFontDC );

     size.cx += 5;                   // add some extra buffer
 
     // Get client rect
     CRect rect, parentrect;
     GetClientRect( &rect );
     GetParent()->GetClientRect( &parentrect );
 
     // Transform rect to parent coordinates
     ClientToScreen( &rect );
     GetParent()->ScreenToClient( &rect );
 
     // Check whether control needs to be resized
     // and whether there is space to grow
     if (size.cx > rect.Width())
     {
         if( size.cx + rect.left < parentrect.right )
             rect.right = rect.left + size.cx;
         else
             rect.right = parentrect.right;
         MoveWindow( &rect );
     }
}