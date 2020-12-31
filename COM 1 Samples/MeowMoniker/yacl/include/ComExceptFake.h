/////////////////////////////////////////////////
//
//  FAKE HRESULTEX class
//
//  Copyright (c) 1997, Chris Sells
//

#ifndef COMEXCEPT_H
#define COMEXCEPT_H

#define COM_TRY \
    HRESULT __hr_ex__ = S_OK; \
    {

#define COM_CATCH \
    } \
    return __hr_ex__; 

class HRESULTEX
{
    HRESULT m_hr;
    void ThrowIfFailed(void)
    {
        if (FAILED(m_hr))
        {
            char    sz[64];
            wsprintfA(sz, "FAILED(hr)= 0x%x\n", m_hr);
            ::OutputDebugString(sz);
            DebugBreak();
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
