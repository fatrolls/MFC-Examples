#include "stdafx.h"
#include "Bar.h"
#include "ColorBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define COMBOBOX_INDEX 2
#define COMBOBOX_WIDTH 150
#define COMBOBOX_HEIGHT 150
#define COMBOBOX_BITMAP 2
#define IDC_EDITBAR_SEARCHBOX	101

CColorBar::CColorBar()
{
}

CColorBar::~CColorBar()
{
}

BOOL CColorBar::AddComboBox()
{
	CRect rect(-COMBOBOX_WIDTH, -COMBOBOX_HEIGHT, 0, 0);

	if(!m_wndComboBox.Create(WS_CHILD | CBS_DROPDOWN |
		CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS, rect, this,
		IDC_EDITBAR_SEARCHBOX))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CColorBar::SetHorizontal()
{
	m_bVertical=FALSE;
	SetBarStyle(GetBarStyle() | CBRS_ALIGN_TOP);
	SetButtonInfo(COMBOBOX_INDEX, IDC_EDITBAR_SEARCHBOX, TBBS_SEPARATOR, COMBOBOX_WIDTH);
	if(m_wndComboBox.m_hWnd != NULL)
	{
		CRect rect;
		GetItemRect(COMBOBOX_INDEX, rect);
		m_wndComboBox.SetWindowPos(NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS);
		m_wndComboBox.ShowWindow(SW_SHOW);
	}
	return TRUE;
}

BOOL CColorBar::SetVertical()
{
	m_bVertical = TRUE;

	SetButtonInfo(COMBOBOX_INDEX, ID_BUTTON_BLUE, TBBS_BUTTON, COMBOBOX_BITMAP);
	if (m_wndComboBox.m_hWnd != NULL)m_wndComboBox.ShowWindow(SW_HIDE);
	return TRUE;
}

CSize CColorBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	if(dwMode & LM_COMMIT)
	{
		if(dwMode & LM_VERTDOCK)
		{
			if(!m_bVertical)SetVertical();
		}
		else
		{
			if(m_bVertical)SetHorizontal();
		}
		return CToolBar::CalcDynamicLayout(nLength, dwMode);
	}
	else
	{
		BOOL bOld=m_bVertical;
		BOOL bSwitch=(dwMode & LM_HORZ) ? bOld : !bOld;

		if(bSwitch)
		{
			if(bOld)SetHorizontal();
			else SetVertical();
		}
		CSize sizeResult = CToolBar::CalcDynamicLayout(nLength, dwMode);
		if(bSwitch)
		{
			if(bOld)SetHorizontal();
			else SetVertical();
		}
		return sizeResult;
	}
}
BEGIN_MESSAGE_MAP(CColorBar, CToolBar)
	//{{AFX_MSG_MAP(CColorBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
