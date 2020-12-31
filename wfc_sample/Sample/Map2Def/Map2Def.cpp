#include <wfc.h>
#include <imagehlp.h>
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
** $Workfile: Map2Def.cpp $
** $Revision: 6 $
** $Modtime: 7/11/98 6:26a $
*/

// include the right library in the linker stage
#pragma comment( lib, "imagehlp.lib" )

void convert_file( const CString& filename, CRandomNumberGenerator& random )
{
   CStdioFile input_file;

   if ( input_file.Open( filename, CFile::modeRead ) == FALSE )
   {
      _tprintf( TEXT( "Can't open %s\n" ), (LPCTSTR) filename );
      return;
   }

   TCHAR undecorated_name[ 513 ];

   DWORD ordinal_number = 10;

   CString beginning(                  TEXT( "??_EC"           ) );
   CString ending(                     TEXT( "@@UAEPAXI@Z"     ) );
   CString static_symbols(             TEXT( " Static symbols" ) );
   CString scalar_deleting_destructor( TEXT( "??_G"            ) );
   CString new_operator(               TEXT( "??2@YAPAXI@Z"    ) );
   CString static_string(              TEXT( "??_C@_0"         ) );
   CString real_string(                TEXT( "__real@"         ) );
   CString line_string(                TEXT( "?__LINE__Var@"   ) );

   CString string_from_file;
   CString time_string;
   CString base_memory_address_string;

   CString def_filename;
   CString library_line;

   BOOL should_i_output_this_line = FALSE;

   CStdioFile def_file;

   DWORD base_memory_address = 0;

   CTime the_time = CTime::GetCurrentTime();

   time_string = the_time.Format( TEXT( "; Created by Map2Def on %Y%m%d %H%M%S\n\n" ) );

   while( input_file.ReadString( string_from_file ) != FALSE )
   {
      def_filename.Empty();
      library_line.Empty();

      int period_location = filename.Find( TEXT( '.' ) );

      if ( period_location != (-1) )
      {
         def_filename = filename.Left( period_location );
      }
      else
      {
         def_filename = filename;
      }

      // Now we have the filename without an extension

      library_line = TEXT( "LIBRARY " ) + def_filename;

      base_memory_address = ( random.GetInteger() % 32767 );

      /*
      ** If we're using Map2Def, we are most likely creating a DLL.
      ** Visual C++ uses a fixed memory location for the DLLs it creates.
      ** This results in memory address space conflicts and the loader
      ** has to relocate your DLL. To fix that problem, we create a random
      ** memory location for the DLL to load. This reduces the chances
      ** of the loader having to relocate your DLL (therefore the EXE
      ** loads faster).
      */

      base_memory_address_string.Format( TEXT( "  BASE=0x%04lX0000\n\n" ), base_memory_address );

      library_line += base_memory_address_string;

      def_filename += TEXT( ".def" );

      if ( def_file.Open( def_filename, CFile::modeCreate | CFile::modeWrite ) == FALSE )
      {
         _tprintf( TEXT( "Can't open output file %s\n" ), (LPCTSTR) def_filename );
         input_file.Close();
         return;
      }
      else
      {
         _tprintf( TEXT( "Creating %s\n" ), (LPCTSTR) def_filename );
      }

      def_file.WriteString( time_string );
      def_file.WriteString( library_line );
      def_file.WriteString( TEXT( "EXPORTS\n\n" ) );

      while( input_file.ReadString( string_from_file ) != FALSE )
      {
         if ( string_from_file.GetLength() > 22 )
         {
            if ( string_from_file.GetAt(  5 ) == TEXT( ':' ) &&
               ( string_from_file.GetAt( 21 ) == TEXT( '?' ) || string_from_file.GetAt( 21 ) == TEXT( '_' ) ) )
            {
               int location_of_space = 0;

               // We may have one here...

               string_from_file = string_from_file.Right( string_from_file.GetLength() - 21 );

               location_of_space = string_from_file.Find( TEXT( ' ' ) );

               if ( location_of_space != (-1) )
               {
                  CString decorated_name;
                  CString output_line;

                  decorated_name = string_from_file.Left( location_of_space );

                  string_from_file = string_from_file.Right( string_from_file.GetLength() - location_of_space );

                  // Now let's see if this is an import

                  location_of_space = string_from_file.Find( TEXT( ':' ) );

                  if ( location_of_space == (-1) )
                  {
                     // We didn't find our colon, let's do one last check for <common>

                     location_of_space = string_from_file.Find( TEXT( '<' ) );

                     if ( location_of_space == (-1) )
                     {
                        // Now make sure we don't include the vector deleting destructor

                        if ( ( decorated_name.GetLength() > ending.GetLength() ) &&
                             ( beginning.Compare( decorated_name.Left( beginning.GetLength() ) ) == 0 ) &&
                             ( ending.Compare( decorated_name.Right( ending.GetLength() ) ) == 0 ) )
                        {
                           // Do Nothing
                        }
                        else if ( scalar_deleting_destructor.Compare( decorated_name.Left( scalar_deleting_destructor.GetLength() ) ) != 0 )
                        {
                           // Now make sure it isn't a special name

                           if ( decorated_name.CompareNoCase( TEXT( "__pRawDllMain"    ) ) != 0 &&
                                decorated_name.CompareNoCase( TEXT( "__afxForceEXTDLL" ) ) != 0 &&
                                decorated_name.CompareNoCase( new_operator               ) != 0 )
                           {
                              should_i_output_this_line = TRUE;

                              if ( decorated_name.GetLength() > static_string.GetLength() )
                              {
                                 if ( static_string.Compare( decorated_name.Left( static_string.GetLength() ) ) == 0 )
                                 {
                                    should_i_output_this_line = FALSE;
                                 }
                              }

                              if ( decorated_name.GetLength() > real_string.GetLength() )
                              {
                                 if ( real_string.Compare( decorated_name.Left( real_string.GetLength() ) ) == 0 )
                                 {
                                    should_i_output_this_line = FALSE;
                                 }
                              }

                              if ( decorated_name.GetLength() > line_string.GetLength() )
                              {
                                 if ( line_string.Compare( decorated_name.Left( line_string.GetLength() ) ) == 0 )
                                 {
                                    should_i_output_this_line = FALSE;
                                 }
                              }

                              if ( should_i_output_this_line != FALSE )
                              {
                                 output_line.Format( TEXT( " %s @ %lu NONAME" ),
                                                     (LPCTSTR) decorated_name,
                                                     ordinal_number );

                                 ZeroMemory( undecorated_name, sizeof( undecorated_name ) );

                                 // It is unclear if the third parameter should be the size of the buffer or
                                 // the number of characters undecorated_name can hold. Documentation is shoddy
                                 if ( UnDecorateSymbolName( decorated_name, undecorated_name, sizeof( undecorated_name ), UNDNAME_COMPLETE ) > 0 )
                                 {
                                    output_line += TEXT( " ; " );
                                    output_line += undecorated_name;
                                 }

                                 output_line += TEXT( "\n" );
                                 ordinal_number++;
                              }
                           }
                        }

                        def_file.WriteString( output_line );
                     }
                  }
               }
            }
         }
         else
         {
            if ( ( string_from_file.GetLength() >= static_symbols.GetLength() ) &&
                 ( static_symbols.Compare( string_from_file.Left( static_symbols.GetLength() ) ) == 0 ) )
            {
               def_file.Close();
               input_file.Close();
               return;
            }
         }
      }

      def_file.Close();
   }

   input_file.Close();
}

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   if ( number_of_command_line_arguments < 2 )
   {
      _tprintf( TEXT( "Usage: Map2Def file [file [file [...]]]\n" ) );
      return( EXIT_SUCCESS );
   }

   HANDLE find_file_handle = (HANDLE) NULL;

   WIN32_FIND_DATA find_data;

   CRandomNumberGenerator random;

   int index = 1;

   while( index < number_of_command_line_arguments )
   {
      ZeroMemory( &find_data, sizeof( find_data ) );

      find_file_handle = FindFirstFile( command_line_arguments[ index ], &find_data );

      if ( find_file_handle != INVALID_HANDLE_VALUE )
      {
         convert_file( find_data.cFileName, random );

         while( FindNextFile( find_file_handle, &find_data ) != FALSE )
         {
            convert_file( find_data.cFileName, random );
         }

         FindClose( find_file_handle );
      }

      index++;
   }

   return( EXIT_SUCCESS );
}
