#include "stdafx.h"
#include "DB.h"
#include "MLDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMLDialog::CMLDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMLDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMLDialog)
	//}}AFX_DATA_INIT
	m_pParent=pParent;
}

void CMLDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMLDialog)
	//}}AFX_DATA_MAP
}

void CMLDialog::DoModeless()
{
	if(GetSafeHwnd() == NULL)
	{
		Create(IDD, m_pParent);
		ShowWindow(SW_SHOW);
		CenterWindow();
	}
	else
	{
		if(IsWindowVisible() == FALSE)
		{
			ShowWindow(SW_SHOW);
		}
	}
}

BEGIN_MESSAGE_MAP(CMLDialog, CDialog)
	//{{AFX_MSG_MAP(CMLDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
