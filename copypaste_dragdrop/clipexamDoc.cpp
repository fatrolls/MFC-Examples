// clipexamDoc.cpp : implementation of the CClipExamDoc class
//

#include "stdafx.h"
#include "clipexam.h"

#include "clipexamDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipExamDoc

IMPLEMENT_DYNCREATE(CClipExamDoc, CDocument)

BEGIN_MESSAGE_MAP(CClipExamDoc, CDocument)
	//{{AFX_MSG_MAP(CClipExamDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CClipExamDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CClipExamDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IClipexam to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {DBF687E7-868E-11D1-B99D-00A0C9763A0A}
static const IID IID_IClipexam =
{ 0xdbf687e7, 0x868e, 0x11d1, { 0xb9, 0x9d, 0x0, 0xa0, 0xc9, 0x76, 0x3a, 0xa } };

BEGIN_INTERFACE_MAP(CClipExamDoc, CDocument)
	INTERFACE_PART(CClipExamDoc, IID_IClipexam, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipExamDoc construction/destruction

CClipExamDoc::CClipExamDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CClipExamDoc::~CClipExamDoc()
{
	AfxOleUnlockApp();
}

BOOL CClipExamDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CClipExamDoc serialization

void CClipExamDoc::Serialize(CArchive& ar)
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
// CClipExamDoc diagnostics

#ifdef _DEBUG
void CClipExamDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClipExamDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClipExamDoc commands
