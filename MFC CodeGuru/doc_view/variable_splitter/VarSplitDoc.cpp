// VarSplitDoc.cpp : implementation of the CVarSplitDoc class
//

#include "stdafx.h"
#include "VarSplit.h"

#include "VarSplitDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVarSplitDoc

IMPLEMENT_DYNCREATE(CVarSplitDoc, CDocument)

BEGIN_MESSAGE_MAP(CVarSplitDoc, CDocument)
	//{{AFX_MSG_MAP(CVarSplitDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVarSplitDoc construction/destruction

CVarSplitDoc::CVarSplitDoc()
{
	// TODO: add one-time construction code here

}

CVarSplitDoc::~CVarSplitDoc()
{
}

BOOL CVarSplitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVarSplitDoc serialization

void CVarSplitDoc::Serialize(CArchive& ar)
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
// CVarSplitDoc diagnostics

#ifdef _DEBUG
void CVarSplitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVarSplitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVarSplitDoc commands
