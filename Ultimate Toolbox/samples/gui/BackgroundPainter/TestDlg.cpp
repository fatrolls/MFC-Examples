// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BackgroundPainter.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog


CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_nAlign = Tile;
	m_sFilename = _T("");
	//}}AFX_DATA_INIT
	m_clrBack=::GetSysColor(COLOR_BTNFACE);
}


void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_FILENAME, m_cmbFilename);
	DDX_Control(pDX, IDC_BACKCLR, m_btnBackColor);
	DDX_Control(pDX, IDC_SEPARATOR, m_ctlSeparator);
	DDX_Radio(pDX, IDC_ALIGN_TILE, m_nAlign);
	DDX_CBString(pDX, IDC_FILENAME, m_sFilename);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BACKCLR, m_clrBack);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_BN_CLICKED(IDC_ALIGN_BOTTOMCENTER, OnAlign)
	ON_BN_CLICKED(IDC_BACKCLR, OnBackclr)
	ON_CBN_SELCHANGE(IDC_FILENAME, OnSelchangeFilename)
	ON_CBN_EDITCHANGE(IDC_FILENAME, OnEditchangeFilename)
	ON_BN_CLICKED(IDC_ALIGN_BOTTOMLEFT, OnAlign)
	ON_BN_CLICKED(IDC_ALIGN_BOTTOMRIGHT, OnAlign)
	ON_BN_CLICKED(IDC_ALIGN_CENTER, OnAlign)
	ON_BN_CLICKED(IDC_ALIGN_CENTERLEFT, OnAlign)
	ON_BN_CLICKED(IDC_ALIGN_CENTERRIGHT, OnAlign)
	ON_BN_CLICKED(IDC_ALIGN_STRETCH, OnAlign)
	ON_BN_CLICKED(IDC_ALIGN_TILE, OnAlign)
	ON_BN_CLICKED(IDC_ALIGN_TOPCENTER, OnAlign)
	ON_BN_CLICKED(IDC_ALIGN_TOPLEFT, OnAlign)
	ON_BN_CLICKED(IDC_ALIGN_TOPRIGHT, OnAlign)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_cmbFilename.SetAutoPersistent(_T("ImageFileName"));
	for(int nIndex=4; nIndex<OX_HISTORY_COMBO_MAX_TOOLBUTTONS; nIndex++)
	{
		m_cmbFilename.ShowButton(nIndex,FALSE);
	}
	CToolBar* pToolbar=m_cmbFilename.GetToolBar();
	pToolbar->ModifyStyle(NULL,TBSTYLE_FLAT);
	m_cmbFilename.RefreshToolbar();

	m_btnBackColor.SetToolTip(TRUE);
	m_btnBackColor.SetDefaultColor(m_clrBack);

	CWnd* pCtrl=GetDlgItem(IDC_IMAGE);
	ASSERT(pCtrl!=NULL);

	CRect rect;
	pCtrl->GetWindowRect(rect);
	pCtrl->DestroyWindow();
	ScreenToClient(rect);
	m_pictureWnd.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rect,this,IDC_IMAGE);
	m_backPainterOrganizer.Attach(&m_pictureWnd,m_sFilename,(PaintType)m_nAlign);
	m_pictureWnd.ModifyStyleEx(NULL,WS_EX_CLIENTEDGE,SWP_DRAWFRAME);

	m_pictureWnd.RedrawWindow();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CTestDlg::OnAlign() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	m_backPainterOrganizer.SetPaintType(&m_pictureWnd,(PaintType)m_nAlign);
}

void CTestDlg::OnBackclr() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	m_backPainterOrganizer.SetBkColor(&m_pictureWnd,m_clrBack);
}

void CTestDlg::OnSelchangeFilename() 
{
	// TODO: Add your control notification handler code here
	
	if(m_cmbFilename.GetCurSel()!=CB_ERR)
	{
		m_cmbFilename.GetLBText(m_cmbFilename.GetCurSel(),m_sFilename);
		m_backPainterOrganizer.SetWallpaper(&m_pictureWnd,m_sFilename);
	}
}


void CTestDlg::OnEditchangeFilename() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	m_backPainterOrganizer.SetWallpaper(&m_pictureWnd,m_sFilename);
}

void CTestDlg::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	// TODO: Add your message handler code here
	SendMessageToDescendants(WM_PALETTECHANGED,(WPARAM)((HWND)*pFocusWnd),NULL);
}

BOOL CTestDlg::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
	
	SendMessageToDescendants(WM_QUERYNEWPALETTE,NULL,NULL);
	return CDialog::OnQueryNewPalette();
}
