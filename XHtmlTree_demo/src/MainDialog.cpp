// MainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MainDialog.h"
#include "XHtmlTreeTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDialog dialog

BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
	//{{AFX_MSG_MAP(CMainDialog)
	ON_BN_CLICKED(IDC_START, OnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDialog)
	m_nInput = 0;
	//}}AFX_DATA_INIT
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDialog)
	DDX_Radio(pDX, IDC_IN_TEXT_ALL, m_nInput);
	//}}AFX_DATA_MAP
}

///////////////////////////////////////////////////////////////////////////////
// CMainDialog message handlers

void CMainDialog::OnStart() 
{
	UpdateData(TRUE);
	CWaitCursor wait;
	CXHtmlTreeTestDlg dlg(this, m_nInput);
	dlg.DoModal();
}
