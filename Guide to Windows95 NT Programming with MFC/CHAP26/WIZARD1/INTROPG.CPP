///////////////////////////////////////////////////////////////////
// Module   : INTROPG.CPP
//
// Purpose  : Implementation of the CIntroPage class
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 05-25-96
///////////////////////////////////////////////////////////////////


#include "intropg.h"

IMPLEMENT_DYNCREATE(CIntroPage, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CIntroPage message map

BEGIN_MESSAGE_MAP(CIntroPage, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()

CIntroPage::CIntroPage() : CPropertyPage(CIntroPage::IDD)
{
}

CIntroPage::~CIntroPage()
{
}

void CIntroPage::DoDataExchange(CDataExchange* pDX)
   { CPropertyPage::DoDataExchange(pDX); }

/////////////////////////////////////////////////////////////////////////////
// CIntroPage::OnPaint()

void CIntroPage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Change the font
   CStatic* pTitle = (CStatic*)GetDlgItem(IDC_TITLE);
   ASSERT_VALID(pTitle);
   pTitle->SetFont(&m_fntTitle);

   // Draw the text
   CString str;
   str.LoadString(IDS_WELCOME);
   SetDlgItemText(IDC_TITLE, (LPCTSTR)str);

   str.LoadString(IDS_INTRO1);
   SetDlgItemText(IDC_INTRO1, (LPCTSTR)str);

   str.LoadString(IDS_INTRO2);
   SetDlgItemText(IDC_INTRO2, (LPCTSTR)str);
}

/////////////////////////////////////////////////////////////////////////////
// CIntroPage::OnInitDialog()

BOOL CIntroPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
   m_fntTitle.CreateFont(TITLE_SIZE, 0, 0, 0, FW_BOLD, FALSE, FALSE,
      0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Times New Roman");

	return TRUE;
}
