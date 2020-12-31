// ListColorDialog.cpp : implementation file
//

#include "stdafx.h"
#include "mylistctrl.h"
#include "ListColorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListColorDialog dialog


CListColorDialog::CListColorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CListColorDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListColorDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CListColorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListColorDialog)
	DDX_Control(pDX, IDC_LIST_COLORS, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListColorDialog, CDialog)
	//{{AFX_MSG_MAP(CListColorDialog)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_QUICKLIST_GETLISTITEMDATA, OnGetListItem) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListColorDialog message handlers

BOOL CListColorDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list.InsertColumn(0, _T("Color"), LVCFMT_CENTER, 120);
	m_list.InsertColumn(1, _T("Red"), LVCFMT_CENTER, 60);
	m_list.InsertColumn(2, _T("Green"), LVCFMT_CENTER, 60);
	m_list.InsertColumn(3, _T("Blue"), LVCFMT_CENTER, 60);

	ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	m_list.SetItemCount(256*256*256);

	m_list.SetKeyfindColumn(-1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CListColorDialog::OnGetListItem(WPARAM , LPARAM lParam)
{
	CQuickList::CListItemData* data = (CQuickList::CListItemData*) lParam;

	int item = data->GetItem();
	int subItem = data->GetSubItem();

	int c[3] = {GetRValue(item), GetGValue(item), GetBValue(item)};

#ifndef QUICKLIST_NOCOLORS
	data->m_colors.m_backColor = RGB(c[0],c[1],c[2]);
	data->m_colors.m_textColor = RGB(255-c[0],255-c[1],255-c[2]);
#endif
	
	if(subItem == 0)
	{
		data->m_text.Format(_T("%d - %d - %d"), c[0], c[1], c[2]);
	}
	else
	{
		data->m_text.Format(_T("%d"), c[subItem-1]);

		#ifndef QUICKLIST_NOCOLORS
		data->m_colors.m_backColor = RGB(0,0,0);
		#endif

		#ifndef QUICKLIST_NOPROGRESSBAR
		data->m_progressBar.m_edge = 0;
		data->m_progressBar.m_maxvalue = 255;
		data->m_progressBar.m_value = c[subItem-1];
		
		
		if(subItem == 1)
		{
			data->m_progressBar.m_fillColor = RGB(c[0],0,0);
			data->m_progressBar.m_fillTextColor = RGB(0,255,255);
		}
		else if(subItem == 2)
		{
			data->m_progressBar.m_fillColor = RGB(0, c[1],0);
			data->m_progressBar.m_fillTextColor = RGB(255,0,255);
		}
		else
		{
			data->m_progressBar.m_fillColor = RGB(0, 0, c[2]);
			data->m_progressBar.m_fillTextColor = RGB(255,255,0);
		}
		#endif

	}
	

	return 0;
}