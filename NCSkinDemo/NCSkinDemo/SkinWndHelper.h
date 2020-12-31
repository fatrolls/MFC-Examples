#pragma once

#include "DUIButton.h"
#include <map>
using namespace std;

/*
窗口非客户区自绘帮助类
只需要在初始化时调用Attach
把窗口句柄跟Helper类关联起来
即可，无需再用额外派生一个类

供大家学习参考
Author: 李其宋
Date:2013-10-29
*/

class CSkinWndHelper
{
public:
	CSkinWndHelper(void);
	~CSkinWndHelper(void);
	BOOL   Attach(HWND hWnd);
	void   Detach();
	CDUIButton* AddTitleButton(LPRECT lpRect, Image *pImage, UINT nCount = 3 , UINT nID = 0,LPCTSTR lpszCaption=NULL);

public:
	LRESULT OnNcPaint(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcActivate(WPARAM wParam, LPARAM lParam);
	LRESULT OnActivate(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcLButtonDblClk(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcLButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcLButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcMouseMove(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcMouseHover(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcMouseLeave(WPARAM wParam, LPARAM lParam);
	LRESULT OnSize(WPARAM wParam, LPARAM lParam);
	LRESULT OnSysCommand(WPARAM wParam, LPARAM lParam);
protected:
	static LRESULT WindowProc(HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam);
	int	    TButtonHitTest(CPoint point, CRect& rtButton);
	void    DoNcPaint();
protected:
	int  m_nTitleHeight;
	int  m_nFrameWidth;
	Image *m_pBkImage;
	//标题按钮列表
	std::map<int,CDUIButton> m_TitleBtn;
	int    m_iXButtonHovering;
	BOOL   m_bNCHovering;
	BOOL   m_bNCTracking;

	BOOL   m_bHaveMaxBox;
	BOOL   m_bHaveMinBox;
	BOOL   m_bHaveCloseBtn;

	CRgn m_Rgn;
	//三个标题按钮图片
	vector<Image*> m_WindowBtnImage;
	CRect  m_rcIcon;
	HWND   m_hWnd;
	WNDPROC   m_oldWndProc;
};
