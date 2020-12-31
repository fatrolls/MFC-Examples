// GLTESTDoc.cpp : implementation of the CGLTESTDoc class
//

#include "stdafx.h"
#include "GLTEST.h"

#include "GLTESTDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLTESTDoc

IMPLEMENT_DYNCREATE(CGLTESTDoc, CDocument)

BEGIN_MESSAGE_MAP(CGLTESTDoc, CDocument)
	//{{AFX_MSG_MAP(CGLTESTDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLTESTDoc construction/destruction

CGLTESTDoc::CGLTESTDoc()
{
	// TODO: add one-time construction code here

}

CGLTESTDoc::~CGLTESTDoc()
{
}

BOOL CGLTESTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGLTESTDoc serialization

void CGLTESTDoc::Serialize(CArchive& ar)
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
// CGLTESTDoc diagnostics

#ifdef _DEBUG
void CGLTESTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGLTESTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLTESTDoc commands
