// ColorPage.cpp : implementation file
//

#include "stdafx.h"
#include "PropDemo.h"
#include "ColorPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorPage property page

IMPLEMENT_DYNCREATE(CColorPage, CPropertyPage)

const COLORREF CColorPage::m_clrColors[3] = {
	RGB (255,   0,   0),	// Red
	RGB (  0, 255,   0),	// Green
	RGB (  0,   0, 255)		// Blue
};

CColorPage::CColorPage() : CPropertyPage(CColorPage::IDD)
{
	//{{AFX_DATA_INIT(CColorPage)
	m_nColor = -1;
	//}}AFX_DATA_INIT
}

CColorPage::~CColorPage()
{
}

void CColorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorPage)
	DDX_Radio(pDX, IDC_RED, m_nColor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorPage, CPropertyPage)
	//{{AFX_MSG_MAP(CColorPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED (IDC_RED, OnChange)
	ON_BN_CLICKED (IDC_GREEN, OnChange)
	ON_BN_CLICKED (IDC_BLUE, OnChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPage message handlers

void CColorPage::OnChange ()
{
	SetModified (TRUE);
}
