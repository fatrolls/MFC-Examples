// ==========================================================================
// 					Class Specification : COXBlob
// ==========================================================================

// Header file : OXBlob.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CByteArray

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class is an extension of CByteArray and it can by used
//	to contain a Binary Large Object

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXBLOB_H__
#define __OXBLOB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "OXVariant.h"


class OX_CLASS_DECL COXBlob : public CByteArray
{
DECLARE_DYNAMIC(COXBlob);

// Data members -------------------------------------------------------------
public:
protected:

private:
	
// Member functions ---------------------------------------------------------
public:

	// Constructors
	COXBlob();
	COXBlob(const COXBlob& blobSrc);
	COXBlob(const CByteArray& arrSrc);
	COXBlob(const CLongBinary& lbSrc);

	COXBlob(const VARIANT& varSrc);
	COXBlob(LPCVARIANT pSrc);
	COXBlob(const COleVariant& varSrc);
	COXBlob(const COXVariant& varSrc);

	// Assignemnt operators
	COXBlob& operator=(const COXBlob& blobSrc);
	COXBlob& operator=(const CByteArray& arrSrc);
	COXBlob& operator=(const CLongBinary& lbSrc);

	COXBlob& operator=(const VARIANT& varSrc);
	COXBlob& operator=(LPCVARIANT pSrc);
	COXBlob& operator=(const COleVariant& varSrc);
	COXBlob& operator=(const COXVariant& varSrc);

	BOOL ReadRaw(LPCTSTR pszPath);
	// --- In  : pszPath : The full path specification
	// --- Out : 
	// --- Returns : Whether it succeeded or not
	// --- Effect : Reads data from the specified file into this object

	BOOL WriteRaw(LPCTSTR pszPath);
	// --- In  : pszPath : The full path specification
	// --- Out : 
	// --- Returns : Whether it succeeded or not
	// --- Effect : Writes the data of this object to the specified file

	// Destructor
	virtual ~COXBlob();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object

protected:
	BOOL CopyVariant(LPCVARIANT pSrc);

private:
                   
};

#include "OXBlob.inl"

#endif // __OXBLOB_H__
// ==========================================================================
