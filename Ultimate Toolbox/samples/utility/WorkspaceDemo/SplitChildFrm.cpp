// ==========================================================================
//				Class Implementation : CSplitChildFrame
// ==========================================================================

// Source file : SplitChildFrm.cpp

//====================================================================
//===============  Dundas Software ==================================
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WorkspaceDemo.h"
#include <afxpriv.h>	// For CDialogTemplate

#include "SplitChildFrm.h"
#include "WorkspaceGraphView.h"
#include "WorkspaceGraphPropView.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSplitChildFrame, CMDIChildWnd)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:

CSplitChildFrame::CSplitChildFrame()
	{
	ASSERT_VALID(this);
	}

BEGIN_MESSAGE_MAP(CSplitChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CSplitChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSplitChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
	{
	// create a splitter with 1 row, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		{
		TRACE0("CSplitChildFrame::OnCreateClient : Failed to CreateStaticSplitter\n");
		return FALSE;
		}

	// Get the size of the first pane (size of the resource)
	CSize firstSize(0,0);
	CSize secondSize(0,0);
	// Block : Dialog template
		{
		CDialogTemplate dlgTempl1;
		VERIFY(dlgTempl1.Load(MAKEINTRESOURCE(CWorkspaceGraphView::IDD)));
		dlgTempl1.GetSizeInPixels(&firstSize);

		CDialogTemplate dlgTempl2;
		VERIFY(dlgTempl2.Load(MAKEINTRESOURCE(CWorkspaceGraphPropView::IDD)));
		dlgTempl2.GetSizeInPixels(&secondSize);

		// Make same width and height
		if (firstSize.cx < secondSize.cx)
			firstSize.cx =  secondSize.cx;
		else
			secondSize.cx =  firstSize.cx;

		if (firstSize.cy < secondSize.cy)
			firstSize.cy =  secondSize.cy;
		else
			secondSize.cy =  firstSize.cy;
		}

	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0,
		pContext->m_pNewViewClass, firstSize, pContext))
		{
		TRACE0("CSplitChildFrame::OnCreateClient : Failed to create first pane\n");
		return FALSE;
		}

	// add the second splitter pane - an property view in column 1
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CWorkspaceGraphPropView), secondSize, pContext))
		{
		TRACE0("CSplitChildFrame::OnCreateClient : Failed to create second pane\n");
		return FALSE;
		}

	// activate the tree view
	SetActiveView((CView*)m_wndSplitter.GetPane(0,0));

	return TRUE;
	}

BOOL CSplitChildFrame::PreCreateWindow(CREATESTRUCT& cs)
	{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
	}

#ifdef _DEBUG
void CSplitChildFrame::AssertValid() const
	{
	CMDIChildWnd::AssertValid();
	}

void CSplitChildFrame::Dump(CDumpContext& dc) const
	{
	CMDIChildWnd::Dump(dc);
	}
#endif //_DEBUG

CSplitChildFrame::~CSplitChildFrame()
	{
	}

// protected:
// private:

// ==========================================================================


