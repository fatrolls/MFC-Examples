// FindDialog.cpp : implementation file
//

#include "stdafx.h"
#include "RegExpression.h"
#include "FindDialog.h"
#include "MainFrm.h"
#include "OXRegExpression.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindDialog dialog


CFindDialog::CFindDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDialog)
	m_bFocus = FALSE;
	//}}AFX_DATA_INIT
	m_cmbHistory.SetAutoPersistent(AfxGetAppName());
}


void CFindDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDialog)
	DDX_Control(pDX, IDC_LIST_RESULT, m_lstResult);
	DDX_Control(pDX, IDC_COMBO_HISTORY, m_cmbHistory);
	DDX_Check(pDX, IDC_CHECK_FOCUS, m_bFocus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDialog, CDialog)
	//{{AFX_MSG_MAP(CFindDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_FIND_BUTTON, OnFindButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RESULT, OnItemchangedListResult)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RESULT, OnClickListResult)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindDialog message handlers

BOOL CFindDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ModifyStyleEx(0,WS_EX_TOPMOST);
	ASSERT(::IsWindow(m_lstResult.m_hWnd));
	RECT rct;
	m_lstResult.GetClientRect(&rct);

	m_lstResult.InsertColumn(0,_T("Found"),LVCFMT_LEFT,
		rct.right-rct.left-80);
	m_lstResult.InsertColumn(1,_T("Start"),LVCFMT_LEFT,
		40);
	m_lstResult.InsertColumn(2,_T("Length"),LVCFMT_LEFT,
		40);
	m_lstResult.SetExtendedStyle(m_lstResult.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_reg.m_pParent=this;
	m_cmbHistory.RestoreContents(AfxGetAppName());
	if (!m_cmbHistory.GetCount())
	{
		m_cmbHistory.AddNewItem(_T("(re).*\\0s+ion"));
		m_cmbHistory.AddNewItem(_T("^C.{0,}s{2}"));
		m_cmbHistory.AddNewItem(_T("al\\b"));
		m_cmbHistory.SetWindowText(_T("(re).*\\0s+ion"));
	}
	m_cmbHistory.SetFocus();
	CMainFrame* pFrame;
	pFrame=(CMainFrame*) AfxGetMainWnd();
	ASSERT(pFrame);
	m_pView=(CEditView*) pFrame->GetActiveView();
	ASSERT(m_pView);
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindDialog::OnOK() 
{
	UpdateData(TRUE);
	if (m_cmbHistory.GetWindowTextLength())
		m_cmbHistory.AddNewItem();
	CDialog::OnOK();
}

LRESULT CFindDialog::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	UNUSED(wParam);
	ASSERT(wParam == MSGF_DIALOGBOX);
	BOOL bContinueIdle = TRUE;

	// Update the edit list
	m_cmbHistory.OnIdle();
	return bContinueIdle;
}


void CFindDialog::OnClose() 
{

	CDialog::OnClose();
}

void CFindDialog::OnFindButton() 
{

	TCHAR szBuffer[_MAX_PATH];
	m_nStartSearch=0;
	SetWindowText(_T("0 items found"));
	CString sText;

	m_lstResult.DeleteAllItems();


	m_pView->GetWindowText(sText);
	if (sText.IsEmpty())
		return;

	CString sRule;
	m_cmbHistory.GetWindowText(sRule);
	if (!m_reg.LoadRule(sRule))
	{
		CString sError;
		m_reg.TranslateError(m_reg.GetError(),sError);
		AfxMessageBox(sError);
		return;
	}
	int nEnd;
	m_pView->GetEditCtrl().GetSel(m_nStartSearch, nEnd); 
	sText=sText.Right(sText.GetLength()-m_nStartSearch);
	m_reg.Match(sText);
	if (!m_lstResult.GetItemCount() && m_nStartSearch)
		wsprintf(szBuffer, _T("%d items found - start search from the begining"),m_lstResult.GetItemCount());
	else
		wsprintf(szBuffer, _T("%d items found"),m_lstResult.GetItemCount());
	SetWindowText(szBuffer);
	UpdateData(TRUE);
	if (m_bFocus)
		m_pView->SetFocus();

}




void CFindDialog::OnItemchangedListResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pNMListView->uNewState & LVIS_FOCUSED)
	{
		int nStart, nLength;
		CString sText=m_lstResult.GetItemText(pNMListView->iItem,1);

		nStart=_ttoi((LPCTSTR) sText);
		sText=m_lstResult.GetItemText(pNMListView->iItem,2);

		nLength=_ttoi((LPCTSTR) sText);
		m_pView->GetEditCtrl().SetSel(nStart, nStart+nLength);
		UpdateData(TRUE);
		if (m_bFocus)
			m_pView->SetFocus();


	}

	*pResult = 0;
}



void CFindDialog::OnClickListResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UNREFERENCED_PARAMETER(pNMHDR);
	UpdateData(TRUE);
	if (m_bFocus)
		m_pView->SetFocus();
	
	*pResult = 0;
}
