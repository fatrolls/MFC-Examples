// EditCell.cpp : implementation file
//

#include "stdafx.h"

#ifndef QUICKLIST_NOEDIT

#include "QuickEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuickEdit

CQuickEdit::CQuickEdit (CQuickList* pCtrl, int iItem, int iSubItem, CString sInitText, bool endonlostfocus)
{
    pListCtrl = pCtrl;
    Item = iItem;
    SubItem = iSubItem;
    InitText = sInitText;

	m_isClosing = false;
	m_endOnLostFocus = endonlostfocus;
}

CQuickEdit::~CQuickEdit()
{
}

BEGIN_MESSAGE_MAP(CQuickEdit, CEdit)
    //{{AFX_MSG_MAP(CQuickEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    ON_WM_CREATE()
    ON_WM_GETDLGCODE()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuickEdit message handlers

void CQuickEdit::SetEndOnLostFocus(bool autoend)
{
	m_endOnLostFocus = autoend;
}

BOOL CQuickEdit::PreTranslateMessage (MSG* pMsg) 
{
    if (pMsg->message == WM_KEYDOWN)
    {
	    if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE || 
			pMsg->wParam == VK_ESCAPE)// || pMsg->wParam == VK_TAB || 
			//pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN || GetKeyState (VK_CONTROL))
			{
				::TranslateMessage (pMsg);
				::DispatchMessage (pMsg);
				return TRUE;		    	// DO NOT process further
			}
    }

    return CEdit::PreTranslateMessage (pMsg);
}

void CQuickEdit::OnKillFocus (CWnd* pNewWnd) 
{
    CEdit::OnKillFocus(pNewWnd);

	//End edit?
	if(!m_isClosing)
	{
		if(m_endOnLostFocus)
		{
			StopEdit(false);
		}
		else
		{
			//Notify list parent
			pListCtrl->GetParent()->SendMessage(	WM_QUICKLIST_EDITINGLOSTFOCUS,
													(WPARAM) pListCtrl->GetSafeHwnd(),
													0);
		}
	}
}

void CQuickEdit::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    BOOL Shift = GetKeyState (VK_SHIFT) < 0;
    switch (nChar)
    {
		case VK_ESCAPE :
		{	
			//GetParent()->SetFocus();
			StopEdit(TRUE, VK_ESCAPE);
			return;
		}
		case VK_RETURN :
		{
			StopEdit(FALSE, VK_RETURN);
			//bEscape = FALSE;
			//SetListText();
//			GetParent()->SetFocus();
			//pListCtrl->EditSubItem (Item + 1, 0);
			return;
		}
    }

    CEdit::OnChar (nChar, nRepCnt, nFlags);
 
}

int CQuickEdit::OnCreate (LPCREATESTRUCT lpCreateStruct) 
{
    if (CEdit::OnCreate (lpCreateStruct) == -1)
		return -1;

    // Set the proper font
    CFont* Font = GetParent()->GetFont();
    SetFont (Font);

    SetWindowText (InitText);
    SetFocus();
    SetSel (0, -1);
    return 0;
}

UINT CQuickEdit::OnGetDlgCode() 
{
    return CEdit::OnGetDlgCode() | DLGC_WANTARROWS;// | DLGC_WANTTAB;
}

#endif

//Stop editing
void CQuickEdit::StopEdit(bool cancel, UINT endkey)
{
	m_isClosing = true;
//	SetListText();

	//Don't call SetListText to set the text. The reason is that
	//the object may be destoyed before DestroyWindow() in this function
	//is called.

	CString Text;
	GetWindowText (Text);

#ifndef QUICKLIST_NOEDIT
	if(pListCtrl != NULL)
		pListCtrl->m_edit = NULL;
#endif
	DestroyWindow();

#ifndef QUICKLIST_NOEDIT
	pListCtrl->OnEndEdit(Item, SubItem, Text, cancel, endkey);
#endif

	delete this;
}
