// SpiderList.cpp : implementation of the CSpiderList class
//

#include "stdafx.h"
#include "Spider.h"
#include "ThreadParams.h"
#include "Thread.h"

#include "SpiderDoc.h"
#include "SpiderList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpiderList

IMPLEMENT_DYNCREATE(CSpiderList, CListView)

BEGIN_MESSAGE_MAP(CSpiderList, CListView)
	//{{AFX_MSG_MAP(CSpiderList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
	ON_MESSAGE(WM_USER_CHECK_DONE,OnUpDateURL)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpiderList construction/destruction

CSpiderList::CSpiderList()
{

}

CSpiderList::~CSpiderList()
{
}

BOOL CSpiderList::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style = (cs.style & ~LVS_TYPEMASK) | LVS_REPORT;
	cs.style |= LVS_AUTOARRANGE;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSpiderList drawing

void CSpiderList::OnDraw(CDC* pDC)
{
	CSpiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CSpiderList::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	CListCtrl& listView = GetListCtrl();
	listView.SetBkColor( RGB(255,255,255) );  // set bk color to white


}
CSpiderList * CSpiderList::GetView()
{
  
	CMDIChildWnd * pChild =
          ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
 
      if ( !pChild )
	  	  return NULL;
 
      CView * pView = pChild->GetActiveView();
 
      if ( !pView )	  return NULL;
 
      // Fail if view is of wrong kind
      if ( ! pView->IsKindOf( RUNTIME_CLASS(CSpiderList) ) )
	  return NULL;
 
      return (CSpiderList *) pView;
   }

/////////////////////////////////////////////////////////////////////////////
// CSpiderList printing

BOOL CSpiderList::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSpiderList::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSpiderList::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSpiderList diagnostics

#ifdef _DEBUG
void CSpiderList::AssertValid() const
{
	CListView::AssertValid();
}

void CSpiderList::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CSpiderDoc* CSpiderList::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpiderDoc)));
	return (CSpiderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpiderList message handlers

BOOL CSpiderList::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	BOOL bCreated = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	if ( bCreated )
	{
		CListCtrl& listView = GetListCtrl();

		listView.InsertColumn( 0,_T("URL"), LVCFMT_LEFT,275,0 );
		listView.InsertColumn( 1,_T("Status"), LVCFMT_LEFT,150,0 );
		listView.InsertColumn( 2,_T("Type"), LVCFMT_LEFT,75, 0 );
		listView.InsertColumn( 3,_T("Size"), LVCFMT_LEFT,75, 0 );
		listView.InsertColumn( 4,_T("Modified"), LVCFMT_LEFT,200, 0 );


	}
	return bCreated;

}



LRESULT CSpiderList::OnUpDateURL(WPARAM wParam,LPARAM lParam) 
{
	CListCtrl& list = GetListCtrl();
	int nListEntries = list.GetItemCount();
	PURLStatus newEntry = (PURLStatus) lParam;

	if(newEntry->m_URL.IsEmpty()) return 0;

	list.InsertItem(nListEntries,newEntry->m_URL);
	list.SetItemText(nListEntries,1,newEntry->m_StatusString);
	list.SetItemText(nListEntries,2,newEntry->m_ContentType);
	list.SetItemText(nListEntries,3,newEntry->m_ContentLength);
	list.SetItemText(nListEntries,4,newEntry->m_LastModified);

	
	return 0;
}

