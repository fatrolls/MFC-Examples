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
** $Workfile: CEventLogRecord.CPP $
** $Revision: 19 $
** $Modtime: 1/04/00 5:11a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CEventLogRecord, CObject, 1 );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG )
#define new DEBUG_NEW
#endif // _DEBUG

CEventLogRecord::CEventLogRecord()
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::CEventLogRecord()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CEventLogRecord::CEventLogRecord( const CEventLogRecord& source )
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::CEventLogRecord( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CEventLogRecord::CEventLogRecord( const EVENTLOGRECORD * source )
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::CEventLogRecord( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CEventLogRecord::~CEventLogRecord()
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::~CEventLogRecord()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

int CEventLogRecord::Compare( const CEventLogRecord& source ) const
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::Compare()" ) );

   int return_value = 0;

   if ( RecordNumber < source.RecordNumber )
   {
      return_value = (-1);
   }
   else if ( RecordNumber > source.RecordNumber )
   {
      return_value = 1;
   }
   else
   {
      return_value = 0;
   }

   return( return_value );
}

void CEventLogRecord::Copy( const CEventLogRecord& source )
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::Copy( CEventLogRecord )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Source              = source.Source;
   ComputerName        = source.ComputerName;
   RecordNumber        = source.RecordNumber;
   Reserved            = source.Reserved;
   TimeGenerated       = source.TimeGenerated;
   TimeWritten         = source.TimeWritten;
   EventID             = source.EventID;
   EventType           = source.EventType;
   EventCategory       = source.EventCategory;
   PairedEventFlags    = source.PairedEventFlags;
   ClosingRecordNumber = source.ClosingRecordNumber;
   UserSID.Copy( source.UserSID );
   Data.Copy( source.Data );
   Strings.Copy( source.Strings );
}

void CEventLogRecord::Copy( const EVENTLOGRECORD *source )
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::Copy( EVENTLOGRECORD )" ) );
   ASSERT( source != NULL );

   Empty();

   // Choose to live

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, do not trust it

   try
   {
      WFCTRACEVAL( TEXT( "source->Length              " ), source->Length              );
      WFCTRACEVAL( TEXT( "source->Reserved            " ), source->Reserved            );
      WFCTRACEVAL( TEXT( "source->RecordNumber        " ), source->RecordNumber        );
      WFCTRACEVAL( TEXT( "source->TimeGenerated       " ), source->TimeGenerated       );
      WFCTRACEVAL( TEXT( "source->TimeWritten         " ), source->TimeWritten         );
      WFCTRACEVAL( TEXT( "source->EventID             " ), source->EventID             );
      WFCTRACEVAL( TEXT( "source->EventType           " ), source->EventType           );
      WFCTRACEVAL( TEXT( "source->NumStrings          " ), source->NumStrings          );
      WFCTRACEVAL( TEXT( "source->EventCategory       " ), source->EventCategory       );
      WFCTRACEVAL( TEXT( "source->ReservedFlags       " ), source->ReservedFlags       );
      WFCTRACEVAL( TEXT( "source->ClosingRecordNumber " ), source->ClosingRecordNumber );
      WFCTRACEVAL( TEXT( "source->StringOffset        " ), source->StringOffset        );
      WFCTRACEVAL( TEXT( "source->UserSidLength       " ), source->UserSidLength       );
      WFCTRACEVAL( TEXT( "source->UserSidOffset       " ), source->UserSidOffset       );
      WFCTRACEVAL( TEXT( "source->DataLength          " ), source->DataLength          );
      WFCTRACEVAL( TEXT( "source->DataOffset          " ), source->DataOffset          );

      // The EVENTLOGRECORD structure looks like it was designed by one
      // of the grown-ups at Microsoft (i.e. no Hungarian notation crap)

      RecordNumber        = source->RecordNumber;
      Reserved            = source->Reserved;
      TimeGenerated       = CTime( source->TimeGenerated );
      TimeWritten         = CTime( source->TimeWritten   );
      EventID             = source->EventID;
      EventType           = source->EventType;
      EventCategory       = source->EventCategory;
      PairedEventFlags    = source->ReservedFlags;
      ClosingRecordNumber = source->ClosingRecordNumber;

      // Here's where things start to get a little tricky...

      BYTE * byte_p = (BYTE *) source;
      BYTE byte_to_add = 0;

      DWORD here  = source->UserSidOffset;
      DWORD index = 0;

      while( index < source->UserSidLength )
      {
         byte_to_add = byte_p[ here ];
         WFCTRACEVAL( TEXT( "Adding this to UserSID " ), byte_to_add );
         UserSID.Add( byte_to_add );
         here++;
         index++;
      }

      index = 0;
      here = source->DataOffset;

      while( index < source->DataLength )
      {
         Data.Add( byte_p[ here ] );
         here++;
         index++;
      }

      here = sizeof( EVENTLOGRECORD );

      // TCHAR character = 0;

      TCHAR * character_pointer = (TCHAR *) &byte_p[ here ];

      // Next comes the SourceName

      // 1999-10-11, Thanks go to Louis Beauchamp (louisbea@nortelnetworks.com)
      // For finding a UNICODE problem here

      while( *character_pointer != 0 )
      {
         Source += *character_pointer;
         character_pointer++;
         here += sizeof( TCHAR );
      }

      while( *character_pointer == 0 )
      {
         character_pointer++;
         here += sizeof( TCHAR );
      }

      // ComputerName

      while( *character_pointer != 0 )
      {
         ComputerName += *character_pointer;
         character_pointer++;
         here += sizeof( TCHAR );
      }

      // Strings

      // Thanks go to Bejan Aminifard (bejan@ix.netcom.com) for
      // finding the bug where I wasn't copying all of the strings
      // in the record. OOPS!

      CString data_string( TEXT( "" ) );

      int number_of_strings = 0;

      here = source->StringOffset;

      character_pointer = (TCHAR *) &byte_p[ here ];

      while( number_of_strings < source->NumStrings )
      {
         data_string.Empty();

         while( *character_pointer != 0 )
         {
            data_string += *character_pointer;
            character_pointer++;
            here += sizeof( TCHAR );
         }

         Strings.Add( data_string );

         number_of_strings++;

         // Advance to the next string

         if ( *character_pointer == 0 && number_of_strings < source->NumStrings )
         {
            while( *character_pointer == 0 )
            {
               character_pointer++;
               here += sizeof( TCHAR );
            }
         }
      }
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CEventLogRecord::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   Source              = " ) << Source              << TEXT( "\n" );
   dump_context << TEXT( "   ComputerName        = " ) << ComputerName        << TEXT( "\n" );
   dump_context << TEXT( "   RecordNumber        = " ) << RecordNumber        << TEXT( "\n" );
   dump_context << TEXT( "   Reserved            = " ) << Reserved            << TEXT( "\n" );
   dump_context << TEXT( "   TimeGenerated       = " ) << TimeGenerated       << TEXT( "\n" );
   dump_context << TEXT( "   TimeWritten         = " ) << TimeWritten         << TEXT( "\n" );
   dump_context << TEXT( "   EventID             = " ) << EventID             << TEXT( "\n" );
   dump_context << TEXT( "   EventType           = " ) << EventType           << TEXT( "\n" );
   dump_context << TEXT( "   EventCategory       = " ) << EventCategory       << TEXT( "\n" );
   dump_context << TEXT( "   PairedEventFlags    = " ) << PairedEventFlags    << TEXT( "\n" );
   dump_context << TEXT( "   ClosingRecordNumber = " ) << ClosingRecordNumber << TEXT( "\n" );
   dump_context << TEXT( "   UserSID             = " ) << UserSID             << TEXT( "\n" );
   dump_context << TEXT( "   Data                = " ) << Data                << TEXT( "\n" );
   dump_context << TEXT( "   Strings             = " ) << Strings             << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CEventLogRecord::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::Empty()" ) );
   Source.Empty();
   ComputerName.Empty();
   RecordNumber        = 0;
   Reserved            = 0;
   TimeGenerated       = CTime( 0 );
   TimeWritten         = CTime( 0 );
   EventID             = 0;
   EventType           = 0;
   EventCategory       = 0;
   PairedEventFlags    = 0;
   ClosingRecordNumber = 0;
   UserSID.RemoveAll();
   Data.RemoveAll();
   Strings.RemoveAll();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CEventLogRecord::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << Source;
      archive << ComputerName;
      archive << RecordNumber;
      archive << Reserved;
      archive << EventID;
      archive << EventType;
      archive << EventCategory;
      archive << PairedEventFlags;
      archive << ClosingRecordNumber;
      archive << TimeGenerated;
      archive << TimeWritten;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> Source;
      archive >> ComputerName;
      archive >> RecordNumber;
      archive >> Reserved;
      archive >> EventID;
      archive >> EventType;
      archive >> EventCategory;
      archive >> PairedEventFlags;
      archive >> ClosingRecordNumber;
      archive >> TimeGenerated;
      archive >> TimeWritten;
   }

   UserSID.Serialize( archive );
   Data.Serialize( archive );
   Strings.Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

CEventLogRecord& CEventLogRecord::operator = ( const CEventLogRecord& source )
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::operator =" ) );
   Copy( source );
   return( *this );
}

BOOL CEventLogRecord::operator == ( const CEventLogRecord& right_record ) const
{
   WFCLTRACEINIT( TEXT( "CEventLogRecord::operator ==" ) );

   if ( Compare( right_record ) == 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CEventLogRecord</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, event logging, source code">
<META name="description" content="The C++ class that handles event log records.">
</HEAD>

<BODY>

<H1>CEventLogRecord : CObject</H1>
$Revision: 19 $
<HR>

<H2>Description</H2>

This class makes it easy to deal with Event Log records. It is patterened after
the EVENTLOGRECORD data structure.

<H2>Data Members</H2>

<DL COMPACT>

<DT><B>ComputerName</B><DD>Name of the computer where the event occured.
<DT><B>Source</B><DD>Name of the application that generated the event.
<DT><B>RecordNumber</B><DD>Number of the record.
<DT><B>Reserved</B><DD>A special field that Microsoft doesn't know
what to do with.
<DT><B>TimeGenerated</B><DD>Time when the event occured.
<DT><B>TimeWritten</B><DD>Time when the event was written.
<DT><B>EventID</B><DD>ID of the event.
<DT><B>EventType</B><DD>Type of event.
<DT><B>EventCategory</B><DD>The category of event.
<DT><B>PairedEventFlags</B><DD>Flags.
<DT><B>ClosingRecordNumber</B><DD>Used in paired events.
<DT><B>UserSID</B><DD>The user's SID.
<DT><B>Data</B><DD>Any data that was written with the event.
<DT><B>Strings</B><DD>String data associated with the event.
</DL>

<H2>Methods</H2>

<DL COMPACT>
<DT><B>Compare</B><DD>Compares this object with another one.
<DT><B>Copy</B><DD>Copies another CEventLogRecord or a EVENTLOGRECORD.
<DT><B>Empty</B><DD>Sets all data members to an initial state.
<DT><B>Serialize</B><DD>After all, we are a CObject...
</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

void test_CEventLog( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CEventLog()&quot; ) );

   <A HREF="CEVNTLOG.htm">CEventLog</A> log;

   if ( log.Open( TEXT( &quot;WFC&quot; ) ) == FALSE )
   {
      WFCTRACE( TEXT( &quot;Can't Open WFC event log because&quot; ) );
      WFCTRACEERROR( log.GetErrorCode() );
   }

   if ( log.RegisterSource( TEXT( &quot;WFC&quot; ) ) == FALSE )
   {
      WFCTRACE( TEXT( &quot;Can't Open WFC event log because&quot; ) );
      WFCTRACEERROR( log.GetErrorCode() );
   }

   <B>CEventLogRecord</B> record;

   DWORD loop_index = 0;

   while( log.Read( loop_index, record ) != FALSE )
   {
#if defined( _DEBUG )
      record.Dump( afxDump );
#endif // _DEBUG
      loop_index++;
   }

}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CEventLogRecord.CPP $<BR>
$Modtime: 1/04/00 5:11a $
</BODY>

</HTML>
#endif
