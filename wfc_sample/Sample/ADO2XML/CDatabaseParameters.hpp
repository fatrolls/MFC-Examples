#if ! defined( DATABASE_PARAMETERS_HEADER_FILE )

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
** $Workfile: CDatabaseParameters.hpp $
** $Revision: 2 $
** $Modtime: 3/21/00 4:21a $
** $Reuse Tracing Code: 1 $
*/

#define DATABASE_PARAMETERS_HEADER_FILE

class CDatabaseParameters
{
   protected:

      CString m_Provider;
      CString m_UserID;
      CString m_Password;
      CString m_DataSource;
      CString m_InitialCatalog;
      CString m_ConnectionString;

   public:

      CDatabaseParameters();
      CDatabaseParameters( const CDatabaseParameters& source );
     ~CDatabaseParameters();

      // General bee-a-good-object methods

      void Empty( void );
      void Copy( const CDatabaseParameters& source );
      CDatabaseParameters& operator=( const CDatabaseParameters& source );

      // Data IO methods

      void GetProvider( CString& return_value ) const;
      void GetUserID( CString& return_value ) const;
      void GetPassword( CString& return_value ) const;
      void GetDataSource( CString& return_value ) const;
      void GetInitialCatalog( CString& return_value ) const;

      void SetProvider( LPCTSTR set_string );
      void SetUserID( LPCTSTR set_string );
      void SetPassword( LPCTSTR set_string );
      void SetDataSource( LPCTSTR set_string );
      void SetInitialCatalog( LPCTSTR set_string );
      void SetConnectionString( LPCTSTR set_string );

      // The reason for the class...

      void GetConnectionString( CString& return_value ) const;
};

#endif // DATABASE_PARAMETERS_HEADER_FILE
