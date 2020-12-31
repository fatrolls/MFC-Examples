////////////////////////////////////////////////////////////////////////////////////////////
// This file was created by Ming(2012-12-14).
// Do not forget add REFLECT_NOTIFICATIONS() to your caller message map,
// if you create CCustomButton dynamically.

#ifndef _CUSTOMBUTTON_H_INCLUDE_
#define _CUSTOMBUTTON_H_INCLUDE_
#pragma once
#include "GdiPlusHelper.h"
#include <memory>
using namespace GdiPlusHelper;
using namespace std;

class CCustomButton :	public CWindowImpl<CCustomButton, CButton>,
						public CCustomDraw<CCustomButton>
{
private:
	CWindow			    m_wndParent;
	COLORREF		    m_clrText;
	COLORREF		    m_clrSelected;
	COLORREF		    m_clrHot;
	COLORREF		    m_clrDisabled;
	int				    m_nNormal;
	int				    m_nSelected;
	int				    m_nHover;
	int				    m_nDisabled;
	int				    m_nBitmaps;
	int				    m_nLast;
	BOOL			    m_bChecked;
	BOOL			    m_bCheckedStyle;
	CFontHelper         m_Font;
	CBrush				m_brTransparent;
	COLORREF			m_clrTransparent;

	typedef auto_ptr<Bitmap> AUTO_BITMAP;
	CBrushHelper        m_brBack;
	CImageHelper        m_imgButton;
	AUTO_BITMAP         m_bmpNormal;
	AUTO_BITMAP         m_bmpHover;
	AUTO_BITMAP         m_bmpSelected;
	AUTO_BITMAP         m_bmpDisable;
	CRITICAL_SECTION	m_Lock;

	/////////////////////////////////////////////////////////////////////
	// Constructor and destructor.
public:
	CCustomButton()
	{
		InitializeCriticalSection(&m_Lock);

		m_clrTransparent	= RGB(255, 0, 0);
		m_brTransparent.CreateSolidBrush(m_clrTransparent);

		// Initializing font.
		FontFamily   fontFamily(L"Arial");
		m_Font.m_Font = new Font(&fontFamily, 12, FontStyleRegular, UnitPoint);

		// Default colors.
		m_clrText			= RGB(0, 0, 0);
		m_clrSelected		= RGB(0, 0, 0);
		m_clrHot			= RGB(255, 255, 255);
		m_clrDisabled		= RGB(40, 40, 40);
		// Image index.
		m_nNormal			= 0;
		m_nSelected			= 0;
		m_nHover			= 0;
		m_nDisabled			= 0;
		m_nBitmaps			= 0;
		m_bChecked			= FALSE;
		m_bCheckedStyle	= FALSE;
	}

	~CCustomButton()
	{
		DeleteCriticalSection(&m_Lock);
	}

	/////////////////////////////////////////////////////////////////////
	// Button initializing functions.
public:
	BOOL SubclassWindow(HWND hWnd)
	{
		ATLASSERT(m_hWnd==NULL);
		ATLASSERT(::IsWindow(hWnd));
		BOOL bRet = CWindowImpl<CCustomButton, CButton>::SubclassWindow(hWnd);
		return bRet;
	}

	void SetThemeParent(HWND hWnd)
	{
		ATLASSERT(::IsWindow(hWnd));
		m_wndParent = hWnd;
	}

	void SetWindowText(const CString strText)
	{
		if( IsWindow() ) 
		{
			::SetWindowText(m_hWnd, strText);
			DrawAllButtons();
		}
	}

	void SetTextColors(COLORREF clrText, COLORREF clrSelected, COLORREF clrHot, COLORREF clrDisabled)
	{
		m_clrText		= clrText;
		m_clrSelected	= clrSelected;
		m_clrHot		= clrHot;
		m_clrDisabled	= clrDisabled;

		if( IsWindow() ) 
		{
			DrawAllButtons();
		}
	}

	void LoadBitmap(int nImageID, int nBimtmaps)
	{
		ATLASSERT(nBimtmaps > 0);

		m_imgButton.Load_Image(nImageID, _T("PNG"));
		m_nBitmaps  = nBimtmaps;

		// The window style should be WS_EX_LAYERED.
		SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

		if( IsWindow() ) 
		{
			DrawAllButtons();
		}
	}

	void SetImages(int nNormal, int nSelected = 0, int nHover = 0, int nDisabled = 0)
	{
		ATLASSERT(nNormal >= 0);
		ATLASSERT(nSelected >= 0);
		ATLASSERT(nHover >= 0);
		ATLASSERT(nDisabled >= 0);

		m_nNormal	= nNormal;
		m_nSelected	= nSelected;
		m_nHover	= nHover;
		m_nDisabled	= nDisabled;
		m_nLast		= nNormal;

		if( IsWindow() ) 
		{
			DrawAllButtons();
		}
	}

	void EnableCheckStyle(const BOOL bEnable = TRUE)
	{
		m_bCheckedStyle = bEnable;
	}

	void SetCheck(BOOL bCheck = TRUE)
	{
		m_bChecked = bCheck;
		Invalidate(TRUE);
	}

	BOOL IsChecked()
	{
		return m_bChecked;  
	}

private:
	// Draw all buttons' image and text.
	BOOL DrawAllButtons()
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		// client is null, do nothing.
		if (rcClient.Width() == 0)
		{
			return FALSE;
		}

		EnterCriticalSection(&m_Lock);

		m_bmpNormal     = AUTO_BITMAP( new Bitmap(rcClient.Width(), rcClient.Height()) );
		m_bmpHover      = AUTO_BITMAP( new Bitmap(rcClient.Width(), rcClient.Height()) );
		m_bmpSelected   = AUTO_BITMAP( new Bitmap(rcClient.Width(), rcClient.Height()) );
		m_bmpDisable    = AUTO_BITMAP( new Bitmap(rcClient.Width(), rcClient.Height()) );

		DrawSingleButton(*(m_bmpNormal.get()), m_nNormal, m_clrText);
		DrawSingleButton(*(m_bmpHover.get()), m_nHover, m_clrHot);
		DrawSingleButton(*(m_bmpSelected.get()), m_nSelected, m_clrSelected);
		DrawSingleButton(*(m_bmpDisable.get()), m_nDisabled, m_clrDisabled);

		LeaveCriticalSection(&m_Lock);
		return TRUE;
	}

	// Draw button via its status.
	void DrawSingleButton(Bitmap& bmp, const int nPart, COLORREF clrText)
	{
		if (nPart >= 0)
		{
			// Draw background.
			Graphics g(&bmp);
			DrawBackground(g);

			float nWidth    = (float)(m_imgButton.GetWidth() / m_nBitmaps);
			float nHeight   = m_imgButton.GetHeight();
			RectF rcButtonPart(nPart * nWidth, 0.0F, (nPart + 1) * nWidth, nHeight);
			RectF rcButton  = RectF(0.0F, 0.0F, nWidth, nHeight);

			// Draw button.
			g.DrawImage(m_imgButton.m_pImage, rcButton, 
				nPart * nWidth, 0.0F, nWidth, nHeight, UnitPixel);

			// Draw button text.
			DrawButtonText(g, rcButton, clrText);
		}
	}

	// Get and draw button's background.
	BOOL DrawBackground(Graphics& g)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		Rect rc(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);

		// Preserve parent background.
		if (m_brBack.m_pBrush == NULL)
		{
			m_brBack.GetBackGroundBrush( m_hWnd, m_wndParent );
		}

		g.FillRectangle(m_brBack.m_pBrush, rc);
		return TRUE;
	}

	// Draw button's text.
	void DrawButtonText(Graphics& g, RectF& rc, COLORREF clrText)
	{
		TCHAR szText[1024] = { 0 };
		GetWindowText(szText, (sizeof(szText) / sizeof(TCHAR)) - 1);
		if ( _tcslen(szText) != 0 )
		{
			SolidBrush solidBrush( Color(255, GetRValue(clrText), GetGValue(clrText), GetBValue(clrText)) );
			StringFormat stringFormat;
			stringFormat.SetAlignment(StringAlignmentCenter);
			stringFormat.SetLineAlignment(StringAlignmentCenter);
			g.SetTextRenderingHint(TextRenderingHintAntiAlias);
			g.DrawString(szText, -1, m_Font.m_Font, rc, &stringFormat, &solidBrush);
		}
	}

	// Draw last status image, it will used for disabled and checked button.
	void DrawLastStatusImage(Graphics& g, int nImageIndex)
	{
		// only worked with selected and normal status.
		if (nImageIndex == m_nSelected)
		{
			g.DrawImage(m_bmpSelected.get(), 0, 0);
		}
		else
		{
			g.DrawImage(m_bmpNormal.get(), 0, 0);  
		}
	}

	/////////////////////////////////////////////////////////////////////
	// Message map and handlers.
public:
	BEGIN_MSG_MAP(CCustomButton)
		MESSAGE_HANDLER(WM_CTLCOLORBTN, OnColorBtn)
		MESSAGE_HANDLER(WM_SIZE, OnMove)
		MESSAGE_HANDLER(WM_MOVE, OnMove)
		MESSAGE_HANDLER(WM_SETFONT, OnSetFont)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		CHAIN_MSG_MAP_ALT( CCustomDraw< CCustomButton >, 1 )
	END_MSG_MAP()

	LRESULT OnColorBtn(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		ATLASSERT(m_brTransparent.m_hBrush != NULL);
		return (LRESULT)m_brTransparent.m_hBrush;
	}

	LRESULT OnMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		EnterCriticalSection(&m_Lock);

		m_brBack.DeleteOldBrush();

		if (m_imgButton.m_pImage != NULL)
		{
			DrawAllButtons();
		}

		LeaveCriticalSection(&m_Lock);
		return TRUE;
	}

	LRESULT OnSetFont(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		m_Font.DeleteOldFont();
		CPaintDC dc(m_hWnd);
		m_Font.m_Font = new Font(dc, (HFONT) wParam);
		DrawAllButtons();

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if (m_bCheckedStyle)
		{
			if (IsChecked())
			{
				m_bChecked = FALSE;
			}
			else
			{
				m_bChecked = TRUE;           
			}
		}

		bHandled = FALSE;
		return 0;
	}

	// Custom drawing.
	DWORD OnPreErase(int /*uCtrl*/, LPNMCUSTOMDRAW lpNMCD)
	{
		// If button image is null, do nothing.
		if (m_bmpNormal.get() == NULL || m_bmpHover.get() == NULL || 
			m_bmpSelected.get() == NULL || m_bmpDisable.get() == NULL)
		{
			return CDRF_DODEFAULT;
		}

		EnterCriticalSection(&m_Lock);

		CDCHandle dc		= lpNMCD->hdc;
		BOOL bIsHot			= ((lpNMCD->uItemState & CDIS_HOT) != 0);
		BOOL bIsDisabled	= ((lpNMCD->uItemState & CDIS_DISABLED) != 0);
		BOOL bIsSelected	= ((lpNMCD->uItemState & CDIS_SELECTED) != 0);

		// Draw image depend on button status and style.
		Graphics g(dc);
		if ( bIsSelected || (m_bChecked && m_bCheckedStyle) )
		{
			m_nLast = m_nSelected;
			g.DrawImage(m_bmpSelected.get(), 0, 0);
		}
		else if (bIsHot)
		{
			g.DrawImage(m_bmpHover.get(), 0, 0);
		}
		else if(bIsDisabled)
		{
			if (m_bCheckedStyle)
			{
				// If button is checked style and been disabled, draw last status image.
				DrawLastStatusImage(g, m_nLast);
			}
			else
			{
				g.DrawImage(m_bmpDisable.get(), 0, 0);
			}
		}
		else
		{
			m_nLast = m_nNormal;
			g.DrawImage(m_bmpNormal.get(), 0, 0);       
		}

		LeaveCriticalSection(&m_Lock);

		return CDRF_SKIPDEFAULT;
	}

	DWORD OnPrePaint(int /*uCtrl*/, LPNMCUSTOMDRAW /*lpNMCD*/)
	{
		return CDRF_DODEFAULT;
	}
};
#endif // _CUSTOMBUTTON_H_INCLUDE_
