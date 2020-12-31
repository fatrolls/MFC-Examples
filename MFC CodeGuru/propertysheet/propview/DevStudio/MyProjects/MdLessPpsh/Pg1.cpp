// Pg1.cpp : implementation file
//

#include "stdafx.h"
#include "MdLessPpsh.h"
#include "Pg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPg1 property page

IMPLEMENT_DYNCREATE(CPg1, CPropertyPage)

CPg1::CPg1() : CPropertyPage(CPg1::IDD)
{
	//{{AFX_DATA_INIT(CPg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPg1::~CPg1()
{
}

void CPg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPg1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPg1, CPropertyPage)
	//{{AFX_MSG_MAP(CPg1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPg1 message handlers
