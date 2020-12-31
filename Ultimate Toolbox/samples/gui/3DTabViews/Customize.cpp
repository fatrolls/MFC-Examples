// Customize.cpp : implementation file
//

#include "stdafx.h"
#include "TabViews.h"
#include "Customize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDlg dialog


CCustomizeDlg::CCustomizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeDlg)
	m_dwOffsetExt = 0;
	m_dwOffsetInt = 0;
	m_bBottom = FALSE;
	m_bFixedWidth = FALSE;
	m_bMultiline = FALSE;
	m_bScrollOpposite = FALSE;
	m_bOpenCustomizeDlg = FALSE;
	m_bVertical = FALSE;
	//}}AFX_DATA_INIT
	m_dwStyle=0;
}


void CCustomizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeDlg)
	DDX_Control(pDX, IDC_STATIC_TITLE, m_ctlTiltle);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR3, m_separator3);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR2, m_separator2);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR1, m_separator1);
	DDX_Control(pDX, IDC_SPIN_OFFSET_EXTERNAL, m_spinOffsetExt);
	DDX_Text(pDX, IDC_EDIT_OFFSET_EXTERNAL, m_dwOffsetExt);
	DDV_MinMaxDWord(pDX, m_dwOffsetExt, 0, 50);
	DDX_Control(pDX, IDC_SPIN_OFFSET_INTERNAL, m_spinOffsetInt);
	DDX_Text(pDX, IDC_EDIT_OFFSET_INTERNAL, m_dwOffsetInt);
	DDV_MinMaxDWord(pDX, m_dwOffsetInt, 0, 50);
	DDX_Check(pDX, IDC_CHECK_BOTTOM, m_bBottom);
	DDX_Check(pDX, IDC_CHECK_FIXED_WIDTH, m_bFixedWidth);
	DDX_Check(pDX, IDC_CHECK_MULTILINE, m_bMultiline);
	DDX_Check(pDX, IDC_CHECK_SCROLL_OPPOSITE, m_bScrollOpposite);
	DDX_Check(pDX, IDC_CHECK_SHOW_CUSTOMIZE_DLG, m_bOpenCustomizeDlg);
	DDX_Check(pDX, IDC_CHECK_VERTICAL, m_bVertical);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomizeDlg)
	ON_BN_CLICKED(IDC_CHECK_VERTICAL, OnCheckVertical)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDlg message handlers

BOOL CCustomizeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CFont font;
	font.CreatePointFont(-140,_T("Times New Roman"));
	m_ctlTiltle.SetTextFont(&font);
	
	m_spinOffsetExt.SetRange(0,50);
	m_spinOffsetInt.SetRange(0,50);

	m_bBottom=((m_dwStyle&TCS_BOTTOM)==TCS_BOTTOM);
	m_bFixedWidth=((m_dwStyle&TCS_FIXEDWIDTH)==TCS_FIXEDWIDTH);
	m_bMultiline=((m_dwStyle&TCS_MULTILINE)==TCS_MULTILINE);
	m_bScrollOpposite=((m_dwStyle&TCS_SCROLLOPPOSITE)==TCS_SCROLLOPPOSITE);
	m_bVertical=((m_dwStyle&TCS_VERTICAL)==TCS_VERTICAL);

	UpdateData(FALSE);

	OnCheckVertical();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomizeDlg::OnOK() 
{
	if(!UpdateData(TRUE))
		return;

	// TODO: Add extra validation here
	if(m_bBottom)
		m_dwStyle|=0x0002;
	else
		m_dwStyle&=~0x0002;
	if(m_bFixedWidth)
		m_dwStyle|=0x0400;
	else
		m_dwStyle&=~0x0400;
	if(m_bMultiline)
		m_dwStyle|=0x0200;
	else
		m_dwStyle&=~0x0200;
	if(m_bScrollOpposite)
		m_dwStyle|=0x0001;
	else
		m_dwStyle&=~0x0001;
	if(m_bVertical)
		m_dwStyle|=0x0080;
	else
		m_dwStyle&=~0x0080;
	
	CDialog::OnOK();

}

void CCustomizeDlg::OnCheckVertical() 
{
	// TODO: Add your control notification handler code here
	if(!UpdateData(TRUE))
		return;
	if(m_bVertical)
		GetDlgItem(IDC_CHECK_BOTTOM)->SetWindowText(_T("Right aligned"));
	else
		GetDlgItem(IDC_CHECK_BOTTOM)->SetWindowText(_T("Bottom aligned"));
}
