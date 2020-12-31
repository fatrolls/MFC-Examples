// ResLibDoc.cpp : implementation of the CResLibDoc class
//

#include "stdafx.h"
#include "ResFile.h"

#include "ResLibDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResLibDoc

IMPLEMENT_DYNCREATE(CResLibDoc, CDocument)

BEGIN_MESSAGE_MAP(CResLibDoc, CDocument)
	//{{AFX_MSG_MAP(CResLibDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResLibDoc construction/destruction

CResLibDoc::CResLibDoc()
	{
	}

CResLibDoc::~CResLibDoc()
	{
	}

BOOL CResLibDoc::OnNewDocument()
	{
	return FALSE;
	}

/////////////////////////////////////////////////////////////////////////////
// CResLibDoc serialization

void CResLibDoc::Serialize(CArchive& ar)
	{
	UNREFERENCED_PARAMETER(ar);
	}

/////////////////////////////////////////////////////////////////////////////
// CResLibDoc diagnostics

#ifdef _DEBUG
void CResLibDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CResLibDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResLibDoc commands

BOOL CResLibDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	if (!m_ResLib.Open(lpszPathName))
		{
		AfxMessageBox(_T("Cannot open the specified file."));
		return FALSE;
		}

	if (!m_ResLib.EnumResources(&m_sTypes, &m_sNames, &m_nLangs))
		{
		AfxMessageBox(_T("Cannot enumerate resources."));
		return FALSE;
		}

	return TRUE;
}

void CResLibDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsModified());
}

BOOL CResLibDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	UNREFERENCED_PARAMETER(lpszPathName);
	if (m_ResLib.Commit())
		{
		SetModifiedFlag(FALSE);
		return TRUE;
		}

	return FALSE;
}
