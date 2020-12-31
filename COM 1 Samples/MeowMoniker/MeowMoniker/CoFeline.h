// CoFeline.h : Declaration of the CoFeline

#ifndef __FELINE_H_
#define __FELINE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CoFeline
class ATL_NO_VTABLE CoFeline : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CoFeline, &CLSID_CoFeline>,
	public ISupportErrorInfoImpl<&IID_DIFeline>,
	public IDispatchImpl<DIFeline, &IID_DIFeline, &LIBID_MEOWMONIKERLib>
{
public:

DECLARE_REGISTRY_RESOURCEID(IDR_FELINE)

BEGIN_COM_MAP(CoFeline)
	COM_INTERFACE_ENTRY(DIFeline)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// DIFeline
public:
	STDMETHOD(GetDisplayName)(/*[in]*/ IDispatch* pdisp, /*[out, retval]*/ BSTR* pbstrName);
	STDMETHOD(ParseDisplayName)(/*[in]*/ BSTR bstrName, /*[out, retval]*/ IDispatch** ppdisp);
};

#endif //__FELINE_H_
