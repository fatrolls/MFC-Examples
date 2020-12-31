// tablesel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "tablesel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableSelect dialog


CTableSelect::CTableSelect(CDaoDatabase* pDatabase, 
	CWnd* pParent /*=NULL*/)
	: CDialog(CTableSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableSelect)
	m_strSelection = "";
	//}}AFX_DATA_INIT
	m_pDatabase = pDatabase;
}

void CTableSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableSelect)
	DDX_LBString(pDX, IDC_LIST1, m_strSelection);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTableSelect, CDialog)
	//{{AFX_MSG_MAP(CTableSelect)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTableSelect message handlers

BOOL CTableSelect::OnInitDialog()
{
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_LIST1);
    int nTables = m_pDatabase->GetTableDefCount();
    TRACE("CTableSelect::OnInitDialog, nTables = %d\n", nTables);
    CDaoTableDefInfo tdi;
    for (int n = 0; n < nTables; n++) {
      m_pDatabase->GetTableDefInfo(n, tdi);
      TRACE("table name = %s\n", (const char*) tdi.m_strName);
      if (tdi.m_strName.Left(4) != "MSys") {
        pLB->AddString(tdi.m_strName);
      }
    }
    return CDialog::OnInitDialog();
}

void CTableSelect::OnDblclkList1()
{
	OnOK();  // Double-click on listbox item exits dialog
}
