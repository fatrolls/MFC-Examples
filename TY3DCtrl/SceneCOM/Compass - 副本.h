
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Jeff Conner
//
///////////////////////////////////////////////////////////////////////////////

#ifndef ossimPlanetCompass_HEADER
#define ossimPlanetCompass_HEADER

#include <osg/Group>
#include <string>



namespace osg { class MatrixTransform; class Geode; }


class  CCompass : public osg::Node
{
public:
   CCompass( );
   
   
   void setCompassTexture ( const std::string& fn );
 
   virtual void traverse(osg::NodeVisitor& nv);
   
   bool isAnimating ( );
   void setAnimation(bool state);
   
   float heading ( );
   void setHeading ( float r );
   void setHeadingRelativeToNorth(const osg::Vec2& north, const osg::Vec2& pos);
   
   float pitch ( );
   void setPitch ( float p );

   
   float roll ( );
   void setRoll(float r);
   
   void setRotateByViewMatrix ( bool m );
   
   const osg::Vec3& position ( );
   void setPosition ( const osg::Vec3& p );
   void setPositionByPercentage ( float width, float height );
   
   float scale ( );
   void  setScale ( float s );
   
   bool isVisible ( );
   
   void buildCompass ( );
   
   
   void updateCompass ( );
   
protected:
        
        virtual ~CCompass ( );
        
	osg::Node* buildCompassObject ( const std::string& location);
	osg::Group*  initCompass ( );
	
	void _showCompass ( );
	void _hideCompass ( );
	void _emptyCompass ( );
        osg::Geode* buildTriangleFan ( const std::string& tex,
                                       float zoff,
                                       unsigned int render_level,
                                       const osg::Vec3& n );
	
private:
        
	osg::Vec3 _pos;
	float _scale;
    std::string theCompassFilename;
 
	unsigned int _numslices;
	float _radius;
	osg::ref_ptr<osg::Group> theCompassGroup;
	osg::ref_ptr<osg::Node> theCompassObject;
 
	bool _showOrHideCompass, _animating;
	bool _rotateByView;
	float _animationStart, _animationEnd, _animationStep;
	
	float _heading, _pitch, _roll;
        osg::ref_ptr< osg::Vec4Array > theCommonColorArray;
   };

#endif // ossimPlanetCompass_HEADER
