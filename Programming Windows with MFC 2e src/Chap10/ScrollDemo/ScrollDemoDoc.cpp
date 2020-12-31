// ScrollDemoDoc.cpp : implementation of the CScrollDemoDoc class
//

#include "stdafx.h"
#include "ScrollDemo.h"

#include "ScrollDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollDemoDoc

IMPLEMENT_DYNCREATE(CScrollDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CScrollDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CScrollDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollDemoDoc construction/destruction

CScrollDemoDoc::CScrollDemoDoc()
{
	// TODO: add one-time construction code here

}

CScrollDemoDoc::~CScrollDemoDoc()
{
}

BOOL CScrollDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CScrollDemoDoc serialization

void CScrollDemoDoc::Serialize(CArchive& ar)
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
// CScrollDemoDoc diagnostics

#ifdef _DEBUG
void CScrollDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScrollDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScrollDemoDoc commands
