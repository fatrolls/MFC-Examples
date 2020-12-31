/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File ConstantStringArray.h
// class CWizConstantStringArray
//
// 14/04/1996 11:57                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizConstantStringArray_H
#define __CWizConstantStringArray_H

#include <TypedLocalHeap.h>
#include <multiptr.h>

/////////////////////////////////////////////////////////////////////////////
// class CWizConstantStringArray
class CWizConstantStringArray
{
public:
// Constructors:
	CWizConstantStringArray ()
		:	m_pPointers (NULL),
			m_pData (NULL),
			m_nPtrsSize (0),
			m_nDataSize (0)
		{}
	CWizConstantStringArray (const CWizConstantStringArray& T)
		:	m_pPointers (NULL),
			m_pData (NULL),
			m_nPtrsSize (0),
			m_nDataSize (0)
		{ Init (T); }
	CWizConstantStringArray (LPCTSTR str)
		:	m_pPointers (NULL),
			m_pData (NULL),
			m_nPtrsSize (0),
			m_nDataSize (0)
		{ Add (str); }

// Destructor:
	~CWizConstantStringArray () { Cleanup() ; }
public:
// Operations:
	CWizConstantStringArray& operator= (const CWizConstantStringArray& T)
		{ Cleanup(); Init(T); return *this; }

	LPCTSTR GetAt (int i) const
		{ 
		ASSERT(i >= 0 && i < m_nPtrsSize);
		ASSERT(m_pPointers[i] >= 0 && m_pPointers[i] < m_nDataSize);
		return &(m_pData[m_pPointers[i]]);
		}
	LPCTSTR operator[] (int i) const
		{ 
		return GetAt(i);
		}
	int StringLength(int i) const
		{
		return strlen(GetAt(i));
		}
	CWizConstantStringArray& operator+=(LPCTSTR str)
		{ Add (str);  return *this; }
	CWizConstantStringArray& operator+=(const CWizConstantStringArray& T)
		{ Add(T);   return *this; }
	int		Add(LPCTSTR str);
	void	Add(const CWizConstantStringArray& T);
	int		GetSize() const { return m_nPtrsSize; }
	void	RemoveAll() { Cleanup(); }
protected:
// Implementation:
	void Cleanup();
	void Init(const CWizConstantStringArray& T);
	void Alloc();
	void ReAlloc();
protected:
// Members:
	int*	m_pPointers;
	LPTSTR	m_pData;
	int		m_nPtrsSize;
	int		m_nDataSize;

	static CWizDefaultTypedLocalHeap m_cHeap;
};
/////////////////////////////////////////////////////////////////////////////
class CWizConstantStringArrayCNT
{
public:
	CWizConstantStringArray	Data;
	int	Counter;

	CWizConstantStringArrayCNT() : Counter(1) {}
	~CWizConstantStringArrayCNT() { Counter = -1; }
	CWizConstantStringArrayCNT(const CWizConstantStringArray& T)
		: Counter(1) , Data(T) {}
	CWizConstantStringArrayCNT(LPCTSTR T)
		: Counter(1) , Data(T) {}
};
/////////////////////////////////////////////////////////////////////////////
class CWizConstantStringArrayPtr : public CWizBaseMultiPtr<CWizConstantStringArray,CWizConstantStringArrayCNT>
{
public:
	CWizConstantStringArrayPtr() {}
	CWizConstantStringArrayPtr(const CWizConstantStringArray& T)
		: CWizBaseMultiPtr<CWizConstantStringArray,CWizConstantStringArrayCNT> (new CWizConstantStringArrayCNT(T)) {}
	CWizConstantStringArrayPtr(LPCTSTR T)
		: CWizBaseMultiPtr<CWizConstantStringArray,CWizConstantStringArrayCNT> (new CWizConstantStringArrayCNT(T)) {}

	CWizConstantStringArrayPtr& operator=(const CWizConstantStringArrayPtr& T)
		{ CWizBaseMultiPtr<CWizConstantStringArray,CWizConstantStringArrayCNT>::operator=(T); return *this; }
};
/////////////////////////////////////////////////////////////////////////////
#endif // __CWizConstantStringArray_H


