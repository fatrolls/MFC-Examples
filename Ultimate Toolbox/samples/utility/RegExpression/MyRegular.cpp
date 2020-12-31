// MyRegular.cpp: implementation of the CMyRegular class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RegExpression.h"
#include "MyRegular.h"
#include "FindDialog.h"
#include "MainFrm.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyRegular::CMyRegular() 
{
m_pParent=NULL;
}

CMyRegular::~CMyRegular()
{

}

BOOL CMyRegular::OnMatch(int nStart, int nLength)
{
	if (m_pParent  && ::IsWindow(m_pParent->GetSafeHwnd())
		&& ::IsWindow(m_pParent->m_lstResult.m_hWnd))
	{

		CMainFrame* pFrame=(CMainFrame*) AfxGetMainWnd();
		ASSERT(pFrame);
		CEditView* pView=(CEditView*) pFrame->GetActiveView();
		ASSERT(pView);
		pView->GetEditCtrl().SetSel(nStart+m_pParent->m_nStartSearch,
			nLength+nStart+m_pParent->m_nStartSearch);
		TCHAR szBuffer[_MAX_PATH];
		UTBStr::itot(nStart+m_pParent->m_nStartSearch,szBuffer,_MAX_PATH,10);
		m_pParent->m_lstResult.InsertItem(
			m_pParent->m_lstResult.GetItemCount(),
			(LPCTSTR) m_sString.Mid(nStart,nLength));
		m_pParent->m_lstResult.SetItemText(
			m_pParent->m_lstResult.GetItemCount()-1,
			1,szBuffer);
		UTBStr::itot(nLength,szBuffer,_MAX_PATH,10);
		m_pParent->m_lstResult.SetItemText(
			m_pParent->m_lstResult.GetItemCount()-1,
			2,szBuffer);
	}
	return TRUE;
}

BOOL CMyRegular::Match(CString sString)
{
	m_sString=sString;
	return COXRegExpression::Match(sString);
}
