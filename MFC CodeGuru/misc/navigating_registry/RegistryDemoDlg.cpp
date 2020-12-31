// RegistryDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RegistryDemo.h"
#include "RegistryDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegistryDemoDlg dialog

CRegistryDemoDlg::CRegistryDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegistryDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegistryDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegistryDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegistryDemoDlg)
	DDX_Control(pDX, IDC_EDIT, m_EditBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegistryDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CRegistryDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegistryDemoDlg message handlers

BOOL CRegistryDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	bool okToPlace = theApp.mPrefs.SectionExists("CRegistryDemoDlg");
	theApp.mPrefs.Descend("CRegistryDemoDlg");

	// Restore the position of the dialog
	if (okToPlace)
	{
		WINDOWPLACEMENT wndInfo;
		wndInfo.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(&wndInfo);

		theApp.mPrefs.Restore("flags", wndInfo.flags);
		theApp.mPrefs.Restore("showCmd", wndInfo.showCmd);
		theApp.mPrefs.Restore("ptMinPosition.x", wndInfo.ptMinPosition.x);
		theApp.mPrefs.Restore("ptMinPosition.y", wndInfo.ptMinPosition.y);
		theApp.mPrefs.Restore("ptMaxPosition.x", wndInfo.ptMaxPosition.x);
		theApp.mPrefs.Restore("ptMaxPosition.y", wndInfo.ptMaxPosition.y);
		theApp.mPrefs.Restore("rcNormalPosition.left", wndInfo.rcNormalPosition.left);
		theApp.mPrefs.Restore("rcNormalPosition.top", wndInfo.rcNormalPosition.top);
		theApp.mPrefs.Restore("rcNormalPosition.right", wndInfo.rcNormalPosition.right);
		theApp.mPrefs.Restore("rcNormalPosition.bottom", wndInfo.rcNormalPosition.bottom);

		SetWindowPlacement(&wndInfo);
	}

	// Restore the text in the edit box
	CString editBoxCaption = "Type something here";
	theApp.mPrefs.Restore("edit box", editBoxCaption);
	m_EditBox.SetWindowText(editBoxCaption);

	float f = 0;
	theApp.mPrefs.Restore("float", f);

	double d = 0;
	theApp.mPrefs.Restore("double", d);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRegistryDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	// Store the position of the dialog
	WINDOWPLACEMENT wndInfo;
	if (GetWindowPlacement(&wndInfo))
	{
		theApp.mPrefs.Store("flags", wndInfo.flags);
		theApp.mPrefs.Store("showCmd", wndInfo.showCmd);
		theApp.mPrefs.Store("ptMinPosition.x", wndInfo.ptMinPosition.x);
		theApp.mPrefs.Store("ptMinPosition.y", wndInfo.ptMinPosition.y);
		theApp.mPrefs.Store("ptMaxPosition.x", wndInfo.ptMaxPosition.x);
		theApp.mPrefs.Store("ptMaxPosition.y", wndInfo.ptMaxPosition.y);
		theApp.mPrefs.Store("rcNormalPosition.left", wndInfo.rcNormalPosition.left);
		theApp.mPrefs.Store("rcNormalPosition.top", wndInfo.rcNormalPosition.top);
		theApp.mPrefs.Store("rcNormalPosition.right", wndInfo.rcNormalPosition.right);
		theApp.mPrefs.Store("rcNormalPosition.bottom", wndInfo.rcNormalPosition.bottom);
	}
	
	theApp.mPrefs.Ascend();
}

void CRegistryDemoDlg::OnOK() 
{
	// Store the text from the edit box
	CString editBoxCaption;
	m_EditBox.GetWindowText(editBoxCaption);
	theApp.mPrefs.Store("edit box", editBoxCaption);

	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegistryDemoDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRegistryDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
