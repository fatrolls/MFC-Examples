#include "stdafx.h"
#include "Help.h"
#include "HelpDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CHelpDoc, CDocument)

BEGIN_MESSAGE_MAP(CHelpDoc, CDocument)
	//{{AFX_MSG_MAP(CHelpDoc)
	ON_COMMAND(ID_HELPTEST_TESTA, OnHelptestTestA)
	ON_COMMAND(ID_HELPTEST_TESTB, OnHelptestTestB)
	ON_COMMAND(ID_HELPTEST_TESTC, OnHelptestTestC)
	ON_COMMAND(ID_HELPTEST_TESTD, OnHelptestTestD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CHelpDoc::CHelpDoc()
{
}

CHelpDoc::~CHelpDoc()
{
}

BOOL CHelpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CHelpDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CHelpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHelpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

void CHelpDoc::OnHelptestTestA() 
{
}

void CHelpDoc::OnHelptestTestB() 
{
}

void CHelpDoc::OnHelptestTestC() 
{
}

void CHelpDoc::OnHelptestTestD() 
{
}
