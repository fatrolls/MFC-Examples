// DialogBitmapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DialogBitmap.h"
#include "DialogBitmapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogBitmapDlg dialog

CDialogBitmapDlg::CDialogBitmapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogBitmapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogBitmapDlg)
	//}}AFX_DATA_INIT
}

void CDialogBitmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogBitmapDlg)
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogBitmapDlg, CDialog)
	//{{AFX_MSG_MAP(CDialogBitmapDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogBitmapDlg message handlers

BOOL CDialogBitmapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Picture.SetBitmap(IDB_BITMAP1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

