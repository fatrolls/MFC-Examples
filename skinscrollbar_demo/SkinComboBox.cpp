// SkinComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinComboBox.h"
#include "skinscrollwnd.h"

// CSkinComboBox

IMPLEMENT_DYNAMIC(CSkinComboBox, CComboBox)

CSkinComboBox::CSkinComboBox()
{
	m_hWndList=NULL;
}

CSkinComboBox::~CSkinComboBox()
{
}


BEGIN_MESSAGE_MAP(CSkinComboBox, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCbnCloseup)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnCbnDropdown)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CSkinComboBox 消息处理程序

void CSkinComboBox::OnCbnCloseup()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_hWndList) return ;
	::ShowWindow(::GetParent(::GetParent(m_hWndList)),SW_HIDE);
}

void CSkinComboBox::OnCbnDropdown()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_hWndList) return ;
	CWnd *pFrame=CWnd::FromHandle(::GetParent(::GetParent(m_hWndList)));
	CRect rc;
	GetWindowRect(&rc);
	CRect rc2;
	this->GetDroppedControlRect(&rc2);
	int nHei;
	int nLineHei=GetItemHeight(0);
	if(nLineHei*GetCount()<rc2.Height()-2)
		nHei=nLineHei*GetCount()+2;
	else
		nHei=rc2.Height();
	pFrame->SetWindowPos(&wndTopMost,rc.left,rc.bottom,rc2.Width(),nHei,0);
	pFrame->ShowWindow(SW_SHOW);
}

HBRUSH CSkinComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_LISTBOX && !m_hWndList && m_hBmpScroll)
	{
		//第一次弹出下拉列表，先隐藏列表
		pWnd->ShowWindow(SW_HIDE);
		SkinWndScroll(pWnd,m_hBmpScroll);
		m_hWndList=pWnd->m_hWnd;
	}
	return hbr;
}
