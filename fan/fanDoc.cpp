// fanDoc.cpp : implementation of the CFanDoc class
//

#include "stdafx.h"
#include "fan.h"

#include "fanDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFanDoc

IMPLEMENT_DYNCREATE(CFanDoc, CDocument)

BEGIN_MESSAGE_MAP(CFanDoc, CDocument)
	//{{AFX_MSG_MAP(CFanDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFanDoc construction/destruction

CFanDoc::CFanDoc()
{
	// TODO: add one-time construction code here

}

CFanDoc::~CFanDoc()
{
}

BOOL CFanDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFanDoc serialization

void CFanDoc::Serialize(CArchive& ar)
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
// CFanDoc diagnostics

#ifdef _DEBUG
void CFanDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFanDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFanDoc commands
