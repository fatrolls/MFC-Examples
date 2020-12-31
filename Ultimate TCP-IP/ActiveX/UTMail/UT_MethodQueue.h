// =================================================================
//  class: CUT_MethodQueue
//  File:  UT_MethodQueue.h
//  
//  Purpose:
//	
//		Non blocking methods queue implementation
//	
// =================================================================
// Ultimate TCP/IP v2.0
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// =================================================================

#if !defined(AFX_UT_METHODQUEUE_H__1D589A3A_0A2B_11D3_A46B_0080C858F182__INCLUDED_)
#define AFX_UT_METHODQUEUE_H__1D589A3A_0A2B_11D3_A46B_0080C858F182__INCLUDED_

#include <stdarg.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		_VP(x)				&_variant_t(x)		// Variant pointer macro
#define		MAX_PARAM_NUMBER	10					// Max parameters number


/////////////////////////////////////////
// CUT_MethodQueue class
/////////////////////////////////////////
template <class T, class MethodIDEnum>
class CUT_MethodQueue  
{

protected:

	// Method list item structure
    typedef struct UTMethodListTag {
        MethodIDEnum		m_MethodID;				// Method ID
		_variant_t			*m_VarParams;			// Pointer to the parameters array

        UTMethodListTag		*pNext;					// Pointer to the next list item
    } UTMethodList;


    UTMethodList	*m_list;						// Pointer to the methods list
	T				*m_ptrT;						// Pointer to the derived class 
	BOOL			m_bMethodThreadRunning;			// Thread running flag
	HANDLE			m_hMethodThread;				// Thread handle
	CComCriticalSection	m_ListLock;					// List box critical section object
	unsigned		m_nThreadID;					// Thread ID

public:
	/////////////////////////////////////////
	// Constructor
	/////////////////////////////////////////
	CUT_MethodQueue(T *pT) : 
					m_ptrT(pT),						// Initialize pointer to the derived class 
					m_list(NULL),					// Initialize pointer to the methods list
					m_hMethodThread(0),				// Initialize thread handle
					m_bMethodThreadRunning(FALSE)	// Clear thread running flag
	{
		// Initialize critical section
		m_ListLock.Init();

		// Starts methods thread
		m_hMethodThread = (HANDLE)_beginthreadex(	NULL,
													0,
													( unsigned (__stdcall *)(void *))	MethodsThread, 
													(void *) this,
													CREATE_SUSPENDED,
													&m_nThreadID);
	}

	/////////////////////////////////////////
	// Virtual destructor
	/////////////////////////////////////////
	virtual ~CUT_MethodQueue() 
	{
		// Lock methods list 
		m_ListLock.Lock();

		// Clear methods list
		UTMethodList	*pNextItem;
		while(m_list != NULL) {
			pNextItem = m_list->pNext;
			if(m_list->m_VarParams)
				delete[] m_list->m_VarParams;
			delete m_list;
			m_list = pNextItem;
			}

		// Unlock methods list 
		m_ListLock.Unlock();

		// Terminate critical section
		m_ListLock.Term();

	}

	/////////////////////////////////////////
	// Methods thread function
	/////////////////////////////////////////
	static unsigned __stdcall  MethodsThread( LPVOID pThis )
	{

		T	*ptrT	= (T*) pThis;

		// Run thread till GoingToClose flag is not set
		while( !ptrT->m_bGoingToClose ) {

			ptrT->m_bMethodThreadRunning = TRUE;

			// Lock methods list 
			ptrT->m_ListLock.Lock();

			// Get the first list item
			UTMethodList	*pFirstItem = ptrT->m_list;
			if(pFirstItem != NULL)
				ptrT->m_list = pFirstItem->pNext;

			// Unlock methods list 
			ptrT->m_ListLock.Unlock();

			// If first list item is not NULL
			if(pFirstItem != NULL) {
				// Initialize COM library
				if(CoInitialize(NULL) == S_OK) {
					// Execute method 
					ptrT->ExecuteMethod(pFirstItem->m_MethodID, 
										pFirstItem->m_VarParams, 
										TRUE);	
					CoUninitialize();					
					}

				// Free item data
				if(pFirstItem->m_VarParams)
					delete[] pFirstItem->m_VarParams;

				delete pFirstItem;
				}

			// Nothing to do - suspend thread
			else {
				ptrT->m_bMethodThreadRunning = FALSE;
				SuspendThread(ptrT->m_hMethodThread);
				}
			}


		// Close handle
		CloseHandle(ptrT->m_hMethodThread);
		ptrT->m_hMethodThread = NULL;

		// Exit thread
		_endthreadex(0);
		return 0;
	}

	/////////////////////////////////////////
	// Adds new method to the queue
	/////////////////////////////////////////
	BOOL	AddMethod(MethodIDEnum ID, long *Result, _variant_t *Param1, ... ) 
	{
		_variant_t		*ptrParam = Param1, *ptrVarArray = new _variant_t[MAX_PARAM_NUMBER];
		va_list			marker;
		int				nParamNumber = 0;

		// Clear abort flag
		m_ptrT->m_bAbortFlag	= FALSE;

		// Initialize variable arguments. 
		va_start( marker, Param1 );	

		// Last variable must be NULL
		while( ptrParam != NULL) {
			ATLASSERT(nParamNumber < MAX_PARAM_NUMBER);
			ptrVarArray[nParamNumber] = *ptrParam;
			++ nParamNumber;

			// Get next parameter
			ptrParam = va_arg( marker, _variant_t*);
			}

		va_end( marker );    
		
		
		// If we use blocking mode just run the method & return
		if(m_ptrT->m_bBlockingMode) {
			*Result = ExecuteMethod(ID, ptrVarArray, FALSE);
			delete [] ptrVarArray;
			return TRUE;
			}

		// If we use nonblocking mode add metod to the queue

		// Lock methods list 
		m_ListLock.Lock();

		// Adds method to the list
		UTMethodList	*pItem = m_list;
		
		// If list is empty
		if(pItem == NULL) {						
			pItem = new UTMethodList;
			m_list = pItem;
			pItem->pNext = NULL;
			}

		// If list is not empty
		else {
			// Search for the last item in the list
			while(pItem->pNext != NULL)
				pItem = pItem->pNext;
		
			pItem->pNext = new UTMethodList;
			pItem = pItem->pNext;
			pItem->pNext = NULL;
			}

		// Initialize new item data
		pItem->m_MethodID = ID;
		pItem->m_VarParams = ptrVarArray;

		// Unlock methods list 
		m_ListLock.Unlock();

		// Set return code
		*Result = ecSuccess;

		// Marshal all event sinks intefaces into streams
		if(!m_bMethodThreadRunning) 
			m_ptrT->MarshalInterfacesToStream(m_ptrT);

		// Resume working thread
		ResumeThread(m_hMethodThread);

		return TRUE;
	}


	/////////////////////////////////////////
	// Abstract virtual functions executes 
	// the specified method
	/////////////////////////////////////////
	virtual long ExecuteMethod(MethodIDEnum MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking) = 0;

};

#endif // !defined(AFX_UT_METHODQUEUE_H__1D589A3A_0A2B_11D3_A46B_0080C858F182__INCLUDED_)
