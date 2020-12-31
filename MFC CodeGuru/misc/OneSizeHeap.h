///////////////////////////////////////////////////////////////////
// Header File OneSizeHeap.h
///////////////////////////////////////////////////////////////////
//
// 29/1/1997 18:52  Author: Poul A. Costinsky  poul@wizsoft.com
// Copyright (C) WizSoft Inc., 1997
///////////////////////////////////////////////////////////////////

#ifndef __CWizOneSizeHeap_H
#define __CWizOneSizeHeap_H

///////////////////////////////////////////////////////////////////
template<class TYPE, class ALLOCATOR>
class CWizOneSizeHeap
{
// Internal goodies
enum
	{ 
	STEP = 1024,		// default grow step
	SIZE = sizeof(TYPE)	// size of the object
	};

union DATA	// helper for managing the pool
	{
	char data[sizeof(TYPE)];// object place
	DATA* next;		// pointer to the next free chunk
	};

public:
// Constructor:
	CWizOneSizeHeap(int Step = -1);
// Destructor:
	~CWizOneSizeHeap();
// Operations:
	int Size()		const { return m_nSize - m_nFreeSize; }
	bool IsEmpty()	const { return (m_Pool == NULL); }

	TYPE* Alloc();
	void Free (void *p);
protected:
// Implementation:
	void TestRelease();
	void TestPool();
	void InitPool();
	void ReallocPool();
	void InitPointers ();
private:
	// data members
	ALLOCATOR	m_All;
	DATA*		m_Pool;
	DATA*		m_pFirstFree;
	int			m_nStep;
	int			m_nSize;
	int			m_nFreeSize;
};
///////////////////////////////////////////////////////////////////
namespace CWizOneSizeHeapAllocators
{
	///////////////////////////////////////////////////////////////////
	class CMallocator  // simple allocator which gets the memory from malloc
	{
	public:
		CMallocator()						{}
		~CMallocator()						{}
		static void* Alloc(size_t& size)	{ return ::malloc(size); }
		static void Free(void* p)			{ ::free(p); }
		static void* ReAlloc(size_t &size, void *p);
	};
	///////////////////////////////////////////////////////////////////
	// Don't use this class! Use CGlobalHeapAllocator or CLocalHeapAllocator!!!
	class CWin32HeapAllocator	// Gets memory right from Win32 API.
	{
	protected: // Don't use it directly!
		CWin32HeapAllocator() : m_hHeap (NULL) {}
	public:
		~CWin32HeapAllocator() {}
		void* Alloc(size_t& size);
		void Free(void* p);
		void* ReAlloc(size_t &size, void *p);

	protected:
		void * _Alloc   (size_t size);
		void * _ReAlloc (size_t size, void *p);
		int  _Size	(void *p);
		void TestHeap();
		UINT Retry();

		HANDLE m_hHeap;
	};
	///////////////////////////////////////////////////////////////////
	class CGlobalHeapAllocator : public CWin32HeapAllocator
	{
	public:
		CGlobalHeapAllocator()	{ m_hHeap = GetProcessHeap(); }
	};
	///////////////////////////////////////////////////////////////////
	class CLocalHeapAllocator : public CWin32HeapAllocator
	{
	public:
		CLocalHeapAllocator()	{}
		~CLocalHeapAllocator()	{ ::HeapDestroy(m_hHeap); }
	};
}; // namespace
///////////////////////////////////////////////////////////////////
// Macros to minimize typing:
///////////////////////////////////////////////////////////////////
//==================================================================
#define DECLARE_ONE_SIZE_PRIVATE_HEAP	\
void *operator new (size_t size);		\
void  operator delete (void* p);	
//==================================================================
#define IMPLEMENT_ONE_SIZE_PRIVATE_HEAP(allocator, dataclass)	\
namespace { CWizOneSizeHeap<dataclass,allocator> theHeap; };	\
void * dataclass::operator new (size_t size)					\
{																\
	ASSERT(size == sizeof(dataclass));							\
	return theHeap.Alloc();										\
}																\
void  dataclass::operator delete (void* p)						\
{																\
	theHeap.Free(p);											\
}
//==================================================================
///////////////////////////////////////////////////////////////////
// Concrete heaps to use:
///////////////////////////////////////////////////////////////////
// malloc's heap
///////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizOneSizeMallocHeap : 
	public CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CMallocator>
{
public:
	CWizOneSizeMallocHeap(int Step = -1)
		: CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CMallocator>(Step) {}
};
///////////////////////////////////////////////////////////////////
// CLocalHeapAllocator's heap
///////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizOneSizeLocalHeap : 
	public CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CLocalHeapAllocator>
{
public:
	CWizOneSizeLocalHeap(int Step = -1)
		: CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CLocalHeapAllocator>(Step) {}
};
///////////////////////////////////////////////////////////////////
// CGlobalHeapAllocator's heap
///////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizOneSizeGlobalHeap : 
	public CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CGlobalHeapAllocator>
{
public:
	CWizOneSizeGlobalHeap(int Step = -1)
		: CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CGlobalHeapAllocator>(Step) {}
};
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
// Implementation:
// 
///////////////////////////////////////////////////////////////////
//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline
CWizOneSizeHeap<TYPE, ALLOCATOR>::CWizOneSizeHeap(int Step) 
		: m_Pool(NULL) , m_pFirstFree (NULL),
		  m_nStep(Step), m_nSize(0), m_nFreeSize(0)
{
	ASSERT(sizeof(DATA) == SIZE);
	// adjust step to reasonable value
	if (m_nStep < STEP) 
		m_nStep = STEP;
	else 
		m_nStep = ((m_nStep + STEP - 1)/STEP)*STEP;
}
//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline
CWizOneSizeHeap<TYPE, ALLOCATOR>::~CWizOneSizeHeap()
{
	if (m_Pool != NULL) 
		m_All.Free(m_Pool);
}
//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline
TYPE* CWizOneSizeHeap<TYPE, ALLOCATOR>::Alloc()
{
	TestPool();

	ASSERT(m_pFirstFree != NULL);
	TYPE* p = (TYPE *)m_pFirstFree;
	m_pFirstFree = m_pFirstFree->next;
	m_nFreeSize--;
	return p;
}
//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline
void CWizOneSizeHeap<TYPE, ALLOCATOR>::Free (void *p)
{
	DATA* p1 = (DATA *)p;
	ASSERT(p1 >= m_Pool);
	ASSERT(p1 <  m_Pool + m_nSize);
	// If the pool was empty - here it is!
	if(m_pFirstFree == NULL)
		{
		m_pFirstFree = p1;
		m_pFirstFree->next = NULL;
		m_nFreeSize++;
		}
	// the new chunk becomes the first free one
	else
		{
		p1->next = m_pFirstFree;
		m_pFirstFree = p1;
		m_nFreeSize++;
		// If all the pool is free - release it
		TestRelease();
		}
}
//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline
void CWizOneSizeHeap<TYPE, ALLOCATOR>::TestRelease()
{
	// Since you're not going to allocate one object from the pool,
	// it's desirable to release all the pool when last object gone.
	if (m_Pool == NULL || m_nFreeSize < m_nSize)
		return;
	ASSERT(m_nFreeSize == m_nSize);
	m_All.Free(m_Pool);
	m_Pool = m_pFirstFree = NULL;
	m_nSize = m_nFreeSize = 0;		
}
//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline
void CWizOneSizeHeap<TYPE, ALLOCATOR>::TestPool()
{
	if (m_Pool == NULL)
		InitPool();
	if(m_pFirstFree == NULL)
		ReallocPool();
}
//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline
void CWizOneSizeHeap<TYPE, ALLOCATOR>::InitPool()
{
	ASSERT(m_nSize == 0);
	ASSERT(m_pFirstFree == NULL);
	size_t s = m_nStep*SIZE;
	m_Pool = (DATA*)m_All.Alloc(s);
	if (m_Pool == NULL)
		AfxThrowMemoryException();
	s /= SIZE;
	m_pFirstFree = m_Pool;
	m_nSize = s;
	m_nFreeSize = m_nSize;
	InitPointers ();
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline
void CWizOneSizeHeap<TYPE, ALLOCATOR>::ReallocPool()
{
	register size_t delta = m_nStep;
	const size_t s = (m_nSize + m_nStep)*SIZE;
	size_t s1 = s;
	DATA* p = (DATA*)m_All.ReAlloc(s1, m_Pool);
	if (p == NULL)
		AfxThrowMemoryException();
	ASSERT(m_Pool == p);
	if (s != s1)
		{
		delta = (s - s1)/SIZE;
		if (delta == 0)
			AfxThrowMemoryException();
		}
	m_pFirstFree = m_Pool + delta;
	m_nSize		+= delta;
	m_nFreeSize += delta;
	InitPointers ();
}
//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline
void CWizOneSizeHeap<TYPE, ALLOCATOR>::InitPointers ()
{
	DATA* p = m_pFirstFree;
	for (INDEX i = 0; i < m_nStep; i++, p++)
		p->next = p + 1;
}
///////////////////////////////////////////////////////////////////
namespace CWizOneSizeHeapAllocators
{

//*****************************************************************
inline void* CMallocator::ReAlloc(size_t &size, void *p) 
{ 
	void* p1 = ::_expand(p, size);
	// if expand cannot get the full size, it tries to do the best.
	if (p1 == NULL)
		{
		size_t size1 = _msize(p);
		if (size1 > size)
			{
			size = size1;
			p1 = p;
			}
		else
			size = 0;
		}
	return p1;
}
//*****************************************************************
enum
	{
	INITIAL_HEAP_SIZE = 65536, // 64K
	MAXIMUM_HEAP_SIZE = 0 // 64K
	};

//*****************************************************************
inline
void* CWin32HeapAllocator::Alloc(size_t& size) 
{ 
	TestHeap();
	void* p = _Alloc(size);
	if(p == NULL)
		{
		Retry();
		p = _Alloc(size);
		if (p == NULL)
			return NULL;
		}
	size = _Size(p);
	return p;
}
//*****************************************************************
inline
void CWin32HeapAllocator::Free(void* p)		
{ 
	if(p)
		::HeapFree(m_hHeap, 0, p);
}
//*****************************************************************
inline
void* CWin32HeapAllocator::ReAlloc(size_t &size, void *p) 
{ 
	TestHeap();
	void* p1 = _ReAlloc(size, p);
	if (p1 == NULL)
		{
		const UINT u = Retry();
		p1 = _ReAlloc(size, p);
		if (p1 == NULL)
			return NULL;
		}
	p = p1;
	size = _Size(p);
	return p;
}

//*****************************************************************
inline
void * CWin32HeapAllocator::_Alloc   (size_t size)	
{ 
	return ::HeapAlloc(m_hHeap, 0, size); 
}

//*****************************************************************
inline
void * CWin32HeapAllocator::_ReAlloc (size_t size, void *p) 
{ 
	return ::HeapReAlloc(m_hHeap, HEAP_REALLOC_IN_PLACE_ONLY, p, size); 
}

//*****************************************************************
inline
int  CWin32HeapAllocator::_Size	(void *p)		
{ 
	return ::HeapSize(m_hHeap, 0, p); 
}
//*****************************************************************
inline
void CWin32HeapAllocator::TestHeap()
{
	if (m_hHeap != NULL)
		return;

	m_hHeap = ::HeapCreate(0, INITIAL_HEAP_SIZE, MAXIMUM_HEAP_SIZE);
	if (m_hHeap == NULL)
		AfxThrowMemoryException();
}

//*****************************************************************
inline
UINT CWin32HeapAllocator::Retry()
{	
	return ::HeapCompact(m_hHeap, 0); 
}

}; // namespace

///////////////////////////////////////////////////////////////////

#endif // __CWizOneSizeHeap_H
