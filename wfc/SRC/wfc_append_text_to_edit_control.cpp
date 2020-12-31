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
** $Workfile: wfc_append_text_to_edit_control.cpp $
** $Revision: 4 $
** $Modtime: 1/17/00 9:31a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void PASCAL wfc_append_text_to_edit_control( HWND edit_control_handle, LPCTSTR text_string )
{
   WFCLTRACEINIT( TEXT( "wfc_append_text_to_edit_control()" ) );

   if ( text_string == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it...

   try
   {
      int index = GetWindowTextLength( edit_control_handle );

      SetFocus( edit_control_handle ); // Do I need this?
      SendMessage( edit_control_handle, EM_SETSEL, (WPARAM) index, (LPARAM) index );
      SendMessage( edit_control_handle, EM_REPLACESEL, 0, (LPARAM) text_string );
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
<TITLE>WFC - wfc_append_text_to_edit_control</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that makes it easy to add text to an edit control.">
</HEAD>

<BODY>

<H1>wfc_append_text_to_edit_control</H1>
$Revision: 4 $<HR>

<H2>Declaration</H2>

<PRE>void <B>wfc_append_text_to_edit_control</B>( void )</PRE>

<H2>Description</H2>

This function appends a string to an edit control.

<H2>Example</H2>

<PRE><CODE>void add_time( HWND edit_control_handle )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;add_time()&quot; ) );

   CTime the_time = CTime::GetCurrentTime();

   CString time_string;

   time_string = the_time.Format( TEXT( &quot;%Y-%m-%dT%H:%M:%S&quot; ) );
   
   <B>wfc_append_text_to_edit_control</B>( edit_control_handle, time_string );
}</CODE></PRE>

<H2>API's Used</H2>

<B>wfc_append_text_to_edit_control</B>() uses the following API's:
<UL>
<LI>GetWindowTextLength
<LI>SendMessage
<LI>SetFocus
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_append_text_to_edit_control.cpp $<BR>
$Modtime: 1/17/00 9:31a $
</BODY>

</HTML>
#endif
