// Test.cpp - WMI test program
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <initguid.h>
#include "..\sys\guids.h"

#define arraysize(p) (sizeof(p)/sizeof((p)[0]))

void ReportError(LPCTSTR fcn, DWORD code);
void ReportInfo(IWbemServices* services, LPCWSTR classname);

///////////////////////////////////////////////////////////////////////////////

int main(int argc, LPTSTR argv[])
	{							// main
	// Initialize COM and get a pointer to the WbemLocator interface. We must use
	// the DCOM flavor of services on a computer where DCOM is installed. WBEMTEST
	// loads ole32.dll and uses GetProcAddress to learn these addresses. This test
	// program simply assumes that it's running in a DCOM-enabled environment.

	HRESULT hr = CoInitializeEx(NULL, 0);
	if (!SUCCEEDED(hr))
		{						// can't initialize COM
		ReportError(_T("CoInitialize"), hr);
		return 1;
		}						// can't initialize COM

	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, 
		RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IMPERSONATE, 
		NULL, 0, 0);
	if (!SUCCEEDED(hr))
		{						// can't fix security
		ReportError(_T("CoInitializeSecurity"), hr);
		CoUninitialize();
		return 1;
		}						// can't fix security

	IWbemLocator* locator;
	hr = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (PVOID*) &locator);
	if (SUCCEEDED(hr))
		{						// found locator

		// Connect to the WMI server on this computer. Note that ConnectServer requires
		// us to allocate a system string for the namespace argument -- a constant causes
		// a crash in the WMI server.

		IWbemServices* services;
		BSTR pnamespace = SysAllocString(L"root\\WMI");
		hr = locator->ConnectServer(pnamespace, NULL, NULL, 0, 0, NULL, NULL, &services);
		SysFreeString(pnamespace);
		if (SUCCEEDED(hr))
			{					// found server

			// Set the interface security to allow the server to impersonate us. Failing to
			// to do this causes an "access denied" failure in CreateInstanceEnum.

			IClientSecurity* security;
			hr = services->QueryInterface(IID_IClientSecurity, (PVOID*) &security);
			if (SUCCEEDED(hr))
				{				// set security
				hr = security->SetBlanket(services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE,
					NULL, RPC_C_AUTHN_LEVEL_CONNECT, RPC_C_IMP_LEVEL_IMPERSONATE,
					NULL, EOAC_NONE);
				if (!SUCCEEDED(hr))
					ReportError(_T("IClientSecurity::SetBlanket"), hr);
				security->Release();
				}				// set security

			// Report WMI information about the specified class

			ReportInfo(services, L"Wmi42");
			services->Release();
			}					// found server
		else
			ReportError(_T("IWbemLocator::ConnectServer"), hr);

		locator->Release();
		}						// found locator
	else
		ReportError(_T("CoCreateInstance(WbemLocator)"), hr);

	CoUninitialize();
	return 0;
	}							// main

///////////////////////////////////////////////////////////////////////////////

void ReportInfo(IWbemServices* services, LPCWSTR classname)
	{							// ReportInfo

	// Open an instance enumerator for the class.

	IEnumWbemClassObject* enumerator = NULL;
	BSTR bs = SysAllocString(classname);
	HRESULT hr = services->CreateInstanceEnum(bs, WBEM_FLAG_SHALLOW | WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, NULL, &enumerator);
	SysFreeString(bs);

	if (SUCCEEDED(hr))
		{						// enumerate instances
		while (TRUE)
			{					// for each instance
			ULONG junk;				
			IWbemClassObject* cop = NULL;
			hr = enumerator->Next(INFINITE, 1, &cop, &junk); // i.e., no timeout, 1 object wanted
			if (hr == WBEM_S_FALSE)
				break;
			if (hr)
				{
				ReportError(_T("IEnumWbemClassObject::Next"), hr);
				break;
				}

			VARIANT instname;
			BSTR propname;

			// Determine the instance name

			propname = SysAllocString(L"InstanceName");
			hr = cop->Get(propname, 0, &instname, NULL, NULL);
			SysFreeString(propname);

			if (!SUCCEEDED(hr))
				{				// can't get instance name
				ReportError(_T("IWbemClassObject::Get(InstanceName)"), hr);
				cop->Release();
				continue;
				}				// can't get instance name

			// Determine the current value of the property
			
			VARIANT answer;
			propname = SysAllocString(L"TheAnswer");
			hr = cop->Get(propname, 0, &answer, NULL, NULL);

			if (!SUCCEEDED(hr))
				{				// can't get instance name
				ReportError(_T("IWbemClassObject::Get(TheAnswer)"), hr);
				SysFreeString(propname);
				cop->Release();
				continue;
				}				// can't get instance name

			printf(_T("The answer from %ws was %d\n"), instname.bstrVal, answer.lVal);

			// Change the property value to be one bigger

			++answer.lVal;
			hr = cop->Put(propname, 0, &answer, 0);
			if (SUCCEEDED(hr))
				{				// update instance
				hr = services->PutInstance(cop, WBEM_FLAG_UPDATE_ONLY, NULL, NULL);
				if (!SUCCEEDED(hr))
					ReportError(_T("IWbemServices::PutInstance"), hr);
				}				// update instance
			else
				ReportError(_T("IWbemClassObject::Put(TheAnswer)"), hr);

			SysFreeString(propname);
			VariantClear(&instname);
			VariantClear(&answer);
			
			cop->Release();
			}
		enumerator->Release();
		}
	else
		ReportError("CreateInstanceEnum", hr);
	}							// ReportInfo

///////////////////////////////////////////////////////////////////////////////

void ReportError(LPCTSTR fcn, DWORD code)
	{							// ReportError
	static struct {DWORD code; LPTSTR text;} wmierrors[] = {
		{WBEM_S_FALSE, _T("WBEM_S_FALSE")},
		{WBEM_S_ALREADY_EXISTS, _T("WBEM_S_ALREADY_EXISTS")},
		{WBEM_S_RESET_TO_DEFAULT, _T("WBEM_S_RESET_TO_DEFAULT")},
		{WBEM_S_DIFFERENT, _T("WBEM_S_DIFFERENT")},
		{WBEM_S_TIMEDOUT, _T("WBEM_S_TIMEDOUT")},
		{WBEM_S_NO_MORE_DATA, _T("WBEM_S_NO_MORE_DATA")},
		{WBEM_S_OPERATION_CANCELLED, _T("WBEM_S_OPERATION_CANCELLED")},
		{WBEM_S_PENDING, _T("WBEM_S_PENDING")},
		{WBEM_S_DUPLICATE_OBJECTS, _T("WBEM_S_DUPLICATE_OBJECTS")},
		{WBEM_E_FAILED, _T("WBEM_E_FAILED")},
		{WBEM_E_NOT_FOUND, _T("WBEM_E_NOT_FOUND")},
		{WBEM_E_ACCESS_DENIED, _T("WBEM_E_ACCESS_DENIED")},
		{WBEM_E_PROVIDER_FAILURE, _T("WBEM_E_PROVIDER_FAILURE")},
		{WBEM_E_TYPE_MISMATCH, _T("WBEM_E_TYPE_MISMATCH")},
		{WBEM_E_OUT_OF_MEMORY, _T("WBEM_E_OUT_OF_MEMORY")},
		{WBEM_E_INVALID_CONTEXT, _T("WBEM_E_INVALID_CONTEXT")},
		{WBEM_E_INVALID_PARAMETER, _T("WBEM_E_INVALID_PARAMETER")},
		{WBEM_E_NOT_AVAILABLE, _T("WBEM_E_NOT_AVAILABLE")},
		{WBEM_E_CRITICAL_ERROR, _T("WBEM_E_CRITICAL_ERROR")},
		{WBEM_E_INVALID_STREAM, _T("WBEM_E_INVALID_STREAM")},
		{WBEM_E_NOT_SUPPORTED, _T("WBEM_E_NOT_SUPPORTED")},
		{WBEM_E_INVALID_SUPERCLASS, _T("WBEM_E_INVALID_SUPERCLASS")},
		{WBEM_E_INVALID_NAMESPACE, _T("WBEM_E_INVALID_NAMESPACE")},
		{WBEM_E_INVALID_OBJECT, _T("WBEM_E_INVALID_OBJECT")},
		{WBEM_E_INVALID_CLASS, _T("WBEM_E_INVALID_CLASS")},
		{WBEM_E_PROVIDER_NOT_FOUND, _T("WBEM_E_PROVIDER_NOT_FOUND")},
		{WBEM_E_INVALID_PROVIDER_REGISTRATION, _T("WBEM_E_INVALID_PROVIDER_REGISTRATION")},
		{WBEM_E_PROVIDER_LOAD_FAILURE, _T("WBEM_E_PROVIDER_LOAD_FAILURE")},
		{WBEM_E_INITIALIZATION_FAILURE, _T("WBEM_E_INITIALIZATION_FAILURE")},
		{WBEM_E_TRANSPORT_FAILURE, _T("WBEM_E_TRANSPORT_FAILURE")},
		{WBEM_E_INVALID_OPERATION, _T("WBEM_E_INVALID_OPERATION")},
		{WBEM_E_INVALID_QUERY, _T("WBEM_E_INVALID_QUERY")},
		{WBEM_E_INVALID_QUERY_TYPE, _T("WBEM_E_INVALID_QUERY_TYPE")},
		{WBEM_E_ALREADY_EXISTS, _T("WBEM_E_ALREADY_EXISTS")},
		{WBEM_E_OVERRIDE_NOT_ALLOWED, _T("WBEM_E_OVERRIDE_NOT_ALLOWED")},
		{WBEM_E_PROPAGATED_QUALIFIER, _T("WBEM_E_PROPAGATED_QUALIFIER")},
		{WBEM_E_PROPAGATED_PROPERTY, _T("WBEM_E_PROPAGATED_PROPERTY")},
		{WBEM_E_UNEXPECTED, _T("WBEM_E_UNEXPECTED")},
		{WBEM_E_ILLEGAL_OPERATION, _T("WBEM_E_ILLEGAL_OPERATION")},
		{WBEM_E_CANNOT_BE_KEY, _T("WBEM_E_CANNOT_BE_KEY")},
		{WBEM_E_INCOMPLETE_CLASS, _T("WBEM_E_INCOMPLETE_CLASS")},
		{WBEM_E_INVALID_SYNTAX, _T("WBEM_E_INVALID_SYNTAX")},
		{WBEM_E_NONDECORATED_OBJECT, _T("WBEM_E_NONDECORATED_OBJECT")},
		{WBEM_E_READ_ONLY, _T("WBEM_E_READ_ONLY")},
		{WBEM_E_PROVIDER_NOT_CAPABLE, _T("WBEM_E_PROVIDER_NOT_CAPABLE")},
		{WBEM_E_CLASS_HAS_CHILDREN, _T("WBEM_E_CLASS_HAS_CHILDREN")},
		{WBEM_E_CLASS_HAS_INSTANCES, _T("WBEM_E_CLASS_HAS_INSTANCES")},
		{WBEM_E_QUERY_NOT_IMPLEMENTED, _T("WBEM_E_QUERY_NOT_IMPLEMENTED")},
		{WBEM_E_ILLEGAL_NULL, _T("WBEM_E_ILLEGAL_NULL")},
		{WBEM_E_INVALID_QUALIFIER_TYPE, _T("WBEM_E_INVALID_QUALIFIER_TYPE")},
		{WBEM_E_INVALID_PROPERTY_TYPE, _T("WBEM_E_INVALID_PROPERTY_TYPE")},
		{WBEM_E_VALUE_OUT_OF_RANGE, _T("WBEM_E_VALUE_OUT_OF_RANGE")},
		{WBEM_E_CANNOT_BE_SINGLETON, _T("WBEM_E_CANNOT_BE_SINGLETON")},
		{WBEM_E_INVALID_CIM_TYPE, _T("WBEM_E_INVALID_CIM_TYPE")},
		{WBEM_E_INVALID_METHOD, _T("WBEM_E_INVALID_METHOD")},
		{WBEM_E_INVALID_METHOD_PARAMETERS, _T("WBEM_E_INVALID_METHOD_PARAMETERS")},
		{WBEM_E_SYSTEM_PROPERTY, _T("WBEM_E_SYSTEM_PROPERTY")},
		{WBEM_E_INVALID_PROPERTY, _T("WBEM_E_INVALID_PROPERTY")},
		{WBEM_E_CALL_CANCELLED, _T("WBEM_E_CALL_CANCELLED")},
		{WBEM_E_SHUTTING_DOWN, _T("WBEM_E_SHUTTING_DOWN")},
		{WBEM_E_PROPAGATED_METHOD, _T("WBEM_E_PROPAGATED_METHOD")},
		{WBEM_E_UNSUPPORTED_PARAMETER, _T("WBEM_E_UNSUPPORTED_PARAMETER")},
		{WBEM_E_MISSING_PARAMETER_ID, _T("WBEM_E_MISSING_PARAMETER_ID")},
		{WBEM_E_INVALID_PARAMETER_ID, _T("WBEM_E_INVALID_PARAMETER_ID")},
		{WBEM_E_NONCONSECUTIVE_PARAMETER_IDS, _T("WBEM_E_NONCONSECUTIVE_PARAMETER_IDS")},
		{WBEM_E_PARAMETER_ID_ON_RETVAL, _T("WBEM_E_PARAMETER_ID_ON_RETVAL")},
		{WBEM_E_INVALID_OBJECT_PATH, _T("WBEM_E_INVALID_OBJECT_PATH")},
		{WBEM_E_OUT_OF_DISK_SPACE, _T("WBEM_E_OUT_OF_DISK_SPACE")},
		{WBEMESS_E_REGISTRATION_TOO_BROAD, _T("WBEMESS_E_REGISTRATION_TOO_BROAD")},
		{WBEMESS_E_REGISTRATION_TOO_PRECISE, _T("WBEMESS_E_REGISTRATION_TOO_PRECISE")},
		};

	LPTSTR msg = NULL;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &msg, 0, NULL))

		_tprintf(_T("Error %8.8lX in %s: %s\n"), code, fcn, msg);
	else
		{						// not a standard message
		for (int i = 0; i < arraysize(wmierrors); ++i)
			if (wmierrors[i].code == code)
				break;
		if (i < arraysize(wmierrors))
			_tprintf(_T("Error %8.8lX in %s: %s\n"), code, fcn, wmierrors[i].text);
		else
			_tprintf(_T("Error %8.8lX in %s\n"), code, fcn);
		}						// not a standard message

	if (msg)
		LocalFree((LPVOID) msg);
	}							// ReportError
