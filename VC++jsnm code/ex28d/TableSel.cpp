// tablesel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "tablesel.h"
#include "tableset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////
// CTableSelect dialog


CTableSelect::CTableSelect(CDatabase* pDatabase,
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


///////////////////////////////////////////////////////////////
// CTableSelect message handlers

BOOL CTableSelect::OnInitDialog()
{
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_LIST1);
    CTables tables(m_pDatabase);  // db passed via constructor
    tables.Open();                // closed on table's
                                  //  destruction
    while (!tables.IsEOF()) {
      TRACE("table name = %s\n", tables.m_strName);
	  
      // reject queries and system tables
      if (_stricmp(tables.m_strType, "TABLE") == 0) {
        pLB->AddString(tables.m_strName);
      }
      tables.MoveNext();
    }
    return CDialog::OnInitDialog();
}

void CTableSelect::OnDblclkList1()
{
    OnOK();  // double-click on list-box item exits dialog
}
