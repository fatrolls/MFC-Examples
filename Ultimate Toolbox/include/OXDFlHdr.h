// ==========================================================================
// 							Class Specification : COXDiffFileHeader
// ==========================================================================

// Header file : OXDFlHdr.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	YES	Persistent objects (saveable on disk)      
//	YES	Uses exceptions 
//      Throws 	CArchiveException::badSchema : 	Incorrect file  type
//												Verion incorrect
//				CArchiveException::badClass :   Value of object out of range
//		Passes through 	CArchiveException
//						CFileException
//						CMemoryException

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//		This class encapsulates the header of a binary difference file

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __DIFF_HEADER_H__
#define __DIFF_HEADER_H__
             
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXDiffFileHeader : public CObject
{
DECLARE_DYNAMIC(COXDiffFileHeader)

// Data members -------------------------------------------------------------
public:
	
protected:
	CString m_sSignText;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXDiffFileHeader(CString sSignature);
	// --- In  : sSignature : Signature of object
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	CString GetSignature() const;
    // --- In  : 
	// --- Out : 
	// --- Returns : the signature of the file that was read from disk
	//				 Identifies a file as one of this category
	// --- Effect :
	
	virtual void ReadHeader(CFile* pFile);
	// --- In  : pFile : pointer to file
	// --- Out : 
	// --- Returns : 
	// --- Effect : Reads the object (header) from the file

	virtual void WriteHeader(CFile* pFile);
	// --- In  : pFile : pointer to file
	// --- Out : 
	// --- Returns : 
	// --- Effect : Writes the object (header) to the file

	virtual void Serialize(CArchive& ar);
	// --- In  : ar : archive
	// --- Out : 
	// --- Returns : 
	// --- Effect : Reads or writes the object (header and/or data) to the archive

	COXDiffFileHeader(const COXDiffFileHeader& HdrSrc);
	// --- In :	HdrSrc : Header object which will be copied
	// --- Out : 
	// --- Returns :
	// --- Effect : Copy contruction.
	//				Notice that global memory will be copied
    
	COXDiffFileHeader& operator=(const COXDiffFileHeader& HdrSrc);
	// --- In :	HdrSrc : Header object which will be assign to 'this' Header object
	// --- Out:
	// --- Returns: 
	// --- Effect : Assignment operator 

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual ~COXDiffFileHeader();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object
	
protected:      
	virtual void Read(CArchive& ar, BOOL bReportLogicalErrors = TRUE);
	virtual void Write(CArchive& ar);
		
private:
                   
};

#endif
// ==========================================================================
