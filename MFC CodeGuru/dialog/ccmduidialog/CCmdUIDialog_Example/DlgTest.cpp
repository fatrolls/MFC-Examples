// DlgTest.cpp : implementation file
//

#include "stdafx.h"
#include "delme.h"
#include "DlgTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTest dialog


BEGIN_MESSAGE_MAP(CDlgTest, CCmdUIDialog)
	//{{AFX_MSG_MAP(CDlgTest)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_EDIT, OnUpdateButtonEdit)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_BROWSE, OnUpdateButtonBrowse)
	// Many controls using the same update handler
	ON_UPDATE_COMMAND_UI(IDC_CHECK_EXPORT_NAMES, OnUpdateCheckExport)
	ON_UPDATE_COMMAND_UI(IDC_CHECK_EXPORT_NUMBERS, OnUpdateCheckExport)
	ON_UPDATE_COMMAND_UI(IDC_CHECK_EXPORT_RATES, OnUpdateCheckExport)

	ON_UPDATE_COMMAND_UI(IDC_CHECK_CLONE, OnUpdateCheckClone)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTest message handlers

void CDlgTest::OnUpdateButtonEdit(CCmdUI* pCmdUI)
{
	// Updates the IDC_BUTTON_EDIT button on the dialog.
	// Only enabled when the IDC_EDIT1 edit control contains text
	CWnd *pWnd=GetDlgItem(IDC_EDIT1);
	pCmdUI->Enable(pWnd->GetWindowTextLength()>0);
}

void CDlgTest::OnUpdateButtonBrowse(CCmdUI* pCmdUI)
{
	// Updates the IDC_BUTTON_BROWSE button on the dialog
	// Only enabled when the IDC_CHECK_EXPORT_NUMBERS button is
	// checked.

	// CCmdUI does not have hide member, so we use the
	// window passed in pCmdUI. This is the window of the dialog control
	// being updated
	CButton *pButton=(CButton *)GetDlgItem(IDC_CHECK_EXPORT_NUMBERS);
	BOOL bShow = pButton->GetCheck()==1;
	pCmdUI->m_pOther->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
}

void CDlgTest::OnUpdateCheckExport(CCmdUI* pCmdUI)
{
	// Updates the following buttons on the dialog:
	//	IDC_CHECK_EXPORT_NAMES
	//	IDC_CHECK_EXPORT_NUMBERS
	//	IDC_CHECK_EXPORT_NUMBERS
	// Enabled only when the IDC_CHECK_EXPORT button is checked
	CButton *pButton=(CButton *)GetDlgItem(IDC_CHECK_EXPORT);
	BOOL bShow = pButton->GetCheck()==1;
	pCmdUI->m_pOther->EnableWindow(bShow);
}

void CDlgTest::OnUpdateCheckClone(CCmdUI* pCmdUI)
{
	// Updates the IDC_CHECK_CLONE button on the dialog
	// Mimics the state of the IDC_CHECK_SELECTALL button
	CButton *pButton=(CButton *)GetDlgItem(IDC_CHECK_SELECTALL);
	pCmdUI->SetCheck(pButton->GetCheck());
}


CDlgTest::CDlgTest(CWnd* pParent /*=NULL*/)
	: CCmdUIDialog(CDlgTest::IDD, pParent),
	m_bDoIt(FALSE)
{
	//{{AFX_DATA_INIT(CDlgTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CCmdUIDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTest)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


