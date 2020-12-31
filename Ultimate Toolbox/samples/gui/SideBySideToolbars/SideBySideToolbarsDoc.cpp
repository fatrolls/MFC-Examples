// SideBySideToolbarsDoc.cpp : implementation of the CSideBySideToolbarsDoc class
//

#include "stdafx.h"
#include "SideBySideToolbars.h"

#include "SideBySideToolbarsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsDoc

IMPLEMENT_DYNCREATE(CSideBySideToolbarsDoc, CDocument)

BEGIN_MESSAGE_MAP(CSideBySideToolbarsDoc, CDocument)
	//{{AFX_MSG_MAP(CSideBySideToolbarsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsDoc construction/destruction

CSideBySideToolbarsDoc::CSideBySideToolbarsDoc()
{
	// TODO: add one-time construction code here

}

CSideBySideToolbarsDoc::~CSideBySideToolbarsDoc()
{
}

BOOL CSideBySideToolbarsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsDoc serialization

void CSideBySideToolbarsDoc::Serialize(CArchive& ar)
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
// CSideBySideToolbarsDoc diagnostics

#ifdef _DEBUG
void CSideBySideToolbarsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSideBySideToolbarsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsDoc commands
