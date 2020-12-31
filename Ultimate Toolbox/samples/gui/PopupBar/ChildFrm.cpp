// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "PopupBar.h"
#include "MainFrm.h"

#include "PopupBarDoc.h"
#include "PopupBarView.h"
#include "ChildFrm.h"

#include <afxpriv.h>

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
	ON_WM_GETMINMAXINFO()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	m_bModal=FALSE;
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

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default

	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);

	CClientDC dc(this);
	ASSERT(&dc);

	CFont* pFont=dc.GetCurrentFont();
	ASSERT(pFont);

	CRect rect(0,0,1,1);
	dc.DrawText(_T("Second Quater"),rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_CALCRECT);

	CSize minTextSize=rect.Size();

	lpMMI->ptMinTrackSize.x=2*ID_EDGE_MARGIN+3*ID_BORDER_MARGIN+
		4*ID_TEXT_MARGIN+2*minTextSize.cx;
	lpMMI->ptMinTrackSize.y=2*ID_EDGE_MARGIN+3*ID_BORDER_MARGIN+
		4*ID_TEXT_MARGIN+2*minTextSize.cy;
}

void CChildFrame::SetModal(BOOL bModal)
{
	ASSERT(m_hWnd != NULL);
	ASSERT(::IsWindow(m_hWnd));

	if(bModal)
	{
		ASSERT(m_arrHandles.GetSize()==0);

		DisableWindows(AfxGetMainWnd()->GetSafeHwnd());
	}
	else 
	{
		for(int nIndex=0; nIndex<m_arrHandles.GetSize(); nIndex++)
		{
			HWND hWnd=(HWND)m_arrHandles.GetAt(nIndex);
			::EnableWindow(hWnd, TRUE);
		}
		m_arrHandles.RemoveAll();
	}

	m_bModal=bModal;
}


void CChildFrame::DisableWindows(HWND hWnd)
{
	while (hWnd != NULL)
	{
		if (::IsWindowEnabled(hWnd) && !AfxIsDescendant(hWnd,m_hWnd) && 
			!AfxIsDescendant(m_hWnd,hWnd) && m_hWnd!=hWnd)
		{
			CWnd* pWnd=CWnd::FromHandle(hWnd);
			if(pWnd->IsKindOf(RUNTIME_CLASS(CChildFrame)))
			{
				::EnableWindow(hWnd, FALSE);
				m_arrHandles.Add((void*)hWnd);
			}
		}
		DisableWindows(::GetWindow(hWnd,GW_CHILD));
		hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
	}
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	if(((CMainFrame*)AfxGetMainWnd())->m_bModal)
		SetModal(TRUE);

	return 0;
}

void CChildFrame::OnDestroy() 
{
	if(IsModal())
		SetModal(FALSE);
	((CMainFrame*)AfxGetMainWnd())->MDINext();

	CMDIChildWnd::OnDestroy();

}

