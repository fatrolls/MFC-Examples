#ifndef __IDictionary_H__
#define __IDictionary_H__

#ifndef __IMyUnknown_H__
#include "IMyUnknown.h"
#endif

typedef wchar_t *String;

// {54BF6568-1007-11D1-B0AA-444553540000}
extern "C" const GUID IID_Dictionary = 
		{ 0x54bf6568, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;

class IDictionary : public IMyUnknown 
{
	public : 
		virtual BOOL __stdcall Initialize() = 0;
		virtual BOOL __stdcall LoadLibrary(String) = 0;
		virtual BOOL __stdcall InsertWord(String, String) = 0;
		virtual void __stdcall DeleteWord(String) = 0;
		virtual BOOL __stdcall LookupWord(String, String *) = 0;
		virtual BOOL __stdcall RestoreLibrary(String) = 0;
		virtual void __stdcall FreeLibrary() = 0;
};

#endif // __IDictionary_H__
