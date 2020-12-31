// DataPage.cpp : implementation file
//

#include "stdafx.h"
#include "TestHTMLHelp.h"
#include "DataPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataPage property page

IMPLEMENT_DYNCREATE(CDataPage, CPropertyPage)

CDataPage::CDataPage() : CPropertyPage(CDataPage::IDD)
{
	//{{AFX_DATA_INIT(CDataPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDataPage::~CDataPage()
{
}

void CDataPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDataPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataPage message handlers
