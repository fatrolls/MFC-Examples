// MyDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "dialog2.h"
#include "MyDlgBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBar dialog


CMyDlgBar::CMyDlgBar(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlgBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyDlgBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgBar, CDialog)
	//{{AFX_MSG_MAP(CMyDlgBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBar message handlers
