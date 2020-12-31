#if ! defined( NET_SESSION_CLASS_HEADER )

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
** $Workfile: cnetsess.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 4:51a $
*/

#define NET_SESSION_CLASS_HEADER

class CNetworkSessionInformation
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkSessionInformation )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CNetworkSessionInformation();
      CNetworkSessionInformation( const SESSION_INFO_502 *source );
      CNetworkSessionInformation( const CNetworkSessionInformation& source );
      virtual ~CNetworkSessionInformation();

      /*
      ** Patterned after SESSION_INFO_502
      */

      CString   ClientName;
      CString   UserName;
      DWORD     NumberOfOpens;
      CTimeSpan Time;
      CTimeSpan IdleTime;
      DWORD     UserFlags;
      CString   ClientTypeName;
      CString   Transport;

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      virtual void Copy( const SESSION_INFO_502 *source );
      virtual void Copy( const CNetworkSessionInformation& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
};

class CNetworkSessions : public CNetwork
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkSessions )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CNetworkSessions( const CNetworkSessions& ) {};
      CNetworkSessions& operator=( const CNetworkSessions& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      CString m_ServerName;
      CString m_ClientName;

      BOOL m_Retrieved0;
      BOOL m_Retrieved1;
      BOOL m_Retrieved2;
      BOOL m_Retrieved10;
      BOOL m_Retrieved502;

      DWORD m_ResumeHandle;

      virtual void m_Get_0_Data( void );
      virtual void m_Get_1_Data( void );
      virtual void m_Get_2_Data( void );
      virtual void m_Get_10_Data( void );
      virtual void m_Get_502_Data( void );

   public:

      CNetworkSessions();
      CNetworkSessions( LPCTSTR machine_name );
      virtual ~CNetworkSessions();

      virtual void  Close( void );
      virtual BOOL  Delete( CNetworkSessionInformation& session_to_delete );
      virtual BOOL  Enumerate( CNetworkSessionInformation& information );
      virtual BOOL  GetNext( CNetworkSessionInformation& information );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
};

#endif // NET_SESSION_CLASS_HEADER
