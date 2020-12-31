#if ! defined( PERFORMANCE_DATA_CLASS_HEADER )

#define PERFORMANCE_DATA_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sblackbu@erols.com
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

/*
** Concept of operation
*/

// Open(), open a connection to a machine.

class CPerformanceData : public CObject
{
   protected:

      PPERF_DATA_BLOCK m_DataBlock_p;

      CStringArray m_CounterNames;

      CPtrArray m_PerformanceObjects; // Array of PPERF_OBJECT_TYPE's

      virtual void m_InitializeObjects( void );

   public:

      CPerformanceData( LPCTSTR machine_name = NULL );
      virtual ~CPerformanceData();

      virtual void  GetName( DWORD number, CString& string ) const;
      virtual DWORD GetNumberOfObjects( void ) const;
      virtual PPERF_OBJECT_TYPE GetObject( DWORD index ) const;

#if defined( _DEBUG )

      virtual void Dump( CDumpContext& dump_context ) const;
      virtual void DumpPerfDataBlock( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // PERFORMANCE_DATA_CLASS_HEADER
