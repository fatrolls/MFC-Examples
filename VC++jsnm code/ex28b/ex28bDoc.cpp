// ex28bDoc.cpp : implementation of the CEx28bDoc class
//

#include "stdafx.h"
#include "ex28b.h"

#include "ex28bSet.h"
#include "ex28bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28bDoc

IMPLEMENT_DYNCREATE(CEx28bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx28bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx28bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28bDoc construction/destruction

CEx28bDoc::CEx28bDoc()
{
	// TODO: add one-time construction code here

}

CEx28bDoc::~CEx28bDoc()
{
}

BOOL CEx28bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx28bDoc diagnostics

#ifdef _DEBUG
void CEx28bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx28bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28bDoc commands
