#include "my_xml.h"
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
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: parse_document.cpp $
** $Revision: 3 $
** $Modtime: 3/08/98 3:20p $
*/

BOOL parse_document( const CString& filename, CExtensibleMarkupLanguageDocument& document )
{
   WFCTRACEINIT( TEXT( "parse_document()" ) );

   CByteArray bytes;

   if ( get_bytes( filename, bytes ) != TRUE )
   {
      return( FALSE );
   }

   CDataParser parser;

   parser.Initialize( &bytes, FALSE );

   if ( document.Parse( parser ) == TRUE )
   {
      WFCTRACE( TEXT( "Parsed OK" ) );


#if defined( _DEBUG )

      //document.Dump( afxDump );

#endif // _DEBUG

      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Can't parse document" ) );
      return( FALSE );
   }

   return( TRUE );
}