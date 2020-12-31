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
** $Workfile: wfc_get_filename_from_handle.cpp $
** $Revision: 1 $
** $Modtime: 1/17/00 9:34a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_get_filename_from_handle( HANDLE file_handle, CString& filename )
{
   typedef struct _io_status_block
   {
      DWORD Status;
      DWORD Information;
   }
   MY_IO_STATUS_BLOCK;

   typedef struct _file_name_information
   {
      DWORD FileNameLength;
      WCHAR FileName[ 4096 ];
   }
   MY_FILE_NAME_INFORMATION;

   filename.Empty();

   DWORD (__stdcall *NtQueryInformationFile)( HANDLE, MY_IO_STATUS_BLOCK *, VOID *, DWORD, DWORD );

   NtQueryInformationFile = ( DWORD (__stdcall *)( HANDLE, MY_IO_STATUS_BLOCK *, VOID *, DWORD, DWORD) )
                              GetProcAddress( GetModuleHandle( TEXT( "ntdll.dll" ) ),
                              "NtQueryInformationFile" );

   if ( NtQueryInformationFile == NULL )
   {
      return( FALSE );
   }

   MY_FILE_NAME_INFORMATION filename_structure;

   ZeroMemory( &filename_structure, sizeof( filename_structure ) );

   MY_IO_STATUS_BLOCK status_block;

   status_block.Status      = 0;
   status_block.Information = 0;

   DWORD status = NtQueryInformationFile( file_handle,
                                         &status_block,
                                         &filename_structure,
                                          sizeof( filename_structure ),
                                          9 );

   if ( status == 0 )
   {
      filename_structure.FileName[ filename_structure.FileNameLength / sizeof( WCHAR ) ] = 0;
   }
   else
   {
      return( FALSE );
   }

   wfc_convert_lpcwstr_to_cstring( filename_structure.FileName, filename );

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_get_filename_from_handle</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that returns a file's name given only its handle.">
</HEAD>

<BODY>

<H1>wfc_get_filename_from_handle</H1>
$Revision: 1 $<HR>

<H2>Declaration</H2>
<PRE>BOOL <B>wfc_get_filename_from_handle</B>( HANDLE file_handle, CString&amp; file_name )</PRE>

<H2>Description</H2>
This function retrieves the name of a file given only its handle.
It does this by using a partially documented function named
<CODE>NtQueryInformationFile</CODE> in NTDLL.DLL.

<H2>Example</H2>
<PRE><CODE>void print_error( DWORD error_code, HANDLE file_handle )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;print_error()&quot; ) );

   CString something_a_human_can_understand;

   <A HREF="wfc_get_error_string.htm">wfc_get_error_string</A>( error_code, something_a_human_can_understand );

   CString filename;

   if ( <B>wfc_get_filename_from_handle</B>( file_handle, filename ) == TRUE )
   {
      _tprintf( TEXT( &quot;%s - %s\n&quot; ),
                (LPCTSTR) filename,
                (LPCTSTR) something_a_human_can_understand );
   }
   else
   {
      _tprintf( TEXT( &quot;%s\n&quot; ), (LPCTSTR) something_a_human_can_understand );
   }
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_get_error_string</B>() uses the following API's:
<UL>
<LI>GetModuleHandle
<LI>GetProcAddress
<LI>NtQueryInformationFile
<LI>ZeroMemory
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_get_filename_from_handle.cpp $<BR>
$Modtime: 1/17/00 9:34a $
</BODY>

</HTML>
#endif
