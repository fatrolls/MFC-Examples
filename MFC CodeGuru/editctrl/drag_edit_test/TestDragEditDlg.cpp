// TestDragEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DragEdit.h"
#include "TestDragEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDragEditDlg dialog


CTestDragEditDlg::CTestDragEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDragEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDragEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestDragEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDragEditDlg)
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDragEditDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDragEditDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDragEditDlg message handlers

BOOL CTestDragEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    //You need to initiate CDragEdit first 
	m_edit1.Init();
    m_edit2.Init();

	m_edit1.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	               // EXCEPTION: OCX Property Pages should return FALSE
}
