#include "stdafx.h"
#include "GDI.h"
#include "PrnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPrnDlg::CPrnDlg(BOOL bPrintSetupOnly, DWORD dwFlags, CWnd *pParentWnd) : 
CPrintDialog(bPrintSetupOnly, dwFlags, pParentWnd)
{
	//{{AFX_DATA_INIT(CPrnDlg)
	//}}AFX_DATA_INIT
	m_pd.Flags|=PD_NOPAGENUMS;
	m_pd.Flags|=PD_NOSELECTION;
}


void CPrnDlg::DoDataExchange(CDataExchange* pDX)
{
	CPrintDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrnDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPrnDlg, CPrintDialog)
	//{{AFX_MSG_MAP(CPrnDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
