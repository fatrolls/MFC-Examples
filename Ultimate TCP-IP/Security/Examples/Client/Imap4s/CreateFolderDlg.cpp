// CreateFolderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imapclient.h"
#include "CreateFolderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateFolderDlg dialog


CCreateFolderDlg::CCreateFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateFolderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateFolderDlg)
	m_strFolderName = _T("");
	//}}AFX_DATA_INIT
}


void CCreateFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateFolderDlg)
	DDX_Text(pDX, IDC_FOLDER_NAME, m_strFolderName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateFolderDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateFolderDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateFolderDlg message handlers
