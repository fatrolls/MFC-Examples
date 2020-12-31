/* -*-c++-*- OpenSceneGraph Cookbook
 * Chapter 2 Recipe 10
 * Author: Wang Rui <wangray84 at gmail dot com>
*/
#include "StdAfx.h"
#include "Compass.h"
#include <osg/Texture2D>
#include <osgDB/ReadFile>
CCompass::CCompass()
{
}

CCompass::CCompass( const CCompass& copy, osg::CopyOp copyop )
:   osg::Camera(copy, copyop),
    _plateTransform(copy._plateTransform),
    //_needleTransform(copy._needleTransform),
    _mainCamera(copy._mainCamera)
{
}

CCompass::~CCompass()
{
}

void CCompass::traverse( osg::NodeVisitor& nv )
{
    if ( _mainCamera.valid() && nv.getVisitorType()==osg::NodeVisitor::CULL_VISITOR )
    {
        osg::Matrix matrix = _mainCamera->getViewMatrix();
        matrix.setTrans( osg::Vec3() );
        
        osg::Vec3 northVec = osg::Z_AXIS * matrix;
        northVec.z() = 0.0f;
        northVec.normalize();
        
        osg::Vec3 axis = osg::Y_AXIS ^ northVec;
        float angle = atan2(axis.length(), osg::Y_AXIS*northVec);
        axis.normalize();
        osg::Matrix compMat = osg::Matrix::rotate(angle, axis);
        //osg::Matrix compMat = osg::Matrix::identity();
        //compMat *= osg::Matrix::inverse( matrix );
        //compMat *= osg::Matrix::rotate( osg::PI * -0.5, 1.0f, 0.0f, 0.0f );
        //compMat *= osg::Matrix::translate( osg::Vec3( 20.0f, 20.0f, -100.0f ) );
        if ( _plateTransform.valid() )
            _plateTransform->setMatrix( compMat );
        //if ( _needleTransform.valid() )
        //    _needleTransform->setMatrix( compMat );
    }
    
    _plateTransform->accept( nv );
    //_needleTransform->accept( nv );
    osg::Camera::traverse( nv );
}
osg::MatrixTransform* CCompass::createCompassPart( const std::string& image, float radius, float height )
{
    osg::Vec3 center(-radius, -radius, height);
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(
        createTexturedQuadGeometry(center, osg::Vec3(radius*2.0f,0.0f,0.0f), osg::Vec3(0.0f,radius*2.0f,0.0f)) );

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage( osgDB::readImageFile(image) );

    osg::ref_ptr<osg::MatrixTransform> part = new osg::MatrixTransform;
    part->getOrCreateStateSet()->setTextureAttributeAndModes( 0, texture.get() );
    part->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    part->addChild( geode.get() );
    return part.release();
}
void CCompass::Init()
{
    setViewport( 0.0, 0.0, 200.0, 200.0 );
    setProjectionMatrix( osg::Matrixd::ortho(-1.5, 1.5, -1.5, 1.5, -10.0, 10.0) );
    setPlate( createCompassPart("compass.png", 1.5f, -1.0f) );
    //setNeedle( createCompassPart("compass_needle.png", 1.5f, 0.0f) );
    setRenderOrder( osg::Camera::POST_RENDER );
    setClearMask( GL_DEPTH_BUFFER_BIT );
    setAllowEventFocus( false );
    setReferenceFrame( osg::Transform::ABSOLUTE_RF );
    getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
    getOrCreateStateSet()->setMode( GL_DEPTH_TEST , osg::StateAttribute::OFF ) ;

    // Need to make sure this geometry is draw last. RenderBins are handled
    // in numerical order so set bin number to 99
    getOrCreateStateSet()->setRenderBinDetails( 99, "RenderBin" ) ;
}
