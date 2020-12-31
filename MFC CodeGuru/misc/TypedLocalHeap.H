/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File TypedLocalHeap.h
// class CWizTypedLocalHeap
//
// 07/04/1996 21:22                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizTypedLocalHeap_H
#define __CWizTypedLocalHeap_H

#include "localhep.h"

/////////////////////////////////////////////////////////////////////////////
// class CWizTypedLocalHeap
template <DWORD flOptions, DWORD  dwInitialSize, 
		DWORD  dwMaximumSize, DWORD dwAllocFlags, DWORD dwReAllocFlags, DWORD dwFreeFlags>
class CWizTypedLocalHeap : public CWizLocalHeap
{
public:
// Constructors:
	CWizTypedLocalHeap ()
		: CWizLocalHeap (flOptions,dwInitialSize,dwMaximumSize)
			{}
// Destructor:
	~CWizTypedLocalHeap () {}
public:
// Operations:
	void*  Alloc   (size_t size)
		{ return CWizLocalHeap::Alloc(size,dwAllocFlags); }
	void*  ReAlloc (void*  lpMem, size_t size)
		{ return CWizLocalHeap::ReAlloc(size,lpMem, dwReAllocFlags); }
	void	Free (void*  lpMem)
		{ CWizLocalHeap::Free (lpMem, dwFreeFlags); }
};

typedef	CWizTypedLocalHeap<CWizLocalHeap::DEFAULT_OPTIONS,
							CWizLocalHeap::DEFAULT_INI_SIZE,
							CWizLocalHeap::DEFAULT_MAX_SIZE,
							CWizLocalHeap::DEFAULT_ALLOC_FLAGS,
							CWizLocalHeap::DEFAULT_REALLOC_FLAGS,
							CWizLocalHeap::DEFAULT_FREE_FLAGS> CWizDefaultTypedLocalHeap;

/////////////////////////////////////////////////////////////////////////////
#define DECLARE_LOCAL_HEAP													\
public:																		\
	void* operator new (size_t size)										\
		{ return m_cHeap.Alloc(size); }										\
	void  operator delete(void* p)											\
		{ m_cHeap.Free(p);     }											\
	static CWizTypedLocalHeap<CWizLocalHeap::DEFAULT_OPTIONS,				\
							CWizLocalHeap::DEFAULT_INI_SIZE,				\
							CWizLocalHeap::DEFAULT_MAX_SIZE,				\
							CWizLocalHeap::DEFAULT_ALLOC_FLAGS,				\
							CWizLocalHeap::DEFAULT_REALLOC_FLAGS,			\
							CWizLocalHeap::DEFAULT_FREE_FLAGS> m_cHeap;
#define IMPLEMENT_LOCAL_HEAP(TYPE)											\
	CWizTypedLocalHeap<CWizLocalHeap::DEFAULT_OPTIONS,						\
							CWizLocalHeap::DEFAULT_INI_SIZE,				\
							CWizLocalHeap::DEFAULT_MAX_SIZE,				\
							CWizLocalHeap::DEFAULT_ALLOC_FLAGS,				\
							CWizLocalHeap::DEFAULT_REALLOC_FLAGS,			\
							CWizLocalHeap::DEFAULT_FREE_FLAGS> TYPE::m_cHeap;
/////////////////////////////////////////////////////////////////////////////
#endif // __CWizTypedLocalHeap_H


