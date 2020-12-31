// Driver.h : Declaration of the CDriver


#include "mdrivres.h"       // main symbols
#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// Drive
struct foo
{
	foo() {nPos = 0;nDir=1;}
	int nPos;
	int nDir;
};

class CDriver : 
	public IDispatchImpl<IRandexeEvent, &IID_IRandexeEvent, &LIBID_CONEXELib>, 
	public CComObjectRoot
{
public:
	CDriver() {}
BEGIN_COM_MAP(CDriver)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IRandexeEvent)
END_COM_MAP()

// IRandomEvent
	STDMETHOD(Fire)(long l);
	int m_nID;
	CMap<long, long, foo, foo> m_mapPos;
	_ThreadModel::AutoCriticalSection m_cs;
public:
};
