// PageTestImages.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageTestImages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTestImages dialog


CPageTestImages::CPageTestImages() : CPropertyPage(CPageTestImages::IDD)
{
	//{{AFX_DATA_INIT(CPageTestImages)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageTestImages::~CPageTestImages()
{
}

void CPageTestImages::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTestImages)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageTestImages, CPropertyPage)
	//{{AFX_MSG_MAP(CPageTestImages)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTestImages message handlers

BOOL CPageTestImages::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_tooltip.Create(this);
	m_tooltip.SetImageList(IDB_SMILES, 16, 16, 22);
	
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), _T("<table align=center valign=middle><tr><td>Original</td><td>Darken</td><td>Lighten</td><td>Grayed</td><td>Shadow</td><td>Scaled</td></tr><tr><td><bmp idres=138 mask></td><td><bmp idres=138 mask style=d></td><td><bmp idres=138 mask style=l></td><td><bmp idres=138 mask style=g></td><td><bmp idres=138 mask style=s></td><td><bmp idres=138 mask width=32 height=48></td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON2), _T("<table align=center valign=middle><tr><td>Original</td><td>Darken</td><td>Lighten</td><td>Grayed</td><td>Shadow</td><td>Scaled</td></tr><tr><td><bmp idres=138></td><td><bmp idres=138 style=d></td><td><bmp idres=138 style=l></td><td><bmp idres=138 style=g></td><td><bmp idres=138 style=s></td><td><bmp idres=138 width=32 height=48></td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON3), _T("<table align=center valign=middle><tr><td>Original</td><td>Darken</td><td>Lighten</td><td>Grayed</td><td>Shadow</td><td>Scaled</td></tr><tr><td><icon idres=142></td><td><icon idres=142 style=d></td><td><icon idres=142 style=l></td><td><icon idres=142 style=g></td><td><icon idres=142 style=s></td><td><icon idres=142 width=48 height=48></td></tr></table>"));
//	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON3), _T("<table align=center valign=middle><tr><td>Original</td><td>Darken</td><td>Lighten</td><td>Grayed</td><td>Shadow</td><td>Scaled</td></tr><tr><td><icon idres=146></td><td><icon idres=146 style=d></td><td><icon idres=146 style=l></td><td><icon idres=146 style=g></td><td><icon idres=146 style=s></td><td><icon idres=146 width=48 height=48></td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON4), _T("<table align=center valign=middle><tr><td>Original</td><td>Darken</td><td>Lighten</td><td>Grayed</td><td>Shadow</td><td>Scaled</td></tr><tr><td><ilst index=2></td><td><ilst index=2 style=d></td><td><ilst index=2 style=l></td><td><ilst index=2 style=g></td><td><ilst index=2 style=s></td><td><ilst index=2 width=48 height=300%></td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON7), _T("<table align=center valign=middle><tr><td>Original</td><td>Darken</td><td>Lighten</td><td>Grayed</td><td>Shadow</td><td>Scaled</td></tr><tr><td><ilst idres=159 cx=32 cy=32 mask speed=1></td><td><ilst idres=159 cx=32 cy=32 mask speed=1 style=d></td><td><ilst idres=159 cx=32 cy=32 mask speed=1 style=l></td><td><ilst idres=159 cx=32 cy=32 mask speed=1 style=g></td><td><ilst idres=159 cx=32 cy=32 mask speed=1 style=s></td><td><ilst idres=159 cx=32 cy=32 mask speed=1 width=200% height=200%></td></tr></table>"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageTestImages::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

BOOL CPageTestImages::OnKillActive() 
{
	m_tooltip.HideTooltip();
	return CPropertyPage::OnKillActive();
}
