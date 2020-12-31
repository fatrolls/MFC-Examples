// multipad.cpp : Defines the class behaviors for the Multipad application.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "multipad.h"
#include "CustomizeDlg.h"
#include "CustomizeCaptionDlg.h"
#include <locale.h>

#include "UTSampleAbout.h"

CMultiPadApp NEAR theApp;
static HINSTANCE g_hRichEdDLL=NULL;

BEGIN_MESSAGE_MAP(CMultiPadApp, CWinApp)
	//{{AFX_MSG_MAP(CMultiPadApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)     // file commands...
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

BOOL CMultiPadApp::InitInstance()
{
	_tsetlocale(LC_ALL, _T(""));

	// Initialize RichEdit control
	// for About Dialog
	if(g_hRichEdDLL==NULL)
	{
		g_hRichEdDLL=::LoadLibrary(_T("RICHED32.DLL"));
		if(g_hRichEdDLL==NULL)
			TRACE(_T("Cannot load library to display RichEditTextControl"));
	}


#if _MSC_VER < 1400
	Enable3dControls();			// Call this when using MFC in a shared DLL
#endif

	// use registry if you want to save CoolToolBars state
	SetRegistryKey(_T("Ultimate Toolbox Samples"));

	LoadStdProfileSettings();

	AddDocTemplate(new CMultiDocTemplate(IDR_TEXTTYPE,
		RUNTIME_CLASS(CPadDoc), 
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CEditView)));
	m_pMainWnd = new CMainFrame;
	((CFrameWnd*)m_pMainWnd)->LoadFrame(IDR_MAINFRAME);
	
	// load saved workspace after all bars were created
	((CMainFrame*)m_pMainWnd)->LoadWorkspace();

	m_pMainWnd->ShowWindow(m_nCmdShow);

	// enable file manager drag/drop and DDE Execute open
	m_pMainWnd->DragAcceptFiles();
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	return TRUE;
}

void CMultiPadApp::OnAppAbout()
{
	CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	dlgAbout.DoModal();
}

int CMultiPadApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);

	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,NULL,NULL,
		AfxGetApp()->LoadIcon(IDR_TEXTTYPE));
	ASSERT(cs.lpszClass);

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_Caption.Attach(this);

	CMainFrame* pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pFrame);
	COXCaptionPainter parentCaption;
	if(::SendMessage(pFrame->m_hWnd,COXCaptionPainter::m_nGetCaptionPainter,0,
		(LPARAM)&parentCaption))
	{
		SendMessage(COXCaptionPainter::m_nSetCaptionPainter,0,(LPARAM)&parentCaption);
	}

	SendMessage(WM_NCPAINT);

	return 0;
}


IMPLEMENT_DYNCREATE(CMainFrame, CMDIFrameWnd)
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_COMMAND(ID_VIEW_CUSTOMIZE_CAPTION, OnViewCustomizeCaption)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_TOOLBAR_FILE, ID_VIEW_TOOLBAR_WINDOW, 
		OnUpdateViewToolbars)
	ON_COMMAND_RANGE(ID_VIEW_TOOLBAR_FILE, ID_VIEW_TOOLBAR_WINDOW, 
		OnViewToolbars)
END_MESSAGE_MAP()


// we need these arrays to make our CoolToolBars customizable
// we use them as parameters in function COXCoolToolBar::SetBitmapIds()

static UINT buttonsFile[] =
{
	ID_FILE_NEW, 
	ID_FILE_OPEN, 
	ID_FILE_CLOSE, 
	ID_FILE_SAVE, 
	ID_FILE_SAVE_AS, 
	ID_FILE_PRINT, 
	ID_APP_ABOUT,
};

static UINT buttonsEdit[] =
{
	ID_EDIT_CUT, 
	ID_EDIT_COPY, 
	ID_EDIT_PASTE, 
	ID_EDIT_CLEAR, 
	ID_EDIT_FIND, 
	ID_EDIT_REPEAT, 
};

static UINT buttonsWindow[] =
{
	ID_WINDOW_CASCADE,
	ID_WINDOW_TILE_HORZ,
	ID_WINDOW_ARRANGE,
};

static UINT indicators[] =
{
	ID_SEPARATOR, 
	ID_INDICATOR_CAPS, 
	ID_INDICATOR_NUM, 
	ID_INDICATOR_SCRL,
};

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CMDIFrameWnd::OnCreate(lpCreateStruct)==-1)
	{
		return -1;
	}

	// create standard statusbar 
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE(_T("Failed to create status bar\n"));
		return -1;      // fail to create
	}

	// create toolbars

	//////////////////////////////
	// File ToolBar
	// this is an example of simple toolbar without text
	// but we add here images to show in hot mode
	// Note that process of creation of CoolToolBar almost the same as
	// standard CToolBar
	if (!m_wndToolBarFile.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP,
		ID_VIEW_TOOLBAR_FILE) ||
		!m_wndToolBarFile.LoadToolBar(IDR_TOOLBAR_FILE))
		{
		TRACE(_T("Failed to create File toolbar\n"));
		return -1;      // fail to create
		} 
	// 	This function specifies the command ID's of the button images in the bitmap.
	m_wndToolBarFile.SetBitmapIds(buttonsFile, sizeof(buttonsFile)/sizeof(UINT));

	/////////////
	// COXCoolToolBar specific functions
	m_wndToolBarFile.IniSizes(CSize(16,16));
	m_wndToolBarFile.SetHotImageList(m_wndToolBarFile.AddImageList(IDR_TOOLBAR_FILE_HOT));
	m_wndToolBarFile.SetDefaultTextColor(RGB(0,0,128));
	m_wndToolBarFile.SetHotTextColor(RGB(0,0,255));
	m_wndToolBarFile.UpdateSizes();
	////////////

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBarFile.SetBarStyle(m_wndToolBarFile.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarFile.EnableDocking(CBRS_ALIGN_ANY);
	//////////////////////////////

	//////////////////////////////
	// Edit ToolBar
	if (!m_wndToolBarEdit.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP,
		ID_VIEW_TOOLBAR_EDIT) ||
		!m_wndToolBarEdit.LoadToolBar(IDR_TOOLBAR_EDIT))
		{
		TRACE(_T("Failed to create Edit toolbar\n"));
		return -1;      // fail to create
		} 
	// 	This function specifies the command ID's of the button images in the bitmap.
	m_wndToolBarEdit.SetBitmapIds(buttonsEdit, sizeof(buttonsEdit)/sizeof(UINT));

	/////////////
	// COXCoolToolBar specific functions
	m_wndToolBarEdit.IniSizes(CSize(16,16));
	m_wndToolBarEdit.SetHotImageList(m_wndToolBarEdit.AddImageList(IDR_TOOLBAR_EDIT_HOT));
	m_wndToolBarEdit.SetDefaultTextColor(RGB(0,0,128));
	m_wndToolBarEdit.SetHotTextColor(RGB(0,0,255));
	// we want to use text from string resource in our CoolToolBar
	m_wndToolBarEdit.SetButtonsMinMaxWidth(0,70);
	m_wndToolBarEdit.SetMaxTextRows(4);
	m_wndToolBarEdit.SetButtonTextFromID(COXCoolToolBar::TTID_PLAIN);
	m_wndToolBarEdit.UpdateSizes();
	////////////

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBarEdit.SetBarStyle(m_wndToolBarEdit.GetBarStyle() |
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	//////////////////////////////

	//////////////////////////////
	// Window ToolBar
	if (!m_wndToolBarWindow.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP,
		ID_VIEW_TOOLBAR_WINDOW) ||
		!m_wndToolBarWindow.LoadToolBar(IDR_TOOLBAR_WINDOW))
		{
		TRACE(_T("Failed to create Window toolbar\n"));
		return -1;      // fail to create
		} 
	// 	This function specifies the command ID's of the button images in the bitmap.
	m_wndToolBarWindow.SetBitmapIds(buttonsWindow, sizeof(buttonsWindow)/sizeof(UINT));

	/////////////
	// COXCoolToolBar specific functions
	// use CoolToolBar in List mode
	m_wndToolBarWindow.IniSizes(CSize(16,16));
	m_wndToolBarWindow.SetList();
	m_wndToolBarWindow.SetHotImageList(m_wndToolBarWindow.AddImageList(IDR_TOOLBAR_WINDOW_HOT));
	m_wndToolBarWindow.SetDefaultTextColor(RGB(0,0,128));
	m_wndToolBarWindow.SetHotTextColor(RGB(0,0,255));
	// we want to use tooltips text in our CoolToolBar
	m_wndToolBarWindow.SetMaxTextRows(1);
	m_wndToolBarWindow.SetButtonTextFromID(COXCoolToolBar::TTID_TOOLTIP);
	m_wndToolBarWindow.UpdateSizes();
	////////////

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBarWindow.SetBarStyle(m_wndToolBarWindow.GetBarStyle() |
		/*CBRS_TOOLTIPS | */CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarWindow.EnableDocking(CBRS_ALIGN_ANY);
	//////////////////////////////


	EnableDocking(CBRS_ALIGN_ANY);

	// TODO: Delete these lines if you don't want the toolbar to
	//  be dockable
	DockControlBar(&m_wndToolBarFile);
	DockControlBar(&m_wndToolBarWindow);

	// Dock Window toolbar to the right side of File toolbar
	m_wndToolBarWindow.DockControlBarLeftOf(&m_wndToolBarFile);

	// Let the menu organizer fix our menus
	Organizer.AttachFrameWnd(this);
	// use button from toolbars with corresponding items in menu
	Organizer.AutoSetMenuImage();

	// Install caption painter
	m_Caption.Attach(this);
	SendMessage(WM_NCPAINT);


	return 0;
}

void CMainFrame::OnUpdateViewToolbars(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CControlBar* pBar=GetControlBar(pCmdUI->m_nID);
	if(pBar!=NULL)
	{
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
}

void CMainFrame::OnViewToolbars(UINT nID) 
{
	// TODO: Add your command handler code here
	
	CControlBar* pBar = GetControlBar(nID);
	if (pBar != NULL)
	{
		ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE) == 0, FALSE);
	}
}


void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	// before close save the workspace
	SaveWorkspace();

	CMDIFrameWnd::OnClose();
}

void CMainFrame::SaveWorkspace() 
{
	// save state of framework caption
	m_Caption.SaveState(_T("FrameworkCaption"));

	// save states of all CoolToolBar
	m_wndToolBarFile.SaveBarState(_T("CoolToolBars"),_T("File"));
	m_wndToolBarEdit.SaveBarState(_T("CoolToolBars"),_T("Edit"));
	m_wndToolBarWindow.SaveBarState(_T("CoolToolBars"),_T("Window"));

	// save the state of all bars within framework
	SaveBarState(_T("FrameworkBarState"));
}

void CMainFrame::LoadWorkspace() 
{
	// load state of framework caption
	m_Caption.LoadState(_T("FrameworkCaption"));
	SendMessageToDescendants(COXCaptionPainter::m_nSetCaptionPainter,0,
		(LPARAM)&m_Caption);
	SendMessageToDescendants(WM_NCPAINT);

	LockWindowUpdate();

	// load all bars state in framework
	LoadBarState(_T("FrameworkBarState"));

	// load state of all CoolToolBar
	m_wndToolBarFile.LoadBarState(_T("CoolToolBars"),_T("File"));
	m_wndToolBarEdit.LoadBarState(_T("CoolToolBars"),_T("Edit"));
	m_wndToolBarWindow.LoadBarState(_T("CoolToolBars"),_T("Window"));

	UnlockWindowUpdate();
}


void CMainFrame::OnViewCustomize() 
{
	// TODO: Add your command handler code here

	CCustomizeDlg dlgCustomize(this);
	dlgCustomize.arrCustomize[0]=GetToolbarProperties(&m_wndToolBarFile);
	dlgCustomize.arrCustomize[1]=GetToolbarProperties(&m_wndToolBarEdit);
	dlgCustomize.arrCustomize[2]=GetToolbarProperties(&m_wndToolBarWindow);

	if(dlgCustomize.DoModal()==IDOK)
	{
		SetToolbarProperties(&m_wndToolBarFile,dlgCustomize.arrCustomize[0]);
		SetToolbarProperties(&m_wndToolBarEdit,dlgCustomize.arrCustomize[1]);
		SetToolbarProperties(&m_wndToolBarWindow,dlgCustomize.arrCustomize[2]);
	}
	
}

CustomizeToolbar CMainFrame::GetToolbarProperties(COXCoolToolBar* pBar)
{
	// collect information about CoolToolBar to use in Customize Toolbars dialog
	CustomizeToolbar ct;
	ct.bCustomizable=pBar->IsCustomizable();
	ct.bFlat=pBar->IsFlat();
	ct.bGripper=pBar->IsGripper();
	ct.bList=pBar->IsList();
	ct.bSeparator=pBar->IsSeparator();
	ct.bText=!pBar->GetButtonText(0).IsEmpty();
	ct.nTextType=(int)pBar->GetTextType();
	ct.nRows=pBar->GetTextRows();
	ct.nWidth=pBar->GetButtonsSize().cx;
	ct.nIndent=pBar->GetIndent();

	return ct;
}

void CMainFrame::SetToolbarProperties(COXCoolToolBar* pBar, CustomizeToolbar ct)
{
	// change styles and properties of CoolToolBar
	pBar->SetCustomizable(ct.bCustomizable);
	pBar->SetFlat(ct.bFlat);
	pBar->SetGripper(ct.bGripper);
	pBar->SetList(ct.bList);
	pBar->SetSeparator(ct.bSeparator);
	pBar->SetIndent(ct.nIndent);
	if(ct.bText)
	{
		pBar->SetButtonTextFromID((COXCoolToolBar::TextTypeFromID)ct.nTextType);
		pBar->SetMaxTextRows(ct.nRows);
		pBar->SetButtonsMinMaxWidth(0,ct.nWidth);
		pBar->UpdateSizes();
	}
	else
	{
		// if we don't want to use text in CoolToolBar then 
		// remove all previously associated text
		if(pBar->GetTextType()!=COXCoolToolBar::TTID_NOTSET)
		{
			pBar->SetButtonTextFromID(COXCoolToolBar::TTID_NONE);
			pBar->SetButtonTextFromID(COXCoolToolBar::TTID_NOTSET);
		}
		pBar->SetMaxTextRows(0);
		pBar->SetButtonsMinMaxWidth(0,24);
		pBar->IniSizes(CSize(16,16));
	}

	CSize sizeChild;
	sizeChild=pBar->GetButtonsSize();

	CRect rect;
	pBar->GetWindowRect(&rect);
	// resize window 
	pBar->SetWindowPos(NULL,0,0,rect.Width(),rect.Height(),
		SWP_NOMOVE|SWP_NOZORDER|SWP_DRAWFRAME|SWP_FRAMECHANGED);

	// it is up to framework to reallocate all other control bars
	CFrameWnd* pFrameWnd=pBar->GetDockingFrame();
	if(pFrameWnd!=NULL)
	{
		pFrameWnd->RecalcLayout();
	}
}

void CMainFrame::OnViewCustomizeCaption() 
{
	// TODO: Add your command handler code here

	CCustomizeCaptionDlg dlgCustomize(this);
	dlgCustomize.arrCustomize[0]=GetCaptionProperties(TRUE);
	dlgCustomize.arrCustomize[1]=GetCaptionProperties(FALSE);

	if(dlgCustomize.DoModal()==IDOK)
	{
		SetCaptionProperties(TRUE,dlgCustomize.arrCustomize[0]);
		SetCaptionProperties(FALSE,dlgCustomize.arrCustomize[1]);
		
		m_Caption.Reset();
		SendMessage(WM_NCPAINT);
		SendMessageToDescendants(COXCaptionPainter::m_nSetCaptionPainter,0,
			(LPARAM)&m_Caption);
		SendMessageToDescendants(WM_NCPAINT);

	}
	
}

CustomizeCaption CMainFrame::GetCaptionProperties(BOOL bActive)
{
	// collect information about CaptionPainter to use in Customize CaptionPainter dialog
	CustomizeCaption cc;
	COXCaptionInfo* pCI=m_Caption.GetCaptionInfo(bActive);

	pCI->GetCaptionLogFont(&cc.m_lf);
	cc.m_clrBackground=pCI->GetBackgroundColor(bActive);
	cc.m_clrText=pCI->GetTextColor(bActive);
	cc.m_bGradient=pCI->GetGradient();
	cc.m_nGradientAlgorithm=pCI->GetGradientAlgorithm();
	cc.m_nGradientAlignment=pCI->GetGradientAlignment();
	cc.m_nNumberShade=pCI->GetNumberShade();
	

	UINT nTextFormat=pCI->GetTextFormat();

	cc.m_nHorizontalAlignment=nTextFormat&DT_RIGHT ? 2 : 
		(nTextFormat&DT_CENTER ? 1 : 0);
	cc.m_nVerticalAlignment=nTextFormat&DT_BOTTOM ? 2 : 
		(nTextFormat&DT_TOP ? 0 : 1);
	cc.m_nEllipsis=nTextFormat&DT_END_ELLIPSIS ? 1 : 
		(nTextFormat&DT_PATH_ELLIPSIS ? 2 : 0);

	return cc;
}

void CMainFrame::SetCaptionProperties(BOOL bActive, CustomizeCaption cc)
{
	COXCaptionInfo* pCI=m_Caption.GetCaptionInfo(bActive);

	pCI->SetCaptionLogFont(&cc.m_lf);
	pCI->SetTextColor(cc.m_clrText);
	pCI->SetBackgroundColor(cc.m_clrBackground);
	pCI->SetGradient(cc.m_bGradient);
	pCI->SetGradientAlgorithm(cc.m_nGradientAlgorithm);
	pCI->SetGradientAlignment(cc.m_nGradientAlignment);
	pCI->SetNumberShade(cc.m_nNumberShade);

	UINT nTextFormat=DT_SINGLELINE;
	nTextFormat|=cc.m_nHorizontalAlignment==0 ? DT_LEFT : 
		(cc.m_nHorizontalAlignment==1 ? DT_CENTER : DT_RIGHT);
	nTextFormat|=cc.m_nVerticalAlignment==0 ? DT_TOP : 
		(cc.m_nVerticalAlignment==1 ? DT_VCENTER : DT_BOTTOM);
	nTextFormat|=cc.m_nEllipsis==0 ? 0 : 
		(cc.m_nEllipsis==1 ? DT_END_ELLIPSIS : DT_PATH_ELLIPSIS);

	pCI->SetTextFormat(nTextFormat);
}

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CPadDoc, CDocument)
BEGIN_MESSAGE_MAP(CPadDoc, CDocument)
	//{{AFX_MSG_MAP(CPadDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPadDoc::Serialize(CArchive& ar)
{
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
