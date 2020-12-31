#include "stdafx.h"
#include "ContextHelp.h"

#include "OXContextHelpPropertyPage.h"
#include "Test2Page.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest2Page property page

const DWORD CTest2Page::m_nHelpIDs[] = 
{
	IDC_TESTCHECK1,		IDH_TESTCHECK1,
	IDC_TESTCOMBO1,		IDH_TESTCOMBO1,
	IDC_TESTBUTTON2,	IDH_TESTBUTTON2,
	IDC_LIST1,			IDH_LIST1,
	IDC_SCROLLBAR1,		IDH_SCROLLBAR1,
	IDD_COLOR,			IDH_COLOR,
	0, 0
};

CTest2Page::CTest2Page()
	: COXContextHelpPropertyPage(CTest2Page::IDD)
{
	//{{AFX_DATA_INIT(CTest2Page)
	//}}AFX_DATA_INIT
}

void CTest2Page::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest2Page)
	DDX_Control(pDX, IDC_SCROLLBAR2, m_scroll1);
	DDX_Control(pDX, IDC_TESTCOMBO1, m_combo1);
	DDX_Control(pDX, IDC_TESTCHECK1, m_check1);
	DDX_Control(pDX, IDC_TESTBUTTON2, m_button2);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTest2Page, COXContextHelpPropertyPage)
	//{{AFX_MSG_MAP(CTest2Page)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest2Page message handlers

BOOL CTest2Page::AdjustToolTips() 
{
	//Set up the Tooltip
	BOOL rt = m_Tooltip.AddTool(&m_scroll1, _T("A Scroll Bar"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_combo1, _T("A Combo Box"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_check1, _T("A Check Box"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_button2, _T("A Button"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_list, _T("A List Box"));
	ASSERT(rt != 0) ;

	return rt;
}

