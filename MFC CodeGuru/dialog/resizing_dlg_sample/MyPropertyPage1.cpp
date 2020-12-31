// MyPropertyPage1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MyPropertyPage1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyPropertyPage1, cdxCSizingPropPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage2, cdxCSizingPropPage)


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage1 property page

CMyPropertyPage1::CMyPropertyPage1() : cdxCSizingPropPage(CMyPropertyPage1::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage1)
	//}}AFX_DATA_INIT
}

CMyPropertyPage1::~CMyPropertyPage1()
{
}

void CMyPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	cdxCSizingPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage1)
	DDX_Control(pDX, IDC_EDIT, m_wndEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage1, cdxCSizingPropPage)
	//{{AFX_MSG_MAP(CMyPropertyPage1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMyPropertyPage1::OnInitDialog()
{
	BOOL	bOK	=	cdxCSizingPropPage::OnInitDialog();
	AddSzControl(m_wndEdit,cdxCSizingDialog::mdResize,cdxCSizingDialog::mdResize);
	return bOK;
}

BOOL CMyPropertyPage1::OnSetActive()
{
	if(!cdxCSizingPropPage::OnSetActive())
		return FALSE;

	GetSheet().SetWizardButtons(PSWIZB_NEXT);
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage2 property page

CMyPropertyPage2::CMyPropertyPage2() : cdxCSizingPropPage(CMyPropertyPage2::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMyPropertyPage2::~CMyPropertyPage2()
{
}

void CMyPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	cdxCSizingPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage2)
	DDX_Control(pDX, IDC_VSCROLLBAR, m_wndVScroll);
	DDX_Control(pDX, IDC_HSCROLLBAR, m_wndHScroll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage2, cdxCSizingPropPage)
	//{{AFX_MSG_MAP(CMyPropertyPage2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMyPropertyPage2::OnInitDialog()
{
	BOOL	bOK	=	cdxCSizingPropPage::OnInitDialog();
	AddSzControl(m_wndHScroll,cdxCSizingDialog::mdResize,cdxCSizingDialog::mdRepos);
	AddSzControl(m_wndVScroll,cdxCSizingDialog::mdRepos,cdxCSizingDialog::mdResize);
	return bOK;
}


BOOL CMyPropertyPage2::OnSetActive()
{
	if(!cdxCSizingPropPage::OnSetActive())
		return FALSE;

	GetSheet().SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
//	CancelToClose();
	SetModified(TRUE);
	return TRUE;
}

