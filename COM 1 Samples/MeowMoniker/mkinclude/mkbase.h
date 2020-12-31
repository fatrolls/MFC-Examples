/////////////////////////////////////////////////////////////////////////////
// mkbase.h: CComMoniker declaration
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1997, Tim Ewald, Chris Sells and Don Box.
// All rights reserved.
//
// The following is a prototype of a moniker base class.
// NO WARRANTIES ARE EXTENDED. USE AT YOUR OWN RISK.
//
// To contact the authors with suggestions or comments, use
// tewald@obelisk-llc.com,
// csells@sellsbrothers.com and
// dbox@develop.com.

#ifndef __COMMONIKER_H__
#define __COMMONIKER_H__

/////////////////////////////////////////////////////////////////////////////
// CComMonikerBase

// CComMonikerRootBase implements the reduction
// and composition methods in the "default" way,
// that is, it assumes you do nothing special
// in terms of composition or reduction

class CComMonikerRootBase : public IMoniker
{
public:
    // IMoniker
	STDMETHODIMP Reduce(IBindCtx *pbc, DWORD dwReduceHowFar,
                        IMoniker **ppmkToLeft, IMoniker **ppmkReduced);
	STDMETHODIMP ComposeWith(IMoniker *pmkRight, BOOL fOnlyIfNotGeneric,
                             IMoniker **ppmkComposite);
    STDMETHODIMP Inverse(IMoniker **ppmk);
	STDMETHODIMP CommonPrefixWith(IMoniker *pmkOther, IMoniker **ppmkPrefix);
	STDMETHODIMP RelativePathTo(IMoniker *pmkOther, IMoniker **ppmkRelPath);
};

class CComMonikerBase :
	public CComMonikerRootBase,
    public IParseDisplayName,
	public IROTData,
	public IMarshal
{
public:
    CComMonikerBase();
    virtual ~CComMonikerBase();

    // IUnknown (so we don't have to depend on ATL)
    STDMETHODIMP QueryInterface(REFIID riid, void** ppv) =0;

    // IPersist (implemented in CComMoniker)
	STDMETHODIMP GetClassID(CLSID *pClassID) =0;

    // IPersistStream
	STDMETHODIMP IsDirty();
    STDMETHODIMP Load(IStream *pStm);
	STDMETHODIMP Save(IStream *pStm, BOOL fClearDirty);
	STDMETHODIMP GetSizeMax(ULARGE_INTEGER *pcbSize);

    // IMarshal
	STDMETHODIMP GetUnmarshalClass(REFIID riid, void *pv, DWORD dwDestContext,
                                   void *pvDestContext, DWORD mshlflags, CLSID *pCid);
	STDMETHODIMP GetMarshalSizeMax(REFIID riid, void *pv, DWORD dwDestContext,
                                   void *pvDestContext, DWORD mshlflags, DWORD *pSize);
	STDMETHODIMP MarshalInterface(IStream *pStm, REFIID riid, void *pv, DWORD dwDestContext,
                                  void *pvDestContext, DWORD mshlflags);

	STDMETHODIMP UnmarshalInterface(IStream *pStm, REFIID riid, void **ppv);
	STDMETHODIMP ReleaseMarshalData(IStream *pStm);
	STDMETHODIMP DisconnectObject(DWORD dwReserved);

    // IParseDisplayName    
    STDMETHODIMP ParseDisplayName(IBindCtx *pbc, LPOLESTR pszDisplayName,
                                  ULONG *pchEaten, IMoniker **ppmkOut);

    // IROTData
	STDMETHODIMP GetComparisonData(byte* pbData, ULONG cbMax, ULONG *pcbData);

    // IMoniker
	STDMETHODIMP BindToStorage(IBindCtx *pbc, IMoniker *pmkToLeft,
                               REFIID riid, void **ppvObj);

	STDMETHODIMP Enum(BOOL fForward, IEnumMoniker **ppenumMoniker);
	STDMETHODIMP IsEqual(IMoniker *pmkOtherMoniker);
	STDMETHODIMP Hash(DWORD *pdwHash);

	STDMETHODIMP IsRunning(IBindCtx *pbc, IMoniker *pmkToLeft, IMoniker *pmkNewlyRunning);
	STDMETHODIMP GetTimeOfLastChange(IBindCtx *pbc, IMoniker *pmkToLeft, FILETIME *pFileTime);
	STDMETHODIMP IsSystemMoniker(DWORD *pdwMksys);

    // YOU MUST IMPLEMENT!
    STDMETHODIMP BindToObject(IBindCtx *pbc, IMoniker *pmkToLeft,
                              REFIID riidResult, void **ppvResult) =0;

	STDMETHODIMP GetDisplayName(IBindCtx *pbc, IMoniker *pmkToLeft,
                                LPOLESTR *ppszDisplayName) =0;

	STDMETHODIMP ParseDisplayName(IBindCtx *pbc, IMoniker *pmkToLeft,
                                  LPOLESTR pszDisplayName, ULONG *pchEaten,
                                  IMoniker **ppmkOut) =0;

protected:
    // Display Name Helpers
    virtual const wchar_t* ProgID() =0;
    virtual const wchar_t* VersionIndependentProgID() =0;
    
    // Match "ProgID:" or "VersionIndependentProgID:"
    // and return pointer one character past ":" in *ppwszDisplayParam
    bool MatchesProgID(const wchar_t* pwszDisplayName, const wchar_t** ppwszDisplayParam);

private:
    const OLECHAR*  m_pwszDisplayName;

    HRESULT CacheDisplayName();
};

template <const CLSID* pclsid>
class CComMoniker : public CComMonikerBase
{
public:
	STDMETHODIMP GetClassID(CLSID *pClassID)
    {
        if( !pClassID ) return E_POINTER;
        *pClassID = *pclsid;
        return S_OK;
    }
};

// Inline Implementations
inline
CComMonikerBase::CComMonikerBase()
    : m_pwszDisplayName(0)
{}

inline
CComMonikerBase::~CComMonikerBase()
{ CoTaskMemFree(const_cast<OLECHAR*>(m_pwszDisplayName)); }


#endif //__COMMONIKER_H__
