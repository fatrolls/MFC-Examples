// IMAPClientDoc.cpp : implementation of the CIMAPClientDoc class
//

#include "stdafx.h"
#include "IMAPClient.h"
#include "IMAPClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIMAPClientDoc

IMPLEMENT_DYNCREATE(CIMAPClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CIMAPClientDoc, CDocument)
	//{{AFX_MSG_MAP(CIMAPClientDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIMAPClientDoc construction/destruction

CIMAPClientDoc::CIMAPClientDoc()
{
}

CIMAPClientDoc::~CIMAPClientDoc()
{
}

BOOL CIMAPClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CIMAPClientDoc serialization

void CIMAPClientDoc::Serialize(CArchive& ar)
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
// CIMAPClientDoc diagnostics

#ifdef _DEBUG
void CIMAPClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIMAPClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIMAPClientDoc commands


BOOL CIMAPClientDoc::SaveModified() 
{
//	return CDocument::SaveModified();
	return -1; // don't allow the framework to prompt for saving
}
