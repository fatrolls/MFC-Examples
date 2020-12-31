// DragEditDoc.cpp : implementation of the CDragEditDoc class
//

#include "stdafx.h"
#include "DragEdit.h"

#include "DragEditDoc.h"
#include "TestDragEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragEditDoc

IMPLEMENT_DYNCREATE(CDragEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CDragEditDoc, CDocument)
	//{{AFX_MSG_MAP(CDragEditDoc)
	ON_COMMAND(ID_FILE_TEST, OnFileTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragEditDoc construction/destruction

CDragEditDoc::CDragEditDoc()
{
	// TODO: add one-time construction code here

}

CDragEditDoc::~CDragEditDoc()
{
}

BOOL CDragEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDragEditDoc serialization

void CDragEditDoc::Serialize(CArchive& ar)
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
// CDragEditDoc diagnostics

#ifdef _DEBUG
void CDragEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDragEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDragEditDoc commands

void CDragEditDoc::OnFileTest() 
{
    CTestDragEditDlg    dlg;
    dlg.DoModal();
}
