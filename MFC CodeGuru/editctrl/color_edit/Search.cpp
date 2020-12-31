// Search.cpp : implementation file
//

#include "stdafx.h"
#include "ColorEdit.h"
#include "Search.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearch dialog


CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearch)
	m_replace_string = _T("");
	m_search_string = _T("");
	//}}AFX_DATA_INIT

	m_view = NULL;
	m_pString = NULL;
}


void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearch)
	DDX_Control(pDX, IDC_SEARCH_STRING, m_search_ctrl);
	DDX_Control(pDX, IDC_REPLACE, m_replaceBtn);
	DDX_Control(pDX, IDC_FIND_NEXT, m_findBtn);
	DDX_Text(pDX, IDC_REPLACE_STRING, m_replace_string);
	DDV_MaxChars(pDX, m_replace_string, 100);
	DDX_Text(pDX, IDC_SEARCH_STRING, m_search_string);
	DDV_MaxChars(pDX, m_search_string, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearch, CDialog)
	//{{AFX_MSG_MAP(CSearch)
	ON_BN_CLICKED(IDC_FIND_NEXT, OnFindNext)
	ON_BN_CLICKED(IDC_REPLACE, OnReplace)
	ON_BN_CLICKED(IDC_REPLACE_ALL, OnReplaceAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearch message handlers

void CSearch::OnFindNext() 
{
	UpdateData(TRUE);
	if (!m_search_string.IsEmpty()) {
		long len;
		long pos = RegSearchFind(m_r, *((CStringEx*) m_pString), m_search_string, m_view->GetSearchPosition(), len);
		if (pos > 0) {
			m_view->SetSelection(pos, pos+len);
			m_view->ScrollToSelection();
		} else {
			AfxMessageBox(_T("Search string not found"));
		}
	}
}

void CSearch::OnReplace() 
{
	UpdateData(TRUE);
	if (!m_replace_string.IsEmpty()) {
		TCHAR *pReplaceStr = m_r.GetReplaceString(m_replace_string);
		m_view->ReplaceSelection(pReplaceStr);
	}
	
}

void CSearch::OnReplaceAll() 
{
	CWaitCursor cursor;

	BOOL bReplace = FALSE;
	UpdateData(TRUE);
	m_view->DisableCheckPoint();
	if (!m_search_string.IsEmpty()) {
		long len, pos;
		do {
			pos = RegSearchFind(m_r, *((CStringEx*) m_pString), m_search_string, m_view->GetSearchPosition(), len);
			if (pos > 0) {
				m_view->SetSelection(pos, pos+len);
				TCHAR *pReplaceStr = m_r.GetReplaceString(m_replace_string);
				m_view->ReplaceSelection(pReplaceStr);
				bReplace = TRUE;
			}
		} while (pos > 0);
	}
	m_view->EnableCheckPoint();
	if (bReplace) m_view->CheckPoint();
}