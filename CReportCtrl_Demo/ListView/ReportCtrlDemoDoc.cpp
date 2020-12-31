// ReportCtrlDemoDoc.cpp : implementation of the CReportCtrlDemoDoc class
//

#include "stdafx.h"
#include "ReportCtrlDemo.h"

#include "ReportCtrlDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoDoc

IMPLEMENT_DYNCREATE(CReportCtrlDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CReportCtrlDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CReportCtrlDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoDoc construction/destruction

CReportCtrlDemoDoc::CReportCtrlDemoDoc()
{
	// TODO: add one-time construction code here

}

CReportCtrlDemoDoc::~CReportCtrlDemoDoc()
{
}

BOOL CReportCtrlDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoDoc serialization

void CReportCtrlDemoDoc::Serialize(CArchive& ar)
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
// CReportCtrlDemoDoc diagnostics

#ifdef _DEBUG
void CReportCtrlDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CReportCtrlDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoDoc commands
