#pragma once
#include <osgEarthFeatures/GeometryUtils>
#include <osgEarthFeatures/Feature>
#include <osgEarthFeatures/FeatureSource>
#include <osgEarthFeatures/FeatureModelSource>
#include <osg/Referenced>
#include <string>
#include <map>

using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace std;
#define MODELLAYER        0x100
#define ELEVATIONLAYER    0x200
#define IMAGELAYER        0x300
class CLayerProperty: public osg::Referenced
{
public:
	CLayerProperty(osgEarth::UID uid, osgEarth::Layer* pLayer);
	virtual ~CLayerProperty(void);
public:


	string GetLayerName(){return mLayerName;}
	string GetLayerPath(){return mLayerPath;}
	double GetLeft() {return mLeft;}
	double GetRight() {return mRight;}
	double GetTop() {return mTop;}
	double GetBottom() {return mBottom;}
    long GetLayerType() {return nLayerType;}
    bool IsVisible(){return mVisible;}
    void SetVisible(bool bVisible);
protected:


protected:
    osgEarth::UID mUid;

	string mLayerName;
	string mLayerPath;

	double mLeft;
	double mRight;
	double mTop;
	double mBottom;
    bool   mVisible;
    long   nLayerType;
    Layer* mLayer;
};

class CModelLayerProperty: public CLayerProperty
{
public:
	CModelLayerProperty(osgEarth::UID uid, osgEarth::ModelLayer* pLayer);
    long GetGeoType(){return mGeoType;}
    unsigned int GetFeatureCount(){return mFeatureCount;}
    static string attributeTypeToString( AttributeType type );
    FeatureSchema& GetFields() {return mFeatureSchema;};
private:
    unsigned int mFeatureCount;
    
	Geometry::Type mGeoType;

    FeatureSchema mFeatureSchema;

};
class CImageLayerProperty: public CLayerProperty
{
public:
	CImageLayerProperty(osgEarth::UID uid, osgEarth::ImageLayer* pLayer);
private:

};
class CElevationLayerProperty: public CLayerProperty
{
public:
	CElevationLayerProperty(osgEarth::UID uid, osgEarth::ElevationLayer* pLayer);
private:

};