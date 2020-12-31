#ifndef _UTIMAP4CP_H_
#define _UTIMAP4CP_H_



template <class T>
class CProxy_IIMAP4Events : public IConnectionPointImpl<T, &DIID__IIMAP4Events, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnAlert(BSTR Message)
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
				pvars[0] = Message;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };

				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnExpunge(LONG MsgID)
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
				pvars[0] = MsgID;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };

				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnRecent(LONG MsgNumber)
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
				pvars[0] = MsgNumber;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };

				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnExists(LONG MsgNumber)
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
				pvars[0] = MsgNumber;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnNoop(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxSelect(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxExamine(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxCreate(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0xa, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxDelete(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0xb, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxSubscribe(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0xc, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxUnsubscribe(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0xd, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxRename(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0xe, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxList(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0xf, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxLSub(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x10, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxAppend(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x11, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxCheck(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x12, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxClose(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x13, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMailBoxStatus(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x14, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMessageExpunge(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x15, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMessageSearch(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x16, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMessageCopy(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x17, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMessageFetch(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x18, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnMessageStore(LONG Result)
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
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x19, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnFetch()
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
				DISPPARAMS disp = { NULL, NULL, 0, 0 };
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
                if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x1a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
                    if(pMarshaledDispatch != NULL)
                        pMarshaledDispatch->Release();
                    }

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
};
#endif