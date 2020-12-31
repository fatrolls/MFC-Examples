// TestPrintFormDoc.cpp : implementation of the CTestPrintFormDoc class
//

#include "stdafx.h"
#include "TestPrintForm.h"

#include "TestPrintFormDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormDoc

IMPLEMENT_DYNCREATE(CTestPrintFormDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestPrintFormDoc, CDocument)
	//{{AFX_MSG_MAP(CTestPrintFormDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormDoc construction/destruction

CTestPrintFormDoc::CTestPrintFormDoc()
{
	// TODO: add one-time construction code here

}

CTestPrintFormDoc::~CTestPrintFormDoc()
{
}

BOOL CTestPrintFormDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormDoc serialization

void CTestPrintFormDoc::Serialize(CArchive& ar)
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
// CTestPrintFormDoc diagnostics

#ifdef _DEBUG
void CTestPrintFormDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestPrintFormDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormDoc commands
