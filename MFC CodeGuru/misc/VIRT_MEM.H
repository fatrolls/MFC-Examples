/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File virt_mem.h
// class CWizVirtualMemory
//
// 08/06/1995 13:01                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizVirtualMemory_H
#define __CWizVirtualMemory_H

/////////////////////////////////////////////////////////////////////////////
// class CWizVirtualMemory
class CWizVirtualMemory
{
public:
// Constructors:
	CWizVirtualMemory (DWORD nMaxSize, 
			DWORD nIniSize, DWORD nSizeStep = 0xffff);
	CWizVirtualMemory (DWORD nSize); // Allocates all
// Destructor:
	~CWizVirtualMemory ();
public:
// Operations:
	LPVOID	GetPtr() 					{ return m_pVoidData;}
	const LPVOID	GetPtr() const 		{ return m_pVoidData;}
	LPVOID	SetSize(DWORD nSize) 	{ Commit (nSize); return m_pVoidData;}

	DWORD	GetSize() const { return m_nSize; }
protected:
// Implementation:
	void	Commit(DWORD nSize);
protected:
// Members:
	LPVOID	m_pVoidData;
	DWORD	m_nSize,
		m_nSizeStep;
};

/////////////////////////////////////////////////////////////////////////////
// CWizTypedVMem - template class Defines array of any elements
// in virtual memory
template<class TYPE>
class CWizTypedVMem : private CWizVirtualMemory
{
public:
	enum 	{ 
		DEFAULT_SIZE_STEP = 0xffff/sizeof(TYPE)
		};
// Constructors:
	CWizTypedVMem (DWORD nMaxElements, 
			DWORD nIniElements = 0, DWORD nSizeStep = DEFAULT_SIZE_STEP)
		: CWizVirtualMemory (nMaxElements*sizeof(TYPE),
				     nIniElements*sizeof(TYPE),
				     nSizeStep*sizeof(TYPE))
			{}
// Destructor:
	~CWizTypedVMem () {}
public:
// Operations:
	TYPE*		GetPtr(int i = 0)		{ return (TYPE *)SetSize(i*sizeof(TYPE));}
	const TYPE*	GetPtr(int i = 0) const	{ return (TYPE *)SetSize(i*sizeof(TYPE));}
	TYPE&		operator[](int i)		{ return *(GetPtr(i));}
	const TYPE&	operator[](int i) const	{ return *(((CWizTypedVMem *)this)->GetPtr(i));}
private:
// Implementation:
};
/////////////////////////////////////////////////////////////////////////////
#endif // __CWizVirtualMemory_H


