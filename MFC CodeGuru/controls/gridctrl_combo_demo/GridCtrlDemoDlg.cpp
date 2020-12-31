// GridCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GridCtrlDemo.h"
#include "GridCtrlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoDlg dialog

CGridCtrlDemoDlg::CGridCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGridCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGridCtrlDemoDlg)
	//}}AFX_DATA_INIT
}

void CGridCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridCtrlDemoDlg)
	//}}AFX_DATA_MAP
    DDX_GridControl(pDX, IDC_GRIDCTRL, m_GridCtrl);
}

BEGIN_MESSAGE_MAP(CGridCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGridCtrlDemoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoDlg message handlers

BOOL CGridCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_GridCtrl.SetRowCount(20);
    m_GridCtrl.SetFixedRowCount(1);
    m_GridCtrl.SetColumnCount(5);
    m_GridCtrl.SetFixedColumnCount(1);

	// fill rows/cols with text
	for (int row = 0; row < m_GridCtrl.GetRowCount(); row++)
		for (int col = 0; col < m_GridCtrl.GetColumnCount(); col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			if (row < m_GridCtrl.GetFixedRowCount()) {
				Item.nFormat = DT_LEFT|DT_WORDBREAK;
				Item.szText.Format(_T("Column %d"),col);
			} else if (col < m_GridCtrl.GetFixedColumnCount()) {
				Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				Item.szText.Format(_T("Row %d"),row);
			} else {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				Item.szText.Format(_T("%d"),row*col);
			}
			m_GridCtrl.SetItem(&Item);
		}

	m_GridCtrl.AutoSize();
    
	return TRUE;  // return TRUE  unless you set the focus to a control
}

