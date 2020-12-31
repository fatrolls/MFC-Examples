// TestGLDoc.cpp : implementation of the CTestGLDoc class
//

#include "stdafx.h"
#include "TestGL.h"

#include "TestGLDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestGLDoc

IMPLEMENT_DYNCREATE(CTestGLDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestGLDoc, CDocument)
	//{{AFX_MSG_MAP(CTestGLDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGLDoc construction/destruction

CTestGLDoc::CTestGLDoc()
{
	// TODO: add one-time construction code here

}

CTestGLDoc::~CTestGLDoc()
{
}

BOOL CTestGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestGLDoc serialization

void CTestGLDoc::Serialize(CArchive& ar)
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
// CTestGLDoc diagnostics

#ifdef _DEBUG
void CTestGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestGLDoc commands
