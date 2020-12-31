#if ! defined( PERFORMANCE_COUNTER_DEFINITION_CLASS_HEADER )

#define PERFORMANCE_COUNTER_DEFINITION_CLASS_HEADER

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

class CPerformanceCounterDefinition : public CObject
{
   protected:

      PPERF_COUNTER_DEFINITION m_Pointer;

   public:

      CPerformanceCounterDefinition();
      CPerformanceCounterDefinition( PPERF_COUNTER_DEFINITION pointer );
     ~CPerformanceCounterDefinition();

     virtual void Copy( PPERF_COUNTER_DEFINITION source ); 
     virtual void TranslateType( CString& return_string ) const;
};

#endif // PERFORMANCE_COUNTER_DEFINITION_CLASS_HEADER
