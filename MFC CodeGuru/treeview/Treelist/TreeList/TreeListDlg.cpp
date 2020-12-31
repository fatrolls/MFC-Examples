// TreeListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TreeList.h"
#include "TreeListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeListDlg dialog

CTreeListDlg::CTreeListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeListDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTreeListDlg, CDialog)
	//{{AFX_MSG_MAP(CTreeListDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListDlg message handlers

BOOL CTreeListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndTreeList.SubclassDlgItem(IDC_TREE_LIST, this);
	m_cImageList.Create(IDB_TREE_LIST, 16, 10, RGB(192, 255, 192));
	m_wndTreeList.m_tree.SetImageList(&m_cImageList, TVSIL_NORMAL);

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// add items to the treelist
	{
		CNewTreeListCtrl *pTree = &m_wndTreeList.m_tree;

		pTree->InsertColumn(0, "Column A", LVCFMT_LEFT, 150);
		pTree->InsertColumn(1, "Column B", LVCFMT_LEFT, 150);
		pTree->InsertColumn(2, "Column C", LVCFMT_LEFT, 150);

		CString m_str;
		for(int i=1;i<=10;i++)
		{
			m_str.Format("Parent Item %d", i);
			HTREEITEM hItem = pTree->InsertItem(m_str, 0, 0);
			for(int j=1;j<=5;j++)
			{
				m_str.Format("Child Item %d", j);
				HTREEITEM hChild = pTree->InsertItem(m_str, 1, 1, hItem);
				pTree->SetItemColor(hChild, RGB((j*i)*13, (j*i)*6, (j*i)*9));
				pTree->SetItemText(hChild, 1, "Data for column 1");
				pTree->SetItemText(hChild, 2, "Data for column 2");
			}
		}

		pTree->SetItemBold(pTree->GetRootItem());
		pTree->SetItemColor(pTree->GetRootItem(), RGB(255, 0, 0));

	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTreeListDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CTreeListDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
