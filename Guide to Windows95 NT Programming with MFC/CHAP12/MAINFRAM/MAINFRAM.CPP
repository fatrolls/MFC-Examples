///////////////////////////////////////////////////////////////////
// Module   : MAINFRAM.CPP
//
// Purpose  : Implementation of the CMainFrame class
//
// Comments : This class is used as the base frame window class 
//            for many of the sample programs in "Peter Norton's 
//            Guide to Windows 95/NT Programming with MFC."
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-05-96
///////////////////////////////////////////////////////////////////

#include "mainfram.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

// CMainFrame Message map
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//
// CMainFrame Methods
//

///////////////////////////////////////////////////////////////////
// CMainFrame::CMainFrame() - constructor 

CMainFrame::CMainFrame()
{
   // Initialize the font pointer
   m_pFont = 0;

   // Initialize logfont bytes
   memset(&m_lf, 0, sizeof(LOGFONT));

   // Initialize the client color & flag
   m_crClient      = crGray50;
   m_bUseClientRGB = FALSE;
}

///////////////////////////////////////////////////////////////////
// CMainFrame::~CMainFrame() - destructor 

CMainFrame::~CMainFrame()
{
   if (m_pFont) delete m_pFont;
}

///////////////////////////////////////////////////////////////////
// CMainFrame::OnEraseBkgnd()

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
   if (m_bUseClientRGB)
   {
      // We're explicitly painting the client area, so we 
      // don't want to call the inherited method...
      SetClientColorRGB(m_crClient);
      return TRUE;
   }
   // Otherwise call the inherited method
   return CFrameWnd::OnEraseBkgnd(pDC);
}    

///////////////////////////////////////////////////////////////////
// CMainFrame::CenterWindow() #1 

void CMainFrame::CenterWindow()
{
   // Default to centering on the screen
   CenterWindow(0);
}

///////////////////////////////////////////////////////////////////
// CMainFrame::CenterWindow() #2 

void CMainFrame::CenterWindow(CWnd* pWnd)
{
   //
   // Center *this window over pWnd (if possible)
   //

   // Get the pWnd window size
   CRect rcWnd;

   if (pWnd == NULL) 
      ::GetWindowRect(::GetDesktopWindow(), &rcWnd);
   else
      pWnd->GetWindowRect(&rcWnd); 

   // Get *this window size
   CRect rcThis;
   GetWindowRect(&rcThis);

   // Get the the screen size
   CRect rcScreen;
   ::GetWindowRect(::GetDesktopWindow(), &rcScreen);
   
   // Calculate new cx position
   int cx = rcWnd.left + ((rcWnd.Width() - rcThis.Width()) / 2);
   
   // Adjust for screen
   if (cx < 0) 
      cx = 0;
   else if ((cx + rcThis.Width()) > rcScreen.Width())
      cx = rcScreen.Width() - rcThis.Width();
   
   // Calculate new cy position
   int cy = rcWnd.top + ((rcWnd.Height() - rcThis.Height()) / 2);
   
   // Adjust for screen
   if (cy < 0) 
     cy = 0;
   else if ((cy + rcThis.Height()) > rcScreen.Height()) 
     cy = rcScreen.Height() - rcThis.Height();
   
   // Set the new position
   SetWindowPos (NULL, cx, cy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

///////////////////////////////////////////////////////////////////
// CMainFrame::CreateChildControls() - virtual placeholder 

void CMainFrame::CreateChildControls()
{
   // This is just a virtual placeholder method. Derived classes
   // will call this method to allocate and initialize child 
   // windows, and will perform these steps:
   //
   // 1. Allocate the child controls
   // 2. Set the positions of the child windows
   // 3. Initialize the child windows 
   // 4. Perform any other special tasks
}
 

///////////////////////////////////////////////////////////////////
// CMainFrame::GetClientHeight() - helper function

UINT CMainFrame::GetClientHeight()
{
   // Get the client area rectangle
   CRect rc;
   GetClientRect(&rc);

   // Return the height
   return rc.Height();
}

///////////////////////////////////////////////////////////////////
// CMainFrame::GetClientWidth() - helper function

UINT CMainFrame::GetClientWidth()
{
   // Get the client area rectangle
   CRect rc;
   GetClientRect(&rc);

   // Return the width
   return rc.Width();
}

///////////////////////////////////////////////////////////////////
// CMainFrame::GetWindowsVerInfo()

DWORD CMainFrame::GetWindowsVerInfo(DWORD &dwMajor, 
                                    DWORD &dwMinor, 
                                    DWORD &dwBuild)
{
   DWORD dwWinOS;
   DWORD dwVersion = GetVersion();

   // See which OS we're running under
   if (dwVersion < 0x80000000) 
   {
      // Windows NT, cool!
      dwWinOS = VER_PLATFORM_WIN32_NT;
      dwMajor = (DWORD)(LOBYTE(LOWORD(dwVersion)));
      dwMinor = (DWORD)(HIBYTE(LOWORD(dwVersion)));
      dwBuild = (DWORD)(HIWORD(dwVersion));
   }
   
   else if (LOBYTE(LOWORD(dwVersion)) < 4)
   {
      // Win32s, bummer...
      dwWinOS = VER_PLATFORM_WIN32s;
      dwMajor = (DWORD)(LOBYTE(LOWORD(dwVersion)));
      dwMinor = (DWORD)(HIBYTE(LOWORD(dwVersion)));
      dwBuild = (DWORD)(HIWORD(dwVersion) & ~0x8000);
   } 
   
   else 
   {
      // Okay, Windows 95!
      dwWinOS = VER_PLATFORM_WIN32_WINDOWS;
      dwMajor = (DWORD)(LOBYTE(LOWORD(dwVersion)));
      dwMinor = (DWORD)(HIBYTE(LOWORD(dwVersion)));
      dwBuild = (DWORD)(HIWORD(dwVersion) & ~0x8000);
   }    
   return dwWinOS;
}

///////////////////////////////////////////////////////////////////
// CMainFrame::ShowWindowsVerInfo() 

void CMainFrame::ShowWindowsVerInfo()
{
   CString sVerInfo;
   DWORD   dwMajor;
   DWORD   dwMinor;
   DWORD   dwBuild;
   DWORD   dwOS;

   dwOS = GetWindowsVerInfo(dwMajor, dwMinor, dwBuild);

   // Which OS?
   CString sVer;
   
   switch (dwOS)
   {
      case VER_PLATFORM_WIN32s:
         sVer = "Windows 3.x with Win32s";
         break;

      case VER_PLATFORM_WIN32_WINDOWS:
         sVer = "Windows 95";
         dwBuild = 0;  // Win95 provides no build numbers
         break;

      case VER_PLATFORM_WIN32_NT:
         sVer = "Windows NT";
         break;

      default:
         sVer = "OS unknown"; 
   }
   
   // Format the info
   sVerInfo.Format(
      "Operating System: %s\nVersion: %d.%d\nBuild: %d", 
      sVer, dwMajor, dwMinor, dwBuild); 

   // Show the Windows version
   MessageBox(sVerInfo, "Windows Version Info", 
      MB_ICONINFORMATION | MB_OK);
}

///////////////////////////////////////////////////////////////////
// CMainFrame::IntToString() - helper function

CString CMainFrame::IntToString(INT nNum)
{
   char szTemp[10];
   
   _itoa(nNum, szTemp, 10); // convert int to string
   return (CString)szTemp;
}

///////////////////////////////////////////////////////////////////
// CMainFrame::SetChildFonts() - helper function

void CMainFrame::SetChildFonts(INT nFirst, INT nLast,
                               CString szFont, LONG lSize)
{
   // Set a new font for each child control
   for (int i = nFirst; i <= nLast; i++)
   {
      CWnd* pWnd = GetDlgItem(i);

      // Set the new font for this window
      if (pWnd) SetWndFont(pWnd, szFont, lSize);
   }
}

///////////////////////////////////////////////////////////////////
// CMainFrame::SetClientBackColor()

void CMainFrame::SetClientBackColor(LONG lColor)
{
   ::SetClassLong(this->m_hWnd, GCL_HBRBACKGROUND, 
      (LONG)(HBRUSH)(lColor + 1));
}                                              

///////////////////////////////////////////////////////////////////
// CMainFrame::SetClientColorRGB()

void CMainFrame::SetClientColorRGB(COLORREF cr)
{
   CRect rc;
   CClientDC dc(this);
   
   // Set the new client color and update the color flag
   m_crClient = cr;
   m_bUseClientRGB = TRUE;

   // Save the current DC state
   dc.SaveDC();

   // Create a new brush
   CBrush br(m_crClient);

   // Select it into the DC
   dc.SelectObject(&br);

   // Repaint only the area needed
   dc.GetClipBox(&rc);  
   dc.PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);

   // Restore the original DC state
   dc.RestoreDC(-1);
}

///////////////////////////////////////////////////////////////////
// CMainFrame::SetWndFont() - helper function

void CMainFrame::SetWndFont(CWnd* pWnd, CString szFont, LONG lSize)
{
   // If the font has already been created, don't do it again!
   if (!m_pFont) 
   {
      // Create a new font
      m_pFont = new CFont;          
      ASSERT_VALID(m_pFont);
      
      // Init the LOGFONT struct
      memset(&m_lf, 0, sizeof(LOGFONT));

      // Set initial font typeface name
      lstrcpy(m_lf.lfFaceName, _T(szFont));

      // Set initial font size
      CWindowDC dcWnd(0);

      int cyPixels  = dcWnd.GetDeviceCaps(LOGPIXELSY);
      m_lf.lfHeight = -MulDiv(lSize, cyPixels, 72); 

      // Create the new font
      m_pFont->CreateFontIndirect(&m_lf);
   }

   // Change the font
   pWnd->SetFont(m_pFont, TRUE);
}

///////////////////////////////////////////////////////////////////
// CMainFrame::StringToInt() - helper function

INT CMainFrame::StringToInt(CString* psNum)
{
   return (INT)atol(psNum->GetBuffer(10)); // convert to int
}

///////////////////////////////////////////////////////////////////
