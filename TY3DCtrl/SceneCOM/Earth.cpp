#include "StdAfx.h"
#include "Earth.h"



#include <osg/ImageStream>

#include <osgDB/FileNameUtils>
#include <osgEarth/ElevationQuery>
#include <osgEarth/GeoMath>
//#include <osgEarth/GeoTransform>
#include <osgEarth/ImageUtils>
#include <osgEarth/Registry>
#include <osgEarth/TerrainEngineNode>

#include <osgEarthFeatures/FeatureSource>
#include <osgEarthFeatures/FeatureModelSource>

#include <osgEarthSymbology/Geometry>
#include <osgEarthSymbology/GeometryFactory>
#include <osgEarthSymbology/GeometryRasterizer>

#include <osgEarthUtil/AnnotationEvents>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthUtil/ContourMap>

#include <osgEarthUtil/FeatureManipTool>
#include <osgEarthUtil/FeatureQueryTool>

#include <osgEarthUtil/LatLongFormatter>
#include <osgEarthUtil/LinearLineOfSight>
#include <osgEarthUtil/LODBlending>
//#include <osgEarthUtil/LogarithmicDepthBuffer>
#include <osgEarthUtil/MeasureTool>
#include <osgEarthUtil/MGRSFormatter>
#include <osgEarthUtil/MGRSGraticule>
#include <osgEarthUtil/MouseCoordsTool>
#include <osgEarthUtil/NormalMap>
#include <osgEarthUtil/ObjectLocator>
#include <osgEarthUtil/RadialLineOfSight>

#include <osgEarthUtil/TerrainProfile>
#include <osgEarthUtil/UTMGraticule>
#include <osgEarthUtil/VerticalScale>
#include <osgViewer/api/Win32/GraphicsWindowWin32>




using namespace osgEarth::Features;
using namespace osgEarth::Symbology;

using namespace osgEarth::Annotation;

// 构造函数获取上一级窗口句柄
CEarth::CEarth(HWND hWnd)   
    :mInit(false),m_hWnd(hWnd)

{
    mViewer = NULL;

}


CEarth::~CEarth()
{   
    mViewer->setDone(true);
    Sleep(1000);
    mViewer->stopThreading();

    delete mViewer;


}

void CEarth::InitOSG(std::string modelname)
{
    // Store the name of the project to load
    mProjectName = modelname;
    if (!mInit)
    {
        // Init different parts of OSG
        InitManipulators();
        InitSceneGraph();
        InitCameraConfig();
        createControls();
        createCompass();
        mInit = true;
    }
    if (0)
    {
        mEn->setHomeViewpoint(Viewpoint( "Mt Rainier", osg::Vec3d( -121.769846, 46.840866, 0.0 ), 0.0, -90, 45000 ));
    }
 

}

void CEarth::InitManipulators(void)
{
    // Create a trackball manipulator
    mEn = new osgEarth::Util::EarthManipulator();

    // Create a Manipulator Switcher
    mKeyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

    // Add our trackball manipulator to the switcher
    mKeyswitchManipulator->addMatrixManipulator( '1', "Trackball", mEn.get());

    // Init the switcher to the first manipulator (in this case the only manipulator)
    mKeyswitchManipulator->selectMatrixManipulator(0);  // Zero based index Value
}

void CEarth::InitSceneGraph(void)
{
    mRoot  = new osg::Group;

    // Load the Node from the project name
    //osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(mProjectName);

    //if (!node.valid())
    //{
    //    return;
    //}

    //mMapNode = osgEarth::MapNode::get(node);
    //mMap = mMapNode->getMap();
    MapOptions mapOptions;
    //mapOptions.cachePolicy() = CachePolicy::NO_CACHE;
    mMap = new Map(mapOptions);

    //TileSourceOptions gdalOpt;
    //gdalOpt
    //FeatureSourceOptions featureOpt;
    //featureOpt.name() = "pipe";
    //featureOpt.setDriver("ogr");
    //featureOpt.url() = "E:/3DCity/data/worldshp/world.shp";

    //osg::ref_ptr< FeatureSource > features = FeatureSourceFactory::create( featureOpt );
    //features->initialize();
    //features->getFeatureProfile();

    //FeatureModelSourceOptions fgmOpt;
    //fgmOpt.featureOptions() = featureOpt;
    //fgmOpt.setDriver("feature_geom");

    //ModelLayer* layer = new ModelLayer("pipe", fgmOpt);

    //mMap->addModelLayer(layer); 

    mMapNode = new MapNode(mMap);
    // Optimize the node
    osgUtil::Optimizer optimizer;
    optimizer.optimize(mMapNode.get());
    optimizer.reset();
    mRoot->addChild(mMapNode);

    mMapNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::ON);
    //=======================================================//

}


void CEarth::InitCameraConfig(void)
{
    // Local Variable to hold window size data
    RECT rect;

    // Create the viewer for this window
    mViewer = new osgViewer::Viewer();

    // Add a Stats Handler to the viewer
    mViewer->addEventHandler(new osgViewer::StatsHandler);

    // Get the current window size
    ::GetWindowRect(m_hWnd, &rect);

    // Init the GraphicsContext Traits
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

    // Init the Windata Variable that holds the handle for the Window to display OSG in.
    osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);

    // Setup the traits parameters
    traits->x = 0;
    traits->y = 0;
    traits->width = rect.right - rect.left;
    traits->height = rect.bottom - rect.top;
    traits->windowDecoration = false;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;
    traits->setInheritedWindowPixelFormat = true;
    traits->inheritedWindowData = windata;

    // Create the Graphics Context
    osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits.get());

    // Init a new Camera (Master for this View)
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;

    // Assign Graphics Context to the Camera
    camera->setGraphicsContext(gc);

    // Set the viewport for the Camera
    camera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));

    // Set projection matrix and camera attribtues
    camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0, 1000.0);
    // Add the Camera to the Viewer
    //mViewer->addSlave(camera.get());
    mViewer->setCamera(camera.get());
    // Add the Camera Manipulator to the Viewer
    mViewer->setCameraManipulator(mKeyswitchManipulator.get());

    // Set the Scene Data
    mViewer->setSceneData(mRoot.get());

    // Realize the Viewer
    mViewer->realize();

    // add some stock OSG handlers:
    mViewer->addEventHandler(new osgViewer::ThreadingHandler());
    mViewer->addEventHandler(new osgViewer::LODScaleHandler());
    mViewer->addEventHandler(new osgViewer::WindowSizeHandler());
    mViewer->addEventHandler(new osgGA::StateSetManipulator(mViewer->getCamera()->getOrCreateStateSet()));
}


// 建立窗口
void CEarth::SetupWindow(void)
{

}

// 建立相机
void CEarth::SetupCamera(void)
{
}

void CEarth::PreFrameUpdate(void)
{
 
}

void CEarth::PostFrameUpdate(void)
{
 
	// 帧后操作可在这里做一下
}


// 渲染，注意这里是静态的，可启用为全局线程
void CEarth::Render(void* ptr)
{
    CEarth* earth=(CEarth*)ptr;
    osgViewer::Viewer* viewer=earth->getViewer();
    //可以这样
    // view->run() or
    // while(!viewer->done()){viewer->frame();}
    // viewer->run();

    //也可以这样，建议这样
    while (!viewer->done())
    {
        earth->PreFrameUpdate();

        viewer->frame();
        earth->PostFrameUpdate();
        //Sleep(10);//让其他程序也占用CPU，放出MS

 
    }
	//退出了程序，弹出个对话框说一下
    //AfxMessageBox("线程退出");
   
    //_endthread();

}
 
void CEarth::ReplaceSceneData(osgEarth::MapNode* node)
{   
    mRoot->removeChildren(0, mRoot->getNumChildren());

    mMapNode =  node;

    osgUtil::Optimizer optimizer;
    optimizer.optimize(mMapNode.get());
    optimizer.reset();

    mRoot->addChild(mMapNode.get());
}

/////////////////////////////////////////////////////////////////////////////////////////////

struct PanClickHandler : public ControlEventHandler
{
 
    PanClickHandler( EarthManipulator* manip, osgViewer::Viewer* viewer)
        :mManip(manip),mViewer(viewer) { };
    void onClick( Control* control, const osg::Vec2f& pos, int mouseButtonMask )
    {
        osg::Vec2f dis = pos - osg::Vec2f(32, 32);
        //dis.normalize();

        mManip->pan(dis.x()/64.0, dis.y()/64.0);
        //OE_NOTICE << "You clicked at (" << pos.x() << ", " << pos.y() << ") within the control."
        //	<< std::endl;
    }

    osg::ref_ptr<osgViewer::Viewer> mViewer;
    osg::ref_ptr<EarthManipulator> mManip;
};
 

void CEarth::createControls()
{
    // create a surface to house the controls
    //ControlCanvas* cs = ControlCanvas::getOrCreate( mViewer );//??
    ControlCanvas* cs = new ControlCanvas(mViewer);    
    mRoot->addChild(cs);
 
    osg::Image* image = osgDB::readImageFile("view-pan.png");
 
    mEn->getSettings()->setLockAzimuthWhilePanning(true);
    ImageControl* pan = new ImageControl( image );
    pan->setSize( 64, 64 );
    pan->setHorizAlign( Control::ALIGN_RIGHT );
    pan->setVertAlign( Control::ALIGN_TOP );
    pan->addEventHandler( new PanClickHandler(mEn, mViewer));
    cs->addControl(pan );
 

}



void CEarth::createCompass()
{
    osg::ref_ptr<CCompass> compass = new CCompass;

    compass->setMainCamera( mViewer->getCamera() );
    compass->Init();

    mRoot->addChild(compass.get());
}