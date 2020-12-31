//
// Category.cpp -
//   Component category demonstration program
//

// This program is not designed to be compiled for UNICODE.

#include <stdlib.h>
#include <iostream.h>
#include <assert.h>

#include <comcat.h>

/////////////////////////////////////////////////
//
// Function declarations
//

// Worker functions

// List the registered component categories.
BOOL ListCategories() ;

// Register our sample component category.
BOOL RegisterCategory() ;

// Unregister our sample component category.
void UnregisterCategory() ;

// Add component to our sample component category.
void AddComponent() ;

// Remove component from our sample component category.
void RemoveComponent() ;

// List all of the components which are members of our sample category.
void ListCategoryMembers() ;

// Helper functions

// Print out the COM/OLE error string for an HRESULT.
void ErrorMessage(const char* str, HRESULT hr) ;

// Get friendly name for a CLSID from the Registry and display.
void OutputFriendlyName(const CLSID& clsid) ;

/////////////////////////////////////////////////
//
// Global Data and constants
//

// Global interface pointers
ICatInformation*  g_pICatInformation = NULL ;
ICatRegister*     g_pICatRegister = NULL ;

// Array of category IDs
// {f2484d60-e8d0-11cf-a6bb-0080c7b2d682}
static GUID CATID_SampleCategories[1] = 
	{0xf2484d60, 0xe8d0, 0x11cf,
	{0xa6, 0xbb, 0x0, 0x80, 0xc7, 0xb2, 0xd6, 0x82}} ;

// Category Information structure used to register categories
CATEGORYINFO g_SampleCategoryInfo =
{    
	{0xf2484d60, 0xe8d0, 0x11cf,
		{0xa6, 0xbb, 0x0, 0x80, 0xc7, 0xb2, 0xd6, 0x82}},  // CATID catid ;
	LOCALE_SYSTEM_DEFAULT,                       // LCID lcid ;
	L"This is the sample category"               // OLECHAR szDescription[128] ;
} ;

// Component to add to the sample category defined above
// {0c092c20-882c-11cf-a6bb-0080c7b2d682}
extern "C" const CLSID CLSID_Component1 =
	{0x0c092c20, 0x882c, 0x11cf,
	{0xa6, 0xbb, 0x0, 0x80, 0xc7, 0xb2, 0xd6, 0x82}} ;

/////////////////////////////////////////////////
//
// main 
//
int main()
{
	// Initialize COM Library.
	OleInitialize(NULL) ;

	// Create the standard COM Category manager.
	HRESULT hr = ::CoCreateInstance(CLSID_StdComponentCategoriesMgr,
	                                NULL, 
	                                CLSCTX_ALL,
	                                IID_ICatInformation, 
	                                (void**)&g_pICatInformation) ;
	if (FAILED(hr))
	{
		ErrorMessage("main: Could not create component category manager.", hr) ;
		goto Uninitialize ;
	}

	// List the categories.
	if (!ListCategories())
	{
		goto Release ;
	}

	// Get the Category Registration interface.
	hr = g_pICatInformation->QueryInterface(IID_ICatRegister,
	                                        (void**)&g_pICatRegister) ;
	if (FAILED(hr))
	{
		ErrorMessage("Attempt to query for ICatRegister failed.", hr) ;
		goto Release ;
	}
	
	//
	// Register our sample component category.
	//
	cout << "--------Register---------------" << endl ;
	if (!RegisterCategory())
	{
		goto Release ;
	}

	// List the categories again to show the newly registered category.
	ListCategories() ;
	
	// Add component to our sample category.
	cout << "--------Add Component----------" << endl ;
	AddComponent() ;

	// List all components implementing our sample category.
	cout << "--------List Category----------" << endl ;
	ListCategoryMembers();	

	// Remove class from our sample category.
	cout << "--------Remove Component-------" << endl ;
	RemoveComponent();

	// List all components implementing our sample category. 
	// Should be empty.
	cout << "--------List Category----------" << endl ;
	ListCategoryMembers() ;	

	// Unregister our sample component category.
	cout << "--------Unregister-------------" << endl ;
	UnregisterCategory() ;

	// List the categories to show that the component category
	// has been removed.
	ListCategories() ;

Release:	
	// Release the interface pointers.
	if (g_pICatInformation != NULL)
	{
		g_pICatInformation->Release() ;
	}
	if (g_pICatRegister != NULL)
	{
		g_pICatRegister->Release() ;
	}

Uninitialize:
	// Unintialize COM Library
	OleUninitialize() ;

	return 0 ;
}

/////////////////////////////////////////////////
//
// Worker functions
//

//
// List the registered component categories.
//
BOOL ListCategories()
{
	BOOL bReturn = TRUE ;

	// Get an enumerator for the categories.
	IEnumCATEGORYINFO* pIEnumCATEGORYINFO = NULL ; 
	HRESULT hr = g_pICatInformation->EnumCategories(::GetUserDefaultLCID(),
	                                                &pIEnumCATEGORYINFO) ;
	if (FAILED(hr))
	{
		ErrorMessage("ListCategories: ICatInformation::EnumCategories failed.", hr) ;
		return FALSE ;
	}

	// Prepare for loop.
	char szDescription[128] ;
	CATEGORYINFO CategoryInfo ;

	// Enumerate the categories.
	while ((hr = pIEnumCATEGORYINFO->Next(1, &CategoryInfo, NULL)) == S_OK)
	{
			// Convert from wchar_t to char.
			::wcstombs(szDescription, CategoryInfo.szDescription,
			           sizeof(szDescription)) ;

			// Print out description.
			cout << szDescription << "\r\n" ;
	} 

	// Did Next fail or finish?
	if (FAILED(hr))
	{
		ErrorMessage("ListCategories: IEnumCATEGORYINFO::Next failed.", hr) ;
		bReturn = FALSE ;
	}


	// Release Interfaces.
	if (pIEnumCATEGORYINFO != NULL)
	{
		pIEnumCATEGORYINFO->Release() ;
	}

	return bReturn ;
}

//
// Register the component category.
//
BOOL RegisterCategory()
{
	HRESULT hr = g_pICatRegister->RegisterCategories(1, &g_SampleCategoryInfo) ;
	if (FAILED(hr))
	{
		ErrorMessage("RegisterCategory: Registering the component category failed.",
		             hr) ;
		return FALSE ;
	}
	return TRUE ;
}

//
// Unregister the component category.
//
void UnregisterCategory()
{
	HRESULT hr = g_pICatRegister->UnRegisterCategories(1, CATID_SampleCategories) ; 
	if (FAILED(hr))
	{
		ErrorMessage("UnregisterCategory: Unregistering component category failed.",
		             hr) ;
	}
}

//
// Add component to component category.
//
void AddComponent()
{	
	HRESULT hr = g_pICatRegister->RegisterClassImplCategories(CLSID_Component1,
	                                                          1, 
	                                                          CATID_SampleCategories) ; 
	if (FAILED(hr))
	{
		ErrorMessage("AddComponent: Adding component to category failed.", hr) ;
	}
}

//
// Remove component from component category.
//
void RemoveComponent()
{	
	HRESULT hr = 
		g_pICatRegister->UnRegisterClassImplCategories(CLSID_Component1,	
		                                               1, 
		                                               CATID_SampleCategories) ; 
	if (FAILED(hr))
	{
		 ErrorMessage("RemoveComponent: Removing component to category failed.",
		              hr) ;
	}
}

//
// List all of the components which are members of a particular category.
//
void ListCategoryMembers()
{
	// Get an enumerator for the categories.
	IEnumCLSID* pIEnumCLSID = NULL; 
	HRESULT hr 
		= g_pICatInformation->EnumClassesOfCategories(1,
		                                              CATID_SampleCategories,
		                                              0,
		                                              NULL,
		                                              &pIEnumCLSID) ;
	if (FAILED(hr))
	{
		ErrorMessage("ListCategoryMembers: EnumClassesOfCategories  failed.", hr) ;
	}

	// Prepare for loop.
	char szDescription[128] ;
	CLSID clsid ;

	// Enumerate the categories.
	while (TRUE)	
	{

		// Get the next category.
		hr = pIEnumCLSID->Next(	1, &clsid, NULL) ;
		if (hr != S_OK)
		{
			// Did Next fail or finish?
			if (FAILED(hr))
			{
				ErrorMessage("ListCategoryMembers: IEnumCLSID::Next failed.",
				             hr) ;
			}
			break ;
		}

		// Print the friendly name.
		OutputFriendlyName(clsid) ;
	} 

	// Release interfaces.
	if (pIEnumCLSID != NULL)
	{
		pIEnumCLSID->Release() ;
	}
}


/////////////////////////////////////////////////
//
// Helper function declarations
//

//
// Print out the COM/OLE error string for an HRESULT.
//
void ErrorMessage(const char* str, HRESULT hr)

{
	void* pMsgBuf ;
 
	::FormatMessage( 
		 FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		 NULL,
		 hr,
		 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		 (LPTSTR) &pMsgBuf,
		 0,
		 NULL 
	) ;

	// Display the string.
	cout << str << "\r\n" ;
	cout << "Error (" << hex << hr << "):  " 
	     << (char*)pMsgBuf << endl ;

	// Free the buffer.
	LocalFree( pMsgBuf ) ;

}

//
// Get friendly name for a CLSID from the Registry and display.
//
void OutputFriendlyName(const CLSID& clsid)
{
	// Convert clsid to a string.
	wchar_t wszCLSID[80] ;
	int r = ::StringFromGUID2(clsid, wszCLSID, 80) ;
	assert(r != 0) ;

	// Convert to single byte char.
	char szCLSID[40] ;
	wcstombs(szCLSID, wszCLSID, 40) ;

	// Open the Registry key.
	HKEY key = NULL ;
	long l = ::RegOpenKeyEx(HKEY_CLASSES_ROOT,
	                        "CLSID",
	                        0,
	                        KEY_ALL_ACCESS,
	                        &key) ;
	assert(l == ERROR_SUCCESS) ;

	// Get the friendly name.
	char szFriendly[256] ;
	long size = sizeof(szFriendly) ;
	l = ::RegQueryValue(key,
	                    szCLSID,
	                    szFriendly,
	                    &size) ;
	assert(l == ERROR_SUCCESS) ;

	// Output the friendly name.
	cout << szFriendly << endl ;

	// Clean up.
	::RegCloseKey(key) ;
}
