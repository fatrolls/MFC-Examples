///////////////////////////////////////////////////////////////////
// Header File SmartPointers.h
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
// class CWizSmartPtr - basic smart pointer class.
//*****************************************************************
// Actually, it is very stupid one - it knows to do nothing
// except holding the pointer. Doesn't have destructor or
// copy.
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
// WARNING! All classes presented here aren't constructed to
// be virtually inherited. They have no virtual destructors or
// functions, and are pure template completely inlined classes.
// Don't even think to use C++ pointer to them somewhere in your code.
// I don't use here any tricks (like private operator new etc.)
// to prevent this, because I suppose programmers to be smart enough.
///////////////////////////////////////////////////////////////////
//
// 29/1/1997 12:38  Author: Poul A. Costinsky  poul@wizsoft.com
// Copyright (C) WizSoft Inc., 1997
///////////////////////////////////////////////////////////////////

#ifndef __CWizSmartPtr_H
#define __CWizSmartPtr_H


#pragma warning(disable : 4284)
/////////////////////////////////////////////////////////////////////////////
// class CWizSmartPtr
template<class TYPE>
class CWizSmartPtr
{
public:
// Constructor:
	CWizSmartPtr (TYPE *ptr = NULL)
		: m_ptr (ptr) {}
	CWizSmartPtr (const CWizSmartPtr& T)
		: m_ptr (T.m_ptr) { }
public:
// Operations:
	// Access to pointer to actual data:
	// Non-const access
	TYPE* const			GetPtr() 			{ return m_ptr; }
	TYPE* const			operator->()		{ return m_ptr; }
	TYPE& 				operator*() 		{ return *m_ptr;}

	// Const access
	const TYPE*	const	GetPtr()	const 	{ return m_ptr;	}
	const TYPE*	const	operator->()const	{ return m_ptr;	}
	const TYPE& 		operator*()	const	{ return *m_ptr;}

	BOOL IsNull()					const   { return (m_ptr == NULL); }
	void ThrowMemoryExceptionIfNull() const { if (IsNull()) AfxThrowMemoryException(); }

	// Swap between two pointers (for sorting etc)
	void	Swap(CWizSmartPtr& T)
		{
		TYPE*	ptr = T.m_ptr;
		T.m_ptr		= m_ptr;
		m_ptr		= ptr;
		}
	void operator=(const CWizSmartPtr& T)
		{ m_ptr  = T.m_ptr; }

protected:
// Members:
	TYPE*	m_ptr;
};
//*****************************************************************
template<class TYPE>
inline BOOL IsNull(const CWizSmartPtr<TYPE>& p)
{
	return (p.GetPtr() == NULL);
}
//*****************************************************************
template<class TYPE>
inline void ThrowMemoryExceptionIfNull(const CWizSmartPtr<TYPE>& p)
{
	if (IsNull(p))
		AfxThrowMemoryException();
}
//*****************************************************************
template<class TYPE>
inline void ThrowMemoryExceptionIfNull(const TYPE const *p)
{
	if (p == NULL)
		AfxThrowMemoryException();
}
//*****************************************************************
/////////////////////////////////////////////////////////////////////////////
// Class CWizSafePtr - knows to delete pointer at destructor
// WARNING! Copy operator is weird - it changes right-hand
// operand (makes it NULL actually.
/////////////////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizSafePtr : public CWizSmartPtr<TYPE>
{
public:
// Constructor:
	CWizSafePtr (TYPE *ptr = NULL)
		: CWizSmartPtr<TYPE> (ptr) {}
// Copy Constructor:
	CWizSafePtr(CWizSafePtr& T)
		: CWizSmartPtr<TYPE> (T) 
		{
		if (&T != this)
			T.m_ptr = NULL;
		}
// Destructor:
	~CWizSafePtr() { delete m_ptr; }
public:
// Operations:
	void operator=(TYPE* new_ptr)
		{
		if (new_ptr != m_ptr)
			{
			delete m_ptr;
			m_ptr = new_ptr;
			}
		}
	void operator=(CWizSafePtr& T)
		{
		if (&T != this)
			{
			delete m_ptr;
			m_ptr = T.m_ptr;
			T.m_ptr = NULL;
			}
		}
};
/////////////////////////////////////////////////////////////////////////////
// Class CWizSafeArray - array of objects
/////////////////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizSafeArray : public CWizSmartPtr<TYPE>
{
public:
// Constructors:
	CWizSafeArray (TYPE *ptr = NULL)
		: CWizSmartPtr<TYPE> (ptr) {}
	CWizSafeArray (int nCount)
		: CWizSmartPtr<TYPE> (new TYPE [nCount]) {}

// Destructor:
	~CWizSafeArray() { delete[] m_ptr; }

public:
// Operations:
	TYPE& 			operator[] (int i) 		 { return m_ptr[i]; }
	const TYPE& 	operator[] (int i) const { return m_ptr[i]; }
private:
	// No copy semantics
	void operator=(const CWizSafeArray& T);
	CWizSafeArray(const CWizSafeArray& T);
};
/////////////////////////////////////////////////////////////////////////////
// class CWizDuplPtr
// Class for holding safe pointer to clonable object
// ###########################################################
// ##	Object must have copy constructor					##
// ##	Copiing implemented by creating new object			##
// ##	via copy constructor.								##
// ##	So class CWizDuplPtr has copy constructor and		##
// ##	copy operator.										##
// ##   Class CANNOT handle inheritance trees!				##
// ##   Use CWizClonePtr for this.						##
// ###########################################################
/////////////////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizDuplPtr : public CWizSafePtr<TYPE>
{
public:
// Constructors:
	CWizDuplPtr (TYPE *ptr = NULL) 
		: CWizSafePtr<TYPE> (ptr) {}
// Copy constructor
	CWizDuplPtr (const CWizDuplPtr& T) 
		: CWizSafePtr<TYPE> (NULL) 
		{
		if(T.m_ptr != NULL)
			m_ptr = new TYPE(*(T.m_ptr));
		}
public:
	// Copy operators
	CWizDuplPtr& operator=(const CWizDuplPtr& T)
		{
		if (this != &T)
			{
			delete m_ptr;
			if (T.m_ptr == NULL)
				m_ptr = NULL;
			else
				m_ptr = new TYPE(*(T.m_ptr));
			}
		return *this;
		}
	void operator=(TYPE* new_ptr)
		{
		if (new_ptr != m_ptr)
			{
			delete m_ptr;
			m_ptr = new_ptr;
			}
		}
};
///////////////////////////////////////////////////////////////////
// class CWizClonePtr
// Class for holding safe pointer to clonable object
// ###########################################################
// ##	Object must have Clone function						##
// ##	Copiing implemented by creating new object			##
// ##	via clone function. 								##
// ##	So class CWizClonePtr has copy constructor and	##
// ##	copy operator.										##
// ##	Differs from class CWizDuplPtr that it can hold 	##
// ##   pointer to inheritance tree members					##
// ###########################################################
/////////////////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizClonePtr : public CWizSafePtr<TYPE>
{
public:
// Constructors:
	CWizClonePtr (TYPE *ptr = NULL) 
		: CWizSafePtr<TYPE> (ptr) {}
// Copy constructor
	CWizClonePtr (const CWizClonePtr& T) 
		: CWizSafePtr<TYPE> (NULL) 
		{
		if (T.m_ptr != NULL)
			m_ptr = T.m_ptr->Clone();
		}
public:
	// Copy operator
	CWizClonePtr& operator=(const CWizClonePtr& T)
		{
		if (this != &T)
			{
			delete m_ptr;
			if (T.m_ptr == NULL)
				m_ptr = NULL;
			else
				m_ptr = T.m_ptr->Clone();
			}
		return *this;
		}
	void operator=(TYPE* new_ptr)
		{
		if (new_ptr != m_ptr)
			{
			delete m_ptr;
			m_ptr = new_ptr;
			}
		}
};
/////////////////////////////////////////////////////////////////////////////
// Recommended (but NOT required) base for clonabe classes.
template<class TYPE>
TYPE* CloneMe(const TYPE& p)
{
	return new TYPE(p);
}
/////////////////////////////////////////////////////////////////////////////
class CWizClonable 
{
	public:
		virtual ~CWizClonable() {}
		virtual CWizClonable* Clone() const = 0;
		/*	This must be in every son!: { return CloneMe(this); } */
};
/////////////////////////////////////////////////////////////////////////////
// Alternative MACRO (Yack!) for clonability
#define DECLARE_CLONABLE(TYPE) public: virtual TYPE* Clone() const { return (TYPE *)::CloneMe(*this); }
/////////////////////////////////////////////////////////////////////////////
// class CWizBaseMultiRefPtr
// This is really smart pointer.
// It implements garbage collection by usage counting.
// Template parameter COUNT means class int-like for
// reference counting. It may be int, like in 
// CWizMultiRefPtr, or some optimized for multiply
// allocations class.
///////////////////////////////////////////////////////////////////
template<class TYPE,class COUNT>
class CWizBaseMultiRefPtr : public CWizSmartPtr<TYPE>
{
public:
	// Copy Constructor:
	CWizBaseMultiRefPtr(const CWizBaseMultiRefPtr& T)
		{ Copy(T);}
	// Default constructor:
	CWizBaseMultiRefPtr(TYPE* ptr = NULL)
		{ Construct (ptr); }
	// Destructor:
	~CWizBaseMultiRefPtr() { Delete(); }

	CWizBaseMultiRefPtr& operator=(const CWizBaseMultiRefPtr& T)
		{
		if (this != &T)	{ Delete();	Copy(T); }
		return *this;
		}
	void operator=(TYPE* ptr)
		{
		if (m_ptr == ptr) return;
		Delete(); Construct (ptr);
		}
	// Swap between two pointers (for sorting etc)
	void	Swap(CWizBaseMultiRefPtr& T)
		{
		CWizSmartPtr<TYPE>::Swap(T);
		COUNT* pRefCount = T.m_pRefCount;
		T.m_pRefCount	 = m_pRefCount;
		m_pRefCount		 = pRefCount;
		}
	bool operator==(const 	CWizBaseMultiRefPtr& t) const
		{ return (m_ptr == t.m_ptr); }
	bool operator!=(const 	CWizBaseMultiRefPtr& t) const
		{ return (m_ptr != t.m_ptr); }

	bool IsLastOne ()	const { return (m_pRefCount && (*m_pRefCount == 1)); }
	bool IsShared()		const { return (m_pRefCount && (*m_pRefCount > 1)); }
protected:
// Implementation
	void Copy(const CWizBaseMultiRefPtr& T)
		{
		m_ptr		= T.m_ptr;
		m_pRefCount = T.m_pRefCount;
		if (m_pRefCount != NULL)
			{
			ASSERT(m_ptr != NULL);
			++*m_pRefCount;
			}
		else
			{ ASSERT(m_ptr == NULL); }
		return;
		}
	void Construct(TYPE* ptr)
		{
		m_ptr = ptr;
		m_pRefCount = NULL;
		if (m_ptr != NULL)
			{
			m_pRefCount = new COUNT(1);
			::ThrowMemoryExceptionIfNull(m_pRefCount);
			}
		return;
		}
	void Delete()
		{
		if (m_pRefCount ==NULL)
			{ ASSERT(m_ptr == NULL); return; }
		ASSERT(m_ptr != NULL);
		if(--*m_pRefCount==0)
			{
			delete m_pRefCount;	m_pRefCount = NULL;
			delete m_ptr;		m_ptr		= NULL;
			}
		return;
		}
protected:
// Data members:
	COUNT* m_pRefCount; // reference counter
};
///////////////////////////////////////////////////////////////////
// class CWizMultiRefPtr - derived from CWizBaseMultiRefPtr
// with int as simple counter.
template<class TYPE>
class CWizMultiRefPtr : public CWizBaseMultiRefPtr<TYPE,int>
{
public:
	// Constructors:
	CWizMultiRefPtr(const CWizMultiRefPtr& T)
		: CWizBaseMultiRefPtr<TYPE,int>(T)	{}
	CWizMultiRefPtr(TYPE* ptr = NULL)
		: CWizBaseMultiRefPtr<TYPE,int>(ptr){}
	~CWizMultiRefPtr() {}
	// Copy operators:
	CWizMultiRefPtr& operator=(const CWizMultiRefPtr& T)
		{
		CWizBaseMultiRefPtr<TYPE,int>::operator=(T);
		return *this;
		}
	void operator=(TYPE* ptr)
		{
		CWizBaseMultiRefPtr<TYPE,int>::operator=(ptr);
		}
};
///////////////////////////////////////////////////////////////////
// class CWizCounterMultiRefPtr
// Variant of reference counting pointer.
// This is one most effective but it has significant limitation:
// The class it points to (or the root class of the hierarchy)
// must implement reference counting itself. The simplest way to
// do this is to derive it from CWizReferenceCounterBase. 
// The catch is that you cannot have it in multiple derivation
// several times, and, the worst, you must be the author of this 
// class.
///////////////////////////////////////////////////////////////////
class CWizReferenceCounterBase
{
public:
	// Construction:
	CWizReferenceCounterBase() : m_Counter(1) {}
	// Interface for CWizCounterMultiRefPtr
	// Adds a reference to the object
	void	AddReference() { m_Counter++; }
	// Removes a reference to the object and returns new count.
	int		RemoveReference() { return --m_Counter; }
	int		GetReferenceCount() const { return m_Counter; }
private:
	int	m_Counter;
};


template<class TYPE>
class CWizCounterMultiRefPtr : public CWizSmartPtr<TYPE>
{
public:
	// Copy Constructor:
	CWizCounterMultiRefPtr(const CWizCounterMultiRefPtr& T)
		{ Copy(T);}
	// Default constructor:
	CWizCounterMultiRefPtr(TYPE* ptr = NULL)
		{ Construct (ptr); }
	// Destructor:
	~CWizCounterMultiRefPtr() { Delete(); }

	CWizCounterMultiRefPtr& operator=(const CWizCounterMultiRefPtr& T)
		{
		if (this != &T)	{ Delete();	Copy(T); }
		return *this;
		}
	void operator=(TYPE* ptr)
		{
		if (m_ptr == ptr) return;
		Delete(); Construct (ptr);
		}
	// Swap between two pointers (for sorting etc)
	void	Swap(CWizCounterMultiRefPtr& T)
		{ CWizSmartPtr<TYPE>::Swap(T); }
	bool operator==(const 	CWizCounterMultiRefPtr& t) const
		{ return (m_ptr == t.m_ptr); }
	bool operator!=(const 	CWizCounterMultiRefPtr& t) const
		{ return (m_ptr != t.m_ptr); }

	bool IsLastOne ()	const { return (m_ptr && (m_ptr->GetReferenceCount() == 1)); }
	bool IsShared()		const { return (m_ptr && (m_ptr->GetReferenceCount() > 1)); }
protected:
// Implementation
	void Copy(const CWizCounterMultiRefPtr& T)
		{
		m_ptr		= T.m_ptr;
		if (m_ptr != NULL)
			m_ptr->AddReference();
		return;
		}
	void Construct(TYPE* ptr)
		{
		m_ptr = ptr;
		return;
		}
	void Delete()
		{
		if (m_ptr == NULL)
			return;
		if(m_ptr->RemoveReference() == 0)
			{
			delete	m_ptr;		
			m_ptr	= NULL;
			}
		return;
		}
};

///////////////////////////////////////////////////////////////////
//#pragma warning(default : 4284)
///////////////////////////////////////////////////////////////////

#endif // __CWizSmartPtr_H


