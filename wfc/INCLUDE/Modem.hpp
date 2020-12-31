#if ! defined( MODEM_CLASS_HEADER )

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
** $Workfile: modem.hpp $
** $Revision: 9 $
** $Modtime: 1/04/00 5:00a $
*/

#define MODEM_CLASS_HEADER

class CModem : public CSerialFile
{
#if ! defined( WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CModem )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CModem( const CModem& ) {};
      CModem& operator=( const CModem& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      BOOL m_IsConnected;
      BOOL m_UsePulseDialing;

      CString m_PhoneNumber;

   public:

      CModem();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CModem();

      virtual BOOL Connect( DWORD number_of_seonds_to_wait = 30 );
      virtual BOOL Disconnect( void ); // Sends +++ATH
      virtual BOOL IsConnected( void ) const;
      virtual void GetPhoneNumber( CString& phone_number_to_dial ) const;
      virtual void SetPhoneNumber( const CString& phone_number_to_dial );
      
      // MFC Stuff

#if ! defined( WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // MODEM_CLASS_HEADER
