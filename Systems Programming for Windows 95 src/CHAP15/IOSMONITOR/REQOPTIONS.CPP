// ReqOptions.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "ReqOptions.h"
#include "RequestLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReqOptions dialog


CReqOptions::CReqOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CReqOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReqOptions)
	m_numlog = 0;
	//}}AFX_DATA_INIT
}


void CReqOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReqOptions)
	DDX_Control(pDX, IDC_DEVLIST, m_ctlList);
	DDX_Control(pDX, IDB_NONE, m_ctlNone);
	DDX_Control(pDX, IDB_ALL, m_ctlAll);
	DDX_Text(pDX, IDC_NUMLOG, m_numlog);
	DDV_MinMaxInt(pDX, m_numlog, 1, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReqOptions, CDialog)
	//{{AFX_MSG_MAP(CReqOptions)
	ON_BN_CLICKED(IDB_ALL, OnAll)
	ON_BN_CLICKED(IDB_NONE, OnNone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReqOptions message handlers

BOOL CReqOptions::OnInitDialog() 
	{							// CReqOptions::OnInitDialog
	CDialog::OnInitDialog();
	CenterWindow();
	for (int i = 0; i < m_devlist.GetSize(); ++i)
		{						// populate list box
		PIOSDCB dcb = m_devlist[i];
		int index = m_ctlList.AddString(DriveName(dcb));
		m_ctlList.SetItemDataPtr(index, dcb);
		if (m_log->m_all)
			m_ctlList.SetSel(index);
		else
			for (int j = 0; j < m_log->m_devlist.GetSize(); ++j)
				if (dcb == m_log->m_devlist[j])
					{				// currently selected
					m_ctlList.SetSel(index);
					break;
					}				// currently selected
		}						// populate list box
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}							// CReqOptions::OnInitDialog

void CReqOptions::OnOK()
	{							// CReqOptions::OnOK
	CDialog::OnOK();

	int nsel = m_ctlList.GetSelCount();
	int *sel = new int[nsel];
	m_ctlList.GetSelItems(nsel, sel);
	
	m_devlist.RemoveAll();
	for (int i = 0; i < nsel; ++i)
		m_devlist.Add((PIOSDCB) m_ctlList.GetItemDataPtr(sel[i]));
	delete [] sel;
	}							// CReqOptions::OnOK

void CReqOptions::OnAll() 
{
	m_ctlList.SetSel(-1, TRUE);
}

void CReqOptions::OnNone() 
{
	m_ctlList.SetSel(-1, FALSE);	
}
