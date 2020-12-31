// Rect.cpp : Implementation of CRect
#include "stdafx.h"
#include "RectPoint.h"
#include "Rect.h"
#include <assert.h>
/////////////////////////////////////////////////////////////////////////////
// CRect
#define _INIT_GIPLIP
#include "giplip.h"
GIT _init_git;

STDMETHODIMP CRect::SetCoords(long left, long top, long right, long bottom)
{
    HRESULT hr = S_OK;
    LIP(IPoint) lipTopLeft(m_gipTopLeft, hr);
    if (FAILED(hr))
        return hr;
    LIP(IPoint) lipBottomRight(m_gipBottomRight, hr);
    if (FAILED(hr))
        return hr;
    hr = lipTopLeft->SetCoords(left, top);
    if (FAILED(hr))
        return hr;
    hr = lipBottomRight->SetCoords(right, bottom);
    return hr;
}

STDMETHODIMP CRect::get_Volume(long * pVal)
{
    HRESULT hr = S_OK;
    *pVal = 0;
    long top, left, right, bottom;
    IPoint *pPoint = 0;
    hr = m_gipTopLeft.Localize(&pPoint);
    if (SUCCEEDED(hr))
    {
        hr = pPoint->GetCoords(&left, &top);
        pPoint->Release();
    }
    if (SUCCEEDED(hr)) {
    
        hr = m_gipBottomRight.Localize(&pPoint);
        if (SUCCEEDED(hr))
        {
            hr = pPoint->GetCoords(&right, &bottom);
            pPoint->Release();
        }
    }
    if (SUCCEEDED(hr))
        *pVal = (right - left) * (bottom - top);
    return hr;
}
