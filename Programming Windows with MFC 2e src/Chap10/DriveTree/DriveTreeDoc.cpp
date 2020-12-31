// DriveTreeDoc.cpp : implementation of the CDriveTreeDoc class
//

#include "stdafx.h"
#include "DriveTree.h"

#include "DriveTreeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriveTreeDoc

IMPLEMENT_DYNCREATE(CDriveTreeDoc, CDocument)

BEGIN_MESSAGE_MAP(CDriveTreeDoc, CDocument)
	//{{AFX_MSG_MAP(CDriveTreeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriveTreeDoc construction/destruction

CDriveTreeDoc::CDriveTreeDoc()
{
	// TODO: add one-time construction code here

}

CDriveTreeDoc::~CDriveTreeDoc()
{
}

BOOL CDriveTreeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDriveTreeDoc serialization

void CDriveTreeDoc::Serialize(CArchive& ar)
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
// CDriveTreeDoc diagnostics

#ifdef _DEBUG
void CDriveTreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDriveTreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDriveTreeDoc commands
