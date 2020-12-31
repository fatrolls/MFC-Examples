#ifndef __CSimpleFree_h__
#define __CSimpleFree_h__

///////////////////////////////////////////////////////////
//
// CSimpleFree
//   - A simple C++ class that encapsulates creating a
//     component on a free thread.
//


class CSimpleFree 
{
public:
	// Constructor
	CSimpleFree() ;

	// Destructor
	virtual ~CSimpleFree() ;

	// Create and start the thread.
	BOOL StartThread(DWORD WaitTime = 1000) ;

	// Stop the thread.
	void StopThread() ;

	// Current thread status
	BOOL IsThreadStarted() ;

	// Signal other thread to create the component.
	HRESULT CreateComponent(const CLSID& clsid,
	                        const IID& iid,
	                        IUnknown** ppI) ;

// Pure virtual functions
protected:

	// Create the component on this thread.
	virtual HRESULT CreateComponentOnThread(const CLSID& clsid,
	                                        const IID& iid,
	                                        IUnknown** ppI) = 0 ;

	// Function for doing background processing
	virtual void WorkerFunction() = 0 ;


// Member variables
protected:
	// ID of thread
	DWORD m_ThreadId ;

	// Handle to thread
	HANDLE m_hThread ;

	// Event tells free thread to create a component.
	HANDLE m_hCreateComponentEvent ;

	// Event signals main thread to continue.
	HANDLE m_hComponentReadyEvent ;

	// Event used to stop thread
	HANDLE m_hStopThreadEvent ;

	// Pointer to the stream for marshaling the interface
	IStream* m_pIStream ;

	// HRESULT returned when creating component
	HRESULT m_hr ;

	// Pointer to CLSID to create
	const CLSID* m_pclsid ;

	// Pointer to IID of interface to get
	const IID* m_piid ;

	// Time to wait before calling WorkerFunction
	DWORD m_WaitTime ;

// Internal helper functions
private:
	// Thread procedure
	static DWORD WINAPI RealThreadProc(void* pv) ;

	// Member thread procedure
	BOOL ClassThreadProc() ;

	// Helper function to simplify CreateComponentOnThread
	void CreateComponentOnThread() ;

	// Wait for an event, but process window messages.
	BOOL WaitWithMessageLoop(HANDLE hEvent) ;

};

#endif __CSimpleFree_h__
