#include "stdafx.h"
#include "LayerTree.h"
#include <osgEarthFeatures/GeometryUtils>
using namespace osgEarth::Symbology;
CLayerTree::CLayerTree(void):
    mScene(NULL)
{
}


CLayerTree::~CLayerTree(void)
{
}
void CLayerTree::FromScene()
{
    HTREEITEM itemRoot = AddCatalog("È«²¿", TVI_ROOT, TVI_LAST);
    variant_t var;
    var = mMap->GetModelLayerIds();
    SAFEARRAY* psa = var.parray;
    if (psa)
    {
        LONG* pLongArr = NULL;
 
        SafeArrayAccessData(psa, (void**)&pLongArr);
        if (pLongArr)
        {
            for (int i = 0; i < psa->rgsabound[0].cElements; i++)
            {
                ILayerInfoPtr pLayerInfo = mMap->GetModelLayerInfo(pLongArr[i]);
                AddLayer(pLongArr[i], pLayerInfo, itemRoot);
            }
        }

        SafeArrayUnaccessData(psa);
    }
    var.Clear();
        
    var = mMap->GetImageLayerIds();
    psa = var.parray;
    if (psa)
    {
        LONG* pLongArr;
 
        SafeArrayAccessData(psa, (void**)&pLongArr);
        for (int i = 0; i < psa->rgsabound[0].cElements; i++)
        {
            ILayerInfoPtr pLayerInfo = mMap->GetImageLayerInfo(pLongArr[i]);
            AddLayer(pLongArr[i], pLayerInfo, itemRoot);
        }
        SafeArrayUnaccessData(psa);
    }
    var.Clear();

    var = mMap->GetElevationLayerIds();
    psa = var.parray;
    if (psa)
    {
        LONG* pLongArr;
 
        SafeArrayAccessData(psa, (void**)&pLongArr);
        for (int i = 0; i < psa->rgsabound[0].cElements; i++)
        {
            ILayerInfoPtr pLayerInfo = mMap->GetElevationLayerInfo(pLongArr[i]);
            AddLayer(pLongArr[i], pLayerInfo, itemRoot);
        }
        SafeArrayUnaccessData(psa);
    }
    var.Clear();
}

void CLayerTree::DeleteLayer(HTREEITEM hItem,BOOL bRemove)
{
	if (hItem)
	{
		HTREEITEM hChild = GetChildItem(hItem);
		while (hChild)
		{
			// recursively delete all the items
			HTREEITEM hNext = GetNextSiblingItem(hChild);
			DeleteLayer(hChild, bRemove);
			hChild = hNext;
		}
		LayerData* pLD = (LayerData* )GetItemData(hItem);
		if((pLD->type & LTREE_LAYER) && mMap && bRemove)
		{
            if (pLD->type & MODELLAYER)
            {
                mMap->RemoveModelLayer(pLD->id);
            }
            else if (pLD->type & ELEVATIONLAYER)
            {
                mMap->RemoveElevationLayer(pLD->id);   
            }
            else if (pLD->type & IMAGELAYER)
            {
                mMap->RemoveImageLayer(pLD->id);   
            }
		}
		delete pLD;
		DeleteItem(hItem);
	}
	else 
	{
		HTREEITEM hChild = GetRootItem();
		while (hChild)
		{
			// recursively delete all the items
			HTREEITEM hNext = GetNextSiblingItem(hChild);
			DeleteLayer(hChild, bRemove);
			hChild = hNext;
		}
	}
}
HTREEITEM CLayerTree::AddCatalog(LPCTSTR strName, HTREEITEM itemRoot, HTREEITEM itemAfter)
{

	int nImage = 0;
	HTREEITEM hItem = InsertItem(strName,nImage,nImage,itemRoot, itemAfter);	
	LayerData* pLData = new LayerData();
	pLData->type = LTREE_CATALOG;
	SetItemData(hItem,(DWORD_PTR)pLData);
	CheckItem(hItem, FALSE);
 
	return hItem;
}
HTREEITEM CLayerTree::AddLayer(LONG id, ILayerInfoPtr pLayer, HTREEITEM itemRoot, HTREEITEM itemAfter)
{
    long nType = pLayer->GetLayerType();
    long nGeoType = pLayer->GetGeoType();
	int nImage = GetLayerImage(nType, nGeoType);
	HTREEITEM hItem = InsertItem(pLayer->GetLayerName(),nImage,nImage,itemRoot, itemAfter);	
	LayerData* pLData = new LayerData();
	pLData->type = LTREE_LAYER | nType;
	pLData->id = id; 
 	pLData->geoType = nGeoType;
    pLData->layer = pLayer;
	SetItemData(hItem,(DWORD_PTR)pLData);
	CheckItem(hItem,pLayer->IsVisible());
 
	return hItem;
}

int CLayerTree::GetLayerImage(long nType, long nGeoType)
{

	int nImg = 0;
	switch(nType)
	{
	case MODELLAYER:
		{
	 
			switch(nGeoType)
			{
            case Geometry::TYPE_POINTSET:
				nImg = 4;
				break;
            case Geometry::TYPE_LINESTRING:
            case Geometry::TYPE_RING:
				nImg = 5;
				break;
			case Geometry::TYPE_POLYGON:
				nImg = 6;
				break;
			default:
				nImg = 3;
				break;
			}
			break;
		}
		break;
 	case ELEVATIONLAYER:
		{
            nImg = 1;
        }
        break;
    case IMAGELAYER:
		{
            nImg = 2;
        }
        break;
	default:
		break;
	}
	return nImg;
}


//DWORD CProjectTree::OnItemPostPaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw )
void CLayerTree::OnItemDraw(WTL::CDCHandle dcPaint, HTREEITEM hItem)
{
	WTL::CRect rect;
	if ( !GetItemRect(hItem, rect, TRUE ) )
		return;
 
	int nContextState = dcPaint.SaveDC();
		
	WTL::CRect rectText;

	rectText = rect;
	rectText.left += 16;

	dcPaint.SetBkColor( m_rgbBackground );
	dcPaint.ExtTextOut( rect.left, rect.top, ETO_OPAQUE, rect, _T( "" ), 0, NULL );
		
	//dcPaint.FillSolidRect(&rect, m_rgbBackground);


    ATL::CString strItemText;
    GetItemText(hItem, strItemText);

	LayerData* pLData = (LayerData* )GetItemData(hItem);

	if (pLData && !strItemText.IsEmpty())
	{
 
		int nImage,nImageSel;
		GetItemImage(hItem,nImage,nImageSel);
		m_ilItemImages.Draw(dcPaint,nImage,rect.TopLeft(),ILD_TRANSPARENT);
 
		UINT uFormat = DT_VCENTER | DT_SINGLELINE | DT_LEFT | DT_NOPREFIX;

 		dcPaint.SelectFont( m_fntTreeFont );
		dcPaint.SetBkMode(OPAQUE);//TRANSPARENT
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;
		if ((GetItemState(hItem, selflag) & selflag))
		{
			dcPaint.SetBkColor(m_rgbItemText);//GetSysColor(COLOR_HIGHLIGHT)
			dcPaint.SetTextColor(m_rgbBackground);//GetSysColor(COLOR_WINDOW)
		}
		else
		{
			dcPaint.SetBkColor(m_rgbBackground);//GetSysColor(COLOR_WINDOW)
			dcPaint.SetTextColor(m_rgbItemText);
		}
		CRect rectOut(rectText);
		dcPaint.DrawText(strItemText, strItemText.GetLength(), &rectOut, uFormat | DT_CALCRECT);
		dcPaint.DrawText(strItemText, strItemText.GetLength(), &rectOut, uFormat);

 
		
		dcPaint.RestoreDC( nContextState );
		

	}
 
}
void CLayerTree::OnStateChange(HTREEITEM hItem)
{
	if(NULL == mMap)
        return;
	//LayerData* pLD = (LayerData* )GetItemData(hItem);	
	//if(pLD)
	//{ 
    //}
    DoLayerStatChange(hItem);
}

BOOL CLayerTree::DealDragTree(HTREEITEM& hBranch, HTREEITEM& hNewParent,HTREEITEM& hAfter)
{
	LayerData* pLData = (LayerData* )GetItemData(hBranch);
	LayerData* pLDesData = (LayerData* )GetItemData(hAfter);
	if(pLData->type & LTREE_LAYERCHILD)
		return FALSE;
	if(pLDesData->type & LTREE_LAYERCHILD)
		return FALSE;
 

	HTREEITEM hParent = GetParentItem(hBranch);
	if(hParent == hAfter)
	{
		hNewParent = hParent;
		hAfter = TVI_FIRST;
	}
	else if(pLDesData->type == LTREE_CATALOG)
	{
		hNewParent = hAfter;
		hAfter = TVI_FIRST;
	}
	return TRUE;
}
void CLayerTree::OnDragComplete(HTREEITEM hItem)
{
	if(NULL == mMap)
		return;
	AdjustLayerByTree(GetRootItem());
	
}
void CLayerTree::AdjustLayerByTree(HTREEITEM hItem)
{
	while(hItem)
	{
		LayerData* pLD = (LayerData* )GetItemData(hItem);
		if(pLD->type & LTREE_LAYER)
		{
			
		}
		HTREEITEM hChild = GetNextItem(hItem,TVGN_CHILD);
		if(hChild)
		{
			AdjustLayerByTree(hChild);
		}			
		hItem = GetNextItem(hItem,TVGN_NEXT);
	}	
	
}
void CLayerTree::DoLayerStatChange(HTREEITEM hItem)
{
	if (hItem)
	{
		LayerData* pLDS = (LayerData* )GetItemData(hItem);			
		if(pLDS->type & LTREE_LAYER)
		{
            //if (pLDS->layer)
            //    pLDS->layer->SetVisible(IsCheck(hItem)?VARIANT_TRUE:VARIANT_FALSE);
		}
		else if(pLDS->type & LTREE_LAYERCHILD)
		{
			HTREEITEM hParent = GetParentItem(hItem);
			//... 
		}
		HTREEITEM hChild = GetChildItem(hItem);
		while (hChild)
		{
			// recursively delete all the items
			HTREEITEM hNext = GetNextSiblingItem(hChild);
			DoLayerStatChange(hChild);
			hChild = hNext;
		}
	}
}

ILayerInfoPtr CLayerTree::GetLayerInfo( HTREEITEM hItem )
{
    LayerData* pLDS = (LayerData* )GetItemData(hItem);			
    if(pLDS->type & LTREE_LAYER)
    {
        return pLDS->layer;
    }
    return NULL;
}

HTREEITEM CLayerTree::AddLocation( LPCTSTR strName )
{
    ILocationPtr loc = mScene->GetLocation();
 
    int nImage = 8;
    HTREEITEM hItem = InsertItem(strName,nImage,nImage,TVI_ROOT, TVI_LAST);	
    LayerData* pLData = new LayerData();
    pLData->type = LTREE_LOCATION;
    pLData->vp = loc;
    SetItemData(hItem,(DWORD_PTR)pLData);
    SetItemState( hItem, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK, FALSE );

    return hItem;
}

void CLayerTree::GotoLocation( HTREEITEM hItem )
{
    LayerData* pLDS = (LayerData* )GetItemData(hItem);			
    if(pLDS->type & LTREE_LOCATION)
    {
        mScene->GotoLocation(pLDS->vp);
    }
}

BOOL CLayerTree::IsLocation( HTREEITEM hItem )
{
    LayerData* pLDS = (LayerData* )GetItemData(hItem);			
    if(pLDS->type & LTREE_LOCATION)
    {
        return TRUE;
    }
    return FALSE;
}

BOOL CLayerTree::IsCatalog( HTREEITEM hItem )
{
    LayerData* pLDS = (LayerData* )GetItemData(hItem);			
    if(pLDS->type & LTREE_CATALOG)
    {
        return TRUE;
    }
    return FALSE;
}
