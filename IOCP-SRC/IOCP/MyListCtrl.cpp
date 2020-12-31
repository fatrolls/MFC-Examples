// SqlListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyListCtrl.h"
#include "IOCP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyListCtrl

MyListCtrl::MyListCtrl()
{

	m_ShowIcons=TRUE;
	m_sortdirection=1;
	m_iCurrentSortColumn=-1;
	m_IconHeight=100;
	m_IconWidth=100;
	m_iNumberOfColumns=-1;
	for(int i=0;i<10;i++)
		m_iColumnWidthArray[i]=0;
}

MyListCtrl::~MyListCtrl()
{


}


BEGIN_MESSAGE_MAP(MyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(MyListCtrl)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyListCtrl message handlers






/* AddItemToList(int nIdex,int iImage, ITEMINFO *pItem)
*
*	Adds an item which has data in the struct "ITEMINFO" into a list.
*--------------------------------------------------------------------------------------
*  Observe that the function FreeAllItems have to be called to free the memory
*  that is allocated.  
*/
int  MyListCtrl::AddItemToList(int nIndex,int iImage, ITEMINFO *pItem)
{

	if(pItem==NULL)
		return FALSE;

	//Init. LVITEM..
	LV_ITEM lvi;

	// Clear the SockAddr. 
	memset(&lvi,0,sizeof(lvi));
	/*
	* LVIF_PARAM Means that we get the data when it is needed(When we show our item).
	* This is done in to save memory and slow memory copy. 
	* The actual data is copyed when the function OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
	* (Message LVN_GETDISPINFO) is called. 
	*/
	if(m_ShowIcons)
		lvi.mask=LVIF_TEXT |LVIF_PARAM|LVIF_IMAGE;
	else
		lvi.mask=LVIF_TEXT |LVIF_PARAM;
	lvi.iItem=nIndex;
	lvi.iSubItem=0;
	lvi.iImage=iImage;
	lvi.pszText=LPSTR_TEXTCALLBACK;
	lvi.lParam=(LPARAM)pItem;
	BOOL bRet=InsertItem(&lvi)!=-1;
	if(bRet)
		Update(nIndex);
	return bRet;
}

int MyListCtrl::AddItemToList(ITEMINFO *pItem, int iImage)
{
	int nCount= GetItemCount();	
	return AddItemToList(nCount++,iImage,pItem);
}

void MyListCtrl::OnDestroy() 
{
	FreeListItems();

	CListCtrl::OnDestroy();

	// TODO: Add your message handler code here

}

/*
*   Frees the memory and removes all the data..  
* 
*	Add additional code for other types of data.. 
*/


BOOL MyListCtrl::FreeListItems()
{
	int nCount= GetItemCount();	
	for(int i=0; i<nCount;i++)
	{   
		ITEMINFO* pItem=(ITEMINFO*)GetItemData(i);
		if(pItem!=NULL)
			delete  pItem;

	}

	return CListCtrl::DeleteAllItems();// <- Ta bort allt..
}


/*
* Function Used For sorting the list.
* RETURNS
* Zero if the Items are identical, 
* <0 if Item1 object is less than item2 (ignoring case), or  
* >0 Item1 object is greater than item2.
*
* Observe The function must be static!
*/
int CALLBACK MyListCtrl::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{


	ITEMINFO* pItem1 = (ITEMINFO*) lParam1;
	ITEMINFO* pItem2 = (ITEMINFO*) lParam2;

	int nResult=0;


	switch (lParamSort) {

	case 0:// Sort after Column 1	
		nResult = pItem1->m_ClientAddress.CompareNoCase (pItem2->m_ClientAddress);
		break;
	case 1:// Sort after Column 1	

		nResult = pItem1->m_iNumberOfReceivedMsg>=pItem2->m_iNumberOfReceivedMsg?-1:1;
		break;

	default:
		nResult = pItem1->m_ClientAddress.CompareNoCase (pItem2->m_ClientAddress);
		break;
	}
	return nResult;
}



// Opposite direction.. 
int CALLBACK MyListCtrl::CompareFunc2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int nResult=MyListCtrl::CompareFunc(lParam1,lParam2,lParamSort);
	return nResult*-1;
}


/*
*	OnGetdispinfoServicelist1
*-------------------------------------------------------
* In this function we get the actual data to be showed in the list.
* This fuction must be optimzed to get the best performance, 
* The structure ITEMINFO does not need to contain all the data. 
*/


void MyListCtrl::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pDispInfo->item.mask & LVIF_TEXT)// If we whant to show text. 
	{
		ITEMINFO* pItem=(ITEMINFO*) pDispInfo->item.lParam; // Get Our Item
		if(pItem!=NULL)
		{
			CString txt;
			switch(pDispInfo->item.iSubItem)
			{
				// First Column 
			case 0: 

				::lstrcpy(pDispInfo->item.pszText,pItem->m_ClientAddress);//copy the string.
				break;
			case 1: // Second Column		
				CString tmp="----------------";
				if(pItem->m_bFileSendMode)
				{
					tmp="File transfer mode..";
				}
				else if(pItem->m_bFileReceivedMode)
				{
					float procent=100.0*pItem->m_iFileBytes/(float)pItem->m_iMaxFileBytes;
					tmp.Format("%0.2f%% %i/%i> ",procent,pItem->m_iFileBytes,pItem->m_iMaxFileBytes);
				}else
					tmp.Format("Number of received packages: %i.",pItem->m_iNumberOfReceivedMsg);
				::lstrcpy(pDispInfo->item.pszText,tmp);//copy the string.
				break;		
			}
		}
	}
	*pResult = 0;

}



/*
*  Function handler for  Custom Draw Message NM_CUSTOMDRAW which is send when the list is  	
*  painted. You can eather Draw everything your self or just change some attributes before  
*  paint (prepaint stage). Here we change the attributes depending on data hold in ITEMINFO Structure.
*/



void MyListCtrl::OnCustomdraw ( NMHDR* pNMHDR, LRESULT* pResult )
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// Take the default processing unless we set this to something else below.
	*pResult = 0;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the prepaint stage for an item. Here's where we set the
		// item's text color. Our return value will tell Windows to draw the
		// item itself, but it will use the new color we set here.
		// We'll cycle the colors through red, green, and light blue.
		COLORREF crText;
		int    nIndex = (int)( pLVCD->nmcd.dwItemSpec );
		int iSubItem =pLVCD->iSubItem;
		ITEMINFO* pItem=(ITEMINFO*)GetItemData(nIndex);



		int mask,state;
		if(m_ShowIcons)
			mask=LVIF_TEXT |LVIF_PARAM|LVIF_IMAGE;
		else 
			mask=LVIF_TEXT |LVIF_PARAM;
		state=GetItemState(nIndex,mask);
		if(state&LVIS_SELECTED==LVIS_SELECTED)
		{
			crText=RGB(10,36,106);
			//crText=RGB(255,0,0);
			pLVCD->clrText=RGB(255,255,255);



		}

		if(nIndex%2==0)
			crText=RGB(180,180,180);
		else
			crText=RGB(255,255,255);



		// Store the color back in the NMLVCUSTOMDRAW struct. 
		pLVCD->clrTextBk=crText;

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}

BOOL MyListCtrl::DeleteAllItems()
{
	return FreeListItems();
}



void MyListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(!pNMListView)
		AfxMessageBox(" C P Fel pNMListView= NULL");
	else
	{	
		if(m_iCurrentSortColumn==pNMListView->iSubItem)
		{
			m_sortdirection	=m_sortdirection*-1;
			if(m_sortdirection>0)
				SetHeaderIcon(pNMListView->iSubItem,0);
			else
				SetHeaderIcon(pNMListView->iSubItem,2);	
		}else
		{
			// Clear all the other Icons.. 
			for (int i=0; i < m_iNumberOfColumns; i++)
				SetHeaderIcon(i,-1);
			// Set the sortdirection 
			m_sortdirection=1;
			// change the icon direction 
			SetHeaderIcon(pNMListView->iSubItem,0);
			//Set the curren sort solumn 
			m_iCurrentSortColumn=pNMListView->iSubItem;

		}



		/*
		*	Sort the elements in the List. (NICE).. 
		*/

		if(m_sortdirection>=0)
			SortItems(CompareFunc, pNMListView->iSubItem);
		else
			SortItems(CompareFunc2, pNMListView->iSubItem);

		m_iCurrentSortColumn=pNMListView->iSubItem;

		*pResult = 0;
	}
}



/*
*	Returns the selected item
*/


ITEMINFO* MyListCtrl::GetSelectedItem()
{
	int Index=GetNextItem(-1,LVNI_SELECTED);

	if(Index<0)
		return NULL;
	//EnsureVisible(Index, FALSE); // visa upp Itemet

	return (ITEMINFO*)GetItemData(Index);
}


BOOL MyListCtrl::init()
{
	//Create Image list. 

	m_ImageListThumb.DeleteImageList();
	m_IconWidth=2;
	m_IconHeight=27;
	m_ImageListThumb.Create(m_IconWidth, m_IconHeight, ILC_COLOR24, 0, 1);
	SetImageList(&m_ImageListThumb, LVSIL_SMALL);
	m_ShowIcons=FALSE;
	Arrange(LVSCW_AUTOSIZE);
	//LVSCW_AUTOSIZE
	FreeListItems();

	// For the resize problem...... 
	m_iNumberOfColumns=2;
	m_iColumnWidthArray[0]=60;
	m_iColumnWidthArray[1]=80;
	m_iColumnWidthArray[2]=110;
	m_iColumnWidthArray[3]=100;



	InsertColumn(0,"Client Address",LVCFMT_LEFT,m_iColumnWidthArray[0]);
	InsertColumn(1,"Status",LVCFMT_LEFT,m_iColumnWidthArray[1]);
	//InsertColumn(1,"Storlek",LVCFMT_LEFT,110);
	//InsertColumn(2,"Unik ID",LVCFMT_LEFT,110);
	// We whant a nice flat list-  	
	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FLATSB |
		LVS_EX_FULLROWSELECT );


	//
	// Setting the header INFO
	//

	// Loading header images.. 
	m_HeaderImages.DeleteImageList();
	m_HeaderImages.Create(IDB_HEADER, 9*2, 1, RGB(255,255,255));

	CHeaderCtrl* pHeader=GetHeaderCtrl();
	if(pHeader)
	{

		pHeader->SetImageList(&m_HeaderImages);

		for (int i=0; i < pHeader->GetItemCount(); i++)
		{
			SetHeaderIcon(i,-1);
		}

		SetBkColor(RGB(255,255,255));
		SetTextBkColor(RGB(255,255,255));
		SetTextColor(RGB(0,0,0));
		SetHeaderIcon(0,0);
		m_iCurrentSortColumn=0;
	}

	ResizeColumns();

	return TRUE;
}



BOOL MyListCtrl::DeleteSelectedItem()
{
	int Index=GetNextItem(-1,LVNI_SELECTED);

	if(Index<0)
		return FALSE;
	else
	{
		ITEMINFO* pItem=(ITEMINFO*)GetItemData(Index);
		if(pItem)
			delete pItem;

	}
	return DeleteItem(Index);
}

void MyListCtrl::SetIconSize(int x, int y)
{
	m_IconHeight=y;
	m_IconWidth=x;

}



/*
*	Markerar Objektet i listan och ser till att den syns samt returnerar en pekare till den.
*	returnerar NULL om det inte fanns någon.. 
*/

ITEMINFO* MyListCtrl::Select(CString ID)
{
	ITEMINFO* pItem=NULL;
	int nCount= GetItemCount();	
	int iItem=-1;
	if(nCount>0)
	{

		for(int i=0;i<nCount;i++)
		{
			ITEMINFO* ptmpItem=(ITEMINFO*)GetItemData(i);
			if(ptmpItem)
				if(ptmpItem->m_ClientAddress==ID)
				{
					pItem=ptmpItem;
					iItem=i;
					break;
				}
		}

		if(pItem)
		{

			int mask,state;
			if(m_ShowIcons)
				mask=LVIF_TEXT |LVIF_PARAM|LVIF_IMAGE;
			else 
				mask=LVIF_TEXT |LVIF_PARAM;
			state=GetItemState(iItem,mask);
			state|=LVIS_SELECTED|LVIS_FOCUSED;	
			if(SetItemState(iItem,state, mask))
			{ 
				EnsureVisible(iItem, FALSE); // vis upp ItemetLVIF_TEXT | LVIF_IMAGE | LVIF_STATE
				Update(iItem);
				SetFocus();
				return pItem;
			}
		}
	}

	return NULL;
}

ITEMINFO* MyListCtrl::Find(CString ID)
{
	return NULL;
}























void MyListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CListCtrl::OnSize(nType, cx, cy);

	if (nType == SIZE_MAXHIDE || nType == SIZE_MAXSHOW)
		return;		// arrangement not needed



	/*
	CHeaderCtrl* pHeader=GetHeaderCtrl();
	if(pHeader)
	iNumberOfColums=pHeader->GetItemCount();

	double normalColumnWidth=500.0;
	int iColumnWidth=0;
	int newColumnWidth=0;
	double fratio=0.0;
	for(int i=0;i<iNumberOfColums;i++)
	{
	iColumnWidth=GetColumnWidth(i);
	fratio=(float)iColumnWidth/normalColumnWidth;
	newColumnWidth=(int)(fratio*(float)cx);
	SetColumnWidth(i,newColumnWidth);
	}

	*/

	ResizeColumns(cx);
}

void MyListCtrl::ResizeColumns(int cx)
{


	if(cx<0)
	{

		CRect wndrc;
		GetClientRect(&wndrc);
		cx=wndrc.right;
	}
	double normalColumnWidth=0;
	int i=0;
	for(i=0;i<m_iNumberOfColumns;i++)
	{
		normalColumnWidth+=m_iColumnWidthArray[i];	
	}

	int iColumnWidth=0;
	int newColumnWidth=0;
	double fratio=0.0;
	for(i=0;i<m_iNumberOfColumns;i++)
	{
		iColumnWidth=m_iColumnWidthArray[i];
		fratio=(float)iColumnWidth/normalColumnWidth;
		newColumnWidth=(int)(fratio*(float)cx);
		if(newColumnWidth>iColumnWidth)
			SetColumnWidth(i,newColumnWidth);
	}
}

/*
* Changes the header with index (iIndex) to the Icon number (iPictureIndex),
* defined in (IDB_HEADER) bitmap. 
*/

BOOL MyListCtrl::SetHeaderIcon(int iIndex,int iPictureIndex)
{
	CHeaderCtrl* pHeader=GetHeaderCtrl();
	if(pHeader)
	{
		HDITEM hdi;
		// Clear the strukture. 
		memset(&hdi,0,sizeof(hdi));
		// We whant the IMAGE info. 
		hdi.fmt |= HDF_IMAGE|HDF_STRING; //Konstigt bugg i release
		hdi.mask |= HDI_IMAGE | HDI_FORMAT;
		//hdi.mask=HDI_IMAGE;	
		if(!pHeader->GetItem(iIndex, &hdi))
			TRACE("ERROR pHeader->GetItem(i, &hdi) failed\r\n");

		hdi.fmt |= HDF_IMAGE|HDF_STRING; //Konstigt bugg i release
		hdi.mask |= HDI_IMAGE | HDI_FORMAT;
		hdi.iImage =  iPictureIndex;
		return pHeader->SetItem( iIndex, &hdi);
	}
	return FALSE;
}




// Resort the list 
void MyListCtrl::ReSort()
{
	if(m_sortdirection>=0)
		SortItems(CompareFunc, m_iCurrentSortColumn);
	else
		SortItems(CompareFunc2, m_iCurrentSortColumn);
}



// Frees the memory allocated for the item and removes it from the list. 
BOOL MyListCtrl::FreeItem(int Index)
{
	ITEMINFO* pItem=(ITEMINFO*)GetItemData(Index);
	if(pItem)
		delete pItem;
	return DeleteItem(Index);
}

BOOL MyListCtrl::Select(int index)
{
	int mask,state;
	if(m_ShowIcons)
		mask=LVIF_TEXT |LVIF_PARAM|LVIF_IMAGE;
	else 
		mask=LVIF_TEXT |LVIF_PARAM;
	state=GetItemState(index,mask);
	state|=LVIS_SELECTED|LVIS_FOCUSED;	
	if(SetItemState(index,state, mask))
	{ 
		EnsureVisible(index, FALSE); // vis upp ItemetLVIF_TEXT | LVIF_IMAGE | LVIF_STATE
		Update(index);
		SetFocus();
		return TRUE;

	}
	return FALSE;
}
