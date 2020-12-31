// scrngrabDoc.cpp : implementation of the CScrngrabDoc class
//

#include "stdafx.h"
#include "scrngrab.h"

#include "scrngrabDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrngrabDoc

IMPLEMENT_DYNCREATE(CScrngrabDoc, CDocument)

BEGIN_MESSAGE_MAP(CScrngrabDoc, CDocument)
	//{{AFX_MSG_MAP(CScrngrabDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrngrabDoc construction/destruction

CScrngrabDoc::CScrngrabDoc()
{
	// TODO: add one-time construction code here

}

CScrngrabDoc::~CScrngrabDoc()
{
}

BOOL CScrngrabDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CScrngrabDoc serialization

void CScrngrabDoc::Serialize(CArchive& ar)
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
// CScrngrabDoc diagnostics

#ifdef _DEBUG
void CScrngrabDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScrngrabDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScrngrabDoc commands
