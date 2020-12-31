#include "ado2xml.h"
#pragma hdrstop

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
** $Workfile: CDatabaseParameters.cpp $
** $Revision: 2 $
** $Modtime: 3/21/00 4:22a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

CDatabaseParameters::CDatabaseParameters()
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::CDatabaseParameters()" ) );
}

CDatabaseParameters::CDatabaseParameters( const CDatabaseParameters& source )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::CDatabaseParameters( CDatabaseParameters& )" ) );

   Copy( source );
}

CDatabaseParameters::~CDatabaseParameters()
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::~CDatabaseParameters()" ) );
   Empty();
}

void CDatabaseParameters::Copy( const CDatabaseParameters& source )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::Copy()" ) );

   if ( &source == this )
   {
      return;
   }

   m_Provider       = source.m_Provider;
   m_UserID         = source.m_UserID;
   m_Password       = source.m_Password;
   m_DataSource     = source.m_DataSource;
   m_InitialCatalog = source.m_InitialCatalog;
}

void CDatabaseParameters::Empty( void )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::Empty()" ) );

   m_Provider.Empty();
   m_UserID.Empty();
   m_Password.Empty();
   m_DataSource.Empty();
   m_InitialCatalog.Empty();
}

CDatabaseParameters& CDatabaseParameters::operator=( const CDatabaseParameters& source )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::operator=()" ) );
   Copy( source );
   return( *this );
}

void CDatabaseParameters::GetDataSource( CString& return_value ) const
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::GetDataSource()" ) );
   return_value = m_DataSource;
}

void CDatabaseParameters::GetInitialCatalog( CString& return_value ) const
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::GetInitialCatalog()" ) );
   return_value = m_InitialCatalog;
}

void CDatabaseParameters::GetPassword( CString& return_value ) const
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::GetPassword()" ) );
   return_value = m_Password;
}

void CDatabaseParameters::GetProvider( CString& return_value ) const
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::GetProvider()" ) );
   return_value = m_Provider;
}

void CDatabaseParameters::GetUserID( CString& return_value ) const
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::GetUserID()" ) );
   return_value = m_UserID;
}

void CDatabaseParameters::SetDataSource( LPCTSTR set_string )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::SetDataSource()" ) );
   m_DataSource = set_string;
}

void CDatabaseParameters::SetInitialCatalog( LPCTSTR set_string )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::SetInitialCatalog()" ) );
   m_InitialCatalog = set_string;
}

void CDatabaseParameters::SetPassword( LPCTSTR set_string )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::SetPassword()" ) );
   m_Password = set_string;
}

void CDatabaseParameters::SetProvider( LPCTSTR set_string )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::SetProvier()" ) );
   m_Provider = set_string;
}

void CDatabaseParameters::SetUserID( LPCTSTR set_string )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::SetUserID()" ) );
   m_UserID = set_string;
}

void CDatabaseParameters::SetConnectionString( LPCTSTR set_string )
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::SetConnectionString()" ) );
   m_ConnectionString = set_string;
}

void CDatabaseParameters::GetConnectionString( CString& return_value ) const
{
   WFCTRACEINIT( TEXT( "CDatabaseParameters::GetConnectionString()" ) );

   if ( m_ConnectionString.GetLength() > 0 )
   {
      // The user already specified a connection string, return
      // that one

      return_value = m_ConnectionString;
      return;
   }

   CString temporary_string;

   return_value.Empty();

   GetProvider( temporary_string );

   if ( temporary_string.GetLength() > 0 )
   {
      return_value += TEXT( "Provider=" );
      return_value += temporary_string;
      return_value += TEXT( ";" );
   }

   GetDataSource( temporary_string );

   if ( temporary_string.GetLength() > 0 )
   {
      return_value += TEXT( "Data Source=" );
      return_value += temporary_string;
      return_value += TEXT( ";" );
   }

   GetInitialCatalog( temporary_string );

   if ( temporary_string.GetLength() > 0 )
   {
      return_value += TEXT( "Initial Catalog=" );
      return_value += temporary_string;
      return_value += TEXT( ";" );
   }

   GetUserID( temporary_string );

   if ( temporary_string.GetLength() > 0 )
   {
      return_value += TEXT( "User Id=" );
      return_value += temporary_string;
      return_value += TEXT( ";" );
   }

   DWORD user_id_length = temporary_string.GetLength();

   GetPassword( temporary_string );

   if ( temporary_string.GetLength() > 0 ||
        user_id_length > 0 )
   {
      return_value += TEXT( "Password=" );
      return_value += temporary_string;
      return_value += TEXT( ";" );
   }
}