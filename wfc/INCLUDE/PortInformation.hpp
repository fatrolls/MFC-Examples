#if ! defined( PORT_INFORMATION_CLASS_HEADER )

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
** $Workfile: PortInformation.hpp $
** $Revision: 8 $
** $Modtime: 1/04/00 5:00a $
*/

#define PORT_INFORMATION_CLASS_HEADER

class CPortInformation
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CPortInformation )
#endif // WFC_NO_SERIALIZATION

   public:

      CPortInformation();
      CPortInformation( const PORT_INFO_1 * source );
      CPortInformation( const PORT_INFO_2 * source );
      CPortInformation( const CPortInformation& source );

      virtual ~CPortInformation();

      CString Name;
      CString Monitor;
      CString Description;
      DWORD   Type;
      CString TypeName;

      virtual void Copy( const PORT_INFO_1 * source );
      virtual void Copy( const PORT_INFO_2 * source );
      virtual void Copy( const CPortInformation& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual void TypeToString( DWORD type, CString& string ) const;

      virtual CPortInformation& operator = ( const CPortInformation& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};

#endif // PORT_INFORMATION_CLASS_HEADER
