// VisualStudioLikeDemoDoc.cpp : implementation of the CVisualStudioLikeDemoDoc class
//

#include "stdafx.h"
#include "VisualStudioLikeDemo.h"

#include "VisualStudioLikeDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoDoc

IMPLEMENT_DYNCREATE(CVisualStudioLikeDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CVisualStudioLikeDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CVisualStudioLikeDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoDoc construction/destruction

CVisualStudioLikeDemoDoc::CVisualStudioLikeDemoDoc()
{
	// TODO: add one-time construction code here

}

CVisualStudioLikeDemoDoc::~CVisualStudioLikeDemoDoc()
{
}

BOOL CVisualStudioLikeDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoDoc serialization

void CVisualStudioLikeDemoDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoDoc diagnostics

#ifdef _DEBUG
void CVisualStudioLikeDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVisualStudioLikeDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoDoc commands
