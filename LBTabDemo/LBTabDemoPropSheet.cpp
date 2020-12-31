// LBTabDemoPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "LBTabDemo.h"
#include "LBTabDemoPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoPropSheet

IMPLEMENT_DYNAMIC(CLBTabDemoPropSheet, CPropertySheet)

CLBTabDemoPropSheet::CLBTabDemoPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CLBTabDemoPropSheet::CLBTabDemoPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CLBTabDemoPropSheet::~CLBTabDemoPropSheet()
{
}


BEGIN_MESSAGE_MAP(CLBTabDemoPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CLBTabDemoPropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoPropSheet message handlers

BOOL CLBTabDemoPropSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	CTabCtrl *pTab = GetTabControl();
	//Subclass default CTabCtrl to CLBTabCtrl
	m_TabCtrlEx.SubclassWindow(pTab->m_hWnd);

	return bResult;
}

