// ROEdit.cpp  Version 1.0
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// History
//     Version 1.0 - 2007 July 15
//     - Initial public release
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this 
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "search.h"
#include "ROEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CROEdit

BEGIN_MESSAGE_MAP(CROEdit, CEdit)
	//{{AFX_MSG_MAP(CROEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CROEdit::CROEdit()
{
}

/////////////////////////////////////////////////////////////////////////////
// CROEdit message handlers


void CROEdit::OnChange() 
{
}

void CROEdit::OnUpdate() 
{
}

// throw away all keystrokes that could cause a change
BOOL CROEdit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 0x43)	// C
		{
			// let Ctrl-C go thru
			BOOL bCtrlDown = GetAsyncKeyState(VK_CONTROL) >> ((sizeof(SHORT) * 8) - 1);
			if (!bCtrlDown)
				return TRUE;
		}
		else if (pMsg->wParam == VK_BACK ||
			pMsg->wParam == VK_DELETE ||
			pMsg->wParam == 0x20 ||
			((pMsg->wParam >= 0x30) && (pMsg->wParam < VK_F1)))
		{
			return TRUE;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}

// disable right-click menu
void CROEdit::OnRButtonUp(UINT /*nFlags*/, CPoint /*point*/) 
{
	//CDialog::OnRButtonUp(nFlags, point);
}
