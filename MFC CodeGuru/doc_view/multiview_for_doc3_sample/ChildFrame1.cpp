// ChildFrame1.cpp : implementation file
//

#include "stdafx.h"
#include "MvTest.h"
#include "ChildFrame1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame1

IMPLEMENT_DYNCREATE(CChildFrame1, CMDIChildWnd)

CChildFrame1::CChildFrame1()
{
}

CChildFrame1::~CChildFrame1()
{
}


BEGIN_MESSAGE_MAP(CChildFrame1, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame1)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame1 message handlers

BOOL CChildFrame1::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style &= ~(LONG)FWS_ADDTOTITLE;
	cs.style &= ~(LONG)WS_MAXIMIZEBOX;
	cs.style &= ~(LONG)WS_MINIMIZEBOX;

	return CMDIChildWnd::PreCreateWindow(cs);
}
