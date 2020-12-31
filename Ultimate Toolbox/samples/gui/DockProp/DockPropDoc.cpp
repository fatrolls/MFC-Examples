// DockPropDoc.cpp : implementation of the CDockPropDoc class
//

#include "stdafx.h"
#include "DockProp.h"

#include "DockPropDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockPropDoc

IMPLEMENT_DYNCREATE(CDockPropDoc, CDocument)

BEGIN_MESSAGE_MAP(CDockPropDoc, CDocument)
	//{{AFX_MSG_MAP(CDockPropDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDockPropDoc construction/destruction

CDockPropDoc::CDockPropDoc()
{
	// TODO: add one-time construction code here

}

CDockPropDoc::~CDockPropDoc()
{
}

BOOL CDockPropDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDockPropDoc serialization

void CDockPropDoc::Serialize(CArchive& ar)
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
// CDockPropDoc diagnostics

#ifdef _DEBUG
void CDockPropDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDockPropDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDockPropDoc commands
