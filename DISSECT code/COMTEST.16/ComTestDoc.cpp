// ComTestDoc.cpp : implementation of the CComTestDoc class
//

#include "stdafx.h"
#include "ComTest.h"

#include "ComTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComTestDoc

IMPLEMENT_DYNCREATE(CComTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CComTestDoc, CDocument)
	//{{AFX_MSG_MAP(CComTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComTestDoc construction/destruction

CComTestDoc::CComTestDoc()
{
	// TODO: add one-time construction code here

}

CComTestDoc::~CComTestDoc()
{
}

BOOL CComTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CComTestDoc serialization

void CComTestDoc::Serialize(CArchive& ar)
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
// CComTestDoc diagnostics

#ifdef _DEBUG
void CComTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CComTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CComTestDoc commands
