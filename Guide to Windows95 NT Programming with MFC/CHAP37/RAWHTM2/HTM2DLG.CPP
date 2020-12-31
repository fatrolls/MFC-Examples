///////////////////////////////////////////////////////////////////
// Module  : HTMLDLG.CPP
//
// Purpose : The main dialog class for the RAWHTML program.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 07-13-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RawHtm2.h"
#include "Htm2Dlg.h"

///////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
   CAboutDlg();
   enum { IDD = IDD_ABOUTBOX };

protected:
   // DDX/DDV support
   virtual void DoDataExchange(CDataExchange* pDX); 
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
   { CDialog::DoDataExchange(pDX); }

///////////////////////////////////////////////////////////////////
// CRawHtmlDlg::CRawHtmlDlg() - Constructor

CRawHtmlDlg::CRawHtmlDlg(CWnd* pParent)
   : CDialog(CRawHtmlDlg::IDD, pParent)
{
   m_strServer = "";
   m_strPath   = "";

   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRawHtmlDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);

   DDX_Control(pDX, IDCANCEL, m_btnClose);
   DDX_Control(pDX, IDOK, m_btnGo);
   DDX_Control(pDX, IDC_EDIT_URL, m_editUrl);
   DDX_Control(pDX, IDC_EDIT_HTML, m_editHtml);
}

///////////////////////////////////////////////////////////////////
// CRawHtmlDlg Message map

BEGIN_MESSAGE_MAP(CRawHtmlDlg, CDialog)
   ON_WM_SYSCOMMAND()
   ON_BN_CLICKED(IDOK, OnBtnGoClicked)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CRawHtmlDlg::OnInitDialog()

BOOL CRawHtmlDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   //
   // Add "About..." menu item to system menu. IDM_ABOUTBOX must
   // be in the system command range...
   //
   
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

   // Set the icon for the dialog 
   SetIcon(m_hIcon, FALSE);      // Set small icon
   SetIcon(m_hIcon, TRUE);       // Set big icon
   
   // Set the default URL
   m_editUrl.SetWindowText(
      "http://www.microsoft.com/msdownload/activex.htm");
   m_editUrl.SetFocus();

   return FALSE;  // m_editUrl has the focus!
}

//////////////////////////////////////////////////////////////////
// CRawHtmlDlg::OnSysCommand()

void CRawHtmlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

//////////////////////////////////////////////////////////////////
// CRawHtmlDlg::OnBtnGoClicked()

void CRawHtmlDlg::OnBtnGoClicked() 
{
   // Get the current URL
   CString strUrl;
   m_editUrl.GetWindowText(strUrl);

   // See if the URL looks valid
   if (strUrl.IsEmpty() || strUrl.Left(7) != "http://")
   {
      ::MessageBeep(MB_ICONASTERISK);
      AfxMessageBox("Sorry, http address required...", 
         MB_OK | MB_ICONINFORMATION);
      return;
   }

   // Parse the URL to get server name and file path (if any) 
   ParseURL(strUrl);

   // Initialize the Internet DLL
   CInternetSession* pSession = new CInternetSession("Raw HTML Reader");

   // See if the session is valid
   if (pSession == NULL)
   {
      ::MessageBeep(MB_ICONEXCLAMATION);
      AfxMessageBox("Internet session initialization failed!",
         MB_OK | MB_ICONEXCLAMATION);
      return;
   }

   // Initialize HTTP session
   CHttpConnection* pConnect = pSession->GetHttpConnection(m_strServer);

   // See if connection is valid
   if (pConnect == NULL)
   {
      ::MessageBeep(MB_ICONEXCLAMATION);
      AfxMessageBox("Internet connection failed!",
         MB_OK | MB_ICONEXCLAMATION);
    
      // Close session 
      pSession->Close();
      delete pSession;
      return;
   }
                                          
   // Open an HTTP request handle
   CHttpFile* pHttpFile = pConnect->OpenRequest("GET", m_strPath);

   // See if HTTP request handle is valid
   if (pHttpFile == NULL)
   {
      ::MessageBeep(MB_ICONEXCLAMATION);
      AfxMessageBox("HTTP request failed!",
         MB_OK | MB_ICONEXCLAMATION);

      // Close session handles and clean up
      pConnect->Close();
      pSession->Close();

      delete pConnect;
      delete pSession;

      return;
   }

   // Disable the user interface sending & processing request
   m_editUrl.EnableWindow(FALSE);
   m_btnGo.EnableWindow(FALSE);
   m_btnClose.EnableWindow(FALSE);

   // Display wait cursor
   CWaitCursor wait;  

   // Send the request
   BOOL bSendRequest = pHttpFile->SendRequest();
   
   if (bSendRequest)                                          
   {
      // Get the size of the requested file
      char achQueryBuf[16];
      DWORD dwFileSize;
      DWORD dwQueryBufLen = sizeof(achQueryBuf);
     
      BOOL bQuery = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, 
         achQueryBuf, &dwQueryBufLen, NULL);

      if (bQuery)
      {
         // The query succeeded, specify memory needed for file
         dwFileSize = (DWORD)atol(achQueryBuf);
      }
      else
      {
         // The query failed, so guess at a max file size
         dwFileSize = 10 * 1024;
      }

      // Allocate a buffer for the file data
      char* lpszBuf = new char[dwFileSize + 1];

      // Read the file
      UINT uBytesRead = pHttpFile->Read(lpszBuf, dwFileSize + 1);   

      // Display the raw HTML
      DisplayRawHtml(lpszBuf);

      // Clean up buffer
      delete [] lpszBuf;

      // Close all open Internet handles
      pHttpFile->Close(); 
      pConnect->Close();
      pSession->Close();

      // Clean up 
      delete pHttpFile; 
      delete pConnect;
      delete pSession;
   }
   
   // Enable the user interface
   m_btnGo.EnableWindow(TRUE);
   m_btnClose.EnableWindow(TRUE);
   m_editUrl.EnableWindow(TRUE);
}

//////////////////////////////////////////////////////////////////
// CRawHtmlDlg::ParseURL()
// Parses the URL to get the server and file names (if any)

void CRawHtmlDlg::ParseURL(CString& strUrl)
{
   if (strUrl.IsEmpty()) 
      return;

   // Strip off "http://"
   CString strTemp = strUrl.Mid(7) ; 
   
   // Check for a path after the host name
   int nSlash = strTemp.Find("/");

   if (nSlash != -1)  // There's a path specified, so grab it
   {
      m_strServer = strTemp.Left(nSlash);
      m_strPath   = strTemp.Mid(nSlash);
   }
   else
      m_strServer = strTemp;
}

//////////////////////////////////////////////////////////////////
// CRawHtmlDlg::DisplayRawHtml()

void CRawHtmlDlg::DisplayRawHtml(char* lpszBuffer)
{
   m_editHtml.SetWindowText((LPCTSTR)lpszBuffer);
}

//////////////////////////////////////////////////////////////////
