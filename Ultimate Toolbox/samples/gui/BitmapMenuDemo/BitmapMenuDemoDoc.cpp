// BitmapMenuDemoDoc.cpp : implementation of the CBitmapMenuDemoDoc class
//

#include "stdafx.h"
#include "BitmapMenuDemo.h"

#include "BitmapMenuDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapMenuDemoDoc

IMPLEMENT_DYNCREATE(CBitmapMenuDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBitmapMenuDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBitmapMenuDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapMenuDemoDoc construction/destruction

CBitmapMenuDemoDoc::CBitmapMenuDemoDoc()
{
	// TODO: add one-time construction code here

}

CBitmapMenuDemoDoc::~CBitmapMenuDemoDoc()
{
}

BOOL CBitmapMenuDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBitmapMenuDemoDoc serialization

void CBitmapMenuDemoDoc::Serialize(CArchive& ar)
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
// CBitmapMenuDemoDoc diagnostics

#ifdef _DEBUG
void CBitmapMenuDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBitmapMenuDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBitmapMenuDemoDoc commands

BOOL CBitmapMenuDemoDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	UNREFERENCED_PARAMETER(lpszPathName);
	
	return TRUE;

	// we don't want to overwright existed file 
//	return CDocument::OnSaveDocument(lpszPathName);
}
