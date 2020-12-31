// ==========================================================================
// 					Class Specification : COXDiffProgress
// ==========================================================================

// Header file : progress.h

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
//	NO 	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class encapsulates a progress bar that will be used
//	when calculating the binary differences
// 	You can derive from this class and use and own implementation

// Remark:
//		***

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////

#ifndef __PROGRESS_H__
#define __PROGRESS_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXDiffProgress : public CObject
{
DECLARE_DYNAMIC(COXDiffProgress)
// Data members -------------------------------------------------------------
public:

protected:
	LONG m_MinVal;
	LONG m_MaxVal;
	LONG m_CurPos;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXDiffProgress();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object

	virtual void Init(LONG minVal, LONG maxVal, LPCTSTR pszMessage);
	// --- In  : minVal : Minimum value
	//			 maxVal : Maximum value
	//			 pszMessage : Message text to show
	// --- Out : 
	// --- Returns :
	// --- Effect : Initializes the progress bar

	virtual BOOL Adjust(LONG curVal);
	// --- In  : curVal : The new current value 
	//                    representing the progress
	// --- Out : 
	// --- Returns : Whether the action may continue (TRUE)
	//				 returning FALSE will abort the action in progress
	// --- Effect : Adjust the progress bar

	virtual void Abort(LPCTSTR pszMessage);
	// --- In  : pszMessage : The abort message
	// --- Out : 
	// --- Returns : 
	// --- Effect : This function shows a message to the user and 
	//				aborts the program
	//				This function should never return

	virtual void Close();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Closes the progress bar

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	virtual ~COXDiffProgress();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:

private:
                   
};

#endif	// __PROGRESS_H__
// ==========================================================================
