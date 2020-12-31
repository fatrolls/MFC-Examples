// ListPrintPage1.cpp : implementation file
//

#include "stdafx.h"
#include "PrintManager.h"
#include "ListPrintPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListPrintPage1 dialog


CListPrintPage1::CListPrintPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CListPrintPage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListPrintPage1)
	csFooter = _T("");
	csHead = _T("");
	csPage = _T("");
	//}}AFX_DATA_INIT
	csFtHead = "";
	csFtFoot = "";
	csFtPrint = "";
	iFtHead = 0;
	iFtFoot = 0;
	iFtPrint = 0;
}


void CListPrintPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListPrintPage1)
	DDX_Control(pDX, IDC_CBSHEAD, wndCbSzHead);
	DDX_Control(pDX, IDC_CBSFOOTER, wndCbSzFooter);
	DDX_Control(pDX, IDC_CBSCORPO, wndCbSzCorpo);
	DDX_Control(pDX, IDC_CBFHEAD, wndCbHead);
	DDX_Control(pDX, IDC_CBFFOOTER, wndCbFooter);
	DDX_Control(pDX, IDC_CBFCORPO, wndCbCorpo);
	DDX_Text(pDX, IDC_EDFOOTER, csFooter);
	DDX_Text(pDX, IDC_EDHEAD, csHead);
	DDX_Text(pDX, IDC_EDPAGE, csPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListPrintPage1, CDialog)
	//{{AFX_MSG_MAP(CListPrintPage1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListPrintPage1 message handlers

void CListPrintPage1::Update()
{
	UpdateData();

	wndCbHead.GetWindowText(csFtHead);
	wndCbFooter.GetWindowText(csFtFoot);
	wndCbCorpo.GetWindowText(csFtPrint);
	CString cs;
	wndCbSzHead.GetWindowText(cs);
	iFtHead = atoi(cs);
	wndCbSzCorpo.GetWindowText(cs);
	iFtPrint = atoi(cs);
	wndCbSzFooter.GetWindowText(cs);
	iFtFoot = atoi(cs);
}

BOOL CListPrintPage1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString cs;
	int is[11] = { 6,8,9,10,11,12,14,16,18,20,22 };
	for (int t = 0; t < 11; t++)
	{
		cs.Format("%d", is[t]);
		wndCbSzHead.AddString(cs);
		wndCbSzFooter.AddString(cs);
		wndCbSzCorpo.AddString(cs);
	}
	wndCbHead.InitFonts();
	wndCbFooter.InitFonts();
	wndCbCorpo.InitFonts();

	if (csFtHead != "") 
	{
		if (wndCbHead.SelectString(-1, csFtHead)<0)
			wndCbHead.SetCurSel(0);
	}
	if (csFtFoot != "") 
	{
		if (wndCbFooter.SelectString(-1, csFtFoot)<0)
			wndCbFooter.SetCurSel(0);
	}
	if (csFtPrint != "") 
	{
		if (wndCbCorpo.SelectString(-1, csFtPrint)<0)
			wndCbCorpo.SetCurSel(0);
	}
	wndCbSzHead.AddString(cs);
	wndCbSzFooter.AddString(cs);
	wndCbSzCorpo.AddString(cs);
	cs.Format("%d", iFtHead);
	wndCbSzHead.SetWindowText(cs);
	cs.Format("%d", iFtFoot);
	wndCbSzFooter.SetWindowText(cs);
	cs.Format("%d", iFtPrint);
	wndCbSzCorpo.SetWindowText(cs);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
