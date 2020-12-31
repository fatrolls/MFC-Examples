// PickTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualList.h"
#include "PickTableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPickTableDlg dialog


CPickTableDlg::CPickTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPickTableDlg::IDD, pParent)
{
	m_TableName = _T("");
}

CPickTableDlg::CPickTableDlg(CDaoDatabase* pDB, CWnd* pParent /*=NULL*/)
	: CDialog(CPickTableDlg::IDD, pParent)
{
	m_pDB = pDB;
	m_TableName = _T("");
	//{{AFX_DATA_INIT(CPickTableDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CPickTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPickTableDlg)
	DDX_Control(pDX, IDC_LISTBOX, m_ListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPickTableDlg, CDialog)
	//{{AFX_MSG_MAP(CPickTableDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPickTableDlg message handlers


void CPickTableDlg::PopulateList() 
{
	CDaoTableDefInfo tabInfo;
	int nTableDefCount = m_pDB->GetTableDefCount();
	for (int i = 0; i < nTableDefCount; i++)
	{
		m_pDB->GetTableDefInfo(i,tabInfo);
		if (tabInfo.m_lAttributes & dbSystemObject)
			continue;
		m_ListBox.AddString(tabInfo.m_strName);
	}
	
	int count = m_ListBox.GetCount();
	if(count != LB_ERR || count != 0)
		m_ListBox.SetCurSel(0);
}



BOOL CPickTableDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	PopulateList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPickTableDlg::OnOK() 
{
	int count = m_ListBox.GetCount();
	if(count == LB_ERR || count == 0)
		EndDialog(IDCANCEL);
	m_ListBox.GetText(m_ListBox.GetCurSel(), m_TableName);
	int currSel = m_ListBox.GetCurSel();
	CDialog::OnOK();

}

void CPickTableDlg::GetTableName(CString& tableName) 
{
	tableName = m_TableName;
}
