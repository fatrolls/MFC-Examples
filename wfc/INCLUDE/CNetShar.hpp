#if ! defined( NETWORK_SHARE_CLASS_HEADER )

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
** $Workfile: cnetshar.hpp $
** $Revision: 13 $
** $Modtime: 1/04/00 4:51a $
*/

#define NETWORK_SHARE_CLASS_HEADER

class CNetworkShareInformation
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkShareInformation )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CNetworkShareInformation();
      CNetworkShareInformation( const SHARE_INFO_1 *information_p );
      CNetworkShareInformation( const SHARE_INFO_2 *information_p );
      CNetworkShareInformation( const CNetworkShareInformation& source );
      virtual ~CNetworkShareInformation();

      CString NetworkName;
      DWORD   Type;
      CString Remark;
      DWORD   Permissions;
      DWORD   MaximumNumberOfUses;
      DWORD   CurrentNumberOfUses;
      CString PathName;
      CString Password;

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      virtual void Copy( const SHARE_INFO_1 *source );
      virtual void Copy( const SHARE_INFO_2 *source );
      virtual void Copy( const CNetworkShareInformation& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual const CNetworkShareInformation& operator = ( const CNetworkShareInformation& source );
};

class CNetworkShares : public CNetwork
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkShares )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CNetworkShares( const CNetworkShares& ) {};
      CNetworkShares& operator=( const CNetworkShares& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      /*
      ** Connection information variables
      */

      SHARE_INFO_1 *m_1InformationBuffer;
      SHARE_INFO_2 *m_2InformationBuffer;

      /*
      ** File Information enumeration variables
      */

      DWORD m_1Index;
      DWORD m_1ResumeHandle;
      DWORD m_1CurrentEntryNumber;
      DWORD m_1NumberOfEntriesRead;
      DWORD m_1TotalNumberOfEntries;

      DWORD m_2Index;
      DWORD m_2ResumeHandle;
      DWORD m_2CurrentEntryNumber;
      DWORD m_2NumberOfEntriesRead;
      DWORD m_2TotalNumberOfEntries;

      BOOL m_GetChunk( void );

   public:

      CNetworkShares();
      CNetworkShares( LPCTSTR machine_name );
      virtual ~CNetworkShares();

      virtual BOOL  Add( CNetworkShareInformation& share_to_add );
      virtual DWORD Check( const CString& name_of_device );
      virtual void  Close( void );
      virtual BOOL  Delete( CNetworkShareInformation& share_to_delete );
      virtual BOOL  Enumerate( void );
      virtual BOOL  GetNext( CNetworkShareInformation& information );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
};

#endif // NETWORK_SHARE_CLASS_HEADER
