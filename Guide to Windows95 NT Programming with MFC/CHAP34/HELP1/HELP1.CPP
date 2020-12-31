///////////////////////////////////////////////////////////////////
//  Header  : HELP1.CPP
//
//  Purpose : Implementation of the HELP1 program that shows 
//            how to use WinHelp Help files in an MFC program.
//            
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 03-31-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Help1.h"
#include "Help1Dlg.h"

///////////////////////////////////////////////////////////////////
// CHelp1App
///////////////////////////////////////////////////////////////////

// CHelpApp message map
BEGIN_MESSAGE_MAP(CHelp1App, CWinApp)
  ON_COMMAND(ID_HELP, OnHelp)       // Help handler
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CHelp1App::InitInstance() - application initialization

BOOL CHelp1App::InitInstance()
{
   CHelp1Dlg dlg;

   // Assign the CHelpDlg dialog as the application's main window 
   m_pMainWnd = &dlg;

   // Execute the CHelpDlg dialog modally
   int nResponse = dlg.DoModal();

   // The dialog has closed, so return FALSE and quit execution
   // instead of entering the application's message pump
   return FALSE;
}

///////////////////////////////////////////////////////////////////
// CHelp1App::OnHelp()  

void CHelp1App::OnHelp()
{
   // Find the control the user wants context-sensitive help for
   // IDCANCEL = 2 (#define'd in WINUSER.H)
   //
   INT nControl = GetHelpControl(IDCANCEL, IDC_CHECK3);
   switch (nControl)
   {
      case IDCANCEL:
         WinHelp(HIDCANCEL, HELP_CONTEXTPOPUP);
         break;

      case IDC_BTNHELP:
         WinHelp(HID_HELP, HELP_CONTEXTPOPUP);
         break;

      case IDC_EDIT1:
         WinHelp(HIDC_EDIT1, HELP_CONTEXTPOPUP);
         break;

      case IDC_EDIT2:
         WinHelp(HIDC_EDIT2, HELP_CONTEXTPOPUP);
         break;

      case IDC_CHECK1:
         WinHelp(HIDC_CHECK1, HELP_CONTEXTPOPUP);
         break;

      case IDC_CHECK2:
         WinHelp(HIDC_CHECK2, HELP_CONTEXTPOPUP);
         break;

      case IDC_CHECK3:
         WinHelp(HIDC_CHECK3, HELP_CONTEXTPOPUP);
         break;
      
      // Ok, no control found, so show default help
      default:
         WinHelp(HIDD_HELP1_DIALOG, HELP_CONTEXT);
   }
}

///////////////////////////////////////////////////////////////////
// CHelp1App::GetHelpControl()  

DWORD CHelp1App::GetHelpControl(DWORD nCtrlFirst, DWORD nCtrlLast)
{
   DWORD dwCurCtrl = 0;
   
   // Get the control under the cursor
   for (dwCurCtrl = nCtrlFirst; dwCurCtrl <= nCtrlLast; dwCurCtrl++)
   {
      //-----------------------------------------------------------
      // Show default help if the user clicked the Help button
      // and its ID falls within this range. (ID_HELP = 0xE146, 
      // #define'd in AFXRES.H) In this program it doesn't, but 
      // in others it might - it depends on the control IDs used...
      //-----------------------------------------------------------
            
      if (dwCurCtrl == ID_HELP) return 0;

      // Ok, it wasn't the Help button, so get a pointer to the 
      // control with ID "dwCurCtrl"
      //
      CWnd* pWnd = m_pMainWnd->GetDlgItem(dwCurCtrl);
      if (!pWnd) continue;

      // Get the position of the mouse cursor
      CPoint pt;
      GetCursorPos(&pt);

      // See if this one's under the cursor
      CRect rc;
      pWnd->GetClientRect(&rc);
      pWnd->ScreenToClient(&pt);  // convert to local coordinates
      
      rc.NormalizeRect();
      if (rc.PtInRect(pt)) 
         return dwCurCtrl;  // found one!
   }
   return 0;  // no control found
}

///////////////////////////////////////////////////////////////////
// Declare and run the application

CHelp1App MyApp;

///////////////////////////////////////////////////////////////////
              