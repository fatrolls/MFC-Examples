// ImageLayer.cpp : Implementation of CImageLayer

#include "stdafx.h"
#include "ImageLayer.h"
#include "ConfigOpt.h"


// CImageLayer


STDMETHODIMP CImageLayer::FromConfig(IConfigOpt* conf)
{
    if (conf == NULL)
    {
        return E_FAIL;
    }
    CConfigOpt* opt = (CConfigOpt*)conf;
    return S_OK;
}