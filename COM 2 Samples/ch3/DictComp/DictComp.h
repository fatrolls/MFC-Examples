#ifndef __DictComp_H__
#define __DictComp_H__

#ifndef __IDictionary_H__
#include "IDictionary.h"
#endif

#ifndef __ISpellCheck_H__
#include "ISpellCheck.h"
#endif

#define MaxWordLength 32
struct DictWord
{
	char wordForLang1[MaxWordLength];
	char wordForLang2[MaxWordLength];
};

class CDictionary : public IDictionary ,  public ISpellCheck
{
	public :
		CDictionary();
		~CDictionary();
	public :
	// IUnknown member function
		virtual HRESULT __stdcall QueryInterface(const IID& iid, void **ppv) ;
		virtual ULONG	__stdcall AddRef() ; 
		virtual ULONG	__stdcall Release() ;

	// IDictionary member function
		virtual BOOL __stdcall Initialize();
		virtual BOOL __stdcall LoadLibrary(String);
		virtual BOOL __stdcall InsertWord(String, String);
		virtual void __stdcall DeleteWord(String);
		virtual BOOL __stdcall LookupWord(String, String *);
		virtual BOOL __stdcall RestoreLibrary(String);
		virtual void __stdcall FreeLibrary();
	
	// ISpellCheck member function
		virtual BOOL __stdcall CheckWord (String word, String *);
	
	private :
		struct	DictWord *m_pData;
		char	*m_DictFilename[128];
		int		m_Ref ;
		int		m_nWordNumber, m_nStructNumber;
};

#endif // __DictComp_H__