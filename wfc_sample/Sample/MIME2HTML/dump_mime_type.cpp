#include "MIME2HTML.h"
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
** $Workfile: dump_mime_type.cpp $
** $Revision: 1 $
** $Modtime: 3/21/00 5:59p $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

void dump_mime_type( const CString& mime_type_name )
{
   WFCTRACEINIT( TEXT( "dump_mime_type()" ) );

   CString key_name( TEXT( "MIME\\Database\\Content Type\\" ) );

   key_name += mime_type_name;

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyClassesRoot ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACE( TEXT( "Can't connect to registry" ) );
      return;
   }

   if ( registry.Open( key_name,
      (CRegistry::CreatePermissions)(CRegistry::permissionRead) ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACEVAL( TEXT( "Can't open key " ), key_name );
      return;
   }

   CString extension;

   if ( registry.GetValue( TEXT( "Extension" ), extension ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACE( TEXT( "Can't GetExtension Value " ) );
      return;
   }

   CString output_string( extension );

   normalize_string( output_string );

   _tprintf( TEXT( "   <TD>%s</TD>\n" ), (LPCTSTR) output_string );

   if ( registry.Open( extension,
      (CRegistry::CreatePermissions)(CRegistry::permissionRead) ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACEVAL( TEXT( "Can't extension key " ), extension );
      return;
   }

   // Get the default value

   CString object_name;

   if ( registry.GetValue( NULL, object_name ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACEVAL( TEXT( "Can't default value for " ), object_name );
      return;
   }

   output_string = object_name;

   normalize_string( output_string );

   _tprintf( TEXT( "   <TD>%s</TD>\n" ), (LPCTSTR) output_string );

   // Microsoft maps MIME types to filename extensions and
   // filename extensions to shell commands that are executed
   // when you double click on them.

   CString command_line;

   get_command_line( object_name, command_line );

   output_string = command_line;

   normalize_string( output_string );

   _tprintf( TEXT( "   <TD>%s</TD>\n" ), (LPCTSTR) output_string );
}
