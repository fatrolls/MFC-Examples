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
** $Workfile: CMemoryFile.cpp $
** $Revision: 10 $
** $Modtime: 3/17/00 4:35p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CMemoryFile::CMemoryFile()
{
   WFCLTRACEINIT( TEXT( "CMemoryFile::CMemoryFile()" ) );

   m_FileLength    = 0I64;
   m_Length        = 0;
   m_MappedLength  = 0;
   m_MappedPointer = NULL;
   m_Pointer       = NULL;
   Size            = 0;

   SYSTEM_INFO si;
   ::GetSystemInfo( &si );

   m_AllocationGranularity = si.dwAllocationGranularity;

   /*
   ** 1999-04-18
   ** Thanks go to Perry Rapp, (PRapp@itb.nawcsti.navy.mil) for 
   ** finding that I wasn't initializing all members here. DOH!
   */

   m_SecurityAttributes_p = (SECURITY_ATTRIBUTES *) NULL;
   m_SecurityDescriptor_p = (SECURITY_DESCRIPTOR *) NULL;
   m_MapHandle            = (HANDLE) INVALID_HANDLE_VALUE;
}

CMemoryFile::~CMemoryFile()
{
   WFCLTRACEINIT( TEXT( "CMemoryFile::~CMemoryFile()" ) );

   Close();

   m_Uninitialize();

   m_AllocationGranularity = 0;
   m_FileLength            = 0I64;
   m_Length                = 0;
   m_MapHandle             = (HANDLE) INVALID_HANDLE_VALUE;
   m_MappedLength          = 0;
   m_MappedPointer         = NULL;
   m_Pointer               = (void *) NULL;
   m_SecurityAttributes_p  = (SECURITY_ATTRIBUTES *) NULL;
   m_SecurityDescriptor_p  = (SECURITY_DESCRIPTOR *) NULL;
   Size                    = 0;
}

void CMemoryFile::Close( void )
{
   WFCLTRACEINIT( TEXT( "CMemoryFile::Close()" ) );

   if ( m_MappedPointer != NULL )
   {
      if ( ::UnmapViewOfFile( m_MappedPointer ) == FALSE )
      {
         WFCTRACEERROR( ::GetLastError() );
         WFCTRACE( TEXT( "UnmapViewOfFile() failed with the above error." ) );
      }

      m_MappedPointer = NULL;
      m_Pointer       = NULL;
   }

   if ( m_MapHandle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      if ( ::CloseHandle( m_MapHandle ) == FALSE )
      {
         WFCTRACEERROR( ::GetLastError() );
         WFCTRACE( TEXT( "CloseHandle() failed with the above error." ) );
      }

      m_MapHandle = (HANDLE) INVALID_HANDLE_VALUE;
   }

   m_Filename.Empty();
   m_FileLength   = 0I64;
   m_Length       = 0;
   m_MappedLength = 0;
   Size           = 0;
}

void CMemoryFile::GetFilename( CString& filename ) const
{
   WFCLTRACEINIT( TEXT( "CMemoryFile::GetFilename()" ) );

   filename = m_Filename;
}

BOOL CMemoryFile::Flush( void )
{
   WFCLTRACEINIT( TEXT( "CMemoryFile::Flush()" ) );

   if ( ::FlushViewOfFile( m_MappedPointer, m_MappedLength ) == 0 )
   {
      WFCTRACEERROR( ::GetLastError() );
      WFCTRACE( TEXT( "FlushViewOfFile() failed for the above reason." ) );
      return( FALSE );
   }

   return( TRUE );
}

void CMemoryFile::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CMemoryFile::m_Initialize()" ) );

   ASSERT( m_SecurityAttributes_p == NULL );
   ASSERT( m_SecurityDescriptor_p == NULL );
   ASSERT( m_MapHandle            == (HANDLE) INVALID_HANDLE_VALUE );

   try
   {
      m_SecurityAttributes_p = new SECURITY_ATTRIBUTES;
   }
   catch( ... )
   {
      m_SecurityAttributes_p = NULL;
   }

   if ( m_SecurityAttributes_p == NULL )
   {
      return;
   }

   try
   {
      m_SecurityDescriptor_p = new SECURITY_DESCRIPTOR;
   }
   catch( ... )
   {
      m_SecurityDescriptor_p = NULL;
   }

   if ( m_SecurityDescriptor_p == NULL )
   {
      delete m_SecurityAttributes_p;
      m_SecurityAttributes_p = NULL;

      return;
   }

   if ( ::InitializeSecurityDescriptor( m_SecurityDescriptor_p, SECURITY_DESCRIPTOR_REVISION ) == FALSE )
   {
      WFCTRACEERROR( ::GetLastError() );
      WFCTRACE( TEXT( "InitializeSecurityDescriptor() failed with the above error." ) );

      delete m_SecurityAttributes_p;
      m_SecurityAttributes_p = NULL;

      delete m_SecurityDescriptor_p;
      m_SecurityDescriptor_p = NULL;

      return;
   }

   if ( ::SetSecurityDescriptorDacl( m_SecurityDescriptor_p, TRUE, NULL, FALSE ) == FALSE )
   {
      WFCTRACEERROR( ::GetLastError() );
      WFCTRACE( TEXT( "SetSecurityDescriptorDacl() failed with the above error." ) );

      delete m_SecurityAttributes_p;
      m_SecurityAttributes_p = NULL;

      delete m_SecurityDescriptor_p;
      m_SecurityDescriptor_p = NULL;

      return;
   }

   m_SecurityAttributes_p->nLength              = sizeof( SECURITY_ATTRIBUTES );
   m_SecurityAttributes_p->lpSecurityDescriptor = m_SecurityDescriptor_p;
   m_SecurityAttributes_p->bInheritHandle       = TRUE;
}

void CMemoryFile::m_Uninitialize( void )
{
   WFCLTRACEINIT( TEXT( "CMemoryFile::m_Uninitialize()" ) );

   if ( m_SecurityAttributes_p != NULL )
   {
      delete m_SecurityAttributes_p;
      m_SecurityAttributes_p = NULL;
   }

   if ( m_SecurityDescriptor_p != NULL )
   {
      delete m_SecurityDescriptor_p;
      m_SecurityDescriptor_p = NULL;
   }
}

BOOL CMemoryFile::Open( LPCTSTR filename, UINT open_flags, ULONGLONG beginning_at_offset, DWORD number_of_bytes_to_map, void * desired_address )
{
   WFCLTRACEINIT( TEXT( "CMemoryFile::Open()" ) );

   if ( m_Pointer != NULL )
   {
      Close();
   }

   if ( filename == NULL )
   {
      return( FALSE );
   }

   CFile file;

   if ( file.Open( filename, open_flags ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open file" ) );
      return( FALSE );
   }

   DWORD protections = PAGE_READWRITE;
   DWORD access_mode = FILE_MAP_WRITE;

   if ( open_flags == CFile::modeRead )
   {
      WFCTRACE( TEXT( "User wants read-only access." ) );
      protections = PAGE_READONLY;
      access_mode = FILE_MAP_READ;
   }

   if ( ( open_flags & CFile::modeWrite ) || ( open_flags & CFile::modeReadWrite ) )
   {
      WFCTRACE( TEXT( "User wants Read/Write access." ) );
      protections = PAGE_READWRITE;
      access_mode = FILE_MAP_WRITE;
   }

   // Let's adjust number_of_bytes_to_map if we're using an offset

   ULARGE_INTEGER file_length;

   file_length.QuadPart = 0I64;

   file_length.LowPart = ::GetFileSize( (HANDLE) file.m_hFile, &file_length.HighPart );

   if ( file_length.LowPart == 0xFFFFFFFF && ( ::GetLastError() != NO_ERROR ) )
   {
      WFCTRACEERROR( ::GetLastError() );
      WFCTRACE( TEXT( "Can't get file size because of above error." ) );
      return( FALSE );
   }

   m_FileLength = file_length.QuadPart;

   if ( beginning_at_offset > 0I64 )
   {
      if ( beginning_at_offset > m_FileLength )
      {
         WFCTRACE( TEXT( "You want to start mapping a file after the end of the file." ) );
         return( FALSE );
      }

      if ( number_of_bytes_to_map == 0 )
      {
         // user has specified default length, since the user also
         // specified an offset, we need to compute how many bytes
         // are really gonna be mapped.

         if ( ( m_FileLength - beginning_at_offset ) > 0xFFFFFFFF )
         {
            number_of_bytes_to_map = 0xFFFFFFFF;
         }
         else
         {
            number_of_bytes_to_map = static_cast< DWORD >( m_FileLength - beginning_at_offset );
         }
      }
   }
   else
   {
      if ( number_of_bytes_to_map == 0 )
      {
         if ( m_FileLength > 0xFFFFFFFF )
         {
            number_of_bytes_to_map = 0xFFFFFFFF;
         }
         else
         {
            number_of_bytes_to_map = static_cast< DWORD >( m_FileLength );
         }
      }
   }

   m_MapHandle = ::CreateFileMapping( (HANDLE) file.m_hFile,
                                      m_SecurityAttributes_p,
                                      protections,
                                      0, // Microsoft isn't very clear about these parameters, always use zero
                                      0, // Microsoft isn't very clear about these parameters, always use zero
                                      NULL );

   if ( m_MapHandle == NULL )
   {
      WFCTRACEERROR( ::GetLastError() );
      WFCTRACE( TEXT( "CreateFileMapping() failed with the above error." ) );

      m_MapHandle = (HANDLE) INVALID_HANDLE_VALUE;
      return( FALSE );
   }

   ULARGE_INTEGER large_file_offset;

   large_file_offset.QuadPart = beginning_at_offset;

   if ( ( large_file_offset.QuadPart % m_AllocationGranularity ) != 0 )
   {
      // The user wants to start mapping at a point in the file that doesn't fall
      // on a memory allocation boundary (usually a 64KB boundary). That means we
      // must do some creative programming to give the user what they asked for.

      large_file_offset.QuadPart -= ( large_file_offset.QuadPart % m_AllocationGranularity );
   }

   m_MappedLength = number_of_bytes_to_map + static_cast< DWORD >( beginning_at_offset - large_file_offset.QuadPart );

   m_MappedPointer = ::MapViewOfFileEx( m_MapHandle, 
                                        access_mode,
                                        large_file_offset.HighPart,
                                        large_file_offset.LowPart,
                                        m_MappedLength,
                                        desired_address );

   if ( m_MappedPointer == NULL )
   {
      WFCTRACEERROR( ::GetLastError() );
      WFCTRACE( TEXT( "MapViewOfFileEx() failed with the above error." ) );

      if ( ::CloseHandle( m_MapHandle ) == FALSE )
      {
         WFCTRACEERROR( ::GetLastError() );
         WFCTRACE( TEXT( "CloseHandle() failed with the aboce error." ) );
      }

      m_MapHandle = (HANDLE) INVALID_HANDLE_VALUE;

      Close();

      return( FALSE );
   }

   m_Filename = filename;
   m_Length   = number_of_bytes_to_map;
   Size       = number_of_bytes_to_map;

   char * temp_pointer = (char *) m_MappedPointer;

   m_Pointer = &temp_pointer[ m_MappedLength - number_of_bytes_to_map ];

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CMemoryFile</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, memory mapped files, mmap, source code">
<META name="description" content="A simple C++ class that handles memory mapped files.">
</HEAD>

<BODY>

<H1>CMemoryFile</H1>

$Revision: 10 $
<HR>

<H2>Description</H2>

This class makes memory mapped files easy to use.
Memory mapped files are great when you have to access the
contents of a file directly. Instead of declaring a big
buffer (at least the size of the file) then reading the
file into that buffer, mapping the file contents to a pointer
is much faster.

<BR>

Mapping a file to a pointer lets you dereference the pointer
as needed and let the operating system handle the retrieval
of the bytes from the file. Very cool.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CMemoryFile</B>()</PRE><DD>
Constructs the object.

</DL>

<H2>Data Members</H2>

<DL COMPACT>

<DT><PRE>DWORD <B><A NAME="Size">Size</A></B></PRE><DD>
Holds the same value as <B>GetLength</B>(). This member
is exposed for speed only. It is not used internally by
the class.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B><A NAME="Close">Close</A></B>( void )</PRE><DD>
Closes the file.

<DT><PRE>BOOL <B><A NAME="Flush">Flush</A></B>( void )</PRE><DD>
Synchronizes the contents of memory with the contents
of the physical disk file.

<DT><PRE>ULONGLONG <B>GetFileLength</B>( void ) const</PRE><DD>
Returns the length of the <B>Open()</B>'d file.
Yes, this returns a 64-bit length.

<DT><PRE>void <B><A NAME="GetFilename">GetFilename</A></B>( CString&amp; filename ) const</PRE><DD>
Retrieves the name of the file that is mapped. If <CODE>filename</CODE>
is empty, no file has been opened.

<DT><PRE>DWORD <B><A NAME="GetLength">GetLength</A></B>( void ) const</PRE><DD>
Returns the number of bytes that were mapped.

<DT><PRE>void * <B><A NAME="GetPointer">GetPointer</A></B>( void ) const</PRE><DD>
Returns the pointer to the mapped bytes. If this method
returns NULL, it means there is no file mapped.

<DT><PRE>BOOL <B><A NAME="Open">Open</A></B>( LPCTSTR filename,
          UINT open_flags = CFile::modeRead,
          DWORD beginning_at = 0,
          DWORD number_of_bytes_to_map,
          void * desired_address = NULL )
BOOL <B>Open</B>( LPCTSTR filename,
          UINT open_flags = CFile::modeRead,
          ULONGLONG beginning_at = 0,
          DWORD number_of_bytes_to_map,
          void * desired_address = NULL )          </PRE><DD>
This method is patterend after the <B>Open</B>() method in the
<A HREF="http://www.stingsoft.com/mfc_faq/">MFC</A>
CFile class. In it's simplest form, you pass a name of a file
and it will open that file in read only mode. This is great
for parsing data files.

You don't have to worry about the <CODE>beginning_at</CODE> value
be a special value (like in the call to the <CODE>MapViewOfFile()</CODE>
API).

The other parameters have these meanings:

<UL>

<LI><CODE><B>open_flags</B></CODE> - May be one of the following values:
<UL>
<LI><CODE><B>CFile::modeRead</B></CODE> - Open the file for read only
<LI><CODE><B>CFile::modeWrite</B></CODE> - Open the file for read/write
<LI><CODE><B>CFile::modeReadWrite</B></CODE> - Open the file for read/write
</UL>

<LI><CODE><B>beginning_at</B></CODE> - The offset into the file of
where to start mapping.

<LI><CODE><B>number_of_bytes_to_map</B></CODE> - The number of bytes
to map. If this parameter is zero, the default is to compute
the number of bytes that were mapped. You can call <B>GetLength</B>()
to find out how many bytes were mapped.

<LI><CODE><B>desired_address</B></CODE> - This is where you ask
nicely that the address returned by <B>GetPointer</B>() be this
value. Win32 may or may not be able to map the bytes in the file
to <CODE>desired_address</CODE>. Never count on <CODE>desired_address</CODE>
actually being used.

</UL>

</DL>

<H2>Example</H2><PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

void test_CMemoryFile( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CMemoryFile()&quot; ) );

   <B>CMemoryFile</B> memory_mapped_file;

   BYTE * pointer = NULL;

   if ( memory_mapped_file.Open( TEXT( &quot;datafile.dat&quot; ) ) == FALSE )
   {
      return;
   }

   pointer = (BYTE *) memory_mapped_file.GetPointer();

   _tprintf( TEXT( &quot;The last byte of the file is %X\n&quot; ),
             pointer[ mempory_mapped_file.GetLength() - 1 ] );
}</CODE></PRE>

<H2>API&#39;s Used</H2>

<UL>
<LI>CloseHandle
<LI>CreateFileMapping
<LI>FlushViewOfFile
<LI>GetFileSize
<LI>GetLastError
<LI>GetSystemInfo
<LI>InitializeSecurityDescriptor
<LI>MapViewOfFileEx
<LI>SetSecurityDescriptorDacl
<LI>UnmapViewOfFile
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CMemoryFile.cpp $<BR>
$Modtime: 3/17/00 4:35p $

</BODY>

</HTML>
#endif
