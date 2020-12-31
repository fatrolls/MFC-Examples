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
** $Workfile: SkyWord.cpp $
** $Revision: 18 $
** $Modtime: 1/17/00 9:29a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CSkyWord::CSkyWord()
{
   WFCLTRACEINIT( TEXT( "CSkyWord::CSkyWord()" ) );
   Empty();
   m_SerialSettings = TEXT( "COM1:2400,n,8,1" );
   m_PhoneNumber    = TEXT( "1-800-759-9673" );
}

CSkyWord::~CSkyWord()
{
   WFCLTRACEINIT( TEXT( "CSkyWord::~CSkyWord()" ) );
   Empty();
}

BOOL CSkyWord::m_Send( void )
{
   WFCLTRACEINIT( TEXT( "CSkyWord::m_Send()" ) );

   if ( m_PhoneNumber.IsEmpty()    ||
        m_Account.IsEmpty()        ||
        m_SerialSettings.IsEmpty()  )
   {
      WFCTRACE( TEXT( "phone number, account or serial settings is empty" ) );
      return( FALSE );
   }

/*
CONNECT 2400

SKYTEL REMOTE TERMINAL

PAGER ID: 1234567
FUNCTION: ?
INVALID FUNCTION
 1. Pager Message Entry
 2. Delayed Pager Message Entry
 3. Next Pager ID
 4. Change Pager Security Code
 5. Page Recall
 6. Review Hold Messages
 7. Hold Pager Messages
 8. Release Hold Messages
 9. Follow Me Paging Functions
10. Coverage Information
11. Priority Call
12. Priority Call Cancel
13. Group Call
16. Usage Security Code
50. Group Page Functions
99. Disconnect
FUNCTION: 1
ENTER ALPHA MESSAGE: TEST - This is a test from Sam Blackburn
SEND ?: Y
FUNCTION: 99
DISCONNECTING
*/

   CModem modem;

   if ( modem.Open( m_SerialSettings ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't open " ), m_SerialSettings );

      m_ErrorCode = modem.GetErrorCode();

      return( FALSE );
   }

   modem.SetPhoneNumber( m_PhoneNumber );

   int connection_try_number = 0;

   BOOL exit_loop = FALSE;

   while( exit_loop == FALSE && connection_try_number < 10 )
   {
      if ( modem.Connect( 90 ) != FALSE )
      {
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

      WFCTRACE( TEXT( "We ran out of connection retries" ) );
      return( FALSE );
   }

   Sleep( 1100 ); // Give them a little time to catch up

   CString string_to_send;
   CString response;

   string_to_send = TEXT( "\r\n" );

   modem.Write( string_to_send );

   WFCTRACE( response );

   if ( modem.WaitForString( TEXT( "PAGER ID: " ), 30, &response ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't find Pager ID, Trying Again..." ) );

      modem.Write( string_to_send );

      if ( modem.WaitForString( TEXT( "PAGER ID: " ), 15, &response ) == FALSE )
      {
         modem.Disconnect();
         return( FALSE );
      }
   }

   // Add the pager ID
   string_to_send = m_Account;
   string_to_send += TEXT( "\r\n" );

   modem.Write( string_to_send );

   WFCTRACE( response );

   if ( modem.WaitForString( TEXT( "FUNCTION: " ), 90, &response ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't find Function" ) );
      modem.Disconnect();
      return( FALSE );
   }

   string_to_send = TEXT( "1\r\n" );

   modem.Write( string_to_send );

   WFCTRACE( response );

   if ( modem.WaitForString( TEXT( "ENTER ALPHA MESSAGE: " ), 90, &response ) == FALSE )
   {
	   WFCTRACEVAL( TEXT( "Can't find Enter Message\nGot this instead:\n" ), response );
      modem.Disconnect();
      return( FALSE );
   }

   string_to_send = m_Message;
 
   string_to_send += TEXT( "\r\n" );

   modem.Write( string_to_send );

   WFCTRACE( response );

   if ( modem.WaitForString( TEXT( "SEND ?: " ), 90, &response ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't find Send?" ) );
      modem.Disconnect();
      return( FALSE );
   }

   string_to_send = TEXT( "Y\r\n" );

   modem.Write( string_to_send );

   WFCTRACE( response );

   if ( modem.WaitForString( TEXT( "FUNCTION: " ), 90, &response ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't find Function to logoff" ) );
      modem.Disconnect();
      return( FALSE );
   }

   string_to_send = TEXT( "99\r\n" );

   modem.Write( string_to_send );

   WFCTRACE( response );

   ::Sleep( 1000 );

   modem.Disconnect();

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CSkyWord</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="The C++ class that handles sending messages to SkyWord/SkyTel pagers.">
</HEAD>

<BODY>

<H1>CSkyWord : <A HREF="Pager.htm">CPager</A></H1>
$Revision: 18 $<HR>

<H2>Description</H2>
This class makes it easy to send messages to a person that has a SkyTel SkyWord
pager.

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

         <B>CSkyWord</B> pager;

         pager.SetAccount( TEXT( &quot;1234567&quot; ) );
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
$Workfile: SkyWord.cpp $<BR>
$Modtime: 1/17/00 9:29a $
</BODY>

</HTML>
#endif
