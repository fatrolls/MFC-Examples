// SkinMenuTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SkinMenuTest.h"
#include "SkinMenuTestDlg.h"

#ifndef NO_SKIN_INI
#include "..\skinwindows\skininiglobalsfile.h"
#endif

#include "..\skinwindows\skinmenumgr.h"
#include "..\skinwindows\skinbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum { COLOR_DEF, COLOR_COFFEE, COLOR_BLUE };

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuTestDlg dialog

CSkinMenuTestDlg::CSkinMenuTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkinMenuTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkinMenuTestDlg)
	m_sSkinPath = _T("");
	m_nColorScheme = COLOR_BLUE;
	m_bGradient = TRUE;
	m_bSidebar = TRUE;
	m_sEdit = _T("Edit Control");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSkinMenuTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkinMenuTestDlg)
	DDX_Control(pDX, IDC_EXPLORER1, m_browser);
	DDX_Text(pDX, IDC_SKINPATH, m_sSkinPath);
	DDX_CBIndex(pDX, IDC_COLORSCHEME, m_nColorScheme);
	DDX_Check(pDX, IDC_GRADIENT, m_bGradient);
	DDX_Check(pDX, IDC_SIDEBAR, m_bSidebar);
	DDX_Text(pDX, IDC_EDIT, m_sEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSkinMenuTestDlg, CDialog)
	//{{AFX_MSG_MAP(CSkinMenuTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_CBN_SELCHANGE(IDC_COLORSCHEME, OnSelchangeColorscheme)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_GRADIENT, OnGradientChange)
	ON_BN_CLICKED(IDC_SIDEBAR, OnSidebarChange)
	ON_COMMAND(ID_FILE_BROWSE, OnBrowse)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuTestDlg message handlers

BOOL CSkinMenuTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_browser.Navigate("about:blank", NULL, NULL, NULL, NULL);

	ResetMenuMgr();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSkinMenuTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSkinMenuTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSkinMenuTestDlg::OnBrowse() 
{
#ifndef NO_SKIN_INI
	CFileDialog dialog(TRUE, NULL, m_sSkinPath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"Skins (*.xml)|*.xml||");
	
	if (dialog.DoModal() == IDOK)
	{
		CSkinIniGlobalsFile sif;
		CString sSkinPath = dialog.GetPathName();

		if (sif.LoadSkin(sSkinPath))
		{
			CSkinMenuMgr::LoadSkin(&sif);

			m_sSkinPath = sSkinPath;
			UpdateData(FALSE);
		}
		else
		{
			CString sMessage;
			sMessage.Format("'%s' is not a skin definition file or does not contain all the necessary resources", sSkinPath);
			AfxMessageBox(sMessage);
		}
	}
#else
	// generic browse to display file open
	CFileDialog dialog(TRUE, NULL, "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"All Files (*.*)|*.*||");
	
	dialog.DoModal();
#endif
}

void CSkinMenuTestDlg::OnSelchangeColorscheme() 
{
	UpdateData();

	ResetMenuMgr();
}

void CSkinMenuTestDlg::ResetMenuMgr()
{
	CSkinMenuMgr::Initialize((m_bSidebar ? SKMS_SIDEBAR : 0) | SKMS_FLAT, 8);
	CSkinMenu::SetRenderer(this);
	
	switch (m_nColorScheme)
	{
	case COLOR_DEF:
		CSkinMenuMgr::ClearColors();
		break;

	case COLOR_COFFEE:
		CSkinMenuMgr::SetColor(COLOR_MENU, RGB(248, 242, 224));
		CSkinMenuMgr::SetColor(COLOR_WINDOWTEXT, RGB(110, 90, 25));
		CSkinMenuMgr::SetColor(COLOR_HIGHLIGHTTEXT, RGB(255, 255, 255));
		CSkinMenuMgr::SetColor(COLOR_3DSHADOW, RGB(150, 130, 70));
		break;

	case COLOR_BLUE:
		CSkinMenuMgr::SetColor(COLOR_MENU, RGB(200, 235, 255));
		CSkinMenuMgr::SetColor(COLOR_WINDOWTEXT, RGB(0, 70, 100));
		CSkinMenuMgr::SetColor(COLOR_HIGHLIGHTTEXT, RGB(255, 255, 255));
		CSkinMenuMgr::SetColor(COLOR_3DSHADOW, RGB(70, 100, 130));
		break;
	}
}

BOOL CSkinMenuTestDlg::DrawMenuNonClientBkgnd(CDC* pDC, LPRECT pRect)
{
	if (m_bGradient)
	{
		DrawGradientBkgnd(pDC, pRect, NULL);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CSkinMenuTestDlg::DrawMenuClientBkgnd(CDC* pDC, LPRECT pRect, LPRECT pClip)
{
	if (m_bGradient)
	{
		DrawGradientBkgnd(pDC, pRect, pClip);
		return TRUE;
	}
	else
		return FALSE;
}

void CSkinMenuTestDlg::DrawGradientBkgnd(CDC* pDC, LPRECT pRect, LPRECT pClip)
{
	COLORREF crFrom = CSkinMenuMgr::GetColor(COLOR_MENU);
	COLORREF crTo = RGB(255, 255, 255);

	if (pClip)
	{
		// ensure that pClip is at least 100 pixels high else the 
		// gradient has artifacts
		CRect rClip(pClip), rRect(pRect);

		if (rClip.Height() < 100 && rRect.Height() > 100)
		{
			rClip.InflateRect(0, (min(rRect.Height(), 100) - rClip.Height()) / 2);

			if (rClip.top < rRect.top)
				rClip.OffsetRect(0, rRect.top - rClip.top);

			else if (rClip.bottom > rRect.bottom)
				rClip.OffsetRect(0, rRect.bottom - rClip.bottom);
		}

		float fHeight = (float)rRect.Height();

		float fFromFactor = (pRect->bottom - rClip.top) / fHeight;
		float fToFactor = (pRect->bottom - rClip.bottom) / fHeight;

		crFrom = CSkinBase::BlendColors(crFrom, crTo, fFromFactor);
		crTo = CSkinBase::BlendColors(crFrom, crTo, fToFactor);

		CSkinBase::GradientFill(pDC, rClip, crFrom, crTo, FALSE);
	}
	else
		CSkinBase::GradientFill(pDC, pRect, crFrom, crTo, FALSE);
}

BOOL CSkinMenuTestDlg::DrawMenuSidebar(CDC* pDC, LPRECT pRect, LPCTSTR szTitle)
{
	if (m_bGradient)
	{
		COLORREF crColor = CSkinMenuMgr::GetColor(COLOR_3DSHADOW);

		COLORREF crFrom = crColor;
		COLORREF crTo = CSkinBase::VaryColor(crFrom, 2.0f);

		CSkinBase::GradientFill(pDC, pRect, crFrom, crTo, FALSE);
		return TRUE;
	}
	else 
	{
		COLORREF crColor = CSkinMenuMgr::GetColor(COLOR_3DSHADOW);

		pDC->FillSolidRect(pRect, crColor);
		return TRUE;
	}

	return FALSE;
}

BOOL CSkinMenuTestDlg::DrawMenuBorder(CDC* pDC, LPRECT pRect)
{
	return FALSE;
}

BOOL CSkinMenuTestDlg::OnEraseBkgnd(CDC* pDC) 
{
	return CDialog::OnEraseBkgnd(pDC);
}

void CSkinMenuTestDlg::OnGradientChange() 
{
	UpdateData();
}

void CSkinMenuTestDlg::OnSidebarChange() 
{
	UpdateData();

	ResetMenuMgr();
}

void CSkinMenuTestDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (pWnd != this)
		return;

	CMenu menu;
	
	if (menu.LoadMenu(IDR_DIALOG_CONTEXT))
	{
		CMenu* pSub = menu.GetSubMenu(0);

		if (pSub)
			pSub->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}
}
