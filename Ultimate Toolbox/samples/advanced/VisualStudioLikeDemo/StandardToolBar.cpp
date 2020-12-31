// StandardToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "StandardToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_COMBO					1022
const int nDropHeight=200;

/////////////////////////////////////////////////////////////////////////////
// CStandardToolBar

CStandardToolBar::CStandardToolBar()
{
	m_nComboItemIndex=-1;
	m_nSavedCurSel=-1;
}

CStandardToolBar::~CStandardToolBar()
{
}


BEGIN_MESSAGE_MAP(CStandardToolBar, COXCoolToolBar)
	//{{AFX_MSG_MAP(CStandardToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStandardToolBar message handlers

BOOL CStandardToolBar::CreateCombo(int nItemIndex)
{
	// retrieve button info
	GetButtonInfo(nItemIndex,m_nID,m_nStyle,m_nImage);
	
	// retrieve tooltip
	CString sTooltip=GetButtonTooltip(nItemIndex);

	// Create the combo box
	SetButtonInfo(nItemIndex,IDC_COMBO,TBBS_SEPARATOR,180);

	// Design guide advises 12 pixel gap between combos and buttons
	CRect rect;
	GetItemRect(nItemIndex, &rect);
	rect.top = 1;
	rect.bottom = rect.top + nDropHeight;
	if (!m_combo.Create(CBS_DROPDOWN|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL, 
		rect, this, IDC_COMBO))
	{
		TRACE(_T("Failed to create combo-box\n"));
		return FALSE;
	}
	
	static CFont font;
	if((HFONT)font!=NULL)
		font.DeleteObject();
	font.CreatePointFont(-80,_T("MS Sans Serif"));
	m_combo.SetFont(&font);
	m_combo.SetTooltipText(sTooltip);

	m_combo.AddString(_T("OnToolTipText"));
	m_combo.AddString(_T("::LoadTool"));
	m_combo.AddString(_T("ID_VIEW_TOOLBAR"));
	m_combo.AddString(_T("class CWnd"));
	m_combo.AddString(_T("SetFont"));
	m_combo.AddString(_T("class CTabCtrl"));

	m_nComboItemIndex=nItemIndex;

	return TRUE;
}

static BOOL bChangeDockSideCalledFirstTime=TRUE;
void CStandardToolBar::OnChangeDockSide(DWORD dwDockSide)
{
	COXCoolToolBar::OnChangeDockSide(dwDockSide);

	if(bChangeDockSideCalledFirstTime)
	{
		bChangeDockSideCalledFirstTime=FALSE;
		return;
	}


	if((m_pDockBar == NULL || (GetBarStyle() & CBRS_FLOATING)) ||
		dwDockSide==CBRS_ALIGN_RIGHT || dwDockSide==CBRS_ALIGN_LEFT)
	{
		if(::IsWindow(m_combo.GetSafeHwnd()))
		{
			m_nSavedCurSel=m_combo.GetCurSel();
			m_combo.DestroyWindow();
			SetButtonInfo(m_nComboItemIndex, m_nID, m_nStyle, m_nImage);
		}
	}
	else
	{
		if(!::IsWindow(m_combo.GetSafeHwnd()) && m_nComboItemIndex!=-1)
		{
			// CreateCombo function might change the visibility 
			// of the bar. We have to restore it.
			BOOL bIsVisible=IsWindowVisible();
			CreateCombo(m_nComboItemIndex);
			m_combo.SetCurSel(m_nSavedCurSel);
			if(bIsVisible)
				SetWindowPos(NULL, 0, 0, 0, 0,
					SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|
					SWP_NOACTIVATE|SWP_SHOWWINDOW);
			else
				SetWindowPos(NULL, 0, 0, 0, 0,
					SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|
					SWP_NOACTIVATE|SWP_HIDEWINDOW);
		}
	}
}

static BOOL bFloatingDockingCalledFirstTime=TRUE;
void CStandardToolBar::OnFloatingDocking(BOOL bFloating)
{
	COXCoolToolBar::OnFloatingDocking(bFloating);
	if(bFloatingDockingCalledFirstTime)
	{
		bFloatingDockingCalledFirstTime=FALSE;
		return;
	}
	OnChangeDockSide(GetBarStyle()&CBRS_ALIGN_ANY);

	GetParentFrame()->DelayRecalcLayout();
}


