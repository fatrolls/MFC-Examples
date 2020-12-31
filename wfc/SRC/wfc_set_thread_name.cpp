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
** $Workfile: wfc_set_thread_name.cpp $
** $Revision: 1 $
** $Modtime: 1/17/00 9:35a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

static WFC_THREAD_INFORMATION_BLOCK * get_thread_information_block( void )
{
   WFC_THREAD_INFORMATION_BLOCK * return_value = NULL;

   __asm
   {
      mov eax, fs:[18h]
      mov return_value, eax
   }

   return( return_value );
}

/*
** This is basically cleaned up code from the Jan 2000 issue of MSJ
*/

void PASCAL wfc_set_thread_name( LPCTSTR thread_name )
{
   WFCLTRACEINIT( TEXT( "wfc_set_thread_name()" ) );

   WFC_THREAD_INFORMATION_BLOCK * thread_information_block_p = get_thread_information_block();

   thread_information_block_p->Arbitrary = (VOID *) thread_name;
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_set_thread_name</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that allows you to give a string name to a thread.">
</HEAD>

<BODY>

<H1>wfc_set_thread_name</H1>
$Revision: 1 $<HR>

<H2>Declaration</H2>
<PRE>void <B>wfc_set_thread_name</B>( LPCTSTR thread_name )</PRE>

<H2>Description</H2>
This function gives a thread a name supplied by the caller.
This makes debugging easier. Instead of having thread 0x3C, you
can have thread &quot;server_worker_thread&quot;.

<H2>Example</H2>

<PRE><CODE>int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   <B>wfc_set_thread_name</B>( &quot;_tmain()&quot; );

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>
None! It does use a little Intel specific assembly code.

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_set_thread_name.cpp $<BR>
$Modtime: 1/17/00 9:35a $
</BODY>

</HTML>
#endif
