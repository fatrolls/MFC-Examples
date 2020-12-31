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
** $Workfile: wfc_undocumented_get_system_process_list.cpp $
** $Revision: 1 $
** $Modtime: 1/17/00 9:36a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_undocumented_get_system_process_list( BYTE * buffer, DWORD size_of_buffer )
{
   WFCLTRACEINIT( TEXT( "wfc_undocumented_get_system_process_list()" ) );

   DWORD (__stdcall *NtQuerySystemInformation)( DWORD, VOID *, DWORD, DWORD * );

   NtQuerySystemInformation = ( DWORD (__stdcall *)( DWORD, VOID *, DWORD, DWORD *) )
                              GetProcAddress( GetModuleHandle( TEXT( "ntdll.dll" ) ),
                              "NtQuerySystemInformation" );

   if ( NtQuerySystemInformation == NULL )
   {
      return( 0 );
   }

   if ( NtQuerySystemInformation( 5, buffer, size_of_buffer, 0 ) != 0 )
   {
      return( 0 );
   }

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_undocumented_get_system_process_list</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="Simple C that uses an undocumented NT function (NtQuerySystemInformation) to get a list of active processes on an NT system.">
</HEAD>

<BODY>

<H1>wfc_undocumented_get_system_process_list</H1>
$Revision: 1 $<HR>

<H2>Declaration</H2>

<PRE>DWORD <B>wfc_undocumented_get_system_process_list</B>( BYTE * buffer, DWORD size_of_buffer )</PRE>

<H2>Description</H2>

This function allows you to get a whole bunch of information about the
currently running processes.

<P>

<B>WARNING</B> It uses an undocumented call and may no longer be supported.

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

void print_system_record( WFC_SYSTEM_PROCESS_INFORMATION * process_p )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;print_system_record()&quot; ) );

   _tprintf( TEXT( &quot;Thread Count     = %lu\n&quot;,  process_p-&gt;ThreadCount );
   _tprintf( TEXT( &quot;CreateTime       = %I64u\n&quot;, process_p-&gt;CreateTime );
   _tprintf( TEXT( &quot;UserTime         = %I64u\n&quot;, process_p-&gt;UsetTime );
   _tprintf( TEXT( &quot;KernelTime       = %I64u\n&quot;, process_p-&gt;KernelTime );
   _tprintf( TEXT( &quot;Name             = %S\n&quot;, process_p-&gt;Name.Buffer );
   _tprintf( TEXT( &quot;BasePriority     = %lu\n&quot;, process_p-&gt;BasePriority );
   _tprintf( TEXT( &quot;UniqueProcessID  = %lu\n&quot;, process_p-&gt;UniqueProcessID );
   _tprintf( TEXT( &quot;InheritedFrom    = %lu\n&quot;, process_p-&gt;InheritedFromUniqueProcessID );
   _tprintf( TEXT( &quot;HandleCount      = %lu\n&quot;, process_p-&gt;HandleCount );

   _tprintf( TEXT( &quot;VmCounters =\n{\n&quot );
   print_vm_counters( &amp;process_p-&gt;VmCounters );
   _tprintf( TEXT) &quot;}\n&quot; );

   _tprintf( TEXT( &quot;CommitCharge     = %lu\n&quot;, process_p-&gt;CommitCharge );

   DWORD loop_index = 0;

   while( loop_index &lt; process_p-&gt;ThreadCount )
   {
      _tprintf( TEXT( &quot;Thread %lu\n{\n&quot;, loop_index );
      print_system_thread( &amp;process_p-&gt;Threads[ loop_index ] );
      _tprintf( TEXT( &quot;}\n&quot; );

      loop_index++;
   }
}

int _tmain( int, LPCTSTR[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   DWORD size_of_buffer = 128 * 1024;

   BYTE * buffer = (BYTE *) malloc( size_of_buffer );

   if ( <B>wfc_undocumented_get_system_process_list</B>( buffer, size_of_buffer ) == FALSE )
   {
      _tprintf( TEXT( &quot;Can't get process information.\n&quot; );
      free( buffer );
      return( EXIT_FAILURE );
   }

   WFC_SYSTEM_PROCESS_INFORMATION * info_p = (WFC_SYSTEM_PROCESS_INFORMATION *) buffer );

   while( info_p-&gt;Next != 0 )
   {
      print_system_record( info_p );
      info_p = (WFC_SYSTEM_PROCESS_INFORMATION *) ( (DWORD) info_p + info_p-&gt;Next );
   }

   free( buffer );

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_undocumented_get_system_process_list</B>() uses the following
<B>undocumented</B> API's:
<UL>
<LI>NtQuerySystemInformation
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_undocumented_get_system_process_list.cpp $<BR>
$Modtime: 1/17/00 9:36a $
</BODY>

</HTML>
#endif
