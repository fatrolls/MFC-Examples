// ProgressDemoDoc.cpp : implementation of the CProgressDemoDoc class
//

#include "stdafx.h"
#include "ProgressDemo.h"

#include "ProgressDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoDoc

IMPLEMENT_DYNCREATE(CProgressDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CProgressDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CProgressDemoDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoDoc construction/destruction

CProgressDemoDoc::CProgressDemoDoc()
{
}

CProgressDemoDoc::~CProgressDemoDoc()
{
}

BOOL CProgressDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CProgressDemoDoc serialization

void CProgressDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoDoc diagnostics

#ifdef _DEBUG
void CProgressDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProgressDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoDoc commands
