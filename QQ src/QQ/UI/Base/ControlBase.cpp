#include "StdAfx.h"
#include <mmsystem.h> 
#include "ControlBase.h"

#pragma comment(lib,"Winmm.lib")  

CControlBase::CControlBase(HWND hWnd, UINT uControlID, CRect rc, CString strTitle, BOOL bIsVisible, BOOL bIsDisable,
						   BOOL bRresponse)
{
	m_hWnd = hWnd;
	m_uID = uControlID;
	m_rc = rc;
	m_bIsVisible = bIsVisible;
	m_bIsDisable = bIsDisable;
	m_bRresponse = bRresponse;
	m_strTitle = strTitle;

	VERIFY(m_font.CreateFont(
		12,							// 字体的高度  
		0,							// 字体的宽度  
		0,							// 字体显示的角度
		0,							// 字体的角度
		FW_DONTCARE,				// 字体的磅数
		FALSE,						// 斜体字体
		FALSE,						// 带下划线的字体
		0,							// 带删除线的字体
		GB2312_CHARSET,				// 所需的字符集
		OUT_DEFAULT_PRECIS,			// 输出的精度
		CLIP_DEFAULT_PRECIS,		// 裁减的精度
		DEFAULT_QUALITY,			// 逻辑字体与输出设备的实际
		DEFAULT_PITCH | FF_SWISS,	// 字体间距和字体集
		"宋体"));					// 字体名称

}


CControlBase::~CControlBase(void)
{
	if (m_font.m_hObject)
	{
		m_font.DeleteObject();
	}
}

void CControlBase::SetTitle(CString strTitle) 
{
	if(strTitle != m_strTitle)
	{
		m_strTitle = strTitle;
		::InvalidateRect(m_hWnd, &m_rc, true);
	}
};

// 发送通知消息
bool  CControlBase::SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessage(m_hWnd, Msg, wParam, lParam);
}