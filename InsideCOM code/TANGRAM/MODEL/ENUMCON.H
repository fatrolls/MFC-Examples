#ifndef __CEnumConnections_h__
#define __CEnumConnections_h__

///////////////////////////////////////////////////////////
//
//
// EnumCon - Header file for CEnumConnecitons.
//
//

#include "CUnknown.h"
#include <olectl.h>
#include <assert.h>

#include "ConData.h"

///////////////////////////////////////////////////////////
//
// CEnumConnections
//
class CEnumConnections :	public CUnknown,
							public IEnumConnections
{
public:
	// Constructor
	CEnumConnections(CConnectDataList& ConnectData) ; //TODO const

	// Copy Constructor
	CEnumConnections(const CEnumConnections& X) ; 

	// Destructor
	~CEnumConnections() ;

	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface(const IID& iid, void** ppv) ;			

	// IEnumConnections
	virtual HRESULT __stdcall Next(ULONG celt, CONNECTDATA* rgelt, ULONG* pceltFetched);
	virtual HRESULT __stdcall Skip(ULONG celt) ;
	virtual HRESULT __stdcall Reset() ;
	virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) ;

	// CONNECTDATA STL array
	CConnectDataList m_list;

	// Current pointer
	CConnectDataList::iterator m_iter ;
};
#endif