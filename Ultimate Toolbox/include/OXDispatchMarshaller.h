// ==========================================================================
// 							Class Specification : COXDispatchMarshaller
// ==========================================================================

// Header file : OXDispatchMarshaller.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Description :         
//	Encapsulation of a IStream object used for marshalling between thread.
//	

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXDISPATCHMARSHALLER_H__
#define __OXDISPATCHMARSHALLER_H__


/////////////////////////////////////////////////////////////////////////////
// COXDispatchMarshaller definition

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXDispatchMarshaller
{
// Data Members
public:

protected:
	LPSTREAM	m_pStream;		//	A IStream object used for marshalling between thread (appartements) 
	HANDLE		m_hMutexEvent;	//  Mutex for synchronisation of Marshall and Unmarshall.

private:

// Member Functions
public:
	COXDispatchMarshaller();
	// --- In  : none
	// --- Out : none
	// --- Returns : 
	// --- Effect : constructs the object ans allocates memory for the Stream

	virtual ~COXDispatchMarshaller();
	// --- In  : none
	// --- Out : none
	// --- Returns : 
	// --- Effect : destructs the object ans releases the Stream

	HRESULT Marshal(IDispatch* pDisp);
	// --- In  : pDisp: the dispatch object that needs to be marshalled between to threads
	// --- Out : none
	// --- Returns : the result of the marshalling
	// --- Effect : calls internally CoMarshalInterface (see DSK Ref. for return values)

	HRESULT Unmarshal(void** pDisp);
	// --- In  : none
	// --- Out : none
	// --- Returns : the result of the Unmarshalling
	// --- Effect : calls internally CoUnmarshalInterface (see DSK Ref. for return values)

	BOOL CheckStream();
	// --- In  : none
	// --- Out : none
	// --- Returns : If the internal stream pointer is created successfully
	// --- Effect : 

protected:

private:

};

#endif //__OXDISPATCHMARSHALLER_H__