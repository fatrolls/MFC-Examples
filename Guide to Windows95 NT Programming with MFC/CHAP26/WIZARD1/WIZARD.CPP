///////////////////////////////////////////////////////////////////
// Module   : WIZARD.CPP
//
// Purpose  : Implementation of the CWizard class
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 05-25-96
///////////////////////////////////////////////////////////////////

#include "wizard.h"
#include "mainwnd.h"

/////////////////////////////////////////////////////////////////////////////
// CWizard

IMPLEMENT_DYNAMIC(CWizard, CPropertySheet)

CWizard::CWizard(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CWizard::CWizard(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CWizard::~CWizard()
{
}

///////////////////////////////////////////////////////////////////
// CWizard::DisplayReport()

void CWizard::DisplayReport()
{
   CWnd* pWnd = AfxGetMainWnd();
   ASSERT_VALID(pWnd);
   CClientDC dc(pWnd);

   CString sMsg;
   sMsg.Format(
      "You chose:   \r\n\r\n"
      "Name: %s %s  \r\n\r\n"
      "Company: %s  \r\n\r\n" 
      "E-Mail: %s   \r\n\r\n" 
      "Food: %s     \r\n\r\n"
      "Compiler: %s",
      m_swd.sFirstName, m_swd.sLastName,
      m_swd.sCompany, m_swd.sEmail,
      m_swd.sFood, m_swd.sCompiler);

   ::MessageBeep(MB_ICONASTERISK);
   MessageBox(sMsg, "Wizard Results", MB_OK | MB_ICONINFORMATION);
}

///////////////////////////////////////////////////////////////////
