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
** $Workfile: wfc_convert_lpwstr_to_cstring.cpp $
** $Revision: 15 $
** $Modtime: 1/17/00 9:33a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void PASCAL wfc_convert_lpcwstr_to_cstring( LPCWSTR source_string, CString& destination_string )
{
   // Always start off with an empty string
   destination_string.Empty();

   if ( source_string == NULL )
   {
      // Our job is done
      return;
   }

   try
   {
      int index = 0;

      TCHAR character_to_add = 0;

      character_to_add = (TCHAR) source_string[ index ];

      while( character_to_add != 0 )
      {
         destination_string += character_to_add;
         index++;
         character_to_add = (TCHAR) source_string[ index ];
      }
   }
   catch( ... )
   {
      return;
   }
}

void PASCAL wfc_convert_lpcstr_to_cstring( const char * source_string, CString& destination_string )
{
   // This function in needed in the UNICODE world

   // Always start off with an empty string
   destination_string.Empty();

   if ( source_string == NULL )
   {
      // Our job is done
      return;
   }

   try
   {
      int index = 0;

      TCHAR character_to_add = 0;

      character_to_add = (TCHAR) source_string[ index ];

      while( character_to_add != 0 )
      {
         destination_string += character_to_add;
         index++;
         character_to_add = (TCHAR) source_string[ index ];
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
<TITLE>WFC - wfc_convert_lpcwstr_to_cstring</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that copies a UNICODE string into a CString object (which may be ASCII).">
</HEAD>

<BODY>

<H1>wfc_convert_lpcwstr_to_cstring</H1>
$Revision: 15 $<HR>

<H2>Declaration</H2>
<PRE><CODE>void wfc_convert_lpcwstr_to_cstring( LPCWSTR&amp; unicode_string, CString&amp; string )</CODE></PRE>

<H2>Description</H2>
This eliminated a lot of code in the networking classes.
Microsoft (even in Visual C++ version 4.2) has the networking API header files all screwed up.
The string parameters are mis-typed. I used to have a lot of code in the classes to detect and 
fix this but it was real ugly (and prevented const correctness). Adding this function allowed
me to fix Microsoft's mistake in one function.

<H2>Example</H2>

<PRE><CODE>void print_machine_name( WKSTA_INFO_102 * information_p )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;print_machine_name()&quot; ) );

   // We were passed a pointer, do not trust it

   try
   {
      CString machine_name;

      // The wki102_computername field of the WKSTA_INFO_102 structure is
      // of type LPTSTR. This is wrong. The correct type is LPWSTR. Why?
      // LPTSTR is #define'd differently for different builds. In ANSI builds,
      // LPTSTR equates to LPSTR, in UNICODE builds LPTSTR equates to LPWSTR.
      // The LanMan data structures are always UNICODE regardless of the
      // build type. It would seem Microsoft's own programmers don't
      // understand the difference. Most of the LanMan API data structures
      // suffer from this problem.

      <B>wfc_convert_lpcwstr_to_cstring</B>( information_p-&gt;wki102_computername, machine_name );

      _tprintf( TEXT( &quot;Machine Name is &quot; ), (LPCTSTR) machine_name );
   }
   catch( ... )
   {
      return;
   }
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_convert_lpwstr_to_cstring.cpp $<BR>
$Modtime: 1/17/00 9:33a $
</BODY>

</HTML>
#endif
