#include <new.h>
#include <algorithm>
#include <xmemory>
#include <list>

#include <assert.h>
#define ASSERT assert

#include "CUnknown.h"
#include "CFactory.h"

#include "GdiWorld.h"
#include "GdiVisl.h"

// Files with CLSID references
#include "World_C.h"

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
   {&CLSID_TangramGdiWorld,  
		CGdiWorld::CreateInstance, 
		"TangramGdiWorld Component",	// Friendly Name
		"TangramGdiWorld.1",			// ProgID
		"TangramGdiWorld",				// Version Independent ProgID
		CGdiWorld::SpecialReg,			// Function to register component categories
		NULL,	0},
	{&CLSID_TangramGdiVisual,  
		CTangramGdiVisual::CreateInstance, 
		"TangramGdiVisual Component",	// Friendly Name
		"TangramGdiVisual.1",			// ProgID
		"TangramGdiVisual",				// Version Independent ProgID
		NULL,							// No special registration
		NULL,	0}
 };
int g_cFactoryDataEntries = sizeof(g_FactoryDataArray) / sizeof(CFactoryData) ;


