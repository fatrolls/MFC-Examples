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
** $Workfile: STL_CDWordArray.cpp $
** $Revision: 3 $
** $Modtime: 5/12/00 7:10p $
*/

#if defined( WFC_STL )

// Get rid of a ton of warnings

#pragma warning( disable : 4710 4702 )

// Now start picking up the STL stuff

#include <vector>
#include <algorithm>

using namespace std;

CDWordArray::CDWordArray()
{
   m_Array = new vector< ARRAY_TYPE >;
}

CDWordArray::~CDWordArray()
{
   if ( m_Array != NULL )
   {
      vector< ARRAY_TYPE > * temp_pointer = reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array );
      delete temp_pointer;
      m_Array = NULL;
   }
}

int CDWordArray::Add( CDWordArray::ARRAY_TYPE new_element )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->push_back( new_element );
   return( GetUpperBound() );
}

void CDWordArray::Append( CDWordArray& source )
{
   int loop_index = 0;

   while( loop_index < source.GetSize() )
   {
      reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->push_back( source.GetAt( loop_index ) );
      loop_index++;
   }
}

void CDWordArray::Copy( const CDWordArray& source )
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

CDWordArray::ARRAY_TYPE& CDWordArray::ElementAt( int array_index )
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->at( array_index ) );
}

void CDWordArray::FreeExtra( void )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->resize( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() );
}

CDWordArray::ARRAY_TYPE CDWordArray::GetAt( int array_index ) const
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->at( array_index ) );
}

int CDWordArray::GetSize( void ) const
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() );
}

int CDWordArray::GetUpperBound( void ) const
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() - 1 );
}

void CDWordArray::InsertAt( int array_index, CDWordArray::ARRAY_TYPE new_element, int number_of_times_to_insert_it )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->insert( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index, number_of_times_to_insert_it, new_element );
}

void CDWordArray::InsertAt( int array_index, CDWordArray * array_p )
{
   vector< ARRAY_TYPE > * source_p = reinterpret_cast< vector< ARRAY_TYPE > * >( array_p->m_Array );
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->insert( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index, source_p->begin(), source_p->end() );
}

void CDWordArray::RemoveAll( void )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->clear();
}
void CDWordArray::RemoveAt( int array_index, int number_of_elements_to_remove )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->erase( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index, reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index + number_of_elements_to_remove );
}

void CDWordArray::SetSize( int new_size, int x )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->resize( new_size );
}

void CDWordArray::SetAt( int array_index, CDWordArray::ARRAY_TYPE new_element )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->at( array_index ) = new_element;
}

const CDWordArray::ARRAY_TYPE * CDWordArray::GetData( void ) const
{
   if ( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() == 0 )
   {
      return( NULL );
   }

   return( &reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->operator[]( 0 ) );
}

CDWordArray::ARRAY_TYPE * CDWordArray::GetData( void )
{
   return( &reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->operator[]( 0 ) );
}

CDWordArray::ARRAY_TYPE CDWordArray::operator[]( int array_index ) const
{
   return( GetAt( array_index ) );
}

CDWordArray::ARRAY_TYPE& CDWordArray::operator[]( int array_index )
{
   return( ElementAt( array_index ) );
}

#endif // WFC_STL