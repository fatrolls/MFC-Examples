/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File localhep.h
// class CWizLocalHeap
//
// 30/10/1995 16:38                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizLocalHeap_H
#define __CWizLocalHeap_H

/////////////////////////////////////////////////////////////////////////////
// class CWizLocalHeap 
// NOTE!!!!
// All function can throw CMemoryException.
// No function returns NULL except 
// ReAlloc with HEAP_REALLOC_IN_PLACE_ONLY flag!!!
class CWizLocalHeap
{
public:
friend class CWizLocalHeapLock;
// Constructors:
	enum { 	DEFAULT_OPTIONS = 0,
		DEFAULT_INI_SIZE = 0,
		DEFAULT_MAX_SIZE = 0,
		DEFAULT_ALLOC_FLAGS = HEAP_ZERO_MEMORY,
		DEFAULT_REALLOC_FLAGS = HEAP_ZERO_MEMORY,
		DEFAULT_FREE_FLAGS = 0
	     };
	CWizLocalHeap ( DWORD  flOptions = DEFAULT_OPTIONS,	// heap allocation flag 
    			DWORD  dwInitialSize = DEFAULT_INI_SIZE,	// initial heap size 
    			DWORD  dwMaximumSize = DEFAULT_MAX_SIZE	// maximum heap size 
			);
private:
// No need and don't allow to compiler to generate default ones:
	CWizLocalHeap(CWizLocalHeap& T);
	CWizLocalHeap& operator=(CWizLocalHeap& T);
public:
// Destructor:
	~CWizLocalHeap ();
public:
// Operations:
	LPVOID  Alloc   (DWORD  dwBytes, DWORD  dwFlags = DEFAULT_ALLOC_FLAGS);
	LPVOID  ReAlloc (DWORD  dwBytes, LPVOID  lpMem, DWORD  dwFlags = DEFAULT_REALLOC_FLAGS);
	void	Free    (LPVOID  lpMem, DWORD  dwFlags = DEFAULT_FREE_FLAGS)
		{ VERIFY(::HeapFree(m_hHeap, dwFlags, lpMem)); }

	void	Compact (DWORD  dwFlags = 0);
protected:
// Implementation:
protected:
// Members:
	HANDLE 	m_hHeap;

};

/////////////////////////////////////////////////////////////////////////////
// The CWizLocalHeapLock attempts to acquire 
// the critical section object, or lock, that is associated 
// with a specified heap. 
// If the function succeeds, the calling thread owns 
// the heap lock. Only the calling thread will be able 
// to allocate or release memory from the heap. 
// The execution of any other thread of the calling process 
// will be blocked if that thread attempts 
// to allocate or release memory from the heap. 
// Such threads will remain blocked until the thread 
// that owns the heap lock calls the HeapUnlock function.
class CWizLocalHeapLock
{
public:
// Constructors:
	CWizLocalHeapLock (CWizLocalHeap& Heap) : m_rHeap (Heap)
		{ VERIFY(::HeapLock   (m_rHeap.m_hHeap)); }
	~CWizLocalHeapLock()
		{ VERIFY(::HeapUnlock (m_rHeap.m_hHeap)); }
private:
	CWizLocalHeap& m_rHeap;
};
/////////////////////////////////////////////////////////////////////////////
#endif // __CWizLocalHeap_H


