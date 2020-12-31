// splashDoc.cpp : Implementierung der Klasse CSplashDoc
//

#include "stdafx.h"
#include "splash.h"

#include "splashDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashDoc

IMPLEMENT_DYNCREATE(CSplashDoc, CDocument)

BEGIN_MESSAGE_MAP(CSplashDoc, CDocument)
	//{{AFX_MSG_MAP(CSplashDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplashDoc Konstruktion/Destruktion

CSplashDoc::CSplashDoc()
{
}

CSplashDoc::~CSplashDoc()
{
}

BOOL CSplashDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSplashDoc Serialisierung

void CSplashDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSplashDoc Diagnose

#ifdef _DEBUG
void CSplashDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSplashDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplashDoc Befehle
