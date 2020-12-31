// Randexe.cpp : Implementation of CRandexe
#include "stdafx.h"
#include "Conexe.h"
#include "Randexe.h"


void ErrorUI(HRESULT h)
{
    if( h != ERROR_SUCCESS )
    {
        void *pMsgBuf;
        ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                         NULL,
                         h,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT ),
                         (LPSTR)&pMsgBuf,
                         0,
                         NULL );

        ATLTRACE("RANDEXE: Windows error 0x%lx, %s", (DWORD)h, (LPSTR)pMsgBuf );         
        MessageBox( NULL, (LPSTR)pMsgBuf, "Error", MB_ICONSTOP );
        LocalFree(pMsgBuf);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CRandexe

DWORD WINAPI RandomSessionThreadEntry(void* pv)
{
	// Need to call CoInitialize on this thread to create a single
    // threaded apartment. If you don't do this you will get the 
    // "CoInitialize has not been called." error.
    
    ErrorUI(CoInitialize(NULL));
    CRandexe::RandomSessionData* pS = (CRandexe::RandomSessionData*)pv;
	CRandexe* p = pS->pRandom;
	while (WaitForSingleObject(pS->m_hEvent, 0) != WAIT_OBJECT_0)
		ErrorUI(p->Fire(pS->m_nID));
	CoUninitialize();
    return 0;
}

CRandexe::~CRandexe()
{
	StopAll();
}

void CRandexe::CreateRandomSession(RandomSessionData& rs)
{
	DWORD dwThreadID = 0;
	_ASSERTE(rs.m_hEvent == NULL);
	_ASSERTE(rs.m_hThread == NULL);
	rs.pRandom = this;
	rs.m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	rs.m_hThread = CreateThread(NULL, 0, &RandomSessionThreadEntry, &rs, 0, &dwThreadID);
}

STDMETHODIMP CRandexe::Start(long* pnID)
{
	if (pnID == NULL)
		return E_POINTER;
	*pnID = 0;
	HRESULT hRes = S_OK;
	m_cs.Lock();
	for (long i=0;i<nMaxSessions;i++)
	{
		if (m_rsArray[i].m_hEvent == NULL)
		{
			m_rsArray[i].m_nID = i;
			CreateRandomSession(m_rsArray[i]);
			*pnID = i;
			break;
		}
	}
	if (i == nMaxSessions) //fell through
		hRes = E_FAIL;
	m_cs.Unlock();
	return hRes;
}


STDMETHODIMP CRandexe::Stop(long nID)
{
	HRESULT hRes = S_OK;
	m_cs.Lock();
	if (m_rsArray[nID].m_hEvent != NULL)
	{
		SetEvent(m_rsArray[nID].m_hEvent);
		WaitForSingleObject(m_rsArray[nID].m_hThread, INFINITE);
		CloseHandle(m_rsArray[nID].m_hThread);
		memset(&m_rsArray[nID], 0, sizeof(RandomSessionData));
	}
	else
		hRes = E_INVALIDARG;
	m_cs.Unlock();
	return hRes;
}

STDMETHODIMP CRandexe::StopAll()
{
	m_cs.Lock();
	for (long i=0;i<nMaxSessions;i++)
	{
		if (m_rsArray[i].m_hEvent != NULL)
		{
			SetEvent(m_rsArray[i].m_hEvent);
			WaitForSingleObject(m_rsArray[i].m_hThread, INFINITE);
			CloseHandle(m_rsArray[i].m_hThread);
			memset(&m_rsArray[i], 0, sizeof(RandomSessionData));
		}
	}
	m_cs.Unlock();
	return S_OK;
}

// broadcast to all the objects
HRESULT CRandexe::Fire(long nID)
{
    IConnectionPointImpl<CRandexe, &IID_IRandexeEvent, CComDynamicUnkArray>* p = this;
	Lock();
	HRESULT hr = S_OK;
	IUnknown** pp = p->m_vec.begin();
	
    int n = 0;

    while (pp < p->m_vec.end() && hr == S_OK)
	{
		if (*pp != NULL)
		{
			IRandexeEvent* pIRandomEvent = (IRandexeEvent*)*pp;
            _ASSERTE( pIRandomEvent != NULL );

            // If you don't call CoMarshalInterThreadInterfaceInStream
            // followed by CoGetInterfaceAndReleaseStream you will get the
            // "The application called an interface that was marshalled for different thread."
            // error message.

            LPSTREAM pStm;
            hr = CoMarshalInterThreadInterfaceInStream( IID_IRandexeEvent, (IRandexeEvent*)pIRandomEvent, &pStm );
            ErrorUI(hr);

            IRandexeEvent *pI;
            hr = CoGetInterfaceAndReleaseStream( pStm, IID_IRandexeEvent, (void**)&pI );
            ErrorUI(hr);

            hr = pI->Fire(nID);

		}
		pp++;
	}
	Unlock();
	return hr;
}












