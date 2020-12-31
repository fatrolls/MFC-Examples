// cdxCSizingDialog.cpp : implementation file
// (c)1998 Hans Bühler, codex design
// Designed to be used with MS VC++ 5.0

#define OEMRESOURCE
#include	<windows.h>

#include "stdafx.h"
#include "cdxCSizingDialog.h"

#ifndef OBM_SIZE
#define	OBM_SIZE		32766
// taken from WinresRc.h
// if not used for any reason
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Some static variables
/////////////////////////////////////////////////////////////////////////////

static LPCTSTR	pfEntry_Left	=	_T("Left"),
					pfEntry_Right	=	_T("Right"),
					pfEntry_Top		=	_T("Top"),
					pfEntry_Bottom	=	_T("Bottom"),
					pfEntry_State	=	_T("State"),
					pfEntry_IsDone	=	_T("(check)");

#define	BAD_ID	((UINT)~0)
static struct cdxCSizingPropSheet::StandardControls	psheetCtrls[]	=
{
	{	ID_WIZNEXT,		cdxCSizingDialog::mdRepos,cdxCSizingDialog::mdRepos	},
	{	ID_WIZFINISH,	cdxCSizingDialog::mdRepos,cdxCSizingDialog::mdRepos	},
	{	ID_WIZBACK,		cdxCSizingDialog::mdRepos,cdxCSizingDialog::mdRepos	},
	{	IDOK,				cdxCSizingDialog::mdRepos,cdxCSizingDialog::mdRepos	},
	{	IDCANCEL,		cdxCSizingDialog::mdRepos,cdxCSizingDialog::mdRepos	},
	{	ID_WIZNEXT,		cdxCSizingDialog::mdRepos,cdxCSizingDialog::mdRepos	},
	{	ID_APPLY_NOW,	cdxCSizingDialog::mdRepos,cdxCSizingDialog::mdRepos	},
	{	IDHELP,			cdxCSizingDialog::mdRepos,cdxCSizingDialog::mdRepos	},
	{	AFX_IDC_TAB_CONTROL,	cdxCSizingDialog::mdResize,cdxCSizingDialog::mdResize	},
	{	ID_WIZFINISH+1,cdxCSizingDialog::mdResize,cdxCSizingDialog::mdRepos},	/* the bevel line; hope that it will keep this id */
	{	BAD_ID	}
};

/////////////////////////////////////////////////////////////////////////////
// cdxCSizingDialog::ControlInfo::Header
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Functions for my windowos
/////////////////////////////////////////////////////////////////////////////

/*
 * OnInitDialog()
 * Gets initial sizes of the window and makes sizing icon
 */

BOOL cdxCSizingDialog::ControlInfo::Header::OnInitDialog(UINT addSzByPcnt)
{
	ASSERT(IsValid() && (m_iClientWid == -1));

	CRect					r;
	WINDOWPLACEMENT	wpl;

	m_pWnd->GetClientRect(&r);
	m_iClientWid	=	r.right - r.left;
	m_iClientHi	=	r.bottom - r.top;

	m_pWnd->GetWindowPlacement(&wpl);
	m_iMinWid	=	wpl.rcNormalPosition.right - wpl.rcNormalPosition.left;
	m_iMinHi		=	wpl.rcNormalPosition.bottom - wpl.rcNormalPosition.top;

	// set up sizing icon

	if(m_bSizeIcon)
	{
		if(!m_bmSizeIcon.LoadOEMBitmap(OBM_SIZE))
		{
			TRACE0(_T("*** ERROR[cdxCSizingDialog::ControlInfo::Header::OnInitDialog()]: LoadOEMBitmap() failed.\n"));
			m_bSizeIcon	=	false;
		}
		else
		{
			CRect	szr(r.Width()-24,r.Height()-24,r.Width(),r.Height());
			if(!m_wndSizeIcon.Create(NULL,WS_CHILD|SS_BITMAP,szr,m_pWnd) ||
				!m_wndSizeIcon.ModifyStyleEx(0,WS_EX_TRANSPARENT) )
			{
				TRACE0(_T("*** ERROR[cdxCSizingDialog::ControlInfo::Header::OnInitDialog()]: Can't create static icon control\n"));
				m_bSizeIcon	=	false;
			}
			else
			{
				m_wndSizeIcon.SetBitmap(m_bmSizeIcon);

				// now the icon has been resized to the real size of the icon

				if(!m_wndSizeIcon.GetWindowPlacement(&wpl))
				{
					TRACE0(_T("*** ERROR[cdxCSizingDialog::ControlInfo::Header::OnInitDialog()]: Can't get windowplacement for sizeicon.\n"));
					m_bSizeIcon	=	false;
				}
				else
				{
					wpl.flags	=	0;
					wpl.rcNormalPosition.left	=	r.Width() - (wpl.rcNormalPosition.right - wpl.rcNormalPosition.left);
					wpl.rcNormalPosition.right	=	r.Width();
					wpl.rcNormalPosition.top	=	r.Height() - (wpl.rcNormalPosition.bottom - wpl.rcNormalPosition.top);
					wpl.rcNormalPosition.bottom=	r.Height();
					if(!m_wndSizeIcon.SetWindowPlacement(&wpl))
					{
						TRACE0(_T("*** ERROR[cdxCSizingDialog::ControlInfo::Header::OnInitDialog()]: Can't set windowplacement for sizeicon.\n"));
						m_bSizeIcon	=	false;
					}
					else
					{
						AddSzControl(m_wndSizeIcon,mdRepos,mdRepos);
						m_wndSizeIcon.ShowWindow(SW_SHOW);		// finally - show it
					}
				}
			}
		}
	}

	if(addSzByPcnt)
		StretchWindow(addSzByPcnt);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

/*
 * OnSize() handler
 * Call before base classes' handler
 */

void cdxCSizingDialog::ControlInfo::Header::OnSize(UINT nType, int cx, int cy) 
{
	if((nType != SIZE_MINIMIZED) && (m_iClientWid != -1))
	{
		ASSERT((m_pWnd != NULL) && ::IsWindow(m_pWnd->m_hWnd));
		ChangeSize(cx,cy);
	}
}

/*
 * tell system what minimum size we have
 * call past original function
 */

void cdxCSizingDialog::ControlInfo::Header::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	ASSERT(m_pWnd != NULL);

	if(::IsWindow(m_pWnd->m_hWnd) && (m_iClientWid != -1))
	{
		lpMMI->ptMinTrackSize.x	=	m_iMinWid;
		lpMMI->ptMinTrackSize.y	=	m_iMinHi;
		if(!(m_Freedom & fdVert))
			lpMMI->ptMaxTrackSize.y	=	m_iMinHi;
		if(!(m_Freedom & fdHoriz))
			lpMMI->ptMaxTrackSize.x	=	m_iMinWid;
	}
}

/////////////////////////////////////////////////////////////////////////////

/*
 * this _really_ sizes/positions the controls
 * call RedrawWindow() afterwards !
 */

bool cdxCSizingDialog::ControlInfo::Header::ChangeSize(int newWid, int newHi)
{
	if(!IsValid() || (m_iClientWid == -1))
		return false;

	register int	deltaX	=	newWid - m_iClientWid,
						deltaY	=	newHi - m_iClientHi;
	bool				ok	=	true;

	if(deltaX < 0)
	{
		ok	=	false;
		deltaX	=	0;
	}

	if(deltaY < 0)
	{
		deltaY	=	0;
		ok	=	false;
	}

	for(register ControlInfo *ci = m_pFirst; ci; ci = ci->GetNext())
		ci->AdaptControlSize(deltaX,deltaY);
	m_pWnd->RedrawWindow();

	return ok;
}

/*
 * force recalculation
 */

bool cdxCSizingDialog::ControlInfo::Header::ReorganizeControls(void)
{
	ASSERT(IsValid());
	CRect	r;
	m_pWnd->GetClientRect(&r);
	return ChangeSize(r.Width(), r.Height());
}

/*
 * resize dialog in all available directions
 */

void cdxCSizingDialog::ControlInfo::Header::StretchWindow(UINT addSzByPcnt)
{
	ASSERT(IsValid());

	register int		delta;
	WINDOWPLACEMENT	wpl;

	if(!m_pWnd->GetWindowPlacement(&wpl))
	{
#ifdef _DEBUG
		CString	s;m_pWnd->GetWindowText(s);
		if(s.IsEmpty())
			s.Format(_T("<Address_0x%lx"),(UINT)this);
		TRACE1(_T("*** ERROR[cdxCSizingDialog::ControlInfo::Header::StretchWindow()]: GetWindowPlacement() failed for dialog with caption \"%s\" !\n"),(LPCSTR)s);
#endif
		return;
	}

	if(addSzByPcnt && (m_Freedom & fdHoriz))
	{
		delta	=	((wpl.rcNormalPosition.right - wpl.rcNormalPosition.left) * addSzByPcnt) / (100/2);
		if((wpl.rcNormalPosition.left -=	delta) < 0)
			wpl.rcNormalPosition.left	=	0;
		wpl.rcNormalPosition.right += delta;
	}
	if(addSzByPcnt && (m_Freedom & fdVert))
	{
		delta	=	((wpl.rcNormalPosition.bottom - wpl.rcNormalPosition.top) * addSzByPcnt) / (100/2);
		if((wpl.rcNormalPosition.top -=	delta) < 0)
			wpl.rcNormalPosition.top	=	0;
		wpl.rcNormalPosition.bottom += delta;
	}
	wpl.flags	=	0;
	m_pWnd->SetWindowPos(&wndBottom,	wpl.rcNormalPosition.left,
												wpl.rcNormalPosition.top,
												wpl.rcNormalPosition.right - wpl.rcNormalPosition.left,
												wpl.rcNormalPosition.bottom - wpl.rcNormalPosition.top,
												SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOREDRAW|SWP_NOZORDER);
}


/////////////////////////////////////////////////////////////////////////////
// cdxCSizingDialog::ControlInfo::Header utility functions: Sizing
/////////////////////////////////////////////////////////////////////////////

/*
 * add a control that might be resized or repositioned
 * (simple)
 */

cdxCSizingDialog::ControlInfo *cdxCSizingDialog::ControlInfo::Header::AddSzControl(CWnd & ctrl, Mode modeX, Mode modeY)
{
	BYTE	dX1pcnt	=	exIgnore,
			dX2pcnt	=	exIgnore,
			dY1pcnt	=	exIgnore,
			dY2pcnt	=	exIgnore;

	switch(modeX)
	{
		default	:			ASSERT(false);	
		case	mdNone	:	break;
		case	mdRepos	:	dX1pcnt	=	dX2pcnt	=	exMaximum;
								break;
		case	mdResize	:	dX2pcnt	=	exMaximum;
								break;
		case	mdRelative:	dX1pcnt	=	dX2pcnt	=	exMaximum / 2;
								break;
	}

	switch(modeY)
	{
		default	:			ASSERT(false);	
		case	mdNone	:	break;
		case	mdRepos	:	dY1pcnt	=	dY2pcnt	=	exMaximum;
								break;
		case	mdResize	:	dY2pcnt	=	exMaximum;
								break;
		case	mdRelative:	dY1pcnt	=	dY2pcnt	=	exMaximum / 2;
								break;
	}

	return AddSzControlEx(ctrl,dX1pcnt,dX2pcnt,dY1pcnt,dY2pcnt);
}

/*
 * add a control that might be resized or repositioned
 * (ex)
 */

cdxCSizingDialog::ControlInfo *cdxCSizingDialog::ControlInfo::Header::AddSzControlEx(CWnd & ctrl, BYTE dX1pcnt, BYTE dX2pcnt, BYTE dY1pcnt, BYTE dY2pcnt)
{
	if(!IsValid() || !::IsWindow(ctrl.m_hWnd) || (m_iClientWid == -1))
	{
		ASSERT(m_iClientWid != -1);		// call cdxCSizingDialog::InitDialog() first !
		ASSERT(::IsWindow(ctrl.m_hWnd));	// that's not a valid control !
		return NULL;
	}

	if((dX1pcnt == exIgnore) && (dX2pcnt == exIgnore) &&
		(dY1pcnt == exIgnore) && (dY2pcnt == exIgnore) )
	{
#ifdef _DEBUG
		CString	s;ctrl.GetWindowText(s);
		if(s.IsEmpty())
			s.Format(_T("No caption; <Address_0x%lx"),(UINT)&ctrl);
		TRACE1(_T("*** WARNING[cdxCSizingDialog::ControlInfo::Header::AddSzControl()]: For control \"%s\", all modifcators are set to NONE (control will not be added).\n"),(LPCTSTR)s);
#endif
		return NULL;
	}

	//
	// check whether we have useful values;
	// NOTE exMaximum == 100
	//

	ASSERT((dX1pcnt <= exMaximum) && (dX2pcnt <= exMaximum) && (dY1pcnt <= exMaximum) && (dY2pcnt <= exMaximum));

	ControlInfo	*ci;

	if(!( ci = new ControlInfo(*this,ctrl,dX1pcnt,dX2pcnt,dY1pcnt,dY2pcnt) ))
	{
		ASSERT(false);
		AfxThrowMemoryException();
	}
	CRect	r;m_pWnd->GetClientRect(&r);
	ci->AdaptControlSize(r.Width() - m_iClientWid,r.Height() - m_iClientHi);
	return ci;
}

/////////////////////////////////////////////////////////////////////////////
// Additional utilities
/////////////////////////////////////////////////////////////////////////////

/*
 * store window position to registry
 */

bool cdxCSizingDialog::ControlInfo::Header::StoreWindowPosition(const CString & profileSec)
{
	ASSERT(IsValid() && !profileSec.IsEmpty());	// can't use an empty profile section string; see CWinApp::GetProfileInt() for further information

	if(m_iClientWid != -1)
	{
		WINDOWPLACEMENT	wpl;

		if(!m_pWnd->GetWindowPlacement(&wpl))
			return false;

		return	AfxGetApp()->WriteProfileInt(profileSec,	pfEntry_IsDone,	~const_IsDone) &&	// invalidate first
					AfxGetApp()->WriteProfileInt(profileSec,	pfEntry_Left,		wpl.rcNormalPosition.left) &&
					AfxGetApp()->WriteProfileInt(profileSec,	pfEntry_Right,		wpl.rcNormalPosition.right) &&
					AfxGetApp()->WriteProfileInt(profileSec,	pfEntry_Top,		wpl.rcNormalPosition.top) &&
					AfxGetApp()->WriteProfileInt(profileSec,	pfEntry_Bottom,	wpl.rcNormalPosition.bottom) &&
					AfxGetApp()->WriteProfileInt(profileSec,	pfEntry_State,		wpl.showCmd) &&
					AfxGetApp()->WriteProfileInt(profileSec,	pfEntry_IsDone,	const_IsDone);		// validate position
	}
	return false;
}

/*
 * Load window position from registry
 */

bool cdxCSizingDialog::ControlInfo::Header::RestoreWindowPosition(const CString & profileSec, bool withState)
{
	ASSERT(IsValid() && !profileSec.IsEmpty());	// can't use an empty profile section string; see CWinApp::GetProfileInt() for further information

	WINDOWPLACEMENT	wpl;
	bool					ok;

	if(!m_pWnd->GetWindowPlacement(&wpl))
	{
#ifdef _DEBUG
		CString	s;m_pWnd->GetWindowText(s);
		if(s.IsEmpty())
			s.Format(_T("<Address_0x%lx"),(UINT)this);
		TRACE1(_T("*** ERROR[cdxCSizingDialog::ControlInfo::Header::RestoreWindowPosition()]: GetWindowPlacement() failed for dialog with caption \"%s\" !\n"),(LPCSTR)s);
#endif
		return false;
	}

	//
	// first, we check whether the position had been saved successful any time before
	//

	if( ok = (AfxGetApp()->GetProfileInt(profileSec,pfEntry_IsDone,0) == const_IsDone) )
	{
		// load previus session

		wpl.rcNormalPosition.left		=	AfxGetApp()->GetProfileInt(profileSec,	pfEntry_Left,		wpl.rcNormalPosition.left);
		wpl.rcNormalPosition.right		=	AfxGetApp()->GetProfileInt(profileSec,	pfEntry_Right,		wpl.rcNormalPosition.right);
		wpl.rcNormalPosition.top		=	AfxGetApp()->GetProfileInt(profileSec,	pfEntry_Top,		wpl.rcNormalPosition.top);
		wpl.rcNormalPosition.bottom	=	AfxGetApp()->GetProfileInt(profileSec,	pfEntry_Bottom,	wpl.rcNormalPosition.bottom);
		wpl.showCmd							=	AfxGetApp()->GetProfileInt(profileSec,	pfEntry_State,		wpl.showCmd);

		if(!withState)
			wpl.showCmd	=	0;

		ok	=	m_pWnd->SetWindowPlacement(&wpl) != FALSE;
	}

	return ok;
}

/////////////////////////////////////////////////////////////////////////////
// cdxCSizingDialog::ControlInfo
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// construction
/////////////////////////////////////////////////////////////////////////////

/*
 * class basics
 */

cdxCSizingDialog::ControlInfo::ControlInfo(Header & hd, CWnd & wnd, BYTE dX1pcnt, BYTE dX2pcnt, BYTE dY1pcnt, BYTE dY2pcnt)
:	m_rHeader(hd), m_Link(wnd), m_dX1pcnt(dX1pcnt), m_dX2pcnt(dX2pcnt), m_dY1pcnt(dY1pcnt), m_dY2pcnt(dY2pcnt)
{
	WINDOWPLACEMENT	wpl;
	wnd.GetWindowPlacement(&wpl);
	
	m_X1	=	wpl.rcNormalPosition.left;
	m_Y1	=	wpl.rcNormalPosition.top;
	m_X2	=	wpl.rcNormalPosition.right;
	m_Y2	=	wpl.rcNormalPosition.bottom;

	if(m_pNext = hd)
		m_pNext->m_pPrev	=	this;
	m_pPrev	=	NULL;
	hd			=	this;
}

cdxCSizingDialog::ControlInfo::~ControlInfo()
{
	m_Link.Empty();		// delete all equal controls

	if(!m_pPrev)
	{
		ASSERT( ((ControlInfo *)m_rHeader) == this);		// should be mine :)
		if(m_rHeader = m_pNext)
			m_pNext->m_pPrev	=	NULL;
	}
	else
	{
		if(m_pPrev->m_pNext = m_pNext)
			m_pNext->m_pPrev	=	m_pPrev;
	}
}

/////////////////////////////////////////////////////////////////////////////

void cdxCSizingDialog::ControlInfo::AddEqualCtrl(CWnd & ctrl)
{
	if(!( new EqualCtrl(m_Link,ctrl) ))
	{
		ASSERT(false);
		AfxThrowMemoryException();
	}
}

/////////////////////////////////////////////////////////////////////////////
// do something :)
/////////////////////////////////////////////////////////////////////////////

/*
 * action
 */

void cdxCSizingDialog::ControlInfo::AdaptControlSize(register int deltaX, register int deltaY)
{
	ASSERT((deltaX >= 0) && (deltaY >= 0));
	register int	x1,y1,x2,y2,i;

	// NOTE: Resizing is even needed if both values are zero
	// (to resize the controls to their default position)

	x1	=	m_X1;
	y1	=	m_Y1;
	x2	=	m_X2;
	y2	=	m_Y2;

	if(deltaX)
	{
		if(i = m_dX1pcnt)			// NOTE exIgnore == 0
			x1	+=	(deltaX * i) / 100;
		if(i = m_dX2pcnt)			// NOTE exIgnore == 0
			x2	+=	(deltaX * i) / 100;
	}

	if(deltaY)
	{
		if(i = m_dY1pcnt)			// NOTE exIgnore == 0
			y1	+=	(deltaY * i) / 100;
		if(i = m_dY2pcnt)			// NOTE exIgnore == 0
			y2	+=	(deltaY * i) / 100;
	}
	
	for(register EqualCtrl *ec = &m_Link; ec; ec = ec->GetNext())
	{
		if(::IsWindow(ec->GetCtrl().m_hWnd))
		{
#ifdef _DEBUG
			ASSERT( ec->GetCtrl().SetWindowPos(&wndTop,x1,y1,x2-x1,y2-y1,SWP_NOREDRAW|SWP_NOZORDER) );
#else
			ec->GetCtrl().SetWindowPos(&wndTop,x1,y1,x2-x1,y2-y1,SWP_NOREDRAW|SWP_NOZORDER);
#endif
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// cdxCSizingDialog dialog
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// construction
/////////////////////////////////////////////////////////////////////////////

void cdxCSizingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cdxCSizingDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(cdxCSizingDialog, CDialog)
	//{{AFX_MSG_MAP(cdxCSizingDialog)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cdxCSizingDialog message handlers
/////////////////////////////////////////////////////////////////////////////

/*
 * set up dialog; this function MUST be called before you add any controls
 * NOTE: The real OnInitDialog() virtual function calls this one by using
 * DEF_STRETCH as a addSzByPcntValue.
 * This value automatically grows the size of the dialog (therefore it
 * won't appear in minimum height what I assume to be worse looking).
 * Call it with a value of 0 to make it as small as you designed it
 * in the resource editor.
 */

BOOL cdxCSizingDialog::OnInitDialog(UINT addSzByPcnt) 
{
	CDialog::OnInitDialog();
	return m_Controls.OnInitDialog(addSzByPcnt);
}

/*
 * perform window sizing and adaption of controls
 */

void cdxCSizingDialog::OnSize(UINT nType, int cx, int cy) 
{
	m_Controls.OnSize(nType,cx,cy);
	CDialog::OnSize(nType, cx, cy);
}

/*
 * tell system what minimum size we have
 */

void cdxCSizingDialog::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CDialog::OnGetMinMaxInfo(lpMMI);
	m_Controls.OnGetMinMaxInfo(lpMMI);
}

/////////////////////////////////////////////////////////////////////////////
// Additional utilities
/////////////////////////////////////////////////////////////////////////////

/*
 * pump all messages for this window
 * call it during lengthy operations to ensure
 * sizing takes place
 */

void cdxCSizingDialog::PumpMessages(void)
{
	// Must call Create() before using the dialog
	ASSERT(::IsWindow(m_hWnd));

	MSG msg;
	// Handle dialog messages for all windows 
	while(::PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE))
	{
		if(!CDialog::IsDialogMessage(&msg))		// not used by our dialog
		{
			::TranslateMessage(&msg);				// pass to application
			::DispatchMessage(&msg);  
		}
	}
}





/////////////////////////////////////////////////////////////////////////////
// cdxCSizingPropSheet
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(cdxCSizingPropSheet, CPropertySheet)

/////////////////////////////////////////////////////////////////////////////
// creation etc.
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(cdxCSizingPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(cdxCSizingPropSheet)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cdxCSizingPropSheet message handlers

/*
 * setup controls
 */

BOOL cdxCSizingPropSheet::OnInitDialog(UINT addSzByPcnt) 
{
	BOOL bResult = CPropertySheet::OnInitDialog();	
	m_Controls.OnInitDialog(addSzByPcnt);

	//
	// now we like to add all pages
	//

	int	i;
	CWnd	*w	=	CPropertySheet::GetActivePage(),
			*helpBut	=	NULL;

	if(!w || !::IsWindow(w->m_hWnd))
	{
		ASSERT(false);
		// ugly...
		// it will work but will even look quite ugly.
		// reason: No page !
	}
	else
	{
		cdxCSizingDialog::ControlInfo	*ci;
		ci	=	m_Controls.AddSzControl(*w,cdxCSizingDialog::mdResize,cdxCSizingDialog::mdResize);
		if(ci)
		{
			CWnd	*ow;
			for(i=0; i<CPropertySheet::GetPageCount(); ++i)
				if(ow = CPropertySheet::GetPage(i))
					ci->AddEqualCtrl(*ow);		// thus they'll be sized the same way :)
		}
	}

	//
	// add buttons, tab and bevel line
	//
	
	for(i=0; psheetCtrls[i].id != BAD_ID; ++i)
	{
		if(w = CPropertySheet::GetDlgItem(psheetCtrls[i].id))
		{
			if(psheetCtrls[i].id == IDHELP)
			{
				ASSERT(helpBut == NULL);		// only one ?
				helpBut	=	w;
			}
			m_Controls.AddSzControl(*w,psheetCtrls[i].modeX,psheetCtrls[i].modeY);
		}
		else
		{
			TRACE1(_T("*** WARNING[cdxCSizingPropSheet::OnInitDialog()]: Can't find CWnd for ID#%ld !\n"),psheetCtrls[i].id);
		}
	}

	if(helpBut && (w = m_Controls.GetSizeIconCtrl()))
		w->SetWindowPos(helpBut,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);

	return bResult;
}


/*
 * add sizing style
 */

int cdxCSizingPropSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	ModifyStyle(0,WS_THICKFRAME|WS_SYSMENU);
	return 0;
}

/*
 * change size
 */

void cdxCSizingPropSheet::OnSize(UINT nType, int cx, int cy) 
{
	CPropertySheet::OnSize(nType, cx, cy);
	m_Controls.OnSize(nType,cx,cy);
}

void cdxCSizingPropSheet::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CPropertySheet::OnGetMinMaxInfo(lpMMI);
	m_Controls.OnGetMinMaxInfo(lpMMI);
}

/*
 * our overload
 */

void cdxCSizingPropSheet::AddPage( cdxCSizingPropPage & rPage )
{
	CPropertySheet::AddPage(&rPage);
	rPage.Init(*this);
}

/////////////////////////////////////////////////////////////////////////////
// cdxCSizingPropPage
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(cdxCSizingPropPage,CPropertyPage);

/////////////////////////////////////////////////////////////////////////////
// cdxCSizingDialog message handlers
/////////////////////////////////////////////////////////////////////////////

void cdxCSizingPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cdxCSizingPropPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(cdxCSizingPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(cdxCSizingPropPage)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cdxCSizingPropPage basics
/////////////////////////////////////////////////////////////////////////////

BOOL cdxCSizingPropPage::OnInitDialog() 
{
	BOOL	bOk	=	CPropertyPage::OnInitDialog();
	m_Controls.OnInitDialog(0);
	
	return bOk;
}

void cdxCSizingPropPage::OnSize(UINT nType, int cx, int cy) 
{
	m_Controls.OnSize(nType,cx,cy);
	CPropertyPage::OnSize(nType, cx, cy);
}
