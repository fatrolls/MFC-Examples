// ConfigHeaderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigListCtrl.h"
#include "ConfigHeaderCtrl.h"

// CConfigHeaderCtrl

IMPLEMENT_DYNAMIC(CConfigHeaderCtrl, CHeaderCtrl)

CConfigHeaderCtrl::CConfigHeaderCtrl()
{
}

CConfigHeaderCtrl::~CConfigHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CConfigHeaderCtrl, CHeaderCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()

// CConfigHeaderCtrl message handlers

LRESULT CConfigHeaderCtrl::OnLayout(WPARAM wParam, LPARAM lParam)
{
	LPHDLAYOUT lphdLayout = (LPHDLAYOUT)lParam;

	lphdLayout->prc;

	((CConfigListCtrl *)GetParent())->OnResizeColumn();

	return CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);
}

void CConfigHeaderCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	HDHITTESTINFO hdHitTestInfo;

	hdHitTestInfo.pt.x = point.x;
	hdHitTestInfo.pt.y = point.y;

	SendMessage(HDM_HITTEST, 0, (long)&hdHitTestInfo);

	if (hdHitTestInfo.flags == HHT_ONDIVIDER || hdHitTestInfo.flags == HHT_ONDIVOPEN)
	{
// Note: the default behaviour does not handle HHT_ONDIVOPEN (hidden column).
// In Excel, the equivalent of HHT_ONDIVOPEN will behave the same way as with HHT_ONDIVIDER,
// that is, set the column width to the minimum width required to fully display all items of column.	
		((CConfigListCtrl *)GetParent())->SetColumnMinWidth(hdHitTestInfo.iItem);
	}
	else
		CHeaderCtrl::OnLButtonDblClk(nFlags, point);
}

void CConfigHeaderCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	((CConfigListCtrl *)GetParent())->OnHeaderLButtonDown(nFlags, point);
	CHeaderCtrl::OnLButtonDown(nFlags, point);
}


