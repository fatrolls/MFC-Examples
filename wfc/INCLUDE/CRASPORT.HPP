#if ! defined( REMOTE_ACCESS_SERVICE_PORT_DATA_CLASS_HEADER )

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
** $Workfile: CRASPORT.HPP $
** $Revision: 9 $
** $Modtime: 1/04/00 4:54a $
*/

#define REMOTE_ACCESS_SERVICE_PORT_DATA_CLASS_HEADER

class CRemoteAccessServiceConnectionProjection
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CRemoteAccessServiceConnectionProjection )
#endif // WFC_NO_SERIALIZATION

   public:

      // Construction

      CRemoteAccessServiceConnectionProjection();
      CRemoteAccessServiceConnectionProjection( const CRemoteAccessServiceConnectionProjection& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessServiceConnectionProjection();

      // Properties

      DWORD ErrorCode;

      // Methods

      virtual void Copy( const CRemoteAccessServiceConnectionProjection& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG

      // Operators

      virtual CRemoteAccessServiceConnectionProjection& operator = ( const CRemoteAccessServiceConnectionProjection& source );
};

class CNetBEUIFramerProjectionResult : public CRemoteAccessServiceConnectionProjection
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetBEUIFramerProjectionResult )
#endif // WFC_NO_SERIALIZATION

   public:

      CNetBEUIFramerProjectionResult();
      CNetBEUIFramerProjectionResult( const RAS_PPP_NBFCP_RESULT * source );
      CNetBEUIFramerProjectionResult( const CNetBEUIFramerProjectionResult& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CNetBEUIFramerProjectionResult();

      // Properties

      DWORD NetBiosError;
      CString Name;
      CString WorkstationName;

      // Methods

      virtual void Copy( const CNetBEUIFramerProjectionResult& source );
      virtual void Copy( const RAS_PPP_NBFCP_RESULT * source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG

      // Operators

      virtual CNetBEUIFramerProjectionResult& operator = ( const CNetBEUIFramerProjectionResult& source );
};

class CInternetworkPacketExchangeProjectionResult : public CRemoteAccessServiceConnectionProjection
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CInternetworkPacketExchangeProjectionResult )
#endif // WFC_NO_SERIALIZATION

   public:

      CInternetworkPacketExchangeProjectionResult();
      CInternetworkPacketExchangeProjectionResult( const RAS_PPP_IPXCP_RESULT * source );
      CInternetworkPacketExchangeProjectionResult( const CInternetworkPacketExchangeProjectionResult& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CInternetworkPacketExchangeProjectionResult();

      // Properties

      CString Address;

      // Methods

      virtual void Copy( const CInternetworkPacketExchangeProjectionResult& source );
      virtual void Copy( const RAS_PPP_IPXCP_RESULT * source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG

      // Operators

      virtual CInternetworkPacketExchangeProjectionResult& operator = ( const CInternetworkPacketExchangeProjectionResult& source );
};

class CInternetProtocolProjectionResult : public CRemoteAccessServiceConnectionProjection
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CInternetProtocolProjectionResult )
#endif // WFC_NO_SERIALIZATION

   public:

      CInternetProtocolProjectionResult();
      CInternetProtocolProjectionResult( const RAS_PPP_IPCP_RESULT * source );
      CInternetProtocolProjectionResult( const CInternetProtocolProjectionResult& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CInternetProtocolProjectionResult();

      // Properties

      CString Address;

      // Methods

      virtual void Copy( const CInternetProtocolProjectionResult& source );
      virtual void Copy( const RAS_PPP_IPCP_RESULT * source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG

      // Operators

      virtual CInternetProtocolProjectionResult& operator = ( const CInternetProtocolProjectionResult& source );
};

class CAppleTalkProjectionResult : public CRemoteAccessServiceConnectionProjection
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CAppleTalkProjectionResult )
#endif // WFC_NO_SERIALIZATION

   public:

      CAppleTalkProjectionResult();
      CAppleTalkProjectionResult( const RAS_PPP_ATCP_RESULT * source );
      CAppleTalkProjectionResult( const CAppleTalkProjectionResult& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CAppleTalkProjectionResult();

      // Properties

      CString Address;

      // Methods

      virtual void Copy( const CAppleTalkProjectionResult& source );
      virtual void Copy( const RAS_PPP_ATCP_RESULT * source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG

      // Operators

      virtual CAppleTalkProjectionResult& operator = ( const CAppleTalkProjectionResult& source );
};

class CPointToPointProtocolProjectionResult
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CPointToPointProtocolProjectionResult )
#endif // WFC_NO_SERIALIZATION

   public:

      CPointToPointProtocolProjectionResult();
      CPointToPointProtocolProjectionResult( const CPointToPointProtocolProjectionResult& source );
      CPointToPointProtocolProjectionResult( const RAS_PPP_PROJECTION_RESULT * source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CPointToPointProtocolProjectionResult();

      // Properties

      CAppleTalkProjectionResult                  AppleTalk;
      CInternetProtocolProjectionResult           IP;
      CInternetworkPacketExchangeProjectionResult IPX;
      CNetBEUIFramerProjectionResult              NetBEUI;

      // Methods

      virtual void Copy( const CPointToPointProtocolProjectionResult& source );
      virtual void Copy( const RAS_PPP_PROJECTION_RESULT * source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG

      // Operators

      virtual CPointToPointProtocolProjectionResult& operator = ( const CPointToPointProtocolProjectionResult& source );
};

class CRemoteAccessServiceUser
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CRemoteAccessServiceUser )
#endif // WFC_NO_SERIALIZATION

   public:

      CRemoteAccessServiceUser();
      CRemoteAccessServiceUser( const RAS_USER_0 * source );
      CRemoteAccessServiceUser( const CRemoteAccessServiceUser& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessServiceUser();

      // Properties

      BYTE Privileges;
      CString PhoneNumber;

      // Methods

      virtual void Copy( const RAS_USER_0 * source );
      virtual void Copy( const CRemoteAccessServiceUser& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG

      // Operators

      virtual CRemoteAccessServiceUser& operator = ( const CRemoteAccessServiceUser& source );
};

class CRemoteAccessServicePort
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CRemoteAccessServicePort );
#endif // WFC_NO_SERIALIZATION

   public:

      CRemoteAccessServicePort();
      CRemoteAccessServicePort( const RAS_PORT_0 * source );
      CRemoteAccessServicePort( const RAS_PORT_1 * source );
      CRemoteAccessServicePort( const CRemoteAccessServicePort& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessServicePort();

      // Possible values for MediaID

      enum _Media
      {
         mediaUnknown     = MEDIA_UNKNOWN,
         mediaSerial      = MEDIA_SERIAL,
         mediaRAS10Serial = MEDIA_RAS10_SERIAL,
         mediaX25         = MEDIA_X25,
         mediaISDN        = MEDIA_ISDN
      };

      // Properties
      // Patterned after RAS_PORT_x structures

      CString Name;                     // RAS_PORT_0.wszPortName
      CString DeviceType;               // RAS_PORT_0.wszDeviceType
      CString DeviceName;               // RAS_PORT_0.wszDeviceName
      CString MediaName;                // RAS_PORT_0.wszMediaName
      DWORD   MediaID;                  // RAS_PORT_0.MediaID
      DWORD   Flags;                    // RAS_PORT_0.Flags
      CString UserName;                 // RAS_PORT_0.wszUserName
      CString ComputerName;             // RAS_PORT_0.wszComputer
      CTime   SessionStartTime;         // RAS_PORT_0.dwStartSessionTime
      CString LogonDomainName;          // RAS_PORT_0.wszLogonDomain
      BOOL    IsAdvancedServer;         // RAS_PORT_0.fAdvancedServer
      DWORD   LineCondition;            // RAS_PORT_1.LineCondition
      DWORD   HardwareCondition;        // RAS_PORT_1.HardwareCondition
      DWORD   LineSpeedInBitsPerSecond; // RAS_PORT_1.LineSpeed
      WORD    NumberOfStatistics;       // RAS_PORT_1.NumStatistics
      WORD    NumberOfMediaParameters;  // RAS_PORT_1.NumMediaParms
      DWORD   SizeOfMediaParameters;    // RAS_PORT_1.SizeMediaParms
      CPointToPointProtocolProjectionResult ProjectionResult;

      // Methods

      virtual void Copy( const CRemoteAccessServicePort& source );
      virtual void Copy( const RAS_PORT_0 * source );
      virtual void Copy( const RAS_PORT_1 * source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG

      // Operators

      virtual CRemoteAccessServicePort& operator = ( const CRemoteAccessServicePort& source );
};

class CRemoteAccessServicePortStatistics
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CRemoteAccessServicePortStatistics )
#endif // WFC_NO_SERIALIZATION

   public:

      CRemoteAccessServicePortStatistics();
      CRemoteAccessServicePortStatistics( const RAS_PORT_STATISTICS *source );
      CRemoteAccessServicePortStatistics( const CRemoteAccessServicePortStatistics& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessServicePortStatistics();

      // Properties
      // Patterned after RAS_PORT_STATISTICS

      DWORD NumberOfBytesTransmitted;
      DWORD NumberOfBytesReceived;
      DWORD NumberOfFramesTransmitted;
      DWORD NumberOfFramesReceived;
      DWORD NumberOfCRCErrors;
      DWORD NumberOfTimeoutErrors;
      DWORD NumberOfAlignmentErrors;
      DWORD NumberOfHardwareOverrunErrors;
      DWORD NumberOfFramingErrors;
      DWORD NumberOfBufferOverrunErrors;
      DWORD NumberOfBytesTransmittedUncompressed;
      DWORD NumberOfBytesReceivedUncompressed;
      DWORD NumberOfBytesTransmittedCompressed;
      DWORD NumberOfBytesReceivedCompressed;

      // Methods

      virtual int  Compare( const CRemoteAccessServicePortStatistics& source ) const;
      virtual void Copy( const RAS_PORT_STATISTICS *source );
      virtual void Copy( const CRemoteAccessServicePortStatistics& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG

      // Operators

      virtual CRemoteAccessServicePortStatistics& operator = ( const CRemoteAccessServicePortStatistics& source );
      virtual BOOL operator == ( const CRemoteAccessServicePortStatistics& right_port ) const;
      virtual BOOL operator <  ( const CRemoteAccessServicePortStatistics& right_port ) const;
      virtual BOOL operator >  ( const CRemoteAccessServicePortStatistics& right_port ) const;
      virtual BOOL operator <= ( const CRemoteAccessServicePortStatistics& right_port ) const;
      virtual BOOL operator >= ( const CRemoteAccessServicePortStatistics& right_port ) const;
};

#endif // REMOTE_ACCESS_SERVICE_PORT_DATA_CLASS_HEADER
