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
** $Workfile: modem.cpp $
** $Revision: 18 $
** $Modtime: 1/05/00 3:37a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined( WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CModem, CSerialFile, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CModem::CModem()
{
   WFCLTRACEINIT( TEXT( "CModem::CModem()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CModem::~CModem()
{
   WFCLTRACEINIT( TEXT( "CModem::~CModem()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( IsConnected() != FALSE )
   {
      Disconnect();
   }

   m_Initialize();
}

BOOL CModem::Connect( DWORD number_of_seconds_to_wait )
{
   WFCLTRACEINIT( TEXT( "CModem::Connect()" ) );
   ASSERT( m_IsOpen != FALSE );

   if ( m_IsOpen == FALSE )
   {
      WFCTRACE( TEXT( "CModem::Connect(), Must open serial port first" ) );
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   CString string_to_send_to_modem( TEXT( "ATM0\r\n" ) );

   Write( string_to_send_to_modem );

   ::Sleep( 500 );

   string_to_send_to_modem  = TEXT( "ATDT" );
   string_to_send_to_modem += m_PhoneNumber;
   string_to_send_to_modem += TEXT( "\r\n" );

   Write( string_to_send_to_modem );

   CString what_was_read( TEXT( "" ) );

   if ( WaitForString( TEXT( "CONNECT" ), number_of_seconds_to_wait, &what_was_read ) == FALSE )
   {
      Disconnect();
      return( FALSE );
   }

   m_ErrorCode = 0;

   // 1999-07-22
   // Thanks go to Don Kennedy (dkennedy@hightower.com) for finding
   // a bug here, I was not setting m_IsConnected

   m_IsConnected = TRUE;

   return( TRUE );
}

BOOL CModem::Disconnect( void )
{
   WFCLTRACEINIT( TEXT( "CModem::Disconnect()" ) );
   ASSERT( m_IsOpen != FALSE );

   if ( m_IsOpen != FALSE )
   {
      CString string_to_send( TEXT( "+++ATH\r\n" ) );

      Write( string_to_send );
      WaitForString( TEXT( "OK" ) );
   }

   m_IsConnected = FALSE;

   return( TRUE );
}

BOOL CModem::IsConnected( void ) const
{
   WFCLTRACEINIT( TEXT( "CModem::IsConnected()" ) );
   return( m_IsConnected );
}

void CModem::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CModem::m_Initialize()" ) );
   m_IsConnected     = FALSE;
   m_UsePulseDialing = FALSE;
   m_PhoneNumber.Empty();
}

void CModem::GetPhoneNumber( CString& phone_number ) const
{
   WFCLTRACEINIT( TEXT( "CModem::GetPhoneNumber()" ) );
   phone_number = m_PhoneNumber;
}

void CModem::SetPhoneNumber( const CString& phone_number )
{
   WFCLTRACEINIT( TEXT( "CModem::SetPhoneNumber()" ) );
   m_PhoneNumber = phone_number;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CModem::Dump( CDumpContext& dump_context ) const
{
   CSerialFile::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_IsConnected     = "  ) << m_IsConnected           << TEXT( "\n" );
   dump_context << TEXT( "   m_UsePulseDialing = "  ) << m_UsePulseDialing       << TEXT( "\n" );
   dump_context << TEXT( "   m_PhoneNumber is   \"" ) << (LPCTSTR) m_PhoneNumber << TEXT( "\"\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

#if ! defined( WFC_NO_SERIALIZATION )

void CModem::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CModem::Serialize()" ) );
   CSerialFile::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << (DWORD) m_IsConnected;
      archive << (DWORD) m_UsePulseDialing;
      archive << m_PhoneNumber;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      DWORD temp_dword = 0;

      archive >> temp_dword;
      m_IsConnected = temp_dword;

      archive >> temp_dword;
      m_UsePulseDialing = temp_dword;

      archive >> m_PhoneNumber;

      if ( m_IsConnected != FALSE )
      {
         m_IsConnected = FALSE;
         Connect();
      }
   }
}

#endif // WFC_NO_SERIALIZATION

// End of source
