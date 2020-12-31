#if ! defined( NETWORK_USER_CLASS_HEADER )

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
** $Workfile: cnetuser.hpp $
** $Revision: 13 $
** $Modtime: 1/04/00 4:51a $
*/

#define NETWORK_USER_CLASS_HEADER

class CNetworkUserInformation
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkUserInformation )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CNetworkUserInformation();
      CNetworkUserInformation( const USER_INFO_0  *information_p );
      CNetworkUserInformation( const USER_INFO_1  *information_p );
      CNetworkUserInformation( const USER_INFO_2  *information_p );
      CNetworkUserInformation( const USER_INFO_3  *information_p );
      CNetworkUserInformation( const USER_INFO_10 *information_p );
      CNetworkUserInformation( const USER_INFO_11 *information_p );
      CNetworkUserInformation( const USER_INFO_20 *information_p );
      CNetworkUserInformation( const USER_INFO_21 *information_p );
      CNetworkUserInformation( const USER_INFO_22 *information_p );
      CNetworkUserInformation( const CNetworkUserInformation& source );
      CNetworkUserInformation( const CNetworkUserInformation *source );

      virtual ~CNetworkUserInformation();

      enum _Priveleges
      {
         privilegeGuest         = USER_PRIV_GUEST,
         privilegeUser          = USER_PRIV_USER,
         privilegeAdministrator = USER_PRIV_ADMIN
      };

      CString    Name;
      CString    Password;
      CByteArray EncryptedPassword;
      CTimeSpan  PasswordAge;
      DWORD      Privileges;
      CString    HomeDirectory;
      CString    Comment;
      DWORD      Flags;
      CString    ScriptPath;
      DWORD      AuthenticationFlags;
      CString    FullName;
      CString    UserComment;
      CString    Parameters;
      CString    Workstations;
      CTime      LastLogon;
      CTime      LastLogoff;
      CTime      AccountExpires;
      DWORD      MaximumStorage;
      DWORD      UnitsPerWeek;
      CByteArray LogonHours;
      DWORD      BadPasswordCount;
      DWORD      NumberOfLogons;
      CString    LogonServer;
      DWORD      CountryCode;
      DWORD      CodePage;
      DWORD      UserID;
      DWORD      PrimaryGroupID;
      CString    HomeDirectoryDrive;
      CString    Profile;
      DWORD      PasswordHasExpired;

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      virtual void Copy( const USER_INFO_0  *source );
      virtual void Copy( const USER_INFO_1  *source );
      virtual void Copy( const USER_INFO_2  *source );
      virtual void Copy( const USER_INFO_3  *source );
      virtual void Copy( const USER_INFO_10 *source );
      virtual void Copy( const USER_INFO_11 *source );
      virtual void Copy( const USER_INFO_20 *source );
      virtual void Copy( const USER_INFO_21 *source );
      virtual void Copy( const USER_INFO_22 *source );
      virtual void Copy( const CNetworkUserInformation& source );
      virtual void Copy( const CNetworkUserInformation *source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual void SetAddDefaults( void );
      virtual const CNetworkUserInformation& operator = ( const CNetworkUserInformation& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

class CNetworkUsers : public CNetwork
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkUsers )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CNetworkUsers( const CNetworkUsers& ) {};
      CNetworkUsers& operator=( const CNetworkUsers& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      /*
      ** Connection information variables
      */

      USER_INFO_0  *m_0InformationBuffer;
      USER_INFO_1  *m_1InformationBuffer;
      USER_INFO_2  *m_2InformationBuffer;
      USER_INFO_3  *m_3InformationBuffer;
      USER_INFO_10 *m_10InformationBuffer;

      /*
      ** File Information enumeration variables
      */

      DWORD m_0Index;
      DWORD m_0ResumeHandle;
      DWORD m_0CurrentEntryNumber;
      DWORD m_0NumberOfEntriesRead;
      DWORD m_0TotalNumberOfEntries;

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

      DWORD m_3Index;
      DWORD m_3ResumeHandle;
      DWORD m_3CurrentEntryNumber;
      DWORD m_3NumberOfEntriesRead;
      DWORD m_3TotalNumberOfEntries;

      DWORD m_10Index;
      DWORD m_10ResumeHandle;
      DWORD m_10CurrentEntryNumber;
      DWORD m_10NumberOfEntriesRead;
      DWORD m_10TotalNumberOfEntries;

      BOOL m_GetChunk( void );

   public:

      CNetworkUsers();
      CNetworkUsers( LPCTSTR machine_name );
      virtual ~CNetworkUsers();

      enum _AccountTypes
      {
         accountBackupDomainController = UF_SERVER_TRUST_ACCOUNT,
         accountMachine                = UF_WORKSTATION_TRUST_ACCOUNT,
         accountInterdomain            = UF_INTERDOMAIN_TRUST_ACCOUNT
      };

      virtual BOOL  Add( const CNetworkUserInformation& user_to_add );
      virtual void  Close( void );
      virtual BOOL  CreateComputerAccount( LPCTSTR computer_name = NULL, DWORD type = accountMachine );
      virtual BOOL  Delete( const CNetworkUserInformation& user_to_delete );
      virtual BOOL  Delete( const CString& user_to_delete );
      virtual BOOL  Enumerate( void );
      virtual DWORD GetLevel( void ) const;
      virtual BOOL  GetNext( CNetworkUserInformation& information );
};

#endif // NETWORK_USER_CLASS_HEADER
