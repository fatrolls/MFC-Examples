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
** $Workfile: wfc_move_file_at_reboot.cpp $
** $Revision: 4 $
** $Modtime: 1/17/00 9:35a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_move_file_at_reboot( const CString& existing_file, const CString& file_to_move )
{
   WFCLTRACEINIT( TEXT( "wfc_move_file_at_reboot()" ) );

   // First, we must delete the destination file

   if ( MoveFileEx( file_to_move, NULL, MOVEFILE_DELAY_UNTIL_REBOOT ) == FALSE )
   {
      WFCTRACEERROR( GetLastError() );
      WFCTRACEVAL( TEXT( "Can't schedule a deletion for " ), file_to_move );
   }

   if ( MoveFileEx( existing_file, file_to_move, MOVEFILE_DELAY_UNTIL_REBOOT ) == FALSE )
   {
      WFCTRACEERROR( GetLastError() );
      WFCTRACEVAL( TEXT( "Can't schedule a move for " ), file_to_move );
      return( FALSE );
   }

   // The children at Microsoft that wrote Windows 95 forgot about MoveFileEx
   // so they stuck with something they could understand, INI files!!!!

   // WritePrivateProfileString( TEXT( "Rename" ), file_to_move, existing_file, TEXT( "wininit.ini" ) );

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_move_file_at_reboot</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="Simple C function that moves a file at boot time.">
</HEAD>

<BODY>

<H1>wfc_move_file_at_reboot</H1>
$Revision: 4 $<HR>

<H2>Declaration</H2>

<PRE>void <B>wfc_move_file_at_reboot</B>( const CString&amp; existing_file, const CString&amp; file_to_move )</PRE>

<H2>Description</H2>

This function allows you to replace a file at reboot. You normally
need to do this when the file is constantly in use (like a DLL). The
only time to replace the file is when it is not being used by the
program that is always running. The only time to do this is when
NT is rebooting. This is how operating system files get updated.

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   if ( number_of_command_line_arguments < 3 )
   {
      _tprintf( TEXT( &quot;Usage: moveatreboot source destination\n&quot; ) );
      return( EXIT_FAILURE );
   }

   if ( <B>wfc_move_file_at_reboot</B>( command_line_arguments[ 1 ], command_line_arguments[ 2 ] ) != FALSE )
   {
      _tprintf( &quot;Move OK\n&quot; );
   }
   else
   {
      _tprintf( &quot;Move not ok\n&quot; );
   }

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_move_file_at_reboot</B>() uses the following API's:
<UL>
<LI>MoveFileEx
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_move_file_at_reboot.cpp $<BR>
$Modtime: 1/17/00 9:35a $
</BODY>

</HTML>
#endif
