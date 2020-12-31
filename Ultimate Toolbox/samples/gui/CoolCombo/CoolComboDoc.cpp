// CoolComboDoc.cpp : implementation of the CCoolComboDoc class
//

#include "stdafx.h"
#include "CoolCombo.h"

#include "CoolComboDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoolComboDoc

IMPLEMENT_DYNCREATE(CCoolComboDoc, CDocument)

BEGIN_MESSAGE_MAP(CCoolComboDoc, CDocument)
	//{{AFX_MSG_MAP(CCoolComboDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoolComboDoc construction/destruction

CCoolComboDoc::CCoolComboDoc()
{
	// TODO: add one-time construction code here

}

CCoolComboDoc::~CCoolComboDoc()
{
}

BOOL CCoolComboDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCoolComboDoc serialization

void CCoolComboDoc::Serialize(CArchive& ar)
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
// CCoolComboDoc diagnostics

#ifdef _DEBUG
void CCoolComboDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCoolComboDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCoolComboDoc commands
