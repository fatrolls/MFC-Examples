// SceneMap.cpp : Implementation of CSceneMap

#include "stdafx.h"
#include "SceneMap.h"

#include "ConfigOpt.h";
#include <osgEarthFeatures/FeatureModelSource>
#include <osgEarthFeatures/FeatureSource>
#include "LayerProperty.h"
#include "LayerInfo.h"
// CSceneMap
STDMETHODIMP CSceneMap::GetModelLayerInfo(LONG uid, ILayerInfo** ppInfo)
{
    if (ppInfo == NULL || mMap == NULL)
    {
        return E_FAIL;
    }
    CLayerInfo* pInfo = new CComObject<CLayerInfo>;
    pInfo->AddRef();
 
	osgEarth::ModelLayer* pLayer = mMap->getModelLayerByUID(uid);
   
	if (pLayer != NULL)
	{
		CModelLayerProperty* layerInfo = new CModelLayerProperty(uid, pLayer);
		pInfo->Attach(layerInfo);
        *ppInfo = pInfo;
	}
    else
    {
        return E_FAIL;
    }
 
    return S_OK;
}
STDMETHODIMP CSceneMap::GetElevationLayerInfo(LONG uid, ILayerInfo** ppInfo)
{
    if (ppInfo == NULL || mMap == NULL)
    {
        return E_FAIL;
    }
    CLayerInfo* pInfo = new CComObject<CLayerInfo>;
    pInfo->AddRef();
 
	osgEarth::ElevationLayer* pLayer = mMap->getElevationLayerByUID(uid);
	if (pLayer != NULL)
	{
		CElevationLayerProperty* layerInfo = new CElevationLayerProperty(uid, pLayer);
		pInfo->Attach(layerInfo);
        *ppInfo = pInfo;
	}
    else
    {
        return E_FAIL;
    }
 
    return S_OK;
}
STDMETHODIMP CSceneMap::GetImageLayerInfo(LONG uid, ILayerInfo** ppInfo)
{
    if (ppInfo == NULL || mMap == NULL)
    {
        return E_FAIL;
    }
    CLayerInfo* pInfo = new CComObject<CLayerInfo>;
    pInfo->AddRef();
 
	osgEarth::ImageLayer* pLayer = mMap->getImageLayerByUID(uid);
	if (pLayer != NULL)
	{
		CImageLayerProperty* layerInfo = new CImageLayerProperty(uid, pLayer);
		pInfo->Attach(layerInfo);
        *ppInfo = pInfo;
	}
    else
    {
        return E_FAIL;
    }  
 
    return S_OK;
}
STDMETHODIMP CSceneMap::AddLayer(IConfigOpt* conf)
{
    if (conf == NULL || mMap == NULL)
    {
        return E_FAIL;
    }
    CConfigOpt* opt = (CConfigOpt*)conf;
    switch (opt->GetType())
    {
    case IMAGELAYEROPT:
        {
            Config* layerDriverConf = opt->GetConfig();
            layerDriverConf->add( "default_tile_size", "256" );

            ImageLayerOptions layerOpt( *layerDriverConf );
            layerOpt.name() = layerDriverConf->value("name");
            layerOpt.driver() = TileSourceOptions( *layerDriverConf );

            mMap->addImageLayer( new osgEarth::ImageLayer(layerOpt) );
        }
        break;
    case MODELLAYEROPT:
        {
            Config* layerDriverConf = opt->GetConfig();

            ModelLayerOptions layerOpt( *layerDriverConf );
            layerOpt.name() = layerDriverConf->value( "name" );
            layerOpt.driver() = ModelSourceOptions( *layerDriverConf );
            FeatureSourceOptions fso;
            layerDriverConf->getObjIfSet( "features", fso );
            if (!fso.empty())
            {
                osg::ref_ptr< FeatureSource > features = FeatureSourceFactory::create(fso);
                features->initialize();
                features->getFeatureProfile();
            }
            mMap->addModelLayer( new osgEarth::ModelLayer(layerOpt) );
        }
        break;
    case ELEVATIONLAYEROPT:
        {
            Config* layerDriverConf = opt->GetConfig();
            layerDriverConf->add( "default_tile_size", "16" );

            ElevationLayerOptions layerOpt( *layerDriverConf );
            layerOpt.name() = layerDriverConf->value( "name" );
            layerOpt.driver() = TileSourceOptions( *layerDriverConf );

            mMap->addElevationLayer( new osgEarth::ElevationLayer(layerOpt) );
        }
        break;
    default:
        return E_FAIL;
    }
    return S_OK;
}

//STDMETHODIMP CSceneMap::AddModelLayer(IModelLayer* pLayer)
//{
//    return S_OK;
//}
//STDMETHODIMP CSceneMap::AddElevationLayer(IElevationLayer* pLayer)
//{
//    return S_OK;
//}
//STDMETHODIMP CSceneMap::AddImageLayer(IImageLayer* pLayer)
//{
//    return S_OK;
//}

STDMETHODIMP CSceneMap::RemoveModelLayer(LONG uid)
{
    if (mMap == NULL)
    {
        return E_FAIL;
    }
    osgEarth::ModelLayer* pLayer = mMap->getModelLayerByUID(uid);
    if (pLayer)
    {
        mMap->removeModelLayer(pLayer);
    }
    else
    {
        return E_FAIL;
    }
    return S_OK;
}
STDMETHODIMP CSceneMap::RemoveElevationLayer(LONG uid)
{
    if (mMap == NULL)
    {
        return E_FAIL;
    }
    osgEarth::ElevationLayer* pLayer = mMap->getElevationLayerByUID(uid);
    if (pLayer)
    {
        mMap->removeElevationLayer(pLayer);
    }
    else
    {
        return E_FAIL;
    }
    return S_OK;
}
STDMETHODIMP CSceneMap::RemoveImageLayer(LONG uid)
{
    if (mMap == NULL)
    {
        return E_FAIL;
    }
    osgEarth::ImageLayer* pLayer = mMap->getImageLayerByUID(uid);
    if (pLayer)
    {
        mMap->removeImageLayer(pLayer);
    }
    else
    {
        return E_FAIL;
    }
    return S_OK;
}

STDMETHODIMP CSceneMap::GetModelLayerIds(VARIANT* uids)
{
    if (uids == NULL || mMap == NULL)
    {
        return E_FAIL;
    }
    int n = mMap->getNumModelLayers();
    if (n == 0)
    {
        VARIANT var; 
        var.vt     = VT_ARRAY | VT_I4;
        var.parray = NULL;  
        *uids = var;
        return S_OK;
    }
    HRESULT hr;
    SAFEARRAY* psa = SafeArrayCreateVector(VT_I4, 0, n);
    if( psa == NULL)
    {
        return E_FAIL;
    }
    LONG* plongArray=NULL;
    if( !SUCCEEDED(hr = SafeArrayAccessData( psa, (void**)&plongArray) ))
    {
        return hr;
    }
 

    osgEarth::ModelLayerVector moderLayerVector;
	mMap->getModelLayers(moderLayerVector);
 
	osgEarth::ModelLayerVector::iterator iter = moderLayerVector.begin();
	for (int i=0; iter != moderLayerVector.end(); ++iter, ++i)
	{
		osgEarth::UID uid = (*iter)->getUID();
        plongArray[i] = uid;

    }
 

    if (! SUCCEEDED(hr = SafeArrayUnaccessData( psa ) ) ) 
    {
        return hr;
    }
    VARIANT var; 
    var.vt     = VT_ARRAY | VT_I4;
    var.parray = psa;  
    *uids = var;
    return S_OK;
}
STDMETHODIMP CSceneMap::GetElevationLayerIds(VARIANT* uids)
{
    if (uids == NULL || mMap == NULL)
    {
        return E_FAIL;
    }
    int n = mMap->getNumElevationLayers();
    if (n == 0)
    {
        VARIANT var; 
        var.vt     = VT_ARRAY | VT_I4;
        var.parray = NULL;  
        *uids = var;
        return S_OK;
    }
    HRESULT hr;
    SAFEARRAY* psa = SafeArrayCreateVector(VT_I4, 0, n);
    if( psa == NULL)
    {
        return E_FAIL;
    }
    LONG* plongArray=NULL;
    if( !SUCCEEDED(hr = SafeArrayAccessData( psa, (void**)&plongArray) ))
    {
        return hr;
    }
 

    osgEarth::ElevationLayerVector elevationLayerVector;
	mMap->getElevationLayers(elevationLayerVector);
 
	osgEarth::ElevationLayerVector::iterator iter = elevationLayerVector.begin();
	for (int i=0; iter != elevationLayerVector.end(); ++iter, ++i)
	{
		osgEarth::UID uid = (*iter)->getUID();
        plongArray[i] = uid;

    }
 

    if (! SUCCEEDED(hr = SafeArrayUnaccessData( psa ) ) ) 
    {
        return hr;
    }
    VARIANT var; 
    var.vt     = VT_ARRAY | VT_I4;
    var.parray = psa;  
    *uids = var;
    return S_OK;
}
STDMETHODIMP CSceneMap::GetImageLayerIds(VARIANT* uids)
{
   if (uids == NULL || mMap == NULL)
    {
        return E_FAIL;
    }
    int n = mMap->getNumImageLayers();
    if (n == 0)
    {
        VARIANT var; 
        var.vt     = VT_ARRAY | VT_I4;
        var.parray = NULL;  
        *uids = var;
        return S_OK;
    }
    HRESULT hr;
    SAFEARRAY* psa = SafeArrayCreateVector(VT_I4, 0, n);
    if( psa == NULL)
    {
        return E_FAIL;
    }
    LONG* plongArray=NULL;
    if( !SUCCEEDED(hr = SafeArrayAccessData( psa, (void**)&plongArray) ))
    {
        return hr;
    }
 

    osgEarth::ImageLayerVector imageLayerVector;
	mMap->getImageLayers(imageLayerVector);
 
	osgEarth::ImageLayerVector::iterator iter = imageLayerVector.begin();
	for (int i=0; iter != imageLayerVector.end(); ++iter, ++i)
	{
		osgEarth::UID uid = (*iter)->getUID();
        plongArray[i] = uid;

    }
 

    if (! SUCCEEDED(hr = SafeArrayUnaccessData( psa ) ) ) 
    {
        return hr;
    }
    VARIANT var; 
    var.vt     = VT_ARRAY | VT_I4;
    var.parray = psa;  
    *uids = var;
    return S_OK;
}

