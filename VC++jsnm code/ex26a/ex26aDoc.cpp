// ex26aDoc.cpp : implementation of the CEx26aDoc class
//

#include "stdafx.h"
#include "ex26a.h"

#include "ex26aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx26aDoc

IMPLEMENT_DYNCREATE(CEx26aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx26aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx26aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx26aDoc construction/destruction

CEx26aDoc::CEx26aDoc()
{
	// TODO: add one-time construction code here

}

CEx26aDoc::~CEx26aDoc()
{
}

BOOL CEx26aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx26aDoc serialization

void CEx26aDoc::Serialize(CArchive& ar)
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
// CEx26aDoc diagnostics

#ifdef _DEBUG
void CEx26aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx26aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx26aDoc commands
