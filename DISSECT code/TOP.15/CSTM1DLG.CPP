// cstm1dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Top Studio.h"
#include "cstm1dlg.h"
#include "Top Studioaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog


CCustom1Dlg::CCustom1Dlg()
	: CAppWizStepDlg(CCustom1Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom1Dlg)
	m_szAuthor = _T("");
	m_szComment = _T("");
	//}}AFX_DATA_INIT
}


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom1Dlg)
	DDX_Text(pDX, IDC_EDIT_AUTHOR, m_szAuthor);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_szComment);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom1Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	if( m_szAuthor.IsEmpty() == FALSE )
		TopStudioaw.m_Dictionary["PROJ_AUTHOR"] = m_szAuthor;
	else
	    TopStudioaw.m_Dictionary["PROJ_AUTHOR"] = "";

	if( m_szComment.IsEmpty() == FALSE )
		TopStudioaw.m_Dictionary["PROJ_COMMENT"] = m_szComment;
	else
		TopStudioaw.m_Dictionary["PROJ_COMMENT"] = "";

	CTime date = CTime::GetCurrentTime();
	CString szDate = date.Format( "%A, %B %d, %Y" );
	TopStudioaw.m_Dictionary["PROJ_DATE"] = szDate;

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg message handlers
