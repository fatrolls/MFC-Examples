// BackgroundPainterDoc.cpp : implementation of the CBackgroundPainterDoc class
//

#include "stdafx.h"
#include "BackgroundPainter.h"

#include "BackgroundPainterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterDoc

IMPLEMENT_DYNCREATE(CBackgroundPainterDoc, CDocument)

BEGIN_MESSAGE_MAP(CBackgroundPainterDoc, CDocument)
	//{{AFX_MSG_MAP(CBackgroundPainterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterDoc construction/destruction

CBackgroundPainterDoc::CBackgroundPainterDoc()
{
	// TODO: add one-time construction code here

}

CBackgroundPainterDoc::~CBackgroundPainterDoc()
{
}

BOOL CBackgroundPainterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterDoc serialization

void CBackgroundPainterDoc::Serialize(CArchive& ar)
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
// CBackgroundPainterDoc diagnostics

#ifdef _DEBUG
void CBackgroundPainterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBackgroundPainterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterDoc commands
