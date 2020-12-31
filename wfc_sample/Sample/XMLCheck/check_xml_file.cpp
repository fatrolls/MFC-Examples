#include "XMLCheck.h"
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
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: save_document.cpp $
** $Revision: 1 $
** $Modtime: 3/23/98 7:09p $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void check_xml_file( const CString& filename )
{
   WFCTRACEINIT( TEXT( "check_xml_file()" ) );
   //WFCTRACEVAL( TEXT( "Checking " ), filename );
   // d:\WFC\test\xml\xmltest\not-wf\sa

   CExtensibleMarkupLanguageDocument document;

   DWORD parsing_options = document.GetParseOptions();

   parsing_options |= WFC_XML_ALLOW_REPLACEMENT_OF_DEFAULT_ENTITIES;

   document.SetParseOptions( parsing_options );

   CFile file;

   if ( file.Open( filename, CFile::modeRead ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't open " ), filename );
      WFCTRACEERROR( GetLastError() );
      _tprintf( TEXT( "Can't open %s\n" ), (LPCTSTR) filename );
      return;
   }

   CByteArray bytes;

   bytes.SetSize( file.GetLength() );

   file.Read( bytes.GetData(), bytes.GetSize() );

   file.Close();

   CDataParser parser;

   parser.Initialize( &bytes, FALSE );

   CSystemTime begin_parsing;
   CSystemTime end_parsing;

   DWORD start_tick_count = 0;
   DWORD end_tick_count   = 0;

   BOOL should_parse_fail = FALSE;

   begin_parsing.Get();
   start_tick_count = GetTickCount();

   WFCTRACELEVELON( 31 );

   if ( document.Parse( parser ) == TRUE )
   {
      // We parsed OK

      end_tick_count = GetTickCount();
      end_parsing.Get();

#if defined( _DEBUG )

      if ( should_parse_fail != FALSE )
      {
         // We should not have been able to parse this XML.
         ASSERT( FALSE );
      }

#endif // _DEBUG

      //WFCTRACEVAL( TEXT( "XML parsed OK " ), filename );
      _tprintf( TEXT( "\"%s\" parsed OK\n" ), (LPCTSTR) filename );

      CTime start_time;
      CTime end_time;

      begin_parsing.CopyTo( start_time );
      end_parsing.CopyTo( end_time );

      CTimeSpan time_span;
      
      time_span = end_time - start_time;

      if ( time_span.GetTotalSeconds() == 0 )
      {
         // Less than a second!

         DWORD number_of_milliseconds = end_tick_count - start_tick_count;

         //WFCTRACEVAL( TEXT( "Parse time in Milliseconds is " ), number_of_milliseconds );
         _tprintf( TEXT( "It took %lu ms to parse.\n\n" ), number_of_milliseconds );
      }
      else
      {
         DWORD number_of_milliseconds = end_tick_count - start_tick_count;
         //WFCTRACEVAL( TEXT( "Parse time in seconds is " ), time_span.GetTotalSeconds() );
         _tprintf( TEXT( "It took %lu seconds (%lu milliseconds) to parse %lu elements (%d bytes).\n\n" ),
                  (DWORD) time_span.GetTotalSeconds(),
                  number_of_milliseconds,
                  document.GetNumberOfElements(),
                  bytes.GetSize() );
      }

#if 0

      // Make sure we write out what we read in

      CFile output_file;

      if ( output_file.Open( TEXT( "d:\\temp\\check.out" ), CFile::modeCreate | CFile::modeWrite ) == FALSE )
      {
         WFCTRACE( TEXT( "Can't open check.out" ) );
      }
      else
      {
         CByteArray xml_output;

         document.WriteTo( xml_output );

         output_file.Write( xml_output.GetData(), xml_output.GetSize() );

         WFCTRACEVAL( TEXT( "Wrote to " ), output_file.GetFilePath() );

         output_file.Close();
      }

#if 0

      CExtensibleMarkupLanguageElement * element_p = document.GetElement( TEXT( "ovvoba.vergabenummern.gesamtvergabelosnummer" ) );

      if ( element_p != NULL )
      {
         CString directory;

         element_p->GetText( directory );

         WFCTRACEVAL( TEXT( "Directory is " ), directory );
      }

#endif // 0

#endif // _DEBUG

      WFCTRACELEVELOFF( 31 );
   }
   else
   {
      WFCTRACEVAL( TEXT( "FAILED! " ), filename );
      _tprintf( TEXT( "FAIL! \"%s\"\n" ), (LPCTSTR) filename );

#if defined( _DEBUG )

      if ( should_parse_fail == FALSE )
      {
         // Skip the files that we know we can't parse

         if ( filename.CompareNoCase( TEXT( "063.XML" ) ) != 0 &&
              filename.CompareNoCase( TEXT( "097.XML" ) ) != 0 )
         {
            // We should have been able to parse this XML
            ASSERT( FALSE );
         }
      }

#endif // _DEBUG

      CString tag_name;
      CString error_message;

      CParsePoint began_at;
      CParsePoint failed_at;

      document.GetParsingErrorInformation( tag_name, began_at, failed_at, &error_message );

      _tprintf( TEXT( "Tag is %s\n" ), (LPCTSTR) tag_name );
      _tprintf( TEXT( "Reason is %s\n" ), (LPCTSTR) error_message );
      _tprintf( TEXT( "Element began at line %lu, column %lu (byte index %lu)\n" ),
                began_at.GetLineNumber(),
                began_at.GetLineIndex(),
                began_at.GetIndex() );

      _tprintf( TEXT( "Error occurred at line %lu, column %lu (byte index %lu)\n\n" ),
                failed_at.GetLineNumber(),
                failed_at.GetLineIndex(),
                failed_at.GetIndex() );

      WFCTRACEVAL( TEXT( "Tag Name is " ), tag_name );
      WFCTRACEVAL( TEXT( "Reason is " ), error_message );
      WFCTRACEVAL( TEXT( "began at line number " ), began_at.GetLineNumber() );
      WFCTRACEVAL( TEXT( "began at column " ), began_at.GetLineIndex() );
      WFCTRACEVAL( TEXT( "began at byte index " ), began_at.GetIndex() );
      WFCTRACEVAL( TEXT( "err'd at line number " ), failed_at.GetLineNumber() );
      WFCTRACEVAL( TEXT( "err'd at column " ), failed_at.GetLineIndex() );
      WFCTRACEVAL( TEXT( "err'd at byte index " ), failed_at.GetIndex() );
   }
}

/*
C:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE\afx.inl(27) : fatal error C1001: INTERNAL COMPILER ERROR
  (compiler file 'E:\8168\vc98\p2\src\P2\main.c', line 494)
    Please choose the Technical Support command on the Visual C++
    Help menu, or open the Technical Support help file for more information
Error executing cl.exe.
*/
