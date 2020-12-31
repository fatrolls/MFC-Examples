// CmdUIDialog.cpp : implementation file
//

#include "stdafx.h"
#include "delme.h"
#include "CmdUIDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmdUIDialog dialog


CCmdUIDialog::CCmdUIDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
	: CDialog(lpszTemplateName, pParentWnd)
{
}

CCmdUIDialog::CCmdUIDialog(UINT nIDTemplate, CWnd* pParentWnd)
	: CDialog(nIDTemplate, pParentWnd)
{
}

CCmdUIDialog::CCmdUIDialog()
{
}


BOOL CCmdUIDialog::ContinueModal()
{
	// Iterate all child windows and instruct to update themselves
	CWnd* pWndChild=GetWindow(GW_CHILD);
	int iIndex=0;
	while (NULL!=pWndChild)
	{

		CCmdUI state;
		state.m_nID=::GetWindowLong(*pWndChild, GWL_ID);
		state.m_nIndex=iIndex++;
		state.m_pOther=pWndChild;

		// ***CCmdUI::DoUpdate is undocumented MFC***
		state.DoUpdate(this, FALSE);

		pWndChild=pWndChild->GetWindow(GW_HWNDNEXT);
	}

	// Must call the base class
	return CDialog::ContinueModal();
}

BEGIN_MESSAGE_MAP(CCmdUIDialog, CDialog)
	//{{AFX_MSG_MAP(CCmdUIDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdUIDialog message handlers
