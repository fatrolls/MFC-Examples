#ifndef _UTFINGERCP_H_
#define _UTFINGERCP_H_



template <class T>
class CProxy_IFingerEvents : public IConnectionPointImpl<T, &DIID__IFingerEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnFinger(LONG Result)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[1];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				VariantClear(&varResult);
				pvars[0] = Result;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };

				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pT->m_bBlockingMode)
					pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
				else if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
};
#endif