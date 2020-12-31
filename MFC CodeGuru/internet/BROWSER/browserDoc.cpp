// browserDoc.cpp : implementation of the CBrowserDoc class
//

#include "stdafx.h"
#include "browser.h"

#include "browserDoc.h"
#include "browserview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc

IMPLEMENT_DYNCREATE(CBrowserDoc, CDocument)

BEGIN_MESSAGE_MAP(CBrowserDoc, CDocument)
	//{{AFX_MSG_MAP(CBrowserDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc construction/destruction

CBrowserDoc::CBrowserDoc()
{
	// TODO: add one-time construction code here

}

CBrowserDoc::~CBrowserDoc()
{
}

BOOL CBrowserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc serialization

void CBrowserDoc::Serialize(CArchive& ar)
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
// CBrowserDoc diagnostics

#ifdef _DEBUG
void CBrowserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBrowserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc commands

BOOL CBrowserDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
    CBrowserView pView;
	pView.NavigateURL(lpszPathName);	
	return TRUE;
}
