// CustomizeDoc.cpp : implementation of the CCustomizeDoc class
//

#include "stdafx.h"
#include "Customize.h"

#include "CustomizeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDoc

IMPLEMENT_DYNCREATE(CCustomizeDoc, CDocument)

BEGIN_MESSAGE_MAP(CCustomizeDoc, CDocument)
	//{{AFX_MSG_MAP(CCustomizeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDoc construction/destruction

CCustomizeDoc::CCustomizeDoc()
{
	// TODO: add one-time construction code here

}

CCustomizeDoc::~CCustomizeDoc()
{
}

BOOL CCustomizeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDoc serialization

void CCustomizeDoc::Serialize(CArchive& ar)
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
// CCustomizeDoc diagnostics

#ifdef _DEBUG
void CCustomizeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCustomizeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDoc commands
