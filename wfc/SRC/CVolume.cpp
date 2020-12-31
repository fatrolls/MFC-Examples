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
** $Workfile: CVolume.cpp $
** $Revision: 6 $
** $Modtime: 3/17/00 4:38p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

// This is a C++ class based on the Microsoft Knowledge Base article Q165721

CVolume::CVolume()
{
   WFCLTRACEINIT( TEXT( "CVolume::CVolume()" ) );
   m_Handle      = (HANDLE) INVALID_HANDLE_VALUE;
   m_DriveLetter = 0;
   m_DriveType   = DRIVE_UNKNOWN;
}

CVolume::~CVolume()
{
   WFCLTRACEINIT( TEXT( "CVolume::~CVolume()" ) );
   Close();
}

BOOL CVolume::AutomaticallyEject( void )
{
   WFCLTRACEINIT( TEXT( "CVolume::AutomaticallyEject()" ) );

   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      WFCTRACE( TEXT( "You must first call Open()." ) );
      return( FALSE );
   }

   DWORD number_of_bytes_returned = 0;

   BOOL return_value = FALSE;

   return_value = ::DeviceIoControl( m_Handle,
                                     IOCTL_STORAGE_EJECT_MEDIA,
                                     NULL,
                                     0,
                                     NULL,
                                     0,
                                    &number_of_bytes_returned,
                                     NULL );

   return( return_value );
}

BOOL CVolume::Close( void )
{
   WFCLTRACEINIT( TEXT( "CVolume::Close()" ) );

   m_Name.Empty();
   m_DriveLetter = 0;
   m_DriveType   = DRIVE_UNKNOWN;

   if ( m_Handle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      ::wfc_close_handle( m_Handle );
   }

   m_Handle = (HANDLE) INVALID_HANDLE_VALUE;

   return( TRUE );
}

BOOL CVolume::Dismount( void )
{
   WFCLTRACEINIT( TEXT( "CVolume::Dismount()" ) );

   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      WFCTRACE( TEXT( "You must first call Open()." ) );
      return( FALSE );
   }

   DWORD number_of_bytes_returned = 0;

   BOOL return_value = FALSE;

   return_value = ::DeviceIoControl( m_Handle,
                                     FSCTL_DISMOUNT_VOLUME,
                                     NULL,
                                     0,
                                     NULL,
                                     0,
                                    &number_of_bytes_returned,
                                     NULL );

   return( return_value );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CVolume::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CVolume at " ) << (VOID *) this << TEXT( "\n{\n" );

   dump_context << TEXT( "   m_Handle is " );

   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      dump_context << TEXT( "INVALID_HANDLE_VALUE\n" );
   }
   else
   {
      dump_context << m_Handle << TEXT( "\n" );
   }

   dump_context << TEXT( "   m_DriveType is " );

   switch( m_DriveType )
   {
      case DRIVE_UNKNOWN:

         dump_context << TEXT( "DRIVE_UNKNOWN\n" );
         break;

      case DRIVE_NO_ROOT_DIR:

         dump_context << TEXT( "DRIVE_NO_ROOT_DIR\n" );
         break;

      case DRIVE_REMOVABLE:

         dump_context << TEXT( "DRIVE_REMOVABLE\n" );
         break;

      case DRIVE_FIXED:

         dump_context << TEXT( "DRIVE_FIXED\n" );
         break;

      case DRIVE_REMOTE:

         dump_context << TEXT( "DRIVE_REMOTE\n" );
         break;

      case DRIVE_CDROM:

         dump_context << TEXT( "DRIVE_CDROM\n" );
         break;

      case DRIVE_RAMDISK:

         dump_context << TEXT( "DRIVE_RAMDISK\n" );
         break;

      default:

         dump_context << TEXT( "unknown( " ) << m_DriveType << TEXT( ")\n" );
   }

   dump_context << TEXT( "   m_Name is " ) << m_Name << TEXT( "\n" );
   dump_context << TEXT( "   m_DriveLetter is " ) << m_DriveLetter << TEXT( "\n" );

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

BOOL CVolume::Eject( void )
{
   WFCLTRACEINIT( TEXT( "CVolume::Eject()" ) );

   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      WFCTRACE( TEXT( "You must first call Open()." ) );
      return( FALSE );
   }

   if ( Lock() == FALSE )
   {
      WFCTRACE( TEXT( "Can't lock volume." ) );
      WFCTRACEERROR( ::GetLastError() );
      return( FALSE );
   }

   if ( Dismount() == FALSE )
   {
      WFCTRACE( TEXT( "Can't dismount volume." ) );
      WFCTRACEERROR( ::GetLastError() );
      return( FALSE );
   }

   if ( PreventRemoval( FALSE ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't not prevent removal of volume." ) );
      WFCTRACEERROR( ::GetLastError() );
      return( FALSE );
   }

   if ( AutomaticallyEject() == FALSE )
   {
      WFCTRACE( TEXT( "Can't eject volume." ) );
      WFCTRACEERROR( ::GetLastError() );
      return( FALSE );
   }

   WFCTRACE( TEXT( "Ejected OK." ) );

   return( TRUE );
}

HANDLE CVolume::GetHandle( void ) const
{
   return( m_Handle );
}

BOOL CVolume::GetType( UINT& drive_type )
{
   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      drive_type = DRIVE_UNKNOWN;
      return( FALSE );
   }

   drive_type = m_DriveType;

   return( TRUE );
}

BOOL CVolume::Load( void )
{
   WFCLTRACEINIT( TEXT( "CVolume::Load()" ) );

   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      WFCTRACE( TEXT( "You must first call Open()." ) );
      return( FALSE );
   }

   DWORD number_of_bytes_returned = 0;

   BOOL return_value = FALSE;

   return_value = ::DeviceIoControl( m_Handle,
                                     IOCTL_STORAGE_LOAD_MEDIA,
                                     NULL,
                                     0,
                                     NULL,
                                     0,
                                    &number_of_bytes_returned,
                                     NULL );

   return( return_value );
}

BOOL CVolume::Lock( void )
{
   WFCLTRACEINIT( TEXT( "CVolume::Lock()" ) );

   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      WFCTRACE( TEXT( "You must first call Open()." ) );
      return( FALSE );
   }

   DWORD number_of_bytes_returned = 0;
   DWORD sleep_time               = 0;
   DWORD number_of_tries          = 0;

   sleep_time = 10000 / 20; // Try 20 times in 10 seconds

   while( number_of_tries < 20 )
   {
      if ( ::DeviceIoControl( m_Handle,
                              FSCTL_LOCK_VOLUME,
                              NULL,
                              0,
                              NULL,
                              0,
                             &number_of_bytes_returned,
                              NULL ) != FALSE )
      {
         return( TRUE );
      }

      ::Sleep( sleep_time );

      number_of_tries++;
   }

   return( FALSE );
}

BOOL CVolume::Open( TCHAR drive_letter )
{
   WFCLTRACEINIT( TEXT( "CVolume::Open()" ) );

   if ( m_Handle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      Close();
   }

   CString root_directory;

   root_directory.Format( TEXT( "%c:\\" ), drive_letter );

   m_DriveType = ::GetDriveType( root_directory );

   DWORD access_flags = 0;

   switch( m_DriveType )
   {
      default:
      case DRIVE_REMOVABLE:

         access_flags = GENERIC_READ | GENERIC_WRITE;
         break;

      case DRIVE_CDROM:

         access_flags = GENERIC_READ;
         break;
   }

   m_Name.Format( TEXT( "\\\\.\\%c:" ), drive_letter );
   m_DriveLetter = drive_letter;

   m_Handle = ::CreateFile( m_Name,
                            access_flags,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            NULL,
                            OPEN_EXISTING,
                            0,
                            NULL );

   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      WFCTRACEVAL( TEXT( "Can't open " ), m_Name );
      WFCTRACEERROR( ::GetLastError() );

      m_DriveType   = DRIVE_UNKNOWN;
      m_DriveLetter = 0;
      m_Name.Empty();

      return( FALSE );
   }

   return( TRUE );
}

BOOL CVolume::PreventRemoval( BOOL prevent_removal )
{
   WFCLTRACEINIT( TEXT( "CVolume::PreventRemoval()" ) );

   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      WFCTRACE( TEXT( "You must first call Open()." ) );
      return( FALSE );
   }

   DWORD number_of_bytes_returned = 0;

   BOOL return_value = FALSE;

   PREVENT_MEDIA_REMOVAL buffer;

   ::ZeroMemory( &buffer, sizeof( buffer ) );

   buffer.PreventMediaRemoval = (BOOLEAN) prevent_removal;

   return_value = ::DeviceIoControl( m_Handle,
                                     IOCTL_STORAGE_MEDIA_REMOVAL,
                                    &buffer,
                                     sizeof( buffer ),
                                     NULL,
                                     0,
                                    &number_of_bytes_returned,
                                     NULL );

   return( return_value );
}

BOOL CVolume::Unlock( void )
{
   WFCLTRACEINIT( TEXT( "CVolume::Unlock()" ) );

   if ( m_Handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      WFCTRACE( TEXT( "You must first call Open()." ) );
      return( FALSE );
   }

   DWORD number_of_bytes_returned = 0;

   BOOL return_value = FALSE;

   return_value = ::DeviceIoControl( m_Handle,
                                     FSCTL_UNLOCK_VOLUME,
                                     NULL,
                                     0,
                                     NULL,
                                     0,
                                    &number_of_bytes_returned,
                                     NULL );

   return( return_value );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CVolume</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles ejecting removable media, locking and dismounting volumes, etc.">
</HEAD>

<BODY>

<H1>CVolume</H1>
$Revision: 6 $<BR>
<HR>

<H2>Description</H2>
This class makes it easy to handle volumes.

<H2>Data Members</H2>
None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>AutomaticallyEject</B>( void )</PRE><DD>
Ejects the volume if it is not in use.

<DT><PRE>BOOL <B>Close</B>( void )</PRE><DD>
Closes the handle to the volume.

<DT><PRE>BOOL <B>Dismount</B>( void )</PRE><DD>
Dismounts the volume.

<DT><PRE>BOOL <B>Eject</B>( void )</PRE><DD>
OK, here's something useful. This method will call the
other methods in the correct order and have the media
spit out of the computer.

<DT><PRE>HANDLE <B>GetHandle</B>( void ) const</PRE><DD>
Gives you the handle to the volume so you can call the
Win32 API yourself.

<DT><PRE>BOOL <B>GetType</B>( UINT&amp; drive_type )</PRE><DD>
Tells you what type of volume you&#39;ve opened. It will return
one of the following (found in <CODE>winioctl.h</CODE>):
<UL>
<LI><CODE>DRIVE_UNKNOWN</CODE> - The drive type cannot be determined.
<LI><CODE>DRIVE_NO_ROOT_DIR</CODE> - The root directory does not exist.
<LI><CODE>DRIVE_REMOVABLE</CODE> - The disk can be removed from the drive.
<LI><CODE>DRIVE_FIXED</CODE> - The disk cannot be removed from the drive.
<LI><CODE>DRIVE_REMOTE</CODE> - The disk is a remote (networked) drive.
<LI><CODE>DRIVE_CDROM</CODE> - The drive is a CD-ROM.
<LI><CODE>DRIVE_RAMDISK</CODE> - The drive is a RAM disk.
</UL>

<DT><PRE>BOOL <B>Load</B>( void )</PRE><DD>
Loads the volume.

<DT><PRE>BOOL <B>Lock</B>( void )</PRE><DD>
Locks the volume.

<DT><PRE>BOOL <B>Open</B>( TCHAR drive_letter )</PRE><DD>
Opens a handle to the drive containing the volume.

<DT><PRE>BOOL <B>PreventRemoval</B>( BOOL prevent_removal = TRUE )</PRE><DD>
Tells NT whether or not you want to prevent the removal
of the volume.

<DT><PRE>BOOL <B>Unlock</B>( void )</PRE><DD>
Unlocks the volume.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

void eject_zip_cartridge( TCHAR zip_drive_letter )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;eject_zip_cartridge()&quot; ) );

   <B>CVolume</B> zip_volume;

   if ( zip_volume.Open( zip_drive_letter ) != FALSE )
   {
      zip_volume.Eject();
   }
}</CODE></PRE>

<H2>API's Used</H2>
<UL>
<LI>CreateFile
<LI>DeviceIoControl
<LI>GetDriveType
<LI>GetLastError
<LI>Sleep
<LI>ZeroMemory
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CVolume.cpp $<BR>
$Modtime: 3/17/00 4:38p $
</BODY>

</HTML>
#endif
