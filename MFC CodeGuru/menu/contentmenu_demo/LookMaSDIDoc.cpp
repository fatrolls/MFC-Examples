// LookMaSDIDoc.cpp : implementation of the CLookMaSDIDoc class
//

#include "stdafx.h"
#include "LookMaSDI.h"

#include "LookMaSDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIDoc

IMPLEMENT_DYNCREATE(CLookMaSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CLookMaSDIDoc, CDocument)
	//{{AFX_MSG_MAP(CLookMaSDIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIDoc construction/destruction

CLookMaSDIDoc::CLookMaSDIDoc()
{
	// TODO: add one-time construction code here

}

CLookMaSDIDoc::~CLookMaSDIDoc()
{
}

BOOL CLookMaSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIDoc serialization

void CLookMaSDIDoc::Serialize(CArchive& ar)
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
// CLookMaSDIDoc diagnostics

#ifdef _DEBUG
void CLookMaSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLookMaSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIDoc commands
