/////////////////////////////////////////////////////////////////////
// This file was created by Ming(2013-09-26) 3099jo@163.com
#ifndef _CTHEMEDLAYERWND_H_INCLUDE_
#define _CTHEMEDLAYERWND_H_INCLUDE_

#pragma once
#include <map>
#include "ThemedAlphaWnd.h"
#include "GdiPlusHelper.h"
using namespace std;
using namespace GdiPlusHelper;

/////////////////////////////////////////////////////////////////////
// CThemedLayerWnd will catch dialog create action and create alpha window first.
template<class T>
class CThemedLayerWnd : public CDialogImpl<T>
{
	// Constructor and destructor.
public:
	CThemedLayerWnd() : m_wndAlpha(NULL)
	{
		m_clrTransparent	= RGB(255, 0, 0);
		m_brBack.CreateSolidBrush(m_clrTransparent);
	}

	~CThemedLayerWnd()
	{
		if (m_wndAlpha != NULL)
		{
			m_wndAlpha->DestroyWindow();

			delete m_wndAlpha;
			m_wndAlpha = NULL;
		}
	}

private:
	COLORREF			m_clrTransparent;	// Define the transparent color.
	CBrush				m_brBack;			// Background brush.
	CImageHelper		m_imgBack;			// Background image.
	CThemedAlphaWnd*	m_wndAlpha;			// Alpha window.
	CBitmap				m_bmpBack;			// GDI bitmap of background image.

public:
	// Create normal dialog and alpha window.
	HWND Create(const HWND wndParent, const int nImageID)
	{
		// Create alpha window before normal dialog created.
		// Do not use WS_CHILD style, we need separated alpha window.
		m_wndAlpha = new CThemedAlphaWnd;
		m_wndAlpha->Create(wndParent, CRect(0, 0, 100, 100), NULL, WS_VISIBLE);
		ATLASSERT(m_wndAlpha->m_hWnd != NULL);
		SetBackgroundImage(nImageID);

		// Create normal dialog.
		HWND hwnd = CDialogImpl<T>::Create(m_wndAlpha->m_hWnd);

		// Pass normal window handle.
		m_wndAlpha->SetNormalWnd(m_hWnd);

		// Set normal dialog style.
		UpdateWindowStyle();
		return hwnd;
	}

	BOOL SetBackgroundImage(const int nImageID)
	{
		m_imgBack.Load_Image(nImageID, _T("PNG"));
		Bitmap* bmp = (Bitmap*)m_imgBack.m_pImage;
		bmp->GetHBITMAP((ARGB)Color::Black, &m_bmpBack.m_hBitmap);
		return m_wndAlpha->SetBackgroundImage(nImageID);
	}

	void SetWindowText(const CString strText)
	{
		if ( ::IsWindow(m_wndAlpha->m_hWnd) )
		{
			m_wndAlpha->SetWindowText(strText);
		}
	}

	BOOL CenterWindow(HWND hWndCenter = NULL)
	{
		if (::IsWindow(m_wndAlpha->m_hWnd))
		{
			return m_wndAlpha->CenterWindow(hWndCenter);
		}
		return FALSE;
	}

private:
	// Set transparent color and remove title window.
	void UpdateWindowStyle()
	{
		ATLASSERT(::IsWindow(this->m_hWnd));
		ModifyStyle(WS_MAXIMIZEBOX | WS_SIZEBOX | WS_CAPTION | WS_DLGFRAME, 0, 0);
		SetWindowLong( GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(m_hWnd, m_clrTransparent, 0, LWA_COLORKEY);
	}

	// Only for control get background image.
	void DoPaint(CDCHandle dc)
	{
		if (m_bmpBack.m_hBitmap != NULL)
		{
			HBITMAP hBmp = dc.SelectBitmap(m_bmpBack.m_hBitmap);
			ATLASSERT(hBmp != NULL);
		}
	}

	// Message mapping.
public:
	BEGIN_MSG_MAP(CThemedLayerWnd)
		MESSAGE_HANDLER(WM_CTLCOLORDLG, OnColorDialog)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	LRESULT OnColorDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		ATLASSERT(m_brBack.m_hBrush != NULL);
		return (LRESULT)m_brBack.m_hBrush;
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// Only for sub controls getting alpha window background image.
		if( wParam != NULL )
		{
			DoPaint((HDC) wParam);
		}

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnShowWindow(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// the window is being hidden
		if (m_wndAlpha->m_hWnd != NULL)
		{
			if (!wParam)	
			{
				m_wndAlpha->ShowWindow(SW_HIDE);
			}
			else
			{
				m_wndAlpha->ShowWindow(SW_SHOW);
			}
		}

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		::SendMessage(m_wndAlpha->m_hWnd, WM_SYSCOMMAND, 0xF012, 0);
		return 0;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		int nWidth = LOWORD(lParam); // width of client area 
		int nHeight = HIWORD(lParam); // height of client area

		// The window is being minimized, inform alpha window.
		if (0 == nHeight && 0 == nWidth)
		{
			m_wndAlpha->ShowWindow(SW_MINIMIZE);
		}

		bHandled = FALSE;
		return 0;
	}
};

#endif // _CTHEMEDLAYERWND_H_INCLUDE_
