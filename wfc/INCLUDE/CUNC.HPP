#if ! defined ( UNC_CLASS_HEADER )

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
** $Workfile: cunc.hpp $
** $Revision: 10 $
** $Modtime: 1/04/00 4:58a $
*/

#define UNC_CLASS_HEADER

class CUniformResourceLocator;

class CUniversalNamingConvention
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CUniversalNamingConvention )
#endif // WFC_NO_SERIALIZATION

   public:

      CUniversalNamingConvention();
      CUniversalNamingConvention( const CUniversalNamingConvention& source );
      CUniversalNamingConvention( const CUniformResourceLocator& source );
      CUniversalNamingConvention( LPCTSTR source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CUniversalNamingConvention();

      /*
      ** Parse stuff like:
      ** \\buckaroo\public\neato\readme.txt
      */

      /*
      ** Data
      */

      CString ServerName;
      CString ShareName;
      CString PathName;
      CString UNC;

      /*
      ** Methods
      */

      virtual int  Compare( const CUniversalNamingConvention& source ) const;
      virtual void Copy( LPCTSTR source );
      virtual void Copy( const CUniversalNamingConvention& source );
      virtual void Copy( const CUniformResourceLocator& source );
      virtual void Empty( void );
      virtual void Make( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual BOOL operator == ( const CUniversalNamingConvention& right_unc ) const;
      virtual CUniversalNamingConvention& operator = ( const CUniversalNamingConvention& source );
      virtual CUniversalNamingConvention& operator = ( const CUniformResourceLocator& source );
      virtual CUniversalNamingConvention& operator = ( LPCTSTR source );

      operator LPCTSTR() const { return( (LPCTSTR) UNC ); }

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
      virtual void Dump( CDumpContext& dump_context ) const;
#endif // _DEBUG
};   

#endif // UNC_CLASS_HEADER
