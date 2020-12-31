// Randexe.h : Declaration of the CRandexe

#ifndef __RANDEXE_H_
#define __RANDEXE_H_

#include "resource.h"       // main symbols

const int nMaxSessions = 10;

/////////////////////////////////////////////////////////////////////////////
// CRandexe
class ATL_NO_VTABLE CRandexe : 
	public IDispatchImpl<IRandexe, &IID_IRandexe, &LIBID_CONEXELib>,
    public IConnectionPointImpl<CRandexe, &IID_IRandexeEvent, CComDynamicUnkArray>,
	public IConnectionPointContainerImpl<CRandexe>,
	public CComObjectRoot,
	public CComCoClass<CRandexe, &CLSID_Randexe>
{
public:
	CRandexe()
	{
		memset(m_rsArray, 0, nMaxSessions*sizeof(RandomSessionData));
	}
	~CRandexe();

DECLARE_REGISTRY_RESOURCEID(IDR_RANDEXE)

BEGIN_COM_MAP(CRandexe)
	COM_INTERFACE_ENTRY2(IDispatch, IRandexe)
	COM_INTERFACE_ENTRY(IRandexe)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CRandexe)
		CONNECTION_POINT_ENTRY(IID_IRandexeEvent)
END_CONNECTION_POINT_MAP()


// IRandexe
public:
	STDMETHOD(Start)(long* pnID);
	STDMETHOD(Stop)(long nID);
	STDMETHOD(StopAll)();

	// method to broadcast a call on the current connections
	HRESULT Fire(long  nID);
	// info associated to each session
	struct RandomSessionData
	{
		CRandexe* pRandom;
		HANDLE m_hEvent;
		HANDLE m_hThread;
		int m_nID;
	};
protected:

	RandomSessionData m_rsArray[nMaxSessions];
	void CreateRandomSession(RandomSessionData& rs);

	_ThreadModel::AutoCriticalSection m_cs;
};

#endif //__RANDEXE_H_
