// DlgAttachments.cpp : implementation file
//

#include "stdafx.h"
#include "ZapMail.h"
#include "DlgAttachments.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAttachments dialog


CDlgAttachments::CDlgAttachments(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAttachments::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAttachments)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAttachments::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAttachments)
	DDX_Control(pDX, IDC_LIST_FILES, m_ctlFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAttachments, CDialog)
	//{{AFX_MSG_MAP(CDlgAttachments)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAttachments message handlers

void CDlgAttachments::OnOK() 
{
	// TODO: Add extra validation here

	// Fill the string array
	CString s;
	m_Files.RemoveAll();
	for( int lp = 0; lp < m_ctlFiles.GetCount(); lp++ )
	{
		m_ctlFiles.GetText( lp, s );
		m_Files.Add( s );
	}
	
	CDialog::OnOK();
}

BOOL CDlgAttachments::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// Fill the list box
	for( int lp = 0; lp <= m_Files.GetUpperBound(); lp++ )
	{
		m_ctlFiles.AddString( (LPCTSTR)m_Files[ lp ] );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAttachments::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg( TRUE, NULL, NULL, OFN_PATHMUSTEXIST, NULL, this );
	dlg.m_ofn.lpstrTitle = _T( "Attach File" );
	if( dlg.DoModal() == IDOK )
	{
		m_ctlFiles.AddString( dlg.GetPathName() );
	}
}

void CDlgAttachments::OnButtonRemove() 
{
	// TODO: Add your control notification handler code here
	int nItem;
	
	nItem = m_ctlFiles.GetCurSel();
	if( nItem == LB_ERR )
		return;
	m_ctlFiles.DeleteString( nItem );
}
