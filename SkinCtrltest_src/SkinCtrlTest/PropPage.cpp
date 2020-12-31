// PropPage.cpp : implementation file
//

#include "stdafx.h"
#include "skinctrltest.h"
#include "PropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPage property page

IMPLEMENT_DYNCREATE(CPropPage, CPropertyPage)

CPropPage::CPropPage() : CPropertyPage(CPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropPage::~CPropPage()
{
}

void CPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPage message handlers
