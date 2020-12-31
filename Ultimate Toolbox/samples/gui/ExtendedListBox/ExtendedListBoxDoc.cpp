// ExtendedListBoxDoc.cpp : implementation of the CExtendedListBoxDoc class
//

#include "stdafx.h"
#include "ExtendedListBox.h"

#include "ExtendedListBoxDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxDoc

IMPLEMENT_DYNCREATE(CExtendedListBoxDoc, CDocument)

BEGIN_MESSAGE_MAP(CExtendedListBoxDoc, CDocument)
	//{{AFX_MSG_MAP(CExtendedListBoxDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxDoc construction/destruction

CExtendedListBoxDoc::CExtendedListBoxDoc()
{
	// TODO: add one-time construction code here

}

CExtendedListBoxDoc::~CExtendedListBoxDoc()
{
}

BOOL CExtendedListBoxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxDoc serialization

void CExtendedListBoxDoc::Serialize(CArchive& ar)
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
// CExtendedListBoxDoc diagnostics

#ifdef _DEBUG
void CExtendedListBoxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExtendedListBoxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExtendedListBoxDoc commands
