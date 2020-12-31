//********************************************
// ChildFrm.cpp
//********************************************
// pierre.alliez@cnet.francetelecom.fr
// Created :
// Modified
//********************************************


#include "stdafx.h"
#include "Tool.h"

#include "RenderView.h"
#include "FormCommandView.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

//********************************************
// OnCreateClient
//********************************************
BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	if (!m_wndSplitter.CreateStatic(this, 1, 2,WS_CHILD | WS_VISIBLE))
  {
		TRACE("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

  // First splitter pane
  if (!m_wndSplitter.CreateView(0, 0,
      RUNTIME_CLASS(CFormCommandView), CSize(200,200), pContext))
  {
		TRACE("Failed to create command view pane\n");
    return FALSE;
  }

  // Second splitter pane
  if (!m_wndSplitter.CreateView(0, 1,
      RUNTIME_CLASS(CRenderView), CSize(200,200), pContext))
  {
    TRACE("Failed to create preview pane\n");
    return FALSE;
  }

	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnPaint() 
{
	CPaintDC dc(this); 

}
