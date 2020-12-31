// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Communicator.h"
#include "CommunicatorDoc.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
//	cs.style &= ~WS_MAXIMIZEBOX; 
	cs.style |= WS_MAXIMIZE;

	cs.style &= ~WS_MINIMIZEBOX; 
	
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClose() 
	{
	// Check whether there are documents that are still blocking
	// (and thus have started a second message loop)
	BOOL bBlocking = FALSE;

	POSITION pos;
	CDocTemplate* pDocTemplate;
	CCommunicatorDoc* pComDoc;

	// Get the one (and only) document template
	pos = AfxGetApp()->GetFirstDocTemplatePosition();
	// ... Should have at least one template
	ASSERT(pos != 0);
	pDocTemplate = AfxGetApp()->GetNextDocTemplate(pos);
	ASSERT(pDocTemplate != 0);
	// ... Should have exactly one template
	ASSERT(pos == 0);

	// Iterate all the documents
	pos = pDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
		{
		pComDoc = (CCommunicatorDoc*)pDocTemplate->GetNextDoc(pos);
		ASSERT(pComDoc != 0);
		ASSERT(pComDoc->IsKindOf(RUNTIME_CLASS(CCommunicatorDoc)));
		if (pComDoc->IsBlocking())
			{
			bBlocking = TRUE;
			pComDoc->CancelBlocking();
			}
		}

	// If blocking abort close and repost message
	if (bBlocking)
		{
		TRACE(_T("CMainFrame::OnClose : Detected communicators that are still blocking, cancelling blocking and reposting WM_CLOSE\n"));
		PostMessage(WM_CLOSE);
		}
	else
		CMDIFrameWnd::OnClose();
	}
