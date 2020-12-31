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
** $Workfile: bit.cpp $
** $Revision: 1 $
*/
// Bit.cpp: implementation of the CBit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Your Project.h"
#include "Bit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Only one function not inline 
//////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
// template <class T > CString CBit<T>::print 
// 
// Description	:	This method formats a string on a numeric base specified by the parameter
// 
// Return type	: CString	the string formatted
// 
// Argument     : CBit<T>::BitFormat l_eBitFormat : enum of type BitFormat who takes only those values
//									CBit<T>::Binary	binary base
//									CBit<T>::Hexa		hexadecimal base
//									CBit<T>::Octal		octal base
//									CBit<T>::Decimal	decimal base
//									CBit<T>::All		all the base up in one string
//------------------------------------------------------------------------------
// Créé le :  vendredi 1 mai 1998	Modifié le :  
// Auteur  :  Ludovic CHARRIER   	Par :  
//------------------------------------------------------------------------------
template <class T > CString CBit<T>::print (CBit<T>::BitFormat l_eBitFormat)
{
	CString l_strFormatted, l_strBuf("");
	switch (l_eBitFormat)
	{
	case CBit<T>::Binary:case CBit<T>::All:
	{
		T l_TVar = m_TVar;
		int l_nSize = sizeof(m_TVar);
		for(int i = 0 ; i < (l_nSize*8) ; i++)
		{
			l_strBuf.Format(_T("%d"),(l_TVar & 0x01));
			l_TVar >>= 1;
			l_strFormatted += l_strBuf;
			if (((i+1) % 4) == 0 )
				l_strFormatted += _T(" ");
		}
		l_strBuf.Empty();
		l_strFormatted.MakeReverse();
		l_strFormatted.TrimLeft();
	}
	if(l_eBitFormat == CBit<T>::All) l_strBuf += l_strFormatted + CString(_T(" ")); else break;
	case CBit<T>::Hexa:
		l_strFormatted.Format(_T("%#x"), m_TVar);
	if(l_eBitFormat == CBit<T>::All) l_strBuf += l_strFormatted + CString(_T(" ")); else break;
	case CBit<T>::Decimal:
		l_strFormatted.Format(_T("%lu"), m_TVar);//Caution : for signed number the number will be wrong, I use %lu so it prints only unsigned number
	if(l_eBitFormat == CBit<T>::All) l_strBuf += l_strFormatted + CString(_T(" ")); else break;
	case CBit<T>::Octal:
		l_strFormatted.Format(_T("%#o"), m_TVar);
	if(l_eBitFormat == CBit<T>::All) l_strFormatted = l_strBuf += l_strFormatted + CString(_T(" ")); else break;
	}//end switch
	return l_strFormatted ;
}


//example of use
/*
void UseOfCBit() 
{
	CBit<unsigned int> var(0x330);
	TRACE(_T("Variable %s\n"),var.print(CBit<unsigned int>::All));
	var.SetBit1(0);
	var.SetBit0(4);
	var.SetBit0(9);
	var.SetBit1(31);

	TRACE(_T("Variable %s\n"),var.print(CBit<unsigned int>::All));
	int value0 = var.GetBit(0);
	int value4 = var.GetBit(4);
	int value5 = var.GetBit(5);
	int value6 = var.GetBit(6);
	int value7 = var.GetBit(7);
	int value8 = var.GetBit(8);
	int value9 = var.GetBit(9);
	int value31 = var.GetBit(31);
	TRACE(_T("value0=%d value4=%d; value5=%d value6=%d; value7=%d value8=%d; value9=%d value31=%d\n"),value0 ,value4, value5,value6, value7,value8, value9,value31 );
}
*/