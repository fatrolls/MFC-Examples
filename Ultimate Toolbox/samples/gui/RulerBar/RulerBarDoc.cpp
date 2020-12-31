// RulerBarDoc.cpp : implementation of the CRulerBarDoc class
//

#include "stdafx.h"
#include "RulerBar.h"

#include "RulerBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulerBarDoc

IMPLEMENT_DYNCREATE(CRulerBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CRulerBarDoc, CDocument)
	//{{AFX_MSG_MAP(CRulerBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRulerBarDoc construction/destruction

CRulerBarDoc::CRulerBarDoc()
{
	// TODO: add one-time construction code here

}

CRulerBarDoc::~CRulerBarDoc()
{
}

BOOL CRulerBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRulerBarDoc serialization

void CRulerBarDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CRulerBarDoc diagnostics

#ifdef _DEBUG
void CRulerBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRulerBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRulerBarDoc commands
