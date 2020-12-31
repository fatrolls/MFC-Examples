#include "stdafx.h"
#include "CButtonST_Demo.h"
#include "DlgAdvanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDS_WEBADDR		_T("http://www.softechsoftware.it")

CDlgAdvanced::CDlgAdvanced(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAdvanced::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAdvanced)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	// Show check box initially checked
	m_bTestCheck = TRUE;
}

void CDlgAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAdvanced)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	// Make our buttons a CButtonST buttons
	DDX_Control(pDX, IDC_BTNDERIVED, m_btnDerived);
	DDX_Control(pDX, IDC_BTNHYPERLINK, m_btnHyperLink);
	DDX_Control(pDX, IDC_BTNCURSOR, m_btnCursor);
	DDX_Control(pDX, IDC_BTNFOCUSRECT, m_btnFocusRect);
	DDX_Control(pDX, IDC_CHECK, m_chkCheckbox);
	DDX_Control(pDX, IDC_BTNBITMAP, m_btnBitmap);

	DDX_Check(pDX, IDC_CHECK, m_bTestCheck);
}

BEGIN_MESSAGE_MAP(CDlgAdvanced, CDialog)
	//{{AFX_MSG_MAP(CDlgAdvanced)
	ON_COMMAND(IDM_ITEM1, OnItem1)
	ON_COMMAND(IDM_ITEM2, OnItem2)
	//}}AFX_MSG_MAP

	ON_MESSAGE(WM_USER + 100, On_MenuCallback)
END_MESSAGE_MAP()

BOOL CDlgAdvanced::OnInitDialog() 
{
	short	shBtnColor = 30;

	CDialog::OnInitDialog();

	// CWinXPButtonST button
	m_btnDerived.SetIcon(IDI_CLASSES1);
	m_btnDerived.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnDerived.SetRounded(TRUE);
	// HyperLink button
	m_btnHyperLink.SetIcon(IDI_WEB2);
	m_btnHyperLink.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnHyperLink.SetURL(IDS_WEBADDR);
	m_btnHyperLink.SetTooltipText(IDS_WEBADDR);
	m_btnHyperLink.SetBtnCursor(IDC_HAND2);
	// Cursor button
	m_btnCursor.SetIcon(IDI_TOOLS4);
	m_btnCursor.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
#ifdef	BTNST_USE_BCMENU
	m_btnCursor.SetMenu(IDR_MENU, m_hWnd, TRUE, IDR_TOOLBAR);
#else
	m_btnCursor.SetMenu(IDR_MENU, m_hWnd);
#endif
	m_btnCursor.SetMenuCallback(m_hWnd, WM_USER + 100);
	// "Focus rectangle always present" button
	m_btnFocusRect.SetIcon(IDI_RUN);
	m_btnFocusRect.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnFocusRect.DrawFlatFocus(TRUE);
	// Checkbox
	m_chkCheckbox.SetIcon(IDI_LEDON, IDI_LEDOFF);
	m_chkCheckbox.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	// Bitmap button
	m_btnBitmap.SetBitmaps(IDB_BUTTON, RGB(255, 0, 255));
	m_btnBitmap.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnBitmap.SetPressedStyle(CButtonST::BTNST_PRESSED_TOPBOTTOM, FALSE);
	m_btnBitmap.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnBitmap.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnBitmap.SizeToContent();
	m_btnBitmap.DrawBorder(FALSE, FALSE);

	return TRUE;
} // End of OnInitDialog

void CDlgAdvanced::OnOK()
{
} // End of OnOK

void CDlgAdvanced::OnCancel()
{
} // End of OnCancel

void CDlgAdvanced::OnItem1() 
{
	MessageBox(_T("Selected <Option 1>"), _T("Menu selection"), MB_ICONINFORMATION);
} // End of OnItem1

void CDlgAdvanced::OnItem2() 
{
	MessageBox(_T("Selected <Option 2>"), _T("Menu selection"), MB_ICONINFORMATION);
} // End of OnItem2

// This function will be called just before the menu associated to the
// m_btnCursor button is displayed.
//
LRESULT CDlgAdvanced::On_MenuCallback(WPARAM wParam, LPARAM lParam)
{
#ifdef	BTNST_USE_BCMENU
	BCMenu*	pMenu = (BCMenu*)wParam;
	pMenu->EnableMenuItem(IDM_ITEM3, TRUE);
#else
	::EnableMenuItem((HMENU)wParam, IDM_ITEM3, MF_BYCOMMAND | MF_GRAYED);
#endif
	return 0;
} // End of ON_MenuCallback
