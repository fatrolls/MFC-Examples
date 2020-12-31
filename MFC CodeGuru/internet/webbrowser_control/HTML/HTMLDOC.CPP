// HtmlDoc.cpp : implementation of the CHtmlDoc class
//

#include "stdafx.h"
#include "Html.h"

#include "HtmlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlDoc

IMPLEMENT_DYNCREATE(CHtmlDoc, CDocument)

BEGIN_MESSAGE_MAP(CHtmlDoc, CDocument)
	//{{AFX_MSG_MAP(CHtmlDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlDoc construction/destruction

CHtmlDoc::CHtmlDoc()
{
	// TODO: add one-time construction code here

}

CHtmlDoc::~CHtmlDoc()
{
}

BOOL CHtmlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHtmlDoc serialization

void CHtmlDoc::Serialize(CArchive& ar)
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
// CHtmlDoc diagnostics

#ifdef _DEBUG
void CHtmlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHtmlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHtmlDoc commands
