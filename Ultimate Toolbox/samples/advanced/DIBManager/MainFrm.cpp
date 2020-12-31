// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DIBManager.h"

#include "MainFrm.h"
#include "DIBManagerView.h"
#include "ChildFrm.h"

#include "ImportDlg.h"
#include "ScaleRollupDlg.h"

#include "OXDocMgr.h"
#include "OXWorkspaceState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, COXMDIFrameWndSizeDock)

BEGIN_MESSAGE_MAP(CMainFrame, COXMDIFrameWndSizeDock)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_QUERYNEWPALETTE()
    ON_WM_PALETTECHANGED()
	ON_COMMAND(ID_WINDOW_SYNCHRONIZE, OnWindowSynchronize)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_SYNCHRONIZE, OnUpdateWindowSynchronize)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ZOOM, OnUpdateZoom)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SIZE, OnUpdateSize)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PARAMETERS, OnUpdateParameters)
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_UPDATE_COMMAND_UI(ID_FILE_PROTECTED, OnUpdateFileProtected)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_LEVEL_DLG, OnUpdateViewZoomLevelDlg)
	//}}AFX_MSG_MAP
	ON_ROLLUP_NOTIFICATION()
	// standard on/off control bar handlers for View menu. 
	ON_UPDATE_COMMAND_UI(ID_TREEFILESBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_TREEFILESBAR, OnBarCheck)
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnDropDown)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars
// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_OPEN,
	ID_FILE_CLOSE,
	ID_FILE_SAVE,
	ID_FILE_SAVE_AS,
		ID_SEPARATOR,
	ID_FILE_IMPORT,
	ID_FILE_EXPORT,
		ID_SEPARATOR,
	ID_FILE_PROTECTED,
		ID_SEPARATOR,
	ID_VIEW_ZOOM_IN,
	ID_VIEW_ZOOM_OUT,
	ID_VIEW_ZOOM_TO_WINDOW,
	ID_VIEW_ZOOM_TO_100,
		ID_SEPARATOR,
	ID_FILE_PRINT,
	ID_FILE_PRINT_PREVIEW,
		ID_SEPARATOR,
	ID_WINDOW_NEW,
	ID_WINDOW_CASCADE,
	ID_WINDOW_TILE_HORZ,
	ID_WINDOW_ARRANGE,
	ID_WINDOW_SYNCHRONIZE,
		ID_SEPARATOR,
	ID_APP_ABOUT,
};

static UINT BASED_CODE buttons1[] =
{
	ID_VIEW_ZOOM_IN,
		ID_SEPARATOR,
	ID_VIEW_ZOOM_OUT,
		ID_SEPARATOR,
	ID_VIEW_ZOOM_TO_WINDOW,
		ID_SEPARATOR,
	ID_VIEW_ZOOM_TO_100,
};

static UINT BASED_CODE allbuttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_OPEN,
	ID_FILE_CLOSE,
	ID_FILE_SAVE,
	ID_FILE_SAVE_AS,
	ID_FILE_IMPORT,
	ID_FILE_EXPORT,
	ID_FILE_PROTECTED,
	ID_VIEW_ZOOM_IN,
	ID_VIEW_ZOOM_OUT,
	ID_VIEW_ZOOM_TO_WINDOW,
	ID_VIEW_ZOOM_TO_100,
	ID_FILE_PRINT,
	ID_FILE_PRINT_PREVIEW,
	ID_WINDOW_NEW,
	ID_WINDOW_CASCADE,
	ID_WINDOW_TILE_HORZ,
	ID_WINDOW_ARRANGE,
	ID_WINDOW_SYNCHRONIZE,
	ID_APP_ABOUT,
};

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_PROGRESS,
	ID_INDICATOR_SIZE,
	ID_INDICATOR_PARAMETERS,
	ID_INDICATOR_ZOOM,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_pShowProgress=NULL;
	m_bShowZoomLevelDlg=FALSE;
}

CMainFrame::~CMainFrame()
{
	if(m_pShowProgress!=NULL)
		delete m_pShowProgress;

	// if roll-up ZoomLevel Dialog is active then delete it
	CScaleRollupDlg *pScaleRollupDlg=((CDIBManagerApp*)AfxGetApp())->GetScaleRollupDlg();
	if(pScaleRollupDlg!=NULL)
		delete pScaleRollupDlg;
	pScaleRollupDlg=NULL;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COXMDIFrameWndSizeDock::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Install caption painter
	m_Caption.Attach(this);
	COXCaptionInfo* pCI=m_Caption.GetCaptionInfo(TRUE);
	pCI->SetBackgroundColor(RGB(128,255,255));
	pCI=m_Caption.GetCaptionInfo(FALSE);
	pCI->SetBackgroundColor(RGB(255,255,128));
	SendMessage(WM_NCPAINT);

	// Create cool bar
	// create toolbar
	if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
		{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
		} 
	// 	This function specifies the command ID's of the button images in the bitmap.
	// 	The following SetButtons() then specifies which buttons are actually present
	m_wndToolBar.SetBitmapIds(allbuttons, sizeof(allbuttons)/sizeof(UINT));

	m_wndToolBar.IniSizes(CSize(16,16));
	m_wndToolBar.UpdateSizes();
	m_wndToolBar.SetHotImageList(m_wndToolBar.AddImageList(IDR_MAINFRAME_HOT));
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.SetButtonStyle(0,m_wndToolBar.GetButtonStyle(0)|TBSTYLE_DROPDOWN);
	m_wndToolBar.SetDropDownArrow(TRUE);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);



	// create standard statusbar? 
	// Wrong! This is our COXStatusBar object
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// set style of second pane in statusbar as pane with progressbar
    UINT nID, nStyle;
	int cxWidth;
	m_wndStatusBar.GetPaneInfo( 1, nID, nStyle, cxWidth);
	nStyle |= SBPS_PERCENT;
	m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, 100);

	ShowWindow(SW_SHOW);
	if (!m_wndStatusBar.SetUpBar(1, TRUE, FALSE))
		return -1;

	// instantiate an object to show progress in specified pane 
	// (in this case pane=1)
	m_pShowProgress=new CShowProgress(this,1);

	EnableDocking(CBRS_ALIGN_ANY);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	DockControlBar(&m_wndToolBar);
//	DockControlBar(&m_wndToolBar1);
//	DockControlBar(&m_wndMenuBar);

	// create dockable TreeFilesBar dialog to show info about opened files
	// ad ID use the same variable as in menu that we use to Show/Hide dialog
	m_TreeFilesBar.SetSizeDockStyle(SZBARF_STDMOUSECLICKS | SZBARF_DLGAUTOSIZE);
	if (!m_TreeFilesBar.Create(this, (UINT)IDD_DIALOG_TREE_FILES, CBRS_LEFT, 
		ID_TREEFILESBAR))   
	{
		TRACE0("Failed to create TreeFiles bar\n");
		return -1;      
	} 
	m_TreeFilesBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_TreeFilesBar);

	RecalcLayout();

	// Let the menu organizer fix our menus
	Organizer.AttachFrameWnd(this);
	// use button from toolbar with corresponding items in menu
	Organizer.AutoSetMenuImage();
	// set buttons 
	Organizer.SetMenuBitmap(ID_VIEW_TOOLBAR,IDB_CHECK);
	Organizer.SetMenuBitmap(ID_VIEW_STATUS_BAR,IDB_CHECK);
	Organizer.SetMenuBitmap(ID_VIEW_TREE_BAR,IDB_CHECK);
	Organizer.SetMenuBitmap(ID_VIEW_ZOOM_LEVEL_DLG,IDB_CHECK);
	Organizer.SetMenuBitmap(ID_TREEFILESBAR,IDB_CHECK);

	// get the number of colors that can be used on that display
	// if it is <=256 than we have to dither DIB image before rendering to screen
	GetNumColors();

	// create the new roll_up ZoomLevel Dialog 
	((CDIBManagerApp*)AfxGetApp())->GetScaleRollupDlg()=new CScaleRollupDlg(this);

	// hook the frame window in order to display tab control in client area
	VERIFY(m_MTIClientWnd.Attach(this));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,NULL,NULL,
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	ASSERT(cs.lpszClass);

	return COXMDIFrameWndSizeDock::PreCreateWindow(cs);
}

BOOL CMainFrame::OnQueryNewPalette() 
{
	CView* pView=GetActiveFrame()->GetActiveView();
	if(pView)
		pView->SendMessage(WM_QUERYNEWPALETTE);
	return FALSE;
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	UNREFERENCED_PARAMETER(pFocusWnd);
	const MSG& msg=AfxGetThreadState()->m_lastSentMsg;
	SendMessageToDescendants(WM_PALETTECHANGED, msg.wParam, msg.lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	COXMDIFrameWndSizeDock::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	COXMDIFrameWndSizeDock::Dump(dc);
}

#endif //_DEBUG


void CMainFrame::OnWindowSynchronize() 
{
	// TODO: Add your command handler code here
	
	// synchronize current active window and 
	// element selected in TreeFilesBar
	m_TreeFilesBar.SetActiveWindowInTree(GetActiveFrame());
}

void CMainFrame::OnUpdateWindowSynchronize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(GetActiveFrame()!=this);
}

void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdateZoom(CCmdUI* pCmdUI)
{
	CString string="";
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(string);
}

void CMainFrame::OnUpdateSize(CCmdUI* pCmdUI)
{
	CString string="";
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(string);
}

void CMainFrame::OnUpdateParameters(CCmdUI* pCmdUI)
{
	CString string="";
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(string);
}

void CMainFrame::OnFileImport() 
{
	// TODO: Add your command handler code here
	
	// import JPEG file
	CImportDlg importDlg;
	if(importDlg.DoModal()==IDOK)
	{
		// use our own function to instantiate new Document object
		// and corresponding classes
		CreateDocumentFromOpenedFile(&importDlg.m_tmpBMPFile,importDlg.m_sFileName);
	}
}


void CMainFrame::CreateDocumentFromOpenedFile(CString sFileName, 
											  CDIBManagerDoc::TypeFile tf) 
{
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();

	// check if we already opened the file
	if(CheckFileAlreadyOpened(sFileName,TRUE))
	{
		return;
	}

	CFile m_file;
	BOOL bSuccess=FALSE;
	// check if we can open file on Read
	TRY
	{
		bSuccess=m_file.Open(sFileName,CFile::modeRead);
	}
	CATCH(CFileException, e)
	{
		TCHAR szCause[255];
        CString strFormatted;
        e->GetErrorMessage(szCause, 255);
        strFormatted = _T("CDIBManagerDoc::OpenDocument:exception: ");
        strFormatted += szCause;
        TRACE(strFormatted);

		bSuccess=FALSE;
	}
	END_CATCH

	if(!bSuccess)
	{
		// send notification to Application object
		// if errors occurs during loading workspace then
		// application has an opportunity to hide and destroy splash window
		pApp->ErrorNotify(_T("Cannot open file!"));
		return;
	}

	CreateDocumentFromOpenedFile(&m_file,sFileName,tf);
}

void CMainFrame::CreateDocumentFromOpenedFile(CFile* pFile, CString sFileName, 
											  CDIBManagerDoc::TypeFile tf) 
{
	CDIBManagerDoc* pDocument=NULL;
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	// our own DocManager
	// we use him to let multiselection in BitmapPreview Dialog
	// as far as we have only one DocTemplate we simplified things
	CDocTemplate* pTemplate=NULL;
	POSITION posTemplate=pApp->GetFirstDocTemplatePosition();
	if(posTemplate!=NULL)
	{
		pTemplate=pApp->GetNextDocTemplate(posTemplate);
	}
	ASSERT_KINDOF(CDocTemplate, pTemplate);

	// create new document 
	pDocument=(CDIBManagerDoc*)pTemplate->CreateNewDocument();
	if (pDocument == NULL)
	{
		TRACE0("CDocTemplate::CreateNewDocument returned NULL.\n");
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return;
	}

	BOOL bAutoDelete=pDocument->m_bAutoDelete;
	pDocument->m_bAutoDelete=FALSE;   // don't destroy if something goes wrong
	// create new frame for document
	CFrameWnd* pFrame=pTemplate->CreateNewFrame(pDocument, NULL);
	pDocument->m_bAutoDelete=bAutoDelete;
	if (pFrame==NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		delete pDocument;       // explicit delete on error
		return ;
	}
	ASSERT_VALID(pFrame);

	CWaitCursor wait;
	if(!pDocument->OpenDocument(pFile,sFileName,tf))
	{
		// if we didn't manage to create new document
		// but already created a window for it then
		// remove info from TreeFilesBar
		m_TreeFilesBar.RemoveWindowFromTree(pFrame);
		delete pDocument;       // explicit delete on error
		delete pFrame;			// explicit delete on error
		return;
	}

	pDocument->SetPathName(pDocument->m_sNameFile,FALSE);

	pTemplate->InitialUpdateFrame(pFrame,pDocument,TRUE);
}

BOOL CMainFrame::CheckFileAlreadyOpened(CString sFileName, BOOL bNotify) 
{
	// check if file already opened
	BOOL bOpened=FALSE;

	// get DocTemplate
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	// as far as we have only one DocTemplate we simplified things
	CDocTemplate* pTemplate=NULL;
	POSITION posTemplate=pApp->GetFirstDocTemplatePosition();
	if(posTemplate!=NULL)
	{
		pTemplate=pApp->GetNextDocTemplate(posTemplate);
	}
	ASSERT_KINDOF(CDocTemplate, pTemplate);

	// iterate documents and check their file name
	CDIBManagerDoc* pDocument;
	POSITION pos=pTemplate->GetFirstDocPosition();
	while(pos!=NULL)
	{
		pDocument=(CDIBManagerDoc*)pTemplate->GetNextDoc(pos);
		if(sFileName==pDocument->m_sNameFile)
		{
			bOpened=TRUE;
			if(bNotify)
			{
				CString sFileAlreadyOpened;
				sFileAlreadyOpened.Format(_T("File %s already opened!"),sFileName);
				pApp->ErrorNotify(sFileAlreadyOpened);
			}
			break;
		}
	}

	return bOpened;
}
void CMainFrame::OnUpdateFileProtected(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainFrame::OnClose() 
{
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	// Save workspace if needed
	if(pApp->m_bSaveWSOnExit)
	{
		SaveWorkspace();
	}
	COXMDIFrameWndSizeDock::OnClose();
}

void CMainFrame::ResetProgress() 
{
	// reset associated progress object
	if(m_pShowProgress==NULL)
		return;
	m_pShowProgress->Reset();
}

void CMainFrame::ShowProgress() 
{
	// iterate associated progress object
	// progress object will show progress
	if(m_pShowProgress==NULL)
		return;
	m_pShowProgress->Iterate();
}

BOOL CMainFrame::IniProgress(WORD nToDo, WORD nStep) 
{
	// initialize associated progress object
	if(m_pShowProgress==NULL)
		return FALSE;

	if(nToDo==0 || nStep==0)
		return FALSE;

	m_pShowProgress->Initialize(nToDo,nStep);
	return TRUE;
}

void CMainFrame::GetNumColors() 
{
	// get the number of bits in current system pallete
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	CWindowDC dc(this);
	pApp->m_nColors=(UINT)dc.GetDeviceCaps(BITSPIXEL);
}

BOOL CMainFrame::OnRollupMessage(CWnd* pWndRollup,UINT message,UINT rollupID)
{
	// notification from roll-up ZoomLevel Dialog
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	CScaleRollupDlg *pScaleRollupDlg=pApp->GetScaleRollupDlg();
	if (pScaleRollupDlg->GetRollupID() == rollupID)
	{
		switch (message)
		{
		// if it is closed then destroy it
		case IDCANCEL:
			{
				pWndRollup->DestroyWindow();	
				m_bShowZoomLevelDlg=FALSE;
			}
		default:
			{
				TRACE2("Unhandled message %d from Rollup %d\n",message,rollupID);
				break;
			}
		}
    }
    // messages from other rollups are being ignored!!!
    return TRUE;
}

void CMainFrame::OnUpdateViewZoomLevelDlg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bShowZoomLevelDlg);
}

void CMainFrame::SaveWorkspace() 
{

	SaveSizeBarState(_T("SizeBarState"));

	// common procedure to save workspace
	COXWorkspaceState workspaceState;
	workspaceState.IncludeMainWindow(FALSE);
	if (!workspaceState.StoreToRegistry())
	{
		TRACE0("CMainFrame::OnClose : Failed to save workspace to registry, continuing\n");
	}
	// If some of files are dirty then when we save workspace it asks
	// whether we want to save dirty doc if we choose No then 
	// it does not unmark the document as dirty
	// so let us do that
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	POSITION posTemplate=pApp->GetFirstDocTemplatePosition();
	while(posTemplate!=NULL)
	{
		CDocTemplate* pTemplate=pApp->GetNextDocTemplate(posTemplate);
		POSITION pos=pTemplate->GetFirstDocPosition();
		while (pos != NULL)
		{
			CDocument* pDoc = pTemplate->GetNextDoc(pos);
			pDoc->SetModifiedFlag(FALSE);
		}
	}

}

void CMainFrame::LoadWorkspace() 
{
	LockWindowUpdate();

	// Since we allow floating control bars MDI child windows, 
	// and these can only be created once
	// we have a main window, we need to restore the bar size state here. 
	// (not on CMainFrame::OnCreate())
	LoadSizeBarState(_T("SizeBarState"));

	COXWorkspaceState workspaceState;
	workspaceState.IncludeMainWindow(FALSE);
	if (!workspaceState.LoadFromRegistry())
	{
		TRACE(_T("CWorkspaceDemoApp::InitInstance : Failed to load workspace from registry, continuing\n"));
	}

	m_wndToolBar.LoadBarState(_T("CoolToolBars"),_T("Bar1"));

	UnlockWindowUpdate();
}

void CMainFrame::OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	// this function handles the dropdown menus from the toolbar
	NMTOOLBAR* pNMToolBar = (NMTOOLBAR*)pNotifyStruct;
	CRect rect;

	// translate the current toolbar item rectangle into screen coordinates
	// so that we'll know where to pop up the menu
	m_wndToolBar.GetItemRect(m_wndToolBar.CommandToIndex(pNMToolBar->iItem), &rect);
	rect.top = rect.bottom;
	::ClientToScreen(pNMToolBar->hdr.hwndFrom, &rect.TopLeft());
	if(pNMToolBar->iItem == ID_FILE_OPEN)
	{
		CMenu menu;
		CMenu* pPopup;

		// the font popup is stored in a resource
		menu.LoadMenu(IDR_MAINFRAME);
		pPopup = menu.GetSubMenu(0);
		pPopup->RemoveMenu(ID_FILE_NEW,MF_BYCOMMAND);
		pPopup->RemoveMenu(ID_SEPARATOR,MF_BYCOMMAND);
		pPopup->RemoveMenu(ID_FILE_IMPORT,MF_BYCOMMAND);
		pPopup->RemoveMenu(ID_SEPARATOR,MF_BYCOMMAND);
		pPopup->RemoveMenu(ID_FILE_PRINT_SETUP,MF_BYCOMMAND);
		pPopup->RemoveMenu(ID_APP_EXIT,MF_BYCOMMAND);
		pPopup->RemoveMenu(pPopup->GetMenuItemCount()-1,MF_BYPOSITION);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rect.left, 
			rect.top + 1, AfxGetMainWnd());
	}
	*pResult = TBDDRET_DEFAULT; 
}

