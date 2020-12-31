// Point.h : Declaration of the CPoint

#ifndef __POINT_H_
#define __POINT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPoint
class ATL_NO_VTABLE CPoint : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPoint, &CLSID_Point>,
	IPoint
{
public:
    CPoint() : m_x(0), m_y(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_POINT)
DECLARE_NOT_AGGREGATABLE(CPoint)

BEGIN_COM_MAP(CPoint)
	COM_INTERFACE_ENTRY(IPoint)
END_COM_MAP()

// IPoint
public:
	STDMETHOD(SetCoords)(/*[in]*/ long x, /*[in]*/ long y);
	STDMETHOD(GetCoords)(/*[out]*/ long *px, /*[out]*/ long *py);
private:
	long m_x;
	long m_y;
};

#endif //__POINT_H_
