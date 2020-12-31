#if ! defined( PERFORMANCE_COUNTER_DATA_CLASS_HEADER )

#define PERFORMANCE_COUNTER_DATA_CLASS_HEADER

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

class CPerformanceCounterData : public CObject
{
   protected:

      CPerformanceCounter * m_Counter_p;

   public:

      CPerformanceCounterData( CPerformanceCounter& counter );
     ~CPerformanceCounterData();

#if defined( _DEBUG )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // PERFORMANCE_COUNTER_DATA_CLASS_HEADER
