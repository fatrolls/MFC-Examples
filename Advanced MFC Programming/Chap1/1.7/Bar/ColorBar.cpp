#include "stdafx.h"
#include "Bar.h"
#include "ColorBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CColorBar::CColorBar()
{
}

CColorBar::~CColorBar()
{
}

BOOL CColorBar::AddComboBox()
{
	CRect rect;

	GetItemRect(2, rect);
	rect.bottom=rect.top+150;
	if
	(
		!m_wndComboBox.Create
		(
			WS_CHILD | CBS_DROPDOWN | CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS,
			rect, 
			this,
			ID_BUTTON_BLUE
		)
	)return FALSE;
	else return TRUE;
}

BOOL CColorBar::ShowComboBox()
{
	CRect rect;

	SetButtonInfo(2, ID_BUTTON_BLUE, TBBS_SEPARATOR, 150);
	if(m_wndComboBox.m_hWnd != NULL)
	{
		m_wndComboBox.ShowWindow(SW_SHOW);
	}

	return TRUE;
}

BOOL CColorBar::HideComboBox()
{
	SetButtonInfo(2, ID_BUTTON_BLUE, TBBS_BUTTON, 2);
	if(m_wndComboBox.m_hWnd != NULL)m_wndComboBox.ShowWindow(SW_HIDE);

	return TRUE;
}

CSize CColorBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	if(dwMode & LM_HORZDOCK)ShowComboBox();
	else HideComboBox();

	return CToolBar::CalcDynamicLayout(nLength, dwMode);
}

BEGIN_MESSAGE_MAP(CColorBar, CToolBar)
	//{{AFX_MSG_MAP(CColorBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
