	
// Rect.h : Declaration of the CRect

#ifndef __RECT_H_
#define __RECT_H_

#include "resource.h"       // main symbols
#include "giplip.h"
/////////////////////////////////////////////////////////////////////////////
// CRect
class ATL_NO_VTABLE CRect : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRect, &CLSID_Rect>,
	public IRect
{
public:
    CRect() 
	{
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RECT)
DECLARE_NOT_AGGREGATABLE(CRect)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CRect)
	COM_INTERFACE_ENTRY(IRect)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

	HRESULT FinalConstruct()
	{
        IPoint *pPoint = 0;
        HRESULT hr = CoCreateInstance(CLSID_Point, 0, CLSCTX_ALL,
                                  IID_IPoint, (void**)&pPoint);
        if (SUCCEEDED(hr))
        {
            hr = m_gipTopLeft.Globalize(pPoint);
            pPoint->Release();
        }
        if (FAILED(hr))
            return hr;
        hr = CoCreateInstance(CLSID_Point, 0, CLSCTX_ALL,
                                  IID_IPoint, (void**)&pPoint);
        if (SUCCEEDED(hr))
        {
            hr = m_gipBottomRight.Globalize(pPoint);
            pPoint->Release();
        }
        if (SUCCEEDED(hr))
            hr = CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p);
        return hr;
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

// IRect
public:
	STDMETHOD(get_Volume)(/*[out, retval]*/ long *pVal);
	STDMETHOD(SetCoords)(/*[in]*/ long left, /*[in]*/ long top, /*[in]*/ long right, /*[in]*/ long bottom);
private:
	GIP(IPoint) m_gipTopLeft;
	GIP(IPoint) m_gipBottomRight;
};

#endif //__RECT_H_
