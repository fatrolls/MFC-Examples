//////////////////////////////////////////////////////////////////////////////
// ThreadManager.h

#ifndef __THREADMANAGER_H_
#define __THREADMANAGER_H_

#ifndef _BUILD_THREADMANAGER		// only do this if the header is being used to import the class
	#define CLASS_DECL_PORT_THREADMANAGER _declspec( dllimport )
	#ifdef _DEBUG 
		#pragma comment(lib, "ThreadManagerD.lib")		// Solves the problem of having to explicitly include this lib
	#else
		#pragma comment(lib, "ThreadManager.lib")		// Solves the problem of having to explicitly include this lib
	#endif 
#else
	#define CLASS_DECL_PORT_THREADMANAGER _declspec( dllexport )
#endif


void CLASS_DECL_PORT_THREADMANAGER StopThreadManager( CDWORD cdwTimeToWait=INFINITE );

typedef UINT (APIPRIVATE *CONSOLETHREADPROC)(LPVOID);

class CLASS_DECL_PORT_THREADMANAGER CThreadManager : public CObject
{
	DECLARE_DYNAMIC( CThreadManager )
	// Constructors
public:
	CThreadManager( CONSOLETHREADPROC pfnThreadProc, LPVOID pParam);
	~CThreadManager();
	CBOOL RunThread();
	HANDLE GetThreadHandle() const { return( m_Handle ); };
	//Implmentation
public:
	// Operators
private:

public:
	// Debug type stuff
	virtual void Dump( CDumpContext &dc ) const
		{	CObject::Dump( dc );
			dc << "\nm_Handle = " << m_Handle << endl;
		}

// Attributes
private:
	// valid after construction
	HANDLE m_Handle;
};		// End class CThreadManager 

//////////////////////////////////////////////////////////////////////////////
#endif // __THREADMANAGER_H_
