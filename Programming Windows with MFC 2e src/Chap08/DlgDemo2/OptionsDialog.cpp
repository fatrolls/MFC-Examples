// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DlgDemo2.h"
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog

COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDialog)
	m_nWidth = 0;
	m_nHeight = 0;
	m_nUnits = -1;
	//}}AFX_DATA_INIT
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDialog)
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDX_Radio(pDX, IDC_INCHES, m_nUnits);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	//{{AFX_MSG_MAP(COptionsDialog)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog message handlers

void COptionsDialog::OnReset() 
{
	m_nWidth = 4;
	m_nHeight = 2;
	m_nUnits = 0;
	UpdateData (FALSE);	
}

void COptionsDialog::OnOK ()
{
	UpdateData (TRUE);

	RECTPROP rp;
	rp.nWidth = m_nWidth;
	rp.nHeight = m_nHeight;
	rp.nUnits = m_nUnits;
 
	AfxGetMainWnd ()->SendMessage (WM_USER_APPLY, 0, (LPARAM) &rp);
}

void COptionsDialog::OnCancel ()
{
	DestroyWindow ();
}

void COptionsDialog::PostNcDestroy () 
{
	CDialog::PostNcDestroy ();
    AfxGetMainWnd ()->SendMessage (WM_USER_DIALOG_DESTROYED, 0, 0);
    delete this;
}
