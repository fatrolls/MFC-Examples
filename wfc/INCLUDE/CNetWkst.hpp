#if ! defined( NET_WORKSTATION_CLASS_HEADER )

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
** $Workfile: cnetwkst.hpp $
** $Revision: 12 $
** $Modtime: 1/04/00 4:51a $
*/

#define NET_WORKSTATION_CLASS_HEADER

class CWorkstationUser
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CWorkstationUser )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CWorkstationUser();

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      CWorkstationUser( const WKSTA_USER_INFO_1 *source );
      CWorkstationUser( const CWorkstationUser& source );
      virtual ~CWorkstationUser();

      /*
      ** Patterned after WKSTA_USER_INFO_1
      */

      CString UserName;
      CString LogonDomain;
      CString OtherDomains;
      CString LogonServer;

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      virtual void Copy( const WKSTA_USER_INFO_1 *source );
      virtual void Copy( const CWorkstationUser& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual const CWorkstationUser& operator = ( const CWorkstationUser& source );
};

class CWorkstationInformation
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CWorkstationInformation )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CWorkstationInformation();

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      CWorkstationInformation( const WKSTA_INFO_100 *source );
      CWorkstationInformation( const WKSTA_INFO_101 *source );
      CWorkstationInformation( const WKSTA_INFO_102 *source );
      CWorkstationInformation( const CWorkstationInformation& source );
      virtual ~CWorkstationInformation();

      /*
      ** Patterned after WKSTA_INFO_102
      */

      DWORD   PlatformID;
      CString ComputerName;
      CString LANGroup;
      DWORD   MajorVersion;
      DWORD   MinorVersion;
      CString LANRoot;
      DWORD   NumberOfLoggedOnUsers;

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      virtual void Copy( const WKSTA_INFO_100 *source );
      virtual void Copy( const WKSTA_INFO_101 *source );
      virtual void Copy( const WKSTA_INFO_102 *source );
      virtual void Copy( const CWorkstationInformation& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual const CWorkstationInformation& operator = ( const CWorkstationInformation& source );
};

class CWorkstationTransport
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CWorkstationTransport )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CWorkstationTransport();

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      CWorkstationTransport( const WKSTA_TRANSPORT_INFO_0 *source );
      CWorkstationTransport( const CWorkstationTransport& source );
      virtual ~CWorkstationTransport();

      /*
      ** Patterned after WKSTA_USER_INFO_1
      */

      DWORD   QualityOfService;
      DWORD   NumberOfVirtualCircuits;
      CString Name;
      CString Address;
      BOOL    WANish;

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      virtual void Copy( const WKSTA_TRANSPORT_INFO_0 *source );
      virtual void Copy( const CWorkstationTransport& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual const CWorkstationTransport& operator = ( const CWorkstationTransport& source );
};

class CNetWorkstation : public CNetwork
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetWorkstation )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CNetWorkstation( const CNetWorkstation& ) {};
      CNetWorkstation& operator=( const CNetWorkstation& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      /*
      ** Workstation information variables
      */

      WKSTA_INFO_100 *m_InformationBuffer100;
      WKSTA_INFO_101 *m_InformationBuffer101;
      WKSTA_INFO_102 *m_InformationBuffer102;

      /*
      ** Transport enumeration variables
      */

      WKSTA_TRANSPORT_INFO_0 *m_TransportBuffer;
      DWORD m_TransportResumeHandle;
      DWORD m_TransportCurrentEntryNumber;
      DWORD m_TransportNumberOfEntriesRead;
      DWORD m_TransportTotalNumberOfEntries;

      /*
      ** User enumeration variables
      */

      WKSTA_USER_INFO_1 *m_UserBuffer;
      DWORD m_UserResumeHandle;
      DWORD m_UserCurrentEntryNumber;
      DWORD m_UserNumberOfEntriesRead;
      DWORD m_UserTotalNumberOfEntries;

   public:

      CNetWorkstation();
      CNetWorkstation( LPCTSTR machine_name );
      virtual ~CNetWorkstation();

      virtual void  Close( void );
      virtual BOOL  EnumerateInformation( void );
      virtual BOOL  EnumerateTransports( void );
      virtual BOOL  EnumerateUsers( void );
      virtual BOOL  GetCurrentUser( CWorkstationUser& information );
      virtual BOOL  GetNext( CWorkstationInformation& information );
      virtual BOOL  GetNext( CWorkstationTransport& information );
      virtual BOOL  GetNext( CWorkstationUser& information );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
};

#endif // NET_WORKSTATION_CLASS_HEADER
