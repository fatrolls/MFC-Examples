#if ! defined( NETWORK_FILE_CLASS_HEADER )

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
** $Workfile: cnetfile.hpp $
** $Revision: 12 $
** $Modtime: 1/04/00 4:51a $
*/

#define NETWORK_FILE_CLASS_HEADER

class CNetworkFileInformation
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkFileInformation )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CNetworkFileInformation();

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      CNetworkFileInformation( const FILE_INFO_3 *information_p );
      CNetworkFileInformation( const CNetworkFileInformation& source );
      virtual ~CNetworkFileInformation();

      DWORD   ID;
      DWORD   Permissions;
      DWORD   NumberOfLocks;
      CString PathName;
      CString UserName;

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      virtual void Copy( const FILE_INFO_3 *source );
      virtual void Copy( const CNetworkFileInformation& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual const CNetworkFileInformation& operator = ( const CNetworkFileInformation& source );
};

class CNetworkFiles : public CNetwork
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkFiles )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CNetworkFiles( const CNetworkFiles& ) {};
      CNetworkFiles& operator=( const CNetworkFiles& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      /*
      ** Workstation information variables
      */

      FILE_INFO_3 *m_103InformationBuffer;

      /*
      ** File Information enumeration variables
      */

      DWORD m_103Index;
      DWORD m_103ResumeHandle;
      DWORD m_103CurrentEntryNumber;
      DWORD m_103NumberOfEntriesRead;
      DWORD m_103TotalNumberOfEntries;

      BOOL m_GetChunk( void );

   public:

      CNetworkFiles();
      CNetworkFiles( LPCTSTR machine_name );
      virtual ~CNetworkFiles();

      virtual void  Close( void );
      virtual BOOL  Close( CNetworkFileInformation& file_to_close );
      virtual BOOL  Enumerate( void );
      virtual BOOL  GetNext( CNetworkFileInformation& information );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
};

#endif // NETWORK_FILE_CLASS_HEADER
