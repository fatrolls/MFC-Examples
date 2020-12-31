// HTMLEditDoc.cpp : implementation of the CHTMLEditDoc class
//

#include "stdafx.h"
#include "HTMLEdit.h"

#include "HTMLEditDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CHTMLEditDoc

IMPLEMENT_DYNCREATE(CHTMLEditDoc, CHtmlEditDoc)

BEGIN_MESSAGE_MAP(CHTMLEditDoc, CHtmlEditDoc)
END_MESSAGE_MAP()


// CHTMLEditDoc construction/destruction

CHTMLEditDoc::CHTMLEditDoc()
{
	// TODO: add one-time construction code here

}

CHTMLEditDoc::~CHTMLEditDoc()
{
}

BOOL CHTMLEditDoc::OnNewDocument()
{
	if (!CHtmlEditDoc::OnNewDocument())
		return FALSE;

	return TRUE;
}


// CHTMLEditDoc diagnostics

#ifdef _DEBUG
void CHTMLEditDoc::AssertValid() const
{
	CHtmlEditDoc::AssertValid();
}

void CHTMLEditDoc::Dump(CDumpContext& dc) const
{
	CHtmlEditDoc::Dump(dc);
}
#endif //_DEBUG


// CHTMLEditDoc commands
