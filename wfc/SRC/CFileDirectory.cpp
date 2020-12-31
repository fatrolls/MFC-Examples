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
** $Workfile: CFileDirectory.cpp $
** $Revision: 5 $
** $Modtime: 3/17/00 4:35p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CFileDirectory::CFileDirectory()
{
   WFCLTRACEINIT( TEXT( "CFileDirectory::CFileDirectory()" ) );
}

CFileDirectory::~CFileDirectory()
{
   WFCLTRACEINIT( TEXT( "CFileDirectory::~CFileDirectory()" ) );
   Close();
}

void CFileDirectory::Close( void )
{
   WFCLTRACEINIT( TEXT( "CFileDirectory::Close()" ) );
   m_Name.Empty();
}

BOOL CFileDirectory::Open( const CString& directory_name )
{
   WFCLTRACEINIT( TEXT( "CFileDirectory::Open()" ) );

   m_Name = directory_name;

   if ( m_Name.GetLength() > 0 )
   {
      if ( m_Name.GetAt( m_Name.GetLength() - 1 ) != TEXT( '/' ) &&
           m_Name.GetAt( m_Name.GetLength() - 1 ) != TEXT( '\\' ) )
      {
         m_Name += TEXT( "/" );
      }

      return( TRUE );
   }

   return( FALSE ); // User passed us an empty string
}

BOOL CFileDirectory::Read( CStringArray& filenames )
{
   WFCLTRACEINIT( TEXT( "CFileDirectory::Read()" ) );

   filenames.RemoveAll();

   HANDLE file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

   WIN32_FIND_DATA find_data;

   ZeroMemory( &find_data, sizeof( find_data ) );

   file_find_handle = ::FindFirstFile( m_Name + TEXT( "*.*" ), &find_data );

   if ( file_find_handle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      CString complete_filename;

      if ( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
      {
         // Skip this file
      }
      else
      {
         complete_filename  = m_Name;
         complete_filename += find_data.cFileName;

         filenames.Add( complete_filename );
      }

      while( ::FindNextFile( file_find_handle, &find_data ) != FALSE )
      {
         if ( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
         {
            // Skip this file
         }
         else
         {
            complete_filename  = m_Name;
            complete_filename += find_data.cFileName;

            filenames.Add( complete_filename );
         }
      }

      if ( ::FindClose( file_find_handle ) == FALSE )
      {
         WFCTRACEERROR( ::GetLastError() );
         WFCTRACE( TEXT( "Couldn't close handle" ) );
      }

      file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

      return( TRUE );
   }

   return( FALSE );
}

BOOL CFileDirectory::Read( FILE_ACTION_FUNCTION action_to_take, void * action_parameter )
{
   WFCLTRACEINIT( TEXT( "CFileDirectory::Read( FILE_ACTION_FUNCTION )" ) );

   HANDLE file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

   WIN32_FIND_DATA find_data;

   ZeroMemory( &find_data, sizeof( find_data ) );

   file_find_handle = ::FindFirstFile( m_Name + TEXT( "*.*" ), &find_data );

   // The user passed us a couple of pointers, don't trust them

   CString complete_filename;

   try
   {
      if ( file_find_handle != (HANDLE) INVALID_HANDLE_VALUE )
      {
         if ( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
         {
            // Skip this file
         }
         else
         {
            complete_filename  = m_Name;
            complete_filename += find_data.cFileName;

            if ( action_to_take( action_parameter, complete_filename ) == FALSE )
            {
               if ( ::FindClose( file_find_handle ) == FALSE )
               {
                  WFCTRACEERROR( ::GetLastError() );
                  WFCTRACE( TEXT( "Couldn't close handle" ) );
               }

               file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

               return( TRUE );
            }
         }

         while( ::FindNextFile( file_find_handle, &find_data ) != FALSE )
         {
            if ( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            {
               // Skip this file
            }
            else
            {
               complete_filename  = m_Name;
               complete_filename += find_data.cFileName;

               if ( action_to_take( action_parameter, complete_filename ) == FALSE )
               {
                  if ( ::FindClose( file_find_handle ) == FALSE )
                  {
                     WFCTRACEERROR( ::GetLastError() );
                     WFCTRACE( TEXT( "Couldn't close handle" ) );
                  }

                  file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

                  return( TRUE );
               }
            }
         }

         if ( ::FindClose( file_find_handle ) == FALSE )
         {
            WFCTRACEERROR( ::GetLastError() );
            WFCTRACE( TEXT( "Couldn't close handle" ) );
         }

         file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

         return( TRUE );
      }
   }
   catch( ... )
   {
      // Do Nothing
   }

   return( FALSE );
}

typedef struct _recursive_directory_read_parameters
{
   HANDLE find_file_handle;
   WIN32_FIND_DATA find_data;
   CString complete_filename;
   CString directory_to_open;
   CString new_directory_name;
   CString directory_name_ending_in_a_slash;
}
RECURSIVE_DIRECTORY_READ_PARAMETERS;

void PASCAL __read_recursively( const CString& directory_name, CStringArray& filenames )
{
   WFCTRACEINIT( TEXT( "__read_recursively()" ) );

   RECURSIVE_DIRECTORY_READ_PARAMETERS * parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );

   try
   {
      parameters_p = new RECURSIVE_DIRECTORY_READ_PARAMETERS;
   }
   catch( ... )
   {
      parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );
   }

   if ( parameters_p == NULL )
   {
      return;
   }

   ZeroMemory( &parameters_p->find_data, sizeof( parameters_p->find_data ) );

   parameters_p->directory_to_open = directory_name;

   if ( parameters_p->directory_to_open.GetLength() == 0 )
   {
      return;
   }

   if ( parameters_p->directory_to_open.GetAt( parameters_p->directory_to_open.GetLength() - 1 ) != TEXT( '/' ) &&
        parameters_p->directory_to_open.GetAt( parameters_p->directory_to_open.GetLength() - 1 ) != TEXT( '\\' ) )
   {
      parameters_p->directory_to_open += TEXT( "/" );
   }

   parameters_p->directory_name_ending_in_a_slash = parameters_p->directory_to_open;

   parameters_p->directory_to_open += TEXT( "*.*" );

   parameters_p->find_file_handle = FindFirstFile( parameters_p->directory_to_open, &parameters_p->find_data );

   if ( parameters_p->find_file_handle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      if ( parameters_p->find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
      {
         if ( _tcscmp( parameters_p->find_data.cFileName, TEXT( "."  ) ) == 0 ||
              _tcscmp( parameters_p->find_data.cFileName, TEXT( ".." ) ) == 0 )
         {
            // Do nothing, to do something would cause infinite recursion and that is a bad thing
         }
         else
         {
            parameters_p->new_directory_name  = parameters_p->directory_name_ending_in_a_slash;
            parameters_p->new_directory_name += parameters_p->find_data.cFileName;

            __read_recursively( parameters_p->new_directory_name, filenames );
         }
      }
      else
      {
         parameters_p->complete_filename  = parameters_p->directory_name_ending_in_a_slash;
         parameters_p->complete_filename += parameters_p->find_data.cFileName;

         filenames.Add( parameters_p->complete_filename );
      }

      while( FindNextFile( parameters_p->find_file_handle, &parameters_p->find_data ) != FALSE )
      {
         if ( parameters_p->find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
         {
            if ( _tcscmp( parameters_p->find_data.cFileName, TEXT( "."  ) ) == 0 ||
                 _tcscmp( parameters_p->find_data.cFileName, TEXT( ".." ) ) == 0 )
            {
               // Do nothing, to do something would cause infinite recursion and that is a bad thing
            }
            else
            {
               parameters_p->new_directory_name  = parameters_p->directory_name_ending_in_a_slash;
               parameters_p->new_directory_name += parameters_p->find_data.cFileName;

               __read_recursively( parameters_p->new_directory_name, filenames );
            }
         }
         else
         {
            parameters_p->complete_filename  = parameters_p->directory_name_ending_in_a_slash;
            parameters_p->complete_filename += parameters_p->find_data.cFileName;

            filenames.Add( parameters_p->complete_filename );
         }
      }

      if ( FindClose( parameters_p->find_file_handle ) == FALSE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Couldn't close handle" ) );
      }

      parameters_p->find_file_handle = (HANDLE) INVALID_HANDLE_VALUE;
   }

   delete parameters_p;
   parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );
}

BOOL PASCAL __read_recursively( const CString& directory_name, FILE_ACTION_FUNCTION action_to_take, void * action_parameter )
{
   WFCTRACEINIT( TEXT( "__read_recursively( FILE_ACTION_FUNCTION )" ) );

   RECURSIVE_DIRECTORY_READ_PARAMETERS * parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );

   try
   {
      parameters_p = new RECURSIVE_DIRECTORY_READ_PARAMETERS;
   }
   catch( ... )
   {
      parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );
   }

   if ( parameters_p == NULL )
   {
      return( FALSE );
   }

   ZeroMemory( &parameters_p->find_data, sizeof( parameters_p->find_data ) );

   parameters_p->directory_to_open = directory_name;

   if ( parameters_p->directory_to_open.GetLength() == 0 )
   {
      return( FALSE );
   }

   if ( parameters_p->directory_to_open.GetAt( parameters_p->directory_to_open.GetLength() - 1 ) != TEXT( '/' ) &&
        parameters_p->directory_to_open.GetAt( parameters_p->directory_to_open.GetLength() - 1 ) != TEXT( '\\' ) )
   {
      parameters_p->directory_to_open += TEXT( "/" );
   }

   parameters_p->directory_name_ending_in_a_slash = parameters_p->directory_to_open;

   parameters_p->directory_to_open += TEXT( "*.*" );

   parameters_p->find_file_handle = FindFirstFile( parameters_p->directory_to_open, &parameters_p->find_data );

   if ( parameters_p->find_file_handle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      if ( parameters_p->find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
      {
         if ( _tcscmp( parameters_p->find_data.cFileName, TEXT( "."  ) ) == 0 ||
              _tcscmp( parameters_p->find_data.cFileName, TEXT( ".." ) ) == 0 )
         {
            // Do nothing, to do something would cause infinite recursion and that is a bad thing
         }
         else
         {
            parameters_p->new_directory_name  = parameters_p->directory_name_ending_in_a_slash;
            parameters_p->new_directory_name += parameters_p->find_data.cFileName;

            if ( __read_recursively( parameters_p->new_directory_name, action_to_take, action_parameter ) == FALSE )
            {
               if ( FindClose( parameters_p->find_file_handle ) == FALSE )
               {
                  WFCTRACEERROR( ::GetLastError() );
                  WFCTRACE( TEXT( "Couldn't close handle" ) );
               }

               delete parameters_p;
               parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );

               return( FALSE );
            }
         }
      }
      else
      {
         parameters_p->complete_filename  = parameters_p->directory_name_ending_in_a_slash;
         parameters_p->complete_filename += parameters_p->find_data.cFileName;

         try
         {
            if ( action_to_take( action_parameter, parameters_p->complete_filename ) == FALSE )
            {
               if ( FindClose( parameters_p->find_file_handle ) == FALSE )
               {
                  WFCTRACEERROR( ::GetLastError() );
                  WFCTRACE( TEXT( "Couldn't close handle" ) );
               }

               delete parameters_p;
               parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );

               return( FALSE );
            }
         }
         catch( ... )
         {
         }
      }

      while( FindNextFile( parameters_p->find_file_handle, &parameters_p->find_data ) != FALSE )
      {
         if ( parameters_p->find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
         {
            if ( _tcscmp( parameters_p->find_data.cFileName, TEXT( "."  ) ) == 0 ||
                 _tcscmp( parameters_p->find_data.cFileName, TEXT( ".." ) ) == 0 )
            {
               // Do nothing, to do something would cause infinite recursion and that is a bad thing
            }
            else
            {
               parameters_p->new_directory_name  = parameters_p->directory_name_ending_in_a_slash;
               parameters_p->new_directory_name += parameters_p->find_data.cFileName;

               if ( __read_recursively( parameters_p->new_directory_name, action_to_take, action_parameter ) == FALSE )
               {
                  if ( FindClose( parameters_p->find_file_handle ) == FALSE )
                  {
                     WFCTRACEERROR( ::GetLastError() );
                     WFCTRACE( TEXT( "Couldn't close handle" ) );
                  }

                  delete parameters_p;
                  parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );

                  return( FALSE );
               }
            }
         }
         else
         {
            parameters_p->complete_filename  = parameters_p->directory_name_ending_in_a_slash;
            parameters_p->complete_filename += parameters_p->find_data.cFileName;

            try
            {
               if ( action_to_take( action_parameter, parameters_p->complete_filename ) == FALSE )
               {
                  if ( FindClose( parameters_p->find_file_handle ) == FALSE )
                  {
                     WFCTRACEERROR( ::GetLastError() );
                     WFCTRACE( TEXT( "Couldn't close handle" ) );
                  }

                  delete parameters_p;
                  parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );

                  return( FALSE );
               }
            }
            catch( ... )
            {
            }
         }
      }

      if ( FindClose( parameters_p->find_file_handle ) == FALSE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Couldn't close handle" ) );
      }

      parameters_p->find_file_handle = (HANDLE) INVALID_HANDLE_VALUE;
   }

   delete parameters_p;
   parameters_p = reinterpret_cast< RECURSIVE_DIRECTORY_READ_PARAMETERS * >( NULL );

   return( TRUE );
}

BOOL CFileDirectory::ReadRecursively( CStringArray& filenames )
{
   WFCLTRACEINIT( TEXT( "CFileDirectory::ReadRecursively( CStringArray )" ) );

   HANDLE file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

   WIN32_FIND_DATA find_data;

   ZeroMemory( &find_data, sizeof( find_data ) );

   file_find_handle = ::FindFirstFile( m_Name + TEXT( "*.*" ), &find_data );

   if ( file_find_handle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      CString complete_filename;
      CString new_directory_name;

      if ( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
      {
         if ( ::_tcscmp( find_data.cFileName, TEXT( "."  ) ) == 0 ||
              ::_tcscmp( find_data.cFileName, TEXT( ".." ) ) == 0 )
         {
            // Avoid infinite recursion here.
         }
         else
         {
            new_directory_name = m_Name;

            new_directory_name += find_data.cFileName;

            ::__read_recursively( new_directory_name, filenames );
         }
      }
      else
      {
         complete_filename  = m_Name;
         complete_filename += find_data.cFileName;

         filenames.Add( complete_filename );
      }

      while( ::FindNextFile( file_find_handle, &find_data ) != FALSE )
      {
         if ( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
         {
            if ( ::_tcscmp( find_data.cFileName, TEXT( "."  ) ) == 0 ||
                 ::_tcscmp( find_data.cFileName, TEXT( ".." ) ) == 0 )
            {
               // Avoid infinite recursion here.
            }
            else
            {
               new_directory_name = m_Name;

               new_directory_name += find_data.cFileName;

               ::__read_recursively( new_directory_name, filenames );
            }
         }
         else
         {
            complete_filename  = m_Name;
            complete_filename += find_data.cFileName;

            filenames.Add( complete_filename );
         }
      }

      if ( ::FindClose( file_find_handle ) == FALSE )
      {
         WFCTRACEERROR( ::GetLastError() );
         WFCTRACE( TEXT( "Couldn't close handle" ) );
      }

      file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

      return( TRUE );
   }

   return( FALSE );
}

BOOL CFileDirectory::ReadRecursively( FILE_ACTION_FUNCTION action_to_take, void * action_parameter )
{
   WFCLTRACEINIT( TEXT( "CFileDirectory::ReadRecursively( FILE_ACTION_FUNCTION )" ) );

   HANDLE file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

   WIN32_FIND_DATA find_data;

   ZeroMemory( &find_data, sizeof( find_data ) );

   file_find_handle = ::FindFirstFile( m_Name + TEXT( "*.*" ), &find_data );

   if ( file_find_handle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      CString complete_filename;
      CString new_directory_name;

      if ( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
      {
         if ( ::_tcscmp( find_data.cFileName, TEXT( "."  ) ) == 0 ||
              ::_tcscmp( find_data.cFileName, TEXT( ".." ) ) == 0 )
         {
            // Avoid infinite recursion here.
         }
         else
         {
            new_directory_name = m_Name;

            new_directory_name += find_data.cFileName;

            if ( ::__read_recursively( new_directory_name, action_to_take, action_parameter ) == FALSE )
            {
               if ( ::FindClose( file_find_handle ) == FALSE )
               {
                  WFCTRACEERROR( ::GetLastError() );
                  WFCTRACE( TEXT( "Couldn't close handle" ) );
               }

               file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

               return( TRUE );
            }
         }
      }
      else
      {
         complete_filename  = m_Name;
         complete_filename += find_data.cFileName;

         // We were passed pointers by the caller, don't trust them

         try
         {
            if ( action_to_take( action_parameter, complete_filename ) == FALSE )
            {
               if ( ::FindClose( file_find_handle ) == FALSE )
               {
                  WFCTRACEERROR( ::GetLastError() );
                  WFCTRACE( TEXT( "Couldn't close handle" ) );
               }

               file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

               return( TRUE );
            }
         }
         catch( ... )
         {
         }
      }

      while( ::FindNextFile( file_find_handle, &find_data ) != FALSE )
      {
         if ( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
         {
            if ( ::_tcscmp( find_data.cFileName, TEXT( "."  ) ) == 0 ||
                 ::_tcscmp( find_data.cFileName, TEXT( ".." ) ) == 0 )
            {
               // Avoid infinite recursion here.
            }
            else
            {
               new_directory_name = m_Name;

               new_directory_name += find_data.cFileName;

               if ( ::__read_recursively( new_directory_name, action_to_take, action_parameter ) == FALSE )
               {
                  if ( ::FindClose( file_find_handle ) == FALSE )
                  {
                     WFCTRACEERROR( ::GetLastError() );
                     WFCTRACE( TEXT( "Couldn't close handle" ) );
                  }

                  file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

                  return( TRUE );
               }
            }
         }
         else
         {
            complete_filename  = m_Name;
            complete_filename += find_data.cFileName;

            // We were passed a couple of pointers by the caller, don't trust them

            try
            {
               if ( action_to_take( action_parameter, complete_filename ) == FALSE )
               {
                  if ( ::FindClose( file_find_handle ) == FALSE )
                  {
                     WFCTRACEERROR( ::GetLastError() );
                     WFCTRACE( TEXT( "Couldn't close handle" ) );
                  }

                  file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

                  return( TRUE );
               }
            }
            catch( ... )
            {
            }
         }
      }

      if ( ::FindClose( file_find_handle ) == FALSE )
      {
         WFCTRACEERROR( ::GetLastError() );
         WFCTRACE( TEXT( "Couldn't close handle" ) );
      }

      file_find_handle = (HANDLE) INVALID_HANDLE_VALUE;

      return( TRUE );
   }

   return( FALSE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CFileDirectory</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The class that lets you search directories recursively or just get a list of files in a directory.">
</HEAD>

<BODY>

<H1>CFileDirectory</H1>

$Revision: 5 $
           
<HR>

<H2>Description</H2>

This class lets you get a list of filenames (complete path)
contianed in a directory. It will also recurse meaning it will
retrieve all filenames for the directory you want and any 
subdirectories too.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CFileDirectory</B>()</PRE><DD>
Constructs the object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
In staying with the file motif, we should be able
to close that which is opened.

<DT><PRE>BOOL <B>Open</B>( const CString&amp; directory_name )</PRE><DD>
Returns TRUE if <CODE>directory_name</CODE> is not empty.

<DT><PRE>BOOL <B>Read</B>( CStringArray&amp; filenames )</PRE><DD>
This method will fill <CODE>filenames</CODE> with the complete path to
the files in the directory specified in the <B>Open</B>() call.

<DT><PRE>BOOL <B>Read</B>( FILE_ACTION_FUNCTION action_to_take, void * action_parameter )</PRE><DD>
This method will call the <CODE>action_to_take</CODE> function with the
supplied <CODE>action_parameter</CODE> for every file in the directory
specified in the <B>Open</B>() call.
<CODE>action_to_take</CODE> will be passed a string containing the complete
path to the file.

<DT><PRE>BOOL <B>ReadRecursively</B>( CStringArray&amp; filenames )</PRE><DD>
This method will fill <CODE>filenames</CODE> with the complete path to
the files in the directory and all subdirectories of the directory
specified in the <B>Open</B>() call.

<DT><PRE>BOOL <B>ReadRecursively</B>( FILE_ACTION_FUNCTION action_to_take, void * action_parameter )</PRE><DD>
This method will call the <CODE>action_to_take</CODE> function with the
supplied <CODE>action_parameter</CODE> for every file in the directory
and all subdirectories of the directory specified in the <B>Open</B>() call.
<CODE>action_to_take</CODE> will be passed a string containing the complete
path to the file.

</DL>

<H2>Example</H2><PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

BOOL action_to_take( void * action_parameter, const CString& complete_filename )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;action_to_take()&quot; ) );

   DWORD * file_counter_p = reinterpret_cast&lt; DWORD * &gt;( action_parameter );

   (*file_counter_p)++; // increment the counter

   // Print the filename
   _tprintf( TEXT( &quot;%s\n&quot; ), (LPCTSTR) complete_filename );
}

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   int argument_index = 1;

   DWORD total_number_of_files = 0;

   <B>CFileDirectory</B> directory;

   while( argument_index &lt; number_of_command_line_arguments )
   {
      if ( directory.Open( command_line_arguments[ argument_index ] ) != FALSE )
      {
         directory.Read( action_to_take, &amp;total_number_of_files );
      }
   }

   _tprintf( &quot;Processed %lu files.\n&quot;, total_number_of_files );

   return( EXIT_SUCCESS );
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CFileDirectory.cpp $<BR>
$Modtime: 3/17/00 4:35p $
</BODY>
</HTML>
#endif
