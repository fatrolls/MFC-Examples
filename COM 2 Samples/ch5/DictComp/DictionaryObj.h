#if !defined(AFX_DICTIONARYOBJ_H__84B0BC03_AD8B_11D2_A2DC_A31D6122660F__INCLUDED_)
#define AFX_DICTIONARYOBJ_H__84B0BC03_AD8B_11D2_A2DC_A31D6122660F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DictionaryObj.h : header file
//

#include "Interface.h"

#define MaxWordLength 32
struct DictWord
{
	char wordForLang1[MaxWordLength];
	char wordForLang2[MaxWordLength];
};


/////////////////////////////////////////////////////////////////////////////
// CDictionaryObj command target

class CDictionaryObj : public CCmdTarget
{
	DECLARE_DYNCREATE(CDictionaryObj)

	CDictionaryObj();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDictionaryObj)
	//}}AFX_VIRTUAL

// IDictionary
	BEGIN_INTERFACE_PART(Dictionary, IDictionary)
		INIT_INTERFACE_PART(CDictionary, Dictionary)
		STDMETHOD_(BOOL, Initialize)();
		STDMETHOD_(BOOL, LoadLibrary)(LPOLESTR);
		STDMETHOD_(BOOL, InsertWord)(LPOLESTR, LPOLESTR);
		STDMETHOD_(void, DeleteWord)( LPOLESTR);
		STDMETHOD_(BOOL, LookupWord)(LPOLESTR, LPOLESTR *);
		STDMETHOD_(BOOL, RestoreLibrary)(LPOLESTR);
		STDMETHOD_(void, FreeLibrary)();
	END_INTERFACE_PART_STATIC(Dictionary) 
	
		// ISpellCheck
	BEGIN_INTERFACE_PART(SpellCheck, ISpellCheck)
		INIT_INTERFACE_PART(CDictionary, SpellCheck)
		STDMETHOD_(BOOL, CheckWord)(LPOLESTR, LPOLESTR *);
	END_INTERFACE_PART_STATIC(SpellCheck)

// Implementation
protected:
	virtual ~CDictionaryObj();

	// Generated message map functions
	//{{AFX_MSG(CDictionaryObj)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_INTERFACE_MAP()
	DECLARE_OLECREATE(CDictionaryObj)

private :
	struct	DictWord *m_pData;
	char	*m_DictFilename[128];
	int		m_nWordNumber, m_nStructNumber;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DICTIONARYOBJ_H__84B0BC03_AD8B_11D2_A2DC_A31D6122660F__INCLUDED_)
