// MvTestDoc.cpp : implementation of the CMvTestDoc class
//

#include "stdafx.h"
#include "MvTest.h"

#include "MvTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMvTestDoc

IMPLEMENT_DYNCREATE(CMvTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CMvTestDoc, CDocument)
	//{{AFX_MSG_MAP(CMvTestDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMvTestDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CMvTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

static const IID IID_IMvTest =
{ 0xa695b2bf, 0xde92, 0x11d1, { 0xb6, 0xbe, 0x0, 0xc0, 0x4f, 0xa3, 0x5f, 0x76 } };

BEGIN_INTERFACE_MAP(CMvTestDoc, CDocument)
	INTERFACE_PART(CMvTestDoc, IID_IMvTest, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMvTestDoc construction/destruction

CMvTestDoc::CMvTestDoc()
{
	EnableAutomation();

	AfxOleLockApp();
}

CMvTestDoc::~CMvTestDoc()
{
	AfxOleUnlockApp();
}

BOOL CMvTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMvTestDoc serialization

void CMvTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMvTestDoc diagnostics

#ifdef _DEBUG
void CMvTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMvTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMvTestDoc commands
