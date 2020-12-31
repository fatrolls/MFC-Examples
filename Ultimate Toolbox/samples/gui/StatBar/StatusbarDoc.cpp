// StatusbarDoc.cpp : implementation of the CStatusbarDoc class
//

#include "stdafx.h"
#include "Statusbar.h"

#include "StatusbarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusbarDoc

IMPLEMENT_DYNCREATE(CStatusbarDoc, CDocument)

BEGIN_MESSAGE_MAP(CStatusbarDoc, CDocument)
	//{{AFX_MSG_MAP(CStatusbarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusbarDoc construction/destruction

CStatusbarDoc::CStatusbarDoc()
{
	// TODO: add one-time construction code here

}

CStatusbarDoc::~CStatusbarDoc()
{
}

BOOL CStatusbarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStatusbarDoc serialization

void CStatusbarDoc::Serialize(CArchive& ar)
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
// CStatusbarDoc diagnostics

#ifdef _DEBUG
void CStatusbarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStatusbarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusbarDoc commands
