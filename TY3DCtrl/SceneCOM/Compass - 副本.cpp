///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Jeff Conner
//
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Compass.h"





// #include "Usul/CommandLine/Arguments.h"

#include "osgUtil/CullVisitor"

#include "osgUtil/CullVisitor"
#include "osgDB/ReadFile"
#include "osg/MatrixTransform"
#include "osg/Math"
#include "osg/Texture2D"
#include "osg/Image"
#include "osg/Geometry"
#include "osg/Geode"


///////////////////////////////////////////////////////////////////////////////
//
//  Update Callback for hiding and showing the compass
//
///////////////////////////////////////////////////////////////////////////////

class CompassAnimationCallback : public osg::NodeCallback
{
public:
   
   CompassAnimationCallback(CCompass* compass, float start, float end, float step)
      {
         _start = start;
         _end = end;
         _step = step;
         _compass = compass;
      }
   
   virtual void operator() (osg::Node* node, osg::NodeVisitor* nv)
      {
         osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);    
         if(0L != transform)
         {
            if(_compass->isAnimating())
            {
               if(_compass->isVisible())
               {
                  if (_start < _end)
                  {
                     _start += _step;
                     if(_start > _end) _start = _end;
                     transform->setMatrix(osg::Matrix::scale(_start,_start,_start));
                     
                  }
                  else
                  {
                     _compass->setAnimation(false);
                  }
               }
               else
               {
                  if (_start > _end)
                  {
                     _start -= _step;
                     if(_start < _end) _start = _end;
                     transform->setMatrix(osg::Matrix::scale(_start,_start,_start));
                     
                  }
                  else
                  {
                     _compass->setAnimation(false);
                  }
               }
            }
         }   
         traverse(node,nv);            
         
      }
   
protected:
   
   osg::ref_ptr<CCompass> _compass;
   float               _angular_velocity;
   float				_start;
   float				_end;
   float				_step; 
};


///////////////////////////////////////////////////////////////////////////////
//
//  Cull Callback for rotating the compass based on the current view matrix
//
///////////////////////////////////////////////////////////////////////////////

class CompassOrientationCallback : public osg::NodeCallback
{
public:
   CompassOrientationCallback(CCompass *compass) :		
      _scale(.07f)		
      {
         _compass = compass;
         _pos = (osg::Vec3(_scale * 4.0f, _scale * -3.0f, -1.0f));
         theHeadingFlag = true;
         theRollFlag = true;
         thePitchFlag = true;
      }
   virtual void operator()(osg::Node *node, osg::NodeVisitor *nv)
      {
         osgUtil::CullVisitor *cv = dynamic_cast<osgUtil::CullVisitor *>(nv);
         if( 0L != cv)
         {
            osg::MatrixTransform *tx = dynamic_cast<osg::MatrixTransform *>(node);
            if( 0L != tx )
            {
               double h = theHeadingFlag?_compass->heading():0.0;
               double p = thePitchFlag? _compass->pitch():0.0;
               double r = theRollFlag?_compass->roll():0.0;

               tx->setMatrix ( osg::Matrix::scale ( _compass->scale(),
                                                    _compass->scale(),
                                                    _compass->scale()) * 
                               osg::Matrix::rotate ( osg::inDegrees ( h ),
                                                     0.0f, 0.0f, 1.0f ) *
                               osg::Matrix::rotate ( osg::inDegrees ( p ),
                                                     1.0f, 0.0f, 0.0f ) *
                               osg::Matrix::rotate ( osg::inDegrees ( r ),
                                                     0.0f, 0.0f, 1.0f ) * // make it about z as well
                               osg::Matrix::translate ( _compass->position() ) );
            }
         }
         traverse( node, nv );
      }
   void setFlags(bool heading, bool pitch, bool roll)
      {
         theHeadingFlag = heading;
         thePitchFlag = pitch;
         theRollFlag = roll;
      }
protected:
   bool theHeadingFlag;
   bool theRollFlag;
   bool thePitchFlag;

   CCompass* _compass;
   osg::Vec3 _pos;
   float _scale;
}; 


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor/Destructor
//
///////////////////////////////////////////////////////////////////////////////

CCompass::CCompass():
  _scale ( .07f ),
  _numslices ( 32 ),
  _radius ( .8 ),
  theCompassGroup ( new osg::Group() ),
  _showOrHideCompass ( true ),
  _animating ( false ),
  _rotateByView ( true ),
  _heading ( 0.0f ),
  _pitch ( 0.0f ),
  _roll(0.0f)
{
   theCommonColorArray = new osg::Vec4Array();
   theCommonColorArray->push_back(osg::Vec4(1.0,1.0,1.0,.5));
   //ossimFilename defaultTop    = ossimEnvironmentUtility::instance()->getUserOssimSupportDir();
   //defaultTop  = defaultTop.dirCat("images");
 
   this->setPositionByPercentage( 1.0f, 0.0f );
 
   buildCompass();
}

CCompass::~CCompass(){}



///////////////////////////////////////////////////////////////////////////////
//
//  Return the state of the compass: visible or not
//
///////////////////////////////////////////////////////////////////////////////

bool CCompass::isVisible()
{
   return _showOrHideCompass;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the texture filename for the compass
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::setCompassTexture(const std::string& fn)
{
   theCompassFilename = fn;
   theCompassObject = this->buildCompassObject(theCompassFilename);
}

//void ossimPlanetCompass::setInterior(const ossimFilename& fn)
//{
//   theInterior = fn;
//   theCompassInteriorObject = this->buildCompassObject(theInterior);
//}
//void ossimPlanetCompass::setInterior(const ossimFilename& fn)
//{
//   theCompassFilename = fn;
//   theCompassObject = this->buildCompassObject(theCompassFilename);
//}

//void ossimPlanetCompass::setCompassTexture(const ossimFilename& ring,
//                                           const ossimFilename& interior)
//{
//   setRing(ring);
//   setInterior(interior);
//}

void CCompass::traverse(osg::NodeVisitor& nv)
{
   switch(nv.getVisitorType())
   {
      case osg::NodeVisitor::UPDATE_VISITOR:
      {
         
         break;
      }
      default:
      {
         break;
      }
   }
   if(theCompassGroup.valid())
   {
      theCompassGroup->accept(nv);
   }
   osg::Node::traverse(nv);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Get the heading of the compass
//
///////////////////////////////////////////////////////////////////////////////

float CCompass::heading()
{
  return _heading;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Set the heading of the compass
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::setHeading(float r)
{
  _heading = r;
}

float CCompass::pitch ( )
{
   return _pitch;
}

void CCompass::setPitch ( float p )
{
   _pitch = p;
}

float CCompass::roll ( )
{
   return _roll;
}

void CCompass::setRoll(float r)
{
   _roll = r;
}
///////////////////////////////////////////////////////////////////////////////
//
//  Set the heading of the compass based on a ( x = lon, y = lat ) position 
//  and a ( x = lon, y = lat ) north.
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::setHeadingRelativeToNorth(const osg::Vec2& north, const osg::Vec2& pos)
{
  //FILE* debug = fopen ("C:/debug.txt","a");

  osg::Vec2f p ( pos.x(), pos.y() );

  /*if( p.x() > 180 )
    p.set( p.x() - 180.0f , p.y() );*/
 
  float theta =  atan ( ( north.y() - p.y() ) / ( north.x() -  p.x() ) );

  //fprintf(debug,"N.x=%f , N.y=%f\tP.x=%f(%f) , P.y=%f\ttheta=%f\n",north.x(),north.y(),pos.x(),p.x(),p.y(),(theta * 180 / osg::PI) );
  //fclose(debug);
  this->setHeading( osg::RadiansToDegrees( theta ) );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Get the position on the screen of the compass
//
///////////////////////////////////////////////////////////////////////////////


const osg::Vec3& CCompass::position()
{
  return _pos;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the position on the screen of the compass by absolute postion
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::setPosition(const osg::Vec3& p)
{
  _pos = p;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the position on the screen of the compass by percentage of screen
//  Pass in a float value between 0 and 1;
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::setPositionByPercentage ( float width, float height )
{
  float w = ( _scale *  width * 8.0f ) - ( 4.0f * _scale );
  float h = ( _scale *  height * 6.0f ) - ( 3.0f * _scale );

  _pos = osg::Vec3(w, h, -1.0f);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Get the xyz scale value of the compass
//
///////////////////////////////////////////////////////////////////////////////

float CCompass::scale()
{
  return _scale;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the xyz scale value of the compass
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::setScale(float s)
{
  _scale = s;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return true if the compass is in the act of showing or hiding
//
///////////////////////////////////////////////////////////////////////////////

bool CCompass::isAnimating()
{
  return _animating;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the animation state to trigger a show or hide.
//  Use showCompass() or hideCompass() methods.
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::setAnimation(bool state)
{
  _animating = state;
}


///////////////////////////////////////////////////////////////////////////////
//  true to use the view matrix
//  false to use "by angle degree"
//		- set using "setRotation" method.
//		- call "updateCompass" after changing angle values to rebuild 
//		  the compass
///////////////////////////////////////////////////////////////////////////////

void CCompass::setRotateByViewMatrix(bool m)
{
  _rotateByView = m;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Rebuilds compass based upon animation show/hide parameters.
//	Call this method to rebuild after changing parameters in a set method
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::updateCompass()
{
	if(_showOrHideCompass)
		buildCompass();
	if(!_showOrHideCompass && _animating)
		buildCompass();
	if(!_showOrHideCompass && !_animating)
		_emptyCompass();
}

///////////////////////////////////////////////////////////////////////////////
//
//  Build a triangle fan object to use as a compass face
//
///////////////////////////////////////////////////////////////////////////////

osg::Geode* CCompass::buildTriangleFan(const std::string& tex, float zoff, unsigned int render_level, const osg::Vec3& n)
{
   osg::ref_ptr< osg::Geode > geode ( new osg::Geode() );
   osg::ref_ptr< osg::StateSet > stateset ( new osg::StateSet() );
   osg::ref_ptr< osg::Image > image;

   if(!tex.empty())
   {
      image = osgDB::readImageFile( tex );
   }
   if ( image.get() )
   {
      osg::ref_ptr< osg::Texture2D > texture ( new osg::Texture2D() ); 
      texture->setImage ( image.get() );
      stateset->setTextureAttributeAndModes ( 0, texture.get(), osg::StateAttribute::ON | osg::StateAttribute::PROTECTED );
      stateset->setMode ( GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED );
      stateset->setMode ( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );    
      stateset->setRenderingHint ( osg::StateSet::TRANSPARENT_BIN );
      stateset->setRenderBinDetails ( render_level, "RenderBin" );
      
   }
   
   osg::ref_ptr< osg::Vec3Array > fan ( new osg::Vec3Array() );
   osg::ref_ptr< osg::Vec2Array > fan_tex ( new osg::Vec2Array() );
   
   fan->reserve( _numslices +1 );
   fan_tex->reserve( _numslices +1 );
   
   fan->push_back( osg::Vec3 ( 0.0f, 0.0f, zoff ) );
   fan_tex->push_back( osg::Vec2 ( 0.5f, 0.5f ) );
   
   for ( unsigned int x = 0; x < _numslices + 1; ++x )
   {	
      float angle =  float ( x ) * ( ( 2 * osg::PI ) / _numslices );
      fan->push_back ( osg::Vec3 ( _radius * ( cos( angle ) ), _radius * ( sin ( angle ) ), zoff ) );
      fan_tex->push_back(osg::Vec2(0.5f + (0.5f * ( cos( angle ) ) ),0.5f +( 0.5f * ( sin ( angle ) ) ) ));
   }
   osg::ref_ptr< osg::Geometry > geometry ( new osg::Geometry() ); 
   osg::ref_ptr< osg::Vec3Array > normal = new osg::Vec3Array;
//    osg::ref_ptr< osg::Vec4Array > color ( new osg::Vec4Array() );
//    color->push_back ( osg::Vec4 ( 1.0f, 1.0f, 1.0f, .5f ) );
   geometry->setColorArray ( theCommonColorArray.get() );
   geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
   normal->push_back ( n );
   
   geometry->setVertexArray ( fan.get() );
   
   geometry->setTexCoordArray ( 0, fan_tex.get() );
   
   geometry->setNormalArray ( normal.get() );
   
   geometry->setNormalBinding ( osg::Geometry::BIND_OVERALL );
   
   geometry->addPrimitiveSet ( new osg::DrawArrays ( osg::PrimitiveSet::TRIANGLE_FAN, 0, fan->size() ) );
   
   geometry->setStateSet ( stateset.get() );
   
   geode->setStateSet ( stateset.get() );
   
   geode->addDrawable ( geometry.get() );
   
   return geode.release();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Build the acutal compass object, consisting of 2 textured triangle fans
//
///////////////////////////////////////////////////////////////////////////////

osg::Node* CCompass::buildCompassObject(const std::string& location)
{
  osg::ref_ptr < osg::Group > group ( new osg::Group() );
  group->addChild ( this->buildTriangleFan ( location,
                                             0.0f,
                                             1001,
                                             osg::Vec3 ( 0.0f, 0.0f, 1.0f ) ) );
//   group->addChild ( this->_buildTriangleFan ( _botTexfn, -0.05f, 1000, osg::Vec3 ( 0.0f, 0.0f, 1.0f ) ) );
  return group.release();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set matrix transforms for the compass.  Add the Cull and update callbacks
//	for rotation and animation.
//
///////////////////////////////////////////////////////////////////////////////

osg::Group* CCompass::initCompass()
{
   osg::ref_ptr<osg::Group> group = new osg::Group;
   osg::ref_ptr < osg::MatrixTransform > rotRing ( new osg::MatrixTransform() );
   osg::ref_ptr < osg::MatrixTransform > rotInterior ( new osg::MatrixTransform() );
   osg::ref_ptr < osg::MatrixTransform > animRing ( new osg::MatrixTransform() );
   osg::ref_ptr < osg::MatrixTransform > animInterior ( new osg::MatrixTransform() );
   osg::ref_ptr < CompassOrientationCallback > rotation_callback_ring ( new CompassOrientationCallback ( this ) );
//   osg::ref_ptr < CompassOrientationCallback > rotation_callback_interior ( new CompassOrientationCallback ( this ) );

   rotation_callback_ring->setFlags(true, true, false);
   //rotation_callback_interior->setFlags(false, true, true);
   CompassAnimationCallback* animCallback = new CompassAnimationCallback ( this,
                                                                          _animationStart,
                                                                          _animationEnd,
                                                                          _animationStep );
   animRing->setUpdateCallback ( animCallback );
   animInterior->setUpdateCallback ( animCallback );
   rotRing->setCullCallback ( rotation_callback_ring.get() );
  // rotInterior->setCullCallback ( rotation_callback_interior.get() );
   
   rotRing->setReferenceFrame ( osg::Transform::ABSOLUTE_RF );
   //rotInterior->setReferenceFrame ( osg::Transform::ABSOLUTE_RF );

   animRing->addChild ( theCompassObject.get() );
  // animInterior->addChild ( theCompassInteriorObject.get() );
   rotRing->addChild ( animRing.get() );
   //rotInterior->addChild ( animInterior.get() );
  // group->addChild(rotInterior.get());
   group->addChild(rotRing.get());
  
   return group.release();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Remove all children from the compass group.  Called when compass is
//  "hidden"
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::_emptyCompass()
{
   theCompassGroup->removeChildren ( 0, theCompassGroup->getNumChildren() );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Build the compass.
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::buildCompass()
{
   osg::ref_ptr < osg::Group > group ( new osg::Group() );
//    osg::ref_ptr < osg::Node > geode = _buildCompassObject();
   
   osg::ref_ptr < osg::StateSet > ss ( theCompassGroup->getOrCreateStateSet() );
   ss->setRenderBinDetails ( 1000, "RenderBin" );
   ss->setMode ( GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );
   ss->setMode ( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::INHERIT );
   
   theCompassGroup->removeChildren ( 0, theCompassGroup->getNumChildren() ); 
   theCompassGroup->addChild ( initCompass (  ) );	
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set parameters to display the "show" animation.
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::_showCompass()
{
   _animationStart = 0.0f;
   _animationEnd = 1.0f; 
   _animationStep = 1.0f / 20.0f;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set parameters to display the "hide" animation.
//
///////////////////////////////////////////////////////////////////////////////

void CCompass::_hideCompass()
{
	_animationStart = 1.0f;
	_animationEnd = 0.0f; 
	_animationStep = -1 * (1.0f / 20.0f);
}
