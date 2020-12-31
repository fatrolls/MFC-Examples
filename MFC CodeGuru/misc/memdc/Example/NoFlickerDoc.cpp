// NoFlickerDoc.cpp : implementation of the CNoFlickerDoc class
//

#include "stdafx.h"
#include "NoFlicker.h"

#include "NoFlickerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoFlickerDoc

IMPLEMENT_DYNCREATE(CNoFlickerDoc, CDocument)

BEGIN_MESSAGE_MAP(CNoFlickerDoc, CDocument)
	//{{AFX_MSG_MAP(CNoFlickerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoFlickerDoc construction/destruction

CNoFlickerDoc::CNoFlickerDoc()
{
	// TODO: add one-time construction code here

}

CNoFlickerDoc::~CNoFlickerDoc()
{
}

BOOL CNoFlickerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNoFlickerDoc serialization

void CNoFlickerDoc::Serialize(CArchive& ar)
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
// CNoFlickerDoc diagnostics

#ifdef _DEBUG
void CNoFlickerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNoFlickerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNoFlickerDoc commands
