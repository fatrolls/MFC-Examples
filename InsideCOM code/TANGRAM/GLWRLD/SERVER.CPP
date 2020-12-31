// Windows
#include <windows.h>
// STL
#include <new.h>
#include <algorithm>
#include <xmemory>
#include <list>

// Utilities
#include "Util.h"

// Base classes
#include "CUnknown.h"
#include "CFactory.h"

// Support classes
#include "CGL.h"

// Components.
#include "GLWorld.h"
#include "GLVisl.h"

// Files with CLSID references
#include "GLWrld_C.h"

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
   {&CLSID_TangramGLWorld,  
		CGLWorld::CreateInstance, 
		"TangramGLWorld Component",		// Friendly Name
		"TangramGLWorld.1",				// ProgID
		"TangramGLWorld",				// Version Independent ProgID
		CGLWorld::SpecialReg,			// Function to register component categories
		NULL,	0},
   {&CLSID_TangramGLVisual,  
		CTangramGLVisual::CreateInstance, 
		"TangramGLVisual Component",	// Friendly Name
		"TangramGLVisual.1",			// ProgID
		"TangramGLVisual",				// Version Independent ProgID
		NULL,							// No special registration
		NULL,	0}
 };
int g_cFactoryDataEntries = sizeof(g_FactoryDataArray) / sizeof(CFactoryData) ;


