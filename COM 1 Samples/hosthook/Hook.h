///////////////////////////////////////////////////
//
//  Hook.h - Copyright 1997, Don Box
//  
//  A host info channel hook
//
//

#ifndef _HOSTHOOK_H
#define _HOSTHOOK_H

#include <windows.h>

class HostHook : public IChannelHook
{
public:
	STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

    STDMETHODIMP_(void) ClientGetSize(REFGUID uExtent, REFIID riid, ULONG *pDataSize);
    STDMETHODIMP_(void) ClientFillBuffer(REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer);
    STDMETHODIMP_(void) ClientNotify(REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep, HRESULT hrFault);

    STDMETHODIMP_(void) ServerNotify(REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep);
    STDMETHODIMP_(void) ServerGetSize(REFGUID uExtent, REFIID riid, HRESULT hrFault, ULONG *pDataSize); 
    STDMETHODIMP_(void) ServerFillBuffer(REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer, HRESULT hrFault);
};

#endif
