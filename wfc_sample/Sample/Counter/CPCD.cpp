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

CPerformanceCounterData::CPerformanceCounterData( CPerformanceCounter& counter )
{
   m_Counter_p = &counter;
}

CPerformanceCounterData::~CPerformanceCounterData()
{
   m_Counter_p = NULL;
}
