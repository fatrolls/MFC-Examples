
// DlgTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgTest.h"
#include "DlgTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlgTestDlg 对话框




CDlgTestDlg::CDlgTestDlg(CWnd* pParent /*=NULL*/)
	: CDrawDlg(CDlgTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDrawDlg::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgTestDlg, CDrawDlg)
	//ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgTestDlg 消息处理程序

BOOL CDlgTestDlg::OnInitDialog()
{
	CDrawDlg::OnInitDialog();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
