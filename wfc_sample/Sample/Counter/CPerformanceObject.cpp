#include "counter.h"
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
** Copyright, 1996, Samuel R. Blackburn
**
** $Workfile: $
** $Revision: $
** $Modtime: $
*/

CPerformanceObject::CPerformanceObject( PPERF_OBJECT_TYPE data ) 
{
   m_ThisObject = data;

   m_InitializeCounterDefinitions();
}

void CPerformanceObject::m_InitializeCounterDefinitions( void )
{
   ASSERT( m_ThisObject != NULL );

   if ( m_ThisObject == NULL )
   {
      return;
   }

   m_CounterDefinitions.RemoveAll();

   DWORD number_of_counters = m_ThisObject->NumCounters;

   if ( number_of_counters < 1 )
   {
      return;
   }

   BYTE * pointer_to_add = (BYTE *) NULL;

   pointer_to_add = ( (BYTE *) m_ThisObject ) + m_ThisObject->HeaderLength;

   m_CounterDefinitions.Add( (VOID *) pointer_to_add );

   PPERF_COUNTER_DEFINITION counter_definition_p = (PPERF_COUNTER_DEFINITION) pointer_to_add;

   DWORD index = 1; // We've already added the first definition

   while( index < number_of_counters )
   {
      pointer_to_add = ( reinterpret_cast<BYTE *>( counter_definition_p ) ) + counter_definition_p->ByteLength;

      m_CounterDefinitions.Add( reinterpret_cast<VOID *>( pointer_to_add ) );

      counter_definition_p = reinterpret_cast<PPERF_COUNTER_DEFINITION>( pointer_to_add );

      index++;
   }
}

void CPerformanceObject::Copy( const CPerformanceObject& source )
{
   m_ThisObject = source.m_ThisObject;
}

PPERF_INSTANCE_DEFINITION CPerformanceObject::m_GetFirstInstance( void ) const
{
   return( (PPERF_INSTANCE_DEFINITION ) ( m_ThisObject + m_ThisObject->DefinitionLength ) );
}

DWORD CPerformanceObject::GetNumberOfCounters( void ) const
{
   return( m_CounterDefinitions.GetSize() );
}

#if defined( _DEBUG )

void CPerformanceObject::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_DataBlock_p      = " ) << (VOID *) m_DataBlock_p    << TEXT( "\n" );
   dump_context << TEXT( "   m_FirstObject      = " ) << (VOID *) m_FirstObject    << TEXT( "\n" );
   dump_context << TEXT( "   m_PreviousObject   = " ) << (VOID *) m_PreviousObject << TEXT( "\n" );
   dump_context << TEXT( "   m_ThisObject       = " ) << (VOID *) m_ThisObject     << TEXT( "\n" );
   dump_context << TEXT( "   m_NumberOfObjects  = " ) << m_NumberOfObjects         << TEXT( "\n" );
   dump_context << TEXT( "   m_ThisObjectNumber = " ) << m_ThisObjectNumber        << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG
