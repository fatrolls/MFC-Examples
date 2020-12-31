
//////////////////////////////////////////////////////////////////////////////
// CProxyICMPComEvent
template <class T>
class CProxyICMPComEvent : public IConnectionPointImpl<T, &IID_ICMPComEvent, CComDynamicUnkArray>
{
public:

//ICMPComEvent : IDispatch
public:
	HRESULT Fire_PingMsgEvent(
		BSTR PingMsg)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		IUnknown** xx = m_vec.end();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ICMPComEvent* pICMPComEvent
					= reinterpret_cast<ICMPComEvent*>(*pp);
				ret = pICMPComEvent->PingMsgEvent(PingMsg);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}

	//
	//
	//
	HRESULT Fire_PingDoneEvent()
	
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		IUnknown** xx = m_vec.end();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ICMPComEvent* pICMPComEvent
					= reinterpret_cast<ICMPComEvent*>(*pp);
				ret = pICMPComEvent->PingDoneEvent();
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

