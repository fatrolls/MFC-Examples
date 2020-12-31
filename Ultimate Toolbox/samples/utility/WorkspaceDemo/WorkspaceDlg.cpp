// WorkspaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorkspaceDemo.h"
#include "WorkspaceDlg.h"
#include "OXWorkspaceState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDlg dialog


CWorkspaceDlg::CWorkspaceDlg(CWnd* pParent /*=NULL*/)
	: 
	CDialog(CWorkspaceDlg::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CWorkspaceDlg)
	m_sFilePath = ((CWorkspaceDemoApp*)AfxGetApp())->GetAppDir() + _T("Test.wsp");
	m_nRegistryType = 1;
	m_sRegistry = _T("Test");
	//}}AFX_DATA_INIT
	}


void CWorkspaceDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkspaceDlg)
	DDX_Text(pDX, IDC_FILE_PATH, m_sFilePath);
	DDX_Radio(pDX, IDC_REGISTRY_TYPE, m_nRegistryType);
	DDX_Text(pDX, IDC_REGISTRY, m_sRegistry);
	//}}AFX_DATA_MAP
	}


BEGIN_MESSAGE_MAP(CWorkspaceDlg, CDialog)
//{{AFX_MSG_MAP(CWorkspaceDlg)
ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
ON_BN_CLICKED(IDC_LOAD, OnLoad)
ON_BN_CLICKED(IDC_STORE, OnStore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDlg message handlers

void CWorkspaceDlg::OnBrowse() 
	{
	if (!UpdateData(TRUE))
		return;
	
	CFileDialog fileDlg(TRUE, NULL, _T("*.wsp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Workspace (*.wsp)| *.* |All Files (*.*)| *.* ||"));
	if (fileDlg.DoModal() == IDOK)
		{
		m_sFilePath = fileDlg.GetPathName();
		m_nRegistryType = 1;
		UpdateData(FALSE);
		}
	}

void CWorkspaceDlg::OnLoad() 
	{
	if (!UpdateData(TRUE))
		return;
	
	COXWorkspaceState workspaceState;
	BOOL bSuccess = FALSE;
	switch(m_nRegistryType)
		{
		case 0:
			bSuccess = workspaceState.LoadFromRegistry(m_sRegistry);
			if (!bSuccess)
				AfxMessageBox(IDS_FAILED_LOAD_REG, MB_ICONEXCLAMATION);
			break;
		case 1:
			bSuccess = workspaceState.LoadFromFile(m_sFilePath);
			if (!bSuccess)
				AfxMessageBox(IDS_FAILED_LOAD_FILE, MB_ICONEXCLAMATION);
			break;
		default:
			TRACE1("CWorkspaceDlg::OnLoad : Unexpected case in switch : %i\n", m_nRegistryType);
			ASSERT(FALSE);
			break;
		}
	
	if (bSuccess)
		// ... Close this dialog
		EndDialog(IDCANCEL);
	}


void CWorkspaceDlg::OnStore() 
	{
	if (!UpdateData(TRUE))
		return;
	
	COXWorkspaceState workspaceState;
	BOOL bSuccess = FALSE;
	switch(m_nRegistryType)
		{
		case 0:
			bSuccess = workspaceState.StoreToRegistry(m_sRegistry);
			if (!bSuccess)
				AfxMessageBox(IDS_FAILED_STORE_REG, MB_ICONEXCLAMATION);
			break;
		case 1:
			bSuccess = workspaceState.StoreToFile(m_sFilePath);
			if (!bSuccess)
				AfxMessageBox(IDS_FAILED_STORE_FILE, MB_ICONEXCLAMATION);
			break;
		default:
			TRACE1("CWorkspaceDlg::OnStore : Unexpected case in switch : %i\n", m_nRegistryType);
			ASSERT(FALSE);
			break;
		}
	
	if (bSuccess)
		// ... Close this dialog
		EndDialog(IDCANCEL);
	}

