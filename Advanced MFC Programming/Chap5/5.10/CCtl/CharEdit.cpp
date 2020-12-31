#include "stdafx.h"
#include "CCtl.h"
#include "CharEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MCCharEdit::MCCharEdit()
{
}

MCCharEdit::~MCCharEdit()
{
}


BEGIN_MESSAGE_MAP(MCCharEdit, CEdit)
	//{{AFX_MSG_MAP(MCCharEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MCCharEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if
	(
		(nChar >= 'A' && nChar <= 'Z') || 
		(nChar == VK_BACK) ||
		(nChar  >= 'a' && nChar <= 'z')
	)CEdit::OnChar(nChar, nRepCnt, nFlags);
    else MessageBeep( MB_ICONEXCLAMATION );	
}
