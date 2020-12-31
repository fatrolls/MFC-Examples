
#include "StdAfx.h"
#include "Resource.h"
#include "SkinScrollBar.h"
#include "SkinSB.h"

CBitmap CSkinScrollBar::m_bmScrollBar;

// 构造函数
CSkinScrollBar::CSkinScrollBar()
{
	if (m_bmScrollBar.m_hObject == NULL) m_bmScrollBar.LoadBitmap(IDB_SCROLLBAR);
}

// 析构函数
CSkinScrollBar::~CSkinScrollBar()
{
}

// 配置滚动
void CSkinScrollBar::InitScroolBar(CWnd* pWnd)
{
	// 设置滚动
	SkinSB_InitH(pWnd->GetSafeHwnd(), (HBITMAP)m_bmScrollBar);

	return;
}
