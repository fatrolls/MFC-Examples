#if ! defined( EVENT_LOG_CLASS )

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
** $Workfile: cevntlog.hpp $
** $Revision: 14 $
** $Modtime: 1/04/00 4:44a $
*/

#define EVENT_LOG_CLASS

class CEventLog
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_DYNAMIC( CEventLog )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CEventLog( const CEventLog& ) {};
      CEventLog& operator=( const CEventLog& ) { return( *this ); };

   protected:

      HANDLE m_LogHandle;
      HANDLE m_EventSourceHandle;

      DWORD m_ErrorCode;
      DWORD m_NumberOfBytesRead;
      DWORD m_NumberOfBytesInNextRecord;

      void m_Initialize( void );

   public:

      enum EventType
      {
         eventError       = EVENTLOG_ERROR_TYPE,
         eventWarning     = EVENTLOG_WARNING_TYPE,
         eventInformation = EVENTLOG_INFORMATION_TYPE,
         eventSuccess     = EVENTLOG_AUDIT_SUCCESS,
         eventFailure     = EVENTLOG_AUDIT_FAILURE
      };

      CEventLog();
      CEventLog( LPCTSTR source_name );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CEventLog();

      /*
      ** Data
      */

      CString ComputerName;
      CString LogName;

      /*
      ** Methods
      */

      virtual BOOL  Backup( LPCTSTR name_of_backup_file );
      virtual BOOL  Clear(  LPCTSTR name_of_backup_file );
      virtual BOOL  Close( void );
      virtual BOOL  CreateApplicationLog( LPCTSTR application_name,
                                          LPCTSTR file_containing_message_table_resource,
                                          DWORD   supported_types );
      virtual BOOL  CreateCustomLog( LPCTSTR log_name, LPCTSTR log_filename = NULL, DWORD maximum_file_size = 0x80000, DWORD overwrite_after_this_many_seconds = 604800 );
      virtual BOOL  Delete( LPCTSTR log_name ); // Very DANGEROUS! Will delete any log you specify
      virtual BOOL  DeleteApplicationLog( LPCTSTR application_name );
      virtual BOOL  DeregisterSource( void );
      virtual BOOL  EnumerateLogs( DWORD& enumerator ) const;
      virtual DWORD GetErrorCode( void ) const;
      virtual HANDLE GetHandle( void ) const;
      virtual BOOL  GetNextLog( DWORD& enumerator, CString& log_name );
      virtual BOOL  GetNumberOfRecords( DWORD& number_of_records );
      virtual DWORD GetOldestRecordNumber( void );
      virtual BOOL  NotifyChange( HANDLE event_handle, HANDLE log_handle = NULL );
      virtual BOOL  OpenBackup( LPCTSTR name_of_backup_file, LPCTSTR name_of_computer = NULL );
      virtual BOOL  Open( LPCTSTR log_name, LPCTSTR name_of_computer = NULL );
      virtual BOOL  Read( DWORD  record_number,
                          CEventLogRecord& record,
                          DWORD  how_to_read = EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ );
      virtual BOOL  Read( DWORD  record_number, 
                          LPVOID buffer, 
                          DWORD& number_of_bytes_to_read, 
                          DWORD  how_to_read = EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ );
      virtual BOOL  RegisterSource( LPCTSTR source_name, LPCTSTR name_of_computer = NULL );
      virtual BOOL  Report( EventType event_type,
                            WORD      category,
                            DWORD     event_id,
                            WORD      number_of_strings        = 0,
                            LPCTSTR * string_array             = NULL,
                            DWORD     number_of_raw_data_bytes = 0,
                            LPVOID    raw_data_buffer          = NULL,
                            PSID      user_sid                 = NULL );
      virtual BOOL  Report( LPCTSTR   log_name, 
                            DWORD     message_string_resource_id,
                            WORD      number_of_strings = 0,
                            LPCTSTR * string_array      = NULL );
      virtual void  ReportError( LPCTSTR string_to_report );
      virtual void  ReportInformation( LPCTSTR string_to_report );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING ) 

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // EVENT_LOG_CLASS
