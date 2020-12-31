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
** $Workfile: CRIFFChunk.cpp $
** $Revision: 5 $
** $Modtime: 1/04/00 5:23a $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CRIFFChunk::CRIFFChunk()
{
   WFCTRACEINIT( "CRIFFChunk::CRIFFChunk()" );
   WFCTRACEVAL( "pointer is ", (VOID *) this );
   Empty();
}

CRIFFChunk::CRIFFChunk( const CRIFFChunk& source )
{
   WFCTRACEINIT( "CRIFFChunk::CRIFFChunk( CRIFFChunk )" );
   WFCTRACEVAL( "pointer is ", (VOID *) this );
   Copy( source );
}

CRIFFChunk::~CRIFFChunk()
{
   WFCTRACEINIT( "CRIFFChunk::~CRIFFChunk()" );
   WFCTRACEVAL( "pointer is ", (VOID *) this );
   Empty();
}

void CRIFFChunk::Copy( const CRIFFChunk& source )
{
   WFCTRACEINIT( "CRIFFChunk::Copy( CPager & )" );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( "Attempt to make a copy of ourself (such silliness)." );
      return;
   }


}

void CPager::Empty( void )
{
   WFCTRACEINIT( "CRIFFChunk::Empty()" );
   m_Account.Empty();
   m_ErrorCode = 0;
   m_PhoneNumber.Empty();
   m_Message.Empty();
   m_SerialSettings.Empty();
   m_NumberOfRetries = 1;
}

void CPager::GetAccount( CString& account ) const
{
   WFCTRACEINIT( "CPager::GetAccount()" );
   account = m_Account;
}

DWORD CPager::GetErrorCode( void ) const
{
   WFCTRACEINIT( "CPager::GetErrorCode()" );
   return( m_ErrorCode );
}

void CPager::GetMessage( CString& message ) const
{
   WFCTRACEINIT( "CPager::GetMessage()" );
   message = m_Message;
}

DWORD CPager::GetNumberOfRetries( void ) const
{
   WFCTRACEINIT( "CPager::GetNumberOfRetries()" );
   return( m_NumberOfRetries );
}

void CPager::GetPhoneNumber( CString& phone_number ) const
{
   WFCTRACEINIT( "CPager::GetPhoneNumber()" );
   phone_number = m_PhoneNumber;
}

void CPager::GetSerialPort( CString& serial_settings ) const
{
   WFCTRACEINIT( "CPager::GetSerialPort()" );
   serial_settings = m_SerialSettings;
}

BOOL CPager::Send( void )
{
   WFCTRACEINIT( "CPager::Send()" );

   DWORD tries = 0;

   BOOL return_value = FALSE;

   // Number of Retries < 1 ain't valid, we will always try at least once

   DWORD number_of_tries = m_NumberOfRetries;

   if ( number_of_tries < 1 )
   {
      WFCTRACE( "m_NumberOfRetries < 1 so setting tries to 1." );
      number_of_tries = 1;
   }

   WFCTRACEVAL( "number of tries is ", number_of_tries );

   while( tries < number_of_tries )
   {
      WFCTRACE( "Calling m_Send()" );
      return_value = m_Send();

      if ( return_value == TRUE )
      {
         WFCTRACE( "m_Send() returned TRUE." );
         return( return_value );
      }
      else
      {
         WFCTRACE( "m_Send() returned FALSE, retrying" );
         tries++;
      }
   }

   return( return_value );
}

void CPager::Serialize( CArchive& archive )
{
   WFCTRACEINIT( "CPager::Serialize()" );
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( "Storing" );
      archive << m_Account;
      archive << m_PhoneNumber;
      archive << m_Message;
      archive << m_SerialSettings;
      archive << m_ErrorCode;
      archive << m_NumberOfRetries;
   }
   else
   {
      WFCTRACE( "Restoring" );
      archive >> m_Account;
      archive >> m_PhoneNumber;
      archive >> m_Message;
      archive >> m_SerialSettings;
      archive >> m_ErrorCode;
      archive >> m_NumberOfRetries;
   }
}

void CPager::SetAccount( const CString& account )
{
   WFCTRACEINIT( "CPager::SetAccount()" );
   m_Account = account;
}

void CPager::SetMessage( const CString& message )
{
   WFCTRACEINIT( "CPager::SetMessage()" );
   m_Message = message;
}

void CPager::SetNumberOfRetries( const DWORD retries )
{
   WFCTRACEINIT( "CPager::SetNumberOfRetries()" );
   m_NumberOfRetries = retries;
}

void CPager::SetPhoneNumber( const CString& phone_number )
{
   WFCTRACEINIT( "CPager::SetPhoneNumber()" );
   m_PhoneNumber = phone_number;
}

void CPager::SetSerialPort( const CString& serial_settings )
{
   WFCTRACEINIT( "CPager::SetSerialPort()" );
   m_SerialSettings = serial_settings;
}

CPager& CPager::operator = ( const CPager& source )
{
   WFCTRACEINIT( "CPager::operator = ( const CPager& )" );
   Copy( source );
   return( *this );
}

#if defined( _DEBUG )

void CPager::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << "{\n";
   dump_context << "   m_Account is         \"" << (LPCTSTR) m_Account        << "\"\n";
   dump_context << "   m_PhoneNumber is     \"" << (LPCTSTR) m_PhoneNumber    << "\"\n";
   dump_context << "   m_Message is         \"" << (LPCTSTR) m_Message        << "\"\n";
   dump_context << "   m_SerialSettings is  \"" << (LPCTSTR) m_SerialSettings << "\"\n";
   dump_context << "   m_NumberOfRetries is  "  << m_NumberOfRetries          << "\n";
   dump_context << "   m_ErrorCode is        "  << m_ErrorCode                << "\n";
   dump_context << "}\n";
}

#endif // _DEBUG

#if 0
<HTML>
<HEAD><TITLE>WFC - CPager</TITLE></HEAD>
<BODY>
<H1>CPager : CObject</H1>
$Revision: 5 $
<HR>
<H2>Description</H2>
This class is a virtual base class that describes the methods of dealing with pagers.
<H2>Data Members</H2>
None.
<H2>Methods</H2>
<DL COMPACT>
<DT><DFN><B>Copy</B></DFN><DD>Copies another CPager.
<DT><DFN><B>Empty</B></DFN><DD>Clears all internal data members.
<DT><DFN><B>GetAccount</B></DFN><DD>Retrieves the account string.
<DT><DFN><B>GetErrorCode</B></DFN><DD>Retrieves the error code for the
last function that failed.
<DT><DFN><B>GetMessage</B></DFN><DD>Retrieves the message that was/may be 
sent to the pager.
<DT><DFN><B>GetNumberOfRetries</B></DFN><DD>Retrieves the number of times
the class will attempt to resend the message if it fails.
<DT><DFN><B>GetPhoneNumber</B></DFN><DD>Retrieves the phone number of the
pager company's computer.
<DT><DFN><B>GetSerialPort</B></DFN><DD>Retrieves the name of the serial port in 
the "COM1:9600,n,8,1" format.
<DT><DFN><B>Send</B></DFN><DD>Method to call after all data members have been set.
This will actually dial the phone, log onto the service, send the message and
log off.
<DT><DFN><B>Serialize</B></DFN><DD>Saves/restores the object.
<DT><DFN><B>SetAccount</B></DFN><DD>Stores the account number to send a message to.
<DT><DFN><B>SetMessage</B></DFN><DD>Stores the message to be sent.
<DT><DFN><B>SetNumberOfRetries</B></DFN><DD>Sets the number of times Send() is to
try to get the message through before giving up.
<DT><DFN><B>SetPhoneNumber</B></DFN><DD>Sets the phone number for the pager company.
<DT><DFN><B>SetSerialPort</B></DFN><DD>Sets the serial port to use to contact the 
pager company.
</DL>
<H2>Example</H2>
<PRE>
<CODE>
void wait_for_ring( void )
{
   CSerialFile serial;

   while( 1 )
   {
      printf( &quot;Opening serial port\n&quot; );

      if ( serial.Open( &quot;COM1:57600,n,8,1&quot; ) == TRUE )
      {
         CString response;

         response = &quot;ATM0\r\n&quot;;

         serial.Write( response );

         // See if the phone rang

         while ( serial.WaitForString( &quot;RING&quot;, 2, &amp;response ) != TRUE )
         {
            if ( response.GetLength() &gt; 0 )
            {
               printf( &quot;Didn't get RING, going to sleep \&quot;%s\&quot;\n&quot;, (LPCTSTR) response );
            }

            ::Sleep( 10000 );
         }

         printf( &quot;Received a RING, waiting for them to end\n&quot; );

         while( serial.WaitForString( &quot;RING&quot;, 7 ) == TRUE )
         {
            // Do Nothing
         }

         printf( &quot;Closing serial port\n&quot; );

         serial.Close();

         CTime time_now( CTime::GetCurrentTime() );

         ::Sleep( 1000 );

         CString message;

         message.Format( &quot;The phone rang at %s&quot;, (LPCTSTR) time_now.Format( &quot;%H:%M:%S %d %b %y&quot; ) );

         CSprintSpectrum pager;

         pager.SetAccount( &quot;4101234567&quot; );
         pager.SetMessage( message );

         printf( &quot;Calling pager.Send()\n&quot; );
         pager.Send();
      }
      else
      {
         printf( &quot;Can't open serial port\n&quot; );
      }

      ::Sleep( 1000 );
   }
}</CODE></PRE>
<I>Copyright, 2000, Samuel R. Blackburn</I><BR>
$Workfile: CRIFFChunk.cpp $<BR>
$Modtime: 1/04/00 5:23a $
</BODY>
</HTML>
#endif
