#ifndef __IDictionary_H__
#define __IDictionary_H__

#include "Unknwn.h"

typedef BSTR String;

// {54BF6568-1007-11D1-B0AA-444553540000}
extern "C" const GUID IID_Dictionary;

class IDictionary : public IUnknown 
{
	public : 
		virtual HRESULT __stdcall Initialize() = 0;
		virtual HRESULT __stdcall LoadLibrary(String) = 0;
		virtual HRESULT __stdcall InsertWord(String, String) = 0;
		virtual HRESULT __stdcall DeleteWord(String) = 0;
		virtual HRESULT __stdcall LookupWord(String, String) = 0;
		virtual HRESULT __stdcall RestoreLibrary(String) = 0;
		virtual HRESULT __stdcall FreeLibrary() = 0;
};

#endif // __IDictionary_H__
