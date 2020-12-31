#include "stdafx.h"
#include "WizPropertyPage.h"
#include "WizPropertySheet.h"

IMPLEMENT_DYNAMIC(CWizPropertyPage, CPropertyPage)

CWizPropertyPage::CWizPropertyPage() : CPropertyPage()
{
	m_pPropSheet = NULL;
	m_bEnabled = TRUE;
}

CWizPropertyPage::CWizPropertyPage(UINT nIDTemplate, UINT nIDCaption /*= 0*/) 
	: CPropertyPage(nIDTemplate, nIDCaption)
{
	m_pPropSheet = NULL;
	m_bEnabled = TRUE;
}

CWizPropertyPage::CWizPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption /*= 0 */)
: CPropertyPage(lpszTemplateName, nIDCaption)
{
	m_pPropSheet = NULL;
	m_bEnabled = TRUE;
}

LRESULT CWizPropertyPage::GetNextPage(BOOL forward)
{
	ASSERT(m_pPropSheet);
	
	int act  = m_pPropSheet->GetActiveIndex();
	int count= m_pPropSheet->GetPageCount();

	act += (forward ? 1: -1);

	BOOL found = FALSE;
	CWizPropertyPage *pPage;

	CString tmp;

	while (!found && act < count && act >=0)
	{
		pPage = (CWizPropertyPage*) m_pPropSheet->GetPage(act);
		if (pPage->IsEnabled())
		{
			found = TRUE;
		}
		else 
		{
			act += (forward ? 1: -1);
		}
		
	}
	
	if (found)
	{
		return (LRESULT) pPage->m_lpszTemplateName; 
	}
	return -1; // Nowhere to go :)
}

BOOL CWizPropertyPage::IsEnabled(void)
{
	return m_bEnabled;
}

BOOL CWizPropertyPage::Enable(BOOL bEnable)
{
	BOOL old = m_bEnabled;
	m_bEnabled = bEnable;
	return old;
}

LRESULT CWizPropertyPage::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	return GetNextPage();
}

LRESULT CWizPropertyPage::OnWizardBack()
{
	return GetNextPage(FALSE);
}


BOOL CWizPropertyPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	return CPropertyPage::OnNotify(wParam,lParam,pResult);
}


BOOL CWizPropertyPage::OnSetActive()
{
	return CPropertyPage::OnSetActive();
}
