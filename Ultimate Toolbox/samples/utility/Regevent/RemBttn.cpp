// RemBttn.cpp : implementation file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#include "stdafx.h"
#include "RegEvent.h"
#include "RemBttn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemBttn

CRemBttn::CRemBttn()
{
	m_bClick = FALSE;
}

CRemBttn::~CRemBttn()
{
}


BEGIN_MESSAGE_MAP(CRemBttn, CButton)
	//{{AFX_MSG_MAP(CRemBttn)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemBttn message handlers

void CRemBttn::OnLButtonDown(UINT nFlags, CPoint point)
// Called when the user presses the left mouse button. Member m_bClick set to TRUE.
// If previous focus was in the list of watched keys, CRegEventDlg::OnKillfocusKeylist()
// function sets m_bClick to FALSE. This lets to keep "Remove Watch" button enabled
// when user kills focus from the list of watched keys.
{
	m_bClick = TRUE;
	CButton::OnLButtonDown(nFlags, point);
}
