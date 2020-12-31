// ==========================================================================
// 					Class Specification : COXCommMsg
// ==========================================================================

// Header file : OXCommMSg.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CArray

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class encapsulates strict typed data
//  It is an array of OLE variants.
//	It can be used to communicate data together with the type

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXCOMMMSG_H__
#define __OXCOMMMSG_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include <afxtempl.h>
#include "OXVariant.h"


class OX_CLASS_DECL COXCommMsg : public CArray<COXVariant, COXVariant>
{
DECLARE_DYNAMIC(COXCommMsg)
// Data members -------------------------------------------------------------
public:
	// Possible types
	enum EOXArgumentTypes		// ID   bytes	C-type			member name
		{								
		ATEmpty =	VT_EMPTY,	// (0)	0		-				-
		ATNull =	VT_NULL,	// (1)	0		-				-
		ATBool =	VT_BOOL,	// (11)	2		VARIANT_BOOL	bool
		ATUI1 =		VT_UI1,		// (17)	1		unsigned char	bVal
		ATI2 =		VT_I2,		// (2)	2		short			iVal
		ATI4 =		VT_I4,		// (3)	4		long			lVal
		ATCy =		VT_CY,		// (6)	8		CY				cyVal
		ATR4 =		VT_R4,		// (4)	4		float			fltVal
		ATR8 =		VT_R8,		// (5)	8		double			dblVal
		ATStr =		VT_BSTR,	// (8)	4+len	BSTR			bstrVal
		ATDate =	VT_DATE,	// (7)	8		DATE			date
		ATError =	VT_ERROR,	// (10)	4		SCODE			scode
		ATBlob =	VT_UI1 | VT_ARRAY
								// (8209)4+len	-				-
		};
	
	// Total number of types
	enum
		{
		m_nArgumentTypesCount = 13
		};
	// Array containing all the types
	static EOXArgumentTypes m_types[m_nArgumentTypesCount];
	static LPCTSTR m_typeNames[m_nArgumentTypesCount];
	
protected:
	static WORD m_nMagicNumber;
	static WORD m_nVariantType;

private:
	
// Member functions ---------------------------------------------------------
public:

	COXCommMsg();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs the object

	virtual void Serialize(CArchive& ar);
	// --- In  : ar : Archive used in serialization
	// --- Out : 
	// --- Returns :
	// --- Effect : Serializes the object

#ifdef _DEBUG
	virtual void AssertValid() const;
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : AssertValid performs a validity check on this object 
	//				by checking its internal state. 
	//				In the Debug version of the library, AssertValid may assert and 
	//				thus terminate the program.
	
	virtual void Dump(CDumpContext& dc) const;
	// --- In  : dc : The diagnostic dump context for dumping, usually afxDump.
	// --- Out : 
	// --- Returns :
	// --- Effect : Dumps the contents of the object to a CDumpContext object. 
	//				It provides diagnostic services for yourself and 
	//				 other users of your class. 
	//				Note  The Dump function does not print a newline character
	//				 at the end of its output. 
#endif

	virtual ~COXCommMsg();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object

protected:

private:
                   
};

#endif // __OXCOMMMSG_H__
// ==========================================================================
