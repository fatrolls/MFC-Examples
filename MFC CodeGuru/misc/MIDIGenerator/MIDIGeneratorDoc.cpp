// MIDIGeneratorDoc.cpp : implementation of the CMIDIGeneratorDoc class
//

#include "stdafx.h"
#include "MIDIGenerator.h"

#include "MIDIGeneratorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorDoc

IMPLEMENT_DYNCREATE(CMIDIGeneratorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMIDIGeneratorDoc, CDocument)
	//{{AFX_MSG_MAP(CMIDIGeneratorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorDoc construction/destruction

CMIDIGeneratorDoc::CMIDIGeneratorDoc()
{
	// TODO: add one-time construction code here

}

CMIDIGeneratorDoc::~CMIDIGeneratorDoc()
{
}

BOOL CMIDIGeneratorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorDoc serialization

void CMIDIGeneratorDoc::Serialize(CArchive& ar)
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
// CMIDIGeneratorDoc diagnostics

#ifdef _DEBUG
void CMIDIGeneratorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMIDIGeneratorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMIDIGeneratorDoc commands
