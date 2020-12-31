// ModelLayer.cpp : Implementation of CModelLayer

#include "stdafx.h"
#include "ModelLayer.h"
#include "ConfigOpt.h"


// CModelLayer


STDMETHODIMP CModelLayer::FromConfig(IConfigOpt* conf)
{
    if (conf == NULL)
    {
        return E_FAIL;
    }
    CConfigOpt* opt = (CConfigOpt*)conf;
    return S_OK;
}