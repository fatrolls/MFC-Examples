// This is a part of the Extraview ExtraClass C++ library.
// Copyright (C) 1997 Extraview Limited
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Extraview ExtraClass Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Extraview Class product.
//
//
// MfcAtlPropertyPage.h
// Template class that allows an MFC COlePropertyPage
// derived class to be used in an ATL server.
//
//




/*********************************************************





  Steps to use CMfcAtlPropertyPage

  0 - Once only
  ~~~~~~~~~
	Import the resource file MfcAtlPropertyPage.rgs into
	your project.
	Give the resource an ID of IDR_MFCATLPPG
	Ensure the correct path is given in the file view for
	MfcAtlPropertyPage.rgs and change if neccessary.


  1. Update your IDL/ODL file
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Add a coclass statement to your IDL/ODL file
	for the new property page and support the interface IUnknown

	Example
	-------
		[
			uuid(E948B670-153F-11d1-8F2D-000000000000),
			helpstring("MFC Property Page")
		]
		coclass PpgAnimal
		{
			interface IUnknown;
		};
		

  2. Create the property page class
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Create a property page resource and	COlePropertyPage
	derived class as normal	using the dialog editor and
	ClassWizard


  3. Create a new header file for the class definition
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Create an empty text file and add the following:
	a)	An include statement for MfcAtlPropertyPage.h
		or Extraview.h
	b)	An include statement for your COlePropertyPage
		derived class
	c)	A typedef statement for the CMfcAtlPropertyPage
		template class using your property page.
		This is required as the ATL OBJECT_ENTRY macro
		does not accept template class declarations

	Example
	-------
		// OlePpgAnimal.h - Declaration of COlePpgAnimal typedef

		#include "MfcAtlPropertyPage.h"

		// Definition of CPpgAnimal (COlePropertyPage derived) class
		#include "PpgAnimal.h"

		// typedef that stops OBJECT_ENTRY macro from crying
		typedef Extraview::CMfcAtlPropertyPage<&CLSID_PpgAnimal, CPpgAnimal> COlePpgAnimal;


   4. Update the server object map
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Open the main ATL server source file that contains
	the server object map. This file typically has the
	same name as your project, with the cpp extension.

	Add your new include file to the list of includes.
	Add your typedef class to the object map by
	inserting a new OBJECT_ENTRY macro entry.

	Example
	-------
		...
		<Many #include statements>
		...
		#include "OlePpgAnimal.h"
		CComModule _Module;
		BEGIN_OBJECT_MAP(ObjectMap)
			OBJECT_ENTRY(CLSID_PpgAnimal, COlePpgAnimal)

		...
		<More OBJECT_ENTRY macro entries>
		...
		END_OBJECT_MAP()


  ATL will now use your MFC COlePropertyPage derived class
  as though it were part of ATL.

---------------------------------------------------------

  Example using three property pages with the minimum of fuss
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  1. IDL update
  ~~~~~~~~~~~~~
		[
			uuid(E948B670-153F-11d1-8F2D-000000000000),
			helpstring("Arms Property Page")
		]
		coclass PpgArms
		{
			interface IUnknown;
		};
		[
			uuid(E948B670-153F-11d1-8F2D-000000000000),
			helpstring("Legs Property Page")
		]
		coclass PpgLegs
		{
			interface IUnknown;
		};
		[
			uuid(E948B670-153F-11d1-8F2D-000000000000),
			helpstring("Body Property Page")
		]
		coclass PpgBody
		{
			interface IUnknown;
		};

	2. dialog resource and class creation
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Usual way for all three classes.
	Assume classes are named CPpgArms, CPpgLegs, CPpgBody
	in PpgArms.h, PpgLegs.h and PpgBody.h respectively

	3. header file with typedefs
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// MFCPpg.h
		// One header file for all object
		#include "MfcAtlPropertyPage.h"
		#include "PpgArms.h"
		#include "PpgLegs.h"
		#include "PpgBody.h"

		typedef Extraview::CMfcAtlPropertyPage
			<&CLSID_PpgArms, CPpgArms> COlePpgArms;
		typedef Extraview::CMfcAtlPropertyPage
			<&CLSID_PpgLegs, CPpgLegs> COlePpgLegs;
		typedef Extraview::CMfcAtlPropertyPage
			<&CLSID_PpgBody, CPpgBody> COlePpgBody;

   4. Update the server object map
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Assume project is CoolControl so object
		// map is in CoolControl.cpp by default

		#include "MFCPpg.h"
		CComModule _Module;
		BEGIN_OBJECT_MAP(ObjectMap)
			OBJECT_ENTRY(CLSID_PpgArms, COlePpgArms)
			OBJECT_ENTRY(CLSID_PpgLegs, COlePpgLegs)
			OBJECT_ENTRY(CLSID_PpgBody, COlePpgBody)

		<More OBJECT_ENTRY macro entries>
		END_OBJECT_MAP()

  Done!

---------------------------------------------------------

*********************************************************/

#ifndef __MFCATLPROPERTYPAGE_H_
#define __MFCATLPROPERTYPAGE_H_

namespace Extraview {

#pragma warning(disable:4786)
/////////////////////////////////////////////////////////////////////////////
// CMfcAtlPropertyPage
template <const CLSID * TpClsid, class TCOlePropertyPageDerived>
class ATL_NO_VTABLE CMfcAtlPropertyPage : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMfcAtlPropertyPage<TpClsid, TCOlePropertyPageDerived>, TpClsid>,
	public IUnknown
{
public:
	CMfcAtlPropertyPage() :
	m_pUnkPpg(NULL)
	{
	}

static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
	{
		USES_CONVERSION;
		_ATL_REGMAP_ENTRY m_regmapEntries[2];
		OLECHAR ochBuffer[50];
		StringFromGUID2(*TpClsid, ochBuffer, 50);
		m_regmapEntries[0].szKey=L"CLSID";
		m_regmapEntries[0].szData=ochBuffer;

		m_regmapEntries[1].szKey=NULL;
		return _Module.UpdateRegistryFromResourceD(
			IDR_MFCATLPPG,
			bRegister,
			m_regmapEntries
			);
	}

BEGIN_COM_MAP(CMfcAtlPropertyPage)
	COM_INTERFACE_ENTRY(IUnknown)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IPropertyPage, m_pUnkPpg)
END_COM_MAP()

public:
	HRESULT FinalConstruct();
	void FinalRelease();
private:
	LPUNKNOWN m_pUnkPpg;
};


template <const CLSID * TpClsid, class TCOlePropertyPageDerived>
HRESULT CMfcAtlPropertyPage<TpClsid, TCOlePropertyPageDerived>::FinalConstruct()
{ AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	TCOlePropertyPageDerived *pPpg= new TCOlePropertyPageDerived;

	pPpg->EnableAutomation();
	pPpg->EnableAggregation();
	pPpg->m_pOuterUnknown=static_cast<LPUNKNOWN>(this);

	LPDISPATCH _pDispatch=pPpg->GetIDispatch(FALSE);
	m_pUnkPpg=reinterpret_cast<LPUNKNOWN>(&(pPpg->m_xInnerUnknown));

	return NOERROR;


}

template <const CLSID * TpClsid, class TCOlePropertyPageDerived>
void CMfcAtlPropertyPage<TpClsid, TCOlePropertyPageDerived>::FinalRelease()
{
	if (m_pUnkPpg)
		m_pUnkPpg->Release();

}

}	// namespace Extraview

#endif //__MFCATLPROPERTYPAGE_H_
