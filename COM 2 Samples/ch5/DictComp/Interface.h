#ifndef __IDictionary_H__
#define __IDictionary_H__

#include "Unknwn.h"

// {54BF6568-1007-11D1-B0AA-444553540000}
extern "C" const IID IID_Dictionary;

class IDictionary : public IUnknown 
{
	public : 
		virtual BOOL __stdcall Initialize() = 0;
		virtual BOOL __stdcall LoadLibrary(LPOLESTR) = 0;
		virtual BOOL __stdcall InsertWord(LPOLESTR, LPOLESTR) = 0;
		virtual void __stdcall DeleteWord(LPOLESTR) = 0;
		virtual BOOL __stdcall LookupWord(LPOLESTR, LPOLESTR*) = 0;
		virtual BOOL __stdcall RestoreLibrary(LPOLESTR) = 0;
		virtual void __stdcall FreeLibrary() = 0;
};

#endif // __IDictionary_H__

#ifndef __ICheckSpell_H__
#define __ICheckSpell_H__

#include "Unknwn.h"

// {54BF6569-1007-11D1-B0AA-444553540000}
extern "C" const IID IID_SpellCheck;

class ISpellCheck : public IUnknown 
{
	public : 
		virtual BOOL __stdcall CheckWord(LPOLESTR, LPOLESTR *) = 0;
};

#endif // __ISpellCheck_H__
