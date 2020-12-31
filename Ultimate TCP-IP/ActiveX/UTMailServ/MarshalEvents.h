//=================================================================
//  class: CMarshalEvents
//  File:  MarshalEvents.h
//
//  Finger ActiveX control event sink marshalling
//
//=================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
//=================================================================

#if !defined(AFX_MARSHALEVENTS_H__B63A9000_ED4F_11D2_A443_0080C858F182__INCLUDED_)
#define AFX_MARSHALEVENTS_H__B63A9000_ED4F_11D2_A443_0080C858F182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Event sinks Marshaled inteface list item
typedef struct MarshalInterfaceTag{
    IStream		*pStream;				// IStream inteface were IDispatch was marshaled
	IDispatch	*pDispatch;				// Original IDispatch interface
	IDispatch	*pMarshaledDispatch;	// UnMarshaled IDispatch interface

    MarshalInterfaceTag *pNext;			// Pointer to the next item
	} MarshalInterface;


/***************************************************
	Events are signaled by calling the Invoke method 
	of an IDispatch interface supplied by container.
	The interface lives in the appartment of its own 
	thread, which is also the one containing the control
	itself. To comply with the STA model, we can only 
	safely call this interface's methods from the thread 
	in which it was created. If the control wants to 
	signal an event from a different thread it must
	Marshal the IDispatch interface into the IStream
	first and then UnMarshal it.

	class T	- object class
	piid	- IDispatch interface of the object events

	bMultipleStreamUse	- TRUE if we are going to signal 
		events from more than one thread. In this case,
		we dont release the IStream interface after
		UnMarshaling becase we need to do that in each
		thread.

	The Fire_XXXX methods of the proxy (CProxy_XXXX<class T>)
	must be changed. ATTENTION! This changes may be overwritten
	by Connection Point Implementation wizard.

	*** Old code:

		pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
  
	*** New code:

		IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
		if(pMarshaledDispatch) {
			pMarshaledDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
					
			// Add this line only if bMultipleStreamUse = TRUE
			pMarshaledDispatch->Release();
			}

****************************************************/
template <class T, const IID* piid, BOOL bMultipleStreamUse>
class CMarshalEvents  
{
public:

	/***************************************************
	CMarshalEvents
		Constructor
	Params
		none
	Return
		none
	****************************************************/
	CMarshalEvents() : m_ptrInterfaces(NULL)	// Initialize interface list
	{ 
	}
	
	/***************************************************
	~CMarshalEvents
		Virtual destructor
	Params
		none
	Return
		none
	****************************************************/
	virtual ~CMarshalEvents() 
	{ 
		ClearInterfaceList();			// Clear interface list
	}

	/***************************************************
	MarshalInterfacesToStream
		Marshall all sink IDispatch into the stream interfaces
	Params
		pT	- pointer to the object class
	Return
		none
	****************************************************/
	void MarshalInterfacesToStream( T *pT ) 
	{
		if(pT) {
			HRESULT				hr;
			MarshalInterface	*ptrNextItem = NULL;
			IStream				*ptrStream;
			int					nConnectionIndex;
			int					nConnections = pT->IConnectionPointImpl<T, piid, CComDynamicUnkArray>::m_vec.GetSize();

			// Clear the list and release interfaces
			ClearInterfaceList();

			// Loop through all connected sinks
			for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++) {
				pT->Lock();
				CComPtr<IUnknown> sp = pT->IConnectionPointImpl<T, piid, CComDynamicUnkArray>::m_vec.GetAt(nConnectionIndex);
				pT->Unlock();
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);

				if (pDispatch != NULL) {

					// Marshal interface into the stream
					if(bMultipleStreamUse)
						hr = AtlMarshalPtrInProc(pDispatch, IID_IDispatch, &ptrStream);
					else
						hr = CoMarshalInterThreadInterfaceInStream(IID_IDispatch, pDispatch, &ptrStream);

					// Add new inteface list item
					if( hr == S_OK) {
						if(ptrNextItem == NULL) {
							m_ptrInterfaces = new MarshalInterface;
							ptrNextItem = m_ptrInterfaces;
							}
						else {
							ptrNextItem->pNext =  new MarshalInterface;
							ptrNextItem = ptrNextItem->pNext;
							}

						// Initialize new inteface list item
						ptrNextItem->pStream = ptrStream;
						ptrNextItem->pDispatch = pDispatch;
						ptrNextItem->pMarshaledDispatch = NULL;
						ptrNextItem->pNext = NULL;
						}
					}
				}
			}
		}

	/***************************************************
	GetMarshaledInterface
		Returns marshaled IDispatch interface. If bMultipleStreamUse
		is FALSE the IStream interface will be released.
	Params
		ptrIDispatch	- original IDispatch interface
	Return
		none
	****************************************************/
	IDispatch *GetMarshaledInterface(IDispatch *ptrIDispatch)
	{
		IDispatch	*ptrResult = NULL;
		HRESULT		hr;

		// Try to find original IDispatch in the Interfaces list
		MarshalInterface	*ptrNextItem = m_ptrInterfaces;
		while(ptrNextItem != NULL) {
			if(ptrNextItem->pDispatch == ptrIDispatch) {
				if((!m_ptrInterfaces->pMarshaledDispatch || bMultipleStreamUse) && m_ptrInterfaces->pStream) {

					// If we are going to use IStream more than once
					// don't release it
					if(bMultipleStreamUse) {
						// Unmarshal IDispatch from IStream
						hr = AtlUnmarshalPtr( m_ptrInterfaces->pStream, IID_IDispatch, (IUnknown **) &m_ptrInterfaces->pMarshaledDispatch );
						}
					else {
						// Unmarshal IDispatch from IStream and release IStream 
						hr = CoGetInterfaceAndReleaseStream(m_ptrInterfaces->pStream, IID_IDispatch, (void **) &m_ptrInterfaces->pMarshaledDispatch);

						m_ptrInterfaces->pStream = NULL;
						}

					if(hr != S_OK)
						return NULL;

					}

				ptrResult = m_ptrInterfaces->pMarshaledDispatch;
				}
			
			ptrNextItem = ptrNextItem->pNext;
			}

		return ptrResult;
	}

private:

	/***************************************************
	ClearInterfaceList
		Clear list and release Interfaces
	Params
		none
	Return
		none
	****************************************************/
	void ClearInterfaceList()
	{
		MarshalInterface	*ptrNextItem;

		while(m_ptrInterfaces != NULL){
			ptrNextItem = m_ptrInterfaces->pNext;
			try {
				if(m_ptrInterfaces->pStream)
					m_ptrInterfaces->pStream->Release();
				// In multiple stream use releasing of the interface is the client responsebilty
				if(m_ptrInterfaces->pMarshaledDispatch && !bMultipleStreamUse)
					m_ptrInterfaces->pMarshaledDispatch->Release();
				delete m_ptrInterfaces;
				}
			catch(...) {}
			m_ptrInterfaces = ptrNextItem;
			}
   	}


private:

	MarshalInterface	*m_ptrInterfaces;	// Marshaled interface list

};

#endif // !defined(AFX_MARSHALEVENTS_H__B63A9000_ED4F_11D2_A443_0080C858F182__INCLUDED_)


