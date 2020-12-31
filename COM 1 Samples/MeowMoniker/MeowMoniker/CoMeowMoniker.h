// CoMeowMoniker.h : Declaration of the CoMeowMoniker

#ifndef __MEOWMONIKER_H_
#define __MEOWMONIKER_H_

#include "resource.h"       // main symbols
#include <mkbase.h>

/////////////////////////////////////////////////////////////////////////////
// CoMeowMoniker

class ATL_NO_VTABLE CoMeowMoniker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CoMeowMoniker, &CLSID_CoMeowMoniker>,
	public CComMoniker<&CLSID_CoMeowMoniker>
{
public:
    CoMeowMoniker() : m_pszItf(0)
	{
	}

    virtual ~CoMeowMoniker()
	{
        delete[] const_cast<char*>(m_pszItf);
	}

    HRESULT MarshalInterface(IUnknown* punk, REFIID riid, DWORD dwDestContext, DWORD mshlflags);
    HRESULT UnmarshalInterface(REFIID riid, void** ppv);

DECLARE_REGISTRY_RESOURCEID(IDR_MEOWMONIKER)
DECLARE_NOT_AGGREGATABLE(CoMeowMoniker)

BEGIN_COM_MAP(CoMeowMoniker)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IPersistStream)
	COM_INTERFACE_ENTRY(IMoniker)
	COM_INTERFACE_ENTRY(IParseDisplayName)
	COM_INTERFACE_ENTRY(IROTData)
	COM_INTERFACE_ENTRY(IMarshal)
END_COM_MAP()

    // IMoniker to implement
    STDMETHODIMP BindToObject(IBindCtx *pbc, IMoniker *pmkToLeft,
                              REFIID riidResult, void **ppvResult);

	STDMETHODIMP GetDisplayName(IBindCtx *pbc, IMoniker *pmkToLeft,
                                LPOLESTR *ppszDisplayName);

	STDMETHODIMP ParseDisplayName(IBindCtx *pbc, IMoniker *pmkToLeft,
                                  LPOLESTR pszDisplayName, ULONG *pchEaten,
                                  IMoniker **ppmkOut);

protected:
    const wchar_t* ProgID() { return L"dm.meow.1"; }
    const wchar_t* VersionIndependentProgID() { return L"dm.meow"; }

private:
    // No reason for this the be Unicode as it will
    // only hold Base64 encoded characters, i.e. ANSI by definition
    const char* m_pszItf;
};

#endif //__MEOWMONIKER_H_
