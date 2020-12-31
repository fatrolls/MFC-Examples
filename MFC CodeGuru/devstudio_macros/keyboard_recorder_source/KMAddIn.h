/////////////////////////////////////////////////////////////////////////////
//
//                           Public Domain.
//
/////////////////////////////////////////////////////////////////////////////
//
//
//  File     :   KMAddIn.h
//
//  Author   :   Darren Richards
//
//  Date     :   25th February 98
//
//  Synopsis :   Declaration of KMAddIn object - where it all happens.
//
////////////////

#ifndef __KMADDIN_H_
#define __KMADDIN_H_

/////////////////////////////////////////////////////////////////////////////
//
//  includes
//
///////////////

#include "resource.h"       // main symbols
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>

/////////////////////////////////////////////////////////////////////////////
//
//  class CKMAddIn
//
///////////////

class ATL_NO_VTABLE CKMAddIn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CKMAddIn, &CLSID_KMAddIn>,
	public IDSAddIn,
	public IDispatchImpl<IKMAddIn, &IID_IKMAddIn, &LIBID_KBDMACLib>
{
public:
	CKMAddIn()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_KMADDIN)

BEGIN_COM_MAP(CKMAddIn)
	COM_INTERFACE_ENTRY(IKMAddIn)
	COM_INTERFACE_ENTRY2(IDispatch, IKMAddIn)
	COM_INTERFACE_ENTRY(IDSAddIn)
END_COM_MAP()

	CComPtr<IApplication> m_spApplication;
	DWORD m_dwAddInID;

// IDSAddIn methods
public:
	STDMETHOD(OnConnection)(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwCookie, VARIANT_BOOL* bOnConnection);
	STDMETHOD(OnDisconnection)(VARIANT_BOOL bLastTime);

// IKMAddIn
public:
	STDMETHOD(KMRecord)();
	STDMETHOD(KMStop)();
	STDMETHOD(KMPlay)();

private:

};

#endif //__KMADDIN_H_
