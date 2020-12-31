#include <afxwin.h>
#include "ColorText.h"

CMyApp myApp;

/////////////////////////////////////////////////////////////////////////
// CMyApp member functions

BOOL CMyApp::InitInstance ()
{
    m_pMainWnd = new CMainWindow;
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow ();
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// CMainWindow message map and member functions

BEGIN_MESSAGE_MAP (CMainWindow, CFrameWnd)
    ON_WM_CREATE ()
    ON_BN_CLICKED (IDC_RED, OnRedButtonClicked)
    ON_BN_CLICKED (IDC_GREEN, OnGreenButtonClicked)
    ON_BN_CLICKED (IDC_BLUE, OnBlueButtonClicked)
END_MESSAGE_MAP ()

CMainWindow::CMainWindow ()
{
    CString strWndClass = AfxRegisterWndClass (
        0,
        myApp.LoadStandardCursor (IDC_ARROW),
        (HBRUSH) (COLOR_3DFACE + 1),
        myApp.LoadStandardIcon (IDI_WINLOGO)
    );

    Create (strWndClass, _T ("ColorText"));
}

int CMainWindow::OnCreate (LPCREATESTRUCT lpcs)
{
    if (CFrameWnd::OnCreate (lpcs) == -1)
        return -1;

    m_font.CreatePointFont (80, _T ("MS Sans Serif"));

    CClientDC dc (this);
    CFont* pOldFont = dc.SelectObject (&m_font);
    TEXTMETRIC tm;
    dc.GetTextMetrics (&tm);
    m_cxChar = tm.tmAveCharWidth;
    m_cyChar = tm.tmHeight + tm.tmExternalLeading;
    dc.SelectObject (pOldFont);

    m_wndGroupBox1.Create (_T ("Sample text"), WS_CHILD | WS_VISIBLE |
        BS_GROUPBOX, CRect (m_cxChar * 2, m_cyChar, m_cxChar * 62,
        m_cyChar * 8), this, UINT (-1));

    m_wndText.Create (_T ("Click a button to change my color"),
        WS_CHILD | WS_VISIBLE | SS_CENTER, CRect (m_cxChar * 4,
        m_cyChar * 4, m_cxChar * 60, m_cyChar * 6), this);

    m_wndGroupBox2.Create (_T ("Color"), WS_CHILD | WS_VISIBLE |
        BS_GROUPBOX, CRect (m_cxChar * 64, m_cyChar, m_cxChar * 80,
        m_cyChar * 8), this, UINT (-1));

    m_wndRadioButtonRed.Create (_T ("Red"), WS_CHILD | WS_VISIBLE |
	    WS_GROUP | BS_AUTORADIOBUTTON, CRect (m_cxChar * 66, m_cyChar * 3,
        m_cxChar * 78, m_cyChar * 4), this, IDC_RED);

    m_wndRadioButtonGreen.Create (_T ("Green"), WS_CHILD | WS_VISIBLE |
        BS_AUTORADIOBUTTON, CRect (m_cxChar * 66, (m_cyChar * 9) / 2,
        m_cxChar * 78, (m_cyChar * 11) / 2), this, IDC_GREEN);

    m_wndRadioButtonBlue.Create (_T ("Blue"), WS_CHILD | WS_VISIBLE |
        BS_AUTORADIOBUTTON, CRect (m_cxChar * 66, m_cyChar * 6,
        m_cxChar * 78, m_cyChar * 7), this, IDC_BLUE);

    m_wndRadioButtonRed.SetCheck (1);
    m_wndText.SetTextColor (RGB (255, 0, 0));

    m_wndGroupBox1.SetFont (&m_font, FALSE);
    m_wndGroupBox2.SetFont (&m_font, FALSE);
    m_wndRadioButtonRed.SetFont (&m_font, FALSE);
    m_wndRadioButtonGreen.SetFont (&m_font, FALSE);
    m_wndRadioButtonBlue.SetFont (&m_font, FALSE);
    return 0;
}

void CMainWindow::OnRedButtonClicked ()
{
    m_wndText.SetTextColor (RGB (255, 0, 0));
}

void CMainWindow::OnGreenButtonClicked ()
{
    m_wndText.SetTextColor (RGB (0, 255, 0));
}

void CMainWindow::OnBlueButtonClicked ()
{
    m_wndText.SetTextColor (RGB (0, 0, 255));
}

/////////////////////////////////////////////////////////////////////////
// CColorStatic message map and member functions

BEGIN_MESSAGE_MAP (CColorStatic, CStatic)
    ON_WM_CTLCOLOR_REFLECT ()
END_MESSAGE_MAP ()

CColorStatic::CColorStatic ()
{
    m_clrText = RGB (0, 0, 0);
    m_clrBack = ::GetSysColor (COLOR_3DFACE);
    m_brBkgnd.CreateSolidBrush (m_clrBack);
}

void CColorStatic::SetTextColor (COLORREF clrText)
{
    m_clrText = clrText;
    Invalidate ();
}

void CColorStatic::SetBkColor (COLORREF clrBack)
{
    m_clrBack = clrBack;
    m_brBkgnd.DeleteObject ();
    m_brBkgnd.CreateSolidBrush (clrBack);
    Invalidate ();
}

HBRUSH CColorStatic::CtlColor (CDC* pDC, UINT nCtlColor)
{
    pDC->SetTextColor (m_clrText);
    pDC->SetBkColor (m_clrBack);
    return (HBRUSH) m_brBkgnd;
}
