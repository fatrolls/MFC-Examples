
//////////////////////////////////////////////////////////////////////////////
// CProxyDICMPComEvent
template <class T>
class CProxyDICMPComEvent : public IConnectionPointImpl<T, &DIID_DICMPComEvent, CComDynamicUnkArray>
{
public:
//methods:
//DICMPComEvent : IDispatch
public:
	void Fire_PingMsgEvent(
		BSTR PingMsg)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				pvars[0].vt = VT_BSTR;
				pvars[0].bstrVal= PingMsg;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		delete[] pvars;
	}
	HRESULT Fire_PingDoneEvent()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				DISPPARAMS disp = { NULL, NULL, 0, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		return varResult.scode;
	}
	HRESULT Fire_PingTerminated()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				DISPPARAMS disp = { NULL, NULL, 0, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		return varResult.scode;
	}

};

