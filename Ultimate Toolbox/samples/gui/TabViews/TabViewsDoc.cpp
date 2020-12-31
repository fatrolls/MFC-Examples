// TabViewsDoc.cpp : implementation of the CTabViewsDoc class
//

#include "stdafx.h"
#include "TabViews.h"

#include "TabViewsDoc.h"
#include "TabViewsView.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabViewsDoc

IMPLEMENT_DYNCREATE(CTabViewsDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabViewsDoc, CDocument)
	//{{AFX_MSG_MAP(CTabViewsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabViewsDoc construction/destruction

CTabViewsDoc::CTabViewsDoc()
{
	// TODO: add one-time construction code here

}

CTabViewsDoc::~CTabViewsDoc()
{
}

BOOL CTabViewsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTabViewsDoc serialization

void CTabViewsDoc::Serialize(CArchive& ar)
{
	CTabViewsView* pPrimaryView=(CTabViewsView*)GetPrimaryView();
	ASSERT_VALID(pPrimaryView);
	pPrimaryView->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CTabViewsDoc diagnostics

#ifdef _DEBUG
void CTabViewsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabViewsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabViewsDoc commands

CEditView* CTabViewsDoc::GetPrimaryView()
{
	POSITION pos=m_viewList.GetHeadPosition(); 
	while(pos!=NULL)
	{
		CView* pView=(CView*)m_viewList.GetNext(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CTabViewsView)))
			return (CEditView*)pView;
	}

	return NULL;
}