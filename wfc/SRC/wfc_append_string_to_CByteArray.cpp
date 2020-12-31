#include <wfc.h>
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
** $Workfile: wfc_append_string_to_CByteArray.cpp $
** $Revision: 2 $
** $Modtime: 1/05/00 3:43a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#if ! defined( WFC_STL )

void PASCAL wfc_append_string_to_CByteArray( const CString& string_to_append, CByteArray& bytes )
{
   WFCLTRACEINIT( TEXT( "wfc_append_string_to_CByteArray()" ) );

#if defined( UNICODE )

   int loop_index = 0;

   while( loop_index < string_to_append.GetLength() )
   {
      bytes.Add( LOBYTE( string_to_append.GetAt( loop_index ) ) );
      bytes.Add( HIBYTE( string_to_append.GetAt( loop_index ) ) );
      loop_index++;
   }

#else // UNICODE

   int loop_index = 0;

   while( loop_index < string_to_append.GetLength() )
   {
      bytes.Add( static_cast< BYTE >( string_to_append.GetAt( loop_index ) ) );
      loop_index++;
   }

#endif // UNICODE
}

#endif // WFC_STL

// End of source
