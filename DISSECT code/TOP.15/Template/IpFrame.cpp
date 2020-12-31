// $$ipframe_ifile$$.cpp : implementation of the $$IPFRAME_CLASS$$ class
//

#include "stdafx.h"
#include "$$root$$.h"

#include "$$ipframe_hfile$$.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$IPFRAME_CLASS$$

IMPLEMENT_DYNCREATE($$IPFRAME_CLASS$$, $$IPFRAME_BASE_CLASS$$)

BEGIN_MESSAGE_MAP($$IPFRAME_CLASS$$, $$IPFRAME_BASE_CLASS$$)
	//{{AFX_MSG_MAP($$IPFRAME_CLASS$$)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
$$IF(INSTALLED_MAC)
#ifdef _MAC
	ON_WM_DESTROY()
#endif
$$ENDIF
$$IF(HELP)
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, $$IPFRAME_BASE_CLASS$$::OnHelpFinder)
	ON_COMMAND(ID_HELP, $$IPFRAME_BASE_CLASS$$::OnHelp)
	ON_COMMAND(ID_DEFAULT_HELP, $$IPFRAME_BASE_CLASS$$::OnHelpFinder)
	ON_COMMAND(ID_CONTEXT_HELP, $$IPFRAME_BASE_CLASS$$::OnContextHelp)
$$ENDIF
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// $$IPFRAME_CLASS$$ construction/destruction

$$IPFRAME_CLASS$$::$$IPFRAME_CLASS$$()
{
}

$$IPFRAME_CLASS$$::~$$IPFRAME_CLASS$$()
{
}

int $$IPFRAME_CLASS$$::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if ($$IPFRAME_BASE_CLASS$$::OnCreate(lpCreateStruct) == -1)
		return -1;

$$IF(INSTALLED_MAC)
#ifdef _MAC
$$IF(VERBOSE)
	// enable built-in Macintosh OLE resizing support.
$$ENDIF
	SetProp(m_hWnd, "Owner", m_hWnd);
#else
$$ENDIF
$$IF(VERBOSE)
	// CResizeBar implements in-place resizing.
$$ENDIF
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // fail to create
	}
$$IF(INSTALLED_MAC)
#endif
$$ENDIF

$$IF(VERBOSE)
	// By default, it is a good idea to register a drop-target that does
	//  nothing with your frame window.  This prevents drops from
	//  "falling through" to a container that supports drag-drop.
$$ENDIF
	m_dropTarget.Register(this);

	return 0;
}

$$IF(TOOLBAR)
$$IF(VERBOSE)
// OnCreateControlBars is called by the framework to create control bars on the
//  container application's windows.  pWndFrame is the top level frame window of
//  the container and is always non-NULL.  pWndDoc is the doc level frame window
//  and will be NULL when the container is an SDI application.  A server
//  application can place MFC control bars on either window.
$$ENDIF
BOOL $$IPFRAME_CLASS$$::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
$$IF(VERBOSE)
	// Remove this if you use pWndDoc
$$ENDIF
	UNREFERENCED_PARAMETER(pWndDoc);

$$IF(VERBOSE)
	// Set owner to this window, so messages are delivered to correct app
$$ENDIF
	m_wndToolBar.SetOwner(this);

$$IF(VERBOSE)
	// Create toolbar on client's frame window
$$ENDIF
	if (!m_wndToolBar.Create(pWndFrame) ||
$$IF(PROJTYPE_MDI)
		!m_wndToolBar.LoadToolBar(IDR_$$DOC$$TYPE_SRVR_IP))
$$ELSE
		!m_wndToolBar.LoadToolBar(IDR_SRVR_INPLACE))
$$ENDIF
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

$$IF(VERBOSE)	
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
$$ENDIF
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

$$IF(VERBOSE)
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
$$ENDIF
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndToolBar);

	return TRUE;
}

$$ENDIF //TOOLBAR
BOOL $$IPFRAME_CLASS$$::PreCreateWindow(CREATESTRUCT& cs)
{
$$IF(VERBOSE)
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

$$ENDIF //VERBOSE
	return $$IPFRAME_BASE_CLASS$$::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// $$IPFRAME_CLASS$$ diagnostics

#ifdef _DEBUG
void $$IPFRAME_CLASS$$::AssertValid() const
{
	$$IPFRAME_BASE_CLASS$$::AssertValid();
}

void $$IPFRAME_CLASS$$::Dump(CDumpContext& dc) const
{
	$$IPFRAME_BASE_CLASS$$::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// $$IPFRAME_CLASS$$ commands
$$IF(INSTALLED_MAC)

#ifdef _MAC
void CInPlaceFrame::OnDestroy() 
{
	RemoveProp(m_hWnd, "Owner");
	COleIPFrameWnd::OnDestroy();
}
#endif
$$ENDIF
