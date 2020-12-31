// Ex07aDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex07a.h"
#include "Ex07aDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx07aDialog dialog


CEx07aDialog::CEx07aDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEx07aDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEx07aDialog)
	m_strEdit1 = _T("");
	//}}AFX_DATA_INIT
	m_pView = NULL;
}

CEx07aDialog::CEx07aDialog(CView* pView) // modeless constructor
{
	m_pView = pView;
}

BOOL CEx07aDialog::Create()
{
	return CDialog::Create(CEx07aDialog::IDD);
}


void CEx07aDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx07aDialog)
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEx07aDialog, CDialog)
	//{{AFX_MSG_MAP(CEx07aDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx07aDialog message handlers

void CEx07aDialog::OnCancel()  // not really a message handler
{
	if (m_pView != NULL) {
		// modeless case -- do not call base class OnCancel
		m_pView->PostMessage(WM_GOODBYE, IDCANCEL);
	}
	else {
		CDialog::OnCancel(); // modal case
	}
}

void CEx07aDialog::OnOK()      // not really a message handler
{
	if (m_pView != NULL) {
		// modeless case -- do not call base class OnOK
		UpdateData(TRUE);
		m_pView->PostMessage(WM_GOODBYE, IDOK);
	}
	else {
		CDialog::OnOK(); // modal case
	}
}
