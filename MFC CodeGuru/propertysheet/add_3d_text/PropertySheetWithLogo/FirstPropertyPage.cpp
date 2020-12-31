// FirstPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "propertysheetwithlogo.h"
#include "FirstPropertyPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirstPropertyPage property page

IMPLEMENT_DYNCREATE(CFirstPropertyPage, CPropertyPage)

CFirstPropertyPage::CFirstPropertyPage() : CPropertyPage(CFirstPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CFirstPropertyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFirstPropertyPage::~CFirstPropertyPage()
{
}

void CFirstPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFirstPropertyPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFirstPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFirstPropertyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstPropertyPage message handlers
