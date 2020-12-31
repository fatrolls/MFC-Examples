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

CPerformanceCounterDefinition::CPerformanceCounterDefinition()
{
   m_Pointer = NULL;
}

CPerformanceCounterDefinition::CPerformanceCounterDefinition( PPERF_COUNTER_DEFINITION pointer )
{
   m_Pointer = pointer;
}

CPerformanceCounterDefinition::~CPerformanceCounterDefinition()
{
   m_Pointer = NULL;
}

void CPerformanceCounterDefinition::Copy( PPERF_COUNTER_DEFINITION source )
{
   m_Pointer = source;
}

void CPerformanceCounterDefinition::TranslateType( CString& type_string ) const
{
   ASSERT( m_Pointer != NULL );

   type_string.Empty();

   if ( m_Pointer == NULL )
   {
      type_string = TEXT( "m_Pointer is NULL" );
      return;
   }

   // Decrypt the CounterType Field

   DWORD type = m_Pointer->CounterType;

   if ( type == 0 )
   {
      type_string = TEXT( "0!" );
   }

   if ( type & PERF_SIZE_VARIABLE_LEN )
   {
      type_string += TEXT( "PERF_SIZE_VARIABLE_LEN" );
   }
   else if ( type & PERF_SIZE_LARGE )
   {
      type_string += TEXT( "PERF_SIZE_LARGE" );
   }
   else if ( type & PERF_SIZE_ZERO )
   {
      type_string += TEXT( "PERF_SIZE_ZERO" );
   }
   else
   {
      type_string += TEXT( "PERF_SIZE_DWORD" );
   }

   if ( type & PERF_TYPE_COUNTER )
   {
      type_string += TEXT( " | PERF_TYPE_COUNTER" );

      if ( type & PERF_COUNTER_RATE )
      {
         type_string += TEXT( " | PERF_COUNTER_RATE" );
      }
      else if ( type & PERF_COUNTER_FRACTION )
      {
         type_string += TEXT( " | PERF_COUNTER_FRACTION" );
      }
      else if ( type & PERF_COUNTER_BASE )
      {
         type_string += TEXT( " | PERF_COUNTER_BASE" );
      }
      else if ( type & PERF_COUNTER_ELAPSED )
      {
         type_string += TEXT( " | PERF_COUNTER_ELAPSED" );
      }
      else if ( type & PERF_COUNTER_QUEUELEN )
      {
         type_string += TEXT( " | PERF_COUNTER_QUEUELEN" );
      }
      else if ( type & PERF_COUNTER_HISTOGRAM )
      {
         type_string += TEXT( " | PERF_COUNTER_HISTOGRAM" );
      }
      else // type & PERF_COUNTER_VALUE
      {
         type_string += TEXT( " | PERF_COUNTER_VALUE" );
      }

      if ( type & PERF_TIMER_TICK )
      {
         type_string += TEXT( " | PERF_TIMER_TICK" );
      }

      if ( type & PERF_TIMER_100NS )
      {
         type_string += TEXT( " | PERF_TIMER_100NS" );
      }

      if ( type & PERF_OBJECT_TIMER )
      {
         type_string += TEXT( " | PERF_OBJECT_TIMER" );
      }
   }
   else if ( type & PERF_TYPE_TEXT )
   {
      type_string += TEXT( " | PERF_TYPE_TEXT" );

      if ( type & PERF_TEXT_ASCII )
      {
         type_string += TEXT( " | PERF_TEXT_ASCII" );
      }
      else // type & PERF_TEXT_UNICODE
      {
         type_string += TEXT( " | PERF_TEXT_UNICODE" );
      }
   }
   else if ( type & PERF_TYPE_ZERO )
   {
      type_string += TEXT( " | PERF_TYPE_ZERO" );
   }
   else // type & PERF_TYPE_NUMBER
   {
      type_string += TEXT( " | PERF_TYPE_NUMBER" );

      if ( type & PERF_NUMBER_DECIMAL )
      {
         type_string += TEXT( " | PERF_NUMBER_DECIMAL" );
      }
      else if ( type & PERF_NUMBER_DEC_1000 )
      {
         type_string += TEXT( " | PERF_NUMBER_DEC_1000" );
      }
      else // type & PERF_NUMBER_HEX
      {
         type_string += TEXT( " | PERF_NUMBER_HEX" );
      }
   }

   if ( type & PERF_DELTA_COUNTER )
   {
      type_string += TEXT( " | PERF_DELTA_COUNTER" );
   }

   if ( type & PERF_DELTA_BASE )
   {
      type_string += TEXT( " | PERF_DELTA_BASE" );
   }

   if ( type & PERF_INVERSE_COUNTER )
   {
      type_string += TEXT( " | PERF_INVERSE_COUNTER" );
   }

   if ( type & PERF_MULTI_COUNTER )
   {
      type_string += TEXT( " | PERF_MULTI_COUNTER" );
   }

   if ( type & PERF_DISPLAY_PER_SEC )
   {
      type_string += TEXT( " | PERF_DISPLAY_PER_SEC" );
   }
   else if ( type & PERF_DISPLAY_PERCENT )
   {
      type_string += TEXT( " | PERF_DISPLAY_PERCENT" );
   }
   else if ( type & PERF_DISPLAY_SECONDS )
   {
      type_string += TEXT( " | PERF_DISPLAY_SECONDS" );
   }
   else if ( type & PERF_DISPLAY_NOSHOW )
   {
      type_string += TEXT( " | PERF_DISPLAY_NOSHOW" );
   }
   else // type & PERF_DISPLAY_NO_SUFFIX
   {
      type_string += TEXT( " | PERF_DISPLAY_NO_SUFFIX" );
   }

   switch( type )
   {
      case PERF_COUNTER_COUNTER:

         type_string += TEXT( " (PERF_COUNTER_COUNTER)" );
         break;

      case PERF_COUNTER_TIMER:

         type_string += TEXT( " (PERF_COUNTER_TIMER)" );
         break;

      case PERF_COUNTER_QUEUELEN_TYPE:

         type_string += TEXT( " (PERF_COUNTER_QUEUELEN_TYPE)" );
         break;

      case PERF_COUNTER_BULK_COUNT:

         type_string += TEXT( " (PERF_COUNTER_BULK_COUNT)" );
         break;

      case PERF_COUNTER_TEXT:

         type_string += TEXT( " (PERF_COUNTER_TEXT)" );
         break;

      case PERF_COUNTER_RAWCOUNT:

         type_string += TEXT( " (PERF_COUNTER_RAWCOUNT)" );
         break;

      case PERF_COUNTER_LARGE_RAWCOUNT:

         type_string += TEXT( " (PERF_COUNTER_LARGE_RAWCOUNT)" );
         break;

      case PERF_COUNTER_RAWCOUNT_HEX:

         type_string += TEXT( " (PERF_COUNTER_RAWCOUNT_HEX)" );
         break;

      case PERF_COUNTER_LARGE_RAWCOUNT_HEX:

         type_string += TEXT( " (PERF_COUNTER_LARGE_RAWCOUNT_HEX)" );
         break;

      case PERF_SAMPLE_FRACTION:

         type_string += TEXT( " (PERF_SAMPLE_FRACTION)" );
         break;

      case PERF_SAMPLE_COUNTER:

         type_string += TEXT( " (PERF_SAMPLE_COUNTER)" );
         break;

      case PERF_COUNTER_NODATA:

         type_string += TEXT( " (PERF_COUNTER_NODATA)" );
         break;

      case PERF_COUNTER_TIMER_INV:

         type_string += TEXT( " (PERF_COUNTER_TIMER_INV)" );
         break;

      case PERF_SAMPLE_BASE:

         type_string += TEXT( " (PERF_SAMPLE_BASE)" );
         break;

      case PERF_AVERAGE_TIMER:

         type_string += TEXT( " (PERF_AVERAGE_TIMER)" );
         break;

      case PERF_AVERAGE_BASE:

         type_string += TEXT( " (PERF_AVERAGE_BASE)" );
         break;

      case PERF_AVERAGE_BULK:

         type_string += TEXT( " (PERF_AVERAGE_BULK)" );
         break;

      case PERF_100NSEC_TIMER:

         type_string += TEXT( " (PERF_100NSEC_TIMER)" );
         break;

      case PERF_100NSEC_TIMER_INV:

         type_string += TEXT( " (PERF_100NSEC_TIMER_INV)" );
         break;

      case PERF_COUNTER_MULTI_TIMER:

         type_string += TEXT( " (PERF_COUNTER_MULTI_TIMER)" );
         break;

      case PERF_COUNTER_MULTI_TIMER_INV:

         type_string += TEXT( " (PERF_COUNTER_MULTI_TIMER_INV)" );
         break;

      case PERF_COUNTER_MULTI_BASE:

         type_string += TEXT( " (PERF_COUNTER_MULTI_BASE)" );
         break;

      case PERF_100NSEC_MULTI_TIMER:

         type_string += TEXT( " (PERF_100NSEC_MULTI_TIMER)" );
         break;

      case PERF_100NSEC_MULTI_TIMER_INV:

         type_string += TEXT( " (PERF_100NSEC_MULTI_TIMER_INV)" );
         break;

      case PERF_RAW_FRACTION:

         type_string += TEXT( " (PERF_RAW_FRACTION)" );
         break;

      case PERF_RAW_BASE:

         type_string += TEXT( " (PERF_RAW_BASE)" );
         break;

      case PERF_ELAPSED_TIME:

         type_string += TEXT( " (PERF_ELAPSED_TIME)" );
         break;

      case PERF_COUNTER_HISTOGRAM_TYPE:

         type_string += TEXT( " (PERF_COUNTER_HISTOGRAM_TYPE)" );
         break;
   }

   _tprintf( TEXT( "End of type (%lX) decrypt\n" ), type );
}
