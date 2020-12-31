#include "stdafx.h"
#include "StatusBar.h"

#include "StatusBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CStatusBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CStatusBarDoc, CDocument)
	//{{AFX_MSG_MAP(CStatusBarDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CStatusBarDoc::CStatusBarDoc()			{ }
CStatusBarDoc::~CStatusBarDoc()			{ }

BOOL CStatusBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())	return FALSE;
	return TRUE;
}

#ifdef _DEBUG
void CStatusBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStatusBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
