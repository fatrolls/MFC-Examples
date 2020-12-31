// ListPrintPage2.cpp : implementation file
//

#include "stdafx.h"
#include "PrintManager.h"
#include "ListPrintPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListPrintPage2 dialog


CListPrintPage2::CListPrintPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CListPrintPage2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListPrintPage2)
	iDown = 0;
	iDx = 0;
	iSx = 0;
	iUp = 0;
	//}}AFX_DATA_INIT
}


void CListPrintPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListPrintPage2)
	DDX_Text(pDX, IDC_ED_MMDOWN, iDown);
	DDV_MinMaxInt(pDX, iDown, 0, 300);
	DDX_Text(pDX, IDC_ED_MMDX, iDx);
	DDV_MinMaxInt(pDX, iDx, 0, 300);
	DDX_Text(pDX, IDC_ED_MMSX, iSx);
	DDV_MinMaxInt(pDX, iSx, 0, 300);
	DDX_Text(pDX, IDC_ED_MMUP, iUp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListPrintPage2, CDialog)
	//{{AFX_MSG_MAP(CListPrintPage2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListPrintPage2 message handlers

void CListPrintPage2::Update()
{
	UpdateData();
}
