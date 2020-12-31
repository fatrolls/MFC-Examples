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

void dump_perf_object_type( PPERF_OBJECT_TYPE object_p )
{
   if ( object_p == NULL )
   {
      return;
   }

   _tprintf( TEXT( "ObjectNameTitleIndex = %lu\n" ), object_p->ObjectNameTitleIndex );
   _tprintf( TEXT( "NumInstances         = %ld\n" ), object_p->NumInstances );
}

LONG GetPerformanceCounterData( LPWSTR lpwObject,
                                LPWSTR lpwCounter,
                                LPBYTE *lplpOutputData,
                                CSystemTime& SystemTime,
                                LARGE_INTEGER& SampleTime )
{
   WCHAR szwObjectIndex[ 100 ];
   WCHAR szwCounterIndex[ 100 ];

   LPBYTE lpOutputData = NULL;

   LONG lNumInstances = 0;

   // Get performance monitoring data

   DWORD dwType      = 0;
   LPBYTE pbyData    = NULL;
   DWORD dwDataBytes = 163840;

   pbyData = (LPBYTE) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, dwDataBytes );

   while( TRUE )
   {
      DWORD dwError = 0;

      // Change to use CRegistry::QueryValue

      if ( ( dwError = RegQueryValueExW( HKEY_PERFORMANCE_DATA,
                                         lpwObject,
                                         NULL,
                                        &dwType,
                                        pbyData,
                                        &dwDataBytes ) ) == ERROR_MORE_DATA )
      {
         pbyData = (LPBYTE) HeapReAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, pbyData, dwDataBytes + 4096 );
      }
      else if ( dwError == ERROR_SUCCESS )
      {
         _tprintf( TEXT( "%d\n" ), __LINE__ );
         break;
      }
      else
      {
         _tprintf( TEXT( "%d\n" ), __LINE__ );
         return( -1 );
      }
   }

   pbyData = (LPBYTE) HeapReAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, pbyData, dwDataBytes );

   *lplpOutputData = (LPBYTE) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, dwDataBytes );

   lpOutputData = *lplpOutputData;

   PPERF_DATA_BLOCK pPerfData = (PPERF_DATA_BLOCK) pbyData;

   // Look for the requested object

   DWORD dwThisObject; // Count of objects
   PPERF_OBJECT_TYPE pThisObject; // pointer to object structure

   PPERF_COUNTER_DEFINITION pThisCounter;
   PBYTE pTempObject = pbyData;

   _tprintf( TEXT( "pPerfData->SystemTime.wSeconds = %d\n" ), pPerfData->SystemTime.wSecond );
   SystemTime.Copy( &pPerfData->SystemTime );
   _tprintf( TEXT( "%d\n" ), __LINE__ );

   // Beginning of object array is indicated by the HeaderLength field
   // of the PERF_DATA_BLOCK

   pThisObject = (PPERF_OBJECT_TYPE) (pTempObject + pPerfData->HeaderLength);
   pTempObject = (PBYTE) pThisObject;

   if ( pThisObject->ObjectNameTitle != NULL )
   {
      wprintf( L"pThisObject->ObjectNameTitle = \"%s\"\n", pThisObject->ObjectNameTitle );
   }
   else
   {
      wprintf( L"pThisObject->ObjectNameTitle is NULL\n" );
   }

   BOOL bFound = FALSE;

   // Look for what the caller wants

   for( dwThisObject = 0; !bFound && (dwThisObject < pPerfData->NumObjectTypes ); dwThisObject++, pThisObject = (PPERF_OBJECT_TYPE) (pTempObject += pThisObject->TotalByteLength ) )
   {
      swprintf( szwObjectIndex, L"%-d", pThisObject->ObjectNameTitleIndex );

      // Is this what we want?

      if ( CompareStringW( GetUserDefaultLCID(), 0, szwObjectIndex, -1, lpwObject, -1 ) != 2 )
      {
         continue;
      }

      // We've found our object

      DWORD dwThisCounter = 0;

      PBYTE pTempCounter = NULL;

      pTempCounter = pTempObject + pThisObject->HeaderLength;

      pThisCounter = (PPERF_COUNTER_DEFINITION) pTempCounter;

      // Loop through the counter definitions

      for( dwThisCounter = 0; dwThisCounter < pThisObject->NumCounters; dwThisCounter++, pThisCounter = (PPERF_COUNTER_DEFINITION) (pTempCounter += pThisCounter->ByteLength ) )
      {
         swprintf( szwCounterIndex, L"%-d", pThisCounter->CounterNameTitleIndex );

         // Is this the counter we're looking for?

         wprintf( L"Comparing \"%s\" to \"%s\"\n", szwCounterIndex, lpwCounter );

         if ( CompareStringW( GetUserDefaultLCID(), 0, szwCounterIndex, -1, lpwCounter, -1 ) == 2 )
         {
            _tprintf( TEXT( "%d\n" ), __LINE__ );
            lNumInstances += pThisObject->NumInstances;
            bFound = TRUE;
            break;
         }
      }

      if ( bFound && pThisObject->NumInstances >= 0 )
      {
         PPERF_INSTANCE_DEFINITION pThisInstance = NULL;
         PPERF_COUNTER_BLOCK       pCounterBlock = NULL;
         DWORD dwThisInstance = 0;
         PBYTE pTempInstance = NULL;
         PBYTE pTempCounterData = NULL;

         // This is a multiple instance object

         pTempInstance = pTempObject + pThisObject->DefinitionLength;

         pThisInstance = (PPERF_INSTANCE_DEFINITION) pTempInstance;

         _tprintf( TEXT( "pThisObject->NumInstances is %lu\n" ), (DWORD) pThisObject->NumInstances );

         CPerformanceCounterDefinition definition;
         CString temp_string;

         for( dwThisInstance = 0; dwThisInstance < (DWORD) pThisObject->NumInstances; dwThisInstance++ )
         {
            pTempCounterData = pTempInstance + pThisInstance->ByteLength;

            pCounterBlock = (PPERF_COUNTER_BLOCK) pTempCounterData;
            pTempCounterData += pThisCounter->CounterOffset;

            DWORD temp_dword = 0;

            CopyMemory( &temp_dword, pTempCounterData, pThisCounter->CounterSize );
            _tprintf( TEXT( "Copying %lu bytes, value %lu\n" ), (DWORD) pThisCounter->CounterSize, temp_dword );

            definition.Copy( pThisCounter );

            definition.TranslateType( temp_string );

            _tprintf( TEXT( "Type decrypts to %s\n" ), (LPCTSTR) temp_string );

            CopyMemory( lpOutputData, pTempCounterData, pThisCounter->CounterSize );
            lpOutputData += pThisCounter->CounterSize;

            pTempInstance += (pCounterBlock->ByteLength + pThisInstance->ByteLength);
            pThisInstance = (PPERF_INSTANCE_DEFINITION) pTempInstance;
         }
      }
      else if ( pThisObject->NumInstances == (PERF_NO_INSTANCES) )
      {
         PBYTE pTempCounterData;

         pTempCounterData = pTempObject + pThisObject->DefinitionLength;
         pTempCounterData += pThisCounter->CounterOffset;

         _tprintf( TEXT( "%d, Copying %lu bytes\n" ), __LINE__, pThisCounter->CounterSize );
            
         CopyMemory( lpOutputData, pTempCounterData, pThisCounter->CounterSize );
         lpOutputData += pThisCounter->CounterSize;
         lNumInstances = 1;
      }
   }

   return( lNumInstances );
}

void count( void )
{
   // Open and monitor a counter.
   // Use a URL to play with counters example:
   // counter://machinename/object/instance/counter

   CUniformResourceLocator counter_url( "counter://SAMMY/Processor/0/% Processor Time" );

   //CPerformanceCounter performance_counter;

   LARGE_INTEGER counter;
   LARGE_INTEGER high_resolution_counter;

   CSystemTime system_time;

   int index = 0;
   LONG x    = 0;

   do
   {
      counter.LowPart  = 0;
      counter.HighPart = 0;

      x = GetPerformanceCounterData( L"870", L"872", reinterpret_cast<LPBYTE *>( &counter ), system_time, high_resolution_counter );

      _tprintf( TEXT( "%d. %ld counter.LowPart = %lu, counter.HighPart = %lu\n" ), (int) index, x, counter.LowPart, counter.HighPart );

      Sleep( 2220 );

      index++;
   }
   while( index < 3 );

   CPerformanceData performance_data;

   // Look for the requested object

   DWORD dwThisObject; // Count of objects
   PPERF_OBJECT_TYPE pThisObject; // pointer to object structure

   CPerformanceObject performance_object;

   PPERF_COUNTER_DEFINITION pThisCounter;
   PBYTE pTempObject = pbyData;

   // Beginning of object array is indicated by the HeaderLength field
   // of the PERF_DATA_BLOCK

   pThisObject = (PPERF_OBJECT_TYPE) (pTempObject + pPerfData->HeaderLength);
   pTempObject = (PBYTE) pThisObject;

   if ( pThisObject->ObjectNameTitle != NULL )
   {
      wprintf( L"pThisObject->ObjectNameTitle = \"%s\"\n", pThisObject->ObjectNameTitle );
   }
   else
   {
      wprintf( L"pThisObject->ObjectNameTitle is NULL\n" );
   }

   BOOL bFound = FALSE;

   // Look for what the caller wants

   for( dwThisObject = 0; !bFound && (dwThisObject < pPerfData->NumObjectTypes ); dwThisObject++, pThisObject = (PPERF_OBJECT_TYPE) (pTempObject += pThisObject->TotalByteLength ) )
   {
      swprintf( szwObjectIndex, L"%-d", pThisObject->ObjectNameTitleIndex );

      // Is this what we want?

      if ( CompareStringW( GetUserDefaultLCID(), 0, szwObjectIndex, -1, lpwObject, -1 ) != 2 )
      {
         continue;
      }

      // We've found our object

      DWORD dwThisCounter = 0;

      PBYTE pTempCounter = NULL;

      pTempCounter = pTempObject + pThisObject->HeaderLength;

      pThisCounter = (PPERF_COUNTER_DEFINITION) pTempCounter;

      // Loop through the counter definitions

      for( dwThisCounter = 0; dwThisCounter < pThisObject->NumCounters; dwThisCounter++, pThisCounter = (PPERF_COUNTER_DEFINITION) (pTempCounter += pThisCounter->ByteLength ) )
      {
         swprintf( szwCounterIndex, L"%-d", pThisCounter->CounterNameTitleIndex );

         // Is this the counter we're looking for?

         wprintf( L"Comparing \"%s\" to \"%s\"\n", szwCounterIndex, lpwCounter );

         if ( CompareStringW( GetUserDefaultLCID(), 0, szwCounterIndex, -1, lpwCounter, -1 ) == 2 )
         {
            _tprintf( TEXT( "%d\n" ), __LINE__ );
            lNumInstances += pThisObject->NumInstances;
            bFound = TRUE;
            break;
         }
      }

      if ( bFound && pThisObject->NumInstances >= 0 )
      {
         PPERF_INSTANCE_DEFINITION pThisInstance = NULL;
         PPERF_COUNTER_BLOCK       pCounterBlock = NULL;
         DWORD dwThisInstance = 0;
         PBYTE pTempInstance = NULL;
         PBYTE pTempCounterData = NULL;

         // This is a multiple instance object

         pTempInstance = pTempObject + pThisObject->DefinitionLength;

         pThisInstance = (PPERF_INSTANCE_DEFINITION) pTempInstance;

         _tprintf( TEXT( "pThisObject->NumInstances is %lu\n" ), (DWORD) pThisObject->NumInstances );

         CPerformanceCounterDefinition definition;
         CString temp_string;

         for( dwThisInstance = 0; dwThisInstance < (DWORD) pThisObject->NumInstances; dwThisInstance++ )
         {
            pTempCounterData = pTempInstance + pThisInstance->ByteLength;

            pCounterBlock = (PPERF_COUNTER_BLOCK) pTempCounterData;
            pTempCounterData += pThisCounter->CounterOffset;

            DWORD temp_dword = 0;

            CopyMemory( &temp_dword, pTempCounterData, pThisCounter->CounterSize );
            _tprintf( TEXT( "Copying %lu bytes, value %lu\n" ), (DWORD) pThisCounter->CounterSize, temp_dword );

            definition.Copy( pThisCounter );

            definition.TranslateType( temp_string );

            _tprintf( TEXT( "Type decrypts to %s\n" ), (LPCTSTR) temp_string );

            CopyMemory( lpOutputData, pTempCounterData, pThisCounter->CounterSize );
            lpOutputData += pThisCounter->CounterSize;

            pTempInstance += (pCounterBlock->ByteLength + pThisInstance->ByteLength);
            pThisInstance = (PPERF_INSTANCE_DEFINITION) pTempInstance;
         }
      }
      else if ( pThisObject->NumInstances == (PERF_NO_INSTANCES) )
      {
         PBYTE pTempCounterData;

         pTempCounterData = pTempObject + pThisObject->DefinitionLength;
         pTempCounterData += pThisCounter->CounterOffset;

         _tprintf( TEXT( "%d, Copying %lu bytes\n" ), __LINE__, pThisCounter->CounterSize );
            
         CopyMemory( lpOutputData, pTempCounterData, pThisCounter->CounterSize );
         lpOutputData += pThisCounter->CounterSize;
         lNumInstances = 1;
      }
   }

   return( lNumInstances );
}

void dump_perf_data( PPERF_DATA_BLOCK performance_data_block_p )
{
   _tprintf( TEXT( "Signature '%c' '%c' '%c' '%c'\n" ),
           (char) performance_data_block_p->Signature[ 0 ],
           (char) performance_data_block_p->Signature[ 1 ],
           (char) performance_data_block_p->Signature[ 2 ],
           (char) performance_data_block_p->Signature[ 3 ] );

   if ( performance_data_block_p->LittleEndian == 0 )
   {
      _tprintf( TEXT( "LittleEndian is BIG ENDIAN\n" ) );
   }
   else
   {
      _tprintf( TEXT( "LittleEndian is LITTLE ENDIAN\n" ) );
   }

   _tprintf( TEXT( "Revision %lu\n"           ), performance_data_block_p->Revision         );
   _tprintf( TEXT( "TotalByteLength  = %lu\n" ), performance_data_block_p->TotalByteLength  );
   _tprintf( TEXT( "HeaderLength     = %lu\n" ), performance_data_block_p->HeaderLength     );
   _tprintf( TEXT( "NumObjectTypes   = %lu\n" ), performance_data_block_p->NumObjectTypes   );
   _tprintf( TEXT( "DefaultObject    = %ld\n" ), performance_data_block_p->DefaultObject    );
   _tprintf( TEXT( "SystemNameLength = %lu\n" ), performance_data_block_p->SystemNameLength );
   _tprintf( TEXT( "SystemNameOffset = %lu\n" ), performance_data_block_p->SystemNameOffset );
}

void get_perf_data_block( void )
{
   PPERF_DATA_BLOCK performance_data_block_p = NULL;

   DWORD buffer_size = 33 * 1024;
 
   performance_data_block_p = (PPERF_DATA_BLOCK) malloc( buffer_size );

   DWORD temp_size = buffer_size;
 
   while( RegQueryValueEx( HKEY_PERFORMANCE_DATA,
                                TEXT( "Global" ),
                                            NULL,
                                            NULL,
      reinterpret_cast<unsigned char *>( performance_data_block_p ),
                                     &temp_size ) == ERROR_MORE_DATA )
   {
      buffer_size += 4096;
      temp_size   = buffer_size;
 
      performance_data_block_p = (PPERF_DATA_BLOCK) realloc( performance_data_block_p, buffer_size );

      if ( performance_data_block_p == NULL )
      {
         break;
      }
   }

   dump_perf_data( performance_data_block_p );

   CStringArray counter_names;

   _tprintf( TEXT( "%d counter names\n" ), counter_names.GetSize() );
   free( performance_data_block_p );
}

void main()
{
   CPerformanceData data;

   CString counter_name;

   data.GetName( 870, counter_name );
   _tprintf( TEXT( "870 == \"%s\"\n" ), (LPCTSTR) counter_name );

   data.GetName( 872, counter_name );
   _tprintf( TEXT( "872 == \"%s\"\n" ), (LPCTSTR) counter_name );

   count();
}
