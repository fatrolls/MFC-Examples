// ==========================================================================
// 							Class Specification : COXThreadEngine
// ==========================================================================

// Header file : OXOwnThread.h

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
//	YES Two stage creation (constructor & Initialize())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Description :         
//	CThreadEngine class
//		You can use the COXThreadEngine for dedicated access to data objects.
//		It is a good approach to the design of multithreaded applications to prevent
//		as much as possible that specific data is accessed from more than one thread.
//		The class provides build-in functionality such as communication techniques
//		to communicate to and between different engines.
//		Suppose for example that we want to access a CMyOLEObject from more threads.
//	***	The first step is to derive a CMyEngine class from the COXThreadEngine base class.
//		We add the CMyOLEObject as a protected data member of the engine class.
//		Then we overload the pure virtual function "OnExecuteCmd()". This function will
//		be called internally by the COXThreadEngine and needs to dispatch the commands
//		to the appropriated function. Most of the time this can be implemented with a simply
//		switch structure.
//		Next, we have to derive a CMyCmd from the COXEngineCmd class to hold your 
//		command parameters and return values. This class will be used internally to queue
//		multiple calls to the engine object. 
//		Finally we provide a public wrapper function "DoSomething" which queues the CDoSomethingCmd
//		commands. We instantiate a CDoSomethingCmd object which we pass on to the PostCommand()
//		function. The PostCommand function will wait until the engine has executed the
//		command (in this example the command is synchronous). Before we return in this function
//		we need to release the command object. This object is reference counted and will
//		be destroyed automatically. If we now want to return a data member of the command
//		object, we need to copy the value to a temporary variable, because the command object could
//		be destroyed after we called the Release() function.
//
//	*** Communication techniques:
//		+ Synchronous, queued: create a COXEngineCmd without optional parameters and
//		  post it with the PostCommand() function to the COXThreadEngine
//		+ Synchronous, ASAP: create a COXEngineCmd without optional parameters and
//		  post it with the PostCommand() function with the bASAP parameter set to TRUE
//		+ Asynchronous, queued: create a COXEngineCmd with the first parameter set to FALSE
//		  and post it with the PostCommand() function
//		+ Asynchronous, ASAP: create a COXEngineCmd with the first parameter set to FALSE
//		  and post it with the PostCommand() function with the bASAP parameter set to TRUE
//	* OPTIONAL for all the techniques, you can use a second parameter in the 
//		constructor of COXEngineCmd if you want to receive a DONE notification.
//		This can be important for the asynchronous techniques. For this: the requesting
//		object need to be derived of COXDoneNotifier. You need to pass the this pointer 
//		of the requesting object to the constructor of COXEngineCmd. Your requesting object
//		will now receive a DoneCommand() call after the execution of the command.
//		The command itself will be passed on as a parameter. You can use the command type and 
//		the command index to track the initial request. For this, it is important that you 
//		catalogue the index of the command after the construction of it.
//		Important is that you need to call the Release() function of your command also after
//		DONE notification.

// Remark:
//		If you forget the call the Release() function of COXEngineCmd you will end up
//		with memory leaks. 
//		You need to call the COXEngineCmd::Release() function after you posted the command
//		with the COXThreadEngine::PostCommand() function. And you need to call the Release()
//		function ones again if you implement a "done notification" for your command.
//		If the object that requested the command is also running in his own engine,
//		it can be necessary to post done notification commands to the queue of your requesting
//		engine. In this case you need to use a own command for this "Post" which takes the first
//		one, that came with the "done notification" as a data member. In this case you must call
//		the Release() function of the first command in the destructor of the second one.

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////


#ifndef __OXTHREADENGINE_H_
#define __OXTHREADENGINE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"



class COXEngineCmd;
class COXThreadEngine;

class OX_CLASS_DECL COXDoneNotifier
{
friend COXThreadEngine;
protected:
	virtual void DoneCommand(COXEngineCmd* pCmd) = 0;
};

class OX_CLASS_DECL COXEngineCmd : public CObject
{
	DECLARE_DYNAMIC(COXEngineCmd)

friend COXThreadEngine;

// Data Members
public:
	DWORD				m_dwIndex;			// every instantiated command has an unique index
	
protected:
	COXDoneNotifier*	m_pDoneNotifier;	// for optional notification after execution
	HANDLE				m_hFinishedEvent;	// use for synchronisation of synchrone commands
	LONG				m_nRef;				// used for reference counting

private:
	static DWORD		m_dwGlobalIndex;	// internal cyclic counter

// Member Functions
public:
	COXEngineCmd(BOOL bSynchrone = TRUE, COXDoneNotifier* pDoneNotifier = NULL);
	// --- In  : bSynchrone: defines if the command will be executed synchronous or asynchronous
	//			 pDoneNotifier: will be notified when the execution  of the command is done
	// --- Out : none
	// --- Returns : none
	// --- Effect : Contructor of an egine command 

	void Release();
	// --- In  : none
	// --- Out : none
	// --- Returns : none
	// --- Effect : decreases the reference count and deletes the object if zero

	BOOL IsSynchrone() const;
	// --- In  : none
	// --- Out : none
	// --- Returns : if the command is synchronous or not
	// --- Effect : 

protected:
	virtual ~COXEngineCmd();

private:
};

class OX_CLASS_DECL COXThreadEngine : public CObject
{
// Data Members
public:

protected:
	BOOL			m_bEndThread;	// thread shall terminate during next thread event
	BOOL			m_bInitialized;	// if successfully initialised
	CWinThread*		m_pThread;		// thread pointer of the engines thread
	HANDLE			m_hCreatedEvent;// event for initialisation synchronisation
	HANDLE			m_hEndEvent;	// event for termination synchronisation
	HANDLE			m_hThreadEvent;	// event when a new command is posted
	DWORD			m_nTerinationTimeout;

	class OX_CLASS_DECL COXEngineCmdList : public CTypedPtrList<CPtrList, COXEngineCmd*>
	{
	// Data Members
	public:
	protected:
		HANDLE	m_hMutex;
	private:
	// Member functions
	public:
		COXEngineCmdList();
		virtual ~COXEngineCmdList();
		void Lock();
		void Unlock();
	protected:
	private:
	} m_cmdList;

private:

// Member Functions
public:
	COXThreadEngine();
	// --- In  : none
	// --- Out : none
	// --- Returns : none
	// --- Effect : construction of engine (still need to be initialised)

	virtual ~COXThreadEngine();
	// --- In : none
	// --- Out : none
	// --- Returns : none
	// --- Effect : destructs the engine (need to be terminated first)

	BOOL Initialize();
	// --- In : none
	// --- Out : none
	// --- Returns : if the engine is successfully initialised
	// --- Effect : start the engines thread (as a result
	//				OnThreadConstruction() will be called)

	BOOL IsInitialized();
	// --- In : none
	// --- Out : none
	// --- Returns : if the engine is successfully initialised
	// --- Effect :

	void Terminate();
	// --- In : none
	// --- Out : none
	// --- Returns : none
	// --- Effect : stops the engines thread (first 
	//				OnThreadDestruction() will be called)

	void PostCommand(COXEngineCmd* pCmd, BOOL bASAP = FALSE);
	// --- In  : pCmd : the command that will be added to the engines queue
	//			 bASAP : the command will be executed as soon as possible
	//					 when this flag is used the command will be added to
	//					 the head instead of the tail of the queue
	// --- Out : none
	// --- Returns : none
	// --- Effect : the command is added to the engines queue and the engine
	//				thread is notified by an event

protected:
/////////////////////////////////////////////////////////////////////////////
//	--- this function must be overloaded in your derived engine
	virtual void OnExecuteCmd(COXEngineCmd* pCmd) = 0;
	// --- In: pCmd: the next command in the queue that should be executed
	// --- Out: none
	// --- Returns: none
	// --- Effect: Up to YOU !!!!!

	// these two function can be overloaded if some specific initialisation and
	// uninitialisation is needed
	virtual BOOL OnThreadCreation();
	virtual void OnThreadDestruction();

	// these two function can be overloaded if some specific initialisation and
	// uninitialisation is needed
	virtual void OnThreadEvent();

private:
	void Run();
	static UINT StartThread( LPVOID pParam );

};


#endif // __OXTHREADENGINE_H_
