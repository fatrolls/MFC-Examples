// AddrDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex32b.h"
#include "AddrDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddrDialog dialog


CAddrDialog::CAddrDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAddrDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddrDialog)
	m_strFile = _T("");
	m_strServerName = _T("");
	//}}AFX_DATA_INIT
}


void CAddrDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddrDialog)
	DDX_Text(pDX, IDC_FILE, m_strFile);
	DDX_Text(pDX, IDC_SERVERNAME, m_strServerName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddrDialog, CDialog)
	//{{AFX_MSG_MAP(CAddrDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddrDialog message handlers
