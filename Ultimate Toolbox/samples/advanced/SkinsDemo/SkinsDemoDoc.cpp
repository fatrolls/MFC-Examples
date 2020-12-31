// SkinsDemoDoc.cpp : implementation of the CSkinsDemoDoc class
//

#include "stdafx.h"
#include "SkinsDemo.h"

#include "SkinsDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoDoc

IMPLEMENT_DYNCREATE(CSkinsDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkinsDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CSkinsDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoDoc construction/destruction

CSkinsDemoDoc::CSkinsDemoDoc()
{
	// TODO: add one-time construction code here

}

CSkinsDemoDoc::~CSkinsDemoDoc()
{
}

BOOL CSkinsDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoDoc serialization

void CSkinsDemoDoc::Serialize(CArchive& ar)
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
// CSkinsDemoDoc diagnostics

#ifdef _DEBUG
void CSkinsDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkinsDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoDoc commands
