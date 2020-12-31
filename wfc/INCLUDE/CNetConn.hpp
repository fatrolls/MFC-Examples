#if ! defined( NETWORK_CONNECTION_CLASS_HEADER )

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
** $Workfile: cnetconn.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 4:51a $
*/

#define NETWORK_CONNECTION_CLASS_HEADER

class CNetworkConnectionInformation
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkConnectionInformation )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CNetworkConnectionInformation();

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      CNetworkConnectionInformation( const CONNECTION_INFO_1 *information_p );
      CNetworkConnectionInformation( const CNetworkConnectionInformation& source );
      virtual ~CNetworkConnectionInformation();

      DWORD   ID;
      DWORD   Type;
      DWORD   NumberOfUsers;
      DWORD   NumberOfOpens;
      DWORD   Time;
      CString UserName;
      CString NetName;

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      virtual void Copy( const CONNECTION_INFO_1 *source );
      virtual void Copy( const CNetworkConnectionInformation& source );
      virtual void Empty( void );

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual const CNetworkConnectionInformation& operator=( const CNetworkConnectionInformation& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

class CNetworkConnections : public CNetwork
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkConnections )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CNetworkConnections( const CNetworkConnections& ) {};
      CNetworkConnections& operator=( const CNetworkConnections& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      /*
      ** Connection information variables
      */

      CONNECTION_INFO_1 * m_1InformationBuffer;

      /*
      ** File Information enumeration variables
      */

      DWORD m_1Index;
      DWORD m_1ResumeHandle;
      DWORD m_1CurrentEntryNumber;
      DWORD m_1NumberOfEntriesRead;
      DWORD m_1TotalNumberOfEntries;

      BOOL m_GetChunk( void );

      WCHAR m_WideShareOrComputerName[ MAX_PATH ];

public:

      CNetworkConnections();
      CNetworkConnections( LPCTSTR machine_name );
      virtual ~CNetworkConnections();

      virtual void  Close( void );
      virtual BOOL  Enumerate( LPCTSTR share_or_computer_name );
      virtual BOOL  GetNext( CNetworkConnectionInformation& information );

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

#endif // NETWORK_CONNECTION_CLASS_HEADER
