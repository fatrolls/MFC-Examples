// PropertySheetCapture.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ScreenGrabber.h"
#include "PropertySheetCapture.h"

#include "PropertyPageActivation.h"
#include "PropertyPageSource.h"
#include "PropertyPageDestination.h"
#include "PropertyPageImage.h"
#include "PropertyPageFile.h"
#include "PropertyPagePreferences.h"

#include "UTSampleAbout.h"

#include "path.h"
#include "OXScreenGrab.h"

#include "oxbmpfle.h"
#include "oxjpgfle.h"
#include "oxjpgcom.h"
#include "oxjpgdom.h"
#include "oxjpgexp.h"

// GIF classes available at additional request (due to patent fee)
//#include "oxgiffle.h"

#include "OXMainRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CWnd* g_pWndLastForeground;
/////////////////////////////////////////////////////////////////////////////
// CPropertySheetCapture dialog

// array of control IDs and corresponding help IDs
const DWORD CPropertySheetCapture::m_nHelpIDs[] = 
{
	0, 0
};

CPropertySheetCapture::CPropertySheetCapture(UINT nIDCaption, CWnd *pParentWnd, 
	UINT iSelectPage) : COXContextHelpPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	IniPropertySheet();
}

CPropertySheetCapture::CPropertySheetCapture(LPCTSTR pszCaption, CWnd *pParentWnd, 
	UINT iSelectPage) : COXContextHelpPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	IniPropertySheet();
}

void CPropertySheetCapture::IniPropertySheet()
{
	m_bInitialized=FALSE;

	pWndTrackingHelper=NULL;

	m_bIsCapturing=FALSE;
	m_nTimerCaptureDelay=0;
	m_bGettingRectArea=FALSE;

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// initialize Taskbar Icon
	IniTaskbarIcon();
}

void CPropertySheetCapture::IniTaskbarIcon()
{
	m_TaskbarIcon.Create();
	// When there is only one taskbar icon, you don't need to specify an ID.
	// The ID is useful only when implementing two (or more) taskbar icons, AND you want 
	// to handle mouse messages from both icons within one message handler (therefore, you
	// need that ID to tell which icon posted the msg). However, it might be a good idea to
	// assign an ID, and check the ID in the message handler, especially when you may need
	// to derive your classes (somebody else may add another taskbar icon).

	// Note: you don't need to detroy a taskbar icon. It's done in its own destructor.

	m_TaskbarIcon.m_pPopupOwner = this;
	// let this dialog handle popup menu's message
	// Note: m_pPopupOwner is NOT a member of COXTaskbarIcon.

	m_TaskbarIcon.SetIcon(IDR_MAINFRAME);
	m_TaskbarIcon.SetTooltipText(AFX_IDS_APP_TITLE);
	m_TaskbarIcon.Show();
}

BEGIN_MESSAGE_MAP(CPropertySheetCapture, COXContextHelpPropertySheet)
	//{{AFX_MSG_MAP(CPropertySheetCapture)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDOK, OnButtonCapture)
	ON_BN_CLICKED(IDCANCEL, OnButtonClose)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_CLOSE, OnButtonClose)
	ON_COMMAND(ID_ABOUT, OnAppAbout)
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetCapture message handlers

int CPropertySheetCapture::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXContextHelpPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	// Make it resizable
	ModifyStyle(0,WS_THICKFRAME);
//	ModifyStyle(0,WS_MAXIMIZEBOX);

	// create window that we use to show tracking rectangle
	// while capturing rectangular area
	pWndTrackingHelper=new CWndTrackingHelper;
	// make it transparent 
	if(!pWndTrackingHelper->CreateEx(WS_EX_TRANSPARENT|WS_EX_TOOLWINDOW, 
		AfxRegisterWndClass(0), _T(""), WS_POPUP, 0, 0, 0, 0, NULL, NULL))
	{
		TRACE0("Warning: unable to create tracking helper window!\n");
		AfxThrowResourceException();
	}
	ASSERT(pWndTrackingHelper->m_hWnd != NULL);
	
	return 0;
}

void CPropertySheetCapture::OnDestroy() 
{
	COXContextHelpPropertySheet::OnDestroy();
	
	// TODO: Add your message handler code here
	if(pWndTrackingHelper!=NULL)
	{
		// delete helper window
		pWndTrackingHelper->DestroyWindow();
		delete pWndTrackingHelper;
		pWndTrackingHelper=NULL;
	}
}

BOOL CPropertySheetCapture::OnInitDialog()
{
	COXContextHelpPropertySheet::OnInitDialog();

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	// Remove standard Restore, Maximize & Minimize items out of system menu.

	if (pSysMenu != NULL)
	{
		pSysMenu->RemoveMenu(SC_RESTORE,MF_BYCOMMAND);
		pSysMenu->RemoveMenu(SC_MINIMIZE,MF_BYCOMMAND);
		pSysMenu->RemoveMenu(SC_MAXIMIZE,MF_BYCOMMAND);
	}
	// Add "Minimize" menu item to system menu.

	// IDM_MINIMIZE must be in the system command range.
	ASSERT((IDM_MINIMIZE & 0xFFF0) == IDM_MINIMIZE);
	ASSERT(IDM_MINIMIZE < 0xF000);

	if (pSysMenu != NULL)
	{
		CString strMinimizeMenu(_T("Mi&nimize"));
		if (!strMinimizeMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_STRING, IDM_MINIMIZE, strMinimizeMenu);
		}
	}

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_LayoutManager.Attach(this);

	m_LayoutManager.SetConstraint(IDOK, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -6, IDCANCEL);
	m_LayoutManager.SetConstraint(IDOK, OX_LMS_BOTTOM, OX_LMT_SAME, -5);

  
	m_LayoutManager.SetConstraint(IDCANCEL, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -6, IDHELP);
	m_LayoutManager.SetConstraint(IDCANCEL, OX_LMS_BOTTOM, OX_LMT_SAME, -5);

	m_LayoutManager.SetConstraint(IDHELP, OX_LMS_RIGHT,  OX_LMT_SAME, -4);
	m_LayoutManager.SetConstraint(IDHELP, OX_LMS_BOTTOM, OX_LMT_SAME, -5);

	m_LayoutManager.SetConstraint(GetTabControl()->GetDlgCtrlID(), 
		OX_LMS_LEFT, OX_LMT_SAME, 4);
	m_LayoutManager.SetConstraint(GetTabControl()->GetDlgCtrlID(),
		OX_LMS_RIGHT, OX_LMT_SAME, -4);
	m_LayoutManager.SetConstraint(GetTabControl()->GetDlgCtrlID(), 
		OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -7, IDOK);
	m_LayoutManager.SetConstraint(GetTabControl()->GetDlgCtrlID(), 
		OX_LMS_TOP, OX_LMT_SAME, 7);
	
	// Draw the layout with the new constraints
	// This is necessary when constraints are implemented and the window must be refreshed
	CRect rect;
	GetWindowRect(&rect);
	GetTabControl()->AdjustRect(FALSE,&rect);
	m_LayoutManager.OnSize(rect.Width(),rect.Height());
	

	// rename standard OK button
	CWnd* pButtonOK=GetDlgItem(IDOK);
	pButtonOK->SetWindowText(_T("Capture"));
	
	// rename standard Cancel button
	CWnd* pButtonCancel=GetDlgItem(IDCANCEL);
	pButtonCancel->SetWindowText(_T("Close"));
	
	m_bInitialized=TRUE;

	GetTabControl()->GetWindowRect(&m_rectPage);
	GetTabControl()->AdjustRect(FALSE,&m_rectPage);
	ScreenToClient(&m_rectPage);
	GetActivePage()->MoveWindow(&m_rectPage);

	return TRUE; 
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPropertySheetCapture::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		COXContextHelpPropertySheet::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPropertySheetCapture::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPropertySheetCapture::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		OnAppAbout();
	}
	else
	{
		if ((nID & 0xFFF0) == IDM_MINIMIZE)
		{
			OnMinimize();
		}
		else
		{
			COXContextHelpPropertySheet::OnSysCommand(nID, lParam);
		}
	}
}

LRESULT CPropertySheetCapture::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	if((int)wParam!=ID_HOTKEY || m_nTimerCaptureDelay!=0 || m_bIsCapturing)
		return 0;

	// user pressed hot key
	CPropertyPageActivation* pActivation=(CPropertyPageActivation*)GetPage(0);
	if(pActivation->m_bInitialDelay)
	{
		// if needed set initial delay
		m_nTimerCaptureDelay=SetTimer(ID_TIMER_CAPTURE_DELAY,
			(DWORD)pActivation->m_nInitialDelay*(DWORD)1000,NULL);
		if(m_nTimerCaptureDelay==0)
		{
			AfxMessageBox(_T("Cannot create timer to set initial delay!"),
				MB_OK|MB_ICONEXCLAMATION);
		}
	}
	else
	{
		// start capturing
		DoCapture();
	}

	return 0;
}

void CPropertySheetCapture::OnLButtonDown(UINT nFlags, CPoint point)
{
	UNREFERENCED_PARAMETER(nFlags);
	if(m_bGettingRectArea)
	{
		// if capture area is rectangle
		ReleaseCapture();
		m_bGettingRectArea=FALSE;
		COXScreenGrabber ScreenGrabber;
		ScreenGrabber.GrabTracker(this,point,pWndTrackingHelper);

		// remove helper window from screen
		RemoveTrackingHelper();

		// try to stream captured image to the destination(s)
		StreamCapture(ScreenGrabber.GetGrabDIB());
	}
}

void CPropertySheetCapture::OnButtonCapture()
{
	// refresh all vars
	PressButton(PSBTN_APPLYNOW);
	
	//
	if(!DoRegisterHotKey())
	{
		AfxMessageBox(_T("Cannot register Hot Key!"));
	}
	else
	{
		// remove property sheet from screen
		OnMinimize();
	}
}

void CPropertySheetCapture::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
	case ID_TIMER_CAPTURE_DELAY:
		{
			KillTimer(m_nTimerCaptureDelay);
			m_nTimerCaptureDelay=0;

			// start capturing
			DoCapture();

			break;
		}
	default:
		break;
	}
}

BOOL CPropertySheetCapture::DoRegisterHotKey() 
{
//	BOOL bProcessed=FALSE;
	UINT vk;

	// define hot key to register
	CPropertyPageActivation* pActivation=(CPropertyPageActivation*)GetPage(0);
	if(pActivation->m_sHotKey==_T("F1"))
		vk=VK_F1;
	else
		if(pActivation->m_sHotKey==_T("F2"))
			vk=VK_F2;
		else
			if(pActivation->m_sHotKey==_T("F3"))
				vk=VK_F3;
			else
				if(pActivation->m_sHotKey==_T("F4"))
					vk=VK_F4;
				else
					if(pActivation->m_sHotKey==_T("F5"))
						vk=VK_F5;
					else
						if(pActivation->m_sHotKey==_T("F6"))
							vk=VK_F6;
						else
							if(pActivation->m_sHotKey==_T("F7"))
								vk=VK_F7;
							else
								if(pActivation->m_sHotKey==_T("F8"))
									vk=VK_F8;
								else
									if(pActivation->m_sHotKey==_T("F9"))
										vk=VK_F9;
									else
										if(pActivation->m_sHotKey==_T("F10"))
											vk=VK_F10;
										else
											return FALSE;
	
	return RegisterHotKey(GetSafeHwnd(),ID_HOTKEY,0,vk);
}

BOOL CPropertySheetCapture::AdjustToolTips() 
{
	return TRUE;
}

void CPropertySheetCapture::OnMinimize() 
{
	m_TaskbarIcon.SetOwner(NULL); // let taskbar icon do it
	// This is only one way to hide the dialog window. In real situation, you may
	// want to try DestroyWindow() to conserve system resource if possible (in this
	// demo, this dialog is the main window).
	ShowWindow(SW_HIDE);
}

void CPropertySheetCapture::OnButtonClose()
{
	// try to cleanup everything
	if(!CleanupCapture())
	{
		return;
	}

	// simulate pressing OK button to save all changes
	PressButton(PSBTN_OK);
}

// handling popup menu commands sent by the taskbar icon object
void CPropertySheetCapture::OnOpen()
{
	// try to cleanup everything
	if(!CleanupCapture())
	{
		return;
	}

	SetForegroundWindow();
	ShowWindow(SW_SHOW);
}

BOOL CPropertySheetCapture::CleanupCapture()
{
	// if we are capturing image then return unsuccess
	if(m_bIsCapturing)
	{
		return FALSE;
	}

	// unregister hot key if we close application
	// when capturing is started
	UnregisterHotKey(GetSafeHwnd(),ID_HOTKEY);

	// if we close while waiting for initial delay then
	// kill timer
	if(m_nTimerCaptureDelay!=0)
	{
		KillTimer(m_nTimerCaptureDelay);
		m_nTimerCaptureDelay=0;
	}

	// if we close while getting capture rectangular area then
	// release capture and remove helper window
	if(m_bGettingRectArea)
	{
		ReleaseCapture();
		RemoveTrackingHelper();
		m_bGettingRectArea=FALSE;
	}

	return TRUE;
}

void CPropertySheetCapture::DoCapture()
{
	m_bIsCapturing=TRUE;

	// get needed property pages
	CPropertyPageSource* pSource=(CPropertyPageSource*)GetPage(1);
	CPropertyPagePreferences* pPreferences=(CPropertyPagePreferences*)GetPage(5);

	// hide TaskbarIcon if needed
	if(pPreferences->m_bHideIcon)
	{
		m_TaskbarIcon.Hide();
	}

	COXScreenGrabber ScreenGrabber;
	switch(pSource->m_nRadioCapturedArea)
	{
	case 0:
		{
			ScreenGrabber.GrabFullWindow(CWnd::GetActiveWindow());
			break;
		}
	case 1:
		{
			ScreenGrabber.GrabClientWindow(CWnd::GetActiveWindow());
			break;
		}
	case 2:
		{
			ScreenGrabber.GrabFullWindow(CWnd::GetDesktopWindow());
			break;
		}
	case 3:
		{
			m_bGettingRectArea=TRUE;
			
			// activate helper window
			SetTrackingHelper();
			SetCapture();

			return;
		}
	default:
		break;
	}

	// try to stream captured image to the destination(s)
	StreamCapture(ScreenGrabber.GetGrabDIB());
}

void CPropertySheetCapture::StreamCapture(COXDIB* pDIB)
{
	if(pDIB==NULL)
	{
		TRACE0("CPropertySheetCapture::StreamCapture - pDIB==NULL");
		return;
	}

	CSize sizeDIB=pDIB->GetSize();
	if(sizeDIB.cx==0 && sizeDIB.cy==0)
	{
		TRACE0("CPropertySheetCapture::StreamCapture - pDIB is empty");
		return;
	}

	// get needed property pages
//	CPropertyPageActivation* pActivation=(CPropertyPageActivation*)GetPage(0);
//	CPropertyPageSource* pSource=(CPropertyPageSource*)GetPage(1);
	CPropertyPageDestination* pDestination=(CPropertyPageDestination*)GetPage(2);
	CPropertyPageImage* pImage=(CPropertyPageImage*)GetPage(3);
	CPropertyPageFile* pFile=(CPropertyPageFile*)GetPage(4);
	CPropertyPagePreferences* pPreferences=(CPropertyPagePreferences*)GetPage(5);

	// resize image if needed
	if(pImage->m_bResize)
	{
		UINT nHeight,nWidth;
		nHeight=pImage->m_nHeight;
		nWidth=pImage->m_nWidth;

		// take into account aspect ratio if needed
		if(pImage->m_bMaintainRatio)
		{
			nHeight=(UINT)(((long)nWidth*(long)sizeDIB.cy)/
				((long)sizeDIB.cx));
		}

		if(sizeDIB.cx!=(int)nWidth || sizeDIB.cy!=(int)nHeight)
		{
			pDIB->ResizeDIB(nWidth,nHeight);
		}
	}

	// copy captured image to clipboard if needed
	if(pDestination->m_bClipboard)
	{
		SaveAsClipboard(pDIB);
	}

	// copy captured image to file if needed
	if(pDestination->m_bFile)
	{
		BOOL bSuccess=TRUE;
		// check if Capture Directory exists
		COXPathSpec pathSpec;
		if(!pathSpec.SetDirectory(pFile->m_sCaptureDir))
		{
			AfxMessageBox(_T("Specified Capture Directory is not valid!"));
			bSuccess=FALSE;
		}
		else
		{
			CString sFileName;
			if(pFile->m_bAutomaticNaming)
			{
				// check if we are capable of automatically naming Capture File
				if(!pathSpec.MakeUnique())
				{
					AfxMessageBox(_T("Cannot automatically name file!"));
					bSuccess=FALSE;
				}
				sFileName=pathSpec.GetBaseName();
			}
			else
			{
				sFileName=pFile->m_sFileName;
			}
			if(bSuccess)
			{
				if(pFile->m_sFileType==CString(_T("Windows Bitmap (*.bmp)")))
				{
					sFileName+=CString(".bmp");
				}
				else
				{
					if(pFile->m_sFileType==CString(_T("JPEG Bitmap (*.jpg)")))
					{
						sFileName+=CString(".jpg");
					}
					else
					{
						if(pFile->m_sFileType==CString(_T("GIF Image (*.gif)")))
						{
							sFileName+=CString(".gif");
						}
					}
				}

			// check if we are capable of creating Capture File
				if(!pathSpec.SetFileName(sFileName))
				{
					AfxMessageBox(_T("Specified Capture Path is not valid"),
						MB_OK|MB_ICONEXCLAMATION);
					bSuccess=FALSE;
				}
			}
		}

		// save captured image to file
		if(bSuccess)
		{
			if(pFile->m_sFileType==CString(_T("Windows Bitmap (*.bmp)")))
			{
				SaveAsBMP(pDIB,pathSpec.GetPath());
			}
			else
			{
				if(pFile->m_sFileType==CString(_T("JPEG Bitmap (*.jpg)")))
				{
					SaveAsJPEG(pDIB,pathSpec.GetPath());
				}
				else
				{
					if(pFile->m_sFileType==CString(_T("GIF Image (*.gif)")))
					{
						SaveAsGIF(pDIB,pathSpec.GetPath());
					}
				}
			}
		}
	}

	// restore TaskbarIcon if it was hidden
	if(pPreferences->m_bHideIcon)
	{
		m_TaskbarIcon.Show();
	}

	m_bIsCapturing=FALSE;

	// notify about end of capture if needed
	if(pPreferences->m_bNotifyEnd)
	{
		AfxMessageBox(_T("The capture has been completed!"),
			MB_OK|MB_ICONINFORMATION);
	}
}

BOOL CPropertySheetCapture::SaveAsClipboard(COXDIB* pDIB) 
{
	if(!OpenClipboard())
	{
		AfxMessageBox("Cannot open the Clipboard!");
		return FALSE;
	}

	// Remove the current Clipboard contents
	if(!::EmptyClipboard())
	{
		AfxMessageBox("Cannot empty the Clipboard!");
		::CloseClipboard();
		return FALSE;
	}

	// create a copy of DIB image 
	HDIB hDIB=pDIB->MakeCopy();
	// For the appropriate data formats...
	if(::SetClipboardData(CF_DIB, hDIB)==NULL)
	{
		AfxMessageBox( "Unable to set Clipboard data!" );
		::CloseClipboard();
		return FALSE;
	}
	// ...
	::CloseClipboard();
	return TRUE;
}

BOOL CPropertySheetCapture::SaveAsBMP(COXDIB* pDIB, LPCTSTR lpszPathName) 
{
	BOOL bSuccess=FALSE;

	// try to open or create file
	CFile m_file;
	TRY
	{
		bSuccess=m_file.Open(lpszPathName,CFile::modeCreate|CFile::modeReadWrite);
	}
	CATCH(CFileException,e)
	{
		TCHAR szCause[255];
        CString strFormatted;
        e->GetErrorMessage(szCause, 255);
        strFormatted = _T("CPropertySheetCapture::SaveAsBMP:exception: ");
        strFormatted += szCause;
        TRACE(strFormatted);
	}
	END_CATCH

	if(!bSuccess)
	{
		CString sMessage;
		sMessage.Format(_T("Cannot open or create %s!"),lpszPathName);
		AfxMessageBox(sMessage);
		return FALSE;
	}

	CArchive ar(&m_file, CArchive::store);
	bSuccess=pDIB->Write(ar);
	ar.Close();

	return bSuccess;
}

BOOL CPropertySheetCapture::SaveAsJPEG(COXDIB* pDIB, LPCTSTR lpszPathName) 
{
	BOOL bSuccess=FALSE;

	BeginWaitCursor();

	// mem file for captured image
	CMemFile m_tmpBMPFile;
	CArchive ar(&m_tmpBMPFile, CArchive::store);
	bSuccess=pDIB->Write(ar);
	ar.Close();
	m_tmpBMPFile.SeekToBegin();

	// create bitmap file
	COXBMPFile BMPFile(&m_tmpBMPFile);
	COXJPEGFile jpgFile(lpszPathName);	
	COXJPEGCompressor JCompr;

	short nReturn(1);
	TCHAR ErrorBuffer[SIZE_ERROR_BUF];
	TRY
	{
		// the only line of code we need to convert bitmap to JPEG
		nReturn = JCompr.DoCompress(&BMPFile, &jpgFile);
		if (nReturn == 2)
			AfxMessageBox(JCompr.GetWarningMessages());
	}
	CATCH(COXJPEGException, e)
	{
		e->GetErrorMessage(ErrorBuffer, SIZE_ERROR_BUF);
		AfxMessageBox(CString("Exception : ") + ErrorBuffer);

		TRACE((LPCTSTR)ErrorBuffer);
	}
	END_CATCH

	EndWaitCursor();

	return nReturn==0 ? TRUE : FALSE;
}

BOOL CPropertySheetCapture::SaveAsGIF(COXDIB* pDIB, LPCTSTR lpszPathName) 
{
	UNREFERENCED_PARAMETER(pDIB);
	UNREFERENCED_PARAMETER(lpszPathName);
	return FALSE;


}

void CPropertySheetCapture::SetTrackingHelper()
{
	// set helper window for purpose of selecting rectangular area to capture
	LockWindowUpdate();
	g_pWndLastForeground=GetForegroundWindow();
	if(g_pWndLastForeground==NULL)
	{
		g_pWndLastForeground=GetDesktopWindow();
	}
	::SetCursor(AfxGetApp()->LoadCursor(IDC_OX_HAND_CURSOR));
	pWndTrackingHelper->SetWindowPos(&wndTopMost,0,0,::GetSystemMetrics(SM_CXSCREEN),
		::GetSystemMetrics(SM_CYSCREEN),SWP_SHOWWINDOW);
}

void CPropertySheetCapture::RemoveTrackingHelper()
{
	pWndTrackingHelper->SetWindowPos(&wndBottom,0,0,0,0,SWP_HIDEWINDOW);
	ASSERT(g_pWndLastForeground->m_hWnd != NULL);
	g_pWndLastForeground->SetForegroundWindow();
	UnlockWindowUpdate();
}

void CPropertySheetCapture::OnAppAbout()
{
	CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	dlgAbout.DoModal();
}

void CPropertySheetCapture::OnSize(UINT nType, int cx, int cy) 
{
	COXContextHelpPropertySheet::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_bInitialized)
	{
		m_LayoutManager.OnSize(cx,cy);
		GetTabControl()->GetWindowRect(&m_rectPage);
		GetTabControl()->AdjustRect(FALSE,&m_rectPage);
		ScreenToClient(&m_rectPage);
		GetActivePage()->MoveWindow(&m_rectPage);
	}
}

BOOL CPropertySheetCapture::OnNotify(WPARAM wParam, 
									 LPARAM lParam, LRESULT* pResult)
{
	BOOL result=COXContextHelpPropertySheet::OnNotify(wParam, lParam, pResult);
	
	if(result)
	{
		NMHDR* pnmh = (LPNMHDR) lParam;

		// the sheet resizes the page whenever it is activated
		// so we need to resize it to what we want
		if (TCN_SELCHANGE == pnmh->code)
		{
			// user-defined message needs to be posted because page must
			// be resized after TCN_SELCHANGE has been processed
			GetActivePage()->MoveWindow(&m_rectPage);
		}
	}

    return result;
}

void CPropertySheetCapture::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	COXContextHelpPropertySheet::OnGetMinMaxInfo(lpMMI);

//	lpMMI->ptMaxSize.x=540;
//	lpMMI->ptMaxSize.y=360;
//	lpMMI->ptMaxTrackSize.x=540;
//	lpMMI->ptMaxTrackSize.y=360;
	lpMMI->ptMinTrackSize.x=300;
//	lpMMI->ptMinTrackSize.y=240;
}

