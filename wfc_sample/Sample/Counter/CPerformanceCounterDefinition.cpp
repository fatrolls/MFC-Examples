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

CPerformanceCounterDefinition::CPerformanceCounterDefinition( CPerformanceObject& instance )
{
   m_Instance_p       = &instance;
   m_FirstCounter_p   = m_Instance_p->GetFirstCounter();
   m_ThisCounter_p    = m_FirstCounter_p;
   m_NumberOfCounters = m_Instance_p->GetNumberOfCounters();
   m_CounterNumber    = 1;
}

CPerformanceCounterDefinition::~CPerformanceCounterDefinition()
{
   m_Instance_p = NULL;
}

#if defined( _DEBUG )

void CPerformanceCounterDefinition::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_NumberOfCounters = " ) << m_NumberOfCounters        << TEXT( "\n" );
   dump_context << TEXT( "   m_CounterNumber    = " ) << m_CounterNumber           << TEXT( "\n" );
   dump_context << TEXT( "   m_ThisCounter_p    = " ) << (VOID_P) m_ThisCounter_p  << TEXT( "\n" );
   dump_context << TEXT( "   m_FirstCounter_p   = " ) << (VOID_P) m_FirstCounter_p << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

BOOL CPerformanceCounter::Enumerate( CPerformanceCounterData& data )
{
   return( FALSE );
}

BOOL CPerformanceCounter::GetNext( CPerformanceCounterData& data )
{
   return( FALSE );
}

void CPerformanceCounter::GetTypeName( CString& name )
{
   switch( m_ThisCounter_p->CounterType )
   {
      case PERF_COUNTER_COUNTER:

         name = TEXT( "PERF_COUNTER_COUNTER, 32-bit Counter. Divide delta by delta time. Display suffix: \"/sec\"" );
         break;

      case PERF_COUNTER_TIMER:

         name = TEXT( "PERF_COUNTER_TIMER, 64-bit Timer. Divide delta by delta time. Display suffix: \"%\"" );
         break;

      case PERF_COUNTER_QUEUELEN_TYPE:

         name = TEXT( "PERF_COUNTER_QUEUELEN_TYPE, Queue Length Space-Time Product. Divide delta by delta time. No Display Suffix." );
         break;

      case PERF_COUNTER_BULK_COUNT:

         name = TEXT( "PERF_COUNTER_BULK_COUNT, 64-bit Counter. Divide delta by delta time. Display Suffix: \"/sec\"" );
         break;

      case PERF_COUNTER_TEXT:

         name = TEXT( "PERF_COUNTER_TEXT, Indicates the counter is not a counter but rather Unicode text Display as text." );
         break;

      case PERF_COUNTER_RAWCOUNT:

         name = TEXT( "PERF_COUNTER_RAWCOUNT, 32-bit Indicates the data is a counter which should not be time averaged on display (such as an error counter on a serial line) Display as is. No Display Suffix." );
         break;

      case PERF_COUNTER_LARGE_RAWCOUNT:

         name = TEXT( "PERF_COUNTER_LARGE_RAWCOUNT, Same as PERF_COUNTER_RAWCOUNT except its size is a large integer" );
         break;

// Special case for RAWCOUNT that want to be displayed in hex
// Indicates the data is a counter  which should not be
// time averaged on display (such as an error counter on a serial line)
// Display as is.  No Display Suffix.
      case PERF_COUNTER_RAWCOUNT_HEX:

         name = TEXT( "PERF_COUNTER_RAWCOUNT_HEX" );
         break;

      case PERF_COUNTER_LARGE_RAWCOUNT_HEX:

         name = TEXT( "PERF_COUNTER_LARGE_RAWCOUNT_HEX, Same as PERF_COUNTER_RAWCOUNT_HEX except its size is a large integer" );
         break;

// A count which is either 1 or 0 on each sampling interrupt (% busy)
// Divide delta by delta base. Display Suffix: "%"
      case PERF_SAMPLE_FRACTION:

         name = TEXT( "PERF_SAMPLE_FRACTION" );
         break;

// A count which is sampled on each sampling interrupt (queue length)
// Divide delta by delta time. No Display Suffix.
      case PERF_SAMPLE_COUNTER:

         name = TEXT( "PERF_SAMPLE_COUNTER" );
         break;

      case PERF_COUNTER_NODATA:

         name = TEXT( "PERF_COUNTER_NODATA, A label: no data is associated with this counter (it has 0 length) Do not display." );
         break;

// 64-bit Timer inverse (e.g., idle is measured, but display busy %)
// Display 100 - delta divided by delta time.  Display suffix: "%"
      case PERF_COUNTER_TIMER_INV:

         name = TEXT( "PERF_COUNTER_TIMER_INV" );
         break;

// The divisor for a sample, used with the previous counter to form a
// sampled %.  You must check for >0 before dividing by this!  This
// counter will directly follow the  numerator counter.  It should not
// be displayed to the user.
      case PERF_SAMPLE_BASE:

         name = TEXT( "PERF_SAMPLE_BASE" );
         break;

// A timer which, when divided by an average base, produces a time
// in seconds which is the average time of some operation.  This
// timer times total operations, and  the base is the number of opera-
// tions.  Display Suffix: "sec"
      case PERF_AVERAGE_TIMER:

         name = TEXT( "PERF_AVERAGE_TIMER" );
         break;

// Used as the denominator in the computation of time or count
// averages.  Must directly follow the numerator counter.  Not dis-
// played to the user.
      case PERF_AVERAGE_BASE:

         name = TEXT( "PERF_AVERAGE_BASE" );
         break;

// A bulk count which, when divided (typically) by the number of
// operations, gives (typically) the number of bytes per operation.
// No Display Suffix.
      case PERF_AVERAGE_BULK:

         name = TEXT( "PERF_AVERAGE_BULK" );
         break;

// 64-bit Timer in 100 nsec units. Display delta divided by
// delta time.  Display suffix: "%"
      case PERF_100NSEC_TIMER:

         name = TEXT( "PERF_100NSEC_TIMER" );
         break;

// 64-bit Timer inverse (e.g., idle is measured, but display busy %)
// Display 100 - delta divided by delta time.  Display suffix: "%"
      case PERF_100NSEC_TIMER_INV:

         name = TEXT( "PERF_100NSEC_TIMER_INV" );
         break;

// 64-bit Timer.  Divide delta by delta time.  Display suffix: "%"
// Timer for multiple instances, so result can exceed 100%.
      case PERF_COUNTER_MULTI_TIMER:

         name = TEXT( "PERF_COUNTER_MULTI_TIMER" );
         break;

// 64-bit Timer inverse (e.g., idle is measured, but display busy %)
// Display 100 * _MULTI_BASE - delta divided by delta time.
// Display suffix: "%" Timer for multiple instances, so result
// can exceed 100%.  Followed by a counter of type _MULTI_BASE.
      case PERF_COUNTER_MULTI_TIMER_INV:

         name = TEXT( "PERF_COUNTER_MULTI_TIMER_INV" );
         break;

// Number of instances to which the preceding _MULTI_..._INV counter
// applies.  Used as a factor to get the percentage.
      case PERF_COUNTER_MULTI_BASE:

         name = TEXT( "PERF_COUNTER_MULTI_BASE" );
         break;

// 64-bit Timer in 100 nsec units. Display delta divided by delta time.
// Display suffix: "%" Timer for multiple instances, so result can exceed 100%.
      case PERF_100NSEC_MULTI_TIMER:

         name = TEXT( "PERF_100NSEC_MULTI_TIMER" );
         break;

// 64-bit Timer inverse (e.g., idle is measured, but display busy %)
// Display 100 * _MULTI_BASE - delta divided by delta time.
// Display suffix: "%" Timer for multiple instances, so result
// can exceed 100%.  Followed by a counter of type _MULTI_BASE.
      case PERF_100NSEC_MULTI_TIMER_INV:

         name = TEXT( "PERF_100NSEC_MULTI_TIMER_INV" );
         break;

// Indicates the data is a fraction of the following counter  which
// should not be time averaged on display (such as free space over
// total space.) Display as is.  Display the quotient as "%".
      case PERF_RAW_FRACTION:

         name = TEXT( "PERF_RAW_FRACTION" );
         break;

      case PERF_RAW_BASE:

         name = TEXT( "PERF_RAW_BASE, Indicates the data is a base for the preceding counter which should not be time averaged on display (such as free space over total space.)" );
         break;

// The data collected in this counter is actually the start time of the
// item being measured. For display, this data is subtracted from the
// sample time to yield the elapsed time as the difference between the two.
// In the definition below, the PerfTime field of the Object contains
// the sample time as indicated by the PERF_OBJECT_TIMER bit and the
// difference is scaled by the PerfFreq of the Object to convert the time
// units into seconds.
      case PERF_ELAPSED_TIME:

         name = TEXT( "PERF_ELAPSED_TIME" );
         break;

      default:

         name.Format( TEXT( "Unknown %lu" ), m_ThisCounter_p->CounterType );
         break;
   }
}
