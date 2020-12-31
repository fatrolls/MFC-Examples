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

CPerformanceInstance::CPerformanceInstance( CPerformanceObject& object )
{
   m_Object_p          = &object;
   m_FirstInstance     = m_Object_p->GetFirstInstance();
   m_ThisInstance      = m_FirstInstance;
   m_InstanceNumber    = 1;
   m_NumberOfInstances = m_Object_p->GetNumberOfInstances();
}

CPerformanceInstance::~CPerformanceInstance()
{
   m_FirstInstance = NULL;
}

PPERF_COUNTER_DEFINITION CPerformanceInstance::GetFirstCounter( void ) const
{
   return( m_Object_p->GetFirstCounter() );
}

BOOL CPerformanceInstance::GetNext( void )
{
   if ( m_InstanceNumber < m_NumberOfInstances )
   {
      // m_ThisInstance = 
      return( TRUE );
   }

   return( FALSE );
}

void CPerformanceInstance::Rewind( void )
{
   m_ThisInstance   = m_FirstInstance;
   m_InstanceNumber = 1;
}

DWORD CPerformanceInstance::GetNumberOfCounters( void ) const
{
   return( m_Object_p->GetNumberOfCounters() );
}
