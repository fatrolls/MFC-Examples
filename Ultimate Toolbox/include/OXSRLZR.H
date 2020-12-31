// ==========================================================================
// 							Class Specification : COXSerializer
// ==========================================================================

// Header file : OXSRLZR.H

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	NO	Is derived from CWnd
//	NO  Two stage creation (constructor & Initialize())
//	NO 	Has a message map
//	NO  Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Description :         
//	COXSerializer class
//    BOOL Initialize(LPCTSTR pFileName, CObject* pObject);
//    ---------------------------------------------------------
//    Set the filename that has to be serialized and its relative object.
//    return FALSE only if an invalid string pointer or a CObject derived
//    object pointer or a not serializable object is passed .
//    Initialize can be called anytime.
//
//    BOOL Load(BOOL DisplayException = TRUE);
//    ----------------------------------------
//    Loads the object from the archive. The object and the file name
//    are to be set by the Initialize function.
//    DisplayException=FALSE: No messages by messagebox are displayed  
//    return FALSE if this object was not initialized or a Exception was
//    encounterd. (see FileException,ArchiveException and MemoryException
//    public data member to obtains more informations)
//
//    BOOL Save(BOOL DisplayException = TRUE);
//    ----------------------------------------------------  
//    Store the object to the archive. The object and the file name
//    are to be set by the Initialize function.
//    DisplayException=FALSE: No messages by messagebox are displayed  
//    return FALSE if this object was not initialized or a Exception was
//    encounterd. (see FileException,ArchiveException and MemoryException
//    public data member to obtains more informations)

// Remark:
//


// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////


#ifndef __OXSRLZR_H__
#define __OXSRLZR_H__


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXSerializer : public CObject
{
// Data Members
public:
    CFileException    m_fileException;		// exceptions as data member
	CArchiveException m_archiveException;	// if you chose not to display exceptions
    BOOL              m_bMemoryException;	// then you can check them via these members

protected:
    BOOL				m_bInitialized;		// if initialized or not
    CString				m_sFileName;		// the filename of the file to serialize from or to
    CObject*			m_pObject;			// the object to serialize

private:

// Member Functions
public:
    COXSerializer();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs the object

	virtual ~COXSerializer();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: destructs the object

    BOOL Initialize(CString sFileName, CObject* pObject);
	// --- In: sFileName: the filename of the file you want to serialize to or from
	//		   pObject: the parent object you want to serialize
	// --- Out: none
	// --- Returns: if the initialization was successful
	// --- Effect: initialize and checks if the object is serializable

    BOOL Load(BOOL bDisplayException = TRUE);
	// --- In: bDisplayException: if the exception is reported
	// --- Out: none
	// --- Returns: if successful or not
	// --- Effect: loads the object (see initialize) from file 

    BOOL Save(BOOL bDisplayException = TRUE);
	// --- In: bDisplayException: if the exception is reported
	// --- Out: none
	// --- Returns: if successful or not
	// --- Effect: saves the object (see initialize) to file 

protected:

private:
};

#endif // __SERIALIZE_ENH_H__

