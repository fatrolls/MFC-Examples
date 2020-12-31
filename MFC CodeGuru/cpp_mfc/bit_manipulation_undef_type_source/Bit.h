/*
** Author: CHARRIER Ludovic
** Internet: l.charrier@hol.fr
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell this class in source code form must have the permission
** of the original author. You can produce commercial executables with
** this class but you can't sell this class.
**
** Copyright, 1998, Ludovic CHARRIER
**
** $Workfile: bit.h $
** $Revision: 2 $
** On a suggestion of  Dave Montgomery <dmont@tradeit.com> from Canada, 
** I integrate an optimization in inline method SetBit0 and SetBit1
** and add a new method SetBit.
*/

// Bit.h: interface for the CBit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIT_H__83FAD793_E250_11D1_B5E0_00400547D2F3__INCLUDED_)
#define AFX_BIT_H__83FAD793_E250_11D1_B5E0_00400547D2F3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/*I didn't find useful to derive this class from CObject because in this case 
Run-time class information, Dynamic creation, Persistence (serialization), Run-time object 
diagnostics is heavy where the initial design goal was lightness, speed, speed and only speed.*/
template<class T> class CBit
{
	T m_TVar;

public:
	CBit(T l_TVar) { m_TVar = (T)l_TVar;}

	~CBit() {};

	T Get() { return m_TVar;}; //Get the value

	T Set(T l_TVar) { m_TVar = (T)l_TVar;};//Set a new value

	int GetMaxBits(void) {return (sizeof(T)*8); };//give the maximum number of bits of the type

	enum BitFormat
	{
		Decimal,
		Hexa,
		Octal,
		Binary,
		All
	};

	CString print (CBit<T>::BitFormat l_eBitFormat);//prints the value in various way see, have a look on file bit.cpp

	//rank is zero based working with bit
	void SetBit1(unsigned int nRang) { ASSERT(nRang < (sizeof(T)*8));//rank overflow
								T mask = 1; 
								m_TVar |= (mask << nRang);}; 

	void SetBit0(unsigned int nRang) { ASSERT(nRang < (sizeof(T)*8));//rank overflow
								T mask = 1; 
								m_TVar &= ~(mask << nRang);};
	
	void SetBit(unsigned int nRang, unsigned int val) { 
								(val) ? SetBit1 (nRang) : SetBit0 (nRang);};

	int GetBit(unsigned int nRang){ ASSERT(nRang < (sizeof(T)*8));//rank overflow
								return ( (m_TVar >> nRang) & 0x1); };

};

#endif // !defined(AFX_BIT_H__83FAD793_E250_11D1_B5E0_00400547D2F3__INCLUDED_)
