// CPPTooltip_demoDoc.cpp : implementation of the CPPTooltip_demoDoc class
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"

#include "CPPTooltip_demoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoDoc

IMPLEMENT_DYNCREATE(CPPTooltip_demoDoc, CDocument)

BEGIN_MESSAGE_MAP(CPPTooltip_demoDoc, CDocument)
	//{{AFX_MSG_MAP(CPPTooltip_demoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoDoc construction/destruction

CPPTooltip_demoDoc::CPPTooltip_demoDoc()
{
	// TODO: add one-time construction code here

}

CPPTooltip_demoDoc::~CPPTooltip_demoDoc()
{
}

BOOL CPPTooltip_demoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoDoc serialization

void CPPTooltip_demoDoc::Serialize(CArchive& ar)
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
// CPPTooltip_demoDoc diagnostics

#ifdef _DEBUG
void CPPTooltip_demoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPPTooltip_demoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoDoc commands
