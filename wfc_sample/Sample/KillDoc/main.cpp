#if ! defined( WINVER )
#define WINVER 0x401
#endif // WINVER

#include <wfc.h>
#pragma hdrstop

#pragma comment( linker, "/verbose:lib" )
#pragma comment( lib, "DebugBuildOfSTLWFC.lib" )
//ragma comment( linker, "/NODEFAULTLIB:msvcprtd.lib" )
//#pragma comment( linker, "/NODEFAULTLIB:libcd.lib" )

#if 0

BOOL wfc_kill_most_recently_used_document_list( void )
{
   WFCTRACEINIT( TEXT( "wfc_kill_most_recently_used_document_list()" ) );

   CRegistry registry;

   if ( registry.Connect( HKEY_CURRENT_USER ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      return( FALSE );
   }

   if ( registry.Open( TEXT( "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs" ),
      (CRegistry::CreatePermissions)( CRegistry::permissionRead | CRegistry::permissionSetValue | CRegistry::permissionWrite ) ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      return( FALSE );
   }

   CString list;

   if ( registry.GetStringValue( TEXT( "MRUList" ), list ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      return( FALSE );
   }

   WFCTRACEVAL( TEXT( "Would delete " ), list );
   _tprintf( TEXT( "Would delete %s\n" ), (LPCTSTR) list );

   int loop_index = 0;

   CString name_of_value_to_delete;

   CByteArray unicode_string;

   char ascii_string[ 4096 ];

   while( loop_index < list.GetLength() )
   {
      //name_of_value_to_delete  = TEXT( "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs\\" );
      name_of_value_to_delete.Empty();
      name_of_value_to_delete += list.GetAt( loop_index );
      WFCTRACEVAL( TEXT( "Would delete " ), name_of_value_to_delete );

      ZeroMemory( ascii_string, sizeof( ascii_string ) );

      registry.GetBinaryValue( name_of_value_to_delete, unicode_string );

      if ( unicode_string.GetSize() > 0 )
      {
         UNICODE_to_ASCII( (LPCWSTR) unicode_string.GetData(), ascii_string );
         WFCTRACEVAL( TEXT( "document was " ), CString( ascii_string ) );
         printf( TEXT( "Deleting reference to %s\n" ), ascii_string );
      }

      if ( registry.DeleteValue( name_of_value_to_delete ) == FALSE )
      {
         WFCTRACEERROR( registry.GetErrorCode() );
         printf( TEXT( "Can't delete reference to %s\n" ), ascii_string );
      }

      loop_index++;
   }

   list.Empty();

   if ( registry.SetStringValue( TEXT( "MRUList" ), list ) == FALSE )
   {
      WFCTRACEERROR( registry.GetErrorCode() );
      return( FALSE );
   }

   return( TRUE );
}

#endif

void main( void )
{
   WFCTRACEINIT( TEXT( "main()" ) );

#if 0
   if ( wfc_kill_most_recently_used_document_list() != TRUE )
   {
      _tprintf( TEXT( "Failed.\n" ) );
   }
#endif
                       
   //                                   1111
   //                         01234567890123
   CString m_Contents( TEXT( "   &39;   &38;" ) );

   int location_of_ampersand = m_Contents.Find( TEXT( '&' ) );

   while( location_of_ampersand != (-1) )
   {
      // There's an ampersand in there, now let's validate it

      int location_of_semicolon = m_Contents.Find( TEXT( ';' ), location_of_ampersand + 1 );

      WFCTRACEVAL( TEXT( "location_of_ampersand is " ), location_of_ampersand );
      WFCTRACEVAL( TEXT( "location_of_semicolon is " ), location_of_semicolon );

      if ( location_of_semicolon == (-1) )
      {
         return;
      }

      location_of_ampersand = m_Contents.Find( TEXT( '&' ), location_of_ampersand + 1 );
   }
}
