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

CPerformanceData::CPerformanceData( LPCTSTR counter_name, LPCTSTR machine_name )
{
   DWORD buffer_size = 33 * 1024;
 
   m_DataBlock_p = reinterpret_cast<PPERF_DATA_BLOCK>( malloc( buffer_size ) );

   DWORD temp_size = buffer_size;

   // The problem here is HKEY_PERFORMANCE_DATA ain't really a registry key.
   // Microsoft hacked the performance counters so they use the same transport
   // mechanism of registry keys without using the hierarchy. In short, they
   // cheated.

   // Here's a real hack. If you want performance counter data from the local
   // machine, you state

   if ( registry.Connect( CRegistry::keyPerformanceData, machine_name ) != FALSE )
   {
      CRegistry::KeyValueTypes type;

      DWORD error_code = 0;

      BOOL exit_loop = FALSE;

      while( exit_loop == FALSE )
      {
         TRACE( TEXT( "Querying value\n" ) );

         // Funny, when I read the documentation for RegQueryValueEx() it made
         // no mention of HKEY_PERFORMANCE_DATA, odd...
         ::RegQueryValueEx( HKEY_PERFORMANCE_DATA...
         exit_loop = registry.QueryValue( TEXT( "Global" ),
                                          type,
                reinterpret_cast<BYTE *>( m_DataBlock_p ),
                                          temp_size );

         if ( exit_loop == FALSE )
         {
            error_code = registry.GetErrorCode();

            if ( error_code == ERROR_MORE_DATA )
            {
               buffer_size *= 2;
               temp_size   = buffer_size;
 
               TRACE( TEXT( "Increasing buffer size to %d bytes\n" ), buffer_size );

               m_DataBlock_p = (PPERF_DATA_BLOCK) realloc( m_DataBlock_p, buffer_size );

               if ( m_DataBlock_p == NULL )
               {
                  TRACE( TEXT( "m_DataBlock_p is NULL at line %d of %s\n" ), __LINE__, __FILE__ );
                  break;
               }
            }
            else
            {
               TRACE( TEXT( "Error!!!! %lu\n" ), error_code );
               break;
            }
         }
      }

      TRACE( TEXT( "Retrieved %lu bytes from Global\n" ), temp_size );
   }
   else
   {
      TRACE( TEXT( "Can't connect to performance data\n" ) );
   }

   if ( registry.Connect( HKEY_LOCAL_MACHINE, machine_name ) != FALSE )
   {
      if ( registry.Open( TEXT( "Software\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\009" ), CRegistry::permissionRead ) != FALSE )
      {
         registry.GetValue( TEXT( "Counter" ), m_CounterNames );
      }
      else
      {
         TRACE( TEXT( "Can't open sub-key\n" ) );
      }

      registry.Close();
   }
   else
   {
      _tprintf( TEXT( "Can't open registry\n" ) );
   }

   m_InitializeObjects();
}

CPerformanceData::~CPerformanceData()
{
   ::free( m_DataBlock_p );
   m_DataBlock_p = NULL;

   m_CounterNames.RemoveAll();
}

void CPerformanceData::GetName( DWORD desired_number, CString& string ) const
{
   int index = 0;

   DWORD number = 0;

   CString name;

   while ( index < m_CounterNames.GetSize() )
   {
      number = _ttol( m_CounterNames.GetAt( index ) );

      if ( number == desired_number )
      {
         string = m_CounterNames.GetAt( index + 1 );
         return;
      }

      index += 2;
   }

   string.Empty();
}

DWORD CPerformanceData::GetNumberOfObjects( void ) const
{
   return( m_PerformanceObjects.GetSize() );
}

PPERF_OBJECT_TYPE CPerformanceData::GetObject( DWORD index ) const
{
   ASSERT( index < m_PerformanceObjects.GetSize() );

   if ( index >= m_PerformanceObjects.GetSize() )
   {
      return( (PPERF_OBJECT_TYPE) NULL );
   }

   return( (PPERF_OBJECT_TYPE) m_PerformanceObjects.GetAt( index ) );
}

void CPerformanceData::m_InitializeObjects( void )
{
   ASSERT( m_DataBlock_p != NULL );

   if ( m_DataBlock_p == NULL )
   {
      return;
   }

   PPERF_OBJECT_TYPE object_p = (PPERF_OBJECT_TYPE) NULL;

   m_PerformanceObjects.RemoveAll();

   // Add the first object to the array...

   object_p = (PPERF_OBJECT_TYPE) ( ( reinterpret_cast<BYTE *>( m_DataBlock_p ) ) + m_DataBlock_p->HeaderLength );

   m_PerformanceObjects.Add( reinterpret_cast<VOID *>( object_p ) );

   int index = 1; // Start at one because we've already added the first element
   int number_of_objects = m_DataBlock_p->NumObjectTypes;

   TRACE( TEXT( "m_DataBlock_p->NumObjectTypes == %d\n" ), m_DataBlock_p->NumObjectTypes );

   PPERF_OBJECT_TYPE pointer_to_add = (PPERF_OBJECT_TYPE) NULL;

   while( index < number_of_objects )
   {
      pointer_to_add = reinterpret_cast<PPERF_OBJECT_TYPE>( ( ( (BYTE *) object_p ) + object_p->TotalByteLength ) );

      m_PerformanceObjects.Add( pointer_to_add );

      object_p = (PPERF_OBJECT_TYPE) pointer_to_add;
      
      index++;
   }
}

#if defined( _DEBUG )

void CPerformanceData::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_DataBlock_p = " ) << (VOID *) m_DataBlock_p << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

void CPerformanceData::DumpPerfDataBlock( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "_PERF_DATA_BLOCK\n{\n" );
   dump_context << TEXT( "   Singature[ 0 ]           = " ) << (char) m_DataBlock_p->Signature[ 0 ]    << TEXT( "\n" );
   dump_context << TEXT( "   Singature[ 1 ]           = " ) << (char) m_DataBlock_p->Signature[ 1 ]    << TEXT( "\n" );
   dump_context << TEXT( "   Singature[ 2 ]           = " ) << (char) m_DataBlock_p->Signature[ 2 ]    << TEXT( "\n" );
   dump_context << TEXT( "   Singature[ 3 ]           = " ) << (char) m_DataBlock_p->Signature[ 3 ]    << TEXT( "\n" );
   dump_context << TEXT( "   LittleEndian             = " ) << m_DataBlock_p->LittleEndian             << TEXT( "\n" );
   dump_context << TEXT( "   Version                  = " ) << m_DataBlock_p->Version                  << TEXT( "\n" );
   dump_context << TEXT( "   Revision                 = " ) << m_DataBlock_p->Revision                 << TEXT( "\n" );
   dump_context << TEXT( "   TotalByteLength          = " ) << m_DataBlock_p->TotalByteLength          << TEXT( "\n" );
   dump_context << TEXT( "   HeaderLength             = " ) << m_DataBlock_p->HeaderLength             << TEXT( "\n" );
   dump_context << TEXT( "   NumObjectTypes           = " ) << m_DataBlock_p->NumObjectTypes           << TEXT( "\n" );
   dump_context << TEXT( "   DefaultObject            = " ) << m_DataBlock_p->DefaultObject            << TEXT( "\n" );
   dump_context << TEXT( "   SystemTime.wYear         = " ) << m_DataBlock_p->SystemTime.wYear         << TEXT( "\n" );
   dump_context << TEXT( "   SystemTime.wMonth        = " ) << m_DataBlock_p->SystemTime.wMonth        << TEXT( "\n" );
   dump_context << TEXT( "   SystemTime.wDayOfWeek    = " ) << m_DataBlock_p->SystemTime.wDayOfWeek    << TEXT( "\n" );
   dump_context << TEXT( "   SystemTime.wDay          = " ) << m_DataBlock_p->SystemTime.wDay          << TEXT( "\n" );
   dump_context << TEXT( "   SystemTime.wHour         = " ) << m_DataBlock_p->SystemTime.wHour         << TEXT( "\n" );
   dump_context << TEXT( "   SystemTime.wMinute       = " ) << m_DataBlock_p->SystemTime.wMinute       << TEXT( "\n" );
   dump_context << TEXT( "   SystemTime.wSecond       = " ) << m_DataBlock_p->SystemTime.wSecond       << TEXT( "\n" );
   dump_context << TEXT( "   SystemTime.wMilliseconds = " ) << m_DataBlock_p->SystemTime.wMilliseconds << TEXT( "\n" );
   dump_context << TEXT( "   PerfTime.LowPart         = " ) << m_DataBlock_p->PerfTime.LowPart         << TEXT( "\n" );
   dump_context << TEXT( "   PerfTime.HighPart        = " ) << m_DataBlock_p->PerfTime.HighPart        << TEXT( "\n" );
   dump_context << TEXT( "   PerfFreq.LowPart         = " ) << m_DataBlock_p->PerfFreq.LowPart         << TEXT( "\n" );
   dump_context << TEXT( "   PerfFreq.HighPart        = " ) << m_DataBlock_p->PerfFreq.HighPart        << TEXT( "\n" );
   dump_context << TEXT( "   PerfTime100nSec.LowPart  = " ) << m_DataBlock_p->PerfTime100nSec.LowPart  << TEXT( "\n" );
   dump_context << TEXT( "   PerfTime100nSec.HighPart = " ) << m_DataBlock_p->PerfTime100nSec.HighPart << TEXT( "\n" );
   dump_context << TEXT( "   SystemNameLength         = " ) << m_DataBlock_p->SystemNameLength         << TEXT( "\n" );
   dump_context << TEXT( "   SystemNameOffset         = " ) << m_DataBlock_p->SystemNameOffset         << TEXT( "\n" );
}   

#if 0
void CPerformanceData::DumpPerfDataBlock( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "_PERF_OBJECT_TYPE\n{\n" );
   dump_context << TEXT( "   TotalByteLength      = " ) << m_DataBlock_p->TotalByteLength      << TEXT( "\n" );
   dump_context << TEXT( "   DefinitionLength     = " ) << m_DataBlock_p->DefinitionLength     << TEXT( "\n" );
   dump_context << TEXT( "   HeaderLength         = " ) << m_DataBlock_p->HeaderLength         << TEXT( "\n" );
   dump_context << TEXT( "   ObjectNameTitleIndex = " ) << m_DataBlock_p->ObjectNameTitleIndex << TEXT( "\n" );
   dump_context << TEXT( "   ObjectNameTitle      = " ) << m_DataBlock_p->ObjectNameTitle      << TEXT( "\n" );
   dump_context << TEXT( "   ObjectHelpTitleIndex = " ) << m_DataBlock_p->ObjectHelpTitleIndex << TEXT( "\n" );
   dump_context << TEXT( "   ObjectHelpTitle      = " ) << m_DataBlock_p->ObjectHelpTitle      << TEXT( "\n" );
   dump_context << TEXT( "   DetailLevel          = " ) << m_DataBlock_p->DetailLevel          << TEXT( "\n" );
   dump_context << TEXT( "   NumCounters          = " ) << m_DataBlock_p->NumCounters          << TEXT( "\n" );
   dump_context << TEXT( "   DefaultCounter       = " ) << m_DataBlock_p->DefaultCounter       << TEXT( "\n" );
   dump_context << TEXT( "   NumInstances         = " ) << m_DataBlock_p->NumInstances         << TEXT( "\n" );
   dump_context << TEXT( "   CodePage             = " ) << m_DataBlock_p->CodePage             << TEXT( "\n" );
   dump_context << TEXT( "   PerfTime.LowPart     = " ) << m_DataBlock_p->PerfTime.LowPart     << TEXT( "\n" );
   dump_context << TEXT( "   PerfTime.HighPart    = " ) << m_DataBlock_p->PerfTime.HighPart    << TEXT( "\n" );
   dump_context << TEXT( "   PerfFreq.LowPart     = " ) << m_DataBlock_p->PerfFreq.LowPart     << TEXT( "\n" );
   dump_context << TEXT( "   PerfFreq.HighPart    = " ) << m_DataBlock_p->PerfFreq.HighPart    << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}
#endif

#endif // _DEBUG

