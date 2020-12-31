// ==========================================================================
// 					Class Specification : COXDataCommunicator
// ==========================================================================

// Header file : OXDataCommunicator.h

//----------------- Dundas Software ----------------------------------------                          
//========================================================================
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from COXCommunicator

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXDATACOMMUNICATOR_H__
#define __OXDATACOMMUNICATOR_H__

#include "OXCommunicator.h"

class CCommunicatorDoc;

class COXDataCommunicator : public COXCommunicator
{
DECLARE_DYNAMIC(COXDataCommunicator)

// Data members -------------------------------------------------------------
public:
	
protected:
	CCommunicatorDoc* m_pCommunicatorDoc;

private:
	
// Member functions ---------------------------------------------------------
public:

	COXDataCommunicator(CCommunicatorDoc* pCommunicatorDoc, UINT nStreamBufferSize = 4096);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs the object

	virtual void OnClientCreate(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator);
	virtual void OnClientReceive(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator, DWORD nSize, int nErrorCode);
	virtual void OnClientClose(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator, int nErrorCode);

	virtual void OnServerReceive(DWORD nSize, int nErrorCode);
	virtual void OnServerClose(int nErrorCode);

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

	virtual ~COXDataCommunicator();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object

protected:

private:
};

#endif // __OXDATACOMMUNICATOR_H__
// ==========================================================================
