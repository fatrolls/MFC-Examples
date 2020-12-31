/////////////////////////////////////////////////
//
//  CCOMException, HRESULTEX classes
//
//  Copyright (c) 1997, Tim Ewald
//

#ifndef COMEXCEPT_H
#define COMEXCEPT_H

#include "smartif.h"

#ifndef  __NO_ERRORINFO__

class CCOMException
{
private:
    SI(IErrorInfo) m_pei;
    HRESULT m_hr;

    friend class HRESULTEX;
    CCOMException(HRESULT hr, SI(IErrorInfo) &pei)
    : m_hr(hr), m_pei(pei)
    {
    }

public:
    CCOMException(HRESULT hr,
                  LPOLESTR wszDescription,
                  LPOLESTR wszSource = 0,
                  REFIID riid = IID_NULL,
                  DWORD dwHelpContext = 0,
                  LPOLESTR wszHelpFile = 0)
    : m_hr(hr)
    {
        SI(ICreateErrorInfo) pcei;
	    CreateErrorInfo(pcei.GetReleasedInterfaceReference());
	    if (pcei)
        {
            pcei->SetDescription(SysAllocString(wszDescription));
            pcei->SetGUID(riid);
            pcei->SetHelpContext(dwHelpContext);
            pcei->SetHelpFile(SysAllocString(wszHelpFile));
            pcei->SetSource(SysAllocString(wszSource));
            m_pei = pcei;
            if (m_pei) SetErrorInfo(0, m_pei.GetNonAddRefedInterface());
        }
    }

    HRESULT hr(void) const
    {
        return m_hr;
    }

    BSTR Description(void) const
    {
        BSTR bstr;
        const_cast<CCOMException*>(this)->m_pei->GetDescription(&bstr);
        return bstr;
    }
    
    IID InterfaceID(void) const
    {
        IID iid;
        const_cast<CCOMException*>(this)->m_pei->GetGUID(&iid);
        return iid;
    }

    DWORD HelpContext(void) const
    {
        DWORD dw;
        const_cast<CCOMException*>(this)->m_pei->GetHelpContext(&dw);
        return dw;
    }

    BSTR HelpFile(void) const
    {
        BSTR bstr;
        const_cast<CCOMException*>(this)->m_pei->GetHelpFile(&bstr);
        return bstr;
    }
        
    BSTR Source(void) const
    {
        BSTR bstr;
        const_cast<CCOMException*>(this)->m_pei->GetSource(&bstr);
        return bstr;
    }
};

#define COM_TRY \
    HRESULT __hr_ex__ = S_OK; \
    try {

#define COM_CATCH \
    } \
    catch (HRESULT h) { \
        __hr_ex__ = h; \
    } \
    catch (const CCOMException &e) { \
        __hr_ex__ = e.hr(); \
    } \
    catch (...) { \
        CCOMException(__hr_ex__ = E_FAIL, OLESTR("The object threw an unknown exception!")); \
    } \
    return __hr_ex__; 

#else // #ifndef __NO_ERRORINFO__

#define COM_TRY \
    HRESULT __hr_ex__ = S_OK; \
    try {

#define COM_CATCH \
    } \
    catch (HRESULT h) { \
        __hr_ex__ = h; \
    } \
    catch (...) { \
        __hr_ex__ = E_FAIL; \
    } \
	return __hr_ex__;

#endif // #ifndef __NO_ERRORINFO__


class HRESULTEX
{
    HRESULT m_hr;
    void ThrowIfFailed(void)
    {
        if (FAILED(m_hr))
        {
#ifndef __NO_ERRORINFO__
            SI(IErrorInfo) pei;
            GetErrorInfo(0, pei.GetReleasedInterfaceReference());
			if (pei)
				throw CCOMException(m_hr, pei);
			else
#endif // #ifndef __NO_ERRORINFO__
            {
#ifdef _DEBUG
                TCHAR   tsz[64];
                wsprintf(tsz, __TEXT("FAILED(hr)= 0x%x\n"), m_hr);
                OutputDebugString(tsz);
#endif
			    throw m_hr;
            }
        }
    }

public:
    HRESULTEX(void) : m_hr(S_OK) {}

    HRESULTEX(HRESULT hr) : m_hr(hr)
    {
        ThrowIfFailed();
    }

    HRESULTEX& operator= (const HRESULT rhs)
    {
        m_hr = rhs;
        ThrowIfFailed();
        return *this;
    }

    operator HRESULT(void)
    {
        return m_hr;
    }
};

#endif // COMEXCEPT_H
