// PrintStatus.cpp : implementation file
//

#include "stdafx.h"
#include "PrintManager.h"
#include "PrintStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool bGfxUserAbort;

/////////////////////////////////////////////////////////////////////////////
// CPrintStatus dialog

CPrintStatus::CPrintStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Create(CPrintStatus::IDD, pParent);      // modeless !
	bGfxUserAbort = false;
}


void CPrintStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintStatus)
	DDX_Control(pDX, IDC_PROGRESS1, wndProg);
	DDX_Control(pDX, IDC_ANIMATE1, wndAnima);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintStatus, CDialog)
	//{{AFX_MSG_MAP(CPrintStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintStatus message handlers

BOOL CPrintStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CenterWindow();
	wndAnima.Open(IDR_PRINT);
	wndAnima.Play(0,(UINT)-1,(UINT)-1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrintStatus::OnCancel() 
{
	bGfxUserAbort = true;	
	CDialog::OnCancel();
}
