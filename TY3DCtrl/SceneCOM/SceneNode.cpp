// SceneNode.cpp : CSceneNode µÄÊµÏÖ

#include "stdafx.h"
#include "SceneNode.h"
#include <osgDB/ReadFile>
#include <osgUtil/optimizer>
#include <atlstr.h>
#include "SceneMap.h"
// CSceneNode

STDMETHODIMP CSceneNode::FromFile(BSTR strFileName)
{
    CStringA str(strFileName);
    osg::Node* node = osgDB::readNodeFile(str.GetString());
    mMapNode = MapNode::get(node);
    return S_OK;
}

STDMETHODIMP CSceneNode::GetMap(ISceneMap** sceneMap)
{
    if (sceneMap == NULL || mMapNode == NULL)
    {
        return E_FAIL;
    }
    CSceneMap* map = new CComObject<CSceneMap>;
    map->AddRef();
    map->Attach(mMapNode->getMap());
    *sceneMap = map;
    return S_OK;
}