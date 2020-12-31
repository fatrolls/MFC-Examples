// FilesDragDropDoc.cpp : implementation of the CFilesDragDropDoc class
//

#include "stdafx.h"
#include "FilesDragDrop.h"

#include "FilesDragDropDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropDoc

IMPLEMENT_DYNCREATE(CFilesDragDropDoc, CDocument)

BEGIN_MESSAGE_MAP(CFilesDragDropDoc, CDocument)
	//{{AFX_MSG_MAP(CFilesDragDropDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropDoc construction/destruction

CFilesDragDropDoc::CFilesDragDropDoc()
{
	// TODO: add one-time construction code here

}

CFilesDragDropDoc::~CFilesDragDropDoc()
{
}

BOOL CFilesDragDropDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropDoc serialization

void CFilesDragDropDoc::Serialize(CArchive& ar)
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
// CFilesDragDropDoc diagnostics

#ifdef _DEBUG
void CFilesDragDropDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFilesDragDropDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropDoc commands
