#ifndef _UTMAILCP_H_
#define _UTMAILCP_H_



template <class T>
class CProxy_IMailEvents : public IConnectionPointImpl<T, &DIID__IMailEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:

#ifndef _BLOCKING_MODE_ONLY

	HRESULT Fire_OnSendMailProgress(LONG BytesSent, LONG BytesTotal)
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
	HRESULT Fire_OnSMTPConnect(LONG Result)
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
	HRESULT Fire_OnSendMail(LONG Result)
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
	HRESULT Fire_OnPOP3Connect(LONG Result)
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
	HRESULT Fire_OnGetMsgNumber(LONG MsgNumber, LONG Result)
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
				pvars[1] = MsgNumber;
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
	HRESULT Fire_OnGetMsgSize(LONG MsgSize, LONG Result)
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
				pvars[1] = MsgSize;
				pvars[0] = Result;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0x6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnSaveMsg(LONG Result)
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
	HRESULT Fire_OnSaveMsgProgress(LONG BytesReceived)
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
					pMarshaledDispatch->Invoke(0x8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnDeleteMsg(LONG Result)
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
	HRESULT Fire_OnResetDelete(LONG Result)
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
	HRESULT Fire_OnOpenMsg(LONG Result)
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
	HRESULT Fire_OnReadMsgLine(BSTR Line, LONG Result)
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
				pvars[1] = Line;
				pvars[0] = Result;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0xc, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
	HRESULT Fire_OnOpenTop(LONG Result)
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
	HRESULT Fire_OnReadTopLine(BSTR Line, LONG Result)
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
				pvars[1] = Line;
				pvars[0] = Result;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				
				IDispatch* pMarshaledDispatch = pT->GetMarshaledInterface(pDispatch);
				if(pMarshaledDispatch)
					pMarshaledDispatch->Invoke(0xe, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}

	HRESULT Fire_OnCloseTop(LONG Result)
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
					pMarshaledDispatch->Invoke(0xf, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);

			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}

	HRESULT Fire_OnCloseMsg(LONG Result)
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

	HRESULT Fire_OnPOP3Close(LONG Result)
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

    HRESULT Fire_OnSMTPClose(LONG Result)
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

#endif // _BLOCKING_MODE_ONLY

};
#endif