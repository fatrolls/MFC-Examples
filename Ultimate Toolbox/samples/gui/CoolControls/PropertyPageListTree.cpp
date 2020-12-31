// PropertyPageListTree.cpp : implementation file
//

#include "stdafx.h"
#include "CoolControls.h"
#include "PropertyPageListTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageListTree property page

IMPLEMENT_DYNCREATE(CPropertyPageListTree, CPropertyPage)

CPropertyPageListTree::CPropertyPageListTree() : CPropertyPage(CPropertyPageListTree::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPageListTree)
	m_bDisable = FALSE;
	//}}AFX_DATA_INIT
}

CPropertyPageListTree::~CPropertyPageListTree()
{
}

void CPropertyPageListTree::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageListTree)
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Control(pDX, IDC_LISTCTRL, m_list);
	DDX_Control(pDX, IDC_LISTBOX, m_listbox);
	DDX_Control(pDX, IDC_CHECK_DISABLE_ALL, m_btnDisable);
	DDX_Check(pDX, IDC_CHECK_DISABLE_ALL, m_bDisable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageListTree, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageListTree)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_ALL, OnCheckDisableAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageListTree message handlers

void CPropertyPageListTree::OnCheckDisableAll() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();

	CWnd* pChildWnd=GetWindow(GW_CHILD);
	while(pChildWnd!=NULL)
	{
		if(pChildWnd!=&m_btnDisable)
			pChildWnd->EnableWindow(!m_bDisable);
		pChildWnd=pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}

BOOL CPropertyPageListTree::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);

	VERIFY(m_il.Create(IDB_IL_SMALL,16,1,RGB(128,128,128)));

	// populate list control
	m_list.SetImageList(&m_il,LVSIL_SMALL);

	CString sColumnText;
	CString sItemText;
	for (int nColumn=0; nColumn<8; nColumn++)
	{
		sColumnText.Format(_T("Column %d"),nColumn+1);
		m_list.InsertColumn(nColumn,sColumnText,LVCFMT_LEFT,100);

		for(int nRow=0; nRow<50; nRow++)
		{
			sItemText.Format(_T("Item %d in column %d"),nRow+1,nColumn+1);
			if(nColumn==0)
				m_list.InsertItem(nRow,sItemText,0);
			else
				m_list.SetItem(nRow,nColumn,LVIF_TEXT,sItemText,NULL,NULL,NULL,NULL);
		}
	}

	m_list.SetTooltipText("This is a cool edit control");

	/////////////////////////////////


	// populate tree control
	m_tree.SetImageList(&m_il,TVSIL_NORMAL);

	CString sParentText;
	int nIndex=0;
	for (nIndex=0; nIndex<15; nIndex++)
	{
		sParentText.Format(_T("Tree item %d"),nIndex+1);
		HTREEITEM hParent=m_tree.InsertItem(sParentText,0,0);
		ASSERT(hParent!=NULL);

		for(int nSubItem=0; nSubItem<5; nSubItem++)
		{
			sItemText.Format(_T("SubItem %d of parent item %d"),nSubItem+1,nIndex+1);
			m_tree.InsertItem(sItemText,0,0,hParent);
		}
	}
	/////////////////////////////////

	
	// populate listbox control
	for (nIndex=0; nIndex<100; nIndex++)
	{
		sItemText.Format(_T("Listbox item %d"),nIndex+1);
		m_listbox.AddString(sItemText);
	}
	/////////////////////////////////

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

