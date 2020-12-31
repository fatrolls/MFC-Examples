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
** $Workfile: get_command_line.cpp $
** $Revision: 1 $
** $Modtime: 3/21/00 5:49p $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

bool get_command_line( const CString& object_name, CString& command_line )
{
   WFCTRACEINIT( TEXT( "get_command_line()" ) );

   command_line.Empty();

   CString key_name( object_name );

   key_name += TEXT( "\\shell\\open\\command" );

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyClassesRoot ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACE( TEXT( "Can't connect to registry" ) );
      return( false );
   }

   if ( registry.Open( key_name,
      (CRegistry::CreatePermissions)(CRegistry::permissionRead) ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACEVAL( TEXT( "Can't open key " ), key_name );
      return( false );
   }

   // Get the default value

   if ( registry.GetValue( NULL, command_line ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      WFCTRACEVAL( TEXT( "Can't default value for " ), object_name );
      return( false );
   }

   return( true );
}
