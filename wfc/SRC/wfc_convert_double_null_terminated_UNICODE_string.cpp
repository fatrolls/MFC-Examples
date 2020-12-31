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
** $Workfile: wfc_convert_double_null_terminated_UNICODE_string.cpp $
** $Revision: 1 $
** $Modtime: 5/12/00 5:19a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void PASCAL wfc_convert_double_null_terminated_UNICODE_string( const WORD * buffer, CStringArray& string_array )
{
   WFCLTRACEINIT( TEXT( "wfc_convert_double_null_terminated_UNICODE_string()" ) );

   // Always start with a virgin array
   string_array.RemoveAll();

   if ( buffer == NULL )
   {
      return;
   }

   CString string_to_add;

   DWORD number_of_bytes_in_string_including_null = 0;

   // We were passed a pointer, don't trust it

   try
   {
      while ( buffer[ 0 ] != 0x00 )
      {
         string_array.Add( CString( (LPCWSTR) buffer ) );

         number_of_bytes_in_string_including_null = ( lstrlenW( (LPCWSTR) buffer ) * sizeof( WCHAR ) ) + ( 1 * sizeof( WCHAR ) );

         buffer = (const WORD *)( ( (DWORD) buffer ) + number_of_bytes_in_string_including_null );
      }
   }
   catch( ... )
   {
      return;
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_convert_double_null_terminated_UNICODE_string</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that converts a double-NULL terminated string to a CStringArray object (which may be ASCII).">
</HEAD>

<BODY>

<H1>wfc_convert_double_null_terminated_UNICODE_string</H1>
$Revision: 1 $<HR>

<H2>Declaration</H2>
<PRE><CODE>void wfc_convert_double_null_terminated_UNICODE_string( const BYTE * unicode_string, buffer, CStringArray&amp; string_array ) )</CODE></PRE>

<H2>Description</H2>
This function converts a double-NULL terminated string to a CStringArray object.

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   WCHAR dos_device_names[ 4096 ];

   ZeroMemory( dos_device_names, sizeof( dos_device_names ) );

   DWORD return_value = 0;

   return_value = QueryDosDeviceW( NULL, dos_device_names, DIMENSION_OF( dos_device_names ) );

   CStringArray names;

   <B>wfc_convert_double_null_terminated_UNICODE_string</B>( reinterpret_cast&lt; const BYTE * &gt;( dos_device_names ), names );

   int loop_index         = 0;
   int number_of_elements = names.GetSize();

   while( loop_index < number_of_elements )
   {
      _tprintf( TEXT( &quot;%s\n&quot; ), (LPCTSTR) names.GetAt( loop_index ) );
      WFCTRACEVAL( TEXT( &quot;Name: &quot; ), names.GetAt( loop_index ) );
      loop_index++;
   }

   return( EXIT_SUCCESS );
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_convert_double_null_terminated_UNICODE_string.cpp $<BR>
$Modtime: 5/12/00 5:19a $
</BODY>

</HTML>
#endif
