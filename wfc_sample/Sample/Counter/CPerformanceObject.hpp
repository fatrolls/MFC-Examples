#if ! defined( PERFORMANCE_OBJECT_CLASS_HEADER )

#define PERFORMANCE_OBJECT_CLASS_HEADER

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

class CPerformanceInstance;

class CPerformanceObject : public CObject
{
   protected:

      PPERF_OBJECT_TYPE m_ThisObject;

      CPtrArray m_CounterDefinitions;

      virtual PPERF_INSTANCE_DEFINITION m_GetFirstInstance( void ) const;

      virtual void m_InitializeCounterDefinitions( void );

   public:

      CPerformanceObject( PPERF_OBJECT_TYPE data );
     ~CPerformanceObject();

      virtual void  Copy( const CPerformanceObject& source );
      virtual void  GetAt( DWORD index );
      virtual DWORD GetNumberOfCounters( void ) const;

#if defined( _DEBUG )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // PERFORMANCE_OBJECT_CLASS_HEADER
