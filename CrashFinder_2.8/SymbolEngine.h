/*----------------------------------------------------------------------
"Debugging Applications" (Microsoft Press)
Copyright (c) 1997-2000 John Robbins -- All rights reserved.
------------------------------------------------------------------------
This class is a paper-thin layer around the DBGHELP.DLL symbol engine.

This class wraps only those functions that take the unique
HANDLE value. Other DBGHELP.DLL symbol engine functions are global in
scope, so I didn’t wrap them with this class.

------------------------------------------------------------------------
Compilation Defines:

USE_BUGSLAYERUTIL - If defined, the class will have another
                    initialization method, BSUSymInitialize, which will
                    use BSUSymInitialize from BUGSLAYERUTIL.DLL to
                    initialize the symbol engine and allow the invade
                    process flag to work for all Win32 operating systems.
                    If you use this define, you must use
                    BUGSLAYERUTIL.H to include this file.
----------------------------------------------------------------------*/

#ifndef _SYMBOLENGINE_H
#define _SYMBOLENGINE_H

#include "imagehlp.h"
#include <tchar.h>

// Include these in case the user forgets to link against them.
#pragma comment (lib,"dbghelp.lib")
#pragma comment (lib,"version.lib")

// The great Bugslayer idea of creating wrapper classes on structures
// that have size fields came from fellow MSJ columnist, Paul DiLascia.
// Thanks, Paul!

// I didn’t wrap IMAGEHLP_SYMBOL because that is a variable-size
// structure.

// The IMAGEHLP_MODULE wrapper class
struct CImageHlp_Module : public IMAGEHLP_MODULE64
{
    CImageHlp_Module ( )
    {
        memset ( this , NULL , sizeof ( IMAGEHLP_MODULE64 ) ) ;
        SizeOfStruct = sizeof ( IMAGEHLP_MODULE64 ) ;
    }
} ;

// The IMAGEHLP_LINE wrapper class
struct CImageHlp_Line : public IMAGEHLP_LINE64
{
    CImageHlp_Line ( )
    {
        memset ( this , NULL , sizeof ( IMAGEHLP_LINE64 ) ) ;
        SizeOfStruct = sizeof ( IMAGEHLP_LINE64 ) ;
    }
} ;

// The symbol engine class
class CSymbolEngine
{
/*----------------------------------------------------------------------
                  Public Construction and Destruction
----------------------------------------------------------------------*/
public      :
    // To use this class, call the SymInitialize member function to
    // initialize the symbol engine and then use the other member
    // functions in place of their corresponding DBGHELP.DLL functions.
    CSymbolEngine ( void )
    {
    }

    virtual ~CSymbolEngine ( void )
    {
    }

/*----------------------------------------------------------------------
                  Public Helper Information Functions
----------------------------------------------------------------------*/
public      :

    // Returns the file version of DBGHELP.DLL being used.
    //  To convert the return values into a readable format:
    //  wsprintf ( szVer                  ,
    //             _T ( "%d.%02d.%d.%d" ) ,
    //             HIWORD ( dwMS )        ,
    //             LOWORD ( dwMS )        ,
    //             HIWORD ( dwLS )        ,
    //             LOWORD ( dwLS )         ) ;
    //  szVer will contain a string like: 5.00.1878.1
    BOOL GetImageHlpVersion ( DWORD & dwMS , DWORD & dwLS )
    {
        return( GetInMemoryFileVersion ( _T ( "DBGHELP.DLL" ) ,
                                         dwMS                 ,
                                         dwLS                  ) ) ;
    }

    BOOL GetDbgHelpVersion ( DWORD & dwMS , DWORD & dwLS )
    {
        return( GetInMemoryFileVersion ( _T ( "DBGHELP.DLL" ) ,
                                         dwMS                 ,
                                         dwLS                  ) ) ;
    }

    // Returns the file version of the PDB reading DLLs
    BOOL GetPDBReaderVersion ( DWORD & dwMS , DWORD & dwLS )
    {
        // First try MSDBI.DLL.
        if ( TRUE == GetInMemoryFileVersion ( _T ( "MSDBI.DLL" ) ,
                                              dwMS               ,
                                              dwLS                ) )
        {
            return ( TRUE ) ;
        }
        else if ( TRUE == GetInMemoryFileVersion ( _T ( "MSPDB60.DLL" ),
                                                   dwMS                ,
                                                   dwLS               ))
        {
            return ( TRUE ) ;
        }
        // Just fall down to MSPDB50.DLL.
        return ( GetInMemoryFileVersion ( _T ( "MSPDB50.DLL" ) ,
                                          dwMS                 ,
                                          dwLS                  ) ) ;
    }

    // The worker function used by the previous two functions
    BOOL GetInMemoryFileVersion ( LPCTSTR szFile ,
                                  DWORD & dwMS   ,
                                  DWORD & dwLS    )
    {
        HMODULE hInstIH = GetModuleHandle ( szFile ) ;

        // Get the full filename of the loaded version.
        TCHAR szImageHlp[ MAX_PATH ] ;
        GetModuleFileName ( hInstIH , szImageHlp , MAX_PATH ) ;

        dwMS = 0 ;
        dwLS = 0 ;

        // Get the version information size.
        DWORD dwVerInfoHandle ;
        DWORD dwVerSize       ;

        dwVerSize = GetFileVersionInfoSize ( szImageHlp       ,
                                             &dwVerInfoHandle  ) ;
        if ( 0 == dwVerSize )
        {
            return ( FALSE ) ;
        }

        // Got the version size, now get the version information.
        LPVOID lpData = (LPVOID)new TCHAR [ dwVerSize ] ;
        if ( FALSE == GetFileVersionInfo ( szImageHlp       ,
                                           dwVerInfoHandle  ,
                                           dwVerSize        ,
                                           lpData            ) )
        {
            delete [] lpData ;
            return ( FALSE ) ;
        }

        VS_FIXEDFILEINFO * lpVerInfo ;
        UINT uiLen ;
        BOOL bRet = VerQueryValue ( lpData              ,
                                    _T ( "\\" )         ,
                                    (LPVOID*)&lpVerInfo ,
                                    &uiLen               ) ;
        if ( TRUE == bRet )
        {
            dwMS = lpVerInfo->dwFileVersionMS ;
            dwLS = lpVerInfo->dwFileVersionLS ;
        }

        delete [] lpData ;

        return ( bRet ) ;
    }

/*----------------------------------------------------------------------
                   Public Initialization and Cleanup
----------------------------------------------------------------------*/
public      :

    BOOL SymInitialize ( IN HANDLE   hProcess       ,
                         IN LPSTR    UserSearchPath ,
                         IN BOOL     fInvadeProcess  )
    {
        m_hProcess = hProcess ;
        return ( ::SymInitialize ( hProcess       ,
                                   UserSearchPath ,
                                   fInvadeProcess  ) ) ;
    }

#ifdef USE_BUGSLAYERUTIL
    BOOL BSUSymInitialize ( DWORD  dwPID          ,
                            HANDLE hProcess       ,
                            PSTR   UserSearchPath ,
                            BOOL   fInvadeProcess  )
    {
        m_hProcess = hProcess ;
        return ( ::BSUSymInitialize ( dwPID          ,
                                      hProcess       ,
                                      UserSearchPath ,
                                      fInvadeProcess  ) ) ;
    }
#endif  // USE_BUGSLAYERUTIL
    BOOL SymCleanup ( void )
    {
        return ( ::SymCleanup ( m_hProcess ) ) ;
    }

/*----------------------------------------------------------------------
                       Public Module Manipulation
----------------------------------------------------------------------*/
public      :

    BOOL SymEnumerateModules64 ( IN PSYM_ENUMMODULES_CALLBACK64
                                                    EnumModulesCallback,
                                 IN PVOID             UserContext )
    {
        return ( ::SymEnumerateModules64 ( m_hProcess           ,
                                           EnumModulesCallback  ,
                                           UserContext           ) ) ;
    }

    BOOL SymLoadModule64 ( IN  HANDLE   hFile       ,
                           IN  PCTSTR   ImageName   ,
                           IN  PCTSTR   ModuleName  ,
                           IN  DWORD64  BaseOfDll   ,
                           IN  DWORD    SizeOfDll    )
    {
        return ( ::SymLoadModuleExW ( m_hProcess  ,
                                      hFile        ,
                                      ImageName    ,
                                      ModuleName   ,
                                      BaseOfDll    ,
                                      SizeOfDll    ,
                                      NULL         ,
                                      0             ) > 0 ) ;
    }

    BOOL EnumerateLoadedModules64 ( IN PENUMLOADED_MODULES_CALLBACK64
                                              EnumLoadedModulesCallback,
                                    IN PVOID         UserContext       )
    {
        return ( ::EnumerateLoadedModules64 ( m_hProcess               ,
                                             EnumLoadedModulesCallback ,
                                             UserContext             ));
    }

    BOOL SymUnloadModule64 ( IN  DWORD64 BaseOfDll )
    {
        return ( ::SymUnloadModule64 ( m_hProcess , BaseOfDll ) ) ;
    }

    BOOL SymGetModuleInfo64 ( IN  DWORD64            dwAddr     ,
                              OUT PIMAGEHLP_MODULE64 ModuleInfo  )
    {
        return ( ::SymGetModuleInfo64 ( m_hProcess    ,
                                        dwAddr        ,
                                        ModuleInfo     ) ) ;
    }

    DWORD64 SymGetModuleBase64 ( IN DWORD64 dwAddr )
    {
        return ( ::SymGetModuleBase64 ( m_hProcess , dwAddr ) ) ;
    }

/*----------------------------------------------------------------------
                       Public Symbol Manipulation
----------------------------------------------------------------------*/
public      :

    BOOL SymGetSymFromAddr64 ( IN  DWORD64             dwAddr          ,
                               OUT PDWORD64            pdwDisplacement ,
                               OUT PIMAGEHLP_SYMBOL64  Symbol           )
    {
        return ( ::SymGetSymFromAddr64 ( m_hProcess       ,
                                         dwAddr           ,
                                         pdwDisplacement  ,
                                         Symbol            ) ) ;
    }

    BOOL SymGetSymFromName64 ( IN  LPSTR              Name   ,
                               OUT PIMAGEHLP_SYMBOL64 Symbol  )
    {
        return ( ::SymGetSymFromName64 ( m_hProcess ,
                                         Name       ,
                                         Symbol      ) ) ;
    }

    BOOL SymGetSymNext64 ( IN OUT PIMAGEHLP_SYMBOL64 Symbol )
    {
        return ( ::SymGetSymNext64 ( m_hProcess , Symbol ) ) ;
    }

    BOOL SymGetSymPrev64 ( IN OUT PIMAGEHLP_SYMBOL64 Symbol )
    {
        return ( ::SymGetSymPrev64 ( m_hProcess , Symbol ) ) ;
    }

/*----------------------------------------------------------------------
                    Public Source Line Manipulation
----------------------------------------------------------------------*/
public      :

    BOOL SymGetLineFromAddr64 ( IN  DWORD64          dwAddr          ,
                                OUT PDWORD           pdwDisplacement ,
                                OUT PIMAGEHLP_LINE64 Line             )
    {

        // Just pass along the values returned by the main function.
        return ( ::SymGetLineFromAddr64 ( m_hProcess      ,
                                          dwAddr          ,
                                          pdwDisplacement ,
                                          Line             ) ) ;
    }

    BOOL SymGetLineFromName64 ( IN     LPSTR            ModuleName     ,
                                IN     LPSTR            FileName       ,
                                IN     DWORD            dwLineNumber   ,
                                OUT    PLONG            plDisplacement ,
                                IN OUT PIMAGEHLP_LINE64 Line           )
    {
        return ( ::SymGetLineFromName64 ( m_hProcess       ,
                                          ModuleName       ,
                                          FileName         ,
                                          dwLineNumber     ,
                                          plDisplacement   ,
                                          Line              ) ) ;
    }

    BOOL SymGetLineNext64 ( IN OUT PIMAGEHLP_LINE64 Line )
    {
        return ( ::SymGetLineNext64 ( m_hProcess , Line ) ) ;
    }

    BOOL SymGetLinePrev64 ( IN OUT PIMAGEHLP_LINE64 Line )
    {
        return ( ::SymGetLinePrev64 ( m_hProcess , Line ) ) ;
    }

    BOOL SymMatchFileName ( IN  LPSTR   FileName        ,
                            IN  LPSTR   Match           ,
                            OUT LPSTR * FileNameStop    ,
                            OUT LPSTR * MatchStop        )
    {
        return ( ::SymMatchFileName ( FileName       ,
                                      Match          ,
                                      FileNameStop   ,
                                      MatchStop       ) ) ;
    }

/*----------------------------------------------------------------------
                          Public Miscellaneous Members
----------------------------------------------------------------------*/
public      :

    LPVOID SymFunctionTableAccess64 ( DWORD64 AddrBase )
    {
        return ( ::SymFunctionTableAccess64 ( m_hProcess , AddrBase ) );
    }

    BOOL SymGetSearchPath ( OUT LPSTR SearchPath        ,
                            IN  DWORD SearchPathLength   )
    {
        return ( ::SymGetSearchPath ( m_hProcess       ,
                                      SearchPath       ,
                                      SearchPathLength  ) ) ;
    }

    BOOL SymSetSearchPath ( IN LPSTR SearchPath )
    {
        return ( ::SymSetSearchPath ( m_hProcess , SearchPath ) ) ;
    }

    BOOL SymRegisterCallback ( IN PSYMBOL_REGISTERED_CALLBACK64
                                                       CallbackFunction,
                               IN ULONG64              UserContext    )
    {
        return ( ::SymRegisterCallback64 ( m_hProcess         ,
                                           CallbackFunction   ,
                                           UserContext         ) ) ;
    }


/*----------------------------------------------------------------------
                         Protected Data Members
----------------------------------------------------------------------*/
protected   :
    // The unique value that will be used for this instance of the
    // symbol engine. This value doesn’t have to be an actual
    // process value, just a unique value.
    HANDLE      m_hProcess      ;

} ;

#endif      // _SYMBOLENGINE_H
