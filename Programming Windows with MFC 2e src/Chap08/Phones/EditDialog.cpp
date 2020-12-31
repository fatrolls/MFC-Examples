// EditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Phones.h"
#include "PhoneEdit.h"
#include "EditDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDialog dialog

CEditDialog::CEditDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDialog)
	m_strName = _T("");
	m_strPhone = _T("");
	//}}AFX_DATA_INIT
}

void CEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDialog)
	DDX_Control(pDX, IDOK, m_wndOK);
	DDX_Control(pDX, IDCANCEL, m_wndCancel);
	DDX_Control(pDX, IDC_PHONE, m_wndPhoneEdit);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 32);
	DDX_Text(pDX, IDC_PHONE, m_strPhone);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditDialog, CDialog)
	//{{AFX_MSG_MAP(CEditDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDialog message handlers

BOOL CEditDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_wndOK.SetIcon (AfxGetApp ()->LoadIcon (IDI_OK));
	m_wndCancel.SetIcon (AfxGetApp ()->LoadIcon (IDI_CANCEL));
	return TRUE;
}
