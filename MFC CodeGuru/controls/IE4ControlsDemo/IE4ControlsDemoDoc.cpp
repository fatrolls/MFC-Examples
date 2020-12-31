// IE4ControlsDemoDoc.cpp : implementation of the CIE4ControlsDemoDoc class
//

#include "stdafx.h"
#include "IE4ControlsDemo.h"

#include "IE4ControlsDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIE4ControlsDemoDoc

IMPLEMENT_DYNCREATE(CIE4ControlsDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CIE4ControlsDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CIE4ControlsDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIE4ControlsDemoDoc construction/destruction

CIE4ControlsDemoDoc::CIE4ControlsDemoDoc()
{
	// TODO: add one-time construction code here

}

CIE4ControlsDemoDoc::~CIE4ControlsDemoDoc()
{
}

BOOL CIE4ControlsDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CIE4ControlsDemoDoc serialization

void CIE4ControlsDemoDoc::Serialize(CArchive& ar)
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
// CIE4ControlsDemoDoc diagnostics

#ifdef _DEBUG
void CIE4ControlsDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIE4ControlsDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIE4ControlsDemoDoc commands
