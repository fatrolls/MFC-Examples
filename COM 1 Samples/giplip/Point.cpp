// Point.cpp : Implementation of CPoint
#include "stdafx.h"
#include "RectPoint.h"
#include "Point.h"

/////////////////////////////////////////////////////////////////////////////
// CPoint


STDMETHODIMP CPoint::GetCoords(long * px, long * py)
{
    *px = m_x;
    *py = m_y;
	return S_OK;
}

STDMETHODIMP CPoint::SetCoords(long x, long y)
{
    m_x = x;
    m_y = y;
	return S_OK;
}
