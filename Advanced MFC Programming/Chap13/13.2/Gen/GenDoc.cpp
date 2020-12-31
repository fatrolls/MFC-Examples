// GenDoc.cpp : implementation of the CGenDoc class
//

#include "stdafx.h"
#include "Gen.h"

#include "GenDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenDoc

IMPLEMENT_DYNCREATE(CGenDoc, CDocument)

BEGIN_MESSAGE_MAP(CGenDoc, CDocument)
	//{{AFX_MSG_MAP(CGenDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenDoc construction/destruction

CGenDoc::CGenDoc()
{
}

CGenDoc::~CGenDoc()
{
}

BOOL CGenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGenDoc serialization

void CGenDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGenDoc diagnostics

#ifdef _DEBUG
void CGenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGenDoc commands
