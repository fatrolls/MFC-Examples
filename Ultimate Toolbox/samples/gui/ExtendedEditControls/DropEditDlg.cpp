// DropEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "extendededitcontrols.h"
#include "DropEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CMenuEdit, COXEdit)

BEGIN_MESSAGE_MAP(CMenuEdit, COXEdit)
	//{{AFX_MSG_MAP(CMenuEdit)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(1,10,OnMenuSelect)
END_MESSAGE_MAP()

void CMenuEdit::OnMenuSelect(UINT nID)
{
	CString sItem;
	m_menu.GetMenuString(nID,sItem,MF_BYCOMMAND);
	CString sText;
	sText.Format(_T("<%s> has been picked"),sItem);

	SetWindowText(sText);
}


/////////////////////////////////////////////////////////////////////////////
// CDropEditDlg property page

IMPLEMENT_DYNCREATE(CDropEditDlg, CPropertyPage)

CDropEditDlg::CDropEditDlg() : CPropertyPage(CDropEditDlg::IDD)
{
	//{{AFX_DATA_INIT(CDropEditDlg)
	m_bLeftAligned = FALSE;
	//}}AFX_DATA_INIT
}

CDropEditDlg::~CDropEditDlg()
{
}

void CDropEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDropEditDlg)
	DDX_Control(pDX, IDC_EDIT_CALCULATOR, m_editCalculator);
	DDX_Control(pDX, IDC_STATIC_CALCULATOR, m_sepCalculator);
	DDX_Control(pDX, IDC_STATIC_MENU_EDIT, m_sepMenu);
	DDX_Control(pDX, IDC_EDIT_MENU, m_editMenu);
	DDX_Control(pDX, IDC_STATIC_BROWSECOLOR_EDIT, m_sepBrowseColor);
	DDX_Control(pDX, IDC_EDIT_BROWSECOLOR, m_editBrowseColor);
	DDX_Control(pDX, IDC_STATIC_BROWSEFILE_EDIT, m_sepBrowseFile);
	DDX_Control(pDX, IDC_EDIT_BROWSEFILE, m_editBrowseFile);
	DDX_Control(pDX, IDC_STATIC_BROWSE32_EDIT, m_sepBrowseDir32);
	DDX_Control(pDX, IDC_EDIT_BROWSE32, m_editBrowseDir32);
	DDX_Control(pDX, IDC_EDIT_BROWSE16, m_editBrowseDir16);
	DDX_Control(pDX, IDC_STATIC_BROWSE16_EDIT, m_sepBrowseDir16);
	DDX_Check(pDX, IDC_CHECK_LEFTALIGNED, m_bLeftAligned);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDropEditDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CDropEditDlg)
	ON_BN_CLICKED(IDC_CHECK_LEFTALIGNED, OnCheckLeftaligned)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropEditDlg message handlers

BOOL CDropEditDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	COLORREF clr=::GetSysColor(COLOR_BTNTEXT);
	m_sepBrowseDir16.SetTextColor(clr);
	m_sepBrowseDir32.SetTextColor(clr);
	m_sepBrowseFile.SetTextColor(clr);
	m_sepBrowseColor.SetTextColor(clr);
	m_sepCalculator.SetTextColor(clr);
	m_sepMenu.SetTextColor(clr);

	m_editBrowseDir16.SetMask(_T("Pick directory: #"));
	m_editBrowseDir16.SetBkColor(RGB(0,0,255));
	m_editBrowseDir16.SetTextColor(::GetSysColor(COLOR_WINDOW));

	m_editMenu.SetWindowText(_T("Pick the item"));
	m_editBrowseColor.SetWindowText(_T("Pick the color"));


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDropEditDlg::OnCheckLeftaligned() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int nAlignment=(m_bLeftAligned ? OXDROPEDIT_BUTTONLEFT : OXDROPEDIT_BUTTONRIGHT);
	m_editBrowseColor.SetButtonAlignment(nAlignment);
	m_editBrowseDir16.SetButtonAlignment(nAlignment);
	m_editBrowseDir32.SetButtonAlignment(nAlignment);
	m_editBrowseFile.SetButtonAlignment(nAlignment);
	m_editMenu.SetButtonAlignment(nAlignment);
}
