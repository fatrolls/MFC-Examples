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
** $Workfile: CPhysicalDiskFile.cpp $
** $Revision: 8 $
** $Modtime: 1/17/00 9:09a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CPhysicalDiskFile::CPhysicalDiskFile()
{
   WFCLTRACEINIT( TEXT( "CPhysicalDiskFile::CPhysicalDiskFile()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_Buffer       = reinterpret_cast< BYTE * >( NULL );
   m_BufferSize   = 0;
   m_BufferOffset = 0;

   ZeroMemory( &m_DiskGeometry, sizeof( m_DiskGeometry ) );
}

CPhysicalDiskFile::~CPhysicalDiskFile()
{
   WFCLTRACEINIT( TEXT( "CPhysicalDiskFile::~CPhysicalDiskFile()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   Close();

   if ( m_Buffer != NULL )
   {
      try
      {
         delete [] m_Buffer;
      }
      catch( ... )
      {
         // Do Nothing
      }
   }

   m_Buffer       = reinterpret_cast< BYTE * >( NULL );
   m_BufferSize   = 0;
   m_BufferOffset = 0;

   ZeroMemory( &m_DiskGeometry, sizeof( m_DiskGeometry ) );
}

void CPhysicalDiskFile::Close( void )
{
   WFCLTRACEINIT( TEXT( "CPhysicalDiskFile::Close()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   CFile::Close();

   if ( m_Buffer != NULL )
   {
      try
      {
         delete [] m_Buffer;
      }
      catch( ... )
      {
         // Do Nothing
      }
   }

   m_Buffer       = reinterpret_cast< BYTE * >( NULL );
   m_BufferSize   = 0;
   m_BufferOffset = 0;

   ZeroMemory( &m_DiskGeometry, sizeof( m_DiskGeometry ) );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CPhysicalDiskFile::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CPhysicalDiskFile at " ) << (VOID *) this << TEXT( "\n{\n" );

   CFile::Dump( dump_context );

   dump_context << "   m_DiskGeometry.MediaType is ";

   // These are taken from WINIOCTL.H

   switch( m_DiskGeometry.MediaType )
   {
      case Unknown:

         dump_context << TEXT( "Unknown (Format is Unknown)\n" );
         break;

      case F5_1Pt2_512:

         dump_context << TEXT( "F5_1Pt2_512 (5.25\", 1.2MB,  512 bytes per sector)\n" );
         break;

      case F3_1Pt44_512:

         dump_context << TEXT( "F3_1Pt44_512 (3.5\",  1.44MB, 512 bytes per sector)\n" );
         break;

      case F3_2Pt88_512:

         dump_context << TEXT( "F3_2Pt88_512 (3.5\",  2.88MB, 512 bytes per sector )\n" );
         break;

      case F3_20Pt8_512:

         dump_context << TEXT( "F3_20Pt8_512 (3.5\",  20.8MB, 512 bytes per sector)\n" );
         break;

      case F3_720_512:

         dump_context << TEXT( "F3_720_512 (3.5\",  720KB,  512 bytes per sector)\n" );
         break;

      case F5_360_512:

         dump_context << TEXT( "F5_360_512 (5.25\", 360KB,  512 bytes per sector)\n" );
         break;

      case F5_320_512:

         dump_context << TEXT( "F5_320_512 (5.25\", 320KB,  512 bytes/sector)\n" );
         break;

      case F5_320_1024:

         dump_context << TEXT( "F5_320_1024 (5.25\", 320KB,  1024 bytes/sector)\n" );
         break;

      case F5_180_512:

         dump_context << TEXT( "F5_180_512 (5.25\", 180KB,  512 bytes per sector)\n" );
         break;

      case F5_160_512:

         dump_context << TEXT( "F5_160_512 (5.25\", 160KB,  512 bytes/sector)\n" );
         break;

      case RemovableMedia:

         dump_context << TEXT( "RemovableMedia (Removable media other than floppy)\n" );
         break;

      case FixedMedia:

         dump_context << TEXT( "FixedMedia (Fixed hard disk media)\n" );
         break;

      case F3_120M_512:

         dump_context << TEXT( "F3_120M_512 (3.5\", 120M Floppy)\n" );
         break;

      default:

         dump_context << TEXT( "Undocumented format has a value of " ) << m_DiskGeometry.MediaType << TEXT( "\n" );
         break;
   }
}

#endif // _DEBUG

DWORD CPhysicalDiskFile::GetLength( void ) const
{
   __int64 total_number_of_bytes = 0;

   total_number_of_bytes  = (__int64) ( (__int64) m_DiskGeometry.BytesPerSector * (__int64) m_DiskGeometry.SectorsPerTrack );
   total_number_of_bytes *= (__int64) m_DiskGeometry.TracksPerCylinder;
   total_number_of_bytes *= (__int64) m_DiskGeometry.Cylinders.QuadPart;

   if ( total_number_of_bytes > 0xFFFFFFFF )
   {
      return( 0xFFFFFFFF );
   }

   return( (DWORD) total_number_of_bytes );
}

DWORD CPhysicalDiskFile::GetMediaType( void ) const
{
   return( m_DiskGeometry.MediaType );
}

BOOL CPhysicalDiskFile::GetSectorSize( DWORD& number_of_bytes_per_sector ) const
{
   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      number_of_bytes_per_sector = 0;
      return( FALSE );
   }
   else
   {
      number_of_bytes_per_sector = m_DiskGeometry.BytesPerSector;
      return( TRUE );
   }
}

BOOL CPhysicalDiskFile::m_SetSectorSize( void )
{
   WFCLTRACEINIT( TEXT( "CPhysicalDiskFile::Close()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      WFCTRACE( TEXT( "m_hFile is bad. Call Open() first." ) );
      return( FALSE );
   }

   ZeroMemory( &m_DiskGeometry, sizeof( m_DiskGeometry ) );

   DWORD number_of_bytes_read = 0;

   if ( ::DeviceIoControl( reinterpret_cast< HANDLE >( m_hFile ),
                           IOCTL_DISK_GET_DRIVE_GEOMETRY,
                           NULL,
                           0,
                          &m_DiskGeometry,
                           sizeof( m_DiskGeometry ),
                          &number_of_bytes_read,
                           NULL ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't get disk geometry." ) );
      WFCTRACEERROR( ::GetLastError() );

      Close();

      return( FALSE );
   }

   // We must read and write on sector boundaries

   ASSERT( m_DiskGeometry.BytesPerSector != 0 );

   if ( m_DiskGeometry.BytesPerSector == 0 )
   {
      WFCTRACE( TEXT( "Something is really screwed up." ) );
      Close();
      return( FALSE );
   }

   m_BufferSize  = ( 2 * 1024 * 1024 ); // Two Megabytes
   m_BufferSize += m_DiskGeometry.BytesPerSector; // This makes sure we have a two meg buffer

   ASSERT( m_Buffer == NULL );

   try
   {
      m_Buffer = new BYTE[ m_BufferSize ];
   }
   catch( ... )
   {
      m_Buffer = reinterpret_cast< BYTE * >( NULL );
   }

   if ( m_Buffer == NULL )
   {
      WFCTRACEVAL( TEXT( "Can't allocate a buffer of this size " ), m_BufferSize );
      WFCTRACEERROR( ::GetLastError() );

      Close();

      return( FALSE );
   }

   // Now we need to see if the address of the buffer sits on a sector boundary

   m_BufferOffset = 0;

   // This will probably break when we go to a 64-bit memory address space

   while( ( reinterpret_cast< DWORD >( &m_Buffer[ m_BufferOffset ] ) % m_DiskGeometry.BytesPerSector ) != 0 )
   {
      m_BufferOffset++;
   }

   WFCTRACEVAL( TEXT( "Wasted this many bytes on alignment " ), m_BufferOffset );

   return( TRUE );
}

#if ! defined( WFC_STL )
BOOL CPhysicalDiskFile::Open( LPCTSTR drive_letter, UINT, CFileException * )
#else // WFC_STL
BOOL CPhysicalDiskFile::Open( LPCTSTR drive_letter, UINT )
#endif // WFC_STL
{
   WFCLTRACEINIT( TEXT( "CPhysicalDiskFile::Open( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   ASSERT( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   if ( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      Close();
   }

   CString filename;

   // We were passed a pointer, don't trust it

   try
   {
      filename.Format( TEXT( "\\\\.\\%c:" ), drive_letter[ 0 ] );

      WFCTRACEVAL( TEXT( "Opening " ), filename );

      m_hFile = reinterpret_cast< UINT >( ::CreateFile( filename,
                                     GENERIC_READ | GENERIC_WRITE,
                                     0,
                                     reinterpret_cast< LPSECURITY_ATTRIBUTES >( NULL ),
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING,
                                     reinterpret_cast< HANDLE >( NULL ) ) );

      if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
      {
         WFCTRACEVAL( TEXT( "Can't open " ), filename );
         WFCTRACEERROR( ::GetLastError() );

         // Clean up any memory allocations and return to a known state

         Close();

         return( FALSE );
      }

      if ( m_SetSectorSize() == FALSE )
      {
         return( FALSE );
      }

      return( TRUE );
   }
   catch( ... )
   {
   }

   return( FALSE );
}

#if ! defined( WFC_STL )
BOOL CPhysicalDiskFile::Open( int physical_disk_number, UINT, CFileException * )
#else // WFC_STL
BOOL CPhysicalDiskFile::Open( int physical_disk_number, UINT )
#endif // WFC_STL
{
   WFCLTRACEINIT( TEXT( "CPhysicalDiskFile::Open( int )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   ASSERT( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   if ( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      Close();
   }

   CString filename;

   filename.Format( TEXT( "\\\\.\\PhysicalDisk%d:" ), physical_disk_number );

   WFCTRACEVAL( TEXT( "Opening " ), filename );

   m_hFile = reinterpret_cast< UINT >( ::CreateFile( filename,
                                  GENERIC_READ | GENERIC_WRITE,
                                  0,
                                  reinterpret_cast< LPSECURITY_ATTRIBUTES >( NULL ),
                                  OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING,
                                  reinterpret_cast< HANDLE >( NULL ) ) );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      WFCTRACEVAL( TEXT( "Can't open " ), filename );
      WFCTRACEERROR( ::GetLastError() );

      // Clean up any memory allocations and return to a known state

      Close();

      return( FALSE );
   }

   if ( m_SetSectorSize() == FALSE )
   {
      return( FALSE );
   }

   return( TRUE );
}

UINT CPhysicalDiskFile::Read( void * buffer, UINT count )
{
   WFCLTRACEINIT( TEXT( "CPhysicalDiskFile::Open( int )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );
   ASSERT( m_Buffer != NULL );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      return( 0 );
   }

   // We were passed a pointer, don't trust it

   UINT number_of_bytes_actually_read = 0;

   try
   {
      if ( count > ( m_BufferSize - m_BufferOffset ) )
      {
         count = m_BufferSize - m_BufferOffset;
      }

      number_of_bytes_actually_read = CFile::Read( &m_Buffer[ m_BufferOffset ], count );

      ASSERT( number_of_bytes_actually_read == count );

      CopyMemory( buffer, &m_Buffer[ m_BufferOffset ], number_of_bytes_actually_read );

      return( number_of_bytes_actually_read );
   }
   catch( ... )
   {
      return( 0 );
   }
}

void CPhysicalDiskFile::SetLength( DWORD )
{
   ASSERT( FALSE ); // Unsupported function
}

void CPhysicalDiskFile::Write( void * buffer, UINT count )
{
   WFCLTRACEINIT( TEXT( "CPhysicalDiskFile::Open( int )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );
   ASSERT( m_Buffer != NULL );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      WFCTRACE( TEXT( "You must first call Open()!" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   UINT number_of_bytes_to_write = 0;
   UINT number_of_bytes_written  = 0;

   try
   {
      while( number_of_bytes_written < count )
      {
         number_of_bytes_to_write = count - number_of_bytes_written;

         if ( number_of_bytes_to_write > ( m_BufferSize - m_BufferOffset ) )
         {
            number_of_bytes_to_write = m_BufferSize - m_BufferOffset;
         }

         CopyMemory( &m_Buffer[ m_BufferOffset ], buffer, number_of_bytes_to_write );
         CFile::Write( &m_Buffer[ m_BufferOffset ], number_of_bytes_to_write );

         number_of_bytes_written += number_of_bytes_to_write;
      }
   }
   catch( ... )
   {
      // Do Nothing
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CPhysicalDiskFile</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that intercepts calls to CFile that would blow up when your derived class isn't playing with data on a disk.">
</HEAD>

<BODY>

<H1>CPhysicalDiskFile : CFile</H1>

$Revision: 8 $<BR>

<HR>

<H2>Description</H2>
This class makes it easy to read physical sectors on a disk.

<H2>Data Members</H2>

None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>Closes the disk.

<DT><PRE>DWORD <B>GetLength</B>( void ) const</PRE><DD>
Returns the total number of bytes in the disk. If (and this is
quite likely) your disk contains more that 4GB, <B>GetLength</B>()
will return 4GB. 4GB is the maximum value of a DWORD.

<DT><PRE>DWORD <B>GetMediaType</B>( void ) const</PRE><DD>
Returns the type of media that has been opened.

<DT><PRE>BOOL <B>GetSectorSize</B>( DWORD&amp; number_of_bytes_per_sector ) const</PRE><DD>
Return TRUE if the disk has been <B>Open</B>()'d or FALSE if <B>Open</B>()
has not yet been called. It will fill <CODE>number_of_bytes_per_sector</CODE>
with the number of bytes per sector on the disk on success.

<DT><PRE>BOOL <B>Open</B>( LPCTSTR drive_letter, UINT open_flags, CFileException * error = NULL )
BOOL <B>Open</B>( int physical_disk_number, UINT open_flags, CFileException * error = NULL )</PRE><DD>
Opens the disk. The <CODE>open_flags</CODE> and <CODE>error</CODE>
parameters are ignored.

<DT><PRE>UINT <B>Read</B>( void * buffer, UINT number_of_bytes_to_read )</PRE><DD>
Reads data from the disk. The class takes care of all that memory
boundary on a page size stuff.

<DT><PRE>void <B>SetLength</B>( DWORD length )</PRE><DD>
This function is intercepted. In other words, it does nothing.

<DT><PRE>void <B>Write</B>( void * buffer, UINT number_of_bytes_to_write )</PRE><DD>
Writes data to the disk.

</DL>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

BOOL copy_diskette_to_file( CFile&amp; file )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;copy_diskette_to_file()&quot; ) );

   <B>CPhysicalDiskFile</B> disk;

   if ( disk.Open( &quot;A:&quot;, 0 ) == FALSE )
   {
      return( FALSE );
   }

   CByteArray disk_contents;

   DWORD length = disk.GetLength();

   disk_contents.SetSize( length );

   disk.Read( disk_contents.GetBuffer(), disk_contents.GetSize() );

   // disk_contents now contains all sectors on the diskette

   file.Write( disk_contents.GetBuffer(), disk_contents.GetSize() );

   return( TRUE );
}

void get_sector( TCHAR drive_letter, DWORD sector_number, CByteArray&amp; sector_contents )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;get_sector()&quot; ) );

   sector_contents.Empty();

   TCHAR filename[ 3 ];

   filename[ 0 ] = drive_letter;
   filename[ 1 ] = TEXT( ':' );
   filename[ 2 ] = 0x00;

   <B>CPhysicalDiskFile</B> disk;

   if ( disk.Open( filename, 0 ) == FALSE )
   {
      return;
   }

   DWORD sector_size = 0;

   disk.GetSectorSize( sector_size );

   DWORD location_to_seek_to = sector_size * sector_number;

   if ( ( location_to_seek_to + sector_size ) &gt; disk.GetLength() )
   {
      return;
   }

   disk.Seek( location_to_seek_to, CFile::begin );

   sector_contents.SetSize( sector_size );

   disk.Read( sector_contents.GetData(), sector_size );
}</CODE></PRE>

<H2>API's Used</H2>

<B>CNetworkUsers</B> uses the following API's:

<UL>
<LI>CreateFile
<LI>DeviceIoControl
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CPhysicalDiskFile.cpp $<BR>
$Modtime: 1/17/00 9:09a $
</BODY>

</HTML>
#endif
