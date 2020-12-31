/////////////////////////////////////////////////////////////////////
// This file was created by Ming(2013-06-18).
// You could reach me via 3099jo@163.com.
// Enjoy open source and WTL!
/////////////////////////////////////////////////////////////////////
#ifndef _BITMAPEDIT_H_INCLUDE_
#define _BITMAPEDIT_H_INCLUDE_
#include "GdiPlusHelper.h"
using namespace GdiPlusHelper;

class CBitmapEdit : public CWindowImpl<CBitmapEdit>
{
	// Data members.
private:
	CEdit			m_Edit;			// Edit control.
	CImageHelper	m_imgWndBack;	// Window back ground.
	CImageHelper	m_imgWndHot;	// Window hot background.
	int				m_nID;			// Edit ID.
	CBrushHelper	m_brWndBack;	// Back ground brush.
	CBrushHelper	m_brEditBack;	// Edit control back ground.
	DWORD			m_dwStyle;		// The edit control style.
	COLORREF		m_clrText;		// Text color.
	HWND			m_wndParent;	// Parent window.
	BOOL			m_bFocus;		// Indicate user is setting focus on.
	CRect			m_rcEdit;

	// Constructor.
public:
	DECLARE_WND_CLASS(_T("WTL_BitmapEditControl"))

	CBitmapEdit() : m_nID(0), m_clrText( RGB(0, 0, 0) ), m_wndParent(NULL), m_bFocus(FALSE), m_rcEdit(1, 1, 1, 1)
	{
		m_dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | ES_AUTOHSCROLL | DT_LEFT;
	}

	// Operations.
public:
	BOOL SetControlID(int nID)
	{
		if (nID > 0)
		{
			m_nID = nID;
			return TRUE;
		}
		ATLASSERT(FALSE);
		return FALSE;
	}

	HWND Create(const HWND wndParent, const int nID)
	{
		if (::IsWindow(wndParent) && nID > 0)
		{
			m_nID = nID;
			m_wndParent = wndParent;
			return CWindowImpl<CBitmapEdit>::Create(wndParent, NULL, NULL, WS_VISIBLE | WS_CHILD, NULL);
		}
		ATLASSERT(FALSE);
		return NULL;
	}

	BOOL SetThemeParent(HWND wndParent)
	{
		ATLASSERT(::IsWindow(wndParent));
		m_wndParent = wndParent;
		return TRUE;
	}

	BOOL LoadBackGroundImage(int nImageNormal, int nImageHot)
	{
		if (nImageNormal > 0 && nImageHot)
		{
			m_imgWndBack.Load_Image(nImageNormal, _T("PNG"));
			m_imgWndHot.Load_Image(nImageHot, _T("PNG"));
			SizeToFit();
			return TRUE;
		}
		ATLASSERT(FALSE);
		return FALSE;
	}

	// Auto adjust control's width and height via back ground image.
	BOOL SizeToFit()
	{
		if (m_imgWndBack.m_pImage)
		{
			ResizeClient(m_imgWndBack.m_pImage->GetWidth(), m_imgWndBack.m_pImage->GetHeight());
			return TRUE;
		}
		ATLASSERT(FALSE);
		return FALSE;
	}

	void SetFont(HFONT font)
	{
		return m_Edit.SetFont(font, TRUE);
	}

	// Set the edit style.
	void SetStyle(DWORD dwStyle)
	{
		m_dwStyle |= dwStyle;
	}

	BOOL SetWindowText(LPCTSTR lpText)
	{
		return m_Edit.SetWindowText(lpText);
	}

	BOOL GetWindowText(CString& strText)
	{
		strText			= _T("");
		int nLength		= m_Edit.GetWindowTextLength();

		if (nLength)
		{
			nLength = nLength + 1;
			TCHAR* pText = new TCHAR[nLength];
			memset(pText, 0, nLength);
			m_Edit.GetWindowText(pText, nLength);
			strText = pText;
			free(pText);
		}
		return TRUE;
	}

	void SetTextColor(COLORREF clrText)
	{
		m_clrText = clrText;
		Invalidate();
	}

	void SetPasswordStyle()
	{
		TCHAR a;
		PBYTE p	= (PBYTE)&a;
		*p		= 0xcf;
		*(p+1)	= 0x25;

		m_Edit.SetPasswordChar(a);
	}

	void DeflateEditRect(CRect rc)
	{
		m_rcEdit = rc;
	};

	BOOL IsFocused()
	{
		return m_bFocus;
	}

	void SetFocus(BOOL bFocus = TRUE)
	{
		if (bFocus)
		{
			::PostMessage(m_Edit.m_hWnd, WM_SETFOCUS, (WPARAM)m_Edit.m_hWnd, 0);
			::PostMessage(m_Edit.m_hWnd, WM_ACTIVATE, WA_ACTIVE, 0);
		}
		else
		{
			::PostMessage(m_Edit.m_hWnd, WM_KILLFOCUS, 0, 0);
		}
	}

private:
	void DoPaint(Graphics& g)
	{
		// If parent window invisible, do nothing.
		if ( !::IsWindowVisible(m_wndParent) )
		{
			return;
		}

		CRect rcClient;
		GetClientRect(&rcClient);
		Rect rc(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);

		// Preserve background.
		if( m_brWndBack.m_pBrush == NULL )
		{
			m_brWndBack.GetBackGroundBrush(m_hWnd, m_wndParent);
		}
		g.FillRectangle(m_brWndBack.m_pBrush, rc);


		// Draw edit back ground.
		CBitmap bmp;
		if (m_bFocus)
		{
			g.DrawImage(m_imgWndHot.m_pImage, rc);
		}
		else
		{
			g.DrawImage(m_imgWndBack.m_pImage, rc);
		}
		
		// Adjust edit control window area.
		AdjustEditWindow(rcClient);
	}

	void AdjustEditWindow(CRect rcClient)
	{
		//rcClient.DeflateRect(m_rcEdit);
		m_Edit.MoveWindow(&m_rcEdit, TRUE);
		m_Edit.ShowWindow(SW_SHOW);
	}

	// Message map and handlers.
public:
	BEGIN_MSG_MAP(CBitmapEdit)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
		MESSAGE_HANDLER(WM_MOVE, OnSize)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnCtlColorEdit)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorEdit)
		COMMAND_HANDLER(m_nID, EN_SETFOCUS, OnEnSetFocus)
		COMMAND_HANDLER(m_nID, EN_KILLFOCUS, OnEnKillFocus)
		COMMAND_HANDLER(m_nID, EN_CHANGE, OnEnChange)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		// You need call SetControlID() before created.
		ATLASSERT(m_nID > 0);

		m_Edit.Create(m_hWnd, CRect(1, 1, 1, 1), _T(""), m_dwStyle, 0, m_nID);

		LPCREATESTRUCT lpcs	= ( LPCREATESTRUCT ) lParam;
		LRESULT res			= DefWindowProc( uMsg, wParam, ( LPARAM ) lpcs );
		return res;
	}

	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 0;
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if( wParam != NULL )
		{
			Graphics g((HDC) wParam);
			DoPaint(g);
		}
		else
		{
			CPaintDC dc(m_hWnd);
			Graphics g(dc.m_hDC);
			DoPaint(g);
		}
		return 0;
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_brWndBack.DeleteOldBrush();
		m_brEditBack.DeleteOldBrush();
		return TRUE;
	}

	LRESULT OnCtlColorEdit(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CDCHandle dc( (HDC) wParam );
		dc.SetTextColor(m_clrText);
		dc.SetBkMode(TRANSPARENT);

		// The AtlGetBackgroundBrush will repaint window.
		if( m_brEditBack.m_GDIBrush.m_hBrush == NULL ) 
		{
			m_brEditBack.GetBackGroundBrush(m_Edit.m_hWnd, m_hWnd);
		}

		return (LRESULT)m_brEditBack.m_GDIBrush.m_hBrush;
	}

	LRESULT OnEnSetFocus(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (!m_bFocus)
		{
			m_bFocus = TRUE;
			SizeToFit();
		}

		Invalidate();

		SetMsgHandled(FALSE);
		return 0;
	}

	LRESULT OnEnKillFocus(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (m_bFocus)
		{
			m_bFocus = FALSE;
			SizeToFit();
		}

		Invalidate();

		SetMsgHandled(FALSE);
		return 0;
	}

	LRESULT OnEnChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
	{
		Invalidate();
		bHandled = FALSE;
		return 0;
	}
};

#endif // _BITMAPEDIT_H_INCLUDE_
