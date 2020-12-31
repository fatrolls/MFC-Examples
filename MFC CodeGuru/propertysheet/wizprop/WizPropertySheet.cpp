// WizPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "MySetup.h"
#include "WizPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizPropertySheet

IMPLEMENT_DYNAMIC(CWizPropertySheet, CPropertySheet)

CWizPropertySheet::CWizPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	SetWizardMode();
}

CWizPropertySheet::CWizPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	SetWizardMode();
}

CWizPropertySheet::~CWizPropertySheet()
{
}

void CWizPropertySheet::AddPage( CWizPropertyPage *pPage )
{
	CPropertySheet::AddPage(pPage);
	pPage->m_pPropSheet = this;
}


BEGIN_MESSAGE_MAP(CWizPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CWizPropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizPropertySheet message handlers

void CWizPropertySheet::EnablePages(BOOL bEnable, int nStart, int nEnd /* = -1 */)
{
	if (nEnd == -1)
		nEnd = nStart;

	if (nStart > nEnd)
	{
		int tmp = nEnd;
		nEnd = nStart;
		nStart = tmp;
	}

	int count = GetPageCount();

	if (nEnd >= count)
		nEnd = count -1;

	CWizPropertyPage *pPage;

	
	for (int act=nStart; act <= nEnd;act++)
	{
		pPage = (CWizPropertyPage*) GetPage(act);
		pPage->Enable(bEnable);
	}
}
