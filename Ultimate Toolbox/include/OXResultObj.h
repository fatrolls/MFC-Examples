// ==========================================================================
// 					Class Specification : COXResultObj
// ==========================================================================

// Header file : OXResultObj.h

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	YES	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class encapsulates a collection of COXResultParts

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXRESULTOBJ_H__
#define __OXRESULTOBJ_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "AfxTempl.h"
#include "OXResultPart.h"


class OX_CLASS_DECL COXResultObj : public CArray<COXResultPart, const COXResultPart&>
{
DECLARE_DYNAMIC(COXResultObj);

// Data members -------------------------------------------------------------
public:
protected:
	COXResultPart m_defaultPart;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXResultObj();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs the object

	COXResultObj(const COXResultPart& defaultPart);
	// --- In  : defaultPart
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs the object and sets the default part
	//				The default part will be returned when 
	//				you want to retrieve a part when this object is empty

	COXResultObj(const COXResultObj& result);
	// --- In  : result : Object to copy
	// --- Out : 
	// --- Returns :
	// --- Effect : Copy constructor

	COXResultObj& operator=(const COXResultObj& result);
	// --- In  : result : Object to assigne
	// --- Out : 
	// --- Returns : This object 
	// --- Effect : Assignment operator

	void operator+=(const COXResultObj& result);
	// --- In  : result : Object to add
	// --- Out : 
	// --- Returns : 
	// --- Effect : Adds the specified result to this object

	void operator+=(const COXResultPart& resultPart);
	// --- In  : resultPart : Object to add
	// --- Out : 
	// --- Returns : 
	// --- Effect : Adds the specified result part to this result object

	COXResultPart& GetDefaultPart();
	// --- In  : 
	// --- Out : 
	// --- Returns : The default part

	COXResultPart GetDefaultPart() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : The default part

	void SetDefaultPart(const COXResultPart& defaultPart);
	// --- In  : defaultPart
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets the default part
	//				The default part will be returned when 
	//				you want to retrieve a part when this object is empty

	void Empty();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Empties this result object

	BOOL IsEmpty() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether this object contains any result itemùs (FALSE) or not (TRUE)
	// --- Effect : 

	COXResultPart& GetMostSeverePart();
	// --- In  : 
	// --- Out : 
	// --- Returns : The result part with the highest extended severity
	// --- Effect : When this object does not contain any parts,
	//				a new part is added to this object and returned

	COXResultPart GetMostSeverePart() const;
	// --- In  : 
	// --- Out : 
	// --- Returns : The result part with the highest extended severity
	// --- Effect : When this object does not contain any parts,
	//				a new empty part is returned

	COXResultPart* operator->();
	// --- In  : 
	// --- Out : 
	// --- Returns : The result part with the highest extended severity
	// --- Effect : When this object does not contain any parts,
	//				a new part is added to this object and returned
	//				This is a quick way to get the most severe part from
	//				the collection and perform a function on it

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
#endif

	virtual ~COXResultObj();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object

protected:

private:
                   
};

#endif // __OXRESULTOBJ_H__
// ==========================================================================
