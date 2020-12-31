// CustomizeManagerDoc.cpp : implementation of the CCustomizeManagerDoc class
//

#include "stdafx.h"
#include "CustomizeManager.h"

#include "CustomizeManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerDoc

IMPLEMENT_DYNCREATE(CCustomizeManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CCustomizeManagerDoc, CDocument)
	//{{AFX_MSG_MAP(CCustomizeManagerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerDoc construction/destruction

CCustomizeManagerDoc::CCustomizeManagerDoc()
{
	// TODO: add one-time construction code here

}

CCustomizeManagerDoc::~CCustomizeManagerDoc()
{
}

BOOL CCustomizeManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerDoc serialization

void CCustomizeManagerDoc::Serialize(CArchive& ar)
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
// CCustomizeManagerDoc diagnostics

#ifdef _DEBUG
void CCustomizeManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCustomizeManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerDoc commands
