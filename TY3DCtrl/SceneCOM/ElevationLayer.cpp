// ElevationLayer.cpp : Implementation of CElevationLayer

#include "stdafx.h"
#include "ElevationLayer.h"
#include "ConfigOpt.h"

// CElevationLayer

STDMETHODIMP CElevationLayer::FromConfig(IConfigOpt* conf)
{
    if (conf == NULL)
    {
        return E_FAIL;
    }
    CConfigOpt* opt = (CConfigOpt*)conf;
    return S_OK;
}
