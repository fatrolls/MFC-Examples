#if ! defined( NET_MESSAGE_CLASS_HEADER )

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
** Copyright, 1999, Samuel R. Blackburn
**
** $Workfile: CNetMesg.hpp $
** $Revision: 4 $
** $Modtime: 9/11/99 7:04a $
*/

#define NET_MESSAGE_CLASS_HEADER

class CMessageInformation
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CMessageInformation )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CMessageInformation();

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      CMessageInformation( MSG_INFO_0 *source );
      CMessageInformation( MSG_INFO_1 *source );
      CMessageInformation( const CMessageInformation& source );
      virtual ~CMessageInformation();

      /*
      ** Patterned after MSG_INFO_1
      */

      CString Name;
      DWORD   ForwardFlag;
      CString ForwardName;

      /*
      ** Can't make Copy take a const pointer because Microsoft screwed up the 
      ** net API header files...
      */

      virtual void Copy( MSG_INFO_0 *source );
      virtual void Copy( MSG_INFO_1 *source );
      virtual void Copy( const CMessageInformation& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
};

class CNetMessage : public CNetwork
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetMessage )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   protected:

      /*
      ** Workstation information variables
      */

      MSG_INFO_0 *m_InformationBuffer0;
      MSG_INFO_1 *m_InformationBuffer1;

      DWORD m_ResumeHandle;
      DWORD m_CurrentEntryNumber;
      DWORD m_NumberOfEntriesRead;
      DWORD m_TotalNumberOfEntries;

   public:

      CNetMessage();
      CNetMessage( LPCTSTR machine_name );
      virtual ~CNetMessage();

      virtual void  Close( void );
      virtual BOOL  Enumerate( void );
      virtual BOOL  GetNext( CMessageInformation& information );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
};

#endif // NET_MESSAGE_CLASS_HEADER
