#include "stdafx.h"
#include "DB.h"
#include "PSht.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMLPropertySheet, CPropertySheet)

CMLPropertySheet::CMLPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pParentWnd=pParentWnd;
	AddPage(&m_page1);
	AddPage(&m_page2);
	AddPage(&m_page3);
}

CMLPropertySheet::CMLPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pParentWnd=pParentWnd;
	AddPage(&m_page1);
	AddPage(&m_page2);
	AddPage(&m_page3);
}

void CMLPropertySheet::DoModeless()
{
	if(GetSafeHwnd() == NULL)
	{
		Create(m_pParentWnd);
		ShowWindow(SW_SHOW);
		CenterWindow();
	}
	else
	{
		if(IsWindowVisible() == FALSE)
		{
			ShowWindow(SW_SHOW);
		}
	}
}

CMLPropertySheet::~CMLPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMLPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMLPropertySheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
