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
** $Workfile: wfc_close_handle.cpp $
** $Revision: 11 $
** $Modtime: 3/17/00 4:47p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_close_handle( HANDLE handle )
{
   WFCLTRACEINIT( TEXT( "wfc_close_handle()" ) );

   BOOL return_value = FALSE;

   return_value = CloseHandle( handle );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "You've got a serious problem here!" ) );
      WFCTRACEERROR( GetLastError() );
      return( FALSE );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_close_handle</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that encapsulates CloseHandle(). It will spit out a debugging message if CloseHandle() fails.">
</HEAD>

<BODY>

<H1>wfc_close_handle</H1>
$Revision: 11 $<HR>

<H2>Declaration</H2>
<PRE>BOOL <B>wfc_close_handle</B>( HANDLE handle )</PRE>

<H2>Description</H2>
This function returns TRUE if the handle was successfully closed
using the <B>CloseHandle</B>() Win32 API.

<H2>Example</H2>

<PRE><CODE>int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   if ( number_of_command_line_arguments &lt; 2 )
   {
      return( EXIT_SUCCESS );
   }

   TCHAR physical_disk[ MAX_PATH ];

   ZeroMemory( physical_disk, sizeof( physical_disk ) );

   _stprintf( physical_disk, TEXT( &quot;\\\\.\\PHYSICALDRIVE%u&quot; ), _ttoi( command_line_arguments[ 1 ] ) );

   HANDLE disk_handle = NULL;

   disk_handle = CreateFile( physical_disk,
                             GENERIC_READ | GENERIC_WRITE,
                             0,
                             0,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL );

   if ( disk_handle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      DISK_GEOMETRY disk_geometry;

      ZeroMemory( &amp;disk_geometry, sizeof( disk_geometry ) );

      DWORD number_of_bytes_read = 0;

      if ( DeviceIoControl( disk_handle,
                            IOCTL_DISK_GET_DRIVE_GEOMETRY,
                            NULL,
                            0,
                           &amp;disk_geometry,
                            sizeof( disk_geometry ),
                           &amp;number_of_bytes_read,
                            NULL ) != FALSE )
      {
         _tprintf( TEXT( &quot;Number of Cylinders (low)     %lu\n&quot; ), disk_geometry.Cylinders.LowPart  );
         _tprintf( TEXT( &quot;Number of Cylinders (high)    %lu\n&quot; ), disk_geometry.Cylinders.HighPart );
         _tprintf( TEXT( &quot;Number of Tracks per Cylinder %lu\n&quot; ), disk_geometry.TracksPerCylinder  );
         _tprintf( TEXT( &quot;Number of Sectors per Track   %lu\n&quot; ), disk_geometry.SectorsPerTrack    );
         _tprintf( TEXT( &quot;Number of Bytes per Sector    %lu\n&quot; ), disl_geometry.BytesPerSector     );
      }

      <B>wfc_close_handle</B>( disk_handle );
   }

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_close_handle</B>() uses the following API's:
<UL>
<LI>CloseHandle
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_close_handle.cpp $<BR>
$Modtime: 3/17/00 4:47p $
</BODY>

</HTML>
#endif
