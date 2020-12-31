/******************************************************************
  Module   : MINSDK1.C

  Purpose  : Implementation of a minimal SDK program.

  Comments : This program does absolutely nothing useful...

  Author   : Rob McGregor, rob_mcgregor@compuserve.com
        
  Date     : 02-23-96
*******************************************************************/

#include <windows.h>

//
// Function prototypes
//
INT PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, INT);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//
// Global variables
//
HINSTANCE ghInst;       // current instance

char szAppName[] = "WinSdk1";                    // The app name
char szAppTitle[] = "A Minimal SDK Application"; // caption text

/******************************************************************
  Function : WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)

  Purpose  : Program entry point. Calls initialization function, 
             processes message loop.
*******************************************************************/

INT PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdParam, INT nCmdShow)
{
   HWND      hwndMain;     // main window handle
   MSG       message;      // window message
   WNDCLASS  wc;           // window class

   //
   // If no previous instance register the new window class
   //
   if (!hPrevInstance) // Are other instances of the app running?
   {
      wc.style         = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc   = WndProc;
      wc.cbClsExtra    = 0;
      wc.cbWndExtra    = 0;
      wc.hInstance     = hInstance;
      wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
      wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground = GetStockObject(WHITE_BRUSH);
      wc.lpszMenuName  = NULL;
      wc.lpszClassName = szAppName;

      // Register the window class with Windows
      RegisterClass (&wc);
   }

   //
   // Create the app window
   //
   hwndMain = CreateWindow (
      szAppName,             // window class name
      szAppTitle,            // window caption
      WS_OVERLAPPEDWINDOW,   // window style
      CW_USEDEFAULT,         // initial x position
      CW_USEDEFAULT,         // initial y position
      CW_USEDEFAULT,         // initial x size
      CW_USEDEFAULT,         // initial y size
      NULL,                  // parent window handle
      NULL,                  // window menu handle
      hInstance,             // program instance handle
      NULL                   // creation parameters
   );

   //
   // Make the window visible and update its client area
   //
   ShowWindow (hwndMain, SW_SHOWMAXIMIZED);
   UpdateWindow (hwndMain);

   //
   // Enter the program's message loop
   //
   while (GetMessage (&message, NULL, 0, 0))
   {
      TranslateMessage (&message);  // Show the window       
      DispatchMessage (&message);   // Sends WM_PAINT message
   }
   return message.wParam;
}

/******************************************************************
  Function : WndProc(HWND, UINT, WPARAM, LPARAM)

  Purpose  : Processes messages
*******************************************************************/

LRESULT CALLBACK WndProc(HWND hwndMain,  // window handle
                         UINT message,   // type of message
                         WPARAM wParam,  // additional information
                         LPARAM lParam)  // additional information
{
   //
   // Some local variables
   //
   char szAboutLeft[] = "This is a minimal Windows SDK program.\n"
                        "You've pressed the left mouse button!";

   char szAboutRight[] = "This is a minimal Windows SDK program.\n"
                         "You've pressed the right mouse button!";

   //
   // message handlers
   //
   switch (message)
   {
      case WM_LBUTTONDOWN:   // left mouse button pressed
      {
         MessageBeep(MB_ICONINFORMATION);
         MessageBox(GetFocus(), szAboutLeft, "About", 
                    MB_OK | MB_ICONINFORMATION);
         break;
      }
      case WM_RBUTTONDOWN:   // right mouse button pressed
      {
         MessageBeep(MB_ICONINFORMATION);
         MessageBox(GetFocus(), szAboutRight, "About", 
                    MB_OK | MB_ICONINFORMATION);
         break;
      }
      case WM_DESTROY:       // the window has been destroyed
      {
         PostQuitMessage(0);
         return 0;
      }
      default:
         break;
   }
   //
   // Send unhandled messages off to Windows for processing
   //
   return DefWindowProc (hwndMain, message, wParam, lParam);
}
