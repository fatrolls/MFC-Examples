// datapkprojDoc.cpp : implementation of the CDatapkprojDoc class
//

#include "stdafx.h"
#include "datapkproj.h"

#include "datapkprojDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojDoc

IMPLEMENT_DYNCREATE(CDatapkprojDoc, CDocument)

BEGIN_MESSAGE_MAP(CDatapkprojDoc, CDocument)
	//{{AFX_MSG_MAP(CDatapkprojDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojDoc construction/destruction

CDatapkprojDoc::CDatapkprojDoc()
{
	// TODO: add one-time construction code here

}

CDatapkprojDoc::~CDatapkprojDoc()
{
}

BOOL CDatapkprojDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDatapkprojDoc serialization

void CDatapkprojDoc::Serialize(CArchive& ar)
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
// CDatapkprojDoc diagnostics

#ifdef _DEBUG
void CDatapkprojDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDatapkprojDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojDoc commands
