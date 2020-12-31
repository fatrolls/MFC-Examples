// PpgTest.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ATLMFC.h"
#include "PpgTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpgTest property page

IMPLEMENT_DYNCREATE(CPpgTest, COlePropertyPage)

CPpgTest::CPpgTest() : COlePropertyPage(CPpgTest::IDD, IDS_PPGTEST)
{
	//{{AFX_DATA_INIT(CPpgTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpgTest::~CPpgTest()
{
}

void CPpgTest::DoDataExchange(CDataExchange* pDX)
{
	COlePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgTest)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpgTest, COlePropertyPage)
	//{{AFX_MSG_MAP(CPpgTest)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgTest message handlers
