#if !defined(AFX_CDXCSIZINGDIALOG_H__1D0F68C2_BF90_11D1_A589_444553540000__INCLUDED_)
#define AFX_CDXCSIZINGDIALOG_H__1D0F68C2_BF90_11D1_A589_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
//
// cdxCSizingDialog.h : header file
// --------------------------------
// Author:  Hans Bühler (hb@codex.ro), Germany/Berlin
//          codex design (http://wwww.codex.ro
// Version: 1.2
// Release: 1 (May 1998 to www.codeguru.com)
// ---------------------------------
// Comments welcome.

/*
 * cdxCSizingDialog[CDialog]
 * =========================
 * A CDialog dervied class that implements a sizable dialog class.

 HOW TO USE:

 - Create your dialog with the minimum size it should have.
   Even create a class for it:
	a) if you are able to use cdxCSizingDialog, use it as base class.
	b) otherwise, use CDialog;
	   open both the header and the implementation file and do a
		find/replace on CDialog => cdxCSizingDialog.
 - In the constructor of your class, use the Freedom parameter
   to decide in what direction (or both) your dialog should
	be changed in size.
	By default, the dialog would be sizable in both x and y direction.
 - If you don't want a little windows-standard sizing icon in your lower
	right corner, set the fourth parameter of the constructor to false.
 - In your OnInitDialog() routine,
   * first call cdxCSizingDialog::OnInitDialog(),
	* then use the AddSzControl() member function for any control that
     should handle window size change.
	  AddSzControl() will allow to reposition, resize and center
	  controls.
	  For more advanced use, have a look at AddSzControlEx().
 - If you use OnSize(), call the base class function first !!

 FURTHER UTILITIES:

 - PumpMessages() empties the windows message queue.
   Use it in lengthy operations to ensure the window will react
	on user size changes.
 - Use StoreWindowPosition() and RestoreWindowPosition() to save and
   load your window's size and position from the registry.

 *
 * (c)Mar.1998 Hans Bühler, codex design; hb@codex.ro | http://www.codex.ro
 *    Note usage license.
 */

class cdxCSizingDialog;
class cdxCSizingPropSheet;
class cdxCSizingPropPage;

/////////////////////////////////////////////////////////////////////////////
// cdxCSizingDialog dialog

class cdxCSizingDialog : public CDialog
{
	/*
	 * some constants
	 */

public:
	enum Mode		// flags for AddSzControl()
	{
		mdNone		=	0,		// does nothing
		mdResize		=	1,		// resize in that dimension
		mdRepos		=	2,		// reposition
		mdRelative	=	3,		// center (size by delta/2 and repos by delta/2)
		md__Num		=	4
	};

	enum Freedom	// for cdxSizingCDialog()
	{
		fdNone		=	0,		// might be used but I don't imagine what you want from this ??
		fdHoriz		=	0x01,				// horizantally sizable only
		fdVert		=	0x02,				// vertically sizable only
		fdAll			=	fdHoriz|fdVert	// sizable in all directions
	};

	enum ExConstants
	{
		exIgnore		=	0,		// ignore this AddSzControlEx() value
		exMaximum	=	100,	// modify coordinate by xnew = xdef + (delta * exMaximum)/dx
		DEF_STRETCH	=	10		// default stretch size
	};

	/*
	 * management storage classes
	 */

public:
	class ControlInfo
	{
	public:
		//
		// the real manager class
		//
		class Header
		{
		private:
			enum { const_IsDone = 0x7f7f };

		protected:
			ControlInfo	*m_pFirst;
			CWnd			*m_pWnd;			// Use Init() !!!!!!!!!
			int			m_iClientWid,m_iClientHi,
							m_iMinWid,m_iMinHi;
			Freedom		m_Freedom;
			CStatic		m_wndSizeIcon;		// the icon control
			CBitmap		m_bmSizeIcon;		// the bitmap
			bool			m_bSizeIcon;		// true if icon is displayed

		public:
			Header(Freedom fd, bool bSizeIcon) : m_pFirst(NULL), m_iClientWid(-1), m_Freedom(fd), m_bSizeIcon(bSizeIcon), m_pWnd(NULL) {}
			virtual ~Header() { Detach(); }

			bool IsValid(void) const { return (m_pWnd != NULL) && ::IsWindow(m_pWnd->m_hWnd); }

			void Init(CWnd & w) { ASSERT(m_pWnd == NULL); m_pWnd = &w; }
			void Detach(void) { while(m_pFirst) delete m_pFirst; }

			operator ControlInfo * () { return m_pFirst; }
			Header & operator=(ControlInfo *c) { m_pFirst = c; return *this; }

			// for our derived classes

			bool RestoreWindowPosition(const CString & profileSec, bool withState);
			bool StoreWindowPosition(const CString & profileSec);
			void StretchWindow(UINT addSzByPcnt);

			bool ReorganizeControls(void);		// call to reposition controls
			void PumpMessages(void);				// just an utility

			ControlInfo *AddSzControl(CWnd & ctrl, Mode modeX, Mode modeY);
			ControlInfo *AddSzControlEx(CWnd & ctrl, BYTE dX1pcnt, BYTE dX2pcnt, BYTE dY1pcnt, BYTE dY2pcnt);

			bool ChangeSize(int newWid, int newHi);

			BOOL OnInitDialog(UINT addSzByPcnt);
			void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
			void OnSize(UINT nType, int cx, int cy);

			// utility

			CStatic *GetSizeIconCtrl(void) { return m_bSizeIcon ? &m_wndSizeIcon : NULL; }
		};

		//
		// for mututally displayed equal sized controls
		// (size will be applied to all but visible)
		//

		class EqualCtrl
		{
		protected:
			EqualCtrl	*m_pNext;
			CWnd			& m_rCtrl;

		public:
			EqualCtrl(CWnd & w) : m_pNext(NULL), m_rCtrl(w) {}
			EqualCtrl(EqualCtrl & prev, CWnd & w) : m_pNext(NULL), m_rCtrl(w)
			{	
				EqualCtrl	*next	=	prev.m_pNext;
				prev.m_pNext = this;
				m_pNext = next;
			}
			virtual ~EqualCtrl()	{ Empty(); }

			CWnd & GetCtrl(void) { return m_rCtrl; }
			EqualCtrl *GetNext(void) { return m_pNext; }

			void Empty(void)  { if(m_pNext) delete m_pNext; m_pNext = NULL; }
		};

	protected:
		ControlInfo	*m_pNext,*m_pPrev;
		Header		& m_rHeader;
		EqualCtrl	m_Link;
		BYTE			m_dX1pcnt,m_dX2pcnt,
						m_dY1pcnt,m_dY2pcnt;	// percentage values of deltaX(Y) to add to coordinate
		DWORD			m_X1,m_Y1,m_X2,m_Y2;	// original positions

	public:
		ControlInfo(Header & hd, CWnd & wnd, BYTE dX1pcnt, BYTE dX2pcnt, BYTE dY1pcnt, BYTE dY2pcnt);
		virtual ~ControlInfo();

		ControlInfo *GetNext(void) { return m_pNext; }
		void AddEqualCtrl(CWnd & ctrl);
		void AdaptControlSize(register int deltaX, register int deltaY);
	};

	/*
	 * members
	 */

private:
	ControlInfo::Header	m_Controls;

	// Construction
protected:
	cdxCSizingDialog(UINT idd, CWnd* pParent = NULL, Freedom fd = fdAll, bool mkSizeIcon = true)
	:	CDialog(idd, pParent), m_Controls(fd,mkSizeIcon) {	m_Controls.Init(*this);	}
public:
	virtual ~cdxCSizingDialog() { DestroyWindow(); }

	// load/store window position to registry
	bool RestoreWindowPosition(const CString & profileSec, bool withState = false) { return m_Controls.RestoreWindowPosition(profileSec,withState); }
	bool StoreWindowPosition(const CString & profileSec) { return m_Controls.StoreWindowPosition(profileSec); }
	bool RestoreWindowPosition(UINT strId, bool withState = false) { CString s;s.LoadString(strId); return RestoreWindowPosition(s,withState); }
	bool StoreWindowPosition(UINT strId) { CString s;s.LoadString(strId); return StoreWindowPosition(s); }

	// stretch window size
	void StretchWindow(UINT addSzByPcnt = DEF_STRETCH) { m_Controls.StretchWindow(addSzByPcnt); }

	// reapply window size
	bool ReorganizeControls(void) { return m_Controls.ReorganizeControls(); }

	// process all messages of the dialog
	void PumpMessages(void);				// just an utility

	// detach controls
	virtual BOOL DestroyWindow(void) { m_Controls.Detach(); return CDialog::DestroyWindow(); }

	//
	// these are those functions you'll be interested in
	//
protected:
	void AddSzControl(CWnd & ctrl, Mode modeX = mdNone, Mode modeY = mdNone) { m_Controls.AddSzControl(ctrl,modeX,modeY); }
	void AddSzXControl(CWnd & ctrl, Mode modeX) { AddSzControl(ctrl,modeX,mdNone); }
	void AddSzYControl(CWnd & ctrl, Mode modeY) { AddSzControl(ctrl,mdNone,modeY); }
	void AddSzControlEx(CWnd & ctrl, BYTE dX1pcnt, BYTE dX2pcnt, BYTE dY1pcnt, BYTE dY2pcnt) { m_Controls.AddSzControlEx(ctrl,dX1pcnt,dX2pcnt,dY1pcnt,dY2pcnt); }
	void AddSzXControlEx(CWnd & ctrl, BYTE dX1pcnt, BYTE dX2pcnt) { AddSzControlEx(ctrl,dX1pcnt,dX2pcnt,exIgnore,exIgnore); }
	void AddSzYControlEx(CWnd & ctrl, BYTE dY1pcnt, BYTE dY2pcnt) { AddSzControlEx(ctrl,exIgnore,exIgnore,dY1pcnt,dY2pcnt); }

private:
	bool ChangeSize(int newWid, int newHi) { return m_Controls.ChangeSize(newWid,newHi); }

// Dialog Data
	//{{AFX_DATA(cdxCSizingDialog)
	enum { IDD = 0 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cdxCSizingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog(UINT addSzByPcnt);
	virtual BOOL OnInitDialog() { return OnInitDialog(DEF_STRETCH); }

	// Generated message map functions
	//{{AFX_MSG(cdxCSizingDialog)
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/*
 * cdxCSizingPropSheet
 * ===================
 * A friend class that even uses the facilities of a cdxCSizingDialog

 HOW TO USE:

 - Instead of CPropertySheet, derive your class from this class.
 - Derive all your pages from cdxCSizingPropPage, NOT from CPropertyPage.
 - Done :)

 */

class cdxCSizingPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(cdxCSizingPropSheet)

private:
	struct StandardControls
	{
		UINT							id;	// ID
		cdxCSizingDialog::Mode	modeX,modeY;
	};

	/*
	 * members
	 */

private:
	cdxCSizingDialog::ControlInfo::Header	m_Controls;

public:
	cdxCSizingPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, cdxCSizingDialog::Freedom fd = cdxCSizingDialog::fdAll, bool mkSizeIcon = false)
	:	CPropertySheet(nIDCaption, pParentWnd, iSelectPage), m_Controls(fd,mkSizeIcon) {	m_Controls.Init(*this); }
	cdxCSizingPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, cdxCSizingDialog::Freedom fd = cdxCSizingDialog::fdAll, bool mkSizeIcon = false)
	:	CPropertySheet(pszCaption, pParentWnd, iSelectPage), m_Controls(fd,mkSizeIcon) {	m_Controls.Init(*this); }
	virtual ~cdxCSizingPropSheet() { DestroyWindow(); }

	// window position in the registry
	bool RestoreWindowPosition(const CString & profileSec, bool withState = false) { return m_Controls.RestoreWindowPosition(profileSec,withState); }
	bool StoreWindowPosition(const CString & profileSec) { return m_Controls.StoreWindowPosition(profileSec); }
	bool RestoreWindowPosition(UINT strId, bool withState = false) { CString s;s.LoadString(strId); return RestoreWindowPosition(s,withState); }
	bool StoreWindowPosition(UINT strId) { CString s;s.LoadString(strId); return StoreWindowPosition(s); }
	// stretch window size
	void StretchWindow(UINT addSzByPcnt = 15) { m_Controls.StretchWindow(addSzByPcnt); }

	// reapply window size
	bool ReorganizeControls(void) { if(!m_Controls.ReorganizeControls()) return false; RedrawWindow(); return true; }

	// add a cdxCSizingPropPage to your sheet
	void AddPage( cdxCSizingPropPage *pPage ) { ASSERT(pPage != NULL); AddPage(*pPage); }
	void AddPage( cdxCSizingPropPage & rPage );

	virtual BOOL DestroyWindow(void) { m_Controls.Detach(); return CPropertySheet::DestroyWindow(); }

private:
	// please don't use this one !
	void AddPage( CPropertyPage *pPage ) { ASSERT(false); CPropertySheet::AddPage(pPage); }

// Operations
public:

// Overrides
	virtual BOOL OnInitDialog(UINT addSzByPcnt);
	virtual BOOL OnInitDialog() { return OnInitDialog(cdxCSizingDialog::DEF_STRETCH); }
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cdxCSizingPropSheet)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(cdxCSizingPropSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
 * cdxCSizingPropPage
 * ==================
 * Base class for all propertypages that are embedded into a
 * cdxCSizingPropSheet
 */

class cdxCSizingPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(cdxCSizingPropPage)

public:

private:
	cdxCSizingDialog::ControlInfo::Header	m_Controls;
	cdxCSizingPropSheet							*m_pSheet;

private:
	cdxCSizingPropPage()
		:	CPropertyPage(), m_Controls(cdxCSizingDialog::fdAll,false), m_pSheet(NULL) {}
public:
	cdxCSizingPropPage(UINT idd, UINT nIDCaption = 0)
		:	CPropertyPage(idd,nIDCaption), m_Controls(cdxCSizingDialog::fdAll,false), m_pSheet(NULL)  { m_Controls.Init(*this); }
	cdxCSizingPropPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0)
		:	CPropertyPage(lpszTemplateName,nIDCaption), m_Controls(cdxCSizingDialog::fdAll,false), m_pSheet(NULL)  { m_Controls.Init(*this); }
	virtual ~cdxCSizingPropPage() { DestroyWindow(); }

	//
	// these are used by the cdxCSizingPropSheet -- you never need to make use of them !
	//
	bool IsInitialized(void) const { return m_pSheet != NULL; }
	void Init(cdxCSizingPropSheet & ps) { ASSERT(m_pSheet == NULL); m_pSheet = &ps; }

	//
	// these are those functions you'll be interested in
	//
protected:
	void AddSzControl(CWnd & ctrl, cdxCSizingDialog::Mode modeX = cdxCSizingDialog::mdNone, cdxCSizingDialog::Mode modeY = cdxCSizingDialog::mdNone) { m_Controls.AddSzControl(ctrl,modeX,modeY); }
	void AddSzXControl(CWnd & ctrl, cdxCSizingDialog::Mode modeX) { AddSzControl(ctrl,modeX,cdxCSizingDialog::mdNone); }
	void AddSzYControl(CWnd & ctrl, cdxCSizingDialog::Mode modeY) { AddSzControl(ctrl,cdxCSizingDialog::mdNone,modeY); }
	void AddSzControlEx(CWnd & ctrl, BYTE dX1pcnt, BYTE dX2pcnt, BYTE dY1pcnt, BYTE dY2pcnt) { m_Controls.AddSzControlEx(ctrl,dX1pcnt,dX2pcnt,dY1pcnt,dY2pcnt); }
	void AddSzXControlEx(CWnd & ctrl, BYTE dX1pcnt, BYTE dX2pcnt) { AddSzControlEx(ctrl,dX1pcnt,dX2pcnt,cdxCSizingDialog::exIgnore,cdxCSizingDialog::exIgnore); }
	void AddSzYControlEx(CWnd & ctrl, BYTE dY1pcnt, BYTE dY2pcnt) { AddSzControlEx(ctrl,cdxCSizingDialog::exIgnore,cdxCSizingDialog::exIgnore,dY1pcnt,dY2pcnt); }

	// reapply current size
	bool ReorganizeControls(void) { if(!m_Controls.ReorganizeControls()) return false; RedrawWindow(); return true; }
	// get sheet
	cdxCSizingPropSheet & GetSheet(void) { VERIFY(m_pSheet != NULL); /* you must use a cdxCSizingPropSheet */ return *m_pSheet; }

	// I need these
	virtual BOOL OnSetActive(void) { BOOL bOk = CPropertyPage::OnSetActive(); if(IsInitialized()) m_pSheet->ReorganizeControls(); ReorganizeControls(); return bOk; }
	virtual BOOL DestroyWindow(void) { m_Controls.Detach(); return CPropertyPage::DestroyWindow(); }

// Dialog Data
	//{{AFX_DATA(cdxCSizingPropPage)
	enum { IDD = 0 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(cdxCSizingPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(cdxCSizingPropPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDXCSIZINGDIALOG_H__1D0F68C2_BF90_11D1_A589_444553540000__INCLUDED_)
