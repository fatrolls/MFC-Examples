// KillHRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KillHR.h"
#include "KillHRDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKillHRDlg dialog

CKillHRDlg::CKillHRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKillHRDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKillHRDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   m_strFileName = "";
}

void CKillHRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKillHRDlg)
	DDX_Control(pDX, IDC_EDITFILENAME, m_editFileName);
	DDX_Control(pDX, IDC_BTNGO, m_btnGo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKillHRDlg, CDialog)
	//{{AFX_MSG_MAP(CKillHRDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNGO, OnBtnGoClick)
	ON_EN_CHANGE(IDC_EDITFILENAME, OnChangeEditFileName)
	//}}AFX_MSG_MAP

	ON_WM_DROPFILES()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKillHRDlg::OnInitDialog()

BOOL CKillHRDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
   CenterWindow();
   DragAcceptFiles();

   m_editFileName.SetFocus();
   m_btnGo.EnableWindow(FALSE);
   
	return FALSE;  // return TRUE unless you set the focus to a control
}

void CKillHRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKillHRDlg::OnPaint() 
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
HCURSOR CKillHRDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKillHRDlg::OnBtnGoClick() 
{
   if (!FileExists(m_strFileName))
   {
      ::MessageBeep(MB_ICONHAND);
      AfxMessageBox(_T("File does not exist!"), MB_ICONSTOP | MB_OK);
      return;
   }
   StripHardReturns(m_strFileName);
}

void CKillHRDlg::OnChangeEditFileName() 
{
   CString str;
   m_editFileName.GetWindowText(str);
   m_strFileName = str;

   BOOL bEnable = (str.GetLength() > 0);
   m_btnGo.EnableWindow(bEnable); 
}

BOOL CKillHRDlg::FileExists(CString strFileName)
{
   CFile file;

   if (file.Open(_T(strFileName), CFile::modeRead, NULL))
   {
      file.Close;
      return TRUE;
   }
   return FALSE;
}

void CKillHRDlg::StripHardReturns(CString strFileName)
{
   //
   // Copy the source file to a new file, 
   //  stripping hard returns as needed...
   //

   CStdioFile      fileSource;
   CStdioFile      fileTarget;
   CFileException  fileException;

   // Create a new file name
   strFileName.MakeUpper();
   CString strNewFileName = strFileName;

   // Strip the extension (if any)
   int nDot = strNewFileName.Find('.');
   if (nDot > -1)
      strNewFileName = strNewFileName.Left(nDot);
   
   strNewFileName += ".DOC";
   
   // Make sure source and target are different!
   if (strFileName == strNewFileName)
   {
      ::MessageBeep(MB_ICONHAND);
      AfxMessageBox("Oops! Source and Target are the same!", 
         MB_OK | MB_ICONSTOP);
      return;
   }
   
   // Open the source file
   if (!fileSource.Open((LPCTSTR)strFileName, 
      CFile::modeRead | CFile::typeText, &fileException))
   {
       TRACE("Can't open file %s, error = %u\n",
    	    &strFileName, fileException.m_cause);
   }

   // Open the new file
   if (!fileTarget.Open((LPCTSTR)strNewFileName, 
      CFile::modeCreate | CFile::modeWrite | CFile::typeText), 
      &fileException)
   {
       TRACE("Can't open file %s, error = %u\n",
    	    &strNewFileName, fileException.m_cause);
   }

   CString strLine;
   CString strHR;
   strHR.Format("\r\n\r\n");
      
   // Read until end of file
   while (fileSource.ReadString(strLine))
   {
      // Strip the hard return
      strLine.TrimLeft();
      if (strLine.GetLength() > 0)
      {
         strLine.TrimRight();
         strLine += " ";
      }
      else
         fileTarget.WriteString(strHR);

      // Write the line to the target file
      fileTarget.WriteString(_T(strLine));
   }
   fileSource.Close();
   fileTarget.Close();

   ::MessageBeep(MB_ICONASTERISK);
   AfxMessageBox("Done!", MB_ICONINFORMATION | MB_OK);

   CString strWrite = "Write " + strNewFileName; 
   ::WinExec((LPCSTR)(LPCTSTR)strWrite, SW_SHOWMAXIMIZED);
}

void CKillHRDlg::OnDropFiles(HDROP hDrop)
{
   // Allocate a buffer for the filename
   char* lpszFileName = new char[512];

   // Get the filename
   UINT nChars = ::DragQueryFile(hDrop, 0, &lpszFileName[0], 512);

   // Free the memory that Windows allocated for the file drop
   ::DragFinish(hDrop);

   // Display the file name
   CString str(&lpszFileName[0], nChars);
   m_editFileName.SetWindowText(str);

   // Clean up
   delete [] lpszFileName;
}

