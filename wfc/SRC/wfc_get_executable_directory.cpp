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
** $Workfile: wfc_get_executable_directory.cpp $
** $Revision: 4 $
** $Modtime: 1/17/00 9:33a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void PASCAL wfc_get_executable_directory( CString& directory_name_ending_in_a_slash )
{
   WFCLTRACEINIT( TEXT( "wfc_get_executable_directory()" ) );

   TCHAR path[ 4096 ];

   ZeroMemory( path, sizeof( path ) );

   if ( GetModuleFileName( NULL, path, DIMENSION_OF( path ) ) != 0 )
   {
      *( _tcsrchr( path, TEXT( '\\' ) ) + 1 ) = 0x00;

      directory_name_ending_in_a_slash = path;
   }
   else
   {
      directory_name_ending_in_a_slash = "\\";
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_get_executable_directory</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that gives you the full pathname to the exectuable.">
</HEAD>

<BODY>

<H1>wfc_get_executable_directory</H1>
$Revision: 4 $<HR>

<H2>Declaration</H2>
<PRE>void <B>wfc_get_executable_directory</B>( CString&amp; directory_name_ending_in_a_slash )</PRE>

<H2>Description</H2>
This function returns the complete path name to the executable. The
string will end in a slash for easy creation of filenames.
Interestingly enough, it is impossible to port this function to Unix.
It is not possible in Unix for a running process to determine which file
it came from. If you ever need an example of something NT can do that
Unix cannot, this is it.

<H2>Example</H2>

<PRE><CODE>int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   CString my_executable;

   <B>wfc_get_executable_directory</B>( my_executable );

   _tprintf( TEXT( &quot;Executing %s\n&quot;, (LPCTSTR) my_executable );

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>

<B>wfc_get_executable_directory</B>() uses the following API's:
<UL>
<LI>GetModuleFileName
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_get_executable_directory.cpp $<BR>
$Modtime: 1/17/00 9:33a $
</BODY>

</HTML>
#endif
