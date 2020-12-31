/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright © 1997-2008 John Robbins -- All rights reserved.

Version 2.8

With excellent updates from Scott Bloom, Ching Ming Kwok,
Jeff Shanholtz, Pablo Presedo, Julian Onions and Ken Gladstone!
----------------------------------------------------------------------*/
#ifndef _BINARYIMAGE_H
#define _BINARYIMAGE_H

#include "SymbolEngine.h"

enum BinaryFailureEnum
{
    // The image is not found.
    eNotFound   = 0  ,
    // Everything is cool.
    eNoFailure       ,
    // The image conflicts with another binary in the project.
    eAddressConflict ,
    // It's not a PE image.
    eNoPEImage       ,
    // The module has SymNone as the symbol type.
    eNoSymbolsAtAll  ,
    // The module does not have PDB symbols.
    eNoPDBSymbols    ,
    // The module is the wrong machine type.
    eNotCorrectMachine
} ;

// The class that manages a single binary image.
class CBinaryImage : public CObject
{
protected   :
    // Necassary MFC macros and functions.
    CBinaryImage ( void ) ;
    DECLARE_SERIAL ( CBinaryImage )
public      :
    virtual void Serialize ( CArchive & ar ) ;

////////////////////////////////////////////////////////////////////////
// Public Construction and Desctruction
////////////////////////////////////////////////////////////////////////
public      :
    // szFileName is the complete filename of the binary file.
    CBinaryImage ( LPCTSTR szFileName ) ;

    // Ye old copy constructor.
    CBinaryImage ( const CBinaryImage & cInit ) ;

    // Simple destructor.
    virtual ~CBinaryImage ( void ) ;

////////////////////////////////////////////////////////////////////////
// Public Validation Methods
////////////////////////////////////////////////////////////////////////
public      :
    // Returns TRUE if the image passed in the constructor is a valid
    // binary image.  Returns FALSE otherwise.
    BOOL IsValidImage ( BOOL bShowErrors = TRUE ) ;

////////////////////////////////////////////////////////////////////////
// Public Property Retrieval Methods
////////////////////////////////////////////////////////////////////////
public      :
    // Returns the load address for this image.
    DWORD64 GetLoadAddress ( void ) const ;

    // Returns the full name for this image.
    const CString GetFullName ( void ) const ;
    const CString GetName ( void ) const ;
    LPCTSTR GetFullNameString ( void ) const ;
    LPCTSTR GetNameString ( void ) const ;

    // Returns the binary image characteristics.
    DWORD GetCharacteristics ( void ) const ;

    // Returns a string that contains any additional information that
    // the class would like to return about this image.
    const CString GetAdditionalInfo ( void ) const ;

    // Gets the extra data for this class.
    DWORD GetExtraData ( void ) const ;

    // Get any binary error.
    BinaryFailureEnum GetBinaryError ( void ) ;

    // Get the time stamp.
    DWORD GetTimeStamp ( void ) ;

    // Get the symbol type.
    SYM_TYPE GetSymType ( void ) ;

    // The symbol image name.
    LPCTSTR GetSymbolImageName ( void ) ;

    // The symbol loaded image name.
    LPCTSTR GetLoadedSymbolImageName ( void ) ;

////////////////////////////////////////////////////////////////////////
// Public Property Setting Methods
////////////////////////////////////////////////////////////////////////
public      :
    // This class is responsible for handling it's own property changing
    // and setting.  This is the function that will be called when the
    // user wants to change the property of a binary image.
    // This returns TRUE if any of the properties changed.
    BOOL SetProperties ( void ) ;

    // This function forces the load address for this instance.  It is
    // only to be called by controller classes that need to do the
    // forcing, i.e., when the address the class has conflicts with
    // an existing load address from another class.
    void SetLoadAddress ( DWORD64 dwAddr ) ;

    // Sets the extra data property for this class.  Think of this as
    // something like the item data LPARAM value in Tree Controls.
    // This is set by the controling class.
    void SetExtraData ( DWORD dwData ) ;

    // Set the binary error.
    void SetBinaryError ( BinaryFailureEnum eCode ) ;

    // Sets all the symbol specific information.
    void SetSymbolInformation ( CImageHlp_Module & cModInfo ) ;

////////////////////////////////////////////////////////////////////////
// Public Module Searching and Uses Functions
////////////////////////////////////////////////////////////////////////
public:
    BOOL GetModules ( LPCTSTR          pModuleName ,
                      CMapStringToPtr& ModuleList   ) ;

    BOOL SearchForModule ( CString& fullpath ) ;

////////////////////////////////////////////////////////////////////////
// Public Operators
////////////////////////////////////////////////////////////////////////
public      :
    CBinaryImage & operator = ( const CBinaryImage & rhs ) ;
    
////////////////////////////////////////////////////////////////////////
// Protected Data Methods
////////////////////////////////////////////////////////////////////////
protected   :
    // Builds the complete search path string for sub modules.
    void BuildSearchPathString ( void ) ;

////////////////////////////////////////////////////////////////////////
// Protected Data Members
////////////////////////////////////////////////////////////////////////
protected   :

    // The full name of the binary image.  This is set by the
    // constructor.
    CString     m_szFullName        ;

    // The load address for this image.
    DWORD64     m_dwLoadAddress     ;

    // The characteristics of the binary.  This is straight out of the
    // PE header.
    DWORD       m_dwCharacteristics ;

    // The flag that indicates if this instance points to a valid
    // binary.
    BOOL        m_bIsValid          ;

    // The extra data parameter.
    DWORD       m_dwExtraData       ;

    // The failure code.
    BinaryFailureEnum m_eFailCode   ;

    // The symbol information from the symbol file.
    DWORD       m_dwTimeStamp        ;
    SYM_TYPE    m_eSymType           ;
    TCHAR       m_szImageName[ MAX_PATH ] ;
    TCHAR       m_szLoadedImageName[ MAX_PATH ] ;
    
    // The search path string.
    CString     m_szSearchPath ;


} ;

#endif      // _BINARYIMAGE_H


