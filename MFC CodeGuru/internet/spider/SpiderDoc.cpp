// SpiderDoc.cpp : implementation of the CSpiderDoc class
//

#include "stdafx.h"
#include "Spider.h"

#include "SpiderDoc.h"
#include "SpiderView.h"
#include "SpiderList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpiderDoc

IMPLEMENT_DYNCREATE(CSpiderDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpiderDoc, CDocument)
	//{{AFX_MSG_MAP(CSpiderDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpiderDoc construction/destruction

CSpiderDoc::CSpiderDoc()
{

}

CSpiderDoc::~CSpiderDoc()
{

}

BOOL CSpiderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSpiderDoc serialization

void CSpiderDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSpiderDoc diagnostics

#ifdef _DEBUG
void CSpiderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpiderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpiderDoc commands

CSpiderDoc * CSpiderDoc::GetDoc()
{
      CMDIChildWnd * pChild =
          ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
 
      if ( !pChild )
          return NULL;
 
      CDocument * pDoc = pChild->GetActiveDocument();
 
      if ( !pDoc )
         return NULL;
 
      // Fail if doc is of wrong kind
      if ( ! pDoc->IsKindOf( RUNTIME_CLASS(CSpiderDoc) ) )
         return NULL;
 
      return (CSpiderDoc *) pDoc;
   }

BOOL CSpiderDoc::ShowURL(LPCTSTR lpString) 
{

	CSpiderView* pView = (CSpiderView*)m_viewList.GetHead();
	ASSERT_KINDOF(CSpiderView, pView);
	pView->GetEditCtrl ().ReplaceSel( lpString, TRUE );

	return TRUE;

}


BOOL CSpiderDoc::CheckURLUpdate (LPCTSTR lpString)
{
	
	CString rString;
	rString.Format("%s",lpString);
	rString +="\r\n";

	CSpiderView* pView = (CSpiderView*)m_viewList.GetHead();
	ASSERT_KINDOF(CSpiderView, pView);

	pView->GetEditCtrl ().ReplaceSel( rString, TRUE );

		return TRUE;
}

