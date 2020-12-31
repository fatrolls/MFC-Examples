// ProjectTreeCtrl.cpp : Implementation of CProjectTreeCtrl
#include "stdafx.h"
#include "ProjectTreeCtrl.h"
#include "PropertyDlg.h"
#include "CatalogDlg.h"
#include "LocationDlg.h"
// CProjectTreeCtrl
HRESULT CProjectTreeCtrl::OnDraw(ATL_DRAWINFO& di)
{
//    RECT& rc = *(RECT*)di.prcBounds;
//    // Set Clip region to the rectangle specified by di.prcBounds
//    HRGN hRgnOld = NULL;
//    if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
//        hRgnOld = NULL;
//    bool bSelectOldRgn = false;
//
//    HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
//
//    if (hRgnNew != NULL)
//    {
//        bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
//    }
//
//    Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
//    SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
//    LPCTSTR pszText = _T("ProjectTreeCtrl");
//#ifndef _WIN32_WCE
//    TextOut(di.hdcDraw,
//        (rc.left + rc.right) / 2,
//        (rc.top + rc.bottom) / 2,
//        pszText,
//        lstrlen(pszText));
//#else
//    ExtTextOut(di.hdcDraw,
//        (rc.left + rc.right) / 2,
//        (rc.top + rc.bottom) / 2,
//        ETO_OPAQUE,
//        NULL,
//        pszText,
//        ATL::lstrlen(pszText),
//        NULL);
//#endif
//
//    if (bSelectOldRgn)
//        SelectClipRgn(di.hdcDraw, hRgnOld);
//
//    DeleteObject(hRgnNew);
//
    return S_OK;
}


LRESULT CProjectTreeCtrl::OnCreate( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
    RECT  rt;
	GetClientRect(&rt);
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |                               
								 //WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
                                 TVS_FULLROWSELECT | TVS_NOTOOLTIPS | TVS_SHOWSELALWAYS;
	
	//mTree.EnableDrop();
	if (!mTree.Create (m_hWnd, rt, _T(""), dwViewStyle,0,ID_LAYER_TREE))
	{
		return -1;      // fail to create
	}
    mTree.EnableDrop(TRUE);
    mTree.Initialise();
    
    LOGFONT ft;
    //mTree.SetFont(ft);
    return 0;
}

LRESULT CProjectTreeCtrl::OnSize( UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
 	if(m_hWnd)
	{
        RECT  rt;
	    GetClientRect(&rt);

        if(mTree.m_hWnd)
        {
            mTree.MoveWindow(&rt);
        }
    }
    return 0;
}

LRESULT CProjectTreeCtrl::OnEraseBkgnd( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
    bHandled = true;
    return  0;
}

LRESULT CProjectTreeCtrl::OnDestroy( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{

    return 0;
}

STDMETHODIMP CProjectTreeCtrl::AttachScene(VARIANT scene)
{
    if (scene.vt != VT_DISPATCH || scene.pdispVal == NULL)
    {
        return E_FAIL;
    }

    CComQIPtr<ISceneCtrl> pScene(scene.pdispVal);
    mTree.SetScene(pScene.Detach());
    mTree.FromScene();
    return S_OK;
}

STDMETHODIMP CProjectTreeCtrl::readEarth(BSTR strEarthPath, VARIANT_BOOL* bSuc)
{
    return S_OK;
}

STDMETHODIMP CProjectTreeCtrl::writeEarth(BSTR strEarthPath, VARIANT_BOOL* bSuc)
{
    return S_OK;
}

LRESULT CProjectTreeCtrl::OnContextMenu( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM  lParam , BOOL& /*bHandled*/ )
{
    if(mhMenu==NULL)
    {
        HMENU hMenu = LoadMenu((HINSTANCE) _AtlBaseModule.m_hInst,MAKEINTRESOURCE(IDR_LAYERPROPERTIES));
        mhMenu = GetSubMenu(hMenu,0);
    }
    POINT hp;
    hp.x = LOWORD(lParam);
    hp.y = HIWORD(lParam);
    //ClientToScreen(&hp);
    m_hitPoint = hp;
    mTree.ScreenToClient(&m_hitPoint);
    UIEnable(ID_NEW_CATALOG,FALSE);  
    UINT  flag = 0;
    HTREEITEM hItem = mTree.HitTest(m_hitPoint, &flag);
    if(hItem)
    {
        mTree.SelectItem(hItem);
        if (mTree.IsCatalog(hItem))
        {
            UIEnable(ID_NEW_CATALOG,TRUE, TRUE); 
        }
    }
    else
    {
        UIEnable(ID_NEW_CATALOG,TRUE, TRUE); 
    }
    TrackPopupMenu(mhMenu,TPM_LEFTALIGN |TPM_RIGHTBUTTON,hp.x,hp.y,0,this->m_hWnd,NULL);
    
    return 0;

}

LRESULT CProjectTreeCtrl::OnProperties( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled )
{
    return 0;
}

LRESULT CProjectTreeCtrl::OnLayerProperties( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled )
{
    UINT  flag = 0;
    HTREEITEM hItem = mTree.HitTest(m_hitPoint, &flag);
    if(hItem == NULL)
        return 0;
    ILayerInfoPtr pLayer = mTree.GetLayerInfo(hItem);
    if(NULL == pLayer)
        return 0;
    CPropertyDlg dlg(pLayer);
    dlg.DoModal();
    return 0;
}

LRESULT CProjectTreeCtrl::OnDoubleClickTree( int idCtrl, LPNMHDR pnmh, BOOL& bHandled )
{
    DWORD pos = GetMessagePos();
    m_hitPoint.x = GET_X_LPARAM(pos);
    m_hitPoint.y = GET_Y_LPARAM(pos);
    mTree.ScreenToClient(&m_hitPoint);
    UINT  flag = 0;
    HTREEITEM hItem = mTree.HitTest(m_hitPoint, &flag);
    if(hItem == NULL)
        return 0;
    ILayerInfoPtr pLayer = mTree.GetLayerInfo(hItem);
    if(NULL != pLayer)
    {
        CPropertyDlg dlg(pLayer);
        dlg.DoModal();
    }
    else
    {
        if (mTree.IsLocation(hItem))
        {
            mTree.GotoLocation(hItem);
        }
        
    }
    return 0;
}

LRESULT CProjectTreeCtrl::OnAddLocaion( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled )
{
    CLocationDlg dlg;
    if(dlg.DoModal() != IDOK)
        return -1;
 
    mTree.AddLocation(dlg.GetName());
    return 0;
}


LRESULT CProjectTreeCtrl::OnAddCatalog( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled )
{
    CCatalogDlg dlg;
    if(dlg.DoModal() != IDOK)
        return -1;
    UINT  flag = 0;
    HTREEITEM hItem = mTree.HitTest(m_hitPoint, &flag);
    if(hItem == NULL)
    {
        hItem = TVI_ROOT;
    }
    mTree.AddCatalog(dlg.GetName(), hItem);
    return 0;
}

