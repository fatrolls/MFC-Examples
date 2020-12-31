// FindDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "FindDialog.h"
#include "XMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindDialog dialog

BEGIN_MESSAGE_MAP(CFindDialog, CDialog)
	//{{AFX_MSG_MAP(CFindDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFindDialog::CFindDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDialog)
	m_nFindStart = 0;
	m_nFindDir = 1;
	m_strFind = _T("");
	m_bCheck = FALSE;
	//}}AFX_DATA_INIT
}

void CFindDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDialog)
	DDX_Control(pDX, IDC_FIND_EDIT, m_edtFind);
	DDX_Radio(pDX, IDC_FIND_CURRENT, m_nFindStart);
	DDX_Radio(pDX, IDC_FIND_UP, m_nFindDir);
	DDX_Text(pDX, IDC_FIND_EDIT, m_strFind);
	DDX_Check(pDX, IDC_FIND_CHECK, m_bCheck);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFindDialog message handlers

BOOL CFindDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_edtFind.SetPromptText(_T("<Enter search string>"));

	if (!m_rect.IsRectEmpty())
		MoveWindow(&m_rect);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindDialog::OnOK() 
{
	UpdateData(TRUE);
	GetWindowRect(&m_rect);
	CDialog::OnOK();
}

void CFindDialog::OnCancel() 
{
	TRACE(_T("in CFindDialog::OnCancel\n"));
	UpdateData(TRUE);
	GetWindowRect(&m_rect);
	CDialog::OnCancel();
}
