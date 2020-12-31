// maxvirtd.cpp : implementation file
//

#include "stdafx.h"
#include "Roll32.h"
#include "maxvirtd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaxVirtDialog dialog


CMaxVirtDialog::CMaxVirtDialog(CWnd* pParent /*=NULL*/)
	: COXRollup(CMaxVirtDialog::IDD, pParent)
{
	SetScrollSteps(100);  // looks pretty

	//{{AFX_DATA_INIT(CMaxVirtDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMaxVirtDialog::DoDataExchange(CDataExchange* pDX)
{
	COXRollup::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaxVirtDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaxVirtDialog, COXRollup)
	//{{AFX_MSG_MAP(CMaxVirtDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMaxVirtDialog message handlers

void CMaxVirtDialog::OnCloseRollup()
{
	ShowWindow(SW_HIDE);	// first we hide
	UnArrange();			// second get out of arrange orderings
	DestroyWindow();		// delete will be done in PostNcDestroy
}

void CMaxVirtDialog::GetTitleBarRect(CRect &rcTBarRect)
{
	GetClientRect(rcTBarRect);
	rcTBarRect.bottom = 20;	
}

LPCTSTR CMaxVirtDialog::GetTitleBarBitmap()
{
	// our slightly enlarged bitmap
	return _T("MAXVIRT");
}

void CMaxVirtDialog::PostNcDestroy()
{
	// Why do I have to place the call to delete this here? someone might ask
	// Answer: if we don´t close the dialog manually (close menu,..), it won´t be 
	// deleted. Placing it to OnDestroy isn´t practical (dbg messages from mfc)
	// see cframewnd or others, they do the same
	COXRollup::PostNcDestroy();
	delete this;
}