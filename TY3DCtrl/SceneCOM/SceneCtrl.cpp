// SceneCtrl.cpp : Implementation of CSceneCtrl
#include "stdafx.h"
#include "SceneCtrl.h"
#include "SceneNode.h"
#include "SceneMap.h"
#include "Location.h"
// CSceneCtrl

LRESULT CSceneCtrl::OnCreate( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
    mEarth = new CEarth(m_hWnd);  
    std::string  csFileName ;  

    mEarth ->InitOSG(csFileName) ;  

    mThreadHandle = (HANDLE)_beginthread(&CEarth::Render, 0, mEarth) ;  
    return 0;
}

LRESULT CSceneCtrl::OnKeyDown( UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL&  bHandled  )
{
    int nChar = wParam;
    mEarth->getViewer()->getEventQueue()->keyPress(nChar);  
    if (nChar==VK_ESCAPE)  
    {  
        bHandled = TRUE;
    } 
    return 0;
}

LRESULT CSceneCtrl::OnEraseBkgnd( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
    bHandled = true;
    return  0;
}

LRESULT CSceneCtrl::OnSize( UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
 	if(m_hWnd)
	{
        RECT  rt;
	    GetClientRect(&rt);

 
    }
    return 0;
}

LRESULT CSceneCtrl::OnDestroy( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
    if (mEarth!=NULL)  
    {  
        delete mEarth;  

    }  
    WaitForSingleObject(mThreadHandle,1000);  
    return 0;
}

STDMETHODIMP CSceneCtrl::ReplaceScene(ISceneNode* scene)
{
    if (scene == NULL || mEarth == NULL)
    {
        return E_FAIL;
    }
    CSceneNode* pNode = (CSceneNode*)scene;
    mEarth->ReplaceSceneData(pNode->GetNode());
    return S_OK;
}
STDMETHODIMP CSceneCtrl::GetMap(ISceneMap** ppMap)
{
    if (ppMap == NULL || mEarth == NULL)
    {
        return E_FAIL;
    }
    CSceneMap* map = new CComObject<CSceneMap>;
    map->AddRef();
    map->Attach(mEarth->getMap());
    *ppMap = map;
    return S_OK;
}

STDMETHODIMP CSceneCtrl::GetLocation(ILocation** viewpoint)
{
    if (mEarth == NULL || viewpoint == NULL)
    {
        return E_FAIL;
    }
    CLocation* vp = new CComObject<CLocation>;
    vp->AddRef();
    vp->Attach(mEarth->getViewPoint());
    *viewpoint = vp;

    return S_OK;
}
STDMETHODIMP CSceneCtrl::GotoLocation(ILocation* viewpoint)
{
    if (mEarth == NULL || viewpoint == NULL)
    {
        return E_FAIL;
    }
    CLocation* loc = (CLocation*)viewpoint;

    mEarth->setViewPoint(loc->GetVP());
 
    return S_OK;
}