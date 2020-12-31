// CreditsTestDoc.cpp : implementation of the CCreditsTestDoc class
//

#include "stdafx.h"
#include "CreditsTest.h"

#include "CreditsTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestDoc

IMPLEMENT_DYNCREATE(CCreditsTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CCreditsTestDoc, CDocument)
	//{{AFX_MSG_MAP(CCreditsTestDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestDoc construction/destruction

CCreditsTestDoc::CCreditsTestDoc()
{
}

CCreditsTestDoc::~CCreditsTestDoc()
{
}

BOOL CCreditsTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCreditsTestDoc serialization

void CCreditsTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestDoc diagnostics

#ifdef _DEBUG
void CCreditsTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCreditsTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestDoc commands
