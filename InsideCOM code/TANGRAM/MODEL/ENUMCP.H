///////////////////////////////////////////////////////////
//
//
//	EnumCP.h - Header file for CEnumConnectionPoints
//
//
#ifndef __CEnumConnectionPoints_h__
#define __CEnumConnectionPoints_h__

#include "CUnknown.h"
#include <olectl.h>
#include <ocidl.h> //For IConnectionPoint and IEnumConnectionPoints

///////////////////////////////////////////////////////////
//
//	CEnumConnectionPoints
//
class CEnumConnectionPoints :	public CUnknown,
								public IEnumConnectionPoints
{
public:
	// STL Types
	typedef std::list<IConnectionPoint*> CConnectionPointList;

	// Constructor - Takes a single IConnectionPoint ptr.
	CEnumConnectionPoints(IConnectionPoint* pIConnectionPoint) ;

	// Constructor - Takes a CConnectionPointList.
	CEnumConnectionPoints(CConnectionPointList& cplist) ; 

	// Copy Constructor
	CEnumConnectionPoints(const CEnumConnectionPoints& X) ; 

	// Destructor
	~CEnumConnectionPoints() ;

	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface(const IID& iid, void** ppv) ;

	// IEnumConnections
	virtual HRESULT __stdcall Next(ULONG cConnections, IConnectionPoint** ppCP, ULONG* pcFetched);
	virtual HRESULT __stdcall Skip(ULONG cConnections) ;
	virtual HRESULT __stdcall Reset() ;
	virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) ;

	// IConnectionsPoints STL list
	CConnectionPointList m_list;

	// Current pointer
	CConnectionPointList::iterator m_iter ;
};

#endif


