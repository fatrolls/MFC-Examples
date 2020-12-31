#ifndef _UTNNTPCP_H_
#define _UTNNTPCP_H_


template <class T>
class CProxy_INntpEvents : public IConnectionPointImpl<T, &DIID__INntpEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnSendArticleProgress(LONG BytesSent, LONG BytesTotal)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[2];
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
				pvars[1] = BytesSent;
				pvars[0] = BytesTotal;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };

				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnConnect(LONG Result)
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
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnClose(LONG Result)
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
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnCheckCanPost(LONG Result)
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
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnGetServerDate(BSTR Date, LONG Result)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[2];
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
				pvars[1] = Date;
				pvars[0] = Result;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };

				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnSelectNewsGroup(LONG Result)
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
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnGetArticle(LONG Result)
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
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnPostArticle(LONG Result)
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
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnGetArticleList(LONG Result)
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
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnGetNewsGroupList(LONG Result)
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
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0xa, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
};
#endif