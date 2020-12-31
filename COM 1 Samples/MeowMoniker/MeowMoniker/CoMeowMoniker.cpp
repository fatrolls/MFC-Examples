// CoMeowMoniker.cpp : Implementation of CoMeowMoniker

#include "stdafx.h"
#include "..\yacl\include\hrx.h"
#include <assert.h>
#include "..\yacl\include\ustring.h"
#include "..\yacl\include\ustring.cpp"

#include "MeowMoniker.h"
#include "CoMeowMoniker.h"
#include "Base64.h"
#include <mkbase.cpp>

/////////////////////////////////////////////////////////////////////////////
// CoMeowMoniker

#define BAD_POINTER_RETURN(p) if( !p ) return E_POINTER
#define BAD_POINTER_RETURN_OR_ZERO(p) if( !p ) return E_POINTER; else *p = 0

// Marshal interface into m_pszItf
HRESULT CoMeowMoniker::MarshalInterface(
    IUnknown*   punk,
    REFIID      riid,
    DWORD       dwDestContext,
    DWORD       mshlflags)
{
    COM_TRY
    {
        HRX   hrx;
        if( m_pszItf ) hrx = E_UNEXPECTED;

        // Marshal the interface into a stream
        SI(IStream) pstm;
        hrx = CreateStreamOnHGlobal(0, TRUE, pstm.RelItfRef());
        hrx = CoMarshalInterface(pstm.Itf(), riid, punk, dwDestContext, 0, mshlflags);

        // Treat the marshalled interface as an array of bytes
        HGLOBAL hg;
        hrx = GetHGlobalFromStream(pstm.Itf(), &hg);

        BYTE*   rgbRaw = (BYTE*)GlobalLock(hg);
        if( !rgbRaw ) hrx = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WINDOWS, GetLastError());

        // Allocate enough memory for encoded string
        ULONG   nRawSize = GlobalSize(hg);
        size_t  nEncodedLen = (nRawSize + 2)/3 * 4; // Round up
        m_pszItf = new char[nEncodedLen + 1];
        if( !m_pszItf ) hrx = E_OUTOFMEMORY;

        // Base64 encode raw data into a string
        hrx = BufferEncode64(const_cast<char*>(m_pszItf), nEncodedLen, rgbRaw, nRawSize);

        // NULL-terminate for convenience
        const_cast<char*>(m_pszItf)[nEncodedLen] = 0;
    }
    COM_CATCH;
}

// Unmarshal interface from m_pszItf
HRESULT CoMeowMoniker::UnmarshalInterface(
    REFIID  riid,
    void**  ppv)
{
    COM_TRY
    {
        HRX   hrx;

        if( !m_pszItf ) hrx = E_UNEXPECTED;

        // Allocate memory for decoded itf
        size_t  nEncodedLen = strlen(m_pszItf);
        assert(nEncodedLen && (nEncodedLen%4 == 0));

        size_t  nRawSize = nEncodedLen/4 * 3;
        HGLOBAL hg = GlobalAlloc(GPTR, nRawSize);
        if( !hg ) hrx = E_OUTOFMEMORY;

        // Build a stream on the memory
        SI(IStream) pstm;
        hrx = CreateStreamOnHGlobal(hg, TRUE, pstm.RelItfRef());

        // Base64 decode from string into raw memory
        BYTE*   rgbRaw = (BYTE*)GlobalLock(hg);
        if( !rgbRaw ) hrx = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WINDOWS, GetLastError());

        hrx = BufferDecode64(rgbRaw, &nRawSize, m_pszItf, nEncodedLen);

        // Unmarshal the interface pointer from the stream
        hrx = CoUnmarshalInterface(pstm.Itf(), riid, ppv);
    }
    COM_CATCH;
}

STDMETHODIMP CoMeowMoniker::BindToObject(
    IBindCtx*   pbc,
    IMoniker*   pmkToLeft,
    REFIID      riidResult,
    void**      ppvResult)
{
    BAD_POINTER_RETURN_OR_ZERO(ppvResult);
    BAD_POINTER_RETURN(pbc);

    COM_TRY
    {
        HRX   hrx;
        if( pmkToLeft ) hrx = E_UNEXPECTED;
        hrx = UnmarshalInterface(riidResult, ppvResult); 
    }
    COM_CATCH;
}

STDMETHODIMP CoMeowMoniker::GetDisplayName(
    IBindCtx*   pbc,
    IMoniker*   pmkToLeft,
    LPOLESTR*   ppwszDisplayName)
{
    BAD_POINTER_RETURN_OR_ZERO(ppwszDisplayName);
    BAD_POINTER_RETURN(pbc);

    COM_TRY
    {
        HRX   hrx;
        if( pmkToLeft ) hrx = E_UNEXPECTED;
        if( !m_pszItf ) hrx = E_UNEXPECTED;

        // Name Format: "dm.meow.1:<marshalled interface as base64 encoding>"
        size_t  cb = (wcslen(ProgID()) + 1 + strlen(m_pszItf) + 1) * sizeof(wchar_t);
        *ppwszDisplayName = (wchar_t*)CoTaskMemAlloc(cb);
        if( !*ppwszDisplayName ) hrx = E_OUTOFMEMORY;
        
        wcscpy(*ppwszDisplayName, ProgID());
        wcscat(*ppwszDisplayName, L":");
        mbstowcs(*ppwszDisplayName + wcslen(*ppwszDisplayName), m_pszItf, strlen(m_pszItf) + 1);
    }
    COM_CATCH;
}

STDMETHODIMP CoMeowMoniker::ParseDisplayName(
    IBindCtx*   pbc,
    IMoniker*   pmkToLeft,
    LPOLESTR    pwszDisplayName,
    ULONG*      pchEaten,
    IMoniker**  ppmkOut)
{
    BAD_POINTER_RETURN_OR_ZERO(ppmkOut);
    BAD_POINTER_RETURN_OR_ZERO(pchEaten);
    BAD_POINTER_RETURN(pbc);
    BAD_POINTER_RETURN(pwszDisplayName);
    BAD_POINTER_RETURN(pchEaten);

    COM_TRY
    {
        HRX   hrx;
        if( pmkToLeft ) hrx = E_UNEXPECTED;
        if( m_pszItf ) hrx = E_UNEXPECTED;

        const wchar_t*  pwszDisplayParam;
        if( CComMonikerBase::MatchesProgID(pwszDisplayName, &pwszDisplayParam) )
        {
            int cchItf = wcslen(pwszDisplayParam);
            m_pszItf = new char[cchItf + 1];
            if( !m_pszItf ) hrx = E_OUTOFMEMORY;

            wcstombs(const_cast<char*>(m_pszItf), pwszDisplayParam, cchItf + 1);
            *pchEaten = wcslen(pwszDisplayName);
            (*ppmkOut = this)->AddRef();
        }
    }
    COM_CATCH;
}

STDAPI CreateMeowMoniker(
    IUnknown*   punk,
    REFIID      riid,
    DWORD       dwDestContext,
    DWORD       mshlflags,
    IMoniker**  ppmk)
{
    BAD_POINTER_RETURN_OR_ZERO(ppmk);

    HRESULT         hr = E_OUTOFMEMORY;
    CoMeowMoniker*  pMeow = new CComObject<CoMeowMoniker>;
    if( pMeow )
    {
        // Just to do AddRef() and Release() so moniker object
        // is properly destroyed if it isn't handed out
        SI(IUnknown)    punkMeow = pMeow->GetUnknown();
        hr = pMeow->MarshalInterface(punk, riid, dwDestContext, mshlflags);
        if( SUCCEEDED(hr) )
        {
            (*ppmk = pMeow)->AddRef();
        }
    }

    return hr;
}
