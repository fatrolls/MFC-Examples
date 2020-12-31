/*
** Here's the important performance counter data:
**
** 1. Get the performance data from the registry
**
** Having gotten this data from the registry, we cast it to a PERF_DATA_BLOCK pointer
**
** Next comes a PERF_OBJECT_TYPE. We compute the beginning of this structure by
** adding the HeaderLength field of the PERF_DATA_BLOCK structure to the address
** of the PERF_DATA_BLOCK. Example:
**
** PPERF_DATA_BLOCK performance_data_block_p = something;
** PPERF_OBJECT_TYPE performance_object_p = NULL;
**
** performance_object_p = performance_data_block_p + performance_data_block_p->HeaderLength;
**
** To get to the next PERF_OBJECT_TYPE in the list, add the value of TotalByteLength
** to the value of the pointer to the PERF_OBJECT_TYPE. Example:
**
** PPERF_OBJECT_TYPE this_object_p = something;
** PPERF_OBJECT_TYPE next_object_p = NULL;
**
** next_object_p = this_object_p + this_object_p->TotalByteLength;
**
** The first thing inside a performance object is counter definition. We find the first
** PPERF_COUNTER_DEFINITION by adding the value of HeaderLength to the pointer.
** Example:
**
** PPERF_OBJECT_TYPE this_object_p = something;
** PPERF_COUNTER_DEFINITION first_counter_definition_p = NULL;
**
** first_counter_definition_p = this_object_p + this_object_p->HeaderLength;
**
** To get to the next counter definition you add the ByteLength field to the pointer.
** You can tell how many counter definitions there are in an object by looking at the
** NumCounters field. Example:
**
** PPERF_COUNTER_DEFINITION this_counter_definition_p = something;
** PPERF_COUNTER_DEFINITION next_counter_definition_p = NULL;
**
** next_counter_definition_p = this_counter_definition_p + this_counter_definition_p->ByteLength;
** 
*/

#include "wfc.h"

#if 0
#include "CPCD.hpp"
#include "CPerfDef.hpp"
#endif

#include "CPerformanceData.hpp"
//#include "CPerformanceObject.hpp"
//#include "CPerformanceInstance.hpp"
//#include "CPerformanceCounterDefinition.hpp"
