#if ! defined ( URL_CLASS_HEADER )

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
** $Workfile: curl.hpp $
** $Revision: 10 $
** $Modtime: 1/04/00 4:58a $
*/

#define URL_CLASS_HEADER

class CUniversalNamingConvention;

class CUniformResourceLocator
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CUniformResourceLocator )
#endif // WFC_NO_SERIALIZATION

   public:

      CUniformResourceLocator();
      CUniformResourceLocator( const CUniversalNamingConvention& source );
      CUniformResourceLocator( const CUniformResourceLocator& source );
      CUniformResourceLocator( LPCTSTR source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CUniformResourceLocator();

      /*
      ** Parse stuff like:
      ** telnet://www.microsoft.com:1234
      ** socket://131.26.31.100:6000
      ** http://www.microsoft.com/hello.html
      */

      /*
      ** Data
      */

      CString ProtocolName;
      CString MachineName;
      CString PathName;
      CString PortName;
      CString URL;

      /*
      ** Methods
      */

      virtual int  Compare( const CUniformResourceLocator& source ) const;
      virtual void Copy( const CUniformResourceLocator& source );
      virtual void Copy( const CUniversalNamingConvention& source );
      virtual void Copy( LPCTSTR source );
      virtual void Empty( void );
      virtual void Make( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual BOOL operator == ( const CUniformResourceLocator& right_url ) const;
      virtual CUniformResourceLocator& operator = ( const CUniversalNamingConvention& source );
      virtual CUniformResourceLocator& operator = ( const CUniformResourceLocator& source );
      virtual CUniformResourceLocator& operator = ( LPCTSTR source );

      operator LPCTSTR() const { return( (LPCTSTR) URL ); }

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};   

#endif // URL_CLASS_HEADER
