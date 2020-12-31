// ==========================================================================
//                     Template Implementation : COXSPtr
// ==========================================================================

// Source file : OXSPtr.inl 

// Source : R.Mortelmans
// Creation Date : 	   19th December 1995
// Last Modification : 23rd January 1996
			  
// //////////////////////////////////////////////////////////////////////////
// Definition of static members

#ifndef new
#define new DEBUG_NEW
#define _REMOVE_DEBUG_NEW
#endif

#if defined(_DEBUG) && !defined(DISABLE_SMART_CHECK)
#include "OXSWatcher.h"
extern COXSmartWatcher smartWatcher;
// We will use sizeof(*pObj) to get the size of the object pointed to by the smart pointer
// This will not be correct when polymorhic assignment is used, but it's the best we can do
#define REG_PTR_OBJ(pObj)	smartWatcher.RegisterPointerAndObject(this, pObj, sizeof(*pObj))
#define UNREG_OBJ(pObj)		smartWatcher.UnRegisterObject(pObj)
#define UNREG_PTR(pObj)		smartWatcher.UnRegisterPointer(this, pObj)
#define IS_REG_OBJ(pObj)	smartWatcher.IsRegisteredObject(pObj)
#else
#define REG_PTR_OBJ(pObj)		
#define UNREG_OBJ(pObj)		
#define UNREG_PTR(pObj)	
#define IS_REG_OBJ(pObj)	(FALSE)
#endif // _DEBUG

// Use special ASSERT_VALID_SPTR macro to check the validity of a
//  smart pointer.  Because COXSPtr is not derived from CObject the
//  normal ASSERT_VALID does not work

#ifdef _DEBUG
#define ASSERT_VALID_SPTR(pSPtr)	(pSPtr)->AssertValid()
#else
#define ASSERT_VALID_SPTR(pSPtr)	
#endif // _DEBUG

// Data members -------------------------------------------------------------
// protected:
	// T* m_pSmartObject;
	// --- Pointer to the object this smart pointer references
	//     or NULL when the smart pointer does not point to anything

	// LONG* m_pnReferenceCount;
	// --- Pointer to the reference count of the object pointed to
	//     or NULL when the smart pointer does not point to anything
	//	   When the object is locked the reference count is a negative number

// private:
	
// Member functions ---------------------------------------------------------
// public:

template <class T> inline COXSPtr<T>::COXSPtr(const COXObjectCreator& objCreator /* = NEW_OBJECT */)
	:
	m_pSmartObject(NULL),
	m_pnReferenceCount(NULL)
	{
	UNUSED(objCreator);
	ASSERT_VALID_SPTR(this);
	// ... May only be used to create a new object
	ASSERT(&objCreator == &NEW_OBJECT);

	m_pSmartObject = new T;
	m_pnReferenceCount = new LONG(0);
	// ... Register new smart pointer (for debugging purposes only)
	Grab();

	ASSERT_VALID_SPTR(this);
	}

#ifndef ENABLE_SMART_WRAPPER
template <class T> inline COXSPtr<T>::COXSPtr(const COXObjectCreator* pNull)
	:
	m_pSmartObject(NULL),
	m_pnReferenceCount(NULL)
	{
	UNUSED(pNull);
	// ... May only assign NULL pointer
	ASSERT(pNull == NULL);
	ASSERT_VALID_SPTR(this);
	}

#else

template <class T> inline COXSPtr<T>::COXSPtr(T* pSObj)
	:
	m_pSmartObject(pSObj),
	m_pnReferenceCount(NULL)
	{
	// ... May only assign valid object
	ASSERT(pSObj == NULL || AfxIsValidAddress(pSObj, sizeof(T)));

	if (pSObj != NULL)
		{
		m_pnReferenceCount = new LONG(0);
		// Make sure this object does not have another smart pointer wrapped
		// around it yet : For polymorhic assignemnt use SmartUpCast or operator<<=
		ASSERT(!IS_REG_OBJ(m_pSmartObject));
		// ... Register new smart pointer (for debugging purposes only)
		Grab();
		}

	ASSERT_VALID_SPTR(this);
	}
#endif // ENABLE_SMART_WRAPPER

template <class T> inline COXSPtr<T>::COXSPtr(const COXSPtr& sPtr)
	:
	m_pSmartObject(sPtr.m_pSmartObject),
	m_pnReferenceCount(sPtr.m_pnReferenceCount)
	{
	ASSERT_VALID_SPTR(&sPtr);
	ASSERT_VALID_SPTR(this);

	if (m_pSmartObject != NULL)
		{
		// ... Should at least have one reference
		ASSERT(sPtr.m_pnReferenceCount != NULL);
		ASSERT(*sPtr.m_pnReferenceCount != 0);
		Grab();
		}

	ASSERT_VALID_SPTR(this);
	}

template <class T> inline COXSPtr<T>& COXSPtr<T>::operator=(const COXSPtr<T>& sPtr)
    {
	ASSERT_VALID_SPTR(this);
	ASSERT_VALID_SPTR(&sPtr);

	// ... Make sure that assigning the same smart element (a = a) works too
	if (m_pSmartObject != sPtr.m_pSmartObject)
		{
		if (m_pSmartObject != NULL)
		    Release(); 
		m_pSmartObject = sPtr.m_pSmartObject;
		m_pnReferenceCount = NULL;
		if (m_pSmartObject != NULL)
			{
			// ... Should at least have one reference
			ASSERT(sPtr.m_pnReferenceCount != NULL);
			ASSERT(*sPtr.m_pnReferenceCount != 0);
			m_pnReferenceCount = sPtr.m_pnReferenceCount;
	    	Grab(); 
			}
		}

	ASSERT_VALID_SPTR(this);
    return *this; 
    }

template <class T> inline COXSPtr<T>& COXSPtr<T>::operator=(const COXObjectCreator& objCreator)
    {
	ASSERT_VALID_SPTR(this);
	// ... May only be used to create a new object
	ASSERT(&objCreator == &NEW_OBJECT);

	if (m_pSmartObject != NULL)
	    Release(); 
	m_pSmartObject = new T;
	m_pnReferenceCount = new LONG(0);
	// ... Register new smart pointer (for debugging purposes only)
	Grab();

	ASSERT_VALID_SPTR(this);
    return *this; 
    }

#ifndef ENABLE_SMART_WRAPPER
template <class T> inline COXSPtr<T>& COXSPtr<T>::operator=(const COXObjectCreator* pNull)
	{
	UNUSED(pNull);
	ASSERT_VALID_SPTR(this);
	// ... May only assign smart NULL pointer
	ASSERT(pNull == NULL);

	if (m_pSmartObject != NULL)
	    Release(); 
	m_pSmartObject = NULL;

	ASSERT_VALID_SPTR(this);
    return *this; 
    }

#else

template <class T> inline COXSPtr<T>& COXSPtr<T>::operator=(T* pSObj) 
	{
	ASSERT_VALID_SPTR(this);
	ASSERT(pSObj == NULL || AfxIsValidAddress(pSObj, sizeof(T)));

	// ... Make sure that assigning the same smart element (a = a) works too
	if (m_pSmartObject != pSObj)
		{
		if (m_pSmartObject != NULL)
		    Release(); 
		m_pSmartObject = pSObj;
		m_pnReferenceCount = NULL;
		if (m_pSmartObject != NULL)
			{
			m_pnReferenceCount = new LONG(0);
			// Make sure this object does not have another smart pointer wrapped
			// around it yet : For polymorhic assignemnt use SmartUpCast or operator<<=
			ASSERT(!IS_REG_OBJ(m_pSmartObject));
			// ... Register new smart pointer (for debugging purposes only)
			Grab();
			}
		}

	ASSERT_VALID_SPTR(this);
    return *this; 
    }
#endif // ENABLE_SMART_WRAPPER

template <class T> inline T& COXSPtr<T>::operator*() const
	{ 
	ASSERT_VALID_SPTR(this);
	if (m_pSmartObject == NULL)
		{
		TRACE(TEXT("COXSPtr<T>::operator* : Trying to dereference a NULL pointer, throwing memory exception\n"));
		ASSERT(FALSE);
		AfxThrowMemoryException();
		}
	return *m_pSmartObject; 
	}

template <class T> inline T* COXSPtr<T>::operator->() const
	{ 
	ASSERT_VALID_SPTR(this);
	if (m_pSmartObject == NULL)
		{
		TRACE(TEXT("COXSPtr<T>::operator-> : Trying to dereference a NULL pointer, throwing memory exception\n"));
		ASSERT(FALSE);
		AfxThrowMemoryException();
		}
	return m_pSmartObject; 
	}

template <class T> inline COXSPtr<T>::operator T*()  const
	{ 
	ASSERT_VALID_SPTR(this);
	return m_pSmartObject; 
	}


template <class T> inline BOOL COXSPtr<T>::operator!() const
	{
	ASSERT_VALID_SPTR(this);
	return (m_pSmartObject == NULL);
	}

template <class T> inline BOOL COXSPtr<T>::operator==(T* pSObj) const
	{
	ASSERT_VALID_SPTR(this);
	return (m_pSmartObject == pSObj);
	}

template <class T> inline BOOL COXSPtr<T>::operator!=(T* pSObj) const
	{
	ASSERT_VALID_SPTR(this);
	return (m_pSmartObject != pSObj);
	}

#ifndef DISABLE_SMART_SERIALIZATION
template <class T> inline CArchive& AFXAPI operator<<(CArchive& ar, const COXSPtr<T>& pSObj)
	{
	ASSERT_VALID_SPTR(&pSObj);
	// Let the object archive itself
	ar << pSObj.m_pSmartObject;
	return ar;	
	}

template <class T> inline CArchive& AFXAPI operator>>(CArchive& ar, COXSPtr<T>& pSObj)
	{
	ASSERT_VALID_SPTR(&pSObj);
	T* pObj = NULL;

	// Create an object dynamically when archiving
	ar >> pObj;

	// Store the newly read object in this smart pointer
	if (pSObj.m_pSmartObject != NULL)
		pSObj.Release(); 
	pSObj.m_pSmartObject = pObj;
	pSObj.m_pnReferenceCount = NULL;

	if (pSObj.m_pSmartObject != NULL)
		{
		pSObj.m_pnReferenceCount = new LONG(0);
		// ... Register new smart pointer (for debugging purposes only)
		pSObj.Grab();
		}

	ASSERT_VALID_SPTR(&pSObj);

	return ar;	
	}
#endif // DISABLE_SMART_SERIALIZATION

template <class T> inline COXSPtr<T>& COXSPtr<T>::PolyAssign(T* pSObj, LONG* pnReferenceCount)
    {
	ASSERT_VALID_SPTR(this);

	// ... May only assign valid object
	ASSERT(pSObj == NULL || AfxIsValidAddress(pSObj, sizeof(T)));
	ASSERT(pnReferenceCount == NULL || AfxIsValidAddress(pnReferenceCount, sizeof(LONG)));

	// ... Make sure that assigning the same smart element (a = a) works too
	if (m_pSmartObject != pSObj)
		{
		if (m_pSmartObject != NULL)
		    Release(); 
		m_pSmartObject = pSObj;
		m_pnReferenceCount = NULL;
		if (m_pSmartObject != NULL)
			{
			// ... Should at least have one reference
			ASSERT(pnReferenceCount != NULL);
			ASSERT(*pnReferenceCount != 0);
			m_pnReferenceCount = pnReferenceCount;
	    	Grab(); 
			}
		}

	ASSERT_VALID_SPTR(this);
    return *this; 
    }

template <class T> inline LONG* COXSPtr<T>::GetRefCountAddress() const
	{
	ASSERT_VALID_SPTR(this);
	return m_pnReferenceCount;
	}

#ifdef ENABLE_SMART_WRAPPER
template <class T> inline void COXSPtr<T>::Lock()
	{
	ASSERT_VALID_SPTR(this);
#ifdef _DEBUG
	if (m_pSmartObject == NULL)
		{
		ASSERT(m_pnReferenceCount == NULL);
		TRACE(TEXT("COXSPtr<T>::Lock : Trying to lock smart NULL pointer, ignoring\n"));
		}
#endif // _DEBUG
	// Make reference count negative to mark a locked object
	if (m_pnReferenceCount != NULL && 0 < *m_pnReferenceCount)
		*m_pnReferenceCount = -*m_pnReferenceCount;
	ASSERT_VALID_SPTR(this);
	}

template <class T> inline void COXSPtr<T>::Unlock()
	{
	ASSERT_VALID_SPTR(this);
#ifdef _DEBUG
	if (m_pSmartObject == NULL)
		{
		ASSERT(m_pnReferenceCount == NULL);
		TRACE(TEXT("COXSPtr<T>::Unlock : Trying to lock smart NULL pointer, ignoring\n"));
		}
#endif // _DEBUG
	// Make reference count positive to mark an unlocked object
	if (m_pnReferenceCount != NULL && *m_pnReferenceCount < 0)
		*m_pnReferenceCount = -*m_pnReferenceCount;
	ASSERT_VALID_SPTR(this);
	}

template <class T> inline BOOL COXSPtr<T>::IsLocked()
	{
	ASSERT_VALID_SPTR(this);
	return (m_pnReferenceCount != NULL && *m_pnReferenceCount < 0);
	}
#endif // ENABLE_SMART_WRAPPER

#ifdef _DEBUG
template <class T> inline void COXSPtr<T>::AssertValid() const
	{
	ASSERT(this != NULL);
	ASSERT(AfxIsValidAddress(this, sizeof(COXSPtr<T>)));
	ASSERT(m_pSmartObject == NULL || AfxIsValidAddress(m_pSmartObject, sizeof(T)));

	// Because thee next check has to many exceptions we skip it.
/*
#if defined(_INC_CRTDBG) && !defined(DISABLE_SMART_CHECK)
	// ... The next assert will fail if a block of memory was not allocated
	//      on the local heap. 
	//     NEVER allocate objects for smart pointers on the STACK !!!
	// ... Because of polymorphic assignment we use _msize(m_pSmartObject) instead of sizeof(T)
	// ... NOTE : This test may also fail if a dynamically linked library (DLL)
	//      contains a static link to the run-time library.
	// ... NOTE : If the object is not derived from CObject it will be allocated 
	//	   as a _NORMAL_BLOCK instead of _CLIENT_BLOCK.  
	//	   In this case you may recieve an assertion of the Debug Heap CRT library 
	//     (pHead->nBlockUse == nBlockUse). You may savely ignore this assert
	ASSERT(m_pSmartObject == NULL || 
		_CrtIsMemoryBlock((const void *)m_pSmartObject, _msize_dbg(m_pSmartObject, _CLIENT_BLOCK), NULL, NULL, NULL));
#endif // _INC_CRTDBG
*/
	ASSERT(m_pnReferenceCount == NULL || AfxIsValidAddress(m_pnReferenceCount, sizeof(LONG)));
	ASSERT( (m_pSmartObject == NULL && m_pnReferenceCount == NULL) ||
			(m_pSmartObject != NULL && m_pnReferenceCount != NULL) );
	ASSERT(m_pnReferenceCount == NULL || *m_pnReferenceCount != 0);
#ifndef ENABLE_SMART_WRAPPER
	ASSERT(m_pnReferenceCount == NULL || 0 <= *m_pnReferenceCount);
#endif // ENABLE_SMART_WRAPPER
	}
#endif // _DEBUG

template <class T> inline COXSPtr<T>::~COXSPtr()
	{
	ASSERT_VALID_SPTR(this);
	if (m_pSmartObject != NULL)
		Release();
	}

// protected:
template <class T> inline LONG COXSPtr<T>::Grab()
	// --- In  : 
	// --- Out : 
	// --- Returns : The reference count after Grab()
	// --- Effect : Increases the reference count by 1 for not locked objects
	//				otherwise the reference count is decreased by 1
	{
	ASSERT(m_pnReferenceCount != NULL);
	REG_PTR_OBJ(m_pSmartObject);
#ifndef ENABLE_SMART_WRAPPER
	ASSERT(0 <= *m_pnReferenceCount);
	(*m_pnReferenceCount)++;
	return *m_pnReferenceCount;
#else
	if (0 <= *m_pnReferenceCount)
		{
		(*m_pnReferenceCount)++;
		return *m_pnReferenceCount;
		}
	else
		// Object is locked : use negative reference count
		{
		(*m_pnReferenceCount)--;
		// ... Always return a positive number
		return -*m_pnReferenceCount;
		}
#endif // ENABLE_SMART_WRAPPER
	}

template <class T> inline LONG COXSPtr<T>::Release()
	// --- In  : 
	// --- Out : 
	// --- Returns : The reference count after Release()
	// --- Effect : Decreases the reference count of non-locked objects by 1 
	//				for loked objects the reference count is increased by 1
	//				Deletes the object and the reference count when 0 is reached
	{
	ASSERT_VALID_SPTR(this);
	ASSERT(m_pnReferenceCount != NULL);
	ASSERT(*m_pnReferenceCount != 0);

	LONG nTempReferenceCount = 0;
   	if (*m_pnReferenceCount == 1)
		{
		// ... Unregister smart pointer (for debugging purposes only)
		UNREG_OBJ(m_pSmartObject);
		// ... Object will be deleted and thus does not have to be reachable
		UNREG_PTR(NULL);
		delete m_pnReferenceCount;
		delete m_pSmartObject;
		}
#ifndef ENABLE_SMART_WRAPPER
	else 
		{
		ASSERT(0 < *m_pnReferenceCount);
		nTempReferenceCount = --(*m_pnReferenceCount);
		UNREG_PTR(m_pSmartObject);
		}
#else
   	else if (*m_pnReferenceCount == -1)
		{
		// Reference count of locked object reached 0, object NOT deleted
		// ... Unregister smart pointer (for debugging purposes only)
		UNREG_OBJ(m_pSmartObject);
		// ... Object will be deleted and thus does not have to be reachable
		UNREG_PTR(NULL);
		delete m_pnReferenceCount;
		}
	else 
		{
		if (0 <= *m_pnReferenceCount)
			nTempReferenceCount = --(*m_pnReferenceCount);
		else
			// ... Object is locked : use negative reference count
			// ... Always return a positive number
			nTempReferenceCount = -(++(*m_pnReferenceCount));
		UNREG_PTR(m_pSmartObject);
		}
#endif // ENABLE_SMART_WRAPPER

	m_pnReferenceCount = NULL;
	m_pSmartObject = NULL;
	return nTempReferenceCount;
	}


// private:

#ifdef _REMOVE_DEBUG_NEW
#undef new
#undef _REMOVE_DEBUG_NEW
#endif
// ==========================================================================
