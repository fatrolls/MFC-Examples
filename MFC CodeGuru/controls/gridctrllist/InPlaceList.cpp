// InPlaceList.cpp : implementation file
//
// Written by Motty Cohen Copyright (c) 1998.
// (based on Chris Maunder's InPlaceEdit class).
// 
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
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InPlaceList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInPlaceList

CInPlaceList::CInPlaceList(CWnd* pParent, CRect& rect, DWORD dwStyle, int nRow, int nColumn, 
						   CString sInitText, UINT nFirstChar)
{
	m_nNumLines = 5;
	m_sInitText = sInitText;
 	m_nRow		= nRow;
 	m_nCol      = nColumn;
 	m_nLastChar = 0; 
	m_bExitOnArrows = FALSE; //(nFirstChar != VK_LBUTTON);	// If mouse click brought us here,

	// Create the ListBox, not using dwStyle argument for now
 	DWORD dwStyle2 = WS_BORDER|WS_CHILD|WS_VISIBLE|WS_VSCROLL|
 					CBS_DROPDOWNLIST|CBS_AUTOHSCROLL;
	int nHeight = rect.Height();
	rect.bottom = rect.bottom + m_nNumLines*nHeight + ::GetSystemMetrics(SM_CYHSCROLL);
	if (!Create(dwStyle2, rect, pParent, IDC_IPLIST)) return;

	// Add the strings, Ask them from the parent
	pParent->SendMessage( IPLM_FILL, nColumn, (LPARAM)this );

	// Get the maximum width of the text strings
	/*
	int nMaxLength = 0;
	CClientDC dc(GetParent());
	CFont* pOldFont = dc.SelectObject(pParent->GetFont());

	for (int i = 0; i < Items.GetSize(); i++) 
		nMaxLength = max(nMaxLength, dc.GetTextExtent(Items[i]).cx);
	
	nMaxLength += (::GetSystemMetrics(SM_CXVSCROLL) + dc.GetTextExtent(_T(" ")).cx*2);
	dc.SelectObject(pOldFont);
	
	if (rect.right < rect.left + nMaxLength + 4)
		rect.right = rect.left + nMaxLength + 4;
	*/

	// Resize the edit window and the drop down window
	MoveWindow(rect);

	SetFont(pParent->GetFont());
	SetItemHeight(-1, nHeight);

	SetHorizontalExtent(0); // no horz scrolling

	// Set the initial text to m_sInitText
	if (SelectString(-1, m_sInitText) == CB_ERR) 
		SetWindowText(m_sInitText);		// No text selected, so restore what was there before

 	SetFocus();
}

CInPlaceList::~CInPlaceList()
{
}

BEGIN_MESSAGE_MAP(CInPlaceList, CListBox)
	//{{AFX_MSG_MAP(CInPlaceList)
	ON_WM_KILLFOCUS()
	ON_WM_NCDESTROY()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

	//ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup) // for ComboBox

/////////////////////////////////////////////////////////////////////////////
// CInPlaceList message handlers

void CInPlaceList::OnKillFocus(CWnd* pNewWnd) 
{
	CListBox::OnKillFocus(pNewWnd);
    EndSelect();
}

// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CInPlaceList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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

	CListBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Need to keep a lookout for Tabs, Esc and Returns. These send a 
// "KeyUp" message, but no "KeyDown". That's why I didn't put their
// code in OnKeyDown. (I will never understand windows...)
void CInPlaceList::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_ESCAPE)
	{
		SetWindowText(m_sInitText);	// restore previous text
		GetParent()->SetFocus();	// This will destroy this window
		return;
	}
	if (nChar == VK_TAB || nChar == VK_RETURN)
	{
		GetParent()->SetFocus();	// This will destroy this window
		return;
	}

	CListBox::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CInPlaceList::EndSelect()
{
    CString		csItemText;
	DWORD		dwUserData = 0;
	int			nItem = GetCurSel();

	if ( nItem != LB_ERR )
	{
		dwUserData = GetItemData(nItem);
		GetText( nItem, csItemText);
	}
	else
	{
		csItemText = m_sInitText;
	}

    // Send Notification to parent (this was originally designed for listviews,
    // so we use listview structures and messages)

    LV_DISPINFO dispinfo;

    dispinfo.hdr.hwndFrom = GetParent()->GetSafeHwnd();
    dispinfo.hdr.idFrom   = GetDlgCtrlID();
    dispinfo.hdr.code     = LVN_ENDLABELEDIT;
 
    dispinfo.item.mask       = LVIF_TEXT|LVIF_PARAM;
    dispinfo.item.iItem      = m_nRow;
    dispinfo.item.iSubItem   = m_nCol;
    dispinfo.item.pszText    = LPTSTR((LPCTSTR)csItemText);
    dispinfo.item.cchTextMax = csItemText.GetLength();
    dispinfo.item.lParam     = (LPARAM)dwUserData; 
 
    // Send a message to the parent of this edit's parent, telling the parent's parent
    // that the parent of this edit ctrl has recieved a LVN_ENDLABELEDIT message. 
    // Makes perfect sense, no? :)
    GetParent()->GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), 
                                          (LPARAM)&dispinfo );
 
    DestroyWindow();
}
void CInPlaceList::OnNcDestroy() 
{
	CListBox::OnNcDestroy();
	delete this;
}

void CInPlaceList::OnLButtonUp( UINT nFlag, CPoint pt )
{
	CListBox::OnLButtonUp( nFlag, pt );
	EndSelect();
}

void CInPlaceList::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CListBox::OnChar(nChar, nRepCnt, nFlags);

	// this event is for the next version to implement
	// Search-As-You-Type functionality.

}

/*
void CInPlaceList::OnCloseup() 
{
	//if (!::IsWindow(GetSafeHwnd())) return;
	//GetParent()->SetFocus();
}
*/