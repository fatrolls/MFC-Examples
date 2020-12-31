// SizeViewBar.cpp : implementation file
//

#include "stdafx.h"
#include "scribble.h"
#include "SizeViewBar.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSizeViewBar
IMPLEMENT_DYNCREATE(CSizeViewBar, CMRCSizeControlBar)


CSizeViewBar::CSizeViewBar() : CMRCSizeControlBar(SZBARF_DESTROY_ON_CLOSE | SZBARF_AUTOTIDY | SZBARF_STDMOUSECLICKS)
{
	m_pChildView = NULL;
}

CSizeViewBar::~CSizeViewBar()
{
}


BEGIN_MESSAGE_MAP(CSizeViewBar, CMRCSizeControlBar)
	//{{AFX_MSG_MAP(CSizeViewBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSizeViewBar message handlers

int CSizeViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMRCSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}


//-------------------------------------------------------------------
void CSizeViewBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	CRect rect(0, 0, cx, cy);		// rectangle for client area
	
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	
	// shrink rectangle if we're docked
	if (IsProbablyFloating())
    {
        rect.InflateRect(-2, -2);		// shrink for border when floating
    }
    else
		rect.InflateRect(-4, -4);

	if (m_pChildView != NULL && m_pChildView->m_hWnd != NULL)
		m_pChildView->MoveWindow(&rect);
}





IMPLEMENT_DYNAMIC(CSizeBarDocTemplate, CMultiDocTemplate)

CSizeBarDocTemplate::CSizeBarDocTemplate(UINT nID, CRuntimeClass* pDocClass,
										 CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
										 :CMultiDocTemplate(nID, pDocClass, pFrameClass, pViewClass)
{
}


CDocument* CSizeBarDocTemplate::OpenDocumentFile(LPCTSTR lpszPathName,
	BOOL bMakeVisible)
{
	CDocument* pDocument = CreateNewDocument();
	if (pDocument == NULL)
	{
		TRACE0("CDocTemplate::CreateNewDocument returned NULL.\n");
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}
	ASSERT_VALID(pDocument);

	BOOL bAutoDelete = pDocument->m_bAutoDelete;
	pDocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
	
	// Create the bar, and put the view in it
	CSizeViewBar * pBar = new CSizeViewBar();
	CMainFrame * pMainFrame = (CMainFrame *)AfxGetMainWnd();
	ASSERT(pMainFrame != NULL);
	VERIFY(pBar->Create(NULL, 
						   NULL,
						   WS_VISIBLE | WS_CHILD | CBRS_BOTTOM | WS_CLIPCHILDREN ,
						  CFrameWnd::rectDefault,
						pMainFrame, 0xE808));
	
 	// Create the view 
	
	CView* pView = (CView*)m_pViewClass->CreateObject();
	if (pView == NULL)
	{
		TRACE1("Warning: Dynamic create of view type %hs failed.\n",
			m_pViewClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(CWnd, pView);

	// views are always created with a border!
	CCreateContext ccontext;
	ccontext.m_pCurrentDoc = pDocument;
	
	if (!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0,0,0,0), pBar, -1 /*AFX_IDW_PANE_FIRST*/ , &ccontext))
	{
		TRACE0("Warning: could not create view for frame.\n");
		return NULL;        // can't continue without a view
	}

	
	//if (afxData.bWin4 && (pView->GetExStyle() & WS_EX_CLIENTEDGE))
	//{
		// remove the 3d style from the frame, since the view is
		//  providing it.
		// make sure to recalc the non-client area
	//	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
	//} 
	pBar->m_pChildView = pView;
	pBar->EnableDocking(CBRS_ALIGN_ANY);
	pMainFrame->DockControlBar(pBar);

	pDocument->m_bAutoDelete = bAutoDelete;

	if (lpszPathName == NULL)
	{
		// create a new document - with default document name
		SetDefaultTitle(pDocument);

		// avoid creating temporary compound file when starting up invisible
		if (!bMakeVisible)
			pDocument->m_bEmbedded = TRUE;

		if (!pDocument->OnNewDocument())
		{
			// user has be alerted to what failed in OnNewDocument
			TRACE0("CDocument::OnNewDocument returned FALSE.\n");
			//pFrame->DestroyWindow();
			return NULL;
		}

		// it worked, now bump untitled count
		m_nUntitledCount++;
	}
	else
	{
		// open an existing document
		CWaitCursor wait;
		if (!pDocument->OnOpenDocument(lpszPathName))
		{
			// user has be alerted to what failed in OnOpenDocument
			TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
			//pFrame->DestroyWindow();
			return NULL;
		}
#ifdef _MAC
		// if the document is dirty, we must have opened a stationery pad
		//  - don't change the pathname because we want to treat the document
		//  as untitled
		if (!pDocument->IsModified())
#endif
			pDocument->SetPathName(lpszPathName);
	}

    // set title for control bar
    pBar->SetWindowText(pDocument->GetTitle());

    //InitialUpdateFrame(pFrame, pDocument, bMakeVisible);
	if (bMakeVisible)
	{
		// send initial update to all views (and other controls) in the frame
		pBar->SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

		// give view a chance to save the focus (CFormView needs this)
		//if (pView != NULL)
		//	pView->OnActivateFrame(WA_INACTIVE, this);

		//if (pView != NULL)
		//	pView->OnActivateView(TRUE, pView, pView);
	}

	// update frame counts and frame title (may already have been visible)
	if (pDocument != NULL)
		pDocument->UpdateFrameCounts();
	
	return pDocument; 
}


CFrameWnd* CSizeBarDocTemplate::CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther)
// window NEW can't work for us.
{
	return NULL;
}
