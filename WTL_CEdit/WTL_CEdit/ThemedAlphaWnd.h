/////////////////////////////////////////////////////////////////////
// This file was created by Ming(2013-09-26) 3099jo@163.com
#ifndef _THEMEALPHAWND_H_INCLUDE_
#define _THEMEALPHAWND_H_INCLUDE_
#pragma once
#include <map>
#include <vector>
#include <math.h>
#include "GdiPlusHelper.h"
using namespace std;
using namespace GdiPlusHelper;

class CThemedAlphaWnd : public CWindowImpl<CThemedAlphaWnd, CWindow, CControlWinTraits>
{
public:
	HWND				m_hParentWnd;
private:
	CImageHelper		m_imgBack;
	HWND				m_wndNormal;
	CBitmap				m_bmpBack;
	int					m_nHeight;
	int					m_nWidth;

public:
	DECLARE_WND_CLASS(_T("WTL_ThemedAlphaWindow"))

	CThemedAlphaWnd() : m_wndNormal(NULL)
	{
		m_nHeight	= 0;
		m_nWidth	= 0;
	}

	~CThemedAlphaWnd()
	{

	}

public:
	void SetNormalWnd(const HWND wndNormal)
	{
		ATLASSERT(::IsWindow(wndNormal));
		m_wndNormal = wndNormal;
		AdjustNormalWndPos();
	}

	BOOL SetBackgroundImage(const int nImageID)
	{
		ATLASSERT(nImageID > 0);

		m_imgBack.Load_Image(nImageID, _T("PNG"));

		if (m_imgBack.m_pImage != NULL)
		{
			m_nWidth	= m_imgBack.m_pImage->GetWidth();
			m_nHeight	= m_imgBack.m_pImage->GetHeight();

			// Resize the window size.
			ResizeClient(m_nWidth, m_nHeight);

			Bitmap* bmp = (Bitmap*)(m_imgBack.m_pImage);
			bmp->GetHBITMAP((ARGB)Color::Black, &m_bmpBack.m_hBitmap);

			// Update layered window.
			CClientDC dc(m_hWnd);

			CDC dcCompat;
			dcCompat.CreateCompatibleDC();
			HBITMAP hOldBitmap = dcCompat.SelectBitmap(m_bmpBack);

			CSize size(m_nWidth, m_nHeight);
			CRect rcWindow;
			GetWindowRect(&rcWindow);

			BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

			CPoint ptWnd(rcWindow.left, rcWindow.top);
			CPoint ptSource(0, 0);

			BOOL bSuccess = UpdateLayeredWindow(m_hWnd, dc.m_hDC, &ptWnd, &size,
				dcCompat.m_hDC, &ptSource, 0, &bf, ULW_ALPHA);
			ATLASSERT(bSuccess != FALSE);

			// Reposition normal window.
			AdjustNormalWndPos();
		}
		return FALSE;
	}

private:
	void AdjustNormalWndPos()
	{
		if (::IsWindow(m_wndNormal))
		{
			CRect rcWindow;
			GetWindowRect(&rcWindow);
			::MoveWindow(m_wndNormal, rcWindow.left, rcWindow.top, m_nWidth, m_nHeight, FALSE);
		}
	}

	// Message mapping and handlers.
public:
	BEGIN_MSG_MAP(CThemedAlphaWnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_SIZE, OnMove)
		MESSAGE_HANDLER(WM_MOVE, OnMove)
		MESSAGE_HANDLER(WM_ACTIVATE, OnMove)
		MESSAGE_HANDLER(WM_NCACTIVATE, OnMove)
		MESSAGE_HANDLER(WM_PAINT, OnMove)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnMove)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		// Reset window styles.
		ModifyStyle(WS_MAXIMIZEBOX | WS_SIZEBOX | WS_CAPTION | WS_DLGFRAME, WS_OVERLAPPED, 0);
		// The window style should be WS_EX_LAYERED.
		SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_LAYERED);

		LPCREATESTRUCT lpcs	= ( LPCREATESTRUCT ) lParam;
		LRESULT res			= DefWindowProc( uMsg, wParam, ( LPARAM ) lpcs );
		return res;
	}

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		SendMessage(WM_SYSCOMMAND, 0xF012, 0);
		return 0;
	}

	LRESULT OnMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		AdjustNormalWndPos();
		bHandled = FALSE;
		return 0;
	}
};
#endif // _THEMEDSHADOWWND_H_INCLUDE_
