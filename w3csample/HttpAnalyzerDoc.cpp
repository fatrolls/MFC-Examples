// HttpAnalyzerDoc.cpp : implementation of the CHttpAnalyzerDoc class
//

#include "stdafx.h"
#include "HttpAnalyzer.h"

#include "HttpAnalyzerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerDoc

IMPLEMENT_DYNCREATE(CHttpAnalyzerDoc, CDocument)

BEGIN_MESSAGE_MAP(CHttpAnalyzerDoc, CDocument)
	//{{AFX_MSG_MAP(CHttpAnalyzerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerDoc construction/destruction

CHttpAnalyzerDoc::CHttpAnalyzerDoc()
{
	// TODO: add one-time construction code here

}

CHttpAnalyzerDoc::~CHttpAnalyzerDoc()
{
}

BOOL CHttpAnalyzerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerDoc serialization

void CHttpAnalyzerDoc::Serialize(CArchive& ar)
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
// CHttpAnalyzerDoc diagnostics

#ifdef _DEBUG
void CHttpAnalyzerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHttpAnalyzerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerDoc commands
