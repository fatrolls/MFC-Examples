// btncodoc.cpp : implementation of the CBtncolorDoc class
//

#include "stdafx.h"
#include "btncolor.h"

#include "btncodoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBtncolorDoc

IMPLEMENT_DYNCREATE(CBtncolorDoc, CDocument)

BEGIN_MESSAGE_MAP(CBtncolorDoc, CDocument)
	//{{AFX_MSG_MAP(CBtncolorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBtncolorDoc construction/destruction

CBtncolorDoc::CBtncolorDoc()
{
	// TODO: add one-time construction code here
}

CBtncolorDoc::~CBtncolorDoc()
{
}

BOOL CBtncolorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBtncolorDoc serialization

void CBtncolorDoc::Serialize(CArchive& ar)
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
// CBtncolorDoc diagnostics

#ifdef _DEBUG
void CBtncolorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBtncolorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBtncolorDoc commands
