#include "stdafx.h"
#include "GDI.h"
#include "StyleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStyleDlg::CStyleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStyleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStyleDlg)
	m_lEsp=0;
	m_bBgdStyle=FALSE;
	//}}AFX_DATA_INIT
}


void CStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStyleDlg)
	DDX_Text(pDX, IDC_EDIT_ESP, m_lEsp);
	DDV_MinMaxLong(pDX, m_lEsp, 0, 3600);
	DDX_Check(pDX, IDC_CHECK_TRANBK, m_bBgdStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStyleDlg, CDialog)
	//{{AFX_MSG_MAP(CStyleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
