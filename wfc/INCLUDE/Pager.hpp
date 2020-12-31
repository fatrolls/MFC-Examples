#if ! defined( PAGER_CLASS_HEADER )

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
** $Workfile: Pager.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 5:00a $
*/

#define PAGER_CLASS_HEADER

class CPager
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
   protected:

      CString m_Account;
      CString m_PhoneNumber;
      CString m_Message;
      CString m_SerialSettings;

      DWORD m_ErrorCode;
      DWORD m_NumberOfRetries;

      virtual BOOL m_Send( void ) = 0;

   public:

      CPager();
      CPager( const CPager& source );
      CPager( const CPager * source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CPager();

      virtual void  Copy( const CPager& source );
      virtual void  Copy( const CPager * source );
      virtual void  Empty( void );
      virtual void  GetAccount( CString& account ) const;
      virtual DWORD GetErrorCode( void ) const;
      virtual void  GetMessage( CString& message ) const;
      virtual DWORD GetNumberOfRetries( void ) const;
      virtual void  GetPhoneNumber( CString& phone_number ) const;
      virtual void  GetSerialPort( CString& serial_settings ) const;
      virtual BOOL  Send( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual void  SetAccount( const CString& account );
      virtual void  SetMessage( const CString& message );
      virtual void  SetNumberOfRetries( const DWORD retries );
      virtual void  SetPhoneNumber( const CString& phone_number );
      virtual void  SetSerialPort( const CString& serial_settings );

      // Operators

      virtual CPager& operator = ( const CPager& source );
      
#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

#endif // PAGER_CLASS_HEADER
