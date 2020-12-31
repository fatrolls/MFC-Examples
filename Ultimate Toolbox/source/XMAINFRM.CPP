// ==========================================================================
// 							Class Implementation : COXMainFrame
// ==========================================================================

// Source file : xmainfrm.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"			// standard MFC include
#include "xmainfrm.h"		// class specification

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXMainFrame, CMDIFrameWnd)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:
	// COXMDIClient			m_XMDIClient
	// --- The subclassed MDI Client.
	//     All messages (like WM_ERASEBACKGROUND,...)meant for the old MDI Client
	//	   will now pass through this new MDI CLIENT

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXMainFrame::COXMainFrame()
	: m_pWindowPlacement(NULL)
	{
	}
	
BOOL COXMainFrame::CreateClient(LPCREATESTRUCT lpCreateStruct, CMenu* pWindowMenu)
	{
	if (CMDIFrameWnd::CreateClient(lpCreateStruct, pWindowMenu))
    	{
       	// Messages meant for the MDICLIENT have to pass our class First
		// the m_hWndMDIClient is a fixed existing handle of the CMDIFrameWnd
       	m_XMDIClient.SubclassWindow(m_hWndMDIClient); 
        
        return TRUE;
    	}

    return FALSE;
	}

void COXMainFrame::InitialShowWindow(WINDOWPLACEMENT& windowPlacement, UINT nCmdShow)
	{
	m_pWindowPlacement = &windowPlacement;
	
	if (m_pWindowPlacement->length == 0)
		ShowWindow(nCmdShow);
	else
		{
		if (nCmdShow != SW_SHOWNORMAL)
			m_pWindowPlacement->showCmd = nCmdShow;
		
		SetWindowPlacement(m_pWindowPlacement);
		ShowWindow(m_pWindowPlacement->showCmd);
		}
	}

BOOL COXMainFrame::GetPaletteState()
	{
	return m_XMDIClient.GetPaletteState();
	}

BOOL COXMainFrame::SetPaletteState(BOOL bBackGround /* = TRUE */)
	{
	return m_XMDIClient.SetPaletteState(bBackGround);
	}

BOOL COXMainFrame::SetWallPaper(COLORREF rgbColor /* = RGB(192, 192, 192) */,
	EWallOrg eWallOrganisation /* = WP_Center */, COXDIB* pDib /* = NULL */)
	{
	return m_XMDIClient.SetNewBackGround(rgbColor, eWallOrganisation, pDib);
	}

COXMainFrame::~COXMainFrame()
	{
	}
	
#ifdef _DEBUG
void COXMainFrame::AssertValid() const
	{
	CMDIFrameWnd::AssertValid();
	}

void COXMainFrame::Dump(CDumpContext& dc) const
	{
	CMDIFrameWnd::Dump(dc);
	
	dc << TEXT("\nm_pWindowPlacement") << (const void*)m_pWindowPlacement;
	dc << TEXT("\nm_XMDIClient") << (const void*)&m_XMDIClient;
	}

#endif //_DEBUG

// protected:


// Message handlers ---------------------------------------------------------
BEGIN_MESSAGE_MAP(COXMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(COXMainFrame)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void COXMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
	{
	CMDIFrameWnd::OnPaletteChanged(pFocusWnd);

	// always realize the palette for the active view
	CMDIChildWnd* pMDIChildWnd = MDIGetActive();
	CView* pView = NULL;
	if (pMDIChildWnd != NULL)
		{
		pView = pMDIChildWnd->GetActiveView();
		ASSERT(pView != NULL);

		// notify all child windows that the palette has changed
		SendMessageToDescendants(WM_DOREALIZE, (WPARAM)pView->m_hWnd);
		}

	// notify the special MDI Client that the palette has changed
  	m_XMDIClient.SendMessage(WM_DOMDICLTREALIZE, (WPARAM)this, (LPARAM)pFocusWnd->m_hWnd);
	}

BOOL COXMainFrame::OnQueryNewPalette()
	{
	// always realize the palette for the active view
	CMDIChildWnd* pMDIChildWnd = MDIGetActive();
	if (pMDIChildWnd == NULL)
		return FALSE; // no active MDI child frame (no new palette)
	
	CView* pView = pMDIChildWnd->GetActiveView();
	ASSERT(pView != NULL);

	// just notify the target view
	pView->SendMessage(WM_DOREALIZE, (WPARAM)pView->m_hWnd);
	return TRUE;
	}

void COXMainFrame::OnClose()
	{
	if (m_pWindowPlacement != NULL)
		{
		// before it is destroyed, save the position of the window
		m_pWindowPlacement->length = sizeof(*m_pWindowPlacement);
		if (GetWindowPlacement(m_pWindowPlacement))
			{
			m_pWindowPlacement->flags = 0;
			if (IsZoomed())
				m_pWindowPlacement->flags |= WPF_RESTORETOMAXIMIZED;
			}
		}
			
	CMDIFrameWnd::OnClose();
	}

void COXMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
	{
	CMDIFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// notify the special MDI Client that the palette could have changed
	m_XMDIClient.SendMessage(WM_DOMDICLTREALIZE, (WPARAM)m_hWnd, (LPARAM)m_hWnd);
	}

