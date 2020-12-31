/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Implementation File localhep.cpp
// class CWizLocalHeap
//
// 30/10/1995 16:38                             Author: Poul
///////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "localhep.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////
// class CWizLocalHeap

#define new DEBUG_NEW
//*****************************************************************
// Default Constructor
CWizLocalHeap::CWizLocalHeap( 	DWORD  flOptions, DWORD  dwInitialSize,
    				DWORD  dwMaximumSize)
		:	m_hHeap (NULL)
{
	m_hHeap = ::HeapCreate(flOptions, dwInitialSize, dwMaximumSize);
	if (m_hHeap == NULL)
		AfxThrowMemoryException();
}
//*****************************************************************
// Destructor
CWizLocalHeap::~CWizLocalHeap()
{
	if (m_hHeap != NULL)
		VERIFY(::HeapDestroy(m_hHeap));
}
//*****************************************************************
void	CWizLocalHeap::Compact (DWORD  dwFlags)
{
	const DWORD POSSIBLE_COMPACT_FLAGS = HEAP_NO_SERIALIZE;
	::HeapCompact(m_hHeap, dwFlags & POSSIBLE_COMPACT_FLAGS);
}
//*****************************************************************
const DWORD POSSIBLE_ALLOC_FLAGS = 	HEAP_GENERATE_EXCEPTIONS |
					HEAP_NO_SERIALIZE | 
					HEAP_ZERO_MEMORY;

LPVOID  CWizLocalHeap::Alloc(DWORD  dwBytes, DWORD  dwFlags)
{
	ASSERT((dwFlags & ~POSSIBLE_ALLOC_FLAGS) == 0);
	LPVOID lpMem = ::HeapAlloc(m_hHeap, dwFlags, dwBytes);
	if (lpMem == NULL)
		{
		Compact (dwFlags);
		lpMem = ::HeapAlloc(m_hHeap, dwFlags, dwBytes);
		if (lpMem == NULL)
			AfxThrowMemoryException();
		}
	return lpMem;
}

//*****************************************************************
LPVOID  CWizLocalHeap::ReAlloc(DWORD  dwBytes, LPVOID  lpMem, DWORD  dwFlags)
{
	if (lpMem == NULL)
		return Alloc(dwBytes, dwFlags & POSSIBLE_ALLOC_FLAGS);
	LPVOID lpRetMem = ::HeapReAlloc(m_hHeap, dwFlags, lpMem, dwBytes);
	if (lpRetMem == NULL)
		{
		Compact (dwFlags);
		lpRetMem = ::HeapReAlloc(m_hHeap, dwFlags, lpMem, dwBytes);
		if (lpRetMem == NULL)
			AfxThrowMemoryException();
		}
	return lpRetMem;
}
//*****************************************************************
