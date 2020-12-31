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


	Enable3dControls();

	// use registry if you want to save CoolToolBars state
	SetRegistryKey(_T("Ultimate Toolbox Samples"));

	LoadStdProfileSettings();

#ifdef _MDI_INTERFACE
	AddDocTemplate(new CMultiDocTemplate(IDR_TEXTTYPE,
		RUNTIME_CLASS(CPadDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CEditView)));
	m_pMainWnd = new CMainFrame;
	((CFrameWnd*)m_pMainWnd)->LoadFrame(IDR_MAINFRAME);
	m_pMainWnd->ShowWindow(m_nCmdShow);
#else
	AddDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CPadDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CEditView)));
#endif

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// enable file manager drag/drop and DDE Execute open
	m_pMainWnd->DragAcceptFiles();
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// load saved workspace after all bars were created
	((CMainFrame*)m_pMainWnd)->LoadWorkspace();

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

IMPLEMENT_DYNCREATE(CMainFrame, CMainFrameWindow)

BEGIN_MESSAGE_MAP(CMainFrame, CMainFrameWindow)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_COMMAND(IDW_COOLBAR, OnCoolbar)
	ON_UPDATE_COMMAND_UI(IDW_COOLBAR, OnUpdateCoolbar)
	//}}AFX_MSG_MAP
#if _MFC_VER>=0x0420
	ON_NOTIFY(NM_CUSTOMDRAW,IDW_COOLBAR,OnCustomDraw)
#endif
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
	ID_INDICATOR_SCRL
};

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CMainFrameWindow::OnCreate(lpCreateStruct)==-1)
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

	// Create cool bar
	// refer to the documentation about styles used to create Coolbar
	if (!m_wndCoolBar.Create(this,
		WS_CHILD|WS_VISIBLE|WS_BORDER|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|
		RBS_TOOLTIPS|RBS_BANDBORDERS|RBS_VARHEIGHT)) 
	{
		TRACE(_T("Failed to create cool bar\n"));
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
	// we want to use this CoolToolBar in CoolBar 
	// so we have to set it in cool mode
	m_wndToolBarFile.SetCool();
	m_wndToolBarFile.SetHotImageList(m_wndToolBarFile.
		AddImageList(IDR_TOOLBAR_FILE_HOT));
	m_wndToolBarFile.SetDefaultTextColor(RGB(0,0,128));
	m_wndToolBarFile.SetHotTextColor(RGB(0,0,255));
	m_wndToolBarFile.UpdateSizes();
	////////////

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBarFile.SetBarStyle(m_wndToolBarFile.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
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
	// we want to use this CoolToolBar in CoolBar 
	// so we have to set it in cool mode
	m_wndToolBarEdit.SetCool();
	m_wndToolBarEdit.SetHotImageList(m_wndToolBarEdit.
		AddImageList(IDR_TOOLBAR_EDIT_HOT));
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
	// we want to use this CoolToolBar in CoolBar 
	// so we have to set it in cool mode
	m_wndToolBarWindow.SetCool();
	m_wndToolBarWindow.SetList();
	m_wndToolBarWindow.SetHotImageList(m_wndToolBarWindow.
		AddImageList(IDR_TOOLBAR_WINDOW_HOT));
	m_wndToolBarWindow.SetDefaultTextColor(RGB(0,0,128));
	m_wndToolBarWindow.SetHotTextColor(RGB(0,0,255));
	// we want to use tooltips text in our CoolToolBar
	m_wndToolBarWindow.SetMaxTextRows(1);
	m_wndToolBarWindow.SetButtonTextFromID(COXCoolToolBar::TTID_TOOLTIP);
	m_wndToolBarWindow.UpdateSizes();
	////////////

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBarWindow.SetBarStyle(m_wndToolBarWindow.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	//////////////////////////////


	// create object of COXCoolBarInfo class to attach image list to the Coolbar
	COXCoolBarInfo rbi;
	// if you call COXCoolBar::AddImageList function to set an image list
	// then CoolBar will take care about creating, saving and
	// destroying of that image list object
	rbi.SetImageList(m_wndCoolBar.AddImageList(IDR_COOLBAR_IMAGELIST));
	if(!m_wndCoolBar.SetBarInfo(&rbi))
	{
		TRACE(_T("Failed to set CoolBar info\n"));
		return -1;      // fail to insert
	} 

	// attaching toolbars to Coolbar
	// the only way to attach any window to the Coolbar
	// is to create object of COXCoolBarBandInfo class,
	// set all properties and insert it into the CoolBar
	COXCoolBarBandInfo rbbi;
	// we want the background bitmap does not move 
	// when the band is resized
	rbbi.SetStyle(RBBS_FIXEDBMP);
	// set the CoolToolBar as child window
	rbbi.SetChildWindow(&m_wndToolBarFile);
	// set the CoolToolBar window min size
	// the first argument is width and the second is height
	rbbi.SetChildWindowMinSize(m_wndToolBarFile.CalcDynamicLayout(-1,0).cx,
		m_wndToolBarFile.CalcDynamicLayout(-1,LM_HORZ).cy-4);
	// set background bitmap
	// if you call COXCoolBar::AddBitmap function to add bitmap
	// then CoolBar will take care about creating, saving and
	// destroying of bitmap object
	rbbi.SetBackgroundBitmap(m_wndCoolBar.AddBitmap(IDB_COOLBAR_WALLPAPER));
	// set the text to the band
	rbbi.SetText(_T("File Toolbar"));
	// set the zero based index number in image list associated with CoolBar
	rbbi.SetImage(0);
	// you have to set to the band an unique, non zero ID
	rbbi.SetID(ID_VIEW_TOOLBAR_FILE);
	// try to insert the band
	if(!m_wndCoolBar.InsertBand((UINT)-1,&rbbi))
	{
		TRACE(_T("Failed to insert band\n"));
		return -1;      // fail to insert
	} 


	// as far as we use the same COXCoolBarBandInfo object
	// we have to change only a few properties.
	// Using COXCoolBarBandInfo::Reset() function you can reset
	// COXCoolBarBandInfo object

	// we want this band to be displayed on the next line
	rbbi.SetStyle(RBBS_FIXEDBMP|RBBS_BREAK);
	// set the CoolToolBar as child window
	rbbi.SetChildWindow(&m_wndToolBarEdit);
	// set the CoolToolBar window min size
	// the first argument is width and the second is height
	rbbi.SetChildWindowMinSize(m_wndToolBarEdit.CalcDynamicLayout(-1,0).cx,
		m_wndToolBarEdit.CalcDynamicLayout(-1,LM_HORZ).cy-4);
	// set the zero based index number in image list associated with CoolBar
	rbbi.SetImage(1);
	// set the text to the band
	rbbi.SetText(_T("Edit Toolbar"));
	// you have to set to the band an unique, non zero ID
	rbbi.SetID(ID_VIEW_TOOLBAR_EDIT);
	// try to insert the band
	if(!m_wndCoolBar.InsertBand((UINT)-1,&rbbi))
	{
		TRACE(_T("Failed to insert band\n"));
		return -1;      // fail to insert
	} 

	// as far as we use the same COXCoolBarBandInfo object
	// we have to change only a few properties

	// set the CoolToolBar as child window
	rbbi.SetChildWindow(&m_wndToolBarWindow);
	// set the CoolToolBar window min size
	// the first argument is width and the second is height
	rbbi.SetChildWindowMinSize(m_wndToolBarWindow.CalcDynamicLayout(-1,0).cx,
		m_wndToolBarWindow.CalcDynamicLayout(-1,LM_HORZ).cy-4);
	// set the zero based index number in image list associated with CoolBar
	rbbi.SetImage(2);
	// set the text to the band
	rbbi.SetText(_T("Window Toolbar"));
	// you have to set to the band an unique, non zero ID
	rbbi.SetID(ID_VIEW_TOOLBAR_WINDOW);
	// try to insert the band
	if(!m_wndCoolBar.InsertBand((UINT)-1,&rbbi))
	{
		TRACE(_T("Failed to insert band\n"));
		return -1;      // fail to insert
	} 


	// Let the menu organizer fix our menus
	Organizer.AttachFrameWnd(this);
	// use button from toolbars with corresponding items in menu
	Organizer.AutoSetMenuImage();

	return 0;
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	// before close save the workspace
	SaveWorkspace();

	CMainFrameWindow::OnClose();
}

void CMainFrame::SaveWorkspace() 
{
	// save the state of all bands within CoolBar
	m_wndCoolBar.SaveState(_T("CoolBar"));

	// save states of all CoolToolBar
	m_wndToolBarFile.SaveBarState(_T("CoolToolBars"),_T("File"));
	m_wndToolBarEdit.SaveBarState(_T("CoolToolBars"),_T("Edit"));
	m_wndToolBarWindow.SaveBarState(_T("CoolToolBars"),_T("Window"));

	// save the state of all bars within framework
	SaveBarState(_T("FrameworkBarState"));
}

void CMainFrame::LoadWorkspace() 
{
	LockWindowUpdate();

	// load all bars state in framework
	LoadBarState(_T("FrameworkBarState"));

	// load state of all CoolToolBar
	m_wndToolBarFile.LoadBarState(_T("CoolToolBars"),_T("File"));
	m_wndToolBarEdit.LoadBarState(_T("CoolToolBars"),_T("Edit"));
	m_wndToolBarWindow.LoadBarState(_T("CoolToolBars"),_T("Window"));

	// load the state of all bands within CoolBar
	m_wndCoolBar.LoadState(_T("CoolBar"));

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
		LockWindowUpdate();

		SetToolbarProperties(&m_wndToolBarFile,dlgCustomize.arrCustomize[0]);
		SetToolbarProperties(&m_wndToolBarEdit,dlgCustomize.arrCustomize[1]);
		SetToolbarProperties(&m_wndToolBarWindow,dlgCustomize.arrCustomize[2]);

		// we applied all changes in SetToolbarProperties function
		// but I believe due to the bug in common control dll when we
		// change band's text from non empty string to empty one the system 
		// doesn't recalculate the size of the band.
		// Workaround is to repopulate Coolbar
		COXCoolBarBandInfo biFirst;
		COXCoolBarBandInfo biSecond;
		COXCoolBarBandInfo biThird;
		int nBand;
		int nBackward;
		// save all CoolBar's bands info
		if(m_wndCoolBar.GetBandInfo(0,&biFirst) && m_wndCoolBar.GetBandInfo(1,&biSecond) && 
			m_wndCoolBar.GetBandInfo(2,&biThird))
		{
			// delete all bands
			for(nBand=0; nBand<3; nBand++)
			{
				if(!m_wndCoolBar.DeleteBand(0))
				{
					break;
				}
			}
			// insert saved bands in back order to make sure
			// the initial width of bands will stay the same
			for(nBackward=nBand-1; nBackward>=0; nBackward--)
			{
				switch(nBackward)
				{
				case 0:
					{
						m_wndCoolBar.InsertBand(0,&biFirst);
						break;
					}
				case 1:
					{
						m_wndCoolBar.InsertBand(0,&biSecond);
						break;
					}
				case 2:
					{
						m_wndCoolBar.InsertBand(0,&biThird);
						break;
					}
				}
			}
		}

		UnlockWindowUpdate();
	}
}

CustomizeBand CMainFrame::GetToolbarProperties(COXCoolToolBar* pBar)
{
	// collect information about CoolBar's band and 
	// corresponding CoolToolBar to use in Customize Toolbars dialog
	CustomizeBand ct;
	ct.bCustomizable=pBar->IsCustomizable();
	ct.bFlat=pBar->IsFlat();
	ct.bList=pBar->IsList();
	ct.bSeparator=pBar->IsSeparator();
	ct.bText=!pBar->GetButtonText(0).IsEmpty();
	ct.nTextType=(int)pBar->GetTextType();
	ct.nRows=pBar->GetTextRows();
	ct.nWidth=pBar->GetButtonsSize().cx;

	UINT nBand;
	if(!m_wndCoolBar.GetBandNumber(pBar->GetDlgCtrlID(),nBand))
	{
		ct.nImage=-1;
		ct.sBandText=CString(_T(""));
	}
	else
	{
		if(!m_wndCoolBar.GetBandImage(nBand,ct.nImage))
		{
			ct.nImage=-1;
		}
		CString sText;
		if(!m_wndCoolBar.GetBandText(nBand,sText))
		{
			ct.sBandText=CString(_T(""));
		}
		else
		{
			ct.sBandText=sText;
		}
	}

	return ct;
}

void CMainFrame::SetToolbarProperties(COXCoolToolBar* pBar, CustomizeBand ct)
{
	// change styles and properties of CoolToolBar
	pBar->SetCustomizable(ct.bCustomizable);
	pBar->SetFlat(ct.bFlat);
	pBar->SetList(ct.bList);
	pBar->SetSeparator(ct.bSeparator);
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
		pBar->SetButtonTextFromID(COXCoolToolBar::TTID_NONE);
		pBar->SetButtonTextFromID(COXCoolToolBar::TTID_NOTSET);
		pBar->SetMaxTextRows(0);
		pBar->SetButtonsMinMaxWidth(0,24);
		pBar->IniSizes(CSize(16,16));
	}

	// change the CoolBar's band properties
	UINT nBand;
	if(m_wndCoolBar.GetBandNumber(pBar->GetDlgCtrlID(),nBand))
	{
		// change the text associated with the band
		CString sText;
		sText=ct.sBandText;
		try
		{
			m_wndCoolBar.SetBandText(nBand,sText.GetBuffer(sText.GetLength()));
			sText.ReleaseBuffer();
		}
		catch(CMemoryException* e)
		{
			AfxMessageBox(_T("Out of memory!"),MB_ICONSTOP);
			e->Delete();
		}

		// change the number of index in CoolBar's image list
		m_wndCoolBar.SetBandImage(nBand,ct.nImage);

		// the size of CoolToolBar could have changed 
		// then reset the min Chid Window Size
		CSize sizeChild;
		if(m_wndCoolBar.GetBandChildWindowMinSize(nBand,sizeChild))
		{
			sizeChild=pBar->GetButtonsSize();
			m_wndCoolBar.SetBandChildWindowMinSize(nBand,
				pBar->CalcDynamicLayout(-1,0).cx,
				sizeChild.cy+4);
		}

	}

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

void CMainFrame::OnUpdateCoolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CControlBar* pBar=GetControlBar(pCmdUI->m_nID);
	if(pBar!=NULL)
	{
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
}

void CMainFrame::OnCoolbar() 
{
	// TODO: Add your command handler code here
	
	CControlBar* pBar = (CControlBar*)&m_wndCoolBar;
	if (pBar != NULL)
	{
		ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE) == 0, FALSE);
	}
}

#if _MFC_VER>=0x0420
//////////////////////
// custom draw of a toolbar is available since MFC 4.2
// in you derived class you can provide your own custom draw routines
afx_msg void CMainFrame::OnCustomDraw(NMHDR* pNotify, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pCDRW;
	pCDRW=(LPNMCUSTOMDRAW)pNotify;

	*pResult = CDRF_DODEFAULT;
	switch( pCDRW->dwDrawStage )
	{
	case CDDS_PREPAINT:
		{
			*pResult=CDRF_NOTIFYITEMDRAW;
			break;
		}
	case CDDS_ITEMPREPAINT:
		{
			*pResult=CDRF_NEWFONT;

			CDC dc;
			dc.Attach(pCDRW->hdc);

			CFont* pFont=dc.GetCurrentFont();
			if(pFont)
			{
				LOGFONT lf;
				VERIFY(pFont->GetLogFont(&lf));
				if(lf.lfWeight!=1000)
					lf.lfWeight=1000;
				lf.lfHeight=-24;
				if((HFONT)m_CoolbarFont)
					m_CoolbarFont.DeleteObject();
				VERIFY(m_CoolbarFont.CreateFontIndirect(&lf));
			}
			else
				TRACE(_T("CMainFrame::OnCustomDraw: failed to get DC font"));

			dc.Detach();

			if((HFONT)m_CoolbarFont)
				::SelectObject(pCDRW->hdc, (HFONT)m_CoolbarFont);
			::SetTextColor(pCDRW->hdc, RGB(255,0,0));
			break;
		}
	default:
		{
			TRACE(_T("Unknown draw stage ...\n"));
			break;
		}
	}
}
//////////////////////
#endif

