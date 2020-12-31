// PagerSizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "PagerSizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPagerSizeDlg dialog


CPagerSizeDlg::CPagerSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPagerSizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPagerSizeDlg)
	iBottom = 0;
	iLeft = 0;
	iRight = 0;
	iTop = 0;
	csPageName = _T("");
	//}}AFX_DATA_INIT
}


void CPagerSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPagerSizeDlg)
	DDX_Text(pDX, IDC_ED_BOTTOM, iBottom);
	DDX_Text(pDX, IDC_ED_LEFT, iLeft);
	DDX_Text(pDX, IDC_ED_RIGHT, iRight);
	DDX_Text(pDX, IDC_ED_TOP, iTop);
	DDX_Text(pDX, IDC_EDIT1, csPageName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPagerSizeDlg, CDialog)
	//{{AFX_MSG_MAP(CPagerSizeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPagerSizeDlg message handlers
