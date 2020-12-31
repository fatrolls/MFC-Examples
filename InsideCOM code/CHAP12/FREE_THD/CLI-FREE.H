#ifndef __CClientFree_h__
#define __CClientFree_h__

///////////////////////////////////////////////////////////
//
// CClientFree
//   - A simple C++ class that encapsulates creating a
//     component on a thread.  It creates the component
//     using CoCreateInstance.
//

class CClientFree : public CSimpleFree
{
public:
	// Constructor
	CClientFree() ;

	// Destructor
	virtual ~CClientFree() ;

	// Create and start the thread.
	virtual HRESULT CreateComponentOnThread(const CLSID& clsid,
	                                        const IID& iid,
	                                        IUnknown** ppI) ;

	// Function for doing background processing
	virtual void WorkerFunction() ;

	// Share its interface pointer with another thread
	IX* ShareUnmarshaledInterfacePointer() ;

	// Use the following interface pointer.
	void UseUnmarshaledInterfacePointer(IX* pIX) ;

protected:
	IX* m_pIX ;

	// Mutex to protect the interface pointer.
	HANDLE m_hInterfaceMutex ;

};


class CClientFree2 : public CClientFree
{
public:
	virtual void WorkerFunction() ;
};

#endif __CClientFree_h__
