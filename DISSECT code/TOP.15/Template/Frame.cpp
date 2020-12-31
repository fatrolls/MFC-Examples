// $$frame_ifile$$.cpp : implementation of the $$FRAME_CLASS$$ class
//

#include "stdafx.h"
#include "$$root$$.h"

#include "$$frame_hfile$$.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$FRAME_CLASS$$

$$IF(PROJTYPE_MDI)
IMPLEMENT_DYNAMIC($$FRAME_CLASS$$, $$FRAME_BASE_CLASS$$)
$$ELSE
IMPLEMENT_DYNCREATE($$FRAME_CLASS$$, $$FRAME_BASE_CLASS$$)
$$ENDIF

BEGIN_MESSAGE_MAP($$FRAME_CLASS$$, $$FRAME_BASE_CLASS$$)
	//{{AFX_MSG_MAP($$FRAME_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
$$ENDIF
$$IF(TOOLBAR || STATUSBAR)
	ON_WM_CREATE()
$$ENDIF //TOOLBAR || STATUSBAR
	//}}AFX_MSG_MAP
$$IF(HELP)
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, $$FRAME_BASE_CLASS$$::OnHelpFinder)
	ON_COMMAND(ID_HELP, $$FRAME_BASE_CLASS$$::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, $$FRAME_BASE_CLASS$$::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, $$FRAME_BASE_CLASS$$::OnHelpFinder)
$$ENDIF
END_MESSAGE_MAP()
$$IF(STATUSBAR)

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
$$IF(DO_KANA)
	ID_INDICATOR_KANA,
$$ENDIF	// DO_KANA
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
$$ENDIF //STATUSBAR

/////////////////////////////////////////////////////////////////////////////
// $$FRAME_CLASS$$ construction/destruction

$$FRAME_CLASS$$::$$FRAME_CLASS$$()
{
$$IF(VERBOSE)
	// TODO: add member initialization code here
	
$$ENDIF
}

$$FRAME_CLASS$$::~$$FRAME_CLASS$$()
{
}
$$IF(TOOLBAR || STATUSBAR)

int $$FRAME_CLASS$$::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if ($$FRAME_BASE_CLASS$$::OnCreate(lpCreateStruct) == -1)
		return -1;
$$IF(TOOLBAR)
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
$$ENDIF //TOOLBAR
$$IF(STATUSBAR)

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
$$ENDIF //STATUSBAR
$$IF(TOOLBAR)

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
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
$$ENDIF //TOOLBAR	

	return 0;
}
$$ENDIF //TOOLBAR || STATUSBAR
$$IF(SPLITTER_SDI)

BOOL $$FRAME_CLASS$$::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	return m_wndSplitter.Create( this,
$$IF(VERBOSE)
		2, 2,                 // TODO: adjust the number of rows, columns
		CSize( 10, 10 ),      // TODO: adjust the minimum pane size
$$ELSE //!VERBOSE
		2, 2,
		CSize( 10, 10 ),
$$ENDIF //VERBOSE
		pContext );
}
$$ENDIF //SPLITTER

BOOL $$FRAME_CLASS$$::PreCreateWindow(CREATESTRUCT& cs)
{
$$IF(VERBOSE)
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

$$ENDIF //VERBOSE
$$IF(FRAME_STYLES)
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		$$FRAME_STYLE_FLAGS$$;

$$ENDIF //FRAME_STYLES
	return $$FRAME_BASE_CLASS$$::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// $$FRAME_CLASS$$ diagnostics

#ifdef _DEBUG
void $$FRAME_CLASS$$::AssertValid() const
{
	$$FRAME_BASE_CLASS$$::AssertValid();
}

void $$FRAME_CLASS$$::Dump(CDumpContext& dc) const
{
	$$FRAME_BASE_CLASS$$::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// $$FRAME_CLASS$$ message handlers
