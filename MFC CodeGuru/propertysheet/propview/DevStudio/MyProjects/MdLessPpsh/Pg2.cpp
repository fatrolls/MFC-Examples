// Pg2.cpp : implementation file
//

#include "stdafx.h"
#include "MdLessPpsh.h"
#include "Pg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPg2 property page

IMPLEMENT_DYNCREATE(CPg2, CPropertyPage)

CPg2::CPg2() : CPropertyPage(CPg2::IDD)
{
	//{{AFX_DATA_INIT(CPg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPg2::~CPg2()
{
}

void CPg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPg2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPg2, CPropertyPage)
	//{{AFX_MSG_MAP(CPg2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPg2 message handlers
