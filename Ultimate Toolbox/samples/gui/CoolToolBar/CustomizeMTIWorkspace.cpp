// CustomizeMTIWorkspace.cpp : implementation file
//

#include "stdafx.h"
#include "multipad.h"
#include "CustomizeMTIWorkspace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeMTIWorkspace dialog


#define STYLESCOUNT				10

static DWORD arrStyles[STYLESCOUNT]={ 1,2,16,32,64,128,256,512,
									  1024,2048 };


CCustomizeMTIWorkspace::CCustomizeMTIWorkspace(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeMTIWorkspace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeMTIWorkspace)
	m_dwOffset = 0;
	//}}AFX_DATA_INIT
	m_dwStyle=0;
}


void CCustomizeMTIWorkspace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeMTIWorkspace)
	DDX_Control(pDX, IDC_SPIN_OFFSET, m_spinOffset);
	DDX_Control(pDX, IDC_LIST_STYLES, m_lbStyles);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_dwOffset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeMTIWorkspace, CDialog)
	//{{AFX_MSG_MAP(CCustomizeMTIWorkspace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeMTIWorkspace message handlers

BOOL CCustomizeMTIWorkspace::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_spinOffset.SetRange(0,50);

	m_lbStyles.AddString(_T("TCS_SCROLLOPPOSITE"));
	m_lbStyles.AddString(_T("TCS_BOTTOM/TCS_RIGHT"));
	m_lbStyles.AddString(_T("TCS_FORCEICONLEFT"));
	m_lbStyles.AddString(_T("TCS_FORCELABELLEFT"));
	m_lbStyles.AddString(_T("TCS_HOTTRACK"));
	m_lbStyles.AddString(_T("TCS_VERTICAL"));
	m_lbStyles.AddString(_T("TCS_BUTTONS"));
	m_lbStyles.AddString(_T("TCS_MULTILINE"));
	m_lbStyles.AddString(_T("TCS_FIXEDWIDTH"));
	m_lbStyles.AddString(_T("TCS_RAGGEDRIGHT"));

	for(int nIndex=0; nIndex<STYLESCOUNT; nIndex++)
	{
		if((m_dwStyle&arrStyles[nIndex])==arrStyles[nIndex])
			m_lbStyles.SetSel(nIndex);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomizeMTIWorkspace::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();

	int nSelItemCount=m_lbStyles.GetSelCount();
	LPINT pSelItems=new int[nSelItemCount];
	VERIFY(m_lbStyles.GetSelItems(nSelItemCount,pSelItems)!=LB_ERR);

	m_dwStyle=0;
	for(int nIndex=0; nIndex<nSelItemCount; nIndex++)
		m_dwStyle|=arrStyles[pSelItems[nIndex]];

	delete[] pSelItems;
}
