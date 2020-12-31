// ChildFrame2.cpp : implementation file
//

#include "stdafx.h"
#include "MvTest.h"
#include "ChildFrame2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame2

IMPLEMENT_DYNCREATE(CChildFrame2, CMDIChildWnd)

CChildFrame2::CChildFrame2()
{
}

CChildFrame2::~CChildFrame2()
{
}


BEGIN_MESSAGE_MAP(CChildFrame2, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame2 message handlers

BOOL CChildFrame2::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style &= ~(LONG)FWS_ADDTOTITLE;
	cs.style |= (LONG)WS_VSCROLL;
	cs.style |= (LONG)WS_HSCROLL;
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
