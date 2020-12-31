#pragma once
//#include "../SceneCOM/SceneCOM_i.h"
#include "MultiTree.h"
#ifdef _DEBUG
#import "..\bin\Debug\SceneCOMd.dll" no_namespace named_guids
#else 
#import "..\bin\Debug\SceneCOM.dll" no_namespace named_guids
#endif
//#include <comdef.h>
//_COM_SMARTPTR_TYPEDEF(ISceneCtrl, __uuidof(ISceneCtrl));
#define LTREE_CATALOG		0x1000	//分类	
#define LTREE_LAYER			0x2000	//图层项
#define LTREE_LAYERCHILD	0x4000	//图层子项
#define LTREE_LOCATION  	0x8000	//Viewpoint

#define MODELLAYER        0x100
#define ELEVATIONLAYER    0x200
#define IMAGELAYER        0x300

class CLayerTree : public  CMultiTree
{

public:
    DECLARE_WND_SUPERCLASS(_T("ProjectTree"), GetWndClassName())
    CLayerTree(void);
    virtual ~CLayerTree(void);
    BEGIN_MSG_MAP(CLayerTree)
        CHAIN_MSG_MAP(CMultiTree)
        DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()
protected:
    ISceneCtrlPtr mScene;
    ISceneMapPtr  mMap;
public:
    void SetScene(ISceneCtrlPtr scene)
    {
        mScene = scene;
        mMap = mScene->GetMap();
    }
    struct LayerData{
        LONG type;
        LONG id;
        LONG geoType;

        ILayerInfoPtr layer;
        ILocationPtr vp;

        LayerData():layer(NULL),vp(NULL), id(-1),type(0),geoType(0){};
        ~LayerData(){
            if (layer) {layer.Release();}
            if (vp) {vp.Release();}

        };

    };
    virtual void OnStateChange(HTREEITEM hItem);
    virtual void OnItemDraw(WTL::CDCHandle pDC, HTREEITEM hItem);
    //virtual DWORD OnItemPostPaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw );
    virtual BOOL DealDragTree(HTREEITEM& hBranch, HTREEITEM& hNewParent,HTREEITEM& hAfter);
    virtual void OnDragComplete(HTREEITEM hItem);
    void AdjustLayerByTree(HTREEITEM hItem);
    int GetLayerImage(long nType, long nGeoType);
    void FromScene();
    HTREEITEM AddLocation(LPCTSTR strName);
    void GotoLocation(HTREEITEM hItem);
    BOOL IsLocation(HTREEITEM hItem);
    BOOL IsCatalog(HTREEITEM hItem);
    ILayerInfoPtr GetLayerInfo(HTREEITEM hItem);
    void DeleteLayer(HTREEITEM hItem,BOOL bRemove);
    HTREEITEM AddLayer(LONG id, ILayerInfoPtr pLayer, HTREEITEM itemRoot, HTREEITEM itemAfter = TVI_LAST);
    void DoLayerStatChange(HTREEITEM hItem);
    HTREEITEM AddCatalog(LPCTSTR strName, HTREEITEM itemRoot, HTREEITEM itemAfter = TVI_LAST);
};

