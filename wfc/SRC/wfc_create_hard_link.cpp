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
** $Workfile: wfc_create_hard_link.cpp $
** $Revision: 4 $
** $Modtime: 3/17/00 4:47p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_create_hard_link( LPCTSTR new_filename, LPCTSTR existing_filename, LPSECURITY_ATTRIBUTES sa )
{
   WFCLTRACEINIT( TEXT( "wfc_create_hard_link()" ) );

   try
   {
      ASSERT( new_filename != NULL );
      ASSERT( existing_filename != NULL );
      ASSERT( new_filename != existing_filename );
      ASSERT( _tcscmp( new_filename, existing_filename ) != 0 );

      if ( new_filename      == NULL ||
           existing_filename == NULL ||
           new_filename      == existing_filename )
      {
         return( FALSE );
      }

      if ( _tcscmp( new_filename, existing_filename ) == 0 )
      {
         return( FALSE );
      }

      // Enable some privileges, this improves our chances of succeeding

      if ( wfc_enable_privilege( SE_BACKUP_NAME ) == FALSE )
      {
         WFCTRACE( TEXT( "Can't enable the backup privilege." ) );
      }

      if ( wfc_enable_privilege( SE_RESTORE_NAME ) == FALSE )
      {
         WFCTRACE( TEXT( "Can't enable the restore privilege." ) );
      }

      HANDLE existing_file_handle = (HANDLE) INVALID_HANDLE_VALUE;

      existing_file_handle = CreateFile( existing_filename,
                                         FILE_WRITE_ATTRIBUTES,
                                         FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                         sa,
                                         OPEN_EXISTING,
                                         0,
                                         NULL );

      if ( existing_file_handle == (HANDLE) INVALID_HANDLE_VALUE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACEVAL( TEXT( "At line number " ), __LINE__ );
         return( FALSE );
      }

      // Now we descend into the UNICODE world...

      WCHAR link_file_path[ MAX_PATH + 1 ];
      WCHAR unicode_new_filename[ MAX_PATH + 1 ];

      ZeroMemory( link_file_path, sizeof( link_file_path ) );
      ZeroMemory( unicode_new_filename, sizeof( unicode_new_filename ) );

#if ! defined( UNICODE )
      ASCII_to_UNICODE( new_filename, unicode_new_filename );
#else
      _tcscpy( unicode_new_filename, new_filename );
#endif

      DWORD link_file_path_length = 0;

      LPWSTR unicode_filename_portion = NULL;

      link_file_path_length = GetFullPathNameW( unicode_new_filename, MAX_PATH, link_file_path, &unicode_filename_portion );

      if ( link_file_path_length == 0 )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACEVAL( TEXT( "At line number " ), __LINE__ );

         wfc_close_handle( existing_file_handle );
         return( FALSE );
      }

      DWORD number_of_bytes_in_path = ( link_file_path_length + 1 ) * sizeof( WCHAR );

      LPVOID context = NULL;

      WIN32_STREAM_ID stream;

      ZeroMemory( &stream, sizeof( stream ) );

      stream.dwStreamId         = BACKUP_LINK;
      stream.dwStreamAttributes = 0;
      stream.dwStreamNameSize   = 0;
      stream.Size.QuadPart      = number_of_bytes_in_path;

      DWORD stream_header_size      = (LPBYTE) &stream.cStreamName - (LPBYTE) &stream + stream.dwStreamNameSize;
      DWORD number_of_bytes_written = 0;

      if ( BackupWrite( existing_file_handle,
              (LPBYTE) &stream,
                        stream_header_size,
                       &number_of_bytes_written,
                        FALSE,
                        FALSE,
                       &context ) == FALSE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACEVAL( TEXT( "At line number " ), __LINE__ );

         wfc_close_handle( existing_file_handle );
         return( FALSE );
      }

      ASSERT( number_of_bytes_written == stream_header_size );
      number_of_bytes_written = 0;

      if ( BackupWrite( existing_file_handle,
               (LPBYTE) link_file_path,
                        number_of_bytes_in_path,
                       &number_of_bytes_written,
                        FALSE,
                        FALSE,
                       &context ) == FALSE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACEVAL( TEXT( "At line number " ), __LINE__ );

         wfc_close_handle( existing_file_handle );
         return( FALSE );
      }

      ASSERT( number_of_bytes_written == number_of_bytes_in_path );
      number_of_bytes_written = 0;

      if ( BackupWrite( existing_file_handle,
                        NULL,
                        0,
                       &number_of_bytes_written,
                        TRUE,
                        FALSE,
                       &context ) == FALSE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACEVAL( TEXT( "At line number " ), __LINE__ );

         wfc_close_handle( existing_file_handle );
         return( FALSE );
      }

      wfc_close_handle( existing_file_handle );
      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_create_hard_link</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that encapsulates CloseHandle(). It will spit out a debugging message if CloseHandle() fails.">
</HEAD>

<BODY>

<H1>wfc_create_hard_link</H1>
$Revision: 4 $<HR>

<H2>Declaration</H2>
<PRE>BOOL <B>wfc_create_hard_link</B>( LPCTSTR new_filename, LPCTSTR existing_filename, LPSECURITY_ATTRIBUTES sa )</PRE>

<H2>Description</H2>
This function creates two directory entries for one file.
NT 5.0 will have an API called <CODE>CreateHardLink()</CODE>
that does the same thing.

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   if ( number_of_command_line_arguments &lt; 2 )
   {
      _tprintf( TEXT( &quot;Usage: ln new_filename existing_filename\n&quot; ) );
      return( EXIT_SUCCESS );
   }

   if ( <B>wfc_create_hard_link</B>( command_line_arguments[ 1 ],
                                 command_line_arguments[ 2 ],
                                 NULL ) == FALSE )
   {
      _tprintf( TEXT( &quot;Failed.\n&quot; ) );
      return( EXIT_FAILURE );
   }

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_create_hard_link</B>() uses the following API's:
<UL>
<LI>BackupWrite
<LI>CreateFile
<LI>GetFullPathNameW
<LI>ZeroMemory
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_create_hard_link.cpp $<BR>
$Modtime: 3/17/00 4:47p $
</BODY>

</HTML>
#endif
