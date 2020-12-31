/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Implementation File virt_mem.cpp
// class CWizVirtualMemory
//
// 08/06/1995 13:01                             Author: Poul
///////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "sys_data.h"

#include "virt_mem.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////
// class CWizVirtualMemory

#define new DEBUG_NEW

//*****************************************************************
// Constructor
CWizVirtualMemory::CWizVirtualMemory(DWORD nMaxSize, DWORD nIniSize,DWORD nSizeStep)
		:	m_pVoidData (NULL),
			m_nSizeStep (nSizeStep),
			m_nSize	    (0)
{
	m_nSizeStep = RoundUp(m_nSizeStep,
				gcSystemData.GetPageSize());

	m_pVoidData = ::VirtualAlloc(NULL, nMaxSize, MEM_RESERVE, PAGE_READWRITE);
	if (m_pVoidData == NULL)
		AfxThrowMemoryException();

	if (nIniSize > 0)
		Commit (nIniSize);
}
//*****************************************************************
// Constructor
CWizVirtualMemory::CWizVirtualMemory(DWORD nSize)
		:	m_pVoidData (NULL),
			m_nSizeStep (0xffff),
			m_nSize	    (nSize)
{
	m_pVoidData = ::VirtualAlloc(NULL, nSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (m_pVoidData == NULL)
		AfxThrowMemoryException();
}
//*****************************************************************
// Destructor
CWizVirtualMemory::~CWizVirtualMemory()
{
	if (m_pVoidData != NULL)
		::VirtualFree (m_pVoidData, 0, MEM_RELEASE);
}
//*****************************************************************
void CWizVirtualMemory::Commit(DWORD nSize)
{
	if (m_pVoidData == NULL)
		AfxThrowMemoryException();
	if (m_nSize >= nSize)
		return;

	DWORD nPhysSize = RoundUp (nSize, gcSystemData.GetPageSize());
	if(::VirtualAlloc (m_pVoidData, nPhysSize, MEM_COMMIT,PAGE_READWRITE) == NULL)
		AfxThrowMemoryException();
	m_nSize = nSize;
}

#if 0
void f()
{
	CWizTypedVMem<double> da(40);
	da [10] = 50.3;
	if (da [8] < 45.2)
		da [0] = -11.333;
}
#endif
