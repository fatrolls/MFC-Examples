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
** $Workfile: wfc_get_operating_system_version_string.cpp $
** $Revision: 11 $
** $Modtime: 1/17/00 9:34a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void PASCAL wfc_get_operating_system_version_string( CString& version_string )
{
   WFCLTRACEINIT( TEXT( "wfc_get_operating_system_version_string()" ) );

   version_string.Empty();

   COperatingSystemVersionInformation version_information;

   if ( GetVersionEx( version_information ) != FALSE )
   {
      CString operating_system_identity;

      switch( version_information.dwPlatformId )
      {
         case VER_PLATFORM_WIN32s:

            operating_system_identity = TEXT( "Windows 3.1 running Win32s" );
            break;

         case VER_PLATFORM_WIN32_WINDOWS:

            operating_system_identity = TEXT( "Windows 95" );
            break;

         case VER_PLATFORM_WIN32_NT:

            operating_system_identity = TEXT( "Windows NT" );
            break;

         default:

            operating_system_identity.Format( TEXT( "Unknown Operating System with an ID of %lu" ), version_information.dwPlatformId );
            break;
      }

      version_string.Format( TEXT( "%s Version %lu.%lu Build %lu %s" ),
                             (LPCTSTR) operating_system_identity,
                             version_information.dwMajorVersion,
                             version_information.dwMinorVersion,
                             version_information.dwBuildNumber,
                             version_information.szCSDVersion );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_get_operating_system_version_string</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that retrieves the operating system version string like the one that is displayed when NT is booting.">
</HEAD>

<BODY>

<H1>wfc_get_operating_system_version_string</H1>
$Revision: 11 $<HR>

<H2>Declaration</H2>
<PRE>void <B>wfc_get_operating_system_version_string</B>( CString&amp; string )</PRE>

<H2>Description</H2>
This function retrieves the operating system version string like the
one that is displayed when NT is booting.

<H2>Example</H2>

<PRE><CODE>void print_version( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;print_version()&quot; ) );

   CString version_string;

   <B>wfc_get_operating_system_version_string</B>( version_string );

   _tprintf( TEXT( &quot;You are running %s\n&quot; ), (LPCTSTR) version_string );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_get_operating_system_version_string</B>() uses the following API's:
<UL>
<LI>GetVersionEx
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_get_operating_system_version_string.cpp $<BR>
$Modtime: 1/17/00 9:34a $
</BODY>

</HTML>
#endif
