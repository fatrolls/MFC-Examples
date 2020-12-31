///////////////////////////////////////////////////////////////////
// Module   : PAGE4.CPP
//
// Purpose  : Implementation of the CPage4 class
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 05-25-96
///////////////////////////////////////////////////////////////////

#include "Page4.h"

IMPLEMENT_DYNCREATE(CPage4, CPropertyPage)

///////////////////////////////////////////////////////////////////
// CPage4 Message Map

BEGIN_MESSAGE_MAP(CPage4, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CPage4 Constructor/destructor

CPage4::CPage4() : CPropertyPage(CPage4::IDD)
{
}

CPage4::~CPage4()
{
}

///////////////////////////////////////////////////////////////////
// CPage4::DoDataExchange()

void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

///////////////////////////////////////////////////////////////////
// CPage4::OnInitDialog()

BOOL CPage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
   m_fntTitle.CreateFont(TITLE_SIZE, 0, 0, 0, FW_BOLD, FALSE, FALSE,
      0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Times New Roman");

   // Display the Finish button


	return TRUE;
}

///////////////////////////////////////////////////////////////////
// CPage4::OnPaint()

void CPage4::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Change the font
   CStatic* pTitle = (CStatic*)GetDlgItem(IDC_TITLE);
   ASSERT_VALID(pTitle);
   pTitle->SetFont(&m_fntTitle);

   // Draw the text
   CString str;
   str.LoadString(IDS_PAGE4_TITLE);
   SetDlgItemText(IDC_TITLE, (LPCTSTR)str);

   str.LoadString(IDS_PAGE4_TEXT);
   SetDlgItemText(IDC_PAGE4_TEXT, (LPCTSTR)str);
}

///////////////////////////////////////////////////////////////////
// CPage4::OnSetActive()

BOOL CPage4::OnSetActive() 
{
   // Display the Finish button
   CPropertySheet* pParent = (CPropertySheet*)GetParent();
   pParent->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

   // Call the inherited method
   return CPropertyPage::OnSetActive();
}

///////////////////////////////////////////////////////////////////
// CPage4::OnWizardFinish()

BOOL CPage4::OnWizardFinish() 
{
	// Get the parent window
   CWizard* pWiz = (CWizard*) GetParent();
   ASSERT_VALID(pWiz);

   // Cleanup any loose ends here...
   pWiz->DisplayReport();

   // Call the inherited method
	return CPropertyPage::OnWizardFinish();
}
