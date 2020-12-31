///////////////////////////////////////////////////////////////////
// Module   : PAGE2.CPP
//
// Purpose  : Implementation of the CPage2 class
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 05-25-96
///////////////////////////////////////////////////////////////////

#include "page2.h"

///////////////////////////////////////////////////////////////////
// CPage2 property page

IMPLEMENT_DYNCREATE(CPage2, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CPage2 message map

BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPage2 constructor/destructor

CPage2::CPage2() : CPropertyPage(CPage2::IDD)
{
}

CPage2::~CPage2()
{
}

/////////////////////////////////////////////////////////////////////////////
// CPage2::DoDataExchange()

void CPage2::DoDataExchange(CDataExchange* pDX)
   {  CPropertyPage::DoDataExchange(pDX); }

/////////////////////////////////////////////////////////////////////////////
// CPage2::OnInitDialog()

BOOL CPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
   m_fntTitle.CreateFont(TITLE_SIZE, 0, 0, 0, FW_BOLD, FALSE, FALSE,
      0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Times New Roman");

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPage2::OnPaint()

void CPage2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Change the font
   CStatic* pTitle = (CStatic*)GetDlgItem(IDC_TITLE);
   ASSERT_VALID(pTitle);
   pTitle->SetFont(&m_fntTitle);

   // Draw the text
   CString str;
   str.LoadString(IDS_PAGE2_TITLE);
   SetDlgItemText(IDC_TITLE, (LPCTSTR)str);

   str.LoadString(IDS_PAGE2_TEXT);
   SetDlgItemText(IDC_PAGE2_TEXT, (LPCTSTR)str);

   str.LoadString(IDS_PAGE2_1);
   SetDlgItemText(IDC_PAGE2_1, (LPCTSTR)str);

   str.LoadString(IDS_PAGE2_2);
   SetDlgItemText(IDC_PAGE2_2, (LPCTSTR)str);
   
   str.LoadString(IDS_PAGE2_3);
   SetDlgItemText(IDC_PAGE2_3, (LPCTSTR)str);

   str.LoadString(IDS_PAGE2_4);
   SetDlgItemText(IDC_PAGE2_4, (LPCTSTR)str);
}

/////////////////////////////////////////////////////////////////////////////
// CPage2::OnWizardNext()

LRESULT CPage2::OnWizardNext() 
{
	// Get the parent window
   CWizard* pWiz = (CWizard*) GetParent();
   ASSERT_VALID(pWiz);

   // Update the wizard data
   CString str;

   if (btn1().GetCheck() == 1)
      str.LoadString(IDS_PAGE2_1);
	
   else if (btn2().GetCheck() == 1)
      str.LoadString(IDS_PAGE2_2);
	
   else if (btn3().GetCheck() == 1)
      str.LoadString(IDS_PAGE2_3);
	
   else if (btn4().GetCheck() == 1)
      str.LoadString(IDS_PAGE2_4);

   pWiz->m_swd.sFood = str;
	
	return CPropertyPage::OnWizardNext();
}
