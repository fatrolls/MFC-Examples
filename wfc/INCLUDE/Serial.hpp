#if ! defined( SERIAL_FILE_CLASS_HEADER )

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
** $Workfile: serial.hpp $
** $Revision: 24 $
** $Modtime: 1/04/00 5:00a $
*/

#define SERIAL_FILE_CLASS_HEADER

class CDeviceControlBlock;

class CSerialFile : public CDummyFile
{
#if ! defined( WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CSerialFile )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CSerialFile( const CSerialFile& ) {};
      CSerialFile& operator=( const CSerialFile& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      BOOL m_IsOpen;
      BOOL m_PurgeBufferOnError;

      DWORD m_CommunicationErrorCodes;
      DWORD m_InputBufferSize;
      DWORD m_OutputBufferSize;

      COMSTAT m_CommunicationsStatus;

      virtual void m_ClearError( int line_number = 0 );

   public:

      CSerialFile();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CSerialFile();

      enum _Flows
      {
         flowNone     = 0,
         flowRtsCts   = 1,
         flowDtrDsr   = 2,
         flowXonXoff  = 4,
         flowSoftware = flowXonXoff,
         flowHardware = flowRtsCts
      };

      enum _Purges
      {
         purgeTerminateWriteOperation = PURGE_TXABORT,
         purgeTerminateReadOperation  = PURGE_RXABORT,
         purgeClearInputBuffer        = PURGE_RXCLEAR,
         purgeClearOutputBuffer       = PURGE_TXCLEAR,
         purgeAll                     = PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_RXABORT | PURGE_TXABORT
      };

      enum _StuffYouCanWaitFor
      {
         waitBreakDetected                       = EV_BREAK,
         waitClearToSendChangedState             = EV_CTS,
         waitDataSetReadyChangedState            = EV_DSR,
         waitLineStatusError                     = EV_ERR,
         waitRing                                = EV_RING,
         waitReceiveLineSignalDetectChangedState = EV_RLSD,
         waitAnyCharacterReceived                = EV_RXCHAR,
         waitParticularCharacterReceived         = EV_RXFLAG,
         waitTransmitBufferEmpty                 = EV_TXEMPTY,
         waitPrinterErrorOccured                 = EV_PERR,
         waitReceiveBuffer80PercentFull          = EV_RX80FULL,
         waitProviderSpecificEvent1              = EV_EVENT1,
         waitProviderSpecificEvent2              = EV_EVENT2
      };

      CString Name; // COM1:9600,n,8,1

      HANDLE FileHandle;

      virtual BOOL  Attach( HANDLE new_handle, HANDLE * old_handle );
      virtual BOOL  CancelWaitFor( void );
      virtual BOOL  ClearBreak( void );
      virtual void  Close( void );
      virtual BOOL  ConfigurationDialog( CCommunicationsConfiguration& configuration, BOOL save_changes = TRUE, HWND parent_window_handle = NULL );
      virtual HANDLE Detach( void );
      virtual DWORD GetBaudRate( void );
      virtual BOOL  GetConfiguration( CCommunicationsConfiguration& configuration );
      virtual DWORD GetFlowControl( void );
      virtual DWORD GetInputBufferSize( void );
      virtual DWORD GetModemStatus( void );
      virtual DWORD GetOutputBufferSize( void );
      virtual BOOL  GetProperties( CCommunicationProperties& properties );
      virtual BOOL  GetState( CDeviceControlBlock& device_control_block );
      virtual BOOL  GetTimeouts( COMMTIMEOUTS& timeouts );
      virtual BOOL  IsDataWaiting( void );
      virtual DWORD NumberOfBytesWaitingToBeRead( void );
      virtual DWORD NumberOfBytesWaitingToBeWritten( void );
      virtual BOOL  Open( void ); // Name already filled, used in re-opening an existing session

#if ! defined( WFC_STL )
      virtual BOOL  Open( LPCTSTR channel_name, UINT open_flags = 0, CFileException* pError = NULL );
#else
      virtual BOOL  Open( LPCTSTR channel_name, UINT open_flags = 0 );
#endif // WFC_STL

      virtual BOOL  Purge( DWORD what_to_purge = purgeAll );
      virtual UINT  Read( void *buffer, UINT length );
      virtual void  ReplaceGarbledCharacter( BOOL yes_or_no = TRUE, BYTE character_to_replace_the_garbled_one_with = ' ' );

#if ! defined( WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual BOOL  SetBaudRate( DWORD baud_rate );
      virtual BOOL  SetBreak( void );
      virtual BOOL  SetCharacterToWaitFor( BYTE character_to_wait_for );
      virtual BOOL  SetDataTerminalReady( BOOL set_DTR_on = TRUE );
      virtual void  SetFlowControl( DWORD flow_control );
      virtual void  SetInputBufferSize( DWORD buffer_size );
      virtual void  SetOutputBufferSize( DWORD buffer_size );
      virtual BOOL  SetPurgeBufferOnError( BOOL purge_buffer = TRUE );
      virtual BOOL  SetRequestToSend( BOOL set_RTS_on = TRUE );
      virtual BOOL  SetState( CDeviceControlBlock& device_control_block );
      virtual BOOL  SetTimeouts( COMMTIMEOUTS * timeouts_p = NULL );
      virtual BOOL  TransmitCharacter( char character_to_transmit );
      virtual BOOL  WaitFor( DWORD& stuff_you_can_wait_for );
      virtual BOOL  WaitForString( const CString& string_to_wait_for, DWORD seconds = 5, CString * what_was_read = NULL );
      virtual void  Write( const CByteArray& bytes );
      virtual void  Write( CString& data_to_write );
      virtual void  Write( const void *buffer, UINT number_of_bytes );
      virtual void  Write( BYTE byte_to_write );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // SERIAL_FILE_CLASS_HEADER
