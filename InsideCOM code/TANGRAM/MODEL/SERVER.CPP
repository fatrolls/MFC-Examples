#include "CUnknown.h"
#include "CFactory.h"

#include "Model.h"

#include "Model_C.h" // For CLSIDs
//////////////////////////////////////////////////////////////////////////////////////
//
// Server.cpp
//
// This file represents the component server.
// The FactoryDataArray contains the components which 
// can be served.
//

// Each component derived from CUnknown defines a static function
// for creating the component with the following prototype. 
// HRESULT CreateInstance(IUnknown* pOuterUnknown, 
//                        CUnknown** ppNewComponent) ;
// This function is used to create the component.
//

//
// The following array contains the data used by CFactory
// to create components. Each element in the array contains
// the CLSID, pointer to create function, and the name
// of the component to place in the registry.
//
CFactoryData g_FactoryDataArray[] =
{
	{&CLSID_TangramModel,
		CTangramModel::CreateInstance,
		"TangramModel Component",		// Friendly Name
		"TangramModel.1",				//	ProgID
		"TangramModel",					// Version Independent ProgID
		NULL,							// No special registration
		NULL,	0}
 };
int g_cFactoryDataEntries = sizeof(g_FactoryDataArray) / sizeof(CFactoryData) ;


