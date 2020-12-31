// $$child_frame_ifile$$.cpp : implementation of the $$CHILD_FRAME_CLASS$$ class
//

#include "stdafx.h"
#include "$$root$$.h"

#include "$$child_frame_hfile$$.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$CHILD_FRAME_CLASS$$

IMPLEMENT_DYNCREATE($$CHILD_FRAME_CLASS$$, $$CHILD_FRAME_BASE_CLASS$$)

BEGIN_MESSAGE_MAP($$CHILD_FRAME_CLASS$$, $$CHILD_FRAME_BASE_CLASS$$)
	//{{AFX_MSG_MAP($$CHILD_FRAME_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
$$ENDIF
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// $$CHILD_FRAME_CLASS$$ construction/destruction

$$CHILD_FRAME_CLASS$$::$$CHILD_FRAME_CLASS$$()
{
$$IF(VERBOSE)
	// TODO: add member initialization code here
	
$$ENDIF
}

$$CHILD_FRAME_CLASS$$::~$$CHILD_FRAME_CLASS$$()
{
}
$$IF(SPLITTER_MDI)

BOOL $$CHILD_FRAME_CLASS$$::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
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

BOOL $$CHILD_FRAME_CLASS$$::PreCreateWindow(CREATESTRUCT& cs)
{
$$IF(VERBOSE)
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

$$ENDIF //VERBOSE
$$IF(CHILD_FRAME_STYLES)
	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE$$CHILD_FRAME_STYLE_FLAGS$$;

$$ENDIF //CHILD_FRAME_STYLES
	return $$CHILD_FRAME_BASE_CLASS$$::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// $$CHILD_FRAME_CLASS$$ diagnostics

#ifdef _DEBUG
void $$CHILD_FRAME_CLASS$$::AssertValid() const
{
	$$CHILD_FRAME_BASE_CLASS$$::AssertValid();
}

void $$CHILD_FRAME_CLASS$$::Dump(CDumpContext& dc) const
{
	$$CHILD_FRAME_BASE_CLASS$$::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// $$CHILD_FRAME_CLASS$$ message handlers
