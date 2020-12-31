///////////////////////////////////////////////////////////////////
// Module   : PAGE3.CPP
//
// Purpose  : Implementation of the CPage3 class
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 05-25-96
///////////////////////////////////////////////////////////////////

#include "page3.h"

IMPLEMENT_DYNCREATE(CPage3, CPropertyPage)

///////////////////////////////////////////////////////////////////
// CPage3 Message Map

BEGIN_MESSAGE_MAP(CPage3, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CPage3 constructor/destructor

CPage3::CPage3() : CPropertyPage(CPage3::IDD)
{
}

CPage3::~CPage3()
{
}

///////////////////////////////////////////////////////////////////
// CPage3::DoDataExchange()

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

///////////////////////////////////////////////////////////////////
// CPage3::OnInitDialog()

BOOL CPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
   m_fntTitle.CreateFont(TITLE_SIZE, 0, 0, 0, FW_BOLD, FALSE, FALSE,
      0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Times New Roman");

	return TRUE;
}

///////////////////////////////////////////////////////////////////
// CPage3::OnPaint()

void CPage3::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Change the font
   CStatic* pTitle = (CStatic*)GetDlgItem(IDC_TITLE);
   ASSERT_VALID(pTitle);
   pTitle->SetFont(&m_fntTitle);

   // Draw the text
   CString str;
   str.LoadString(IDS_PAGE3_TITLE);
   SetDlgItemText(IDC_TITLE, (LPCTSTR)str);

   str.LoadString(IDS_PAGE3_TEXT);
   SetDlgItemText(IDC_PAGE3_TEXT, (LPCTSTR)str);

   str.LoadString(IDS_PAGE3_1);
   SetDlgItemText(IDC_PAGE3_1, (LPCTSTR)str);

   str.LoadString(IDS_PAGE3_2);
   SetDlgItemText(IDC_PAGE3_2, (LPCTSTR)str);
   
   str.LoadString(IDS_PAGE3_3);
   SetDlgItemText(IDC_PAGE3_3, (LPCTSTR)str);

   str.LoadString(IDS_PAGE3_4);
   SetDlgItemText(IDC_PAGE3_4, (LPCTSTR)str);
}
                                                      
BOOL CPage3::OnSetActive() 
{
   // Remove the Finish button if it's present
   CPropertySheet* pParent = (CPropertySheet*)GetParent();
   pParent->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

   // Call the inherited method
   return CPropertyPage::OnSetActive();
}

///////////////////////////////////////////////////////////////////
// CPage3::OnWizardNext()

LRESULT CPage3::OnWizardNext() 
{
	// Get the parent window
   CWizard* pWiz = (CWizard*) GetParent();
   ASSERT_VALID(pWiz);

   // Update the wizard data
   CString str;

   if (btn1().GetCheck() == 1)
      str.LoadString(IDS_PAGE3_1);
	
   else if (btn2().GetCheck() == 1)
      str.LoadString(IDS_PAGE3_2);
	
   else if (btn3().GetCheck() == 1)
      str.LoadString(IDS_PAGE3_3);
	
   else if (btn4().GetCheck() == 1)
      str.LoadString(IDS_PAGE3_4);

   pWiz->m_swd.sCompiler = str;
	
   // Call the inherited handler
   return CPropertyPage::OnWizardNext();
}

///////////////////////////////////////////////////////////////////

