// ==========================================================================
// 						Template Specification : COXSPtr
// ==========================================================================

// Header file : OXSPtr.h

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	NO	Derived from 

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions
//			(CMemoryException by NULL-pointer dereference)

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class works together with CObject derived classesto provide 
//   a solution for smart pointers and objects
//	All access to the object must be done through its smart pointer

// 	Normally construction of the object is done together with the
//	 smart pointer.  So when a smart pointer is constructed it also constructs
//   the object
//	When you specify NULL as parameter when construcing a smart pointer
//	 it will not construct an object

// 	The lifetime of objects is ruled by reference counting
//	When no references to the object exists it will be deleted.
//	You can remove the reference to an object explicitely by assigning
//	 NULL to the smart pointer
//	You can also construct a new object explicitely by assigning the special value
//	 NEW_OBJECT to it.

//  Apart from construction and destruction everything that can be done with a 
//   normal (dumb) pointer can also be done with a smart pointer

// Remark:
//	The runtime overhead of using a smart pointer instead of a dumb pointer
//	 are very minimal
//  COXSPtr is a class with no base class and no virtual functions
//	 The size of a smart pointer thus equals the size of its members :
//	 two pointer (to the object and to the reference count).  
//	All access functions  of COXSPtr are inline and are very short.
//	 E.g. operator-> just checks whether the pointer is not NULL
//	                 and returns it then
//	 So computational overhead is minimal too.

//	When you try to dereference a smart pointer that is NULL
//	 a CMemoryException will be thrown (and in DEBUG the function will ASSERT)

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __OXSPTR_H__
#define __OXSPTR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


// Defining ENABLE_SMART_WRAPPER enables the possibility to wrap a smart pointer
// around an existing object.  The locking functions are also available then.
// By default this is not defined and thus not enabled
// #define ENABLE_SMART_WRAPPER 1

// Defining DISABLE_SMART_DOWNCAST_TEST disnables the runtime test when a 
// smart pointer is downcasted (from base class to derived class)
// By default this is not defined and thus enabled
// #define DISABLE_SMART_DOWNCAST_TEST 1

// Defining DISABLE_SMART_SERIALIZATION disnables the serialization functionality
// of a smart pointer (and groups)
// By default this is not defined and thus enabled
// #define DISABLE_SMART_SERIALIZATION 1

// Defining DISABLE_SMART_CHECK disables the runtime checks during Debug
// These checks include wrapping a smart pointer around an existing object,
// a smart pointer around a steck based object and cyclic graphs.
// By default this is not defined and thus enabled
// #define DISABLE_SMART_CHECK 1

// Use special creator object (NEW_OBJECT) that can be used in the
//  constructor and assignment operator of a smart pointer
//  to construct a new object
class OX_CLASS_DECL COXObjectCreator
	{
	// This class is only used to mark a special parameter
	// during construction or assignment of a smart pointer
	// No actual members are needed
	};
extern OX_CLASS_DECL COXObjectCreator NEW_OBJECT;

template <class T> class OX_CLASS_DECL COXSPtr;
#ifndef DISABLE_SMART_SERIALIZATION
template <class T> CArchive& AFXAPI operator<<(CArchive& ar, const COXSPtr<T>& pSObj);
template <class T> CArchive& AFXAPI operator>>(CArchive& ar, COXSPtr<T>& pSObj);
#endif // DISABLE_SMART_SERIALIZATION

template <class T> class OX_CLASS_DECL COXSPtr 
{
// Data members -------------------------------------------------------------
public:
protected:
	T*		m_pSmartObject;
	LONG*	m_pnReferenceCount;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXSPtr(const COXObjectCreator& objCreator = NEW_OBJECT);
	// --- In  : objCreator  : NEW_OBJECT : Creates a new object
	// --- Out : 
	// --- Returns : 
	// --- Effect : This constructs a smart pointer and it also 
	//			    creates the associated object
	//				This is the default constructor
	//				The only valid parameter is NEW_OBJECT

#ifndef ENABLE_SMART_WRAPPER
	COXSPtr(const COXObjectCreator* pNull);
	// --- In  : pNull : NULL
	// --- Out : 
	// --- Returns : 
	// --- Effect : This constructs a smart NULL pointer 
	//				The only valid parameter is NULL

#else

	COXSPtr(T* pSObj);
	// --- In  : pSObj  : Pointer to the object
	//					  around which this smart pointer will be created
	//					  or NULL : Makes this a NULL-pointer
	// --- Out : 
	// --- Returns : 
	// --- Effect : This constructs a smart pointer around an existing
	//				object or constructs a smart NULL pointer
	//				The object's lifetime is now decided by the smart pointer
	//				You should not delete the object directly
#endif // ENABLE_SMART_WRAPPER

	COXSPtr(const COXSPtr& sPtr);
	// --- In  : sPtr : The smart pointer to be copied
	// --- Out : 
	// --- Returns : 
	// --- Effect : Copy constructor

	COXSPtr& operator=(const COXSPtr<T>& sPtr);
    // --- In  : sPtr : A smart pointer
	// --- Out : 
	// --- Returns : 
	// --- Effect : Assignment operator
	
	COXSPtr& operator=(const COXObjectCreator& objCreator);
    // --- In  : objCreator : NEW_OBJECT
	// --- Out : 
	// --- Returns : 
	// --- Effect : Constructs a new object and assigns it to this smart pointer
	//				The only valid parameter is NEW_OBJECT
	
#ifndef ENABLE_SMART_WRAPPER
	COXSPtr& operator=(const COXObjectCreator* pNull);
    // --- In  : pNull : NULL
	// --- Out : 
	// --- Returns : 
	// --- Effect : Makes this smart pointer a smart NULL pointer
	//				The only valid parameter is NULL
	
#else

    COXSPtr& operator=(T* pSObj);
    // --- In  : pSObj : A pointer to the object or NULL
	// --- Out : 
	// --- Returns : 
	// --- Effect : Assignment operator
	//				If pSObj == NULL this smart pointer becomes a smart NULL pointer 
	//				The object's lifetime is now decided by the smart pointer
	//				You should not delete the object directly
#endif // ENABLE_SMART_WRAPPER

    T& operator*() const;
		// throw(CMemoryException);
    // --- In  : 
	// --- Out : 
	// --- Returns : The object pointed to
	// --- Effect : Dereference operator

    T* operator->() const;
		// throw(CMemoryException);
    // --- In  : 
	// --- Out : 
	// --- Returns : Pointer to the object
	// --- Effect : Member operator

    operator T*() const;
    // --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Conversion operator

    BOOL operator!() const;
    // --- In  : 
	// --- Out : 
	// --- Returns : Whether this pointer points to NULL (TRUE) or to
	//			     a valid object (FALSE)
	// --- Effect : 

    BOOL operator==(T* pSObj) const;
    // --- In  : pSObj : Pointer to a smart element
	// --- Out : 
	// --- Returns : Whether this pointer points to the specified
	//				 object
	// --- Effect : 

    BOOL operator!=(T* pSObj) const;
    // --- In  : pSObj : Pointer to a smart element
	// --- Out : 
	// --- Returns : Whether this pointer does not point to the specified
	//				 object
	// --- Effect : 

#ifndef DISABLE_SMART_SERIALIZATION
	friend CArchive& AFXAPI operator<<(CArchive& ar, const COXSPtr<T>& pSObj);
    // --- In  : ar : Archive to store the object in
	//			 pSObj : Object to store
	// --- Out : 
	// --- Returns : The archive itself
	// --- Effect : This functions serializes the object wrapped by this smart pointer
	//				Object I/O is pointer based to avoid added construction overhead and
	//               to support polymorphism
	//				Use the Serialize member function directly for embedded objects.

	friend CArchive& AFXAPI operator>>(CArchive& ar, COXSPtr<T>& pSObj);
    // --- In  : ar : Archive to load the object from
	//			 pSObj : Object pointer to load into
	// --- Out : 
	// --- Returns : The archive itself
	// --- Effect : This functions serializes the object into this smart pointer
	//				Object I/O is pointer based to avoid added construction overhead and
	//               to support polymorphism
	//				Use the Serialize member function directly for embedded objects.
#endif // DISABLE_SMART_SERIALIZATION

	COXSPtr& PolyAssign(T* pSObj, LONG* pnReferenceCount);
    // --- In  : pSObj : Pointer to a T or T derived object
	//			 pnReferenceCount : Pointer to its reference count
	// --- Out : 
	// --- Returns : A smart pointer wrapping the object
	// --- Effect : Assignment function, internally used for
	//				polymorphic assignment
	//				Do not call this function directly, use
	//				the operator <<= instead

	LONG* GetRefCountAddress() const;
    // --- In  : 
	// --- Out : 
	// --- Returns : The address of the reference count of the object
	//				 or NULL when smart null pointer
	// --- Effect : Helper function, internally used for polymorphic assignment
	//				Do not call this function directly, use
	//				the operator <<= instead

#ifdef ENABLE_SMART_WRAPPER
	// CAUTION : THE NEXT THREE FUNCTIONS ARE NOT INTENDED FOR NORMAL USE
	//           THEY DISABLE A LOT OF IMPORTANT FUNCTIONALITY AND
	//			 SHOULD ONLY BE USED IN EXCEPTIONAL CIRCUMSTANCES

	void Lock();
    // --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Locks all the smart pointers that point to the object 
	//			    this smart pointer points to
	//				Locking will disable automatic deletion when the
	//				reference count reaches 0

	void Unlock();
    // --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Unlocks all the smart pointers that point to the object 
	//			    this smart pointer points to
	//				Unlocking will re-enable automatic deletion when the
	//				reference count reaches 0

	BOOL IsLocked();
    // --- In  : 
	// --- Out : 
	// --- Returns : Whether the smart pointer is locked or not
	// --- Effect : 
#endif // ENABLE_SMART_WRAPPER

#ifdef _DEBUG
	void AssertValid() const;
#endif // _DEBUG

	~COXSPtr();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : This destructs the pointer object

protected:
	LONG Grab();
	LONG Release();

private:
                   
};

template <class BASE_T, class T>
inline COXSPtr<BASE_T>& SmartUpCast(COXSPtr<BASE_T>& pBaseObj, const COXSPtr<T>& pObj)
	// --- In  : pBaseObj : Smart pointer you want to assign to
	//			 pObj : Smart pointer being assigned
	// --- Out : 
	// --- Returns : The smart pointer assigned to
	// --- Effect : This is the 'polymorphic assignemnt' operator 
	//				A smart pointer wrapping a T object can be assigned to a 
	//				 smart pointer normally wrapping BASE_T object, 
	//				 if T* could be assigned to BASE_T*
	//				This means T must be derived from BASE_T
	{
	// The next line will generate a compiler error (cannot convert parameter 1 from ...)
	// if T (pObj) is not derived from BASE_T (pBaseObj)
	return pBaseObj.PolyAssign(pObj, pObj.GetRefCountAddress());
	};

template <class BASE_T, class T>
inline COXSPtr<BASE_T>& operator<<=(COXSPtr<BASE_T>& pBaseObj, const COXSPtr<T>& pObj)
	{
	return SmartUpCast(pBaseObj, pObj);
	};

template <class BASE_T, class T>
inline COXSPtr<T>& SmartDownCast(COXSPtr<T>& pObj, const COXSPtr<BASE_T>& pBaseObj)
	// --- In  : pObj : Smart pointer you want to assign to
	//			 pBaseObj : Smart pointer being assigned
	// --- Out : 
	// --- Returns : The smart pointer assigned to
	// --- Effect : This is the 'cast assignemnt' operator 
	//				A smart pointer wrapping a BASE_T object will be assigned to a 
	//				 smart pointer wrapping a T object, 
	//				A runtime check will be performed, to check the validity
	//			When an incorrect cast is performed a smart NULL pointer is returned
	{
#ifndef DISABLE_SMART_DOWNCAST_TEST
	// The macro DYNAMIC_DOWNCAST does not work with templates, so we mimic that functionality
	// ... Build a (temporary T object) just to get to the runtime class
	COXSPtr<T> pDummyObj;
	if (pBaseObj != NULL && !pBaseObj->IsKindOf(pDummyObj->GetRuntimeClass()))
		{
		TRACE(_T("SmartDownCast (Cast assignment) returning smart NULL pointer\n"));
		return pObj.PolyAssign(NULL, NULL);
		}
	else
#endif // DISABLE_SMART_DOWNCAST_TEST
		return pObj.PolyAssign((T*)(BASE_T*)pBaseObj, pBaseObj.GetRefCountAddress());
	};

template <class BASE_T, class T>
inline COXSPtr<T>& operator>>=(COXSPtr<T>& pObj, const COXSPtr<BASE_T>& pBaseObj)
	{
	return SmartDownCast(pObj, pBaseObj);
	};

#include "OXSPtr.inl"

#endif // __OXSPTR_H__
// ==========================================================================
