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
** $Workfile: wfc_get_web_page.cpp $
** $Revision: 18 $
** $Modtime: 1/17/00 9:34a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void PASCAL wfc_get_web_page( CUniformResourceLocator& url, CStringArray& page_contents )
{
   WFCLTRACEINIT( TEXT( "wfc_get_web_page()" ) );

   CInternetSession * internet_session_p = NULL;

   CHttpFile * source_file_p = NULL;

   try
   {
      page_contents.RemoveAll();

      CString temp_string;

      temp_string.Format( TEXT( "wfc_get_web_page( \"%s\" ) : %lu" ), (LPCTSTR) url, (DWORD) ::GetTickCount() );

      WFCTRACEVAL( TEXT( "Unique ID is " ), temp_string );

      internet_session_p = NULL;

      try
      {
         try
         {
            internet_session_p = new CInternetSession( temp_string );
         }
         catch( ... )
         {
            if ( internet_session_p == NULL )
            {
               return;
            }
         }

         // We use the INTERNET_FLAG_RELOAD because this function is probably NOT
         // going to be the basis for a browser. It will usually be used to retrieve
         // things like stock quotes that change frequently. In this case, cacheing
         // screws you because you don't get the latest data from the Web.

         source_file_p = (CHttpFile *) internet_session_p->OpenURL( url, 1, INTERNET_FLAG_RELOAD | INTERNET_FLAG_TRANSFER_ASCII );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG

         exception_p->Delete();
      }

      if ( source_file_p == NULL )
      {
         return;
      }

      source_file_p->SetReadBufferSize( 65535 * 4 );

      int index = 0;

      while( source_file_p->ReadString( temp_string ) != FALSE )
      {
         index++;
         page_contents.Add( temp_string );
      }

      source_file_p->Close();
      delete source_file_p;
      internet_session_p->Close();
      delete internet_session_p;
   }
   catch( ... )
   {
      try
      {
         source_file_p->Close();
      }
      catch( ... )
      {
         ;
      }

      try
      {
         delete source_file_p;
      }
      catch( ... )
      {
         ;
      }

      try
      {
         internet_session_p->Close();
      }
      catch( ... )
      {
         ;
      }

      try
      {
         delete internet_session_p;
      }
      catch( ... )
      {
         ;
      }

      return;
   }
}

#endif // WFC_STL

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_get_web_page</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that retrieves a web page and stores in an array of strings.">
</HEAD>

<BODY>

<H1>wfc_get_web_page</H1>
$Revision: 18 $<HR>

<H2>Declaration</H2>
<PRE><CODE>void wfc_get_web_page( CUniformResourceLocator&amp; url, CStringArray&amp; page_contents )</CODE></PRE>

<H2>Description</H2>
This function takes a url and retrieves it from Internet. What you get is an
array of CStrings containing the source for that page. This function is meant
to provide the capability to pull data from Internet and chew on it inside
a program (as opposed to display it to a user).

<H2>Example</H2>

<PRE><CODE>void print_maryland_weather_report( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;print_maryland_weather_report()&quot; ) );

   CUniformResourceLocator url( TEXT( &quot;http://iwin.nws.noaa.gov/iwin/md/hourly.html&quot; ) );

   CStringArray weather_report;

   <B>wfc_get_web_page</B>( url, weather_report );

   int index = 0;
   int number_of_lines_in_report = weather_report.GetSize();

   while( index &lt; number_of_lines_in_report )
   {
      _tprintf( TEXT( &quot;%s\n&quot; ), (LPCTSTR) weather_report.GetAt( index ) );
      index++;
   }
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_get_web_page.cpp $<BR>
$Modtime: 1/17/00 9:34a $
</BODY>

</HTML>
#endif
