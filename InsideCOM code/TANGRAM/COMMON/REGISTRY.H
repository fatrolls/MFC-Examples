#ifndef __Registry_H__
#define __Registry_H__
////////////////////////////////////////////////////////
//
//
// Registry.h -	Helper functions registering and unregistering
//				a component.
//
////////////////////////////////////////////////////////
//
// Constants
//

// Size of a CLSID as a string
const int CLSID_STRING_SIZE = 39 ;

////////////////////////////////////////////////////////
//
// Function Prototypes
//

// This function will register a component in the Registry.
// The component calls this function from its DllRegisterServer function.
HRESULT RegisterServer(	HMODULE hModule, 
						const CLSID& clsid, 
						const char*  szFriendlyName,
						const char*  szVerIndProgID,
						const char*  szProgID);

// This function will unregister a component. Components
// call this function from their DllUnregisterServer function.
HRESULT UnregisterServer(	const CLSID& clsid,
							const char* szVerIndProgID,
							const char* szProgID);

// Converts a CLSID into a char string.
void CLSIDtochar(	const CLSID& clsid, 
					char* szCLSID,
					int length)	;
#endif