//MFToolbar.cpp : Implementation of CMFToolbar

//***************************************************************************//
//                                                                           //
//  This file was created using the CWindowImpl ATL Object Wizard            //
//  By Erik Thompson © 2000                                                  //
//	Version 1.1                                                              //
//  Email questions and comments to ErikT@RadBytes.com                       //
//                                                                           //
//***************************************************************************//

#include "stdafx.h"
#include "resource.h"
#include "MFToolbar.h"

/////////////////////////////////////////////////////////////////////////////
// CMFToolbar

CMFToolbar::CMFToolbar()
: m_hImageList(NULL)
, m_pBrowser(NULL)
{
}

CMFToolbar::~CMFToolbar()
{
	ImageList_Destroy(m_hImageList);
	SetBrowser(NULL);
	if (IsWindow()) DestroyWindow();
}

LRESULT CMFToolbar::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// buttons with images and text
	SendMessage(m_hWnd, TB_SETEXTENDEDSTYLE, 0, (LPARAM)TBSTYLE_EX_MIXEDBUTTONS);
	// Sets the size of the TBBUTTON structure.
	SendMessage(m_hWnd, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
	// Set the maximum number of text rows and bitmap size.
	SendMessage(m_hWnd, TB_SETMAXTEXTROWS, 1, 0L);

	// add our button's caption to the toolbar window
	TCHAR* pCaption = _T("Get Quote");
	int iIndex = ::SendMessage(m_hWnd, TB_ADDSTRING, 0,(LPARAM)pCaption);

	// load our button's icon and create the image list to house it.
	HICON hMotley = LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_MOTLEY));
	m_hImageList = ImageList_Create(16,16, ILC_COLOR16, 1, 0);
	int iImageIndex = ImageList_AddIcon(m_hImageList, hMotley);
	DestroyIcon(hMotley);
	// Set the toolbar's image
	::SendMessage(m_hWnd, TB_SETIMAGELIST, 0, (LPARAM)m_hImageList);

	// add the button for the toolbar to the window
	TBBUTTON Button;
	ZeroMemory((void*)&Button, sizeof(TBBUTTON));
	Button.idCommand = IDM_GETQUOTE;
	Button.fsState = TBSTATE_ENABLED;
	Button.fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE | BTNS_SHOWTEXT;
	Button.dwData = 0;
	Button.iString = iIndex;
	Button.iBitmap = 0;
	::SendMessage(m_hWnd, TB_INSERTBUTTON, 0, (LPARAM)&Button);

	// create our EditQuote window and set the font.
	RECT rect = {0,0,0,0};
	m_EditWnd.Create(m_hWnd, rect, NULL, WS_CHILD|WS_VISIBLE, WS_EX_CLIENTEDGE);
	m_EditWnd.SetFont(static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT)));
	return 0;
}

LRESULT CMFToolbar::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// based on the size of the window area minus the size of the toolbar button, 
	// indent the toolbar so that we can place the edit box before the toolbar 
	// button. This will right justify the toolbar button in the toolbar and the 
	// edit box will use the vaction space to the left of the button but after the 
	// toolbar text as it's usable space.
	RECT wndRect, btnRect;
	GetClientRect(&wndRect);
	::SendMessage(m_hWnd, TB_GETITEMRECT, 0, (LPARAM)&btnRect);
	wndRect.right -= (btnRect.right - btnRect.left);
	SendMessage(TB_SETINDENT, wndRect.right - wndRect.left);
	// put a small spacing gap between the edit box's right edge and the toolbar button's left edge
	wndRect.right -= 3;
	m_EditWnd.MoveWindow(&wndRect, FALSE);
	return 0;
}

void CMFToolbar::SetBrowser(IWebBrowser2* pBrowser)
{
	if (m_pBrowser) m_pBrowser->Release();
	m_pBrowser = pBrowser;
	if (m_pBrowser) m_pBrowser->AddRef();
}

LRESULT CMFToolbar::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!HIWORD(wParam))
	{
		long lSite = LOWORD(wParam);
		if ( lSite == IDM_GETQUOTE)
		{
			GetQuote();
			return 0;
		}
	}
	return -1;
}

LRESULT CMFToolbar::OnGetQuote(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	GetQuote();
	return 0;
}

void CMFToolbar::GetQuote()
{
	// if we have a web browser pointer then try to navigate to The Motley Fool site to retrieve stock quotes.
	if (m_pBrowser)
	{
		VARIANT vEmpty;
		VariantInit(&vEmpty);
		m_pBrowser->Stop();
		_bstr_t bsSite;
		// if the user has entered stock quotes then append them to the url
		if (m_EditWnd.GetWindowTextLength())
		{
			BSTR bstrTickers = NULL;
			m_EditWnd.GetWindowText(&bstrTickers);
			bsSite = "http://quote.fool.com/news/symbolnews.asp?Symbols=";
			bsSite += bstrTickers;
			SysFreeString(bstrTickers);
		}
		// if the user has not entered any stock quotes then just take them to The Motley Fool website.
		else
			bsSite = "http://www.fool.com";
		// have the webrowser navigate to the site URL requested depending on user input.
		m_pBrowser->Navigate(bsSite, &vEmpty, &vEmpty, &vEmpty, &vEmpty);
	}
}