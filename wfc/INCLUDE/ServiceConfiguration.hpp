#if ! defined( SERVICE_CONFIGURATION_CLASS_HEADER )

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
** $Workfile: ServiceConfiguration.hpp $
** $Revision: 10 $
** $Modtime: 1/04/00 5:00a $
*/

#define SERVICE_CONFIGURATION_CLASS_HEADER

class CServiceConfigurationA
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CServiceConfigurationA )
#endif // WFC_NO_SERIALIZATION

   protected:

      DWORD   m_TypeOfService;
      DWORD   m_WhenToStart;
      DWORD   m_ErrorControl;
      DWORD   m_Tag;
      CString m_NameOfExecutableFile;
      CString m_LoadOrderGroup;
      CString m_StartName;
      CString m_DisplayName;

      CStringArray m_Dependencies;

   public:

      CServiceConfigurationA();
      CServiceConfigurationA( const _QUERY_SERVICE_CONFIGA& source );
      CServiceConfigurationA( const _QUERY_SERVICE_CONFIGA * source );
      CServiceConfigurationA( const CServiceConfigurationA& source );
      CServiceConfigurationA( const CServiceConfigurationA * source );
      virtual ~CServiceConfigurationA();

      virtual void  Copy( const _QUERY_SERVICE_CONFIGA& source );
      virtual void  Copy( const _QUERY_SERVICE_CONFIGA * source );
      virtual void  Copy( const CServiceConfigurationA& source );
      virtual void  Copy( const CServiceConfigurationA * source );
      virtual void  Empty( void );
      virtual void  GetDependencies( CStringArray& dependencies ) const;
      virtual void  GetDisplayName( CString& display_name ) const;
      virtual DWORD GetErrorControl( void ) const;
      virtual void  GetLoadOrderGroup( CString& load_order_group ) const;
      virtual void  GetNameOfExecutableFile( CString& name_of_executable ) const;
      virtual void  GetStartName( CString& start_name ) const;
      virtual DWORD GetTag( void ) const;
      virtual DWORD GetTypeOfService( void ) const;
      virtual DWORD GetWhenToStart( void ) const;
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual CServiceConfigurationA& operator=( const CServiceConfigurationA& source );
      virtual CServiceConfigurationA& operator=( const _QUERY_SERVICE_CONFIGA& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

class CServiceConfigurationW
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CServiceConfigurationW );
#endif // WFC_NO_SERIALIZATION

   protected:

      DWORD   m_TypeOfService;
      DWORD   m_WhenToStart;
      DWORD   m_ErrorControl;
      DWORD   m_Tag;
      CString m_NameOfExecutableFile;
      CString m_LoadOrderGroup;
      CString m_StartName;
      CString m_DisplayName;

      CStringArray m_Dependencies;

   public:

      CServiceConfigurationW();
      CServiceConfigurationW( const _QUERY_SERVICE_CONFIGW&  source );
      CServiceConfigurationW( const _QUERY_SERVICE_CONFIGW * source );
      CServiceConfigurationW( const CServiceConfigurationW&  source );
      CServiceConfigurationW( const CServiceConfigurationW * source );
      virtual ~CServiceConfigurationW();

      virtual void  Copy( const _QUERY_SERVICE_CONFIGW& source );
      virtual void  Copy( const _QUERY_SERVICE_CONFIGW * source );
      virtual void  Copy( const CServiceConfigurationW& source );
      virtual void  Copy( const CServiceConfigurationW * source );
      virtual void  Empty( void );
      virtual void  GetDependencies( CStringArray& dependencies ) const;
      virtual void  GetDisplayName( CString& display_name ) const;
      virtual DWORD GetErrorControl( void ) const;
      virtual void  GetLoadOrderGroup( CString& load_order_group ) const;
      virtual void  GetNameOfExecutableFile( CString& name_of_executable ) const;
      virtual void  GetStartName( CString& start_name ) const;
      virtual DWORD GetTag( void ) const;
      virtual DWORD GetTypeOfService( void ) const;
      virtual DWORD GetWhenToStart( void ) const;
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual CServiceConfigurationW& operator=( const CServiceConfigurationW& source );
      virtual CServiceConfigurationW& operator=( const _QUERY_SERVICE_CONFIGW& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};


#if defined( UNICODE )
#define CServiceConfiguration CServiceConfigurationW
#else
#define CServiceConfiguration CServiceConfigurationA
#endif // UNICODE

#endif // SERVICE_CONFIGURATION_CLASS_HEADER
