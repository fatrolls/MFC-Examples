/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "BinaryImage.h"
#include "BinaryImageOptionsDlg.h"

#define MakePtr( cast , ptr , AddValue ) \
                             (cast)( (DWORD64)(ptr)+(DWORD64)(AddValue))

#ifdef _M_IX86
static int g_iAppMachineCode = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
static int g_iAppMachineCode = IMAGE_FILE_MACHINE_AMD64;
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE [] = __FILE__ ;
#endif

// MFC stuff.
IMPLEMENT_SERIAL ( CBinaryImage , CObject , 1 )

CBinaryImage :: CBinaryImage ( void )
              : CObject ( )     ,
                m_szFullName ( )
{
    ASSERT ( this ) ;
    m_dwLoadAddress     = 0     ;
    m_dwCharacteristics = 0     ;
    m_bIsValid          = FALSE ;
    m_dwExtraData       = 0     ;
    m_eFailCode         = eNoFailure ;

    m_dwTimeStamp       = 0 ;
    m_eSymType          = SymNone ;
    m_szImageName[ 0 ]  = _T ( '\0' ) ;
    m_szLoadedImageName[ 0 ] = _T ( '\0' ) ;
}

void CBinaryImage :: Serialize ( CArchive & ar )
{
    ASSERT ( this ) ;
    if( ar.IsStoring( ) )
    {
        ar << m_szFullName    ;
    }
    else
    {
        ar >> m_szFullName    ;
    }
}

////////////////////////////////////////////////////////////////////////
// Public Construction and Destruction
////////////////////////////////////////////////////////////////////////
CBinaryImage :: CBinaryImage ( LPCTSTR szFileName )
              : CObject ( )     ,
                m_szFullName ( )
{
    ASSERT ( this ) ;
    m_dwLoadAddress = 0 ;
    m_szFullName = szFileName ;
    m_bIsValid = FALSE ;
    m_dwCharacteristics = 0 ;
    m_dwExtraData = 0 ;
    m_eFailCode = eNoFailure ;

    m_dwTimeStamp       = 0 ;
    m_eSymType          = SymNone ;
    m_szImageName[ 0 ]  = _T ( '\0' ) ;
    m_szLoadedImageName[ 0 ] = _T ( '\0' ) ;

    // Validate the image without showing errors.
    IsValidImage ( FALSE ) ;
}

CBinaryImage :: CBinaryImage ( const CBinaryImage & cInit )
{
    ASSERT ( this ) ;
    m_szFullName        = cInit.m_szFullName        ;
    m_dwLoadAddress     = cInit.m_dwLoadAddress     ;
    m_dwCharacteristics = cInit.m_dwCharacteristics ;
    m_bIsValid          = cInit.m_bIsValid          ;
    m_dwExtraData       = cInit.m_dwExtraData       ;
    m_eFailCode         = cInit.m_eFailCode         ;

    m_dwTimeStamp       = cInit.m_dwTimeStamp ;
    m_eSymType          = cInit.m_eSymType ;
    StringCchCopy ( m_szImageName , MAX_PATH , cInit.m_szImageName ) ;
    StringCchCopy ( m_szLoadedImageName       , 
                    MAX_PATH                  , 
                    cInit.m_szLoadedImageName  ) ;
    m_szSearchPath       = cInit.m_szSearchPath ;
}

CBinaryImage :: ~CBinaryImage ( void )
{
    ASSERT ( this ) ;
}

////////////////////////////////////////////////////////////////////////
// Public Validation Methods
////////////////////////////////////////////////////////////////////////
// Returns TRUE if the image passed in the constructor is a valid
// binary image.  Returns FALSE otherwise.
BOOL CBinaryImage :: IsValidImage ( BOOL bShowErrors )
{
    ASSERT ( this ) ;
    // If the m_bIsValid value was already true, then the image is OK.
    if ( TRUE == m_bIsValid )
    {
        return ( m_bIsValid ) ;
    }

    // The error message holder.
    CString sMsg ;

    // First check if the file actually exists.
    CFileFind cFFile ;

    BOOL bRet = cFFile.FindFile ( m_szFullName ) ;
    if ( FALSE == bRet )
    {
        if ( TRUE == bShowErrors )
        {
            sMsg.FormatMessage ( IDS_FILENOTFOUND , m_szFullName ) ;
            AfxMessageBox ( sMsg ) ;
        }
        m_bIsValid = FALSE ;
        m_eFailCode = eNotFound ;
        return ( FALSE ) ;
    }

    // The file exists, now see if it is a real PE file.
    
    LOADED_IMAGE stLI ;
    
    size_t iAnsiLen = _tcslen ( m_szFullName ) + 1 ;
    char * szAnsi = 
#if _MSC_VER <= 1310        
                    (char*)_alloca ( iAnsiLen ) ;
#else               
                    (char*)_malloca ( iAnsiLen ) ;
#endif

    WideCharToMultiByte ( CP_THREAD_ACP  ,
                          0              ,
                          m_szFullName   ,
                          -1             ,
                          szAnsi         ,
                          (int)iAnsiLen  ,
                          NULL           ,
                          NULL            ) ;
    
    BOOL bMapLoadRes = MapAndLoad ( szAnsi ,
                                    NULL   ,
                                    &stLI  ,
                                    TRUE   ,
                                    TRUE    ) ;
#if _MSC_VER >= 1310
    // Free up the allocated buffer.
    _freea ( szAnsi ) ;
#endif

    if ( ( FALSE == bMapLoadRes                             ) ||
         ( IMAGE_NT_SIGNATURE != stLI.FileHeader->Signature )    )
    {
        if ( TRUE == bShowErrors )
        {
            sMsg.FormatMessage ( IDS_NOTPEIMAGE , m_szFullName ) ;
            AfxMessageBox ( sMsg ) ;
        }
        m_bIsValid = FALSE ;
        m_eFailCode = eNoPEImage ;
        return ( FALSE ) ;
    }
    // Look to see if machine type matches the type this image was built 
    // for.
    if ( g_iAppMachineCode != stLI.FileHeader->FileHeader.Machine )
    {
        if ( TRUE == bShowErrors )
        {
            sMsg.FormatMessage ( IDS_ERR_WRONGMACHINE , m_szFullName ) ;
            AfxMessageBox ( sMsg ) ;
        }
        m_bIsValid = FALSE ;
        m_eFailCode = eNotCorrectMachine ;
        return ( FALSE ) ;
    }


    // The load address is ALWAYS based off the current image.
    m_dwLoadAddress = stLI.FileHeader->OptionalHeader.ImageBase ;

    // Save off the characteristics.
    m_dwCharacteristics = stLI.Characteristics ;

    // Unload the image.
    bRet = UnMapAndLoad ( &stLI ) ;
    ASSERT ( TRUE == bRet ) ;

    m_bIsValid = ( bRet == TRUE ) ;
    return ( m_bIsValid ) ;
}

////////////////////////////////////////////////////////////////////////
// Public Property Retrieval Methods
////////////////////////////////////////////////////////////////////////
// Returns the load address for this image.
DWORD64 CBinaryImage :: GetLoadAddress ( void ) const
{
    ASSERT ( this ) ;
    return ( m_dwLoadAddress ) ;
}

// Returns the full name for this image.
const CString CBinaryImage :: GetFullName ( void ) const
{
    ASSERT ( this ) ;
    return ( m_szFullName ) ;
}

// Returns just the name of the image.
const CString CBinaryImage :: GetName ( void ) const
{
    ASSERT ( this ) ;

    TCHAR szFName [ MAX_PATH ] ;
    TCHAR szExt [ MAX_PATH ] ;

#if _MSC_VER <= 1310
     _tsplitpath ( m_szFullName , NULL , NULL , szFName , szExt ) ;
#else
    _tsplitpath_s ( m_szFullName , 
                    NULL         , 
                    0            , 
                    NULL         , 
                    0            , 
                    szFName      , 
                    MAX_PATH     , 
                    szExt        , 
                    MAX_PATH      ) ;
#endif
     CString szTemp = szFName ;

     szTemp += szExt ;

     return ( szTemp ) ;
}

LPCTSTR CBinaryImage :: GetFullNameString ( void ) const
{
    return ( (LPCTSTR)m_szFullName ) ;
}

LPCTSTR CBinaryImage :: GetNameString ( void ) const
{
    return ( (LPCTSTR)GetName ( ) ) ;
}

DWORD CBinaryImage :: GetCharacteristics ( void ) const
{
    ASSERT ( this ) ;
    return ( m_dwCharacteristics ) ;
}

// Returns a string that contains any additional information that
// the class would like to return about this image.
const CString CBinaryImage :: GetAdditionalInfo ( void ) const
{
    ASSERT ( this ) ;
    CString szTemp ;
    return ( szTemp ) ;
}

// Gets the extra data for this class.
DWORD CBinaryImage :: GetExtraData ( void ) const
{
    ASSERT ( this ) ;
    return ( m_dwExtraData ) ;
}

////////////////////////////////////////////////////////////////////////
// Public Property Setting Methods
////////////////////////////////////////////////////////////////////////
BOOL CBinaryImage :: SetProperties ( void )
{
    ASSERT ( this ) ;
    CBinaryImageOptionsDlg cDlg ;
    cDlg.m_dwAddr = m_dwLoadAddress ;
    cDlg.m_strImageName = GetName ( ) ;
    if ( IDOK == cDlg.DoModal ( ) )
    {
        if ( cDlg.m_dwAddr != m_dwLoadAddress )
        {
            m_dwLoadAddress = cDlg.m_dwAddr ;
            return ( TRUE ) ;
        }
    }
    return ( FALSE ) ;
}

void CBinaryImage :: SetLoadAddress ( DWORD64 dwAddr )
{
    ASSERT ( this ) ;
    m_dwLoadAddress = dwAddr ;
}

void CBinaryImage :: SetExtraData ( DWORD dwData )
{
    ASSERT ( this ) ;
    m_dwExtraData = dwData ;
}


////////////////////////////////////////////////////////////////////////
// Public Operators
////////////////////////////////////////////////////////////////////////
CBinaryImage & CBinaryImage:: operator = ( const CBinaryImage & rhs )
{
    if ( this != &rhs )
    {
        m_szFullName        = rhs.m_szFullName        ;
        m_dwLoadAddress     = rhs.m_dwLoadAddress     ;
        m_dwCharacteristics = rhs.m_dwCharacteristics ;
        m_bIsValid          = rhs.m_bIsValid          ;
        m_dwExtraData       = rhs.m_dwExtraData       ;
        m_eFailCode         = rhs.m_eFailCode         ;
        m_dwTimeStamp       = rhs.m_dwTimeStamp ;
        m_eSymType          = rhs.m_eSymType ;
        StringCchCopy ( m_szImageName , MAX_PATH , rhs.m_szImageName ) ;
        StringCchCopy ( m_szLoadedImageName     , 
                        MAX_PATH                , 
                        rhs.m_szLoadedImageName  ) ;
    }
    return ( *this ) ;
}


BOOL CBinaryImage :: GetModules ( LPCTSTR          pModuleName ,
                                  CMapStringToPtr& ModuleList   )
{
    HINSTANCE hModule = NULL ;
    CString strName ( pModuleName ) ;
    strName.MakeUpper ( ) ;
    ModuleList[strName] = NULL ;

    hModule = LoadLibraryEx ( pModuleName ,
                              NULL        ,
                              DONT_RESOLVE_DLL_REFERENCES ) ;
    if ( NULL == hModule )
    {
        m_eFailCode = eNotFound ;
        return ( FALSE ) ;
    }

    PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule ;

    // Is this the MZ header?
    if ( ( TRUE == IsBadReadPtr ( pDOSHeader                   ,
                                  sizeof ( IMAGE_DOS_HEADER ) ) ) ||
        ( IMAGE_DOS_SIGNATURE != pDOSHeader->e_magic            )   )
    {
        m_eFailCode = eNoPEImage ;
        FreeLibrary ( hModule ) ;
        SetLastErrorEx ( ERROR_INVALID_PARAMETER , SLE_ERROR ) ;
        return ( FALSE ) ;
    }

    // Get the PE header.
    PIMAGE_NT_HEADERS pNTHeader = MakePtr ( PIMAGE_NT_HEADERS    ,
                                            pDOSHeader           ,
                                            pDOSHeader->e_lfanew  ) ;

    // Is this a real PE image?
    if ( ( TRUE == IsBadReadPtr ( pNTHeader                    ,
                                  sizeof ( IMAGE_NT_HEADERS ) ) ) ||
         ( IMAGE_NT_SIGNATURE != pNTHeader->Signature           )   )
    {
        m_eFailCode = eNoPEImage ;
        FreeLibrary ( hModule ) ;
        SetLastErrorEx ( ERROR_INVALID_PARAMETER , SLE_ERROR ) ;
        return ( FALSE ) ;
    }
    // Running as a 32-bit application on Win64, you can get valid PE 
    // files like NTDLL.DLL that don't have import sections. I'll do the 
    // check here if the import section is zero, I'll say it was a good 
    // load, but without an imports section there's no need to check for
    // imports. ;)
    if ( 0 == pNTHeader->OptionalHeader.
                         DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].
                         VirtualAddress  ) 
    {
        m_eFailCode = eNoFailure;
        FreeLibrary ( hModule ) ;
        return ( TRUE ) ;
    }


    // Get the pointer to the imports section.
    PIMAGE_IMPORT_DESCRIPTOR pImportDesc =
                            MakePtr ( PIMAGE_IMPORT_DESCRIPTOR ,
                                      pDOSHeader               ,
                        pNTHeader->OptionalHeader.
                            DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].
                                                      VirtualAddress ) ;
    // Does it have an imports section?
    if ( 0 == pImportDesc )
    {
        m_eFailCode = eNoPEImage ;
        FreeLibrary ( hModule ) ;
        return ( FALSE ) ;
    }
    
    // Build the search path.
    BuildSearchPathString ( ) ;
    
    // Loop through the import module descriptors looking for the
    // module whose name matches szImportMod.
    LPVOID pPtr;
    while ( NULL != pImportDesc->Name )
    {
        CString szModName = MakePtr ( PSTR              ,
                                      pDOSHeader        ,
                                      pImportDesc->Name  ) ;
        if ( TRUE == SearchForModule ( szModName ) )
        {
            szModName.MakeUpper ( ) ;
            if ( FALSE == ModuleList.Lookup ( szModName , pPtr ) )
            {
                ModuleList[szModName] = NULL ;
                if ( FALSE == GetModules ( szModName , ModuleList) )
                {
                    m_eFailCode = eNoPEImage ;
                    FreeLibrary ( hModule ) ;
                    return ( FALSE ) ;
                }
            }
        }

        // Look at the next one.
        pImportDesc++;
    }
    
    FreeLibrary ( hModule ) ;
    return ( TRUE ) ;
}

BOOL CBinaryImage :: SearchForModule ( CString& szModName )
{
    CString strName ;
    CString szExt ;

    int i = szModName.Find ( _T ( '.' ) ) ;

    if ( -1 != i )
    {
        strName = szModName.Left ( i ) ;
        szExt = szModName.Mid ( i ) ;
    }
    else
    {
        strName = szModName ;
        szExt = _T ( '.' ) ;
    }
    TCHAR szBuff [ MAX_PATH + 1 ];
    LPTSTR pFilePart ;
    DWORD len = SearchPath ( m_szSearchPath ,
                             strName        ,
                             szExt          ,
                             MAX_PATH       ,
                             szBuff         ,
                             &pFilePart      ) ;
    if ( ( len > 0 ) && ( len < MAX_PATH ) )
    {
        szModName = szBuff ;
        return ( TRUE ) ;
    }
    else
    {
        szModName = strName + szExt ;
        return ( FALSE ) ;
    }
}

void CBinaryImage :: SetBinaryError ( BinaryFailureEnum eCode )
{
    m_eFailCode = eCode ;
}

BinaryFailureEnum CBinaryImage :: GetBinaryError ( void )
{
    return ( m_eFailCode ) ;
}

DWORD CBinaryImage :: GetTimeStamp ( void )
{
    return ( m_dwTimeStamp ) ;
}

SYM_TYPE CBinaryImage :: GetSymType ( void )
{
    return ( m_eSymType ) ;
}

LPCTSTR CBinaryImage :: GetSymbolImageName ( void )
{
    return ( m_szImageName ) ;
}

LPCTSTR CBinaryImage :: GetLoadedSymbolImageName ( void )
{
    return ( m_szLoadedImageName ) ;
}

void CBinaryImage :: SetSymbolInformation ( CImageHlp_Module & cModInfo)
{
    m_dwTimeStamp = cModInfo.TimeDateStamp ;
    m_eSymType    = cModInfo.SymType ;
    
    MultiByteToWideChar ( CP_THREAD_ACP      ,
                          0                  ,
                          cModInfo.ImageName ,
                          -1                 ,
                          m_szImageName      ,
                          MAX_PATH            ) ;
    
    MultiByteToWideChar ( CP_THREAD_ACP             ,
                          0                         ,
                          cModInfo.LoadedImageName  ,
                          -1                        ,
                          m_szLoadedImageName       ,
                          MAX_PATH                   ) ;
}

////////////////////////////////////////////////////////////////////////
// Protected Data Methods
////////////////////////////////////////////////////////////////////////
void CBinaryImage :: BuildSearchPathString ( void )
{
    // Add the path to this particular binary.  This fixes the
    // problem where the binary has implicitly loaded modules that
    // are in the same directory, but not in the path AND the
    // directory is not the current directory.
    TCHAR szCurrPath[ MAX_PATH ] ;
    
    StringCchCopy ( szCurrPath , MAX_PATH , m_szFullName ) ;
    
    TCHAR * pSlash = _tcsrchr ( szCurrPath , _T ( '\\' ) ) ;
    if  ( NULL != pSlash )
    {
        *pSlash = _T ( '\0' ) ;
    }
    m_szSearchPath += szCurrPath ;
    m_szSearchPath += _T ( ";" ) ;

    // Add the current working directory.
    if ( NULL != _tgetcwd ( szCurrPath , MAX_PATH ) )
    {
        m_szSearchPath += szCurrPath ;
        m_szSearchPath += _T ( ";" ) ;
    }

    // Add %SYSTEMROOT%\System32.
    GetSystemDirectory ( szCurrPath , MAX_PATH ) ;
    m_szSearchPath += szCurrPath ;
    m_szSearchPath += _T ( ";" ) ;
    
    // Add %SYSTEMROOT%\System
    if ( 0 != GetWindowsDirectory ( szCurrPath , MAX_PATH ) )
    {
        StringCchCopy ( szCurrPath , MAX_PATH , _T ( "SYSTEM" ) ) ;
        m_szSearchPath += szCurrPath ;
        m_szSearchPath += _T ( ";" ) ;
    }

    // Add %SYSTEMROOT%
    if ( 0 != GetWindowsDirectory ( szCurrPath , MAX_PATH ) )
    {
        m_szSearchPath += szCurrPath ;
        m_szSearchPath += _T ( ";" ) ;
    }
    
    // Finally, get the real PATH.
    CString cTemp ;
    if ( 0 != cTemp.GetEnvironmentVariable ( _T ( "PATH" ) ) )
    {
        m_szSearchPath += cTemp ;
    }
}
