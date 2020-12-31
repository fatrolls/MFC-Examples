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
** $Workfile: SprintSpectrum.cpp $
** $Revision: 17 $
** $Modtime: 1/17/00 9:31a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CSprintSpectrum::CSprintSpectrum()
{
   WFCLTRACEINIT( TEXT( "CSprintSpectrum::CSprintSpectrum()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();

   m_SerialSettings = TEXT( "COM1:9600,e,7,1" );
   m_PhoneNumber    = TEXT( "1-800-272-6505" );
}

CSprintSpectrum::~CSprintSpectrum()
{
   WFCLTRACEINIT( TEXT( "CSprintSpectrum::~CSprintSpectrum()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

BOOL CSprintSpectrum::m_Send( void )
{
   WFCLTRACEINIT( TEXT( "CSprintSpectrum::m_Send()" ) );

   // Idiot proof the data

   if ( m_PhoneNumber.IsEmpty() )
   {
      WFCTRACE( TEXT( "No Phone Number Set" ) );
      return( FALSE );
   }

   if ( m_Account.IsEmpty() )
   {
      WFCTRACE( TEXT( "No Account Number Set" ) );
      return( FALSE );
   }

   if ( m_SerialSettings.IsEmpty() )
   {
      WFCTRACE( TEXT( "No Serial Port Specified" ) );
      return( FALSE );
   }

/*
CONNECT 9600
ID=
ID=
ID=



WELCOME TO PC MESSAGE CENTER

MAXIMUM ONLINE TIME IS 10 MINUTES
MAXIMUM RESPONSE TIME PER PROMPT IS 60 SECONDS

PRESS <ESC> TO TERMINATE TRANSACTION

1. SEND MESSAGE
2. SUBSCRIBER SERVICES

F. POUR PASSER EN FRANCAIS
S. CAMBIA A ESPANOL

SELECT OPTION >1

ENTER PHONE NUMBER (INCLUDING AREA CODE) OR NAME
> 4101234567

ENTER MESSAGE DATA:
YOU MUST COMPLETE MESSAGE ENTRY IN 5 MINUTES

Good morning, get up and go to work you lazy lima bean.

4101234567 MESSAGE SENT.



PRESS <ESC> TO TERMINATE TRANSACTION

1. SEND MESSAGE
2. SUBSCRIBER SERVICES

F. POUR PASSER EN FRANCAIS
S. CAMBIA A ESPANOL

SELECT OPTION >

ONLINE TIME: 0:46

USER ABORT: THANK YOU FOR USING PC MESSAGE CENTER

*/

   CModem modem;

   if ( modem.Open( m_SerialSettings ) == FALSE )
   {
      m_ErrorCode = modem.GetErrorCode();

      WFCTRACEVAL( TEXT( "Can't open " ), m_SerialSettings );

      return( FALSE );
   }

   modem.SetPhoneNumber( m_PhoneNumber );

   int connection_try_number = 0;

   BOOL exit_loop = FALSE;

   while( exit_loop == FALSE && connection_try_number < 10 )
   {
      if ( modem.Connect( 90 ) != FALSE )
      {
         WFCTRACE( TEXT( "Connected" ) );
         exit_loop = TRUE;
      }
      else
      {
         WFCTRACE( TEXT( "Can't Connect" ) );
         modem.Disconnect();
         connection_try_number++;
      }
   }

   if ( exit_loop == FALSE )
   {
      // We ran out of connection retries...

      return( FALSE );
   }

   Sleep( 1100 ); // Give them a little time to catch up

   CString string_to_send;
   CString response;

   string_to_send = TEXT( "\r\n" );

   modem.Write( string_to_send );

   WFCTRACE( response );

   if ( modem.WaitForString( TEXT( "SELECT OPTION >" ), 60, &response ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't find prompt, Trying Again..." ) );

      modem.Write( string_to_send );

      if ( modem.WaitForString( TEXT( "SELECT OPTION >" ), 15, &response ) == FALSE )
      {
         modem.Disconnect();
         return( FALSE );
      }
   }

   string_to_send = TEXT( "1" );
   WFCTRACE( TEXT( "Sending 1" ) );
   modem.Write( string_to_send );

   if ( modem.WaitForString( TEXT( "> " ), 30, &response ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't find prompt to send account" ) );
      
      modem.Disconnect();

      return( FALSE );
   }

   // Add the pager ID
   string_to_send = m_Account;
   string_to_send += TEXT( "\r" );

   modem.Write( string_to_send );

   WFCTRACE( (LPCTSTR) response );

   if ( modem.WaitForString( TEXT( "ENTER MESSAGE DATA:" ), 90, &response ) == FALSE )
   {
	   WFCTRACEVAL( TEXT( "Can't find Enter Message\nGot this instead:\n" ), response );
      modem.Disconnect();
      return( FALSE );
   }

   // Should check m_Message to make sure it doesn't have carriage returns in it
   string_to_send = m_Message;
   string_to_send += TEXT( "\r" );

   modem.Write( string_to_send );

   WFCTRACE( response );

   if ( modem.WaitForString( TEXT( "SELECT OPTION >" ), 90, &response ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't find Send?" ) );
      modem.Disconnect();
      return( FALSE );
   }

   string_to_send.Empty();
   string_to_send += (TCHAR) 27;

   modem.Write( string_to_send );

   WFCTRACE( response );

   if ( modem.WaitForString( TEXT( "USER ABORT: THANK YOU FOR USING PC MESSAGE CENTER" ), 90, &response ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't find Abort" ) );
   }

   modem.Disconnect();

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CSprintSpectrum</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="The C++ class that handles sending messages to Sprint Spectrum (PCS) pagers.">
</HEAD>

<BODY>

<H1>CSprintSpectrum : <A HREF="Pager.htm">CPager</A></H1>
$Revision: 17 $<HR>

<H2>Description</H2>
This class makes it easy to send messages to a person that has a Sprint Spectrum
PCS.

<H2>Data Members</H2>

None.

<H2>Methods</H2>

No public ones. See <A HREF="Pager.htm">CPager</A>.
<H2>Example</H2>

<PRE><CODE>void wait_for_ring( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;wait_for_ring()&quot; ) );

   <A HREF="Serial.htm">CSerialFile</A> serial;

   while( 1 )
   {
      _tprintf( TEXT( &quot;Opening serial port\n&quot; ) );

      if ( serial.Open( TEXT( &quot;COM1:57600,n,8,1&quot; ) ) != FALSE )
      {
         CString response;

         response = TEXT( &quot;ATM0\r\n&quot; );

         serial.Write( response );

         // See if the phone rang

         while ( serial.WaitForString( TEXT( &quot;RING&quot; ), 2, &amp;response ) == FALSE )
         {
            if ( response.GetLength() &gt; 0 )
            {
               _tprintf( TEXT( &quot;Didn't get RING, going to sleep \&quot;%s\&quot;\n&quot; ), (LPCTSTR) response );
            }

            Sleep( 10000 );
         }

         _tprintf( TEXT( &quot;Received a RING, waiting for them to end\n&quot; ) );

         while( serial.WaitForString( TEXT( &quot;RING&quot; ), 7 ) != FALSE )
         {
            // Do Nothing
         }

         _tprintf( TEXT( &quot;Closing serial port\n&quot; ) );

         serial.Close();

         CTime time_now( CTime::GetCurrentTime() );

         Sleep( 1000 );

         CString message;

         message.Format( TEXT( &quot;The phone rang at %s&quot; ), (LPCTSTR) time_now.Format( &quot;%H:%M:%S %d %b %y&quot; ) );

         <B>CSprintSpectrum</B> pager;

         pager.SetAccount( TEXT( &quot;4101234567&quot; ) );
         pager.SetMessage( message );

         _tprintf( TEXT( &quot;Calling pager.Send()\n&quot; ) );
         pager.Send();
      }
      else
      {
         _tprintf( TEXT( &quot;Can't open serial port\n&quot; ) );
      }

      Sleep( 1000 );
   }
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: SprintSpectrum.cpp $<BR>
$Modtime: 1/17/00 9:31a $
</BODY>

</HTML>
#endif
