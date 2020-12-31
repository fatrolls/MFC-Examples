#include "stdafx.h"
#include "Contexthelp.h"

#include "OXContextHelpPropertyPage.h"
#include "TestPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPage dialog

const DWORD CTestPage::m_nHelpIDs[] = 
{
	IDC_STATIC3,		IDH_STATIC3,
	IDC_STATIC4,		IDH_STATIC4,
	IDC_TESTEDIT,		IDH_TESTEDIT,
	IDC_TESTBUTTON,		IDH_TESTBUTTON,
	IDC_CHECK3,			IDH_CHECK3,
	IDD_STYLE,			IDH_STYLE,
	0, 0
};

CTestPage::CTestPage() : COXContextHelpPropertyPage(CTestPage::IDD)
{
	//{{AFX_DATA_INIT(CTestPage)
	//}}AFX_DATA_INIT
}

void CTestPage::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPage)
	DDX_Control(pDX, IDC_STATIC3, m_static3);
	DDX_Control(pDX, IDC_STATIC4, m_static4);
	DDX_Control(pDX, IDC_TESTEDIT, m_edit1);
	DDX_Control(pDX, IDC_CHECK3, m_check1);
	DDX_Control(pDX, IDC_TESTBUTTON, m_button2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestPage, COXContextHelpPropertyPage)
	//{{AFX_MSG_MAP(CTestPage)
	ON_BN_CLICKED(IDC_TESTBUTTON, OnTestbutton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPage message handlers

BOOL CTestPage::AdjustToolTips()
{
	//Set up the Tooltip
	BOOL rt = m_Tooltip.AddTool(&m_static3, _T("A Group Box"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_static4, _T("Some static Text"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_edit1, _T("An Edit Field"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_check1, _T("A Check Box"));
	ASSERT(rt != 0) ;
	rt = m_Tooltip.AddTool(&m_button2, _T("A Button"));
	ASSERT(rt != 0) ;

	return rt;
}


void CTestPage::OnTestbutton() 
{
	AfxMessageBox(_T("Hi, there ..."));
	
}
