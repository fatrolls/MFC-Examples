#include "stdafx.h"
#include "ExtendedEditControls.h"
#include "EditExtensionsSht.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditExtensionsSheet

IMPLEMENT_DYNAMIC(CEditExtensionsSheet, CPropertySheet)

CEditExtensionsSheet::CEditExtensionsSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddControlPages();

	// TODO :: Add the pages for the rest of the controls here.
}

CEditExtensionsSheet::CEditExtensionsSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CEditExtensionsSheet::~CEditExtensionsSheet()
{
}

void CEditExtensionsSheet::AddControlPages()
{
	// Add icon and remove "Apply" button
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_psh.dwFlags |= PSP_USEHICON;
	m_psh.dwFlags|=PSH_NOAPPLYNOW;
	m_psh.hIcon = m_hIcon;

	// add property pages
	AddPage(&m_extendedEditPage);
	AddPage(&m_numericEditPage);
	AddPage(&m_currencyEditPage);
	AddPage(&m_physicalEditPage);
	AddPage(&m_maskedEditPage);
	AddPage(&m_dropEditPage);
}

BEGIN_MESSAGE_MAP(CEditExtensionsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CEditExtensionsSheet)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDHELP, OnAppAbout)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditExtensionsSheet message handlers

BOOL CEditExtensionsSheet::OnInitDialog()
{
	CMenu* pSysMenu = GetSystemMenu(FALSE);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// rename standard Help button
	CWnd* pButtonCancel=GetDlgItem(IDHELP);
	pButtonCancel->SetWindowText(_T("About..."));

//	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);

	return CPropertySheet::OnInitDialog();
}

HCURSOR CEditExtensionsSheet::OnQueryDragIcon() 
{
	return (HCURSOR) m_hIcon;
}

void CEditExtensionsSheet::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		OnAppAbout();
	}
	else
	{
		CPropertySheet::OnSysCommand(nID, lParam);
	}
}

void CEditExtensionsSheet::OnAppAbout()
{
	CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	dlgAbout.DoModal();
}

