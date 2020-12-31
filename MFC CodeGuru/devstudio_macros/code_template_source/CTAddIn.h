/////////////////////////////////////////////////////////////////////////////
//
//                           Public Domain.
//
/////////////////////////////////////////////////////////////////////////////
//
//
//  File     :   CTAddIn.h
//
//  Author   :   Darren Richards (darrenr@gissing-consulting.co.uk)
//
//  Date     :   20th March 98
//
//  Synopsis :   Declaration of CTAddIn object - where it all happens.
//
////////////////

#ifndef CTADDIN_H
#define CTADDIN_H

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

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
//
//  struct TemplateData/VecTemplateData - storage for our code templates
//
///////////////

struct TemplateData
{
    string strName;
    string strText;
};

bool operator==(TemplateData t1, TemplateData t2);
bool operator<(TemplateData t1, TemplateData t2);

typedef vector<TemplateData>      VecTemplateData;
typedef VecTemplateData::iterator VecTemplateDataIter;

/////////////////////////////////////////////////////////////////////////////
//
//  struct TemplateData/VecTemplateData - storage for our code templates
//
///////////////

class ATL_NO_VTABLE CCTAddIn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCTAddIn, &CLSID_CTAddIn>,
	public IDSAddIn,
	public IDispatchImpl<ICTAddIn, &IID_ICTAddIn, &LIBID_CODETMPLLib>
{
public:
	CCTAddIn()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CTADDIN)

BEGIN_COM_MAP(CCTAddIn)
	COM_INTERFACE_ENTRY(ICTAddIn)
	COM_INTERFACE_ENTRY2(IDispatch, ICTAddIn)
	COM_INTERFACE_ENTRY(IDSAddIn)
END_COM_MAP()

    CComPtr<IApplication> m_spApplication;
	DWORD m_dwAddInID;

// IDSAddIn methods
public:
	STDMETHOD(OnConnection)(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwCookie, VARIANT_BOOL* bOnConnection);
	STDMETHOD(OnDisconnection)(VARIANT_BOOL bLastTime);

// ICTAddIn
public:
	STDMETHOD(CTInsCodeTmpl)();

private:
    void ReadTmplFile();
    VecTemplateData m_vecTemplateData;
};

#endif // CTADDIN_H_
