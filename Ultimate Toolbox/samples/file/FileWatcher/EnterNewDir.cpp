// EnterNewDir.cpp : implementation file
//

#include "stdafx.h"
#include "FileWatcher.h"
#include "EnterNewDir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnterNewDir dialog


CEnterNewDir::CEnterNewDir(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterNewDir::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnterNewDir)
	m_bChangeAttributes = FALSE;
	m_bChangeCreation = FALSE;
	m_bChangeDirName = FALSE;
	m_bChangeFileName = FALSE;
	m_bChangeLastAccess = FALSE;
	m_bChangeLastWrite = FALSE;
	m_bChangeSecurity = FALSE;
	m_bChangeSize = FALSE;
	m_sDir = _T("");
	m_bSubTree = FALSE;
	//}}AFX_DATA_INIT
}


void CEnterNewDir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterNewDir)
	DDX_Check(pDX, IDC_CHANGE_ATTRIBUTES, m_bChangeAttributes);
	DDX_Check(pDX, IDC_CHANGE_CREATION, m_bChangeCreation);
	DDX_Check(pDX, IDC_CHANGE_DIR_NAME, m_bChangeDirName);
	DDX_Check(pDX, IDC_CHANGE_FILE_NAME, m_bChangeFileName);
	DDX_Check(pDX, IDC_CHANGE_LAST_ACCESS, m_bChangeLastAccess);
	DDX_Check(pDX, IDC_CHANGE_LAST_WRITE, m_bChangeLastWrite);
	DDX_Check(pDX, IDC_CHANGE_SECURITY, m_bChangeSecurity);
	DDX_Check(pDX, IDC_CHANGE_SIZE, m_bChangeSize);
	DDX_Text(pDX, IDC_DIR, m_sDir);
	DDX_Check(pDX, IDC_WATCH_SUB_TREE, m_bSubTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnterNewDir, CDialog)
	//{{AFX_MSG_MAP(CEnterNewDir)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnterNewDir message handlers
