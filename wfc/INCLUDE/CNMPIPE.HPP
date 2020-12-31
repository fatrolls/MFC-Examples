#if ! defined( NAMED_PIPE_CLASS_HEADER )

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
** $Workfile: cnmpipe.hpp $
** $Revision: 10 $
** $Modtime: 1/04/00 4:51a $
*/

#define NAMED_PIPE_CLASS_HEADER

class CNamedPipe : public CDummyFile
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CNamedPipe( const CNamedPipe& ) {};
      CNamedPipe& operator=( const CNamedPipe& ) { return( *this ); };

   public:

      enum NamedPipeTypes
      {
         typeClientEnd = PIPE_CLIENT_END,
         typeServerEnd = PIPE_SERVER_END,
         typeMessage   = PIPE_TYPE_MESSAGE
      };

   private:

      void m_Initialize( DWORD input_buffer_size, DWORD output_buffer_size );

   protected:

      HANDLE m_PipeHandle;

      BOOL m_AutomaticallyDelete;

      NamedPipeTypes m_TypeOfPipe; // From GetInfo()

      LPVOID m_InputBuffer;
      LPVOID m_OutputBuffer;

      DWORD m_MaximumNumberOfInstances; // From GetInfo()

      DWORD m_InputBufferSize;
      DWORD m_OutputBufferSize;
      DWORD m_NumberOfBytesToWrite;
      DWORD m_NumberOfBytesRead;
      DWORD m_Timeout;

      CString m_PipeName;

      CUniversalNamingConvention m_FullPipeName;

      /*
      ** Information returned from GetNamedPipeHandleState()
      */

      DWORD m_PipeState;
      DWORD m_NumberOfInstances;
      DWORD m_MaximumNumberOfBytesBeforeRemoteTransmission;
      DWORD m_MaximumNumberOfMillisecondsBeforeRemoteTransmission;

      CString m_UserNameOfClientProcess;
      
   public:

      CNamedPipe( DWORD input_buffer_size = 4096, DWORD output_buffer_size = 4096 );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CNamedPipe();

      /*
      ** The Win32 API
      */

      virtual BOOL Call( CString& name_of_pipe, 
                         LPVOID   write_buffer, 
                         DWORD    size_of_write_buffer, 
                         LPVOID   read_buffer, 
                         DWORD    size_of_read_buffer, 
                         DWORD   *address_of_number_of_bytes_read,
                         DWORD    number_of_milliseconds_to_wait = NMPWAIT_WAIT_FOREVER ); // CallNamedPipe

      virtual BOOL Connect( LPOVERLAPPED overlapped_p = NULL ); // ConnectNamedPipe

      virtual BOOL Create( LPCTSTR server_name,
                           LPCTSTR name_of_pipe,
                           DWORD   open_mode       = PIPE_ACCESS_DUPLEX,
                           DWORD   type_of_pipe    = PIPE_TYPE_BYTE,
                           DWORD   number_of_pipes = PIPE_UNLIMITED_INSTANCES,
                           LPSECURITY_ATTRIBUTES security_attributes_p = NULL );

      virtual BOOL Disconnect( void ); // DisconnectNamedPipe
      virtual BOOL GetState( void ); // GetNamedPipeHandleState
      virtual BOOL GetInformation( void ); // GetNamedPipeInfo

      virtual BOOL Peek( LPVOID buffer_address,
                         DWORD  size_of_buffer,
                         DWORD& number_of_bytes_read,
                         DWORD& number_of_bytes_available,
                         DWORD& number_of_bytes_remaining_in_message );
      
      virtual BOOL SetState( DWORD new_pipe_mode,
                             DWORD maximum_number_of_bytes_before_transmission, 
                             DWORD maximum_number_of_milliseconds_before_transmission );
      
      virtual BOOL Transact( LPOVERLAPPED overlapped_p = NULL ); // TransactNamedPipe
      
      virtual BOOL Wait( LPCTSTR server_name,
                         LPCTSTR name_of_pipe, 
                         DWORD   number_of_milliseconds = NMPWAIT_USE_DEFAULT_WAIT );

      /*
      ** API's to make life a little easier 
      */

#if ! defined( WFC_STL )
      virtual BOOL Open( LPCTSTR pipe_name, UINT port_number = PIPE_CLIENT_END, CFileException * perror = NULL );
#else // WFC_STL
      virtual BOOL Open( LPCTSTR pipe_name, UINT port_number = PIPE_CLIENT_END );
#endif // WFC_STL

      virtual void Close( void );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // NAMED_PIPE_CLASS_HEADER
