#include <wfc.h>
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
** $Workfile: CNetworkResourceInformation.cpp $
** $Revision: 6 $
** $Modtime: 1/04/00 5:18a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkResourceInformation, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkResourceInformation::CNetworkResourceInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkResourceInformation::CNetworkResourceInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkResourceInformation::CNetworkResourceInformation( const NETRESOURCE *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkResourceInformation::CNetworkResourceInformation( NETRESOURCE )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkResourceInformation::CNetworkResourceInformation( const CNetworkResourceInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkResourceInformation::CNetworkResourceInformation( CNetworkResourceInformation )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkResourceInformation::~CNetworkResourceInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkResourceInformation::~CNetworkResourceInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CNetworkResourceInformation::Copy( const NETRESOURCE *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkResourceInformation::Copy()" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      if ( source->lpLocalName != (LPTSTR) NULL )
      {
         LocalName = source->lpLocalName;
      }
      else
      {
         LocalName.Empty();
      }

      if ( source->lpRemoteName != (LPTSTR) NULL )
      {
         RemoteName = source->lpRemoteName;
      }
      else
      {
         RemoteName.Empty();
      }

      if ( source->lpComment != (LPTSTR) NULL )
      {
         Comment = source->lpComment;
      }
      else
      {
         Comment.Empty();
      }

      if ( source->lpProvider != (LPTSTR) NULL )
      {
         Provider = source->lpProvider;
      }                               
      else
      {
         Provider.Empty();
      }

      Scope       = source->dwScope;
      Type        = source->dwType;
      DisplayType = source->dwDisplayType;
      Usage       = source->dwUsage;
   }
   catch( ... )
   {
      Empty();
   }
}

void CNetworkResourceInformation::Copy( const CNetworkResourceInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkResourceInformation::Copy()" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   LocalName   = source.LocalName;
   RemoteName  = source.RemoteName;
   Comment     = source.Comment;
   Provider    = source.Provider;
   Scope       = source.Scope;
   Type        = source.Type;
   DisplayType = source.DisplayType;
   Usage       = source.Usage;
}

void CNetworkResourceInformation::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkResourceInformation::Empty()" ) );
   m_Initialize();
}

void CNetworkResourceInformation::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkResourceInformation::m_Initialize()" ) );

   LocalName.Empty();
   RemoteName.Empty();
   Comment.Empty();
   Provider.Empty();
   Scope       = 0;
   Type        = 0;
   DisplayType = 0;
   Usage       = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkResourceInformation::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkResourceInformation::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << LocalName;
      archive << RemoteName;
      archive << Comment;
      archive << Provider;
      archive << Scope;
      archive << Type;
      archive << DisplayType;
      archive << Usage;
   }
   else
   {
      archive >> LocalName;
      archive >> RemoteName;
      archive >> Comment;
      archive >> Provider;
      archive >> Scope;
      archive >> Type;
      archive >> DisplayType;
      archive >> Usage;
   }
}

#endif // WFC_NO_SERIALIZATION

// End of source
