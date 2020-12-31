// mltithrdDoc.cpp : implementation of the CMltithrdDoc class
//

#include "stdafx.h"
#include "mltithrd.h"

#include "mltithrdDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMltithrdDoc

IMPLEMENT_DYNCREATE(CMltithrdDoc, CDocument)

BEGIN_MESSAGE_MAP(CMltithrdDoc, CDocument)
	//{{AFX_MSG_MAP(CMltithrdDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMltithrdDoc construction/destruction

CMltithrdDoc::CMltithrdDoc()
{
	// TODO: add one-time construction code here

}

CMltithrdDoc::~CMltithrdDoc()
{
}

BOOL CMltithrdDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMltithrdDoc serialization

void CMltithrdDoc::Serialize(CArchive& ar)
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
// CMltithrdDoc diagnostics

#ifdef _DEBUG
void CMltithrdDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMltithrdDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMltithrdDoc commands
