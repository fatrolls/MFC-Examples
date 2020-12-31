//
// Create.cpp 
//
#include <iostream.h>
#include <unknwn.h>    // Declare IUnknown.

#include "Create.h"

typedef IUnknown* (*CREATEFUNCPTR)() ;

IUnknown* CallCreateInstance(char* name)
{
	// Load dynamic link library into process.
	HINSTANCE hComponent = ::LoadLibrary(name) ;
	if (hComponent == NULL)
	{
		cout << "CallCreateInstance:\tError: Cannot load component." << endl ;
		return NULL ;
	}

	// Get address for CreateInstance function.
	CREATEFUNCPTR CreateInstance 
		= (CREATEFUNCPTR)::GetProcAddress(hComponent, "CreateInstance") ;
	if (CreateInstance == NULL)
	{
		cout  << "CallCreateInstance:\tError: "
		      << "Cannot find CreateInstance function."
		      << endl ;
		return NULL ;
	}

	return CreateInstance() ;
}
