// StyleBar.cpp : implementation file
//

#include "stdafx.h"
#include "MyWord.h"
#include "MyWordDoc.h"
#include "MyWordView.h"
#include "StyleBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStyleBar

BEGIN_MESSAGE_MAP(CStyleBar, CToolBar)
	//{{AFX_MSG_MAP(CStyleBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
    ON_CBN_SELENDOK (IDC_FONTNAMES, OnSelectFont)
    ON_CBN_SELENDOK (IDC_FONTSIZES, OnSelectSize)
    ON_CBN_CLOSEUP (IDC_FONTNAMES, OnCloseUp)
    ON_CBN_CLOSEUP (IDC_FONTSIZES, OnCloseUp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStyleBar message handlers

int CStyleBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    static int nFontSizes[] = {
        8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 32, 36, 48, 72
    };

	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//
    // Load the toolbar.
	//
    if (!LoadToolBar (IDR_STYLE_BAR))
        return -1;

	//
    // Create an 8-point MS Sans Serif font for the combo boxes.
	//
    CClientDC dc (this);
    m_font.CreatePointFont (80, _T ("MS Sans Serif"));
    CFont* pOldFont = dc.SelectObject (&m_font);

    TEXTMETRIC tm;
    dc.GetTextMetrics (&tm);
    int cxChar = tm.tmAveCharWidth;
    int cyChar = tm.tmHeight + tm.tmExternalLeading;

    dc.SelectObject (pOldFont);

	//
    // Add the font name combo box to the toolbar.
	//
    SetButtonInfo (8, IDC_FONTNAMES, TBBS_SEPARATOR, cxChar * 32);

    CRect rect;
    GetItemRect (8, &rect);
    rect.bottom = rect.top + (cyChar * 16);

    if (!m_wndFontNames.Create (WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        CBS_DROPDOWNLIST | CBS_SORT, rect, this, IDC_FONTNAMES))
        return -1;

    m_wndFontNames.SetFont (&m_font);
    InitTypefaceList (&dc);

	//
    // Add the font size combo box to the toolbar.
	//
    SetButtonInfo (10, IDC_FONTSIZES, TBBS_SEPARATOR, cxChar * 12);

    GetItemRect (10, &rect);
    rect.bottom = rect.top + (cyChar * 14);

    if (!m_wndFontSizes.Create (WS_CHILD | WS_VISIBLE | WS_VSCROLL |
        CBS_DROPDOWNLIST, rect, this, IDC_FONTSIZES))
        return -1;

    m_wndFontSizes.SetFont (&m_font);

    CString string;
	int nCount = sizeof (nFontSizes) / sizeof (int);
    for (int i=0; i<nCount; i++) {
        string.Format (_T ("%d"), nFontSizes[i]);            
        m_wndFontSizes.AddString (string);
    }
    return 0;
}

void CStyleBar::OnSelectFont ()
{
    TCHAR szFaceName[LF_FACESIZE];
    int nIndex = m_wndFontNames.GetCurSel ();
    m_wndFontNames.GetLBText (nIndex, szFaceName);

    CMyWordView* pView =
        (CMyWordView*) ((CFrameWnd*) AfxGetMainWnd ())->GetActiveView ();
    pView->ChangeFont (szFaceName);
}

void CStyleBar::OnSelectSize ()
{
    TCHAR szSize[8];
    int nIndex = m_wndFontSizes.GetCurSel ();
    m_wndFontSizes.GetLBText (nIndex, szSize);

    int nSize = atoi (szSize) * 20; // Need twips

    CMyWordView* pView =
        (CMyWordView*) ((CFrameWnd*) AfxGetMainWnd ())->GetActiveView ();
    pView->ChangeFontSize (nSize);
}

void CStyleBar::OnCloseUp ()
{
    ((CFrameWnd*) AfxGetMainWnd ())->GetActiveView ()->SetFocus ();
}

void CStyleBar::InitTypefaceList (CDC* pDC)
{
    ::EnumFontFamilies (pDC->m_hDC, NULL,
        (FONTENUMPROC) EnumFontNameProc, (LPARAM) this);
}

int CALLBACK CStyleBar::EnumFontNameProc (ENUMLOGFONT* lpelf,
    NEWTEXTMETRIC* lpntm, int nFontType, LPARAM lParam)
{
    CStyleBar* pWnd = (CStyleBar*) lParam;
    if (nFontType & TRUETYPE_FONTTYPE)
        pWnd->m_wndFontNames.AddString (lpelf->elfLogFont.lfFaceName);
    return 1;
}

void CStyleBar::OnUpdateCmdUI (CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
    CToolBar::OnUpdateCmdUI (pTarget, bDisableIfNoHndler);

    CWnd* pWnd = GetFocus ();
    if ((pWnd == &m_wndFontNames) || (pWnd == &m_wndFontSizes))
        return;

	//
    // Get the font name and size.
	//
    int nTwips;
    TCHAR szFaceName[LF_FACESIZE];

    CMyWordView* pView =
        (CMyWordView*) ((CFrameWnd*) AfxGetMainWnd ())->GetActiveView ();
    pView->GetFontInfo (szFaceName, nTwips);

	//
    // Update the font name combo box.
	//
    TCHAR szSelection[LF_FACESIZE];
    m_wndFontNames.GetWindowText (szSelection,
		sizeof (szSelection) / sizeof (TCHAR));

    if (::lstrcmp (szFaceName, szSelection) != 0) {
        if (szFaceName[0] == 0)
            m_wndFontNames.SetCurSel (-1);
        else {
            if (m_wndFontNames.SelectString (-1, szFaceName) == CB_ERR)
                m_wndFontNames.SetCurSel (-1);
        }
    }

	//
    // Update the font size combo box.
	//
    TCHAR szSize[4];
    m_wndFontSizes.GetWindowText (szSize, sizeof (szSize) / sizeof (TCHAR));
    int nSizeFromComboBox = atoi (szSize);
    int nSizeFromView = nTwips / 20;

    if (nSizeFromComboBox != nSizeFromView) {
        if (nTwips == -1)
            m_wndFontSizes.SetCurSel (-1);
        else {
            CString string;
            string.Format (_T ("%d"), nSizeFromView);
            if (m_wndFontSizes.SelectString (-1, string) == CB_ERR)
                m_wndFontSizes.SetCurSel (-1);
        }
    }
}
