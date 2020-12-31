/* -*-c++-*- OpenSceneGraph Cookbook
 * Chapter 2 Recipe 10
 * Author: Wang Rui <wangray84 at gmail dot com>
*/

#ifndef H_COOKBOOK_CH2_COMPASS
#define H_COOKBOOK_CH2_COMPASS

#include <osg/MatrixTransform>
#include <osg/Camera>
#include <osg/Geode>
#include <osg/Geometry>

class CCompass : public osg::Camera
{
public:
    CCompass();
    CCompass( const CCompass& copy, osg::CopyOp copyop=osg::CopyOp::SHALLOW_COPY );
    META_Node( osg, CCompass );
    
    /** Set the plate of the compass inside the camera projection range. */
    void setPlate( osg::MatrixTransform* plate ) { _plateTransform = plate; }
    osg::MatrixTransform* getPlate() { return _plateTransform.get(); }
    const osg::MatrixTransform* getPlate() const { return _plateTransform.get(); }
    
    /** Set the needle of the compass inside the camera projection range. */
    //void setNeedle( osg::MatrixTransform* needle ) { _needleTransform = needle; }
    //osg::MatrixTransform* getNeedle() { return _needleTransform.get(); }
    //const osg::MatrixTransform* getNeedle() const { return _needleTransform.get(); }
    
    /** Set the main camera for the compass; otherwise there will be no effect. */
    void setMainCamera( osg::Camera* camera ) { _mainCamera = camera; }
    osg::Camera* getMainCamera() { return _mainCamera.get(); }
    const osg::Camera* getMainCamera() const { return _mainCamera.get(); }
    void Init();

    virtual void traverse( osg::NodeVisitor& nv );
    
protected:
    osg::MatrixTransform* createCompassPart( const std::string& image, float radius, float height );
    virtual ~CCompass();
    
    osg::ref_ptr<osg::MatrixTransform> _plateTransform;
    //osg::ref_ptr<osg::MatrixTransform> _needleTransform;
    osg::observer_ptr<osg::Camera> _mainCamera;
};

 

#endif
