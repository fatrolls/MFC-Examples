///////////////////////////////////////////////////////////////////
// Header File SmartPointerArrays.h
///////////////////////////////////////////////////////////////////
//
// 309/1/1997 11:28  Author: Poul A. Costinsky  poul@wizsoft.com
// Copyright (C) WizSoft Inc., 1997
///////////////////////////////////////////////////////////////////

#ifndef __CWizSmartPtrArrays_H
#define __CWizSmartPtrArrays_H

#include <SmartPointers.h>

///////////////////////////////////////////////////////////////////
// Array of smart pointers without GOOD copy operations.
//--------------------------------------------------------
template<class TYPE>
class CRefArgArray : public CArray<TYPE, TYPE&>
{
public:
	const TYPE& GetAt(int i) const 
		{ return const_cast<CRefArgArray*>(this)->ElementAt(i); }
	TYPE& operator[](int i)
		{ return ElementAt(i); }
	const TYPE& operator[](int i) const 
		{ return GetAt(i); }
};
//--------------------------------------------------------
template<class POINTER_TYPE, class TYPE>
class CWizGenSmartPtrArray : public CRefArgArray<POINTER_TYPE>
{
typedef CRefArgArray<POINTER_TYPE> PARENT;
public:
	// Constructor
	CWizGenSmartPtrArray() {}
	// Destructor
	~CWizGenSmartPtrArray() {}
	// Add elements
	int Add(TYPE* ptr)
		{ return PARENT::Add(POINTER_TYPE(ptr)); }
	void SetAtGrow(int i, TYPE* ptr)
		{ PARENT::SetAtGrow(i,POINTER_TYPE(ptr)); }
	void SetAt(int i, TYPE* ptr)
		{ PARENT::SetAt(i,POINTER_TYPE(ptr)); }
	void InsertAt(int i, TYPE* ptr)
		{ PARENT::InsertAt(i,POINTER_TYPE(ptr)); }
	void Add(const CWizGenSmartPtrArray& A)
		{ CopyArray(A);	}
	// Swapping (for sorting etc.)
	void Swap(int i, int j)
		{
		ASSERT(i >= 0 && i < GetSize());
		ASSERT(j >= 0 && j < GetSize());
		ASSERT(i != j);
		ElementAt(i).Swap(ElementAt(j));
		}

	CWizGenSmartPtrArray(const CWizGenSmartPtrArray& A)
		{ CopyArray(A);	}
	CWizGenSmartPtrArray& operator=(const CWizGenSmartPtrArray& A)
		{ RemoveAll(); CopyArray(A); return *this; }
	CWizGenSmartPtrArray& operator+=(const CWizGenSmartPtrArray& A)
		{ CopyArray(A);	return *this; }
private:
	void CopyArray(const CWizGenSmartPtrArray& A)
		{
		const int n = A.GetSize();
		const int s = GetSize();
		SetSize(s + n);
		for (INDEX i = 0; i < n; i++)
			ElementAt(i + s) = 
				const_cast<CWizGenSmartPtrArray&>(A).ElementAt(i);
		}
};
//--------------------------------------------------------
// Array of smart pointers with GOOD copy operations.
template<class POINTER_TYPE, class TYPE>
class CWizCopySmartPtrArray : public CWizGenSmartPtrArray<POINTER_TYPE,TYPE>
{
public:
	int Add(POINTER_TYPE& e)
		{ return PARENT::Add(e); }
	void SetAtGrow(int i, POINTER_TYPE& e)
		{ PARENT::SetAtGrow(i,e); }
	void SetAt(int i, POINTER_TYPE& e)
		{ PARENT::SetAt(i,e); }
	void InsertAt(int i, POINTER_TYPE& e)
		{ PARENT::InsertAt(i,e); }
	int Add(TYPE* ptr)
		{ return PARENT::Add(POINTER_TYPE(ptr)); }
	void SetAtGrow(int i, TYPE* ptr)
		{ PARENT::SetAtGrow(i,POINTER_TYPE(ptr)); }
	void SetAt(int i, TYPE* ptr)
		{ PARENT::SetAt(i,POINTER_TYPE(ptr)); }
	void InsertAt(int i, TYPE* ptr)
		{ PARENT::InsertAt(i,POINTER_TYPE(ptr)); }
};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizSmartPtrArray : 
	public CWizGenSmartPtrArray<CWizSmartPtr<TYPE> , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizSafePtrArray : 
	public CWizGenSmartPtrArray<CWizSafePtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizDuplPtrArray : 
	public CWizGenSmartPtrArray<CWizDuplPtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizClonePtrArray : 
	public CWizGenSmartPtrArray<CWizClonePtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE,class COUNT>
class CWizBaseMultiRefPtrArray : 
	public CWizCopySmartPtrArray<CWizBaseMultiRefPtr<TYPE,COUNT>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizMultiRefPtrArray : 
	public CWizCopySmartPtrArray<CWizMultiRefPtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class TYPE>
class CWizCounterMultiRefPtrArray : 
	public CWizCopySmartPtrArray<CWizCounterMultiRefPtr<TYPE>  , TYPE >
{};
///////////////////////////////////////////////////////////////////
template<class ARRAY>
inline int DeepCopyArray (ARRAY& a1, const ARRAY& a2)
{
	const int imax = a2.GetSize();
	a1.RemoveAll();
	if(imax > 0)
		{
		a1.SetSize(imax);
		for (INDEX i = 0; i < imax; i++)
			a1[i] = a2[i]->Clone();
		}
	return imax;
}
///////////////////////////////////////////////////////////////////

#endif // __CWizSmartPtrArrays_H


