#include "stdafx.h"
#include "DDESrv.h"
#include "Advise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAdviseDialog::CAdviseDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAdviseDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdviseDialog)
	m_szText = _T("");
	//}}AFX_DATA_INIT
}


void CAdviseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdviseDialog)
	DDX_Text(pDX, IDC_EDIT, m_szText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAdviseDialog, CDialog)
	//{{AFX_MSG_MAP(CAdviseDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
