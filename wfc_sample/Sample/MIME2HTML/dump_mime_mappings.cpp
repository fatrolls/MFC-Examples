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
** $Workfile: dump_mime_mappings.cpp $
** $Revision: 1 $
** $Modtime: 3/22/00 4:31a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

void dump_mime_mappings( void )
{
   WFCTRACEINIT( TEXT( "dump_mime_mappings()" ) );

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyClassesRoot ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACE( TEXT( "Can't connect to registry" ) );
      return;
   }

   if ( registry.Open( TEXT( "MIME\\Database\\Content Type" ),
      (CRegistry::CreatePermissions)(CRegistry::permissionRead) ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACE( TEXT( "Can't open key \"MIME\\Database\\Content Type\"" ) );
      return;
   }

   CString subkey_name;
   CString class_name;

   _tprintf( TEXT( "<HTML>\n\n" ) );
   _tprintf( TEXT( "<HEAD>\n" ) );
   _tprintf( TEXT( "<TITLE>Microsoft MIME Mappings</TITLE>\n" ) );
   _tprintf( TEXT( "</HEAD>\n\n" ) );
   _tprintf( TEXT( "<BODY>\n\n" ) );
   _tprintf( TEXT( "<H1>Microsoft MIME Mappings</H1>\n\n" ) );
   _tprintf( TEXT( "<TABLE BORDER=1>" ) );
   _tprintf( TEXT( "<TR>\n" ) );
   _tprintf( TEXT( "   <TD ALIGN=CENTER>MIME Type</TD>\n" ) );
   _tprintf( TEXT( "   <TD ALIGN=CENTER>Associated Filename Extension</TD>\n" ) );
   _tprintf( TEXT( "   <TD ALIGN=CENTER>OLE Object Interface Name</TD>\n" ) );
   _tprintf( TEXT( "   <TD ALIGN=CENTER>Command Line Executed</TD>\n" ) );
   _tprintf( TEXT( "</TR>\n\n" ) );

   DWORD key_index = 0;

   CString output_string;

   while( registry.EnumerateKeys( key_index, subkey_name, class_name ) != FALSE )
   {
      _tprintf( TEXT( "<TR>\n" ) );

      output_string = subkey_name;

      normalize_string( output_string );
      _tprintf( TEXT( "   <TD>%s</TD>\n" ), (LPCTSTR) output_string );
      dump_mime_type( subkey_name );
      _tprintf( TEXT( "</TR>\n\n" ) );

      key_index++;
   }

   _tprintf( TEXT( "</BODY>\n\n" ) );
   _tprintf( TEXT( "</HTML>\n" ) );
}
