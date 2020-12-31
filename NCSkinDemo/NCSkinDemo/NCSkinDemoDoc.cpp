
// NCSkinDemoDoc.cpp : implementation of the CNCSkinDemoDoc class
//

#include "stdafx.h"
#include "NCSkinDemo.h"

#include "NCSkinDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNCSkinDemoDoc

IMPLEMENT_DYNCREATE(CNCSkinDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CNCSkinDemoDoc, CDocument)
END_MESSAGE_MAP()


// CNCSkinDemoDoc construction/destruction

CNCSkinDemoDoc::CNCSkinDemoDoc()
{
	// TODO: add one-time construction code here

}

CNCSkinDemoDoc::~CNCSkinDemoDoc()
{
}

BOOL CNCSkinDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CNCSkinDemoDoc serialization

void CNCSkinDemoDoc::Serialize(CArchive& ar)
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


// CNCSkinDemoDoc diagnostics

#ifdef _DEBUG
void CNCSkinDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNCSkinDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNCSkinDemoDoc commands
