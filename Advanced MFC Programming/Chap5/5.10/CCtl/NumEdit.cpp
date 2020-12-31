#include "stdafx.h"
#include "CCtl.h"
#include "NumEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MCNumEdit::MCNumEdit()
{
}

MCNumEdit::~MCNumEdit()
{
}


BEGIN_MESSAGE_MAP(MCNumEdit, CEdit)
	//{{AFX_MSG_MAP(MCNumEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MCNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if
	(
		(nChar >= '0' && nChar <= '9') || 
		(nChar == VK_BACK)
	)CEdit::OnChar(nChar, nRepCnt, nFlags);
    else MessageBeep(MB_ICONEXCLAMATION);
}
