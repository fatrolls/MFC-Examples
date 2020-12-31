///////////////////////////////////////////////////////////////////
// Header File SmartPointerArraysSort.h
///////////////////////////////////////////////////////////////////
//
// 309/1/1997 11:28  Author: Poul A. Costinsky  poul@wizsoft.com
// Copyright (C) WizSoft Inc., 1997
///////////////////////////////////////////////////////////////////

#ifndef __CWizSmartPtrArraysSort_H
#define __CWizSmartPtrArraysSort_H

#include <SmartPointerArrays.h>
#include <WizArr.h>

/////////////////////////////////////////////////////////////////////////////
template<class ARRAY_TYPE, class COMPARE_TYPE>
class CWizSmartPrtComparer
{
public:
	CWizSmartPrtComparer() {}

	int	Compare(ARRAY_TYPE& arr, int i, int j) const
		{
		return m_cRealComparer.Compare(*(arr[i]),*(arr[j]));
		}
private:
	COMPARE_TYPE	m_cRealComparer;
};
/////////////////////////////////////////////////////////////////////////////
// The function for sorting the array
template<class ARRAY_TYPE, class COMPARE_TYPE>
void SortSmartPrtArray(ARRAY_TYPE& Arr, COMPARE_TYPE& Comparer)
{
	if (Arr.GetSize() > 1)
		{
		CWizSmartPrtComparer<ARRAY_TYPE,COMPARE_TYPE> comp;
		CWizArrSort<ARRAY_TYPE,CWizSmartPrtComparer<ARRAY_TYPE,COMPARE_TYPE> > Sorter(Arr, comp);
		Sorter.Sort();
		}
}
/////////////////////////////////////////////////////////////////////////////

#endif // __CWizSmartPtrArraysSort_H


