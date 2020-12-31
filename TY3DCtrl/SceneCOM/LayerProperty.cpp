#include "stdafx.h"
#include "LayerProperty.h"


CLayerProperty::CLayerProperty(osgEarth::UID uid, osgEarth::Layer* pLayer):
	mLeft(0.0),
	mRight(0.0),
	mTop(0.0),
	mBottom(0.0),
    mUid(uid),
    mLayer(pLayer)
{
    nLayerType = 0;  
}


CLayerProperty::~CLayerProperty(void)
{
}
void CLayerProperty::SetVisible(bool bVisible)
{
    if (nLayerType & MODELLAYER)
    {
        osgEarth::ModelLayer* pLayer = dynamic_cast<osgEarth::ModelLayer*> (mLayer);
        pLayer->setVisible(bVisible);
    }else// if ((nLayerType & ELEVATIONLAYER) || (nLayerType & IMAGELAYER))
    {
        osgEarth::TerrainLayer* pLayer = dynamic_cast<osgEarth::TerrainLayer*> (mLayer);
        pLayer->setVisible(bVisible);
    }
}

CModelLayerProperty::CModelLayerProperty(osgEarth::UID uid, osgEarth::ModelLayer* pLayer):
    CLayerProperty(uid,pLayer),
	mFeatureCount(0),
	mGeoType(Geometry::Type::TYPE_UNKNOWN)
{

    mVisible = pLayer->getVisible();

    mLayerName = pLayer->getName();
    FeatureModelSource* fmsrc = dynamic_cast<FeatureModelSource*>(pLayer->getModelSource());
    if (fmsrc)
    {
        FeatureSource* fsrc = fmsrc->getFeatureSource();
        if (fsrc)
        {
            mFeatureCount = fsrc->getFeatureCount();
            mGeoType = fsrc->getGeometryType();
            mFeatureSchema = fsrc->getSchema();

            mLayerPath = fsrc->getFeatureSourceOptions().url()->full();

            mLeft = fsrc->getFeatureProfile()->getExtent().xMin();
            mRight = fsrc->getFeatureProfile()->getExtent().xMax();
            mTop = fsrc->getFeatureProfile()->getExtent().yMax();
            mBottom = fsrc->getFeatureProfile()->getExtent().yMin();

        }
    }

    nLayerType |= MODELLAYER; 
}


std::string CModelLayerProperty::attributeTypeToString( AttributeType type )
{
	switch (type)
	{
	case ATTRTYPE_BOOL: return "Boolean";
	case ATTRTYPE_DOUBLE: return "Double";
	case ATTRTYPE_INT: return "Integer";
	case ATTRTYPE_STRING: return "String";
	default:  return "Unspecified";
	}
}

//void CModelLayerProperty::AnaySchema()
//{
//	for (FeatureSchema::const_iterator itr = mFeatureSchema.begin(); itr != mFeatureSchema.end(); ++itr)
//	{
//		mFields.insert(make_pair(itr->first, attributeTypeToString(itr->second)));
//	}
//}

CElevationLayerProperty::CElevationLayerProperty(osgEarth::UID uid, osgEarth::ElevationLayer* pLayer):
    CLayerProperty(uid,pLayer)
{
    mVisible = pLayer->getVisible();
 
	//mLayerPath = pLayer->getTileSource()->getOptions();

	mLayerName = pLayer->getName();
 
    nLayerType |= ELEVATIONLAYER; 
}


CImageLayerProperty::CImageLayerProperty(osgEarth::UID uid, osgEarth::ImageLayer* pLayer):
    CLayerProperty(uid,pLayer)
{
    mVisible = pLayer->getVisible();
 
	//mLayerPath = pLayer->getTileSource()->getOptions();

	mLayerName = pLayer->getName();
 
    nLayerType |= IMAGELAYER; 
	 
}

