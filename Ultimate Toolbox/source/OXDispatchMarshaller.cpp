// ==========================================================================
// 							Class Implementation : COXDispatchMarshaller
// ==========================================================================

// Source file : OXDispatchMarshaller.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXDispatchMarshaller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const LARGE_INTEGER     bZero = {0,0};

COXDispatchMarshaller::COXDispatchMarshaller() :
	m_pStream(NULL),
	m_hMutexEvent(NULL)
{
	HRESULT hr;

	m_hMutexEvent = CreateEvent(NULL,FALSE,TRUE,NULL);
    // create an IStream to be used for marshalling new objects between
    // the worker and the CClassFactory
    hr = CreateStreamOnHGlobal(NULL, TRUE, &m_pStream);
    if (hr!=S_OK)
        m_pStream=NULL;
}

COXDispatchMarshaller::~COXDispatchMarshaller()
{
	if (m_pStream != NULL)
		m_pStream->Release();
	CloseHandle(m_hMutexEvent);
}

HRESULT COXDispatchMarshaller::Marshal(IDispatch* pDisp)
{
	HRESULT hResult;
	
	WaitForSingleObject(m_hMutexEvent, INFINITE);
	hResult = m_pStream->Seek(bZero, STREAM_SEEK_SET, NULL);
	if (hResult==S_OK)
	{
		hResult = CoMarshalInterface(m_pStream,
									IID_IDispatch,
  									pDisp,
    								MSHCTX_INPROC,
    								NULL,
    								MSHLFLAGS_NORMAL);
		if (hResult==S_OK)
		{
			// pDisp is now referenced by its marshal-data in vpstmMarshalling.
			// we release our local reference here so the unmarshaller will
			// have the sole reference. a common mistake is to forget this
			// release and end up with orphaned objects in the server.
			pDisp->Release();
		}
	}
	return hResult;
}

HRESULT COXDispatchMarshaller::Unmarshal(void** pDisp)
{
	HRESULT hResult;

	ASSERT(WaitForSingleObject(m_hMutexEvent, 0)==WAIT_TIMEOUT);
	hResult = m_pStream->Seek(bZero, STREAM_SEEK_SET, NULL);
    if (hResult==S_OK)
		hResult = CoUnmarshalInterface(m_pStream, IID_IDispatch, pDisp);
	SetEvent(m_hMutexEvent);
	return hResult;
}

BOOL COXDispatchMarshaller::CheckStream()
{
	return (m_pStream!=NULL);
}
