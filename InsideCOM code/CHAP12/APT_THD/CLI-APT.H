#ifndef __CClientApartment_h__
#define __CClientApartment_h__

///////////////////////////////////////////////////////////
//
// CClientApartment
//   - A simple C++ class that encapsulates creating a
//     component on a thread.
//     It creates the component using CoCreateInstance.
//

class CClientApartment : public CSimpleApartment
{
public:
	// Constructor
	CClientApartment() ;

	// Destructor
	virtual ~CClientApartment() ;

	// Create and start the thread.
	virtual HRESULT CreateComponentOnThread(const CLSID& clsid,
                                                const IID& iid,
                                                IUnknown** ppI) ;

	// Function for doing background processing
	virtual void WorkerFunction() ;

protected:
	IX* m_pIX ;

} ;

#endif __CClientApartment_h__
