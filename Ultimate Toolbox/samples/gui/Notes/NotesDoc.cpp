// NotesDoc.cpp : implementation of the CNotesDoc class
//

#include "stdafx.h"
#include "Notes.h"

#include "NotesDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotesDoc

IMPLEMENT_DYNCREATE(CNotesDoc, CDocument)

BEGIN_MESSAGE_MAP(CNotesDoc, CDocument)
	//{{AFX_MSG_MAP(CNotesDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotesDoc construction/destruction

CNotesDoc::CNotesDoc()
{
	// TODO: add one-time construction code here

}

CNotesDoc::~CNotesDoc()
{
}

BOOL CNotesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNotesDoc serialization

void CNotesDoc::Serialize(CArchive& ar)
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
// CNotesDoc diagnostics

#ifdef _DEBUG
void CNotesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNotesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNotesDoc commands
