// DataSheet.cpp : implementation file
//

#include "stdafx.h"
#include "TestHTMLHelp.h"
#include "DataSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSheet

IMPLEMENT_DYNAMIC(CDataSheet, CPropertySheet)

CDataSheet::CDataSheet(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_TESTDLG_CAPTION, pParentWnd, iSelectPage)
//
// if you will work with an opther help-topic activate this line
//
//	,: m_Page2(nHelpNameID)
{
	m_Page2.pSheet = this;

	AddPage(&m_Page1);
	AddPage(&m_Page2);
}

CDataSheet::~CDataSheet()
{
}


BEGIN_MESSAGE_MAP(CDataSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDataSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataSheet message handlers
