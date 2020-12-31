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
** $Workfile: wfc_delete_oldest_file.cpp $
** $Revision: 4 $
** $Modtime: 3/17/00 4:47p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_delete_oldest_file( const CString& directory_path )
{
   WFCLTRACEINIT( TEXT( "wfc_delete_oldest_file()" ) );

   CString filename;

   BOOL return_value = FALSE;

   double oldest_file_time = 0.0;
   double this_file_time   = 0.0;
   double high_value       = static_cast< double >( 0xFFFFFFFF );

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
      oldest_file_time  = find_data.ftLastWriteTime.dwLowDateTime;
      oldest_file_time += static_cast< double >( static_cast< double >( find_data.ftLastWriteTime.dwHighDateTime ) * high_value );

      filename = find_data.cFileName;

      while( FindNextFile( find_file_handle, &find_data ) != FALSE )
      {
         this_file_time  = find_data.ftLastWriteTime.dwLowDateTime;
         this_file_time += static_cast< double >( static_cast< double >( find_data.ftLastWriteTime.dwHighDateTime ) * high_value );

         if ( this_file_time < oldest_file_time )
         {
            oldest_file_time = this_file_time;
            filename = find_data.cFileName;
         }
      }

      FindClose( find_file_handle );
   }
   else
   {
      return( FALSE );
   }

   mask = mask.Left( mask.GetLength() - 3 );

   mask += filename;

   return_value = DeleteFile( mask );

   if ( return_value == FALSE )
   {
      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_delete_oldest_file</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that deletes the oldest file in a directory.">
</HEAD>

<BODY>

<H1>wfc_delete_oldest_file</H1>
$Revision: 4 $<HR>

<H2>Declaration</H2>
<PRE><CODE>BOOL wfc_delete_oldest_file( const CString&amp; directory_name )</CODE></PRE>

<H2>Description</H2>
This exciting revolutionary concept in computing . . .
OK, this is a boring function.
All it does is search a directory for the oldest file and
deletes it. I use it to clear out log file directories
when I need room. A file's age is computed using the
time the file was last written to. This function will
return TRUE if a file was deleted or FALSE if no file 
was deleted.

<H2>Example</H2>
<PRE><CODE>void make_some_room( const CString&amp; log_directory )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;make_some_room()&quot; ) );

   double percent_used = 0.0;
   
   percent_used = wfc_get_directory_usage_percentage( log_directory );

   while( percent_used &gt;= 85.0 )
   {
      <B>wfc_delete_oldest_file</B>( log_directory );
      percent_used = wfc_get_directory_usage_percentage( log_directory );
   }
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_delete_oldest_file</B>() uses the following API's:
<UL>
<LI>DeleteFile
<LI>FindClose
<LI>FindFirstFile
<LI>FindNextFile
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_delete_oldest_file.cpp $<BR>
$Modtime: 3/17/00 4:47p $
</BODY>

</HTML>
#endif
