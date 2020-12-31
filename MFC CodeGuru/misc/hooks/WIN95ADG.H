/******************************************************************************
Module name: Win95ADG.h
Purpose: Common header file 
         Contains handy macros and definitions used throughout
         the applications.
******************************************************************************/

/* Disable ridiculous warnings so that the code */
/* compiles cleanly using warning level 4.      */

/* nonstandard extension 'single line comment' was used */
#pragma warning(disable: 4001)

// nonstandard extension used : nameless struct/union
#pragma warning(disable: 4201)

// nonstandard extension used : bit field types other than int
#pragma warning(disable: 4214)

// Note: Creating precompiled header 
#pragma warning(disable: 4699)

// unreferenced inline function has been removed
#pragma warning(disable: 4514)

// unreferenced formal parameter
#pragma warning(disable: 4100)

// indirection to slightly different base types
#pragma warning(disable: 4057)

// named type definition in parentheses
#pragma warning(disable: 4115)

// nonstandard extension used : benign typedef redefinition
#pragma warning(disable: 4209)


//////////////////////// Windows Version Build Option /////////////////////////


#define WINVER 0x0400


////////////////////////// Application Build Option ///////////////////////////


// Force all EXEs/DLLs to be built for Windows 4.0. Comment out the following
// #pragma line to create applications that run under Windows NT 3.1 or Win32s.
// NOTE: Windows NT 3.5 and 3.51 run Win32 programs marked as 4.0.
//#pragma comment(lib, "kernel32 " "-subsystem:Windows")


///////////////////////////// STRICT Build Option /////////////////////////////


// Force all EXEs/DLLs to use STRICT type checking.
#define STRICT


/////////////////////////// CPU Portability Macros ////////////////////////////


// If no CPU platform was specified, default to the current platform.
#if !defined(_PPC_) && !defined(_ALPHA_) && !defined(_MIPS_) && !defined(_X86_)
   #if defined(_M_IX86)
      #define _X86_
   #endif
   #if defined(_M_MRX000)
      #define _MIPS_
   #endif
   #if defined(_M_ALPHA)
      #define _ALPHA_
   #endif
   #if defined(_M_PPC)
      #define _PPC_
   #endif
#endif

#if defined(_DEBUG)
   #define adgLIBBUILDTYPE "Dbg_"
#else
   #define adgLIBBUILDTYPE "Rel_"
#endif

#if defined(_X86_)
   #define adgLIBCPUTYPE "x86"
#elif defined(_MIPS_)
   #define adgLIBCPUTYPE "MIPS"
#elif defined(_ALPHA_)
   #define adgLIBCPUTYPE "Alph"
#elif defined(_PPC_)
   #define adgLIBCPUTYPE "PPC"
#else
   #error Win95ADG.h : Unknown CPU platform.
#endif


//////////////////////////// Unicode Build Option /////////////////////////////


// If we are not compiling for an x86 CPU, we always compile using Unicode.
#ifndef _X86_
#define UNICODE
#endif


// To compile using Unicode on the x86 CPU, uncomment the line below.
//#define UNICODE

// When using Unicode Win32 functions, use Unicode C-Runtime functions too.
#ifdef UNICODE
#define _UNICODE
#endif


///////////////////////////// adgARRAY_SIZE Macro /////////////////////////////


// This macro evaluates to the number of elements in an array. 
#define adgARRAY_SIZE(Array) (sizeof(Array) / sizeof((Array)[0]))


/////////////////////////////// adgINRANGE Macro //////////////////////////////


// This macro evaluates to TRUE if val is between lo and hi inclusive.
#define adgINRANGE(lo, val, hi) (((lo) <= (val)) && ((val) <= (hi)))


//////////////////////////// Assert/Verify Macros /////////////////////////////


#define adgFAIL(szMSG) {                                                  \
      MessageBox(GetActiveWindow(), szMSG,                                \
         __TEXT("Assertion Failed"), MB_OK | MB_ICONERROR);               \
      DebugBreak();                                                       \
   }

// Put up an assertion failure message box
#define adgASSERTFAIL(file,line,expr) {                                   \
      TCHAR sz[128];                                                      \
      wsprintf(sz, __TEXT("File %hs, line %d : %hs"), file, line, expr);  \
      adgFAIL(sz);                                                        \
   }

// Put up a message box if an assertion fails in a debug build
#ifdef _DEBUG
#define adgASSERT(x) if (!(x)) adgASSERTFAIL(__FILE__, __LINE__, #x)
#else
#define adgASSERT(x)
#endif

// Assert in debug builds, but don't remove the code in retail builds
#ifdef _DEBUG
#define adgVERIFY(x) adgASSERT(x)
#else
#define adgVERIFY(x) (x)
#endif


/////////////////////////// adgHANDLE_DLGMSG Macro ////////////////////////////


// The normal HANDLE_MSG macro in WINDOWSX.H does not work properly for dialog
// boxes because DlgProc's return a BOOL instead of an LRESULT (like
// WndProcs). This adgHANDLE_DLGMSG macro corrects the problem:
#define adgHANDLE_DLGMSG(hwnd, message, fn)                          \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,               \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))


////////////////////////// Window Extra Byte Macros ///////////////////////////


// Macros to compute the size and offset of structure members
#define adgMEMBEROFFSET(structure, member) (int) (&(((structure *)0)->member))

// Macros to compute offsets and get/set window values based on the layout of
// a structure.
#define adgSETWINDOWWORD(hwnd, structure, member, value) \
   SetWindowWord(hwnd, adgMEMBEROFFSET(structure, member), (WORD) (value))
#define adgSETWINDOWLONG(hwnd, structure, member, value) \
   SetWindowLong(hwnd, adgMEMBEROFFSET(structure, member), (LONG) (value))
#define adgGETWINDOWWORD(hwnd, structure, member) \
   GetWindowWord(hwnd, adgMEMBEROFFSET(structure, member))
#define adgGETWINDOWLONG(hwnd, structure, member) \
   GetWindowLong(hwnd, adgMEMBEROFFSET(structure, member))


/////////////////////////// Quick MessageBox Macro ////////////////////////////


#define adgMB(s) {                                                   \
      TCHAR szTMP[128];                                              \
      GetModuleFileName(NULL, szTMP, adgARRAY_SIZE(szTMP));          \
      MessageBox(GetActiveWindow(), s, szTMP, MB_OK);                \
   }


///////////////////////////// Zero Variable Macro /////////////////////////////


// Zero out a structure. If fInitSize is TRUE then initialize the first int to
// the size of the structure. Many structures like WNDCLASSEX and STARTUPINFO
// require that their first member be set to the size of the structure itself.
#define adgINITSTRUCT(structure, fInitSize)                          \
   (ZeroMemory(&(structure), sizeof(structure)),                     \
   fInitSize ? (*(int*) &(structure) = sizeof(structure)) : 0)


//////////////////////// Dialog Box Icon Setting Macro ////////////////////////


// The call to SetClassLong is for Windows NT 3.51 or less.  The WM_SETICON
// messages are for Windows 95 and future versions of NT.
#define adgSETDLGICONS(hwnd, idiLarge, idiSmall)                              \
   {                                                                          \
      OSVERSIONINFO VerInfo;                                                  \
      adgINITSTRUCT(VerInfo, TRUE);                                           \
      GetVersionEx(&VerInfo);                                                 \
      if ((VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) &&                  \
          (VerInfo.dwMajorVersion <= 3 && VerInfo.dwMinorVersion <= 51)) {    \
         SetClassLong(hwnd, GCL_HICON, (LONG)                                 \
            LoadIcon(GetWindowInstance(hwnd), MAKEINTRESOURCE(idiLarge)));    \
      } else {                                                                \
         SendMessage(hwnd, WM_SETICON, TRUE,  (LPARAM)                        \
            LoadIcon(GetWindowInstance(hwnd), MAKEINTRESOURCE(idiLarge)));    \
         SendMessage(hwnd, WM_SETICON, FALSE, (LPARAM)                        \
            LoadIcon(GetWindowInstance(hwnd), MAKEINTRESOURCE(idiSmall)));    \
      }                                                                       \
   }
    

///////////////////////////// UNICODE Check Macro /////////////////////////////


#ifdef UNICODE

#define adgWARNIFUNICODEUNDERWIN95()                                       \
   if (GetWindowsDirectoryW(NULL, 0) <= 0)                                 \
      MessageBoxA(NULL, "This operating system doesn't support Unicode.",  \
         NULL, MB_OK)

#else

#define adgWARNIFUNICODEUNDERWIN95()

#endif


////////////////// WM_CAPTURECHANGED Message Cracker Macros ///////////////////


// I have defined message cracker macros for the WM_CAPTURECHANGED message
// because Microsoft did not do this in the WINDOWSX.H header file.

/* void Cls_OnCaptureChanged(HWND hwnd, HWND hwndNewCapture) */
#define HANDLE_WM_CAPTURECHANGED(hwnd, wParam, lParam, fn) \
    ((fn)((hwnd), (HWND)(lParam)), 0L)
#define FORWARD_WM_CAPTURECHANGED(hwnd, hwndNewCapture, fn) \
    (void)(fn)((hwnd), WM_CAPTURECHANGED, (WPARAM)(HWND)(hwndNewCapture), 0L)


///////////////////////////////// End of File /////////////////////////////////
