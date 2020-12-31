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
** $Workfile: STL_CStringArray.cpp $
** $Revision: 3 $
** $Modtime: 5/12/00 7:09p $
*/

#if defined( WFC_STL )

// Get rid of a ton of warnings

#pragma warning( disable : 4710 4702 )

// Now start picking up the STL stuff

#include <vector>
#include <algorithm>

using namespace std;

CStringArray::CStringArray()
{
   m_Array = new vector< ARRAY_TYPE >;
}

CStringArray::~CStringArray()
{
   if ( m_Array != NULL )
   {
      vector< ARRAY_TYPE > * temp_pointer = reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array );
      delete temp_pointer;
      m_Array = NULL;
   }
}

CStringArray::CStringArray( const CStringArray& source )
{
   m_Array = new vector< ARRAY_TYPE >;
   Copy( source );
}

int CStringArray::Add( CStringArray::ARRAY_TYPE new_element )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->push_back( new_element );
   return( GetUpperBound() );
}

void CStringArray::Append( const CStringArray& source )
{
   int loop_index = 0;
   
   while( loop_index < source.GetSize() )
   {
      reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->push_back( source.GetAt( loop_index ) );
      loop_index++;
   }
}

void CStringArray::Copy( const CStringArray& source )
{
   RemoveAll();

   long loop_index            = 0;
   long number_of_array_items = source.GetSize();

   while( loop_index < number_of_array_items )
   {
      Add( source.GetAt( loop_index ) );
      loop_index++;
   }
}

CStringArray::ARRAY_TYPE& CStringArray::ElementAt( int array_index )
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->at( array_index ) );
}

void CStringArray::FreeExtra( void )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->resize( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() );
}

CStringArray::ARRAY_TYPE CStringArray::GetAt( int array_index ) const
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->at( array_index ) );
}

int CStringArray::GetSize( void ) const
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() );
}

int CStringArray::GetUpperBound( void ) const
{
   return( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->size() - 1 );
}

void CStringArray::InsertAt( int array_index, CStringArray::ARRAY_TYPE new_element, int number_of_times_to_insert_it )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->insert( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index, number_of_times_to_insert_it, new_element );
}

void CStringArray::InsertAt( int array_index, CStringArray * array_p )
{
   vector< ARRAY_TYPE > * source_p = reinterpret_cast< vector< ARRAY_TYPE > * >( array_p->m_Array );
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->insert( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index, source_p->begin(), source_p->end() );
}

void CStringArray::RemoveAll( void )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->clear();
}

void CStringArray::RemoveAt( int array_index, int number_of_elements_to_remove )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->erase( reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index, reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->begin() + array_index + number_of_elements_to_remove );
}

void CStringArray::SetSize( int new_size, int )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->resize( new_size );
}

void CStringArray::SetAt( int array_index, CStringArray::ARRAY_TYPE new_element )
{
   reinterpret_cast< vector< ARRAY_TYPE > * >( m_Array )->at( array_index ) = new_element;
}

CStringArray::ARRAY_TYPE CStringArray::operator[]( int array_index ) const
{
   return( GetAt( array_index ) );
}

CStringArray::ARRAY_TYPE& CStringArray::operator[]( int array_index )
{
   return( ElementAt( array_index ) );
}

#endif // WFC_STL