// Test.h : Declaration of the CTest

/////////////////////////////////////////////////////////////
// Test object to demonstrate the use of displaying an
// MFC property page from ATL.
// This file is only used to show the property page in action
/////////////////////////////////////////////////////////////


#ifndef __TEST_H_
#define __TEST_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest
class ATL_NO_VTABLE CTest : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTest, &CLSID_Test>,
	public IDispatchImpl<ITest, &IID_ITest, &LIBID_ATLMFCLib>,
	public ISpecifyPropertyPages	// Added for property pages
{
public:
	CTest()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TEST)

BEGIN_COM_MAP(CTest)
	COM_INTERFACE_ENTRY(ITest)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)	// Added for property pages
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// Added for property pages
///////////////////////////////////
//ISpecifyPropertyPages
public:
	STDMETHOD(GetPages)(CAUUID *pPages)
	{
		_ASSERTE(pPages);
		if (!pPages)
			return E_POINTER;
		pPages->cElems=1;
		pPages->pElems= (LPGUID) CoTaskMemAlloc( pPages->cElems * sizeof(GUID));
		if (!pPages->pElems)
			return E_POINTER;
		pPages->pElems[0]=CLSID_PpgTest;
		return NOERROR;
	}
//ISpecifyPropertyPages
///////////////////////////////////

// ITest
public:
};

#endif //__TEST_H_
