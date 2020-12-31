// WorkspaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dibmanager.h"
#include "WorkspaceDlg.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDlg dialog


CWorkspaceDlg::CWorkspaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkspaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorkspaceDlg)
	m_bLoadOnEnter = FALSE;
	m_bSaveOnExit = FALSE;
	//}}AFX_DATA_INIT
}


void CWorkspaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkspaceDlg)
	DDX_Check(pDX, IDC_CHECK_LOAD_ON_ENTER, m_bLoadOnEnter);
	DDX_Check(pDX, IDC_CHECK_SAVE_ON_EXIT, m_bSaveOnExit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorkspaceDlg, CDialog)
	//{{AFX_MSG_MAP(CWorkspaceDlg)
	ON_BN_CLICKED(IDC_SAVE_WORKSPACE, OnSaveWorkspace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDlg message handlers

void CWorkspaceDlg::OnSaveWorkspace() 
{
	// TODO: Add your control notification handler code here

	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	((CMainFrame*)pApp->m_pMainWnd)->SaveWorkspace();
}
