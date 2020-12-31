// coolsb_mfctestDoc.cpp : implementation of the CCoolsb_mfctestDoc class
//

#include "stdafx.h"
#include "coolsb_mfctest.h"

#include "coolsb_mfctestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestDoc

IMPLEMENT_DYNCREATE(CCoolsb_mfctestDoc, CDocument)

BEGIN_MESSAGE_MAP(CCoolsb_mfctestDoc, CDocument)
	//{{AFX_MSG_MAP(CCoolsb_mfctestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestDoc construction/destruction

CCoolsb_mfctestDoc::CCoolsb_mfctestDoc()
{
	// TODO: add one-time construction code here

}

CCoolsb_mfctestDoc::~CCoolsb_mfctestDoc()
{
}

BOOL CCoolsb_mfctestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestDoc serialization

void CCoolsb_mfctestDoc::Serialize(CArchive& ar)
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
// CCoolsb_mfctestDoc diagnostics

#ifdef _DEBUG
void CCoolsb_mfctestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCoolsb_mfctestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestDoc commands
