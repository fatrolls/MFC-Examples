// SafeLocker.cpp: implementation of the CSafeLocker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SafeLocker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSafeLocker::CSafeLocker()
{
	m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
}


CSafeLocker::~CSafeLocker()
{
	// close handles
	if (m_hMutex != NULL)
	{
		::CloseHandle(m_hMutex);
	}
}


void CSafeLocker::Lock(void)
{
	// Unsignal the mutex, block the access
	::WaitForSingleObject(m_hMutex, INFINITE); 
}


void CSafeLocker::UnLock(void)
{
   	// Release the mutex ownership
	::ReleaseMutex(m_hMutex);

}	

   
BOOL CSafeLocker::CanLock(void)
{
	return (m_hMutex != NULL);
}


