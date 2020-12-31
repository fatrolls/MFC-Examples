#ifndef __ICheckSpell_H__
#define __ICheckSpell_H__

#ifndef __IMyUnknown_H__
#include "IMyUnknown.h"
#endif

#ifndef String
typedef wchar_t *String;
#endif

// {54BF6569-1007-11D1-B0AA-444553540000}
extern "C" const GUID IID_SpellCheck = 
		{ 0x54bf6569, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;

class ISpellCheck : public IMyUnknown 
{
	public : 
		virtual BOOL __stdcall CheckWord(String, String*) = 0;
};

#endif // __ISpellCheck_H__
