#if ! defined ( FILE_TIME_CLASS_HEADER )

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
** $Workfile: CFileTime.hpp $
** $Revision: 10 $
** $Modtime: 1/04/00 4:46a $
*/

#define FILE_TIME_CLASS_HEADER

class CSystemTime;

class CFileTime : public _FILETIME
{
   public:

      CFileTime();
      CFileTime( const CFileTime& source );
      CFileTime( const CSystemTime& source );
      CFileTime( WORD ms_dos_date, WORD ms_dos_time );
      CFileTime( const FILETIME * source );
      CFileTime( const SYSTEMTIME * source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CFileTime();

      virtual LONG Compare( const CFileTime& source ) const;

      virtual void Copy( const CFileTime& source );
      virtual void Copy( const CSystemTime& source );
      virtual void Copy( const FILETIME * source );
      virtual void Copy( const SYSTEMTIME * source );
      virtual void Copy( WORD ms_dos_date, WORD ms_dos_time );

#if ! defined( WFC_STL )
      virtual void CopyTo( COleDateTime& destination ) const;
#endif // WFC_STL

      virtual void CopyTo( CTime&        destination ) const;

      virtual void Empty( void );

      /*
      ** Operators
      */

      virtual BOOL operator == ( const CFileTime& source ) const;
      virtual BOOL operator <  ( const CFileTime& source ) const;
      virtual BOOL operator >  ( const CFileTime& source ) const;
      virtual CFileTime& operator = ( const CFileTime& source );
      virtual CFileTime& operator = ( const CSystemTime& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};   

#endif // FILE_TIME_CLASS_HEADER
