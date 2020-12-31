// ==========================================================================
// 					Class Specification : COXVariant
// ==========================================================================

// Header file : OXVariant.h

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from COleVariant

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class is an extension on COleVariant
//  It supports the serialization of byte arrays (VT_UI1 | VT_ARRAY)

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXVARIANT_H__
#define __OXVARIANT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXVariant : public COleVariant
{
// Data members -------------------------------------------------------------
public:
protected:

private:
	
// Member functions ---------------------------------------------------------
public:

	// Constructors
	COXVariant();

	COXVariant(const VARIANT& varSrc);
	COXVariant(LPCVARIANT pSrc);
	COXVariant(const COleVariant& varSrc);
	COXVariant(const COXVariant& varSrc);

	COXVariant(LPCTSTR lpszSrc);
	COXVariant(CString& strSrc);

	COXVariant(BYTE nSrc);
	COXVariant(short nSrc, VARTYPE vtSrc = VT_I2);
	COXVariant(long lSrc, VARTYPE vtSrc = VT_I4);
	COXVariant(const COleCurrency& curSrc);
   COXVariant(bool bSrc);

	COXVariant(float fltSrc);
	COXVariant(double dblSrc);
	COXVariant(const COleDateTime& timeSrc);

	COXVariant(const CByteArray& arrSrc);
	COXVariant(const CLongBinary& lbSrc);

	COXVariant(LPCTSTR lpszSrc, VARTYPE vtSrc);    // Used by DAO classes

   // Assignemnt operators
	const COXVariant& operator=(const VARIANT& varSrc);
	const COXVariant& operator=(LPCVARIANT pSrc);
	const COXVariant& operator=(const COleVariant& varSrc);
	const COXVariant& operator=(const COXVariant& varSrc);

	const COXVariant& operator=(const LPCTSTR lpszSrc);
	const COXVariant& operator=(const CString& strSrc);

	const COXVariant& operator=(BYTE nSrc);
	const COXVariant& operator=(short nSrc);
	const COXVariant& operator=(long lSrc);
	const COXVariant& operator=(const COleCurrency& curSrc);
	const COXVariant& operator=(bool bSrc);

	const COXVariant& operator=(float fltSrc);
	const COXVariant& operator=(double dblSrc);
	const COXVariant& operator=(const COleDateTime& dateSrc);

	const COXVariant& operator=(const CByteArray& arrSrc);
	const COXVariant& operator=(const CLongBinary& lbSrc);

	static void CheckError(SCODE sc);
	// --- In  : The result an OLE call
	// --- Out : 
	// --- Returns :
	// --- Effect : If the result code indicates failure an COleException is thrown
	//				unless it indicates out of memory, then a CMemoryException is thrown
	//				When no failure is indicated, this function does nothing

	virtual ~COXVariant();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object

protected:

private:
                   
};

// COXVariant diagnostics and serialization
#ifdef _DEBUG
OX_API_DECL CDumpContext& AFXAPI operator<<(CDumpContext& dc, COXVariant varSrc);
#endif
OX_API_DECL CArchive& AFXAPI operator<<(CArchive& ar, COXVariant varSrc);
OX_API_DECL CArchive& AFXAPI operator>>(CArchive& ar, COXVariant& varSrc);

// special collections functions for COXVariant
OX_API_DECL void AFXAPI ConstructElements(COXVariant* pElements, int nCount);
OX_API_DECL void AFXAPI DestructElements(COXVariant* pElements, int nCount);
OX_API_DECL void AFXAPI CopyElements(COXVariant* pDest, const COXVariant* pSrc, 
									 int nCount);
OX_API_DECL void AFXAPI SerializeElements(CArchive& ar, COXVariant* pElements, 
										  int nCount);
OX_API_DECL void AFXAPI DumpElements(CDumpContext& dc, COXVariant* pElements, 
									 int nCount);

#include "OXVariant.inl"

#endif // __OXVARIANT_H__
// ==========================================================================
