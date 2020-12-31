// SizePage.cpp : implementation file
//

#include "stdafx.h"
#include "PropDemo.h"
#include "SizePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSizePage property page

IMPLEMENT_DYNCREATE(CSizePage, CPropertyPage)

CSizePage::CSizePage() : CPropertyPage(CSizePage::IDD)
{
	//{{AFX_DATA_INIT(CSizePage)
	m_nWidth = 0;
	m_nHeight = 0;
	m_nUnits = -1;
	//}}AFX_DATA_INIT
}

CSizePage::~CSizePage()
{
}

void CSizePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSizePage)
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDV_MinMaxInt(pDX, m_nWidth, 1, 128);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDV_MinMaxInt(pDX, m_nHeight, 1, 128);
	DDX_Radio(pDX, IDC_INCHES, m_nUnits);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSizePage, CPropertyPage)
	//{{AFX_MSG_MAP(CSizePage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_EN_CHANGE (IDC_WIDTH, OnChange)
	ON_EN_CHANGE (IDC_HEIGHT, OnChange)
	ON_BN_CLICKED (IDC_INCHES, OnChange)
	ON_BN_CLICKED (IDC_CENTIMETERS, OnChange)
	ON_BN_CLICKED (IDC_PIXELS, OnChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSizePage message handlers

void CSizePage::OnChange ()
{
	SetModified (TRUE);
}
