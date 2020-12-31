// TranslucentWnd.cpp : implementation file
//

#include "stdafx.h"
#include "TranslucentWnd.h"


// CTranslucentWnd

IMPLEMENT_DYNAMIC(CTranslucentWnd, CWnd)
CTranslucentWnd::CTranslucentWnd()
	: CWnd()
	, m_pRenderListener(NULL)
	, m_bVisible(true)
	, m_bDisabled(false)
{
}

CTranslucentWnd::~CTranslucentWnd()
{
	DestroyImageList();
}


BEGIN_MESSAGE_MAP(CTranslucentWnd, CWnd)
	ON_WM_ENABLE()
END_MESSAGE_MAP()

// CTranslucentWnd message handlers
void CTranslucentWnd::OnEnable(BOOL bEnable)
{
	CWnd::OnEnable(bEnable);

	bool bDisabled = (bEnable != TRUE);
	if (bDisabled != m_bDisabled)
	{
		m_bDisabled = bDisabled;
		UpdateState();
	}
}

BOOL CTranslucentWnd::ShowWindow(int nCmdShow)
{
	BOOL bPrevious = CWnd::ShowWindow(nCmdShow);
	bool visible = (GetWindowLong(GetSafeHwnd(), GWL_STYLE) & WS_VISIBLE) != 0;
	if (visible != m_bVisible)
	{
		m_bVisible = visible;
		NotifyRender();
	}

	return bPrevious;
}

void CTranslucentWnd::UpdateState()
{
	NotifyRender();
}

void CTranslucentWnd::NotifyRender()
{
	if (m_pRenderListener != NULL)
		m_pRenderListener->OnRenderEvent(this);
}

void CTranslucentWnd::DestroyImageList()
{
	size_t nSize = m_imageList.size();
	for (size_t i = 0; i < nSize; ++i)
	{
		if (m_imageList[i] != NULL)
		{
			Gdiplus::DllExports::GdipFree(m_imageList[i]);
			m_imageList[i] = NULL;
		}
	}
}

void CTranslucentWnd::DestroyImage(UINT index)
{
	if (index < m_imageList.size())
	{
		if (m_imageList[index] != NULL)
		{
			Gdiplus::DllExports::GdipFree(m_imageList[index]);
			m_imageList[index] = NULL;
		}
	}
}

void CTranslucentWnd::PreSubclassWindow()
{
	LONG style = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	m_bVisible = (style & WS_VISIBLE) != 0;
	m_bDisabled = (style & WS_DISABLED) != 0;
}
