// ResourceTree.cpp : implementation file
//

#include "stdafx.h"
#include "resviewer.h"
#include "resviewerDoc.h"
#include "ResourceTree.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceTree
IMPLEMENT_DYNCREATE(CResourceTree, CTreeView)

CResourceTree::CResourceTree()
{
}

CResourceTree::~CResourceTree()
{
}


BEGIN_MESSAGE_MAP(CResourceTree, CTreeView)
	//{{AFX_MSG_MAP(CResourceTree)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceTree drawing

void CResourceTree::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CResourceTree diagnostics

#ifdef _DEBUG
void CResourceTree::AssertValid() const
{
	CTreeView::AssertValid();
}

void CResourceTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResourceTree message handlers

int CResourceTree::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_imglFolders.Create(IDB_FOLDERIMAGES,16,1,RGB(255,0,255));
	GetTreeCtrl().SetImageList(&m_imglFolders,TVSIL_NORMAL);
	
	// TODO: Add your specialized creation code here
	
	return 0;
}



BOOL CResourceTree::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |
				TVS_SHOWSELALWAYS;

	return CTreeView::PreCreateWindow(cs);
}

void CResourceTree::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CResviewerDoc* pDoc = (CResviewerDoc*)GetDocument();
	PERsrcTbl* RsrcTbl = pDoc->GetPERsrc();
	
	if (!RsrcTbl)
	{
		GetTreeCtrl().DeleteAllItems();
		return;
	}

	InitTree(RsrcTbl);
	//TRACE("ResTREE\n",lHint);


	
}

BOOL CResourceTree::InitTree(PERsrcTbl * RsrcTbl)
{
	//
	// init the tree cntrl with the filename at the top of 
	// the tree followed by the resource types we want.

	HTREEITEM hTreeroot;
	HTREEITEM hTreechild;
	PERsrcType * RsrcType;
	
	CTreeCtrl& m_tree = GetTreeCtrl();
	CResviewerDoc* pDoc = (CResviewerDoc*)GetDocument();


	hTreeroot = m_tree.InsertItem(pDoc->GetPathName(),
									ILI_CLOSED_FOLDER,
									ILI_OPEN_FOLDER);


	RsrcType = RsrcTbl->GetResourceTypeById((WORD)RT_ICON);

	if (RsrcType)
	{
		hTreechild = m_tree.InsertItem("RT_ICON",
									ILI_CLOSED_FOLDER,
									ILI_OPEN_FOLDER,hTreeroot);

		m_tree.InsertItem("",ILI_CLOSED_FOLDER,
							ILI_CLOSED_FOLDER,
							hTreechild);

		delete RsrcType;
	}


	RsrcType = RsrcTbl->GetResourceTypeById((WORD)RT_BITMAP);

	if (RsrcType)
	{
		hTreechild = m_tree.InsertItem("RT_BITMAP",
									ILI_CLOSED_FOLDER,
									ILI_OPEN_FOLDER,hTreeroot);

		m_tree.InsertItem("",ILI_CLOSED_FOLDER,
							ILI_CLOSED_FOLDER,
							hTreechild);
		delete RsrcType;
		
	}

	RsrcType = RsrcTbl->GetResourceTypeById((WORD)RT_CURSOR);

	if (RsrcType)
	{
		hTreechild = m_tree.InsertItem("RT_CURSOR",
									ILI_CLOSED_FOLDER,
									ILI_OPEN_FOLDER,hTreeroot);

		m_tree.InsertItem("",ILI_CLOSED_FOLDER,
							ILI_CLOSED_FOLDER,
							hTreechild);
		delete RsrcType;
		
	}

	RsrcType = RsrcTbl->GetResourceTypeById((WORD)RT_DIALOG);

	if (RsrcType)
	{
		hTreechild = m_tree.InsertItem("RT_DIALOG",
									ILI_CLOSED_FOLDER,
									ILI_OPEN_FOLDER,hTreeroot);

		m_tree.InsertItem("",ILI_CLOSED_FOLDER,
							ILI_CLOSED_FOLDER,
							hTreechild);
		delete RsrcType;
		
	}


	return TRUE;

}

void CResourceTree::DeleteFirstChild(HTREEITEM hParent)
{
	HTREEITEM hItem;
    if ((hItem = GetTreeCtrl ().GetChildItem (hParent)) != NULL)
        GetTreeCtrl ().DeleteItem (hItem);

}

void CResourceTree::DeleteAllChildren(HTREEITEM hParent)
{
	HTREEITEM hItem;
    if ((hItem = GetTreeCtrl ().GetChildItem (hParent)) == NULL)
        return;

    do {
        HTREEITEM hNextItem = GetTreeCtrl ().GetNextSiblingItem (hItem);
        GetTreeCtrl ().DeleteItem (hItem);
        hItem = hNextItem;
    } while (hItem != NULL);

}

void CResourceTree::AddResourceInst(HTREEITEM hitem)
{
	//
	// when a resource item is expanded we look for 
	// each instance of the resource and add it 
	// to the tree.

	PERsrcType * RsrcType;
	PERsrcInst * RsrcInst;
	HTREEITEM ItemInst;
	DWORD WordParm;
	CString ItemText;
	DWORD RsrcID;
	CHAR szRsrcID[255];
	CTreeCtrl& m_tree = GetTreeCtrl();

	CResviewerDoc* pDoc = (CResviewerDoc*)GetDocument();
	PERsrcTbl* RsrcTbl = pDoc->GetPERsrc();

	if (!RsrcTbl)
		return;

	ItemText = GetTreeCtrl().GetItemText(hitem);
	

	if (ItemText == "RT_ICON")
	{

		RsrcType = RsrcTbl->GetResourceTypeById((WORD)RT_ICON);

		RsrcInst = RsrcType->GetNextResourceInst(0);

		if (RsrcInst)
		{

			do
			{
				
				RsrcID = RsrcInst->Id();
				if (RsrcID & 0x80000000)
				{
					RsrcInst->Name(szRsrcID,sizeof(szRsrcID));
					// Icon resoure name
					WordParm = MAKELPARAM(1,(WORD)RT_ICON);
				}
					
				else
				{
					itoa(RsrcID,szRsrcID,10);
					// Icon resource ID
					WordParm = MAKELPARAM(0,(WORD)RT_ICON);
					
				}
				ItemInst = m_tree.InsertItem(szRsrcID,
									ILI_CLOSED_FOLDER,
									ILI_CLOSED_FOLDER,hitem);
				
				m_tree.SetItemData(ItemInst,WordParm);

				RsrcInst = RsrcType->GetNextResourceInst(RsrcInst);

			}
			while(RsrcInst);
			delete RsrcType;
			
		}
	} // end rt_icon

	if (ItemText == "RT_BITMAP")
	{

		RsrcType = RsrcTbl->GetResourceTypeById((WORD)RT_BITMAP);

		RsrcInst = RsrcType->GetNextResourceInst(0);

		if (RsrcInst)
		{

			do
			{
				RsrcID = RsrcInst->Id();
				if (RsrcID & 0x80000000)
				{
					RsrcInst->Name(szRsrcID,sizeof(szRsrcID));
					// bitmap resoure name
					WordParm = MAKELPARAM(1,(WORD)RT_BITMAP);
				}
					
				else
				{
					itoa(RsrcID,szRsrcID,10);
					// bitmap resource ID
					WordParm = MAKELPARAM(0,(WORD)RT_BITMAP);
					
				}
				
				
				ItemInst = m_tree.InsertItem(szRsrcID,
									ILI_CLOSED_FOLDER,
									ILI_CLOSED_FOLDER,hitem);
				
				m_tree.SetItemData(ItemInst,WordParm);
				
				RsrcInst = RsrcType->GetNextResourceInst(RsrcInst);

			}
			while(RsrcInst);
			delete RsrcType;
			
		}
	}  // end rt_bitmap



	if (ItemText == "RT_CURSOR")
	{

		RsrcType = RsrcTbl->GetResourceTypeById((WORD)RT_CURSOR);

		RsrcInst = RsrcType->GetNextResourceInst(0);

		if (RsrcInst)
		{

			do
			{
				RsrcID = RsrcInst->Id();
				if (RsrcID & 0x80000000)
				{
					RsrcInst->Name(szRsrcID,sizeof(szRsrcID));
					// bitmap resoure name
					WordParm = MAKELPARAM(1,(WORD)RT_CURSOR);
				}
					
				else
				{
					itoa(RsrcID,szRsrcID,10);
					// bitmap resource ID
					WordParm = MAKELPARAM(0,(WORD)RT_CURSOR);
					
				}
				
				
				ItemInst = m_tree.InsertItem(szRsrcID,
									ILI_CLOSED_FOLDER,
									ILI_CLOSED_FOLDER,hitem);
				
				m_tree.SetItemData(ItemInst,WordParm);
				
				RsrcInst = RsrcType->GetNextResourceInst(RsrcInst);

			}
			while(RsrcInst);
			delete RsrcType;
			
		}
	}  // end rt_cursor

	if (ItemText == "RT_DIALOG")
	{

		RsrcType = RsrcTbl->GetResourceTypeById((WORD)RT_DIALOG);

		RsrcInst = RsrcType->GetNextResourceInst(0);

		if (RsrcInst)
		{

			do
			{
				RsrcID = RsrcInst->Id();
				if (RsrcID & 0x80000000)
				{
					RsrcInst->Name(szRsrcID,sizeof(szRsrcID));
					// bitmap resoure name
					WordParm = MAKELPARAM(1,(WORD)RT_DIALOG);
				}
					
				else
				{
					itoa(RsrcID,szRsrcID,10);
					// bitmap resource ID
					WordParm = MAKELPARAM(0,(WORD)RT_DIALOG);
					
				}
				
				
				ItemInst = m_tree.InsertItem(szRsrcID,
									ILI_CLOSED_FOLDER,
									ILI_CLOSED_FOLDER,hitem);
				
				m_tree.SetItemData(ItemInst,WordParm);
				
				RsrcInst = RsrcType->GetNextResourceInst(RsrcInst);

			}
			while(RsrcInst);
			delete RsrcType;
			
		}
	}  // end rt_dialog

	return;

}




void CResourceTree::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
    //CString string = GetPathFromNode (hItem);

	*pResult = 0;

	// return if at highest level;
	if (GetTreeCtrl().GetParentItem(hItem) == NULL)
		return;

	*pResult = 0;
	if (pNMTreeView->action == TVE_EXPAND)
	{
       DeleteFirstChild (hItem);
       AddResourceInst(hItem);
       
    }
    else 
	{ // pnmtv->action == TVE_COLLAPSE
		DeleteAllChildren (hItem);
        
        GetTreeCtrl ().InsertItem ("", ILI_CLOSED_FOLDER,
							        ILI_CLOSED_FOLDER, hItem);
		
        
    }
}

void CResourceTree::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// get and save the selected item in the document 
	// variables. the listview uses the variables 
	// when displaying the resources 
	//

	// TODO: Add your control notification handler code here
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	CResviewerDoc* pDoc = (CResviewerDoc*)GetDocument();
	RESINFO Res;

	CPoint		ptAction;
	UINT		nFlags;

	GetCursorPos(&ptAction);
	ScreenToClient(&ptAction);
	*pResult = 0;
	HTREEITEM hitem = GetTreeCtrl().HitTest(ptAction, &nFlags);

	HTREEITEM hParent;
	hParent = GetTreeCtrl().GetParentItem(hitem);
	if (!hParent)
		return;

	CString text = GetTreeCtrl().GetItemText(hParent);
	INT rc = strncmp(text,"RT_",3);
	if (rc == 0) // equal
	{
		DWORD RsrcID = GetTreeCtrl().GetItemData(hitem);
		WORD Name = (WORD)LOWORD(RsrcID);
		Res.riType = (WORD)HIWORD(RsrcID);
		CString Rsrc = GetTreeCtrl().GetItemText(hitem);
		
		if (Name)
		{
			strcpy(Res.riIDName,Rsrc);
			Res.riIDNum = 0;
		}
		else
		{
			Res.riIDNum = atol(Rsrc);
		}

		pDoc->SetCurrentItem(&Res); // tell document 
		pDoc->UpdateAllViews(this,(LPARAM)&Res); // tell view
		*pResult = 0;
	}


	
	
}

void CResourceTree::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	//CResviewerDoc* pDoc = (CResviewerDoc*)GetDocument();
	//PERsrcTbl* RsrcTbl = pDoc->GetPERsrc();

	//if (!RsrcTbl)
	//	return;

	//InitTree(RsrcTbl);

}
