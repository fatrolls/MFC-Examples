// MessengerDoc.cpp : implementation of the CMessengerDoc class
//

#include "stdafx.h"
#include "Messenger.h"

#include "MessengerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessengerDoc

IMPLEMENT_DYNCREATE(CMessengerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMessengerDoc, CDocument)
	//{{AFX_MSG_MAP(CMessengerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessengerDoc construction/destruction

CMessengerDoc::CMessengerDoc()
{
	// TODO: add one-time construction code here

}

CMessengerDoc::~CMessengerDoc()
{
}

BOOL CMessengerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMessengerDoc serialization

void CMessengerDoc::Serialize(CArchive& ar)
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
// CMessengerDoc diagnostics

#ifdef _DEBUG
void CMessengerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMessengerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMessengerDoc commands
