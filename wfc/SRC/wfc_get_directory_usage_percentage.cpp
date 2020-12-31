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
** $Workfile: wfc_get_directory_usage_percentage.cpp $
** $Revision: 9 $
** $Modtime: 3/17/00 4:48p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

DWORD PASCAL wfc_get_directory_usage_percentage( const CString& directory_path )
{
   WFCLTRACEINIT( TEXT( "wfc_get_directory_usage_percentage()" ) );

   double number_of_bytes_free_on_drive     = 0.0;
   double number_of_bytes_used_in_directory = 0.0;
   double high_value                        = static_cast< double >( 0xFFFFFFFF );

   high_value++;

   HANDLE find_file_handle = (HANDLE) NULL;

   CString mask( directory_path );

   if ( mask.GetAt( mask.GetLength() - 1 ) != TEXT( '\\' ) &&
        mask.GetAt( mask.GetLength() - 1 ) != TEXT( '/' ) )
   {
      mask += TEXT( '/' );
   }

   mask += TEXT( "*.*" );

   WIN32_FIND_DATA find_data;

   ZeroMemory( &find_data, sizeof( find_data ) );

   find_file_handle = FindFirstFile( mask, &find_data );

   if ( find_file_handle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      number_of_bytes_used_in_directory += find_data.nFileSizeLow;

      if ( find_data.nFileSizeHigh != 0 )
      {
         number_of_bytes_used_in_directory += static_cast< double >( static_cast< double >( find_data.nFileSizeHigh ) * high_value );
      }

      while( FindNextFile( find_file_handle, &find_data ) != FALSE )
      {
         number_of_bytes_used_in_directory += find_data.nFileSizeLow;

         if ( find_data.nFileSizeHigh != 0 )
         {
            number_of_bytes_used_in_directory += static_cast< double >( static_cast< double >( find_data.nFileSizeHigh ) * high_value );
         }
      }

      FindClose( find_file_handle );
   }
   else
   {
      return( 0 );
   }

   // Strip off the "/*.*" from the directory name

   mask = mask.Left( mask.GetLength() - 4 );

   ULARGE_INTEGER number_of_free_bytes_on_disk;
   ULARGE_INTEGER total_number_of_bytes_on_disk;

   if ( GetDiskFreeSpaceEx( mask,
                           &number_of_free_bytes_on_disk,
                           &total_number_of_bytes_on_disk,
                            NULL ) == FALSE )
   {
      WFCTRACE( "Failure!" );
      WFCTRACEERROR( GetLastError() );
      return( 0 );
   }

   number_of_bytes_free_on_drive  = number_of_free_bytes_on_disk.LowPart;
   number_of_bytes_free_on_drive += static_cast< double >( static_cast< double >( number_of_free_bytes_on_disk.HighPart ) * high_value );

   double percentage = 0.0;

   percentage = number_of_bytes_used_in_directory / number_of_bytes_free_on_drive;
   percentage *= 100.0;

   return( static_cast< DWORD >( percentage ) );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_get_directory_usage_percentage</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that computes how much room on a disk a directory is using (non-recursive).">
</HEAD>

<BODY>

<H1>wfc_get_directory_usage_percentage</H1>
$Revision: 9 $<HR>

<H2>Declaration</H2>
<PRE><CODE>DWORD wfc_get_directory_usage_percentage( const CString&amp; directory_name )</CODE></PRE>

<H2>Description</H2>
This function tells you how much space is used by
the specified directory. It takes into account quotas and
distributed file systems (DFS). If the function fails, it will
return zero.

<H2>Example</H2>

<PRE><CODE>void check_home_directory_usage( const CString&amp; home_directory )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;check_home_directory_usage()&quot; ) );

   double percent_used = <B>wfc_get_directory_usage_percentage</B>( home_directory );

   if ( percent_used &gt;= 85.0 )
   {
      _tprintf( &quot;%s is %lf full\n&quot;, (LPCTSTR) home_directory, percent_used );
   }
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_get_directory_usage_percentage</B>() uses the following API's:
<UL>
<LI>FindClose
<LI>FindFirstFile
<LI>FindNextFile
<LI>GetDiskFreeSpaceEx
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_get_directory_usage_percentage.cpp $<BR>
$Modtime: 3/17/00 4:48p $
</BODY>

</HTML>
#endif
