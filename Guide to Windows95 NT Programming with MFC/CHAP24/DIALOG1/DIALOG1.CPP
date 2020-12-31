///////////////////////////////////////////////////////////////////
//  Module   : DIALOG1.CPP
//
//  Purpose  : Implementation of an MFC program using common 
//             dialogs.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 05-18-96
///////////////////////////////////////////////////////////////////

#include "dialog1.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CMainWnd, CFrameWnd)

// Register a custom application-specific message
static UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_CREATE()
   ON_COMMAND(ID_FILE_CHOOSECOLOR, OnFileColor)
   ON_COMMAND(ID_FILE_EXIT, OnFileExit)
   ON_COMMAND(ID_FILE_FIND, OnFileFind)
   ON_COMMAND(ID_FILE_FONT, OnFileFont)
   ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
   ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
   ON_COMMAND(ID_FILE_PRINTSETUP, OnFilePrintSetup)
   ON_COMMAND(ID_FILE_REPLACE, OnFileReplace)
   ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveAs)
   ON_COMMAND(ID_FILE_PAGESETUP, OnFilePageSetup)
   ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
   ON_REGISTERED_MESSAGE(WM_FINDREPLACE, OnFindReplace)
END_MESSAGE_MAP()

// Status bar array
static UINT auIndicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{ 
   m_crBackColor     = crGray50;
   m_pdlgFindReplace = 0;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{  
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate()

int CMainWnd::OnCreate(LPCREATESTRUCT lpCS)
{
   // Create a status bar
   if (!m_wndStatusBar.Create(this))
   {
      TRACE0("Failed to create status bar\n");
      return -1;    
   }

   if (!m_wndStatusBar.SetIndicators(auIndicators,
       sizeof(auIndicators) / sizeof(UINT)))
   {
      TRACE0("Failed to set status bar indicators\n");
      return -1;    
   }

return 0;
}

///////////////////////////////////////////////////////////////////
//  CMainWnd message handlers
///////////////////////////////////////////////////////////////////
    
///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileColor()

void CMainWnd::OnFileColor() 
{
   // Construct the dialog with red selected initially
   CColorDialog dlgColor(crRed, CC_RGBINIT, this);

   // Display the dialog modally and
   // see if the user canceled the dialog
   if (IDOK == dlgColor.DoModal())
   {
      // Change the window color to the selected color
      SetClientColorRGB(dlgColor.GetColor());
   }
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFilePageSetup()

void CMainWnd::OnFilePageSetup() 
{
   // Construct the dialog with margins, and inches 
   //  as the unit of measure
   CPageSetupDialog dlgPage(
      PSD_MARGINS | PSD_INTHOUSANDTHSOFINCHES, 
      this);

   // Display the dialog modally and
   // see if the user canceled the dialog
   if (IDOK == dlgPage.DoModal())
   {
      // Get the page margins
      CRect rcMargins;
      dlgPage.GetMargins(&rcMargins, NULL);
      
      // Get the paper size
      CSize sizPaper;
      sizPaper = dlgPage.GetPaperSize();
      
      // Get the paper orientation
      CString strOrientation;
      LPDEVMODE lpdm = dlgPage.GetDevMode();

      switch (lpdm->dmOrientation)
      {
         case DMORIENT_PORTRAIT:
            strOrientation = "Portrait";
            break;

         case DMORIENT_LANDSCAPE:
            strOrientation = "Landscape";         
      }

      //
      // Format the info into nice looking strings for MessageBox()
      //
      
      CString str[3];

      str[0].Format("Paper Size: %1.2f\" x %1.2f\"\n\n",
         float(sizPaper.cx) / 1000, 
         float(sizPaper.cy) / 1000);

      str[1].Format(
         "Left Margin:\t%1.2f\"  \nRight Margin:\t%1.2f\" " \
         "\nTop Margin:\t%1.2f\" \nBottom Margin:\t%1.2f\" \n\n", 
         float(rcMargins.left)   / 1000, 
         float(rcMargins.right)  / 1000,
         float(rcMargins.top)    / 1000,
         float(rcMargins.bottom) / 1000);

      str[2] = "Paper Orientation: " + strOrientation;

      ::MessageBeep(MB_ICONASTERISK);
      MessageBox(str[0] + str[1] + str[2], "Page Setup Info", 
         MB_OK | MB_ICONINFORMATION);
   }
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileFont()

void CMainWnd::OnFileFont() 
{
   // Construct the font dialog
   LOGFONT lf;
   CFontDialog dlgFont(
      &lf, CF_TTONLY | CF_LIMITSIZE | CF_EFFECTS | CF_SCREENFONTS, 
      0, this);

   // Initalize the strikout and underline members
   lf.lfStrikeOut = FALSE;
   lf.lfUnderline = FALSE;

   // Specify text color and font size ranges for the dialog
   dlgFont.m_cf.rgbColors  = crBlue;
   dlgFont.m_cf.nSizeMin   = 5;    // min font point size
   dlgFont.m_cf.nSizeMax   = 120;  // max font point size
   dlgFont.m_cf.iPointSize = 10;   // initial point size
   
   // Initial fontname 
   lstrcpy(dlgFont.m_cf.lpLogFont->lfFaceName, "Arial");

   // Display the dialog
   if (IDCANCEL == dlgFont.DoModal()) 
      return;
                             
   //
   // The user didn't cancel, so display some text 
   // on the screen using the selected font
   //
   CClientDC dc(this);
   
   // Save the DC state, set the text background and color
   dc.SaveDC();
   dc.SetBkMode(TRANSPARENT);
   dc.SetTextColor(dlgFont.GetColor());

   // Create the new font per user selections
   CFont fnt;
   fnt.CreateFontIndirect(&dlgFont.m_lf);

   // Select the font into the DC
   dc.SelectObject(&fnt);

   // Prepare to draw some text
   CRect rc;
   GetClientRect(&rc);

   CString sSize = IntToString((int)(dlgFont.GetSize() / 10));
   CString str   = dlgFont.GetFaceName() + ", " + sSize + " pt: " +
      "ABC abc 123";
   
   // Save current state of, and reset, the client color flag
   // If we don't do this, the text we draw will be erased!
   BOOL bUseClientRGB = m_bUseClientRGB;
   m_bUseClientRGB = FALSE;
   
   // Draw the text
   dc.DrawText(str, &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

   // Restore client color flag
   m_bUseClientRGB = bUseClientRGB;

   // Restore the DC to saved state
   dc.RestoreDC(-1);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileOpen()

void CMainWnd::OnFileOpen() 
{
   // Set the file filter
   CString sFilter = 
      "C++ Files (*.cpp)|*.cpp|Header Files (*.h)|*.h||";
 
   // Construct the dialog
   CFileDialog dlgOpen(TRUE, 0, 0, OFN_HIDEREADONLY | 
      OFN_FILEMUSTEXIST, (LPCTSTR)sFilter, this);

   // Display the dialog modally and
   // see if the user canceled the dialog
   if (IDCANCEL == dlgOpen.DoModal())
      return;

   // Display the selected file name
   CString sMsg;
   sMsg.Format("You chose the file: \n%s", dlgOpen.GetPathName());
   MessageBeep(MB_ICONASTERISK);
   MessageBox(sMsg, "Open File", MB_OK | MB_ICONINFORMATION);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileSaveAs()

void CMainWnd::OnFileSaveAs() 
{
   // Set the file filter
   CString sFilter = 
      "C++ Files (*.cpp)|*.cpp|Header Files (*.h)|*.h||";
 
   // Construct the dialog
   CFileDialog dlgSave(FALSE, 0, 0, OFN_HIDEREADONLY | 
      OFN_OVERWRITEPROMPT, (LPCTSTR)sFilter, this);

   // Display the dialog modally and
   // see if the user canceled the dialog
   if (IDCANCEL == dlgSave.DoModal())
      return;

   // Display the selected file name
   CString sMsg;
   sMsg.Format("You chose to save to the file: \n%s", dlgSave.GetPathName());
   ::MessageBeep(MB_ICONASTERISK);
   MessageBox(sMsg, "Save File As", MB_OK | MB_ICONINFORMATION);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileExit()

void CMainWnd::OnFileExit() 
{
   DestroyWindow();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::InitFindReplace()

void CMainWnd::InitFindReplace(BOOL bFind) 
{
   //
   // If the dialog has been called already, and then closed,
   // the pointer is still non-NULL, but the object is already
   // dead, so reset the pointer!
   //
   m_pdlgFindReplace = NULL;

   // Construct the dialog
   m_pdlgFindReplace = new CFindReplaceDialog;
   ASSERT(m_pdlgFindReplace != NULL);

   // Initialize the dialog
   if (!m_pdlgFindReplace->Create(bFind, 0, 0, FR_DOWN, this))
   {
      TRACE0("Error creating find/replace dialog!");
      m_pdlgFindReplace = NULL;
      return;
   }
 
   // Display the dialog
   ASSERT(m_pdlgFindReplace != NULL);
   m_pdlgFindReplace->SetActiveWindow();
   m_pdlgFindReplace->ShowWindow(SW_SHOW);
}

///////////////////////////////////////////////////////////////////
// OnFileFind() and OnFileReplace()

void CMainWnd::OnFileFind() 
   { InitFindReplace(TRUE); }

void CMainWnd::OnFileReplace() 
   { InitFindReplace(FALSE); }

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFilePrintSetup()

void CMainWnd::OnFilePrintSetup() 
{
   // Construct the Print Setup dialog
   CPrintDialog dlgPrint(TRUE);

   // Display the dialog modally
   dlgPrint.DoModal();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFilePrint()

void CMainWnd::OnFilePrint() 
{
   // Construct the Print dialog
   CPrintDialog dlgPrint(FALSE);

   // Display the dialog modally and
   // see if the user canceled the dialog
   if (IDOK == dlgPrint.DoModal())
   {
      // Call custom print method here      
   }
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnHelpAbout()

void CMainWnd::OnHelpAbout() 
{
   CString str;
   if (str.LoadString(IDS_HELP_ABOUT))
   {
      ::MessageBeep(MB_ICONASTERISK);
      AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);
   }
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFindReplace()

LONG CMainWnd::OnFindReplace(WPARAM wParam, LPARAM lParam)
{
   CString sMsg;

   // Get a pointer to the calling dialog
   CFindReplaceDialog* pDlg = 
      CFindReplaceDialog::GetNotifier(lParam);
   ASSERT(pDlg != NULL);
   
   // See what the user is up to out there...
   if (pDlg->IsTerminating()) 
   {
      // Time to kill the dialog box
      sMsg = "Terminating dialog...";
      MessageBeep(MB_ICONASTERISK);
      AfxMessageBox(sMsg, MB_ICONINFORMATION | MB_OK);
      return 0;
   }

   if (pDlg->ReplaceAll())
   {   
      // Put a call to your ReplaceAll() method here...
      sMsg = "Replacing all...";
      MessageBeep(MB_ICONASTERISK);
      AfxMessageBox(sMsg, MB_ICONINFORMATION | MB_OK);
      return 0;
   }
   
   if (pDlg->ReplaceCurrent()) 
   {   
      // Put a call to your ReplaceCurrent() method here...
      sMsg = "Replacing current...";
      MessageBeep(MB_ICONASTERISK);
      AfxMessageBox(sMsg, MB_ICONINFORMATION | MB_OK);
      return 0;
   }
   
   if (pDlg->SearchDown()) 
   {
      // Put a call to your Search() method here...
      sMsg = "Searching down...";
   }
   else
   {   // Put a call to your Search() method here...
      sMsg = "Searching up...";
   }
   MessageBeep(MB_ICONASTERISK);
   AfxMessageBox(sMsg, MB_ICONINFORMATION | MB_OK);

   return 0;
}

///////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - overrides CWinApp::InitInstance

BOOL CMyApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd();

   // Initialize the frame window
   pFrame->LoadFrame(IDR_MAINFRAME, 
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;
   pFrame->SetClientBackColor(COLOR_APPWORKSPACE);

   // Show the frame window, centered
   pFrame->CenterWindow();
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CMyApp MyApp;

///////////////////////////////////////////////////////////////////
