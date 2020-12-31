// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "DIBManager.h"

#include "ChildFrm.h"

#include "MainFrm.h"
#include "DIBManagerDoc.h"
#include "ScaleRollupDlg.h"

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
	ON_WM_CREATE()
	ON_WM_DESTROY()
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

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,NULL,NULL,
		AfxGetApp()->LoadIcon(IDR_DIBMANTYPE));
	ASSERT(cs.lpszClass);

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

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_Caption.Attach(this);
	SendMessage(WM_NCPAINT);

	// when we create new child window we add info about it 
	// into TreeFilesBar docking control
	((CMainFrame*)GetMDIFrame())->
		m_TreeFilesBar.AddNewWindowToTree(this);
	
	return 0;
}

void CChildFrame::OnDestroy() 
{
	CMDIChildWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	CMainFrame* pMainFrame=(CMainFrame*)pApp->m_pMainWnd;

	// notify TreeFilesBar docking control that the child window is about 
	// to be destroyed and we have to remove info about the window
	pMainFrame->m_TreeFilesBar.RemoveWindowFromTree(this);

	// if we are about to destroy the last child window and 
	// roll-up ZoomLevel Dialog is active then destroy that dialog
	if(pMainFrame->m_bShowZoomLevelDlg && 
		pMainFrame->m_TreeFilesBar.m_TreeFiles.GetCount()==1)
	{
		CScaleRollupDlg *pScaleRollupDlg=pApp->GetScaleRollupDlg();
		pScaleRollupDlg->DestroyWindow();
		pMainFrame->m_bShowZoomLevelDlg=FALSE;
	}
}


LRESULT CChildFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	switch(message)
	{
	// when mainframe sets new title for the child window
	// we notify TreeFilesBar docking control about that
	case WM_SETTEXT:
		{
			((CMainFrame*)GetMDIFrame())->
				m_TreeFilesBar.SetTextForWindowInTree(this,
				(const CString&)(CString)((LPCSTR)lParam));
			break;
		}
	}
	
	return CMDIChildWnd::WindowProc(message, wParam, lParam);
}
