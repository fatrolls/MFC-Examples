// EZPrintDoc.cpp : implementation of the CEZPrintDoc class
//

#include "stdafx.h"
#include "EZPrint.h"

#include "EZPrintDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEZPrintDoc

IMPLEMENT_DYNCREATE(CEZPrintDoc, CDocument)

BEGIN_MESSAGE_MAP(CEZPrintDoc, CDocument)
	//{{AFX_MSG_MAP(CEZPrintDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEZPrintDoc construction/destruction

CEZPrintDoc::CEZPrintDoc()
{
	// TODO: add one-time construction code here

}

CEZPrintDoc::~CEZPrintDoc()
{
}

BOOL CEZPrintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEZPrintDoc serialization

void CEZPrintDoc::Serialize(CArchive& ar)
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
// CEZPrintDoc diagnostics

#ifdef _DEBUG
void CEZPrintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEZPrintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEZPrintDoc commands
