// FileExplorerDoc.cpp : implementation of the CFileExplorerDoc class
//

#include "stdafx.h"
#include "FileExplorer.h"

#include "FileExplorerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerDoc

IMPLEMENT_DYNCREATE(CFileExplorerDoc, CDocument)

BEGIN_MESSAGE_MAP(CFileExplorerDoc, CDocument)
	//{{AFX_MSG_MAP(CFileExplorerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerDoc construction/destruction

CFileExplorerDoc::CFileExplorerDoc()
{
	// TODO: add one-time construction code here

}

CFileExplorerDoc::~CFileExplorerDoc()
{
}

BOOL CFileExplorerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFileExplorerDoc serialization

void CFileExplorerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerDoc diagnostics

#ifdef _DEBUG
void CFileExplorerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFileExplorerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerDoc commands
