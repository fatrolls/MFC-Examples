#ifndef _UTFTPSERVCP_H_
#define _UTFTPSERVCP_H_






template <class T>
class CProxy_IFtpServEvents : public IConnectionPointImpl<T, &DIID__IFtpServEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnStatus(BSTR Message)
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
					pMarshaledDispatch->Release();
					}

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnConnect()
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
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
					pMarshaledDispatch->Invoke(0x2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
					pMarshaledDispatch->Release();
					}

			}
		}
		return varResult.scode;
	
	}
	HRESULT Fire_OnMaxConnect()
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
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
					pMarshaledDispatch->Invoke(0x3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
					pMarshaledDispatch->Release();
					}

			}
		}
		return varResult.scode;
	
	}
	HRESULT Fire_OnCommandStarted(FtpCommand CommandID, BSTR Params, VARIANT_BOOL * Accept)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[3];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				VARIANT	var;
				var.vt = VT_BOOL | VT_BYREF;
				var.pboolVal = Accept;

				VariantClear(&varResult);
				pvars[2] = CommandID;
				pvars[1] = Params;
				pvars[0] = var;
				DISPPARAMS disp = { pvars, NULL, 3, 0 };
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
					pMarshaledDispatch->Release();
					}

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnCommandFinished(FtpCommand CommandID, BSTR Params, LONG Success)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[3];
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
				pvars[2] = CommandID;
				pvars[1] = Params;
				pvars[0] = Success;
				DISPPARAMS disp = { pvars, NULL, 3, 0 };
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
					pMarshaledDispatch->Release();
					}

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnCheckPassword(BSTR User, BSTR Password, VARIANT_BOOL * Accept)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[3];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				VARIANT	var;
				var.vt = VT_BOOL | VT_BYREF;
				var.pboolVal = Accept;

				VariantClear(&varResult);
				pvars[2] = User;
				pvars[1] = Password;
				pvars[0] = var;
				DISPPARAMS disp = { pvars, NULL, 3, 0 };
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
					pMarshaledDispatch->Release();
					}

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnConnectNotify(BSTR IPAddress, VARIANT_BOOL * Accept)
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
				VARIANT	var;
				var.vt = VT_BOOL | VT_BYREF;
				var.pboolVal = Accept;

				VariantClear(&varResult);
				pvars[1] = IPAddress;
				pvars[0] = var;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
					pMarshaledDispatch->Release();
					}

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnDisconnect()
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
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
					pMarshaledDispatch->Invoke(0x8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
					pMarshaledDispatch->Release();
					}

			}
		}
		return varResult.scode;
	
	}
	HRESULT Fire_OnCanAccept(BSTR Address, VARIANT_BOOL * Result)
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
				VARIANT	var;
				var.vt = VT_BOOL | VT_BYREF;
				var.pboolVal = Result;

				VariantClear(&varResult);
				pvars[1] = Address;
				pvars[0] = var;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch) {
					pMarshaledDispatch->Invoke(0x9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
					pMarshaledDispatch->Release();
					}

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}

};
#endif