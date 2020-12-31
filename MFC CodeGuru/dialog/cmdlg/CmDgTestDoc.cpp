// CmDgTestDoc.cpp : implementation of the CCmDgTestDoc class
//

#include "stdafx.h"
#include "CmDgTest.h"

#include "CmDgTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestDoc

IMPLEMENT_DYNCREATE(CCmDgTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CCmDgTestDoc, CDocument)
	//{{AFX_MSG_MAP(CCmDgTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestDoc construction/destruction

CCmDgTestDoc::CCmDgTestDoc()
{
	// TODO: add one-time construction code here

}

CCmDgTestDoc::~CCmDgTestDoc()
{
}

BOOL CCmDgTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestDoc serialization

void CCmDgTestDoc::Serialize(CArchive& ar)
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
// CCmDgTestDoc diagnostics

#ifdef _DEBUG
void CCmDgTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCmDgTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestDoc commands

BOOL CCmDgTestDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}
