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
** $Workfile: STL_CWordArray.cpp $
** $Revision: 3 $
** $Modtime: 5/12/00 7:08p $
*/

#if defined( WFC_STL )

// Get rid of a ton of warnings

#pragma warning( disable : 4710 4702 )

// Now start picking up the STL stuff

#include <vector>
#include <algorithm>

using namespace std;

CWordArray::CWordArray()
{
   m_Array = new vector< ARRAY_TYPE >;
}

CWordArray::~CWordArray()
{
   if ( m_Array != NULL )
   {
      vector< ARRAY_TYPE > * temp_pointer = reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array );
      delete temp_pointer;
      m_Array = NULL;
   }
}

int CWordArray::Add( CWordArray::ARRAY_TYPE new_element )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->push_back( new_element );
   return( GetUpperBound() );
}

void CWordArray::Append( CWordArray& source )
{
   int loop_index = 0;

   while( loop_index < source.GetSize() )
   {
      reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->push_back( source.GetAt( loop_index ) );
      loop_index++;
   }
}

void CWordArray::Copy( const CWordArray& source )
{
   // There ain't no easy way to copy vectors
   if ( source.GetSize() == 0 )
   {
      // Empty array copy
      RemoveAll();
      return;
   }

   SetSize( source.GetSize() );

   CopyMemory( GetData(), source.GetData(), source.GetSize() * sizeof( ARRAY_TYPE ) );
}

CWordArray::ARRAY_TYPE& CWordArray::ElementAt( int array_index )
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->at( array_index ) );
}

void CWordArray::FreeExtra( void )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->resize( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() );
}

CWordArray::ARRAY_TYPE CWordArray::GetAt( int array_index ) const
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->at( array_index ) );
}

int CWordArray::GetSize( void ) const
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() );
}

int CWordArray::GetUpperBound( void ) const
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() - 1 );
}

void CWordArray::InsertAt( int array_index, CWordArray::ARRAY_TYPE new_element, int number_of_times_to_insert_it )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->insert( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index, number_of_times_to_insert_it, new_element );
}

void CWordArray::InsertAt( int array_index, CWordArray * array_p )
{
   vector< ARRAY_TYPE > * source_p = reinterpret_cast< vector< ARRAY_TYPE > * >( array_p->m_Array );
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->insert( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index, source_p->begin(), source_p->end() );
}

void CWordArray::RemoveAll( void )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->clear();
}
void CWordArray::RemoveAt( int array_index, int number_of_elements_to_remove )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->erase( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index, reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index + number_of_elements_to_remove );
}

void CWordArray::SetSize( int new_size, int x )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->resize( new_size );
}

void CWordArray::SetAt( int array_index, CWordArray::ARRAY_TYPE new_element )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->at( array_index ) = new_element;
}

const CWordArray::ARRAY_TYPE * CWordArray::GetData( void ) const
{
   if ( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() == 0 )
   {
      return( NULL );
   }

   return( &reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->operator[]( 0 ) );
}

CWordArray::ARRAY_TYPE * CWordArray::GetData( void )
{
   return( &reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->operator[]( 0 ) );
}

CWordArray::ARRAY_TYPE CWordArray::operator[]( int array_index ) const
{
   return( GetAt( array_index ) );
}

CWordArray::ARRAY_TYPE& CWordArray::operator[]( int array_index )
{
   return( ElementAt( array_index ) );
}

#endif // WFC_STL