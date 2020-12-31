#include <afxwin.h>
#include "FontView.h"

#define IDC_PRINT       100
#define IDC_CHECKBOX    101
#define IDC_LISTBOX     102
#define IDC_SAMPLE      103

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

BEGIN_MESSAGE_MAP (CMainWindow, CWnd)
    ON_WM_CREATE ()
    ON_BN_CLICKED (IDC_PRINT, OnPushButtonClicked)
    ON_BN_CLICKED (IDC_CHECKBOX, OnCheckBoxClicked)
    ON_LBN_SELCHANGE (IDC_LISTBOX, OnSelChange)
END_MESSAGE_MAP ()

CMainWindow::CMainWindow ()
{
    CString strWndClass = AfxRegisterWndClass (
        0,
        myApp.LoadStandardCursor (IDC_ARROW),
        (HBRUSH) (COLOR_3DFACE + 1),
        myApp.LoadStandardIcon (IDI_WINLOGO)
    );

    CreateEx (0, strWndClass, _T ("FontView"),
        WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, NULL);

    CRect rect (0, 0, m_cxChar * 68, m_cyChar * 26);
    CalcWindowRect (&rect);

    SetWindowPos (NULL, 0, 0, rect.Width (), rect.Height (),
        SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
}

int CMainWindow::OnCreate (LPCREATESTRUCT lpcs)
{
    if (CWnd::OnCreate (lpcs) == -1)
        return -1;

	//
	// Create an 8-point MS Sans Serif font to use in the controls.
	//
    m_fontMain.CreatePointFont (80, _T ("MS Sans Serif"));

	//
	// Compute the average width and height of a character in the font.
	//
    CClientDC dc (this);
    CFont* pOldFont = dc.SelectObject (&m_fontMain);
    TEXTMETRIC tm;
    dc.GetTextMetrics (&tm);
    m_cxChar = tm.tmAveCharWidth;
    m_cyChar = tm.tmHeight + tm.tmExternalLeading;
    dc.SelectObject (pOldFont);

	//
	// Create the controls that will appear in the FontView window.
	//
    CRect rect (m_cxChar * 2, m_cyChar, m_cxChar * 48, m_cyChar * 2);
    m_wndLBTitle.Create (_T ("Typefaces"), WS_CHILD | WS_VISIBLE | SS_LEFT,
        rect, this);

    rect.SetRect (m_cxChar * 2, m_cyChar * 2, m_cxChar * 48,
        m_cyChar * 18);
    m_wndListBox.CreateEx (WS_EX_CLIENTEDGE, _T ("listbox"), NULL,
        WS_CHILD | WS_VISIBLE | LBS_STANDARD, rect, this, IDC_LISTBOX);

    rect.SetRect (m_cxChar * 2, m_cyChar * 19, m_cxChar * 48,
        m_cyChar * 20);
    m_wndCheckBox.Create (_T ("Show TrueType fonts only"),  WS_CHILD |
        WS_VISIBLE | BS_AUTOCHECKBOX, rect, this, IDC_CHECKBOX);

    rect.SetRect (m_cxChar * 2, m_cyChar * 21, m_cxChar * 66,
        m_cyChar * 25);
    m_wndGroupBox.Create (_T ("Sample"),  WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        rect, this, (UINT) -1);

    rect.SetRect (m_cxChar * 4, m_cyChar * 22, m_cxChar * 64,
        (m_cyChar * 99) / 4);
    m_wndSampleText.Create (_T (""), WS_CHILD | WS_VISIBLE | SS_CENTER, rect,
        this, IDC_SAMPLE);

    rect.SetRect (m_cxChar * 50, m_cyChar * 2, m_cxChar * 66,
        m_cyChar * 4);
    m_wndPushButton.Create (_T ("Print Sample"), WS_CHILD | WS_VISIBLE |
        WS_DISABLED | BS_PUSHBUTTON, rect, this, IDC_PRINT);

	//
	// Set each control's font to 8-point MS Sans Serif.
	//
    m_wndLBTitle.SetFont (&m_fontMain, FALSE);
    m_wndListBox.SetFont (&m_fontMain, FALSE);
    m_wndCheckBox.SetFont (&m_fontMain, FALSE);
    m_wndGroupBox.SetFont (&m_fontMain, FALSE);
    m_wndPushButton.SetFont (&m_fontMain, FALSE);

	//
	// Fill the list box with typeface names and return.
	//
    FillListBox ();
    return 0;
}

void CMainWindow::PostNcDestroy ()
{
    delete this;
}

void CMainWindow::OnPushButtonClicked ()
{
    MessageBox (_T ("This feature is currently unimplemented. Sorry!"),
        _T ("Error"), MB_ICONINFORMATION | MB_OK);
}

void CMainWindow::OnCheckBoxClicked ()
{
    FillListBox ();
    OnSelChange ();
}

void CMainWindow::OnSelChange ()
{
    int nIndex = m_wndListBox.GetCurSel ();

    if (nIndex == LB_ERR) {
        m_wndPushButton.EnableWindow (FALSE);
        m_wndSampleText.SetWindowText (_T (""));
    }
    else {
        m_wndPushButton.EnableWindow (TRUE);
        if ((HFONT) m_fontSample != NULL)
            m_fontSample.DeleteObject ();

        CString strFaceName;
        m_wndListBox.GetText (nIndex, strFaceName);

        m_fontSample.CreateFont (-m_cyChar * 2, 0, 0, 0, FW_NORMAL,
            0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
            FF_DONTCARE, strFaceName);

        m_wndSampleText.SetFont (&m_fontSample);
        m_wndSampleText.SetWindowText (_T ("AaBbCcDdEeFfGg"));
    }
}

void CMainWindow::FillListBox ()
{
    m_wndListBox.ResetContent ();

    CClientDC dc (this);
    ::EnumFontFamilies ((HDC) dc, NULL, (FONTENUMPROC) EnumFontFamProc,
        (LPARAM) this);
}

int CALLBACK CMainWindow::EnumFontFamProc (ENUMLOGFONT* lpelf,
    NEWTEXTMETRIC* lpntm, int nFontType, LPARAM lParam)
{
    CMainWindow* pWnd = (CMainWindow*) lParam;

    if ((pWnd->m_wndCheckBox.GetCheck () == BST_UNCHECKED) ||
        (nFontType & TRUETYPE_FONTTYPE))
        pWnd->m_wndListBox.AddString (lpelf->elfLogFont.lfFaceName);
    return 1;
}
