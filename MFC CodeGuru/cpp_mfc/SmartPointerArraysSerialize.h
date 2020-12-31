///////////////////////////////////////////////////////////////////
// Header File SmartPointerArraysSerialize.h
///////////////////////////////////////////////////////////////////
//
// 309/1/1997 11:28  Author: Poul A. Costinsky  poul@wizsoft.com
// Copyright (C) WizSoft Inc., 1997
///////////////////////////////////////////////////////////////////

#ifndef __CWizSmartPtrArraysSerialize_H
#define __CWizSmartPtrArraysSerialize_H

#include <SerializeVersion.h>
#include <SmartPointersSerialize.h>

///////////////////////////////////////////////////////////////////
template<class ARRAY_TYPE, class TYPE>
void SerializeArray(ARRAY_TYPE& Arr, TYPE* /*null*/, CArchive& ar, int VERSION)
{
	SerializeVersion(ar,VERSION, TRUE); // Throws exception if wrong version
	long n;
	if (ar.IsStoring())
		{
		n = Arr.GetSize();
		ar << n;
		for (INDEX i = 0 ; i < n; i++)
			StoreSmartPtr(ar, Arr.ElementAt(i));
		}	
	else
		{
		ar >> n;
		Arr.RemoveAll();
		Arr.SetSize(n);
		for (INDEX i = 0; i < n; i++)
			{
			LoadSmartPtr(ar, Arr.ElementAt(i), (TYPE*)NULL);
			if (Arr.ElementAt(i).IsNull())
				{ 
				ASSERT(0); 
				AfxThrowArchiveException(CArchiveException::badSchema,ar.m_strFileName);
				}
			}
		}
}
///////////////////////////////////////////////////////////////////

#endif // __CWizSmartPtrArraysSerialize_H


