// LayerInfo.cpp : Implementation of CLayerInfo

#include "stdafx.h"
#include "LayerInfo.h"

#include "LayerProperty.h"



// CLayerInfo

CLayerInfo::~CLayerInfo()
{
    if (mLayerInfo != NULL)
    {
        delete mLayerInfo;
    }
}
STDMETHODIMP CLayerInfo::GetGeoType(LONG* type)
{
    if (type == NULL || mLayerInfo == NULL)
    {
        return E_FAIL;
    }

    if (mLayerInfo->GetLayerType() == MODELLAYER)
    {
        *type = static_cast<CModelLayerProperty*>(mLayerInfo)->GetGeoType();
    }
    else
    {
        *type = Geometry::Type::TYPE_UNKNOWN;
    }
    return S_OK;
}
STDMETHODIMP CLayerInfo::IsVisible(VARIANT_BOOL* bVisible)
{
    if (bVisible == NULL || mLayerInfo == NULL)
    {
        return E_FAIL;
    }

    *bVisible = mLayerInfo->IsVisible();
    return S_OK;
}
STDMETHODIMP CLayerInfo::GetLayerType(LONG* type)
{
    if (type == NULL || mLayerInfo == NULL)
    {
        return E_FAIL;
    }

 
    *type = mLayerInfo->GetLayerType();
    return S_OK;
}
STDMETHODIMP CLayerInfo::GetLayerName(BSTR* name)
{
    if (name == NULL || mLayerInfo == NULL)
    {
        return E_FAIL;
    }

    CComBSTR bstr = mLayerInfo->GetLayerName().c_str();
    *name = bstr.Detach();
    return S_OK;
}
STDMETHODIMP CLayerInfo::GetLayerPath(BSTR* url)
{
    if (url == NULL || mLayerInfo == NULL)
    {
        return E_FAIL;
    }
    CComBSTR bstr = mLayerInfo->GetLayerPath().c_str();
    *url = bstr.Detach();
    return S_OK;
}
STDMETHODIMP CLayerInfo::GetEnvelop(DOUBLE* left, DOUBLE* top, DOUBLE* right, DOUBLE* bottom)
{
    if (left == NULL || top == NULL || right == NULL || bottom == NULL || mLayerInfo == NULL)
    {
        return E_FAIL;
    }   
    *left = mLayerInfo->GetLeft();
    *top = mLayerInfo->GetTop();
    *right = mLayerInfo->GetRight();
    *bottom = mLayerInfo->GetBottom();

    return S_OK;
}

STDMETHODIMP CLayerInfo::SetVisible(VARIANT_BOOL bVisible)
{
    if (bVisible == NULL || mLayerInfo == NULL)
    {
        return E_FAIL;
    }

    mLayerInfo->SetVisible((bVisible==VARIANT_TRUE)?true:false);
    return S_OK;
}

STDMETHODIMP CLayerInfo::GetFields(VARIANT* names, VARIANT* types)
{
    if (names == NULL || types == NULL || mLayerInfo == NULL)
    {
        return E_FAIL;
    }

    if (mLayerInfo->GetLayerType() == MODELLAYER)
    {
        VARIANT var; 
        var.vt     = VT_ARRAY | VT_BSTR;
        CModelLayerProperty* modelLayerProp = static_cast<CModelLayerProperty*>(mLayerInfo);
        FeatureSchema & fSchema = modelLayerProp->GetFields();
        int n = fSchema.size();
        if (n == 0)
        {
            var.parray = NULL;  
            *names = var;
            *types = var;
            return S_OK;
        }
        HRESULT hr;
        SAFEARRAY* psaName = SafeArrayCreateVector(VT_BSTR, 0, n);
        SAFEARRAY* psaType = SafeArrayCreateVector(VT_BSTR, 0, n);
        if( psaName == NULL || psaType == NULL)
        {
            return E_FAIL;
        }
        BSTR* pNameArray=NULL;
        BSTR* pTypeArray=NULL;

        if( !SUCCEEDED(hr = SafeArrayAccessData( psaName, (void**)&pNameArray) ) ||  
            !SUCCEEDED(hr = SafeArrayAccessData( psaType, (void**)&pTypeArray) ))
        {
            return hr;
        }
        int i=0;
        for (FeatureSchema::const_iterator itr = fSchema.begin(); itr != fSchema.end(); ++itr, ++i)
        {
            CComBSTR str(itr->first.c_str());
            pNameArray[i] = str.Detach();
            CComBSTR strType(CModelLayerProperty::attributeTypeToString(itr->second).c_str());
            pTypeArray[i] = strType.Detach();
        }

        if (! SUCCEEDED(hr = SafeArrayUnaccessData( psaName ) ) ) 
        {
            return hr;
        }

        var.parray = psaName;  
        *names = var;

        var.parray = psaType;  
        *types = var;
    }
    else
    {
        VARIANT var; 
        var.vt     = VT_ARRAY | VT_I4;
        var.parray = NULL;  
        *names = var;
        *types = var;
        return S_OK;  
    }
    return S_OK;
}