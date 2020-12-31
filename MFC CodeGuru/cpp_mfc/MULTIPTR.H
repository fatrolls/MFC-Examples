/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File multiptr.h
// class CWizMultiPtr
//
// 29/11/1995 14:49                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizMultiPtr_H
#define __CWizMultiPtr_H

/////////////////////////////////////////////////////////////////////////////
// Warning!!! class TYPE must have default constructor !!!
// class CWizMultiPtr
template <class TYPE, class CNT_TYPE>
class CWizBaseMultiPtr
{
public:
// Constructors:
	CWizBaseMultiPtr ()  : m_pObject (new CNT_TYPE) {}
	CWizBaseMultiPtr (const CWizBaseMultiPtr& T) : m_pObject (NULL)
		{ Init (T); }
// Destructor:
	~CWizBaseMultiPtr () { CleanUp(); }
public:
	CWizBaseMultiPtr& operator=(const CWizBaseMultiPtr& T)
		{ CleanUp(); Init (T); return *this; }
// Operations:
	TYPE*		GetPtr() 	  { return &(m_pObject->Data); }
	TYPE* 		operator->() 	  { return &(m_pObject->Data); }
	const TYPE*	GetPtr() const 	  { return &(m_pObject->Data); }
	const TYPE* 	operator->()const { return &(m_pObject->Data); }

	TYPE& 		operator*() 	  { return m_pObject->Data; }
	const TYPE& 	operator*()const  { return m_pObject->Data; }
protected:
// Implementation:
	void Init(const CWizBaseMultiPtr& T);
	void CleanUp();
protected:
// Members:
	CNT_TYPE*	m_pObject;
protected:
	// Constructor for derived classes
	CWizBaseMultiPtr (CNT_TYPE*	m_pObject) 
		: m_pObject (m_pObject) 
			{}
};

/////////////////////////////////////////////////////////////////////////////
template <class TYPE>
class SIMPLE_CNT_TYPE
{
public:
	TYPE	Data;
	int	Counter;
	// Constructor:

	SIMPLE_CNT_TYPE() : Counter(1) {}
	~SIMPLE_CNT_TYPE() { Counter = -1; }
};
/////////////////////////////////////////////////////////////////////////////
template <class TYPE>
class CWizMultiPtr : public CWizBaseMultiPtr<TYPE, SIMPLE_CNT_TYPE<TYPE> >
{
public: // Copy constructor is compiler-generated
	CWizMultiPtr() {}
	CWizMultiPtr& operator=(const CWizMultiPtr& T)
		{ CWizBaseMultiPtr<TYPE, SIMPLE_CNT_TYPE<TYPE> >::operator=(T); return *this; }
};

/////////////////////////////////////////////////////////////////////////////
template <class TYPE,class CNT_TYPE>
CWizBaseMultiPtr<TYPE,CNT_TYPE>& CWizBaseMultiPtr<TYPE,CNT_TYPE>::operator=(const CWizBaseMultiPtr& T)
{ 
	CleanUp(); 
	Init (T); 
	return *this; 
}

template <class TYPE,class CNT_TYPE>
inline void CWizBaseMultiPtr<TYPE,CNT_TYPE>::Init(const CWizBaseMultiPtr& T)
{
	if (T.m_pObject == NULL)
		m_pObject = new CNT_TYPE;
	else
		{
		m_pObject = T.m_pObject;
		T.m_pObject->Counter++;
		}
}

template <class TYPE,class CNT_TYPE>
inline void CWizBaseMultiPtr<TYPE,CNT_TYPE>::CleanUp()
{
	if (m_pObject != NULL)
		{
		if (m_pObject->Counter <= 1)
			{
			delete m_pObject;
			m_pObject = NULL;
			}
		else
			m_pObject->Counter--;
		}
}
/////////////////////////////////////////////////////////////////////////////

#endif // __CWizMultiPtr_H


