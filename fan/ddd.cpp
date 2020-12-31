// ddd.cpp : implementation file
//

#include "stdafx.h"
#include "fan.h"
#include "ddd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cddd dialog


Cddd::Cddd(CWnd* pParent /*=NULL*/)
	: CDialog(Cddd::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cddd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cddd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cddd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cddd, CDialog)
	//{{AFX_MSG_MAP(Cddd)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cddd message handlers
