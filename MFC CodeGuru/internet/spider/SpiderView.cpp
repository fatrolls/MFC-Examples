// SpiderView.cpp : implementation of the CSpiderView class
//

#include "stdafx.h"
#include "Spider.h"
#include "ThreadParams.h"
#include "SpiderDoc.h"
#include "SpiderView.h"
#include "utily.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CSpiderView

IMPLEMENT_DYNCREATE(CSpiderView, CEditView)

BEGIN_MESSAGE_MAP(CSpiderView, CEditView)
	//{{AFX_MSG_MAP(CSpiderView)
	ON_COMMAND(ID_TOOLS_SHOWURLS, OnToolsShowurls)
	ON_COMMAND(ID_TOOLS_STRIPHTML, OnToolsStripHTML)
	ON_COMMAND(ID_TOOLS_STRIPTEXT, OnToolsStripText)
	ON_COMMAND(ID_TOOLS_EMAILADDRESS, OnToolsEmailAddress)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_MESSAGE(WM_USER_CHECK_DONE,OnUpDateURL)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpiderView construction/destruction

CSpiderView::CSpiderView()
{

}

CSpiderView::~CSpiderView()
{
}

BOOL CSpiderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CSpiderView drawing

void CSpiderView::OnDraw(CDC* pDC)
{
	CSpiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSpiderView printing

BOOL CSpiderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CSpiderView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CSpiderView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CSpiderView diagnostics

#ifdef _DEBUG
void CSpiderView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSpiderView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CSpiderDoc* CSpiderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpiderDoc)));
	return (CSpiderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpiderView message handlers
CSpiderView * CSpiderView::GetView()
{
  
	CMDIChildWnd * pChild =
          ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
 
      if ( !pChild )
	  	  return NULL;
 
      CView * pView = pChild->GetActiveView();
 
      if ( !pView )	  return NULL;
 
      // Fail if view is of wrong kind
      if ( ! pView->IsKindOf( RUNTIME_CLASS(CSpiderView) ) )
	  return NULL;
 
      return (CSpiderView *) pView;
   }

void CSpiderView::OnToolsShowurls() 
{
	
	CStringList list;
	BOOL found=FALSE;

	LPCTSTR lpszText = LockBuffer();
	ASSERT(lpszText != NULL);
	UINT nLen = GetBufferLength();
	TRY
	{
		found= GetHref(lpszText,_T("href"),list);

	}
	CATCH_ALL(e)
	{
		UnlockBuffer();
		THROW_LAST();
	}
	END_CATCH_ALL
	UnlockBuffer();

	int count = list.GetCount();
	POSITION pos=NULL;
	CString str, rString="";

	if(found==TRUE && count>0)
	{
		for(int i=0; i<count; i++)
		{
			if( ( pos = list.FindIndex( i)) != NULL )
			{
				str = list.GetAt( pos );
				rString +=str;
				rString += "\r\n";

			}
		}
		GetEditCtrl().SetSel(0, -1);


		GetEditCtrl ().ReplaceSel( rString, TRUE );

	}
}

void CSpiderView::OnToolsStripHTML() 
{
	CStringList list;
	BOOL found=FALSE;

	LPCTSTR lpszText = LockBuffer();
	ASSERT(lpszText != NULL);
	UINT nLen = GetBufferLength();
	TRY
	{
		found= GetHTMLText(lpszText,list);

	}
	CATCH_ALL(e)
	{
		UnlockBuffer();
		THROW_LAST();
	}
	END_CATCH_ALL
	UnlockBuffer();

	int count = list.GetCount();
	POSITION pos=NULL;
	CString str, rString="";

	if(found==TRUE && count>0)
	{
		for(int i=0; i<count; i++)
		{
			if( ( pos = list.FindIndex( i)) != NULL )
			{
				str = list.GetAt( pos );
				rString +=str;
				rString += "\r\n";

			}
		}
		GetEditCtrl().SetSel(0, -1);


		GetEditCtrl ().ReplaceSel( rString, TRUE );

	}	
}

void CSpiderView::OnToolsStripText() 
{
	CStringList list;
	BOOL found=FALSE;

	LPCTSTR lpszText = LockBuffer();
	ASSERT(lpszText != NULL);
	UINT nLen = GetBufferLength();
	TRY
	{
		found= GetHTMLTags(lpszText,list);

	}
	CATCH_ALL(e)
	{
		UnlockBuffer();
		THROW_LAST();
	}
	END_CATCH_ALL
	UnlockBuffer();

	int count = list.GetCount();
	POSITION pos=NULL;
	CString str, rString="";

	if(found==TRUE && count>0)
	{
		for(int i=0; i<count; i++)
		{
			if( ( pos = list.FindIndex( i)) != NULL )
			{
				str = list.GetAt( pos );
				rString +=str;
				rString += "\r\n";

			}
		}
		GetEditCtrl().SetSel(0, -1);


		GetEditCtrl ().ReplaceSel( rString, TRUE );

	}	
}


void CSpiderView::OnToolsEmailAddress() 
{
	CStringList list;
	BOOL found=FALSE;

	LPCTSTR lpszText = LockBuffer();
	ASSERT(lpszText != NULL);
	UINT nLen = GetBufferLength();
	TRY
	{
		found= GetEmail(lpszText,_T("href"),list);

	}
	CATCH_ALL(e)
	{
		UnlockBuffer();
		THROW_LAST();
	}
	END_CATCH_ALL
	UnlockBuffer();

	int count = list.GetCount();
	POSITION pos=NULL;
	CString str, rString="";

	if(found==TRUE && count>0)
	{
		for(int i=0; i<count; i++)
		{
			if( ( pos = list.FindIndex( i)) != NULL )
			{
				str = list.GetAt( pos );
				rString +=str;
				rString += "\r\n";

			}
		}
		GetEditCtrl().SetSel(0, -1);


		GetEditCtrl ().ReplaceSel( rString, TRUE );

	}
	
}
BOOL CSpiderView::UpdateString (LPCTSTR lpString)
{
	
	CString rString;
	rString.Format("%s",lpString);
	rString +="\r\n";

	GetEditCtrl ().ReplaceSel( rString, TRUE );
	return TRUE;
}

LRESULT CSpiderView::OnUpDateURL(WPARAM wParam,LPARAM lParam) 
{

	LPCSTR prtline;;
	
	prtline = (LPCSTR)lParam;
	UpdateString(prtline);


	return 0;
}
