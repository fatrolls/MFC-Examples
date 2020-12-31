#if ! defined( WFC_LINKER_SETUP_HEADER_FILE )

#define WFC_LINKER_SETUP_HEADER_FILE

/*
** Now that we've included all the necessary MFC stuff,
** it is safe to set the linker options. Otherwise, we may
** get a LNK2005 error. Apparently the order in which libs
** appear on the link line is significant. That reminds me
** of the old Unix days.
** The knowledge base article that explains this is Q148652
** http://support.microsoft.com/support/kb/articles/q148/6/52.asp
*/

// Uncomment the following line to debug the link process
// #pragma comment( linker, "/verbose:lib" )

#if ! defined( MAKING_WFC )

#if ! defined( _AFX_NOFORCE_LIBS ) && defined( __AFX_H__ )

   // The programmer has already #include'f afx.h before wfc.h, we can't help them

   #pragma message( "WARNING: _AFX_NOFORCE_LIBS was not defined." )
   #pragma message( "Please #define _AFX_NOFORCE_LIBS before including wfc.h" )
   #pragma message( "If you do not #define _AFX_NOFORCE_LIBS you may get LNK2005 errors." )

#else

   #define _AFX_NOFORCE_LIBS

#endif // _AFX_NOFORCE_LIBS

#if ! defined( WFC_STL )

#if defined( _AFXDLL )

   #pragma message( "Using MFC in a Shared DLL." )

   // DLL Build of WFC
   #if defined( _DEBUG )

      #if ! defined( _UNICODE )

         // Link with the ANSI-debug build of the library
         #pragma message( "Linking with DebugBuildOfWFC.lib" )
         #pragma comment( lib, "DebugBuildOfWFC.lib" )
         #pragma comment( lib, "mfc42d.lib" )
         #pragma comment( lib, "mfcs42d.lib" )

      #else

         // Link with the UNICODE-debug build of the library
         #pragma message( "Linking with UnicodeDebugBuildOfWFC.lib" )
         #pragma comment( lib, "UnicodeDebugBuildOfWFC.lib" )
         #pragma comment( lib, "mfc42ud.lib" )
         #pragma comment( lib, "mfcs42ud.lib" )

      #endif // _UNICODE

   #else // _DEBUG

      #if ! defined( _UNICODE )

         // Link with the ANSI-Release build of the library
         #pragma message( "Linking with WFC.lib" )
         #pragma comment( lib, "WFC.lib" )
         #pragma comment( lib, "mfc42.lib" )
         #pragma comment( lib, "mfcs42.lib" )

      #else

         // Link with the UNICODE-Release build of the library
         #pragma message( "Linking with UnicodeWFC.lib" )
         #pragma comment( lib, "UnicodeWFC.lib" )
         #pragma comment( lib, "mfc42u.lib" )
         #pragma comment( lib, "mfcs42u.lib" )

      #endif // _UNICODE

   #endif // _DEBUG

#else // _AFXDLL

   #pragma message( "Using MFC in a Static Library" )

   // Static Linked version of WFC

   #if defined( _DEBUG )

      #if ! defined( _UNICODE )

         // Link with the ANSI-debug build of the library
         #pragma message( "Linking with StaticDebugBuildOfWFC" )
         #pragma comment( lib, "StaticDebugBuildOfWFC.lib" )
         #pragma comment( lib, "nafxcwd.lib" )

      #else

         // Link with the UNICODE-debug build of the library
         #pragma message( "Linking with StaticUnicodeDebugBuildOfWFC" )
         #pragma comment( lib, "StaticUnicodeDebugBuildOfWFC.lib" )
         #pragma comment( lib, "uafxcwd.lib" )

      #endif // _UNICODE

   #else // _DEBUG

      #if ! defined( _UNICODE )

         // Link with the ANSI-Release build of the library
         #pragma message( "Linking with StaticWFC" )
         #pragma comment( lib, "StaticWFC.lib" )
         #pragma comment( lib, "nafxcw.lib" )

      #else

         // Link with the UNICODE-Release build of the library
         #pragma message( "Linking with StaticUnicodeWFC" )
         #pragma comment( lib, "StaticUnicodeWFC.lib" )
         #pragma comment( lib, "uafxcw.lib" )

      #endif // _UNICODE

   #endif // _DEBUG

#endif // _AFXDLL

#else // WFC_STL

   #pragma message( "Using STL version of WFC." )

   #if defined( _DEBUG )

      // Debug build

      #if ! defined( _UNICODE )

         // Link with the ANSI-Debug build of the library
         #pragma message( "Linking with DebugBuildOfSTLWFC" )
         #pragma comment( lib, "DebugBuildOfSTLWFC.lib" )

      #else // _UNICODE

         // Link with the Unicode-Debug build of the library
         #pragma message( "Linking with DebugBuildOfUnicodeSTLWFC" )
         #pragma comment( lib, "DebugBuildOfUnicodeSTLWFC.lib" )

      #endif // _UNICODE

   #else // _DEBUG

      // Release build

      #if ! defined( _UNICODE )

         // Link with the ANSI-Release build of the library
         #pragma message( "Linking with STLWFC" )
         #pragma comment( lib, "STLWFC.lib" )

      #else // _UNICODE

         // Link with the ANSI-Release build of the library
         #pragma message( "Linking with UnicodeSTLWFC" )
         #pragma comment( lib, "UnicodeSTLWFC.lib" )

      #endif // _UNICODE

   #endif // _DEBUG   

#endif // WFC_STL

#if defined( _MT )

   #if defined( _DEBUG )

      #if defined( _DLL )

         // Using Debug multithreaded C Runtime in a DLL (MSVCRTD.DLL)
      #else // _DLL

         #pragma message( "WARNING! You are using Debug Multithreaded C Runtime in a static library(LIBCMTD.LIB)" )
         #pragma message( "WFC was built to use the Debug Multithreaded C Runtime in a DLL (MSVCRTD.DLL)" )

      #endif // _DLL

   #else // _DEBUG

      #if defined( _DLL )

         // Using Multithreaded C Runtime in a DLL (MSVCRT.DLL)

      #else // _DLL

         #pragma message( "WARNING! You are using Multithreaded C Runtime in a static library(LIBCMT.LIB)" )
         #pragma message( "WFC was built to use the Multithreaded C Runtime in a DLL (MSVCRT.DLL)" )

      #endif // _DLL

   #endif // _DEBUG

#else // _MT

   #if defined( _DEBUG )

      #if defined( _DLL )

         #pragma message( "Debug Single Threaded C Runtime in a DLL is not a valid option." )

      #else // _DLL

         #pragma message( "WARNING! You are using Debug Single Threaded C Runtime in a static library(LIBCD.LIB)" )
         #pragma message( "WFC was built to use the Debug Multithreaded C Runtime in a DLL (MSVCRTD.DLL)" )

      #endif // _DLL

   #else // _DEBUG

      #if defined( _DLL )

         #pragma message( "Single Threaded C Runtime in a DLL is not a valid option." )

      #else // _DLL

         #pragma message( "WARNING! You are using Single Threaded C Runtime in a static library(LIBC.LIB)" )
         #pragma message( "WFC was built to use the Multithreaded C Runtime in a DLL (MSVCRT.DLL)" )

      #endif // _DLL

   #endif // _DEBUG

#endif // _MT

// Other stuff from AFX.H header file

#ifdef _DLL
   #if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
      #pragma comment(lib, "msvcrtd.lib")
   #else
      #pragma comment(lib, "msvcrt.lib")
   #endif
#else
#ifdef _MT

   #pragma message( "Using Multi-Threaded C Runtime library." )

   #if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
      #pragma comment(lib, "libcmtd.lib")
   #else
      #pragma comment(lib, "libcmt.lib")
   #endif
#else

   #pragma message( "Using Single-Threaded C Runtime library." )

   #if !defined(_AFX_NO_DEBUG_CRT) && defined(_DEBUG)
      #pragma comment(lib, "libcd.lib")
   #else
      #pragma comment(lib, "libc.lib")
   #endif
#endif
#endif

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "comctl32.lib")

#if ! defined( WFC_STL )
// force inclusion of NOLIB.OBJ for /disallowlib directives
#pragma comment(linker, "/include:__afxForceEXCLUDE")

// force inclusion of DLLMODUL.OBJ for _USRDLL
#ifdef _USRDLL
#pragma comment(linker, "/include:__afxForceUSRDLL")
#endif

// force inclusion of STDAFX.OBJ for precompiled types
#ifdef _AFXDLL
#pragma comment(linker, "/include:__afxForceSTDAFX")
#endif

// From AFXCOM_.H
#pragma comment(lib, "uuid.lib")

// From AFXDAO.H
#pragma comment(lib, "daouuid.lib")

#ifdef _AFXDLL
   #if defined(_DEBUG) && !defined(_AFX_MONOLITHIC)
      #ifndef _UNICODE
         #pragma comment(lib, "mfco42d.lib")
         #pragma comment(lib, "mfcd42d.lib")
      #else
         #pragma comment(lib, "mfco42ud.lib")
         #pragma comment(lib, "mfcd42ud.lib")
      #endif
#endif
#endif // _AFXDLL

// From AFXDISP.H
#pragma comment(lib, "oledlg.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "olepro32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "urlmon.lib")

// From AFXISAPI.H
#if ! defined( IGNORE_AFXISAPI_LIBS )
#ifdef _AFXDLL
#ifdef _DEBUG
   #ifdef _UNICODE
      #pragma comment(lib, "MFCISUD.lib")
   #else
      #pragma comment(lib, "EAFXISD.lib")
   #endif
#else
   #ifdef _UNICODE
      #pragma comment(lib, "MFCISU.lib")
   #else
      #pragma comment(lib, "EAFXIS.lib")
   #endif // _UNICODE
#endif // _DEBUG
#else
#ifdef _DEBUG
   #ifdef _UNICODE
      #pragma comment(lib, "UAFXISD.lib")
   #else
      #pragma comment(lib, "NAFXISD.lib")
   #endif
#else
   #ifdef _UNICODE
      #pragma comment(lib, "UAFXIS.lib")
   #else
      #pragma comment(lib, "NAFXIS.lib")
   #endif // _UNICODE
#endif // _DEBUG
#endif // _AFXDLL
#endif // IGNORE_AFXISAPI_LIBS

// From AFXSOCK.H
#ifdef _AFXDLL
   #if defined(_DEBUG) && !defined(_AFX_MONOLITHIC)
      #ifndef _UNICODE
         #pragma comment(lib, "mfcn42d.lib")
      #else
         #pragma comment(lib, "mfcn42ud.lib")
      #endif
   #endif
#endif

#endif // WFC_STL

// Other libs required to build applications with WFC

// Get the NetRemoteTOD library
#pragma comment( lib, "netapi32.lib" )

// Get the RasAdmin library
#pragma comment( lib, "rassapi.lib" )

// Get the LZ compression library
#pragma comment( lib, "lz32.lib" )

// Get the library for WNetCloseEnum(), etc
#pragma comment( lib, "mpr.lib" )

#endif // MAKING_WFC

#endif // WFC_LINKER_SETUP_HEADER_FILE
