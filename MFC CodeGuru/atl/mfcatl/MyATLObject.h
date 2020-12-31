#ifndef __MYATLOBJECT_H_
#define __MYATLOBJECT_H_

#include "resource.h"       // main symbols

/*
// {C107FF50-5F0F-11d1-934C-E4CFDA000000}
DEFINE_GUID(CLSID_MyATLObject, 
0xc107ff50, 0x5f0f, 0x11d1, 0x93, 0x4c, 0xe4, 0xcf, 0xda, 0x0, 0x0, 0x0);

// {C107FF51-5F0F-11d1-934C-E4CFDA000000}
DEFINE_GUID(IID_IMyATLObject, 
0xc107ff51, 0x5f0f, 0x11d1, 0x93, 0x4c, 0xe4, 0xcf, 0xda, 0x0, 0x0, 0x0);
*/
/////////////////////////////////////////////////////////////////////////////
// CMyATLObject
class ATL_NO_VTABLE CMyATLObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyATLObject, &CLSID_MyATLObject>,
	public IDispatchImpl<IMyATLObject, &IID_IMyATLObject, &LIBID_MFCATL_OCXLib>
{
public:
	CMyATLObject()
	{
      ::MessageBox(NULL,"ctor CMyATLObject","MFCATL",MB_OK);
   }

DECLARE_REGISTRY_RESOURCEID(IDR_MYATLOBJECT)

BEGIN_COM_MAP(CMyATLObject)
	COM_INTERFACE_ENTRY(IMyATLObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMyATLObject
public:
};

#endif //__MYATLOBJECT_H_
