///////////////////////////////////////////////////////////////////
//  Module   : WALLFLIP.CPP
//
//  Purpose  : Implementation of the WALLFLIP.EXE application.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-27-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WallFlip.h"
#include "FlipDlg.h"
#include <winreg.h>

///////////////////////////////////////////////////////////////////
// CWallFlipApp::InitInstance()

BOOL CWallFlipApp::InitInstance()
{
   CWallFlipDlg dlg;
   m_pMainWnd = &dlg;

   CString str = GetCommandLine();

   // Check command line for "/flip" switch
   if ((str.Find(" /flip") > 0) || (str.Find(" /FLIP") > 0))
   {
      // Flip the wallpaper and exit
      FlipWallpaper();
      m_pMainWnd = NULL;
      return FALSE;
   }

   // Display the dialog
   dlg.DoModal();

   // Flip the wallpaper
   FlipWallpaper();
   
   // Return FALSE and exit instead of starting the 
   // application's message pump...
   return FALSE;
}

///////////////////////////////////////////////////////////////////
// CWallFlipApp::FlipWallpaper()

void CWallFlipApp::FlipWallpaper()
{
   // Specify the registry location to get data from
   CString strKey = 
      "SOFTWARE\\TikiSoft\\WallFlip\\CurrentVersion";   

   // Open the registry key
   HKEY  hResult;
   if (ERROR_SUCCESS != RegOpenKey(HKEY_CURRENT_USER, 
       (LPCTSTR) strKey, &hResult))    
      return;

   // Get the number of bitmaps stored here
   BYTE   cBitmaps;
   DWORD  dwCount = sizeof(DWORD);

   if (ERROR_SUCCESS != RegQueryValueEx(hResult, 
       (LPCTSTR) "BitmapCount", 0, 0, &cBitmaps, &dwCount))
   {
     RegCloseKey(hResult);	 // Close the key
     return;
   }
   
   // Get the index of the next bitmap to use as wallpaper
   BYTE   cIndex;
   dwCount = sizeof(DWORD);

   if (!ERROR_SUCCESS == RegQueryValueEx(hResult, 
       (LPCTSTR) "NextBitmap", 0, 0, &cIndex, &dwCount))
   {
     RegCloseKey(hResult);	 // Close the key
     return;
   }

   // Get the filename for the new wallpaper bitmap
   CString str = "Bitmap" + IntToString((int)cIndex + 1);
   BYTE szBuf[255];
   dwCount = 255;

   RegQueryValueEx(hResult, (LPCTSTR) str,
      0, 0, &szBuf[0], &dwCount);

   RegCloseKey(hResult);	 // Close the key

   // Set the new value for "NextBitmap"
   if (cIndex >= cBitmaps - 1)
      cIndex = 0;
   else 
      cIndex++;

   CWallFlipDlg* pDlg = (CWallFlipDlg*) m_pMainWnd;
   pDlg->SetRegValue(HKEY_CURRENT_USER, strKey, 
      "NextBitmap", cIndex);

   // Specify the wallpaper registry key location
   strKey = "Control Panel\\Desktop";   

   // Set the new wallpaper filename
   pDlg->SetRegValue(HKEY_CURRENT_USER, strKey, "Wallpaper", 
      (CString) szBuf);
}

///////////////////////////////////////////////////////////////////
// CWallFlipApp::IntToString() - helper function

CString CWallFlipApp::IntToString(INT nNum)
{
   char szTemp[10];
   
   _itoa(nNum, szTemp, 10); // convert int to string
   return (CString)szTemp;
}

///////////////////////////////////////////////////////////////////
// Declare and run the application

CWallFlipApp MyApp;

///////////////////////////////////////////////////////////////////
