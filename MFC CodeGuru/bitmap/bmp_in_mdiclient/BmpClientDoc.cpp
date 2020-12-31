// BmpClientDoc.cpp : implementation of the CBmpClientDoc class
//

#include "stdafx.h"
#include "BmpClient.h"

#include "BmpClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpClientDoc

IMPLEMENT_DYNCREATE(CBmpClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CBmpClientDoc, CDocument)
	//{{AFX_MSG_MAP(CBmpClientDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpClientDoc construction/destruction

CBmpClientDoc::CBmpClientDoc()
{
}

CBmpClientDoc::~CBmpClientDoc()
{
}

BOOL CBmpClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBmpClientDoc serialization

void CBmpClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBmpClientDoc diagnostics

#ifdef _DEBUG
void CBmpClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBmpClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpClientDoc commands
