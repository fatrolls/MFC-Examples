#include "ado2xml.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: print_COM_error.cpp $
** $Revision: 1 $
** $Modtime: 3/14/00 4:46a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

void print_COM_error( _com_error &exception )
{
   WFCTRACEINIT( TEXT( "print_COM_error()" ) );

   _bstr_t source( exception.Source() );
   _bstr_t description( exception.Description() );

#if defined( _DEBUG )

   {
      CString error_string;

      error_string.Format( TEXT( "%08lX" ), (unsigned long) exception.Error() );
      WFCTRACEVAL( TEXT( "HRESULT " ), error_string );
   }

#endif // _DEBUG

   WFCTRACEVAL( TEXT( "HRESULT " ), (DWORD) exception.Error() );
   WFCTRACEVAL( TEXT( "Source " ), CString( source ) );
   WFCTRACEVAL( TEXT( "Description " ), CString( description ) );
   WFCTRACEVAL( TEXT( "Error Message " ), CString( exception.ErrorMessage() ) );

   _tprintf( TEXT( "COM Error:\n" ) );
   _tprintf( TEXT( "Code: %08lX\n" ), exception.Error() );
   _tprintf( TEXT( "Source: %s\n" ), (LPCTSTR) source );
   _tprintf( TEXT( "Description: %s\n" ), (LPCTSTR) description );
   _tprintf( TEXT( "Message: %s\n" ), exception.ErrorMessage() );
}
