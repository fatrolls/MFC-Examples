//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================


// StealthFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "StealthFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStealthFrame

IMPLEMENT_DYNCREATE(CStealthFrame, CPersistentFrameWnd)

CStealthFrame::CStealthFrame()
{
}

CStealthFrame::~CStealthFrame()
{
	//SAMPLE: added these lines to destroy our invisible owner when we're done

	if (m_wndOwner.m_hWnd != NULL)
		m_wndOwner.DestroyWindow();
	
	//SAMPLE: end of added lines
}


BEGIN_MESSAGE_MAP(CStealthFrame, CPersistentFrameWnd)
	//{{AFX_MSG_MAP(CStealthFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStealthFrame message handlers

BOOL CStealthFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	//SAMPLE: added these lines to create our invisible owner
//	cs.style = WS_OVERLAPPED | WS_CAPTION | 
//		WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	cs.dwExStyle &= ~(WS_EX_APPWINDOW);

	if (!CPersistentFrameWnd::PreCreateWindow(cs))
		return FALSE;

	// we have to check since PreCreateWindow may be called
	// more than once

	if (m_wndOwner.m_hWnd == NULL)
	{
		// we don't care about any attributes of our hidden window

		LPCTSTR pstrOwnerClass = AfxRegisterWndClass(0);

		if (!m_wndOwner.CreateEx(0, pstrOwnerClass, _T(""), WS_POPUP,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, 0))
			return FALSE;
	}

	// note that we _don't_ set WS_CHILD... making the _owner_
	// window of our frame some invisible window.

	cs.hwndParent = m_wndOwner.m_hWnd;

	// seticon
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_wndOwner.SetIcon(hIcon,TRUE);

	return TRUE;

	//SAMPLE: end of added lines

}
