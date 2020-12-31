#ifndef __ICheckSpell_H__
#define __ICheckSpell_H__

#include "Unknwn.h"

#ifndef String
typedef BSTR String;
#endif

// {54BF6569-1007-11D1-B0AA-444553540000}
extern "C" const GUID IID_SpellCheck;

class ISpellCheck : public IUnknown 
{
	public : 
		virtual HRESULT __stdcall CheckWord(String, String) = 0;
};

#endif // __ISpellCheck_H__
