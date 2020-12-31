/******************************************************************
  Module   : SDKWIN2.C

  Purpose  : Implementation of a minimal SDK application with a 
             more realistic program structure.

  Comments : This program does absolutely nothing useful...

  Author   : Rob McGregor, rob_mcgregor@compuserve.com
        
  Date     : 02-23-96
*******************************************************************/

#include <windows.h>

//
// Function prototypes
//
INT PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, INT);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, INT);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//
// Global variables
//
HINSTANCE ghInst;       // current instance

char szAppName[] = "WinSdk2";                       // The app name
char szAppTitle[] = "Another Minimal SDK Application"; // caption text

/******************************************************************
  Function : WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)

  Purpose  : Program entry point. Calls initialization function, 
             processes message loop.
*******************************************************************/

INT PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdParam, INT nCmdShow)
{
   MSG message;   // window message

   //
   // If no previous instance register the new window class
   //
   if (!hPrevInstance) // Are other instances of the app running?
   {       
      // Initialize 1st instance 
      if (!InitApplication(hInstance)) 
      { 
         return (FALSE);  // Exits if unable to initialize
      }
   }

   // Perform initializations that apply to a specific instance
   if (!InitInstance(hInstance, SW_SHOWMAXIMIZED)) 
   {
      return (FALSE);
   }

   //
   // Enter the application message loop. Get and dispatch  
   // messages until a WM_QUIT message is received
   //
   while (GetMessage(&message, NULL, 0, 0))
   {
      TranslateMessage(&message);  // Translates virtual key codes
      DispatchMessage(&message);   // Dispatches message to window
   }
   return (message.wParam); // Returns value from PostQuitMessage
}

/******************************************************************
  Function : InitApplication(HINSTANCE)

  Purpose  : Initializes window data and registers window class.
*******************************************************************/

BOOL InitApplication(HINSTANCE hInstance)
{
   WNDCLASS  wc;

   //
   // Fill in window class structure with parameters  
   // that describe the main window
   //
   wc.style         = CS_HREDRAW | CS_VREDRAW; 
   wc.lpfnWndProc   = (WNDPROC)WndProc;        
   wc.cbClsExtra    = 0;                      
   wc.cbWndExtra    = 0;                     
   wc.hInstance     = hInstance;               
   wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wc.lpszMenuName  = NULL;
   wc.lpszClassName = szAppName;

   // Register the window class and return success or failure
   return (RegisterClass(&wc));
}

/******************************************************************
  Function : InitInstance(HINSTANCE, int)

  Purpose  : Saves instance handle and creates main window
*******************************************************************/

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hwndMain;      // Main window handle.

   ghInst = hInstance; // Store instance handle in global variable

   //
   // Create a main window for this application instance.
   //
   hwndMain = CreateWindow(
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
   // Return FALSE if window handle is NULL 
   // (window not could not be created)
   //
   if (!hwndMain) 
   {
      return (FALSE);
   }

   //
   // Make the window visible and update its client area
   //
   ShowWindow(hwndMain, SW_SHOWMAXIMIZED); // Show the window
   UpdateWindow(hwndMain);                 // Sends WM_PAINT message

   return (TRUE);                          // Success!
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
      case WM_DESTROY:       // the window is being destroyed
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
   return (DefWindowProc (hwndMain, message, wParam, lParam));
}
