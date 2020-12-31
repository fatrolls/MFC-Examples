#include "XMLUser.h"
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
** $Revision: 1 $
** $Modtime: 6/14/98 9:39a $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void user_element_callback( void * parameter, CExtensibleMarkupLanguageElement * element_p )
{
   WFCTRACEINIT( TEXT( "user_element_callback()" ) );

   _tprintf( TEXT( "in user_element_callback\n" ) );

   // SCHWEET! We have a user element

   CByteArray names;

   CXMLArchive archive;

   archive.ReadFrom( element_p );

   if ( archive.Read( TEXT( "BINARY" ), names ) == NULL )
   {
      WFCTRACE( TEXT( "Can't find BINARY" ) );
      _tprintf( TEXT( "Can't find BINARY" ) );
      return;
   }

   WFCTRACEVAL( TEXT( "Number of strings is " ), names.GetSize() );

   CFile output_file;

   if ( output_file.Open( TEXT( "c:\\temp\\output.bin" ), CFile::modeCreate | CFile::modeWrite ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't create output.bin" ) );
      return;
   }

   output_file.Write( names.GetData(), names.GetSize() );
}

void parse_document( void )
{
   WFCTRACEINIT( TEXT( "parse_document()" ) );

   CExtensibleMarkupLanguageDocument document;

   CFile file;

//   if ( file.Open( TEXT( "users.xml" ), CFile::modeRead ) == FALSE )
   if ( file.Open( TEXT( "c:\\temp\\stuff.xml" ), CFile::modeRead ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open stuff.xml" ) );
      _tprintf( TEXT( "Can't open users.xml\n" ) );
      return;
   }

   CByteArray bytes;

   bytes.SetSize( file.GetLength() );

   file.Read( bytes.GetData(), bytes.GetSize() );

   file.Close();

   CDataParser parser;

   parser.Initialize( &bytes, FALSE );

   document.AddCallback( TEXT( "USER" ), user_element_callback, NULL );

   if ( document.Parse( parser ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't parse" ) );
   }
   else
   {
      WFCTRACE( TEXT( "Parsed OK" ) );
   }
}
