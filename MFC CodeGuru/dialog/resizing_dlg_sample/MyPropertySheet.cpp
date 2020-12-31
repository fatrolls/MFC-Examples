// MyPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MyPropertySheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, cdxCSizingPropSheet)

CMyPropertySheet::CMyPropertySheet(CWnd* pWndParent)
	 : cdxCSizingPropSheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	AddPage(&m_Page1);
	AddPage(&m_Page2);

//	SetWizardMode();	// remove this to get a tab dialog
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, cdxCSizingPropSheet)
	//{{AFX_MSG_MAP(CMyPropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyPropertySheet message handlers


