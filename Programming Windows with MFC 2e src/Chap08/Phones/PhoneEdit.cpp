// PhoneEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Phones.h"
#include "PhoneEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhoneEdit

CPhoneEdit::CPhoneEdit()
{
}

CPhoneEdit::~CPhoneEdit()
{
}

BEGIN_MESSAGE_MAP(CPhoneEdit, CEdit)
	//{{AFX_MSG_MAP(CPhoneEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhoneEdit message handlers

void CPhoneEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if (((nChar >= _T ('0')) && (nChar <= _T ('9'))) ||
        (nChar == VK_BACK) || (nChar == _T ('(')) || (nChar == _T (')')) ||
        (nChar == _T ('-')) || (nChar == _T (' ')))
	
		CEdit::OnChar(nChar, nRepCnt, nFlags);
}
