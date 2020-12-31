// ==========================================================================
//				Class Implementation : COXVariant
// ==========================================================================

// Source file : OXVariant.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXVariant.h"
#include <new.h>		// For ConstructElements()

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Definition of static functions

// Data members -------------------------------------------------------------
// protected:
// private:
	
// Member functions ---------------------------------------------------------
// public:

#ifdef _DEBUG
CDumpContext& AFXAPI operator<<(CDumpContext& dc, COXVariant varSrc)
	{
	// First let the base class implementation process what it can
	operator<<(dc, *(COleVariant*)&varSrc);

	// Then process our extensions
	// Nothing extra to do

	return dc;
	}
#endif

CArchive& AFXAPI operator<<(CArchive& ar, COXVariant varSrc)
	{
	// First let the base class implementation process what it can
	operator<<(ar, *(COleVariant*)&varSrc);

	// Then process our extensions
	if ((V_VT(&varSrc) == (VT_UI1 | VT_ARRAY)) && 
		(SafeArrayGetDim(V_ARRAY(&varSrc)) == 1) )
		{
		void* pBuffer;
		long lLower, lUpper;
		DWORD lSize;

		// ... Make sure that it is an array of BYTEs
		ASSERT(SafeArrayGetElemsize(V_ARRAY(&varSrc)) == 1);
		// ... Get the lower and upper bound
		COXVariant::CheckError(SafeArrayGetLBound(V_ARRAY(&varSrc), 1, &lLower));
		COXVariant::CheckError(SafeArrayGetUBound(V_ARRAY(&varSrc), 1, &lUpper));
		lSize = (DWORD)(lUpper - lLower + 1);
		// ... Get a pointer to the actual data
		COXVariant::CheckError(SafeArrayAccessData(V_ARRAY(&varSrc), &pBuffer));

		// Write the size and data
		ar << lSize;
		ar.Write(pBuffer, lSize);

		// ... Release access
		COXVariant::CheckError(SafeArrayUnaccessData(V_ARRAY(&varSrc)));
		}

	return ar;
	}

CArchive& AFXAPI operator>>(CArchive& ar, COXVariant& varSrc)
	{
	// First let the base class implementation process what it can
	operator>>(ar, *(COleVariant*)&varSrc);

	// Then process our extensions
	if (V_VT(&varSrc) == (VT_UI1 | VT_ARRAY))
		{
		// Read as a only dimensional array of unsigned bytes
		void* pBuffer;
		DWORD lSize;

		// ... Read the needed size
		ar >> lSize;

		// Create a new one dimensional safe array
		VERIFY(VariantClear(&varSrc) == NOERROR);
		V_VT(&varSrc) = VT_UI1 | VT_ARRAY;

		SAFEARRAYBOUND bound;
		bound.cElements = lSize;
		bound.lLbound = 0;
		V_ARRAY(&varSrc) = SafeArrayCreate(VT_UI1, 1, &bound);
		if (V_ARRAY(&varSrc) == NULL)
			{
			TRACE(_T("COXVariant operator>> : Failed to create array\n"));
			AfxThrowMemoryException();
			}

		// Fill with the actual data
		COXVariant::CheckError(SafeArrayAccessData(V_ARRAY(&varSrc), &pBuffer));
		ar.Read(pBuffer, lSize);
		COXVariant::CheckError(SafeArrayUnaccessData(V_ARRAY(&varSrc)));
		}

	return ar;
	}

void COXVariant::CheckError(SCODE sc)
	{
	if (FAILED(sc))
		{
		if (sc == E_OUTOFMEMORY)
			AfxThrowMemoryException();
		else
			AfxThrowOleException(sc);
		}
	}

// protected:
// private:

// Declare special versions for COleVariant
void AFXAPI ConstructElements(COleVariant* pElements, int nCount);
void AFXAPI DestructElements(COleVariant* pElements, int nCount);
void AFXAPI CopyElements(COleVariant* pDest, const COleVariant* pSrc, int nCount);
void AFXAPI SerializeElements(CArchive& ar, COleVariant* pElements, int nCount);
void AFXAPI DumpElements(CDumpContext& dc, COleVariant* pElements, int nCount);

void AFXAPI ConstructElements(COXVariant* pElements, int nCount)
	{
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pElements, nCount * sizeof(COXVariant)));

	for (; nCount--; ++pElements)
		new(pElements) COXVariant;
	}

void AFXAPI DestructElements(COXVariant* pElements, int nCount)
	{
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pElements, nCount * sizeof(COXVariant)));

	for (; nCount--; ++pElements)
		pElements->~COXVariant();
	}

void AFXAPI CopyElements(COXVariant* pDest, const COXVariant* pSrc, int nCount)
	{
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pDest, nCount * sizeof(COXVariant)));
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pSrc, nCount * sizeof(COXVariant)));

	for (; nCount--; ++pDest, ++pSrc)
		*pDest = *pSrc;
	}

void AFXAPI SerializeElements(CArchive& ar, COXVariant* pElements, int nCount)
	{
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pElements, nCount * sizeof(COXVariant)));

	if (ar.IsStoring())
		{
		for (; nCount--; ++pElements)
			ar << *pElements;
		}
	else
		{
		for (; nCount--; ++pElements)
			ar >> *pElements;
		}
	}

#ifdef _DEBUG
void AFXAPI DumpElements(CDumpContext& dc, COXVariant* pElements, int nCount)
	{
	for (; nCount--; ++pElements)
		dc << *pElements;
	}
#endif // _DEBUG

// ==========================================================================
