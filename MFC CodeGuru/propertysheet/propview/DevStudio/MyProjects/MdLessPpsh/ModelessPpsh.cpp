// ModelessPpsh.cpp : implementation file
//

#include "stdafx.h"
#include "MdLessPpsh.h"
#include "ModelessPpsh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelessPpsh

IMPLEMENT_DYNAMIC(CModelessPpsh, CPropertySheet)

CModelessPpsh::CModelessPpsh(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CModelessPpsh::CModelessPpsh(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CModelessPpsh::~CModelessPpsh()
{
}


BEGIN_MESSAGE_MAP(CModelessPpsh, CPropertySheet)
	//{{AFX_MSG_MAP(CModelessPpsh)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelessPpsh message handlers

BOOL CModelessPpsh::OnInitDialog() 
{
	m_bModeless = FALSE;
	BOOL bResult = CPropertySheet::OnInitDialog();
	m_bModeless = TRUE;
	
	return bResult;
}
