#ifndef _UTFTPCP_H_
#define _UTFTPCP_H_




template <class T>
class CProxy_IFtpEvents : public IConnectionPointImpl<T, &DIID__IFtpEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnReceiveStatus(LONG BytesReceived)
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
				pvars[0] = BytesReceived;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };

				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnSendStatus(LONG BytesSend)
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
				pvars[0] = BytesSend;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
 	HRESULT Fire_OnCdUp(LONG Result)
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
	HRESULT Fire_OnChDir(LONG Result)
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
					pMarshaledDispatch->Invoke(0x5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnDeleteFile(LONG Result)
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
	HRESULT Fire_OnGetDirInfo(LONG Result)
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
	HRESULT Fire_OnGetHelp(LONG Result)
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
	HRESULT Fire_OnMkDir(LONG Result)
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
	HRESULT Fire_OnNOOP(LONG Result)
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
	HRESULT Fire_OnReceiveFile(LONG Result)
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
					pMarshaledDispatch->Invoke(0xb, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnRenameFile(LONG Result)
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
					pMarshaledDispatch->Invoke(0xc, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnRemDir(LONG Result)
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
					pMarshaledDispatch->Invoke(0xd, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnSendFile(LONG Result)
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
					pMarshaledDispatch->Invoke(0xe, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnGetCurDir(LONG Result, BSTR Directory)
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
				pvars[1] = Result;
				pvars[0] = Directory;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0xf, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

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
					pMarshaledDispatch->Invoke(0x10, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnSetTransferMode(LONG Result)
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
					pMarshaledDispatch->Invoke(0x11, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnSetTransferStructure(LONG Result)
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
					pMarshaledDispatch->Invoke(0x12, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnSetTransferType(LONG Result)
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
					pMarshaledDispatch->Invoke(0x13, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnResumeFile(LONG Result)
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
					pMarshaledDispatch->Invoke(0x14, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}

	HRESULT Fire_OnQuote(LONG Result)
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
					pMarshaledDispatch->Invoke(0x15, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}

};
#endif