// PageTestTable.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageTestTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTestTable property page

IMPLEMENT_DYNCREATE(CPageTestTable, CPropertyPage)

CPageTestTable::CPageTestTable() : CPropertyPage(CPageTestTable::IDD)
{
	//{{AFX_DATA_INIT(CPageTestTable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageTestTable::~CPageTestTable()
{
}

void CPageTestTable::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTestTable)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageTestTable, CPropertyPage)
	//{{AFX_MSG_MAP(CPageTestTable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTestTable message handlers

BOOL CPageTestTable::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_tooltip.Create(this);
	m_tooltip.SetImageList(IDR_MAINFRAME, 16, 15, 9, RGB(192, 192, 192));
	
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), _T("<table><tr><td valign=vcenter><icon idres=141 width=32 height=32></td><td><center><h2>Sample of Simple Table</h2><br><hr color=blue></center><br>2 columns and 1 row without a border</td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON2), _T("<table border=1><tr><td rowspan=2><icon idres=141 width=32 height=32></td><td colspan=2 align=center><h2>Table with colspan and rowspan</h2></td></tr><tr><td>Second row & column</td><td>Second row & third column</td></tr></table>"));
//	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON2), _T("<table border=1><tr><td rowspan=2><icon idres=141 width=32 height=32></td><td colspan=2 align=center><h2>Table with colspan and rowspan</h2></td></tr><tr><td>Second row & column</td><td>Second row & third column</td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON3), _T("<table border=1><tr><td colspan=2 align=center><h2>Table with other table inside</h2></td></tr><tr><td>Look next column</td><td><table border=1 bordercolor=red><tr><td>1</td><td>2</td></tr><tr><td>3</td><td>4</td></tr></table></td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON5), _T("<center><h2>Table backgrounds</h2></center><br><hr color=blue><br>1) Solid background<table border=1 bgcolor=white><tr><td> </td><td> </td></tr></table><br>2) Softbump and Hardbump backgrounds<br><font size=90%>for example only, more types are availables</font><table align=center border=1 bgeffect=softbump bgcolor=white bgmidcolor=#F0F7FF bgendcolor=#C0C0D0><tr><td>Softbump</td><td bgeffect=hardbump>Hardbump</td></tr></table><br>3) Bitmap background<table border=1 background=\"idres:138\"><tr><td> </td><td> </td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON6), _T("<center><h2>Styles of the Table Borders</h2><br><hr color=blue></center><br>1) Border style = solid<table borderstyle=solid cellspacing=1><tr><td width=100> </td><td width=100> </td></tr></table><br>2) Border style = dotted<table borderstyle=dotted cellspacing=1><tr><td> </td><td> </td></tr></table><br>3) Border style = dashed<table borderstyle=dashed cellspacing=1><tr><td> </td><td> </td></tr></table><br>4) Border style = double<table borderstyle=double cellspacing=1><tr><td> </td><td> </td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON4), _T("<center><h2>Colors in the Table</h2></center><br><hr color=blue><br>1) Red Border <table border=2 bordercolor=red width=100><tr><td> </td><td> </td></tr></table><br>2) Lighten and Darken Border<table border=2 bordercolorlight=red bordercolordark=darkred width=100><tr><td> </td><td> </td></tr></table>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON7), _T("<table border=1 align=left valign=vcenter bgeffect=hgradient bgcolor=white bgmidcolor=#F0F7FF bgendcolor=#C0C0D0><tr border=0><td> <ilst index=0> </td><td bgeffect=solid>Demo Dialog</td></tr><tr border=0><td> <ilst index=1> </td><td bgeffect=solid>New</td></tr><tr border=0><td> <ilst index=2> </td><td bgeffect=solid>Open</td></tr><tr border=0><td> <ilst index=3> </td><td bgeffect=solid>Save</td></tr><tr border=0><td> <ilst index=4> </td><td bgeffect=solid>Copy</td></tr><tr border=0><td> <ilst index=5> </td><td bgeffect=solid>Cut</td></tr><tr border=0><td> <ilst index=6> </td><td bgeffect=solid>Paste</td></tr><tr border=0><td> <ilst index=7> </td><td bgeffect=solid>Print</td></tr><tr border=0><td> <ilst index=8> </td><td bgeffect=solid>Help</td></tr></table>"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageTestTable::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

BOOL CPageTestTable::OnKillActive() 
{
	m_tooltip.HideTooltip();
	return CPropertyPage::OnKillActive();
}
