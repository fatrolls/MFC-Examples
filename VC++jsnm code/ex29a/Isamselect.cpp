// IsamSelect.cpp : implementation file
//

#include "stdafx.h"
#include "ex29a.h"
#include "IsamSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIsamSelect dialog


CIsamSelect::CIsamSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CIsamSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIsamSelect)
	m_strIsam = _T("");
	m_strDirectory = _T("");
	//}}AFX_DATA_INIT
}


void CIsamSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIsamSelect)
	DDX_LBString(pDX, IDC_LIST1, m_strIsam);
	DDX_Text(pDX, IDC_EDIT1, m_strDirectory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIsamSelect, CDialog)
	//{{AFX_MSG_MAP(CIsamSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIsamSelect message handlers

BOOL CIsamSelect::OnInitDialog() 
{
	CListBox* pLB = (CListBox*) GetDlgItem(IDC_LIST1);
	pLB->AddString("dBASE III");
	pLB->AddString("dBASE IV");
	pLB->AddString("dBASE 5");
	pLB->AddString("Paradox 3.x");
	pLB->AddString("Paradox 4.x");
	pLB->AddString("Paradox 5.x");
	pLB->AddString("Btrieve");
	pLB->AddString("FoxPro 2.0");
	pLB->AddString("FoxPro 2.5");
	pLB->AddString("FoxPro 2.6");
	pLB->AddString("Excel 3.0");
	pLB->AddString("Excel 4.0");
	pLB->AddString("Excel 5.0");
	pLB->AddString("Excel 7.0");
	pLB->AddString("Text");
	CDialog::OnInitDialog();
	
	return TRUE;  // Return TRUE unless you set the focus to a control.
	              //  EXCEPTION: OCX Property Pages should return FALSE.
}
