///////////////////////////////////////////////////////////////////
// Module   : PAGE1.CPP
//
// Purpose  : Implementation of the CPage1 class
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-05-96
///////////////////////////////////////////////////////////////////

#include "page1.h"

IMPLEMENT_DYNCREATE(CPage1, CPropertyPage)

///////////////////////////////////////////////////////////////////
// CPage1 message map

BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
//  CPage1::CPage1() -- constructor     

CPage1::CPage1() : CPropertyPage(CPage1::IDD)
{
	m_sFirstName = "";
	m_sLastName  = "";
	m_sCompany   = "";
	m_sEmail     = "";
}

///////////////////////////////////////////////////////////////////
//  CPage1::CPage1() -- destructor     

CPage1::~CPage1()
{
}

///////////////////////////////////////////////////////////////////
//  CPage1::DoDataExchange()     

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	// Call the inherited method
   CPropertyPage::DoDataExchange(pDX);

   // Date map
	DDX_Text(pDX, IDC_COMPANY, m_sCompany);
	DDX_Text(pDX, IDC_EMAIL, m_sEmail);
	DDX_Text(pDX, IDC_FIRSTNAME, m_sFirstName);
	DDX_Text(pDX, IDC_LASTNAME, m_sLastName);
}

///////////////////////////////////////////////////////////////////
// CPage1::OnPaint() 

void CPage1::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Change the font
   CStatic* pTitle = (CStatic*)GetDlgItem(IDC_TITLE);
   ASSERT_VALID(pTitle);
   pTitle->SetFont(&m_fntTitle);

   // Draw the text
   CString str;
   str.LoadString(IDS_PAGE1_TITLE);
   SetDlgItemText(IDC_TITLE, (LPCTSTR)str);
}

///////////////////////////////////////////////////////////////////
// CPage1::OnInitDialog() 

BOOL CPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
   m_fntTitle.CreateFont(TITLE_SIZE, 0, 0, 0, FW_BOLD, FALSE, FALSE,
      0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Times New Roman");

	return TRUE;
}

///////////////////////////////////////////////////////////////////
// CPage1::OnWizardNext() 

LRESULT CPage1::OnWizardNext() 
{
   // Updata and verify dialog data
   UpdateData(TRUE);

   // Check to see that text exists in Name edit controls	
   if (m_sFirstName.GetLength() == 0)
   {
      MessageBeep(MB_ICONASTERISK);
      AfxMessageBox("You must enter your First Name...",
         MB_OK | MB_ICONINFORMATION);
      editFirst().SetFocus();

      // Prevent the page from turning
      return -1;
   }

   if (m_sLastName.GetLength() == 0)
   {
      MessageBeep(MB_ICONASTERISK);
      AfxMessageBox("You must enter your Last Name...",
         MB_OK | MB_ICONINFORMATION);
      editLast().SetFocus();

      // Prevent the page from turning
      return -1;
   }

	// Get the parent window
   CWizard* pWiz = (CWizard*) GetParent();
   ASSERT_VALID(pWiz);

   // Update the wizard data
   pWiz->m_swd.sFirstName = m_sFirstName;
   pWiz->m_swd.sLastName  = m_sLastName;
   pWiz->m_swd.sCompany   = m_sCompany;
   pWiz->m_swd.sEmail     = m_sEmail;
   
   // Call the inherited method
	return CPropertyPage::OnWizardNext();
}

///////////////////////////////////////////////////////////////////

