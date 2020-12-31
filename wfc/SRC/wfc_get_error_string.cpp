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
** $Workfile: wfc_get_error_string.cpp $
** $Revision: 11 $
** $Modtime: 1/17/00 9:33a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void PASCAL wfc_get_error_string( DWORD error_code, CString& error_string )
{
   error_string.Empty();

   LPVOID message_buffer = NULL;

   ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    error_code,
                    MAKELANGID( LANG_NEUTRAL, SUBLANG_SYS_DEFAULT ),
          (LPTSTR) &message_buffer,
                    0,
                    NULL );

   error_string = (LPCTSTR) message_buffer;

   ::LocalFree( message_buffer );
   message_buffer = NULL;

   error_string.TrimRight();

   if ( error_string.GetLength() == 0 )
   {
      error_string.Format( TEXT( "Unknown System Error %lu" ), error_code );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_get_error_string</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that converts error codes to something humanly readable.">
</HEAD>

<BODY>

<H1>wfc_get_error_string</H1>
$Revision: 11 $<HR>

<H2>Declaration</H2>
<PRE>void <B>wfc_get_error_string</B>( DWORD error_code, CString&amp; error_string )</PRE>

<H2>Description</H2>
This function takes a value returned from GetLastError() and formats 
it into something humanly readable.

<H2>Example</H2>
<PRE><CODE>void print_error( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;print_error()&quot; ) );

   DWORD error_code = GetLastError();

   CString something_a_human_can_understand;

   <B>wfc_get_error_string</B>( error_code, something_a_human_can_understand );

   _tprintf( TEXT( &quot;%s\n&quot; ), (LPCTSTR) something_a_human_can_understand );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_get_error_string</B>() uses the following API's:
<UL>
<LI>FormatMessage
<LI>LocalFree
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_get_error_string.cpp $<BR>
$Modtime: 1/17/00 9:33a $
</BODY>

</HTML>
#endif
