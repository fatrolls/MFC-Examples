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
** $Workfile: wfc_start_screen_saver.cpp $
** $Revision: 9 $
** $Modtime: 1/17/00 9:36a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void PASCAL wfc_start_screen_saver( void )
{
   WFCLTRACEINIT( TEXT( "wfc_start_screen_saver()" ) );
   SendMessage( GetDesktopWindow(), WM_SYSCOMMAND, SC_SCREENSAVE, 0L );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_start_screen_saver</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that starts the screen saver.">
</HEAD>

<BODY>

<H1>wfc_start_screen_saver</H1>
$Revision: 9 $<HR>

<H2>Declaration</H2>
<PRE>void <B>wfc_start_screen_saver</B>( void )</PRE>

<H2>Description</H2>
This function starts the current screen saver.

<H2>Example</H2>

<PRE><CODE>int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   <B>wfc_start_screen_saver</B>();

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_start_screen_saver</B>() uses the following API's:
<UL>
<LI>GetDesktopWindow
<LI>SendMessage
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_start_screen_saver.cpp $<BR>
$Modtime: 1/17/00 9:36a $
</BODY>
</HTML>
#endif
