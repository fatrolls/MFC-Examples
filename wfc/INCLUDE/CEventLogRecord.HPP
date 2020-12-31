#if ! defined ( EVENT_LOG_RECORD_CLASS_HEADER )

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
** $Workfile: CEventLogRecord.HPP $
** $Revision: 6 $
** $Modtime: 1/04/00 4:43a $
*/

#define EVENT_LOG_RECORD_CLASS_HEADER

class CEventLogRecord
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CEventLogRecord )
#endif // WFC_NO_SERIALIZATION

   public:

      CEventLogRecord();
      CEventLogRecord( const CEventLogRecord& source );
      CEventLogRecord( const EVENTLOGRECORD * source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CEventLogRecord();

      /*
      ** Data
      */

      CString    Source;
      CString    ComputerName;
      DWORD      RecordNumber;
      DWORD      Reserved;
      CTime      TimeGenerated;
      CTime      TimeWritten;
      DWORD      EventID;
      WORD       EventType;
      WORD       EventCategory;
      WORD       PairedEventFlags;
      DWORD      ClosingRecordNumber;
      CByteArray UserSID;
      CByteArray Data;

      CStringArray Strings;

      /*
      ** Methods
      */

      virtual int  Compare( const CEventLogRecord& source ) const;
      virtual void Copy( const EVENTLOGRECORD * source );
      virtual void Copy( const CEventLogRecord& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual BOOL operator == ( const CEventLogRecord& right_record ) const;
      virtual CEventLogRecord& operator = ( const CEventLogRecord& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};   

#endif // EVENT_LOG_RECORD_CLASS_HEADER
