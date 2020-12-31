///////////////////////////////////////////////////////////////////////////////
//
// hrx.h - Copyright 1997, Chris Sells
// Based on ComExcept.h, Copyright 1997, Tim Ewald
//
// Usage:
/*
HRESULT CoPoint::GetCoords(long* px, long* py)
{
    COM_TRY
    {
        HRX hrx;
        if( !px || !py ) hrx = E_POINTER;

        *px = m_x;
        *py = m_y;
    }
    COM_CATCH
}
*/

#ifndef HRX_H
#define HRX_H

class HRX
{
public:
    HRX(HRESULT hr = S_OK) : m_hr(hr)
    {
        ThrowIfFailed();
    }

    HRX(const HRX& hrx) : m_hr(hrx.m_hr)
    {
        ThrowIfFailed();
    }

    HRX& operator=(HRESULT hr)
    {
        m_hr = hr;
        ThrowIfFailed();
        return *this;
    }

private:
    HRESULT m_hr;

    void ThrowIfFailed()
    {
        if( FAILED(m_hr) )
        {
#ifdef _DEBUG
            char    szBuf[32];
            wsprintfA(szBuf, "Throwing hr= 0x%x\n", m_hr);
            OutputDebugStringA(szBuf);
#endif
            throw m_hr;
        }
    }
};

#define COM_TRY \
    HRESULT __hr_ex__ = S_OK; \
    try {

#define COM_CATCH \
    } \
    catch (HRESULT hr) { \
        __hr_ex__ = hr; \
    } \
    catch (...) { \
        __hr_ex__ = E_FAIL; \
    } \
	return __hr_ex__;

#endif  // HRX_H
