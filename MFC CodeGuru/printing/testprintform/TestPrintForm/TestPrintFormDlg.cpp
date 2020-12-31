// TestPrintFormDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestPrintForm.h"
#include "TestPrintFormDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormDlg dialog


CTestPrintFormDlg::CTestPrintFormDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPrintFormDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestPrintFormDlg)
	bCheck = FALSE;
	csVal1 = _T("test value 1");
	csVal2 = _T("test value 2");
	csVal3 = _T("test value 3");
	csVal4 = _T("test value 4");
	//}}AFX_DATA_INIT

	cMultiJob.pDlg = this;
	cSingleJob.pDlg = this;
}


void CTestPrintFormDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPrintFormDlg)
	DDX_Control(pDX, IDC_LIST1, wndList);
	DDX_Check(pDX, IDC_CHECK1, bCheck);
	DDX_Text(pDX, IDC_EDIT1, csVal1);
	DDX_Text(pDX, IDC_EDIT2, csVal2);
	DDX_Text(pDX, IDC_EDIT3, csVal3);
	DDX_Text(pDX, IDC_EDIT4, csVal4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestPrintFormDlg, CDialog)
	//{{AFX_MSG_MAP(CTestPrintFormDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormDlg message handlers

BOOL CTestPrintFormDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	wndList.InsertColumn(0, "Field 1", LVCFMT_LEFT, 80);
	wndList.InsertColumn(1, "Field 2", LVCFMT_LEFT, 300);
	
	CString cs;
	for (int t = 0; t < 200; t++)
	{
		cs.Format("%d", t);
		int idx = wndList.InsertItem(t, cs);
		cs.Format("Field 2 of item %d", t);
		wndList.SetItemText(idx, 1, cs);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestPrintFormDlg::OnOK() 
{
	UpdateData();

	if (bCheck)
	{
		cMultiJob.Clear();
		cMultiJob.strTitle = "Test dialog multiitem pages";
		cMultiJob.AddPage("testform2.prx", "testpage", 1, wndList.GetItemCount());
		cMultiJob.OnFilePrint();
	}
	else
	{
		cSingleJob.Clear();
		cMultiJob.strTitle = "Test dialog singleitem page";
		cSingleJob.AddPage("testform1.prx", "testpage", 1);
		cSingleJob.OnFilePrint();
	}
}
