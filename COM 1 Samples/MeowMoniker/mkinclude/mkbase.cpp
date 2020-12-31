/////////////////////////////////////////////////////////////////////////////
// ComMonikerBase.cpp: CComMonikerBase definition
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1997, Tim Ewald, Chris Sells and Don Box.
// All rights reserved.

#include <windows.h>
#include "mkbase.h"
#include "..\yacl\include\smartif.h"

STDMETHODIMP CComMonikerRootBase::Reduce(
    IBindCtx*   pbc,
    DWORD       dwReduceHowFar,
    IMoniker**  ppmkToLeft,
    IMoniker**  ppmkReduced)
{
    HRESULT hr = E_INVALIDARG;
    if( ppmkReduced )
    {
        (*ppmkReduced = this)->AddRef();
        hr = MK_S_REDUCED_TO_SELF;
    }
    return hr;
}

STDMETHODIMP CComMonikerRootBase::ComposeWith(
    IMoniker*   pmkRight,
    BOOL        fOnlyIfNotGeneric,
    IMoniker**  ppmkComposite)
{
    HRESULT hr = E_INVALIDARG;
    if( ppmkComposite )
    {
        *ppmkComposite = 0;
        if( pmkRight )
        {
            DWORD dwMkSys;
            hr = pmkRight->IsSystemMoniker(&dwMkSys);
            if( !(hr == S_OK && dwMkSys == MKSYS_ANTIMONIKER) )
            {
                if( fOnlyIfNotGeneric )
                    hr = MK_E_NEEDGENERIC;
                else
                    hr = CreateGenericComposite(this, pmkRight, ppmkComposite);
            }
            else
                hr = S_OK; // right is AntiMoniker, so we're done
        }
    }
    return hr;
}

STDMETHODIMP CComMonikerRootBase::Inverse(
    IMoniker**  ppmk)
{
    return CreateAntiMoniker(ppmk);
}

STDMETHODIMP CComMonikerRootBase::CommonPrefixWith(
    IMoniker*   pmkOther,
    IMoniker**  ppmkPrefix)
{
    HRESULT hr = E_INVALIDARG;
    if( ppmkPrefix )
    {
        *ppmkPrefix = 0;
        if( pmkOther )
        {
            hr = this->IsEqual(pmkOther);
            if( hr == S_OK )
            {
                (*ppmkPrefix = this)->AddRef();
                hr = MK_S_US;
            }
            else
                hr = MonikerCommonPrefixWith(this, pmkOther, ppmkPrefix);
        }
    }
    return hr;
}

STDMETHODIMP CComMonikerRootBase::RelativePathTo(
    IMoniker*   pmkOther, 
    IMoniker**  ppmkRelPath)
{
    HRESULT hr = E_INVALIDARG;
    if( ppmkRelPath != 0 )
    {
        *ppmkRelPath = 0;
        hr = MonikerRelativePathTo(this, pmkOther, ppmkRelPath, TRUE);
    }
    return hr;
}



HRESULT CComMonikerBase::CacheDisplayName()
{
    HRESULT hr = S_OK;

    // If we don't have the constant display named
    // cached, ask the derived class for it.
    if( !m_pwszDisplayName )
    {
        SI(IBindCtx)    pbc;
        hr = CreateBindCtx(0, pbc.ItfRef());

        if( SUCCEEDED(hr) )
        {
            // Const-cast is required as Monikers are
            // set once and then read-only.
            hr = GetDisplayName(pbc.Itf(), 0,
                                const_cast<OLECHAR**>(&m_pwszDisplayName));
        }
    }

    return hr;
}

// IPersistStream
STDMETHODIMP CComMonikerBase::IsDirty()
{
    // Monikers are constant (hence the by-value marshaling)
    return S_FALSE;
}

STDMETHODIMP CComMonikerBase::Load(
    IStream* pstm)
{
    HRESULT hr;

    if( !pstm ) return E_INVALIDARG;
    if( m_pwszDisplayName ) return E_UNEXPECTED;

    // TODO: Support other platforms
    DWORD   cb;
    DWORD   nTag;
    hr = pstm->Read(&nTag, sizeof(nTag), &cb);
    if( FAILED(hr) ) return hr;
    if( nTag != NDR_LOCAL_DATA_REPRESENTATION ) return E_UNEXPECTED;

    DWORD   nSize;
    hr = pstm->Read(&nSize, sizeof(nSize), &cb);
    if( FAILED(hr) ) return hr;

    // Const-cast is required as Monikers are
    // set once and then read-only.
    m_pwszDisplayName = (OLECHAR*)CoTaskMemAlloc(nSize);
    if( !m_pwszDisplayName ) return E_OUTOFMEMORY;

    hr = pstm->Read(const_cast<OLECHAR*>(m_pwszDisplayName), nSize, &cb);
    if( FAILED(hr) ) return hr;

    ULONG           cch;
    SI(IBindCtx)    pbc;
    SI(IMoniker)    pmk;

    hr = CreateBindCtx(0, pbc.ItfRef());
    if( FAILED(hr) ) return hr;

    // const_cast<> required because
    // ParseDisplayName() isn't const correct!
    hr = ParseDisplayName(pbc.Itf(), 0,
                          const_cast<OLECHAR*>(m_pwszDisplayName),
                          &cch, pmk.ItfRef());

    return hr;
}

STDMETHODIMP CComMonikerBase::Save(
    IStream*    pstm,
    BOOL        fClearDirty)
{
    HRESULT hr;
    if( !pstm ) return E_INVALIDARG;

    hr = CacheDisplayName();
    if( SUCCEEDED(hr) )
    {
        DWORD   nSize = (wcslen(m_pwszDisplayName) + 1) * sizeof(OLECHAR);
        DWORD   nTag = NDR_LOCAL_DATA_REPRESENTATION;
        DWORD   cb;

        if( SUCCEEDED(hr = pstm->Write(&nTag, sizeof(nTag), &cb)) &&
            SUCCEEDED(hr = pstm->Write(&nSize, sizeof(nSize), &cb)) )
        {
            hr = pstm->Write(m_pwszDisplayName, nSize, &cb);
        }
    }

    return hr;
}

STDMETHODIMP CComMonikerBase::GetSizeMax(
    ULARGE_INTEGER* pcbSize)
{
    HRESULT hr;
    if( !pcbSize ) return E_POINTER;

    hr = CacheDisplayName();
    if( SUCCEEDED(hr) )
    {
        pcbSize->LowPart = sizeof(DWORD) +  // NDR data rep.
                           sizeof(DWORD) +  // Display name size
                           wcslen(m_pwszDisplayName) +  // Display name
                           sizeof(OLECHAR); // NULL
        pcbSize->HighPart = 0;
    }

    return hr;
}

// IMarshal
STDMETHODIMP CComMonikerBase::GetUnmarshalClass(
    REFIID  riid,
    void*   pv,
    DWORD   dwDestContext,
    void*   pvDestContext,
    DWORD   mshlflags,
    CLSID*  pCid)
{
    return GetClassID(pCid);
}

STDMETHODIMP CComMonikerBase::GetMarshalSizeMax(
    REFIID  riid,
    void*   pv,
    DWORD   dwDestContext,
    void*   pvDestContext,
    DWORD   mshlflags,
    DWORD*  pSize)
{
    HRESULT hr;

    if( !pSize ) return E_POINTER;
    *pSize = 0;

    ULARGE_INTEGER  uli;
    hr = GetSizeMax(&uli);
    if( SUCCEEDED(hr) )
    {
        *pSize = uli.LowPart;
    }

    return hr;
}

STDMETHODIMP CComMonikerBase::MarshalInterface(
    IStream*    pstm,
    REFIID      riid,
    void*       pv,
    DWORD       dwDestContext,
    void*       pvDestContext,
    DWORD       mshlflags)
{
    return Save(pstm, FALSE);
}

STDMETHODIMP CComMonikerBase::UnmarshalInterface(
    IStream*    pstm,
    REFIID      riid,
    void**      ppv)
{
    HRESULT hr;
    if( !ppv ) return E_POINTER; *ppv = 0;

    hr = Load(pstm);
    if( SUCCEEDED(hr) )
    {
        hr = QueryInterface(riid, ppv);
    }

    return hr;
}

STDMETHODIMP CComMonikerBase::ReleaseMarshalData(
    IStream*    /*pstm*/)
{
    return S_OK;
}

STDMETHODIMP CComMonikerBase::DisconnectObject(
    DWORD   /*dwReserved*/)
{
    return S_OK;
}

// IMoniker

STDMETHODIMP CComMonikerBase::BindToStorage(
    IBindCtx*   /*pbc*/,
    IMoniker*   /*pmkToLeft*/,
    REFIID      /*riid*/,
    void**      ppvObj)
{
    if( !ppvObj ) return E_POINTER;
    *ppvObj = 0;
    return E_NOTIMPL;
}

STDMETHODIMP CComMonikerBase::Enum(
    BOOL            fForward,
    IEnumMoniker**  ppenumMoniker)
{
    if( !ppenumMoniker ) return E_POINTER;
    *ppenumMoniker = 0;
    return S_OK;
}

STDMETHODIMP CComMonikerBase::IsEqual(
    IMoniker*   pmkOtherMoniker)
{
    HRESULT hr;

    // Check the type of the other moniker for us
    CLSID   clsid;
    CLSID   clsidOther;

    if( SUCCEEDED(hr = GetClassID(&clsid)) &&
        SUCCEEDED(hr = pmkOtherMoniker->GetClassID(&clsidOther)) )
    {
        if( clsid == clsidOther )
        {
            SI(IROTData)    prd;
            hr = pmkOtherMoniker->QueryInterface(IID_PPV(prd));
            if( SUCCEEDED(hr) )
            {
                byte	rgb[2][2048];
                ULONG	cbData[2];
    
                if( SUCCEEDED(hr = GetComparisonData(rgb[0], 2048, cbData + 0)) &&
                    SUCCEEDED(hr = prd->GetComparisonData(rgb[1], 2048, cbData + 1)) )
                {
                    if( cbData[0] == cbData[1] &&
                        memcmp(rgb[0], rgb[1], cbData[0]) == 0 )
                    {
                        hr = S_OK;
                    }
                    else
                    {
                        hr = S_FALSE;
                    }
                }
            }
        }
        else
        {
            hr = S_FALSE;
        }
    }

    return hr;
}

STDMETHODIMP CComMonikerBase::Hash(
    DWORD*  pdwHash)
{
    HRESULT hr = S_OK;
    if( !pdwHash ) return E_POINTER; *pdwHash = 0;
    if( !m_pwszDisplayName ) return E_UNEXPECTED;

    // TODO: Pick something better than a sum
    const OLECHAR*  pwsz = m_pwszDisplayName;
    while( pwsz )
    {
        *pdwHash += *pwsz;
        pwsz++;
    }

    return hr;
}

STDMETHODIMP CComMonikerBase::IsRunning(
    IBindCtx*   /*pbc*/,
    IMoniker*   /*pmkToLeft*/,
    IMoniker*   /*pmkNewlyRunning*/)
{
    return S_FALSE;
}

STDMETHODIMP CComMonikerBase::GetTimeOfLastChange(
    IBindCtx*   /*pbc*/,
    IMoniker*   /*pmkToLeft*/,
    FILETIME*   /*pFileTime*/)
{
    return MK_E_UNAVAILABLE;
}

STDMETHODIMP CComMonikerBase::ParseDisplayName(
    IBindCtx*   pbc,
    LPOLESTR    pszDisplayName,
    ULONG*      pchEaten,
    IMoniker**  ppmkOut)
{
    return ParseDisplayName(pbc, 0, pszDisplayName, pchEaten, ppmkOut);
}

STDMETHODIMP CComMonikerBase::IsSystemMoniker(
    DWORD*  pdwMksys)
{
    *pdwMksys = MKSYS_NONE;
    return S_FALSE;
}

// IROTData
STDMETHODIMP CComMonikerBase::GetComparisonData(
    byte*   pbData,
    ULONG   cbMax,
    ULONG*  pcbData)
{
    HRESULT hr = S_OK;
    if( !pbData ) return E_POINTER; *pbData = 0;
    if( !pcbData ) return E_POINTER; *pcbData = 0;
    if( !m_pwszDisplayName ) return E_UNEXPECTED;

    ULONG&  cbData = *pcbData;
    cbData = wcslen(m_pwszDisplayName);
    if( cbData > cbMax ) cbData = cbMax; 
    memcpy(pbData, m_pwszDisplayName, cbData);

    return hr;
}

bool CComMonikerBase::MatchesProgID(
    const wchar_t*  pwszDisplayName,
    const wchar_t** ppwszDisplayParam)
{
    int nColon = 0;

    if( (nColon = wcslen(ProgID()))&&
        (memicmp(pwszDisplayName, ProgID(), nColon) == 0) &&
        (pwszDisplayName[nColon] == ':') )
    {
        // Fall through
    }
    else if( (nColon = wcslen(VersionIndependentProgID())) &&
             (memicmp(pwszDisplayName, VersionIndependentProgID(), nColon) == 0) &&
             (pwszDisplayName[nColon] == ':') )
    {
        // Fall through
    }
    else
    {
        return false;
    }

    if( ppwszDisplayParam )
    {
        *ppwszDisplayParam = pwszDisplayName + nColon + 1;
    }

    return true;
}

