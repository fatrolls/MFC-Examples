#if ! defined ( SYSTEM_TIME_CLASS_HEADER )

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
** $Workfile: CSystemTime.hpp $
** $Revision: 14 $
** $Modtime: 1/04/00 4:54a $
*/

#define SYSTEM_TIME_CLASS_HEADER

// Thanks go to Dean Grimm (dean@cortron.com) for suggesting
// the SQL date/time types in CSystemTime

class CFileTime;

class CSystemTime : public _SYSTEMTIME
{
   public:

      CSystemTime();
      CSystemTime( const CSystemTime& source );
      CSystemTime( const CFileTime& source );
      CSystemTime( const CTime& source );

#if ! defined( WFC_STL )
      CSystemTime( const COleDateTime& source );
#endif // WFC_STL

      CSystemTime( const SYSTEMTIME * source );
      CSystemTime( const FILETIME * source );
      CSystemTime( const TIME_OF_DAY_INFO * source );
      CSystemTime( const TIMESTAMP_STRUCT * source ); // from sqltypes.h

      virtual ~CSystemTime();

      /*
      ** Unfortunately, I can't call this GetCurrentTime (like in CTime)
      ** because Microsoft #define's it in winbase.h and it royally screws me.
      */

      static CSystemTime GetTheCurrentTime( void );

      virtual void Empty( void );

      virtual LONG Compare( const CSystemTime& source ) const;

      virtual void Copy( const CSystemTime&       source );
      virtual void Copy( const CFileTime&         source );
      virtual void Copy( const CTime&             source );

#if ! defined( WFC_STL )
      virtual void Copy( const COleDateTime&      source );
#endif // WFC_STL

      virtual void Copy( const SYSTEMTIME *       source );
      virtual void Copy( const FILETIME *         source );
      virtual void Copy( const TIME_OF_DAY_INFO * source );
      virtual void Copy( const TIMESTAMP_STRUCT * source ); // from sqltypes.h

#if ! defined( WFC_STL )
      virtual void CopyTo( COleDateTime&      destination ) const;
#endif // WFC_STL

      virtual void CopyTo( CTime&             destination ) const;
      virtual void CopyTo( TIMESTAMP_STRUCT * destination ) const;

      virtual void Get( void );
      virtual BOOL Set( void ) const;

      /*
      ** Operators
      */

      virtual CSystemTime& operator = ( const CSystemTime&  source );
      virtual CSystemTime& operator = ( const CFileTime&    source );
      virtual CSystemTime& operator = ( const CTime&        source );

#if ! defined( WFC_STL )
      virtual CSystemTime& operator = ( const COleDateTime& source );
#endif // WFC_STL

      virtual BOOL operator == ( const CSystemTime& source ) const;
      virtual BOOL operator >  ( const CSystemTime& source ) const;
      virtual BOOL operator <  ( const CSystemTime& source ) const;

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // SYSTEM_TIME_CLASS_HEADER
