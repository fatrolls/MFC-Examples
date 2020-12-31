// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "caption.h"

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

void CChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CDocument* pDoc = GetActiveDocument();

	if (bAddToTitle && pDoc != NULL)
	{
		CString strCurCaption, strWindowText, strNewCaption;

		// Get the current child window caption text
		GetWindowText(strCurCaption);

		// Get the special view name through the view's window text
		GetActiveView()->GetWindowText(strWindowText);

		// Get the doc name attached to this window
		const CString& strDocTitle = pDoc->GetTitle();

		// generate our new window caption
		strNewCaption = strDocTitle;
    if(m_nWindow > 0){
    	strNewCaption += ":";
		  CString temp;
      temp.Format("%d",m_nWindow);
      strNewCaption += temp;
    }
    if(!strWindowText.IsEmpty()){
    	strNewCaption += " - ";
		  strNewCaption += strWindowText;
    }
    if(pDoc->IsModified())strNewCaption += "*";

		// Only switch to the new caption if it differs from the old
		// (this reduces flicker--MFC uses AfxSetCaption)
		if (strNewCaption != strCurCaption)
			SetWindowText(strNewCaption);
	}

	// give the MDI frame window a chance to update its title

	GetMDIFrame()->OnUpdateFrameTitle(bAddToTitle);
}
