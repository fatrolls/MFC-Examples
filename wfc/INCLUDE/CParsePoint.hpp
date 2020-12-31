#if ! defined ( PARSE_POINT_CLASS_HEADER )

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
** $Workfile: CParsePoint.hpp $
** $Revision: 7 $
** $Modtime: 1/04/00 4:52a $
*/

#define PARSE_POINT_CLASS_HEADER

class CParsePoint
{
   protected:

      DWORD m_ByteIndex;
      DWORD m_LineIndex;
      DWORD m_LineNumber;

   public:

      inline CParsePoint()
      {
         Empty();
      };

      inline CParsePoint( const CParsePoint& source )
      {
         Copy( source );
      };

      inline ~CParsePoint()
      {
         Empty();
      };

      inline CParsePoint& operator=( const CParsePoint& source )
      {
         Copy( source );
         return( *this );
      };

      inline void Copy( const CParsePoint& source )
      {
         m_ByteIndex  = source.m_ByteIndex;
         m_LineIndex  = source.m_LineIndex;
         m_LineNumber = source.m_LineNumber;
      };

      inline void Empty( void )
      {
         m_ByteIndex  = 0;
         m_LineIndex  = 1;
         m_LineNumber = 1;
      };

      inline DWORD GetIndex( void ) const
      {
         return( m_ByteIndex );
      };

      inline DWORD GetLineIndex( void ) const
      {
         return( m_LineIndex );
      };

      inline DWORD GetLineNumber( void ) const
      {
         return( m_LineNumber );
      };

      inline void SetIndex( DWORD index )
      {
         m_ByteIndex = index;
      };

      inline void SetLineIndex( DWORD index )
      {
         m_LineIndex = index;
      };

      inline void SetLineNumber( DWORD index )
      {
         m_LineNumber = index;
      };

      inline void IncrementIndex( int steps = 1 )
      {
         m_ByteIndex += steps;
      };

      inline void IncrementLineIndex( int steps = 1 )
      {
         m_LineIndex += steps;
      };

      inline void IncrementLineNumber( int steps = 1 )
      {
         m_LineNumber += steps;
      };

      inline void AutoIncrement( BYTE character )
      {
         m_ByteIndex++;
         m_LineIndex++;

         if ( character == LINE_FEED )
         {
            m_LineNumber++;
            m_LineIndex = 1;
         }
      };
};   

#endif // PARSE_POINT_CLASS_HEADER
