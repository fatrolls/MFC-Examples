// ApplicationBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ApplicationBar.h"
#include "ApplicationBarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CApplicationBarDlg dialog

CApplicationBarDlg::CApplicationBarDlg(CWnd* pParent /*=NULL*/)
: COXAppBar<CDialog>(CApplicationBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CApplicationBarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CApplicationBarDlg::~CApplicationBarDlg()
{
}
void CApplicationBarDlg::DoDataExchange(CDataExchange* pDX)
{
	COXAppBar<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CApplicationBarDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CApplicationBarDlg, COXAppBar<CDialog>)
	//{{AFX_MSG_MAP(CApplicationBarDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_ALWAYSONTOP, OnAlwaysontop)
	ON_COMMAND(ID_BOTTOMDOCK, OnBottomdock)
	ON_COMMAND(ID_FLOATDOCK, OnFloat)
	ON_COMMAND(ID_LEFTDOCK, OnLeftdock)
	ON_COMMAND(ID_RIGHTDOCK, OnRightdock)
	ON_COMMAND(ID_TOPDOCK, OnTopdock)
	ON_COMMAND(ID_UNREGISTER, OnUnregister)
	ON_COMMAND(ID_AUTOHIDE, OnAutoHide)
	ON_COMMAND(ID_REGISTER, OnRegister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApplicationBarDlg message handlers

BOOL CApplicationBarDlg::OnInitDialog()
{
	COXAppBar<CDialog>::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	m_menu.LoadMenu(IDR_MENU_POPUP);
	Register();
	if (!LoadState())
	{
		SetEdge(ABE_RIGHT);
		OnAutoHide();
		OnAlwaysontop();
	}

	CMenu* pMenu=m_menu.GetSubMenu(0);
	ASSERT(pMenu);
	const tBarData* pBarData=GetBarData();

	UINT nCheck=/*IsAutoHidden()*/pBarData->bAutoHideDesired?MF_CHECKED:MF_UNCHECKED;
	pMenu->CheckMenuItem(ID_AUTOHIDE, MF_BYCOMMAND | nCheck);   
	nCheck=IsAlwaysOnTop()?MF_CHECKED:MF_UNCHECKED;
	pMenu->CheckMenuItem(ID_ALWAYSONTOP ,MF_BYCOMMAND | nCheck);   


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CApplicationBarDlg::OnPaint() 
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
		COXAppBar<CDialog>::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CApplicationBarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CApplicationBarDlg::DoPopupMenu()
{
	CMenu* pPopupMenu=m_menu.GetSubMenu(0);

	CPoint posMouse;
	GetCursorPos(&posMouse);
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,
		posMouse.x,posMouse.y, this);
}

void CApplicationBarDlg::OnAutoHide()
{
	CMenu* pMenu=m_menu.GetSubMenu(0);
	if (IsAutoHidden())
		SetAutoHide(FALSE);
	else
		SetAutoHide(TRUE);

	UINT nCheck=(IsAutoHidden()?MF_CHECKED:MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_AUTOHIDE, MF_BYCOMMAND | nCheck);   
}

void CApplicationBarDlg::OnAlwaysontop() 
{
	CMenu* pMenu=m_menu.GetSubMenu(0);
	if (IsAlwaysOnTop())
		SetAlwaysOnTop(FALSE);
	else
		SetAlwaysOnTop(TRUE);

	UINT nCheck=(IsAlwaysOnTop()?MF_CHECKED:MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_ALWAYSONTOP ,MF_BYCOMMAND | nCheck);   

}

void CApplicationBarDlg::OnBottomdock() 
{
	CMenu* pMenu=m_menu.GetSubMenu(0);
	UINT nCheck;
	DWORD dwStyle=GetBarStyle();
	if (dwStyle & OX_APPBARS_BOTTOM)
	{
		dwStyle&=~OX_APPBARS_BOTTOM;
		SetBarStyle(dwStyle);
		nCheck=MF_UNCHECKED;
	}
	else
	{
		dwStyle|=OX_APPBARS_BOTTOM;
		SetBarStyle(dwStyle);
		nCheck=MF_CHECKED;
	}
	pMenu->CheckMenuItem(ID_BOTTOMDOCK ,MF_BYCOMMAND | nCheck);   
}

void CApplicationBarDlg::OnFloat() 
{
	CMenu* pMenu=m_menu.GetSubMenu(0);
	UINT nCheck;
	DWORD dwStyle=GetBarStyle();
	if (dwStyle & OX_APPBARS_FLOAT)
	{
		dwStyle&=~OX_APPBARS_FLOAT;
		SetBarStyle(dwStyle);
		nCheck=MF_UNCHECKED;
	}
	else
	{
		dwStyle|=OX_APPBARS_FLOAT;
		SetBarStyle(dwStyle);
		nCheck=MF_CHECKED;
	}
	pMenu->CheckMenuItem(ID_FLOATDOCK ,MF_BYCOMMAND | nCheck);   
	
}


void CApplicationBarDlg::OnLeftdock() 
{
	CMenu* pMenu=m_menu.GetSubMenu(0);
	UINT nCheck;
	DWORD dwStyle=GetBarStyle();
	if (dwStyle & OX_APPBARS_LEFT)
	{
		dwStyle&=~OX_APPBARS_LEFT;
		SetBarStyle(dwStyle);
		nCheck=MF_UNCHECKED;
	}
	else
	{
		dwStyle|=OX_APPBARS_LEFT;
		SetBarStyle(dwStyle);
		nCheck=MF_CHECKED;
	}
	pMenu->CheckMenuItem(ID_LEFTDOCK ,MF_BYCOMMAND | nCheck);   
	
}

void CApplicationBarDlg::OnRightdock() 
{
	CMenu* pMenu=m_menu.GetSubMenu(0);
	UINT nCheck;
	DWORD dwStyle=GetBarStyle();
	if (dwStyle & OX_APPBARS_RIGHT)
	{
		dwStyle&=~OX_APPBARS_RIGHT;
		SetBarStyle(dwStyle);
		nCheck=MF_UNCHECKED;
	}
	else
	{
		dwStyle|=OX_APPBARS_RIGHT;
		SetBarStyle(dwStyle);
		nCheck=MF_CHECKED;
	}
	pMenu->CheckMenuItem(ID_RIGHTDOCK ,MF_BYCOMMAND | nCheck);   
	
}

void CApplicationBarDlg::OnTopdock() 
{
	CMenu* pMenu=m_menu.GetSubMenu(0);
	UINT nCheck;
	DWORD dwStyle=GetBarStyle();
	if (dwStyle & OX_APPBARS_TOP)
	{
		dwStyle&=~OX_APPBARS_TOP;
		SetBarStyle(dwStyle);
		nCheck=MF_UNCHECKED;
	}
	else
	{
		dwStyle|=OX_APPBARS_TOP;
		SetBarStyle(dwStyle);
		nCheck=MF_CHECKED;
	}
	pMenu->CheckMenuItem(ID_TOPDOCK ,MF_BYCOMMAND | nCheck);   
	
}

void CApplicationBarDlg::OnSetEdge(UINT nEdge)
{
	UNREFERENCED_PARAMETER(nEdge);
}

void CApplicationBarDlg::OnUnregister() 
{
	Register(FALSE);	
}

void CApplicationBarDlg::OnRegister() 
{
	Register();	
}
