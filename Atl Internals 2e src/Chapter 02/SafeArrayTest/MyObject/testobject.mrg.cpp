// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 02\safearraytest\myobject\testobject.mrg.cpp
// compiler-generated file created 06/21/12 at 10:20:01
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//



//+++ Start Injected Code For Attribute 'support_error_info'
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"

#include <comdef.h>

//--- End Injected Code For Attribute 'support_error_info'
// TestObject.cpp : Implementation of CTestObject

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


#include "TestObject.h"
#include <atlsafe.h>
#import "C:\Program Files\IVI\Bin\IviDriverTypeLib.dll" no_namespace

// CTestObject


STDMETHODIMP CTestObject::GetArray(SAFEARRAY** ppsa)
{
	if (!ppsa) return E_POINTER;

	long rgIndices[] = { 4, 5 };

	{
		IIviDriver* pDriver = NULL;
		IUnknown* punk = NULL;
		CComPtr<IUnknown> spUnk;
		CComSafeArray<BSTR> sa;
	}

	/*
	{
		CComSafeArrayBound bound1(3);
		CComSafeArrayBound bound2(4);
		CComSafeArrayBound bound3(5);
		CComSafeArrayBound rgBound[] = { bound1, bound2, bound3 };
		CComSafeArray<int> sa(rgBound, 3);
	}

	{
		CComSafeArray<double> saSrc(500);
		CComSafeArray<char> saDest(saSrc);
	}

	{
		CComSafeArray<long> saOrig;

		CComSafeArray<long> sa1;
		sa1.Attach(saOrig);
	}

	{
		CComSafeArray<long> sa(5);
		sa.SetAt(3, 5);
	}
	*/

	{
		CComSafeArray<int> sa(5);
		ATLTRACE(sa.IsSizable() ? "\n\nSizeable\n\n" : "\n\nNo\n\n");
	}

	{
		CComSafeArray<int> sa;
		sa.Add(2);
		int rgVal[] = { 4, 6 };
		sa.Add(2, rgVal);
		sa.Add(sa);
	}

	{
		CComSafeArray<int> sa(5);
		ATLASSERT(sa[2] == 0);
		long l = sa[3];
		sa[2] = 3;
		ATLASSERT(sa[2] == 3);
	}
	
	return S_OK;
}

