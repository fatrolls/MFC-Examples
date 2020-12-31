// WorkspaceTextDoc.cpp : implementation of the CWorkspaceTextDoc class
//

#include "stdafx.h"
#include "WorkspaceDemo.h"

#include "WorkspaceTextDoc.h"

#include "UTB64Bit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextDoc

IMPLEMENT_DYNCREATE(CWorkspaceTextDoc, CDocument)

BEGIN_MESSAGE_MAP(CWorkspaceTextDoc, CDocument)
	//{{AFX_MSG_MAP(CWorkspaceTextDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextDoc construction/destruction

CWorkspaceTextDoc::CWorkspaceTextDoc()
{
	// TODO: add one-time construction code here

}

CWorkspaceTextDoc::~CWorkspaceTextDoc()
{
}

BOOL CWorkspaceTextDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

BOOL CWorkspaceTextDoc::SetText(CString sText)
	{
	BOOL bModified = FALSE;
	if (sText != m_sText)
		{
		m_sText = sText;
		bModified = TRUE;
		SetModifiedFlag(TRUE);
		}

	return bModified;
	}

CString CWorkspaceTextDoc::GetText() const
	{
	return m_sText;
	}

	/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextDoc serialization

void CWorkspaceTextDoc::Serialize(CArchive& ar)
	{
	if (ar.IsStoring())
		{
		DWORD nLength = 0;

#ifdef _UNICODE
		LPSTR pszText = NULL;
		const int nMaxLength = m_sText.GetLength() + 2;
		pszText = new char[nMaxLength];
		nLength = wcstombs(pszText, m_sText, nMaxLength);
		VERIFY(nLength != (size_t)-1);
#else
		LPCSTR pszText = NULL;
		pszText = m_sText;
		nLength = m_sText.GetLength();
#endif

		ar.Write(pszText, nLength);

#ifdef _UNICODE
		delete[] pszText;
#endif
		}
	else
		{
		CFile* pFile = ar.GetFile();
		ASSERT(pFile->GetPosition() == 0);
		DWORD_PTR nFileSize = (DWORD_PTR) pFile->GetLength();

		char* pszText = new char[nFileSize + 1];
		ar.Read(pszText, (UINT)nFileSize);
		pszText[nFileSize] = '\0';
		m_sText = pszText;
		delete[] pszText;
		}
	}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextDoc diagnostics

#ifdef _DEBUG
void CWorkspaceTextDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWorkspaceTextDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextDoc commands
