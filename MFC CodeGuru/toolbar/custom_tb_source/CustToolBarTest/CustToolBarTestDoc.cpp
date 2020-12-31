// CustToolBarTestDoc.cpp : implementation of the CCustToolBarTestDoc class
//

#include "stdafx.h"
#include "CustToolBarTest.h"

#include "CustToolBarTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestDoc

IMPLEMENT_DYNCREATE(CCustToolBarTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CCustToolBarTestDoc, CDocument)
	//{{AFX_MSG_MAP(CCustToolBarTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestDoc construction/destruction

CCustToolBarTestDoc::CCustToolBarTestDoc()
{
	// TODO: add one-time construction code here

}

CCustToolBarTestDoc::~CCustToolBarTestDoc()
{
}

BOOL CCustToolBarTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestDoc serialization

void CCustToolBarTestDoc::Serialize(CArchive& ar)
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
// CCustToolBarTestDoc diagnostics

#ifdef _DEBUG
void CCustToolBarTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCustToolBarTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestDoc commands
