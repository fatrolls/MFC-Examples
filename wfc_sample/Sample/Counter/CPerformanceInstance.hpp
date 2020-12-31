#if ! defined( PERFORMANCE_INSTANCE_CLASS_HEADER )

#define PERFORMANCE_INSTANCE_CLASS_HEADER

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

class CPerformanceInstance : public CObject
{
   protected:

      CPerformanceObject * m_Object_p;

      PPERF_INSTANCE_DEFINITION m_ThisInstance;
      PPERF_INSTANCE_DEFINITION m_FirstInstance;

      LONG m_InstanceNumber;
      LONG m_NumberOfInstances;

   public:

      CPerformanceInstance( CPerformanceObject& object );
     ~CPerformanceInstance();

      virtual BOOL GetNext( void );
      virtual DWORD GetNumberOfCounters( void ) const;
      virtual PPERF_COUNTER_DEFINITION GetFirstCounter( void ) const;
      virtual void  Rewind( void );

#if defined( _DEBUG )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // PERFORMANCE_INSTANCE_CLASS_HEADER
