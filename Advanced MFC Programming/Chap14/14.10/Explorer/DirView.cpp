#include "stdafx.h"
#include "Explorer.h"
#include "Doc.h"
#include "DirView.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDirView, CTreeView)

CDirView::CDirView()
{
}

CDirView::~CDirView()
{
}


BEGIN_MESSAGE_MAP(CDirView, CTreeView)
	//{{AFX_MSG_MAP(CDirView)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblClk)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDirView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

#ifdef _DEBUG
void CDirView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDirView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif

void CDirView::OnInitialUpdate() 
{
	TV_INSERTSTRUCT tvInsertStruct;
	HTREEITEM hTreeItem;
	CImageList *pilCtrl;
	CBitmap bmp;
	char buffer[MAX_COMPUTERNAME_LENGTH+1];
	DWORD dwSize=MAX_COMPUTERNAME_LENGTH+1;
	LONG lStyleOld;
	int drive, curdrive;

	pilCtrl=new CImageList();
	pilCtrl->Create(BMP_SIZE_X, BMP_SIZE_Y, ILC_MASK, 6, 0);
	
	bmp.LoadBitmap(IDB_BITMAP_DESKTOP);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();
	
	bmp.LoadBitmap(IDB_BITMAP_COMPUTER);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP_HARD);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP_FLOOPY);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP_CLOSEFOLDER);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP_OPENFOLDER);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	pilCtrl->SetBkColor(RGB(255, 255, 255));
	GetTreeCtrl().SetImageList(pilCtrl, TVSIL_NORMAL);

	lStyleOld=::GetWindowLong(GetTreeCtrl().GetSafeHwnd(), GWL_STYLE);
	lStyleOld|=TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	::SetWindowLong(GetTreeCtrl().GetSafeHwnd(), GWL_STYLE, lStyleOld);

	memset(&tvInsertStruct, 0, sizeof(TV_INSERTSTRUCT));

	tvInsertStruct.hParent=NULL;
	tvInsertStruct.hInsertAfter=TVI_LAST;
	tvInsertStruct.item.iImage=0;
	tvInsertStruct.item.iSelectedImage=0;
	tvInsertStruct.item.pszText="Desktop";
	tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_STATE;
	tvInsertStruct.item.stateMask|=TVIS_EXPANDED;
	tvInsertStruct.item.state|=TVIS_EXPANDED;

	hTreeItem=GetTreeCtrl().InsertItem(&tvInsertStruct);
	ASSERT(hTreeItem);

	::GetComputerName(buffer, &dwSize);

	tvInsertStruct.hParent=hTreeItem;
	tvInsertStruct.hInsertAfter=TVI_LAST;
	tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_STATE;
	tvInsertStruct.item.iImage=1;
	tvInsertStruct.item.iSelectedImage=1;
	tvInsertStruct.item.pszText=buffer;
	tvInsertStruct.item.stateMask|=TVIS_EXPANDED;
	tvInsertStruct.item.state|=TVIS_EXPANDED;

	hTreeItem=GetTreeCtrl().InsertItem(&tvInsertStruct);
	ASSERT(hTreeItem);

	curdrive=_getdrive();
	for(drive=1; drive <= 26; drive++)
	{
		if(!_chdrive(drive))
		{
			HTREEITEM hSubItem;

			memset(buffer, 0, dwSize);
			buffer[0]=drive+'A'-1;
			buffer[1]=':';
			tvInsertStruct.hParent=hTreeItem;
			tvInsertStruct.hInsertAfter=TVI_LAST;
			tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_STATE;
			tvInsertStruct.item.iImage=2;
			tvInsertStruct.item.iSelectedImage=2;
			tvInsertStruct.item.pszText=buffer;
			tvInsertStruct.item.stateMask|=TVIS_EXPANDED;
			tvInsertStruct.item.state|=TVIS_EXPANDED;

			hSubItem=GetTreeCtrl().InsertItem(&tvInsertStruct);
			ASSERT(hSubItem);

			if(_getcwd(m_szPath, _MAX_PATH) != NULL)
			{
				_chdir("\\");
				AddDirs(hSubItem);
				_chdir(m_szPath);
			}
		}
	}

	_chdrive(curdrive);

	CTreeView::OnInitialUpdate();
}

void CDirView::AddDirs(HTREEITEM hTreeItem)
{
	CFileFind ff;
	CString szFilePath;
	CString szCompare;
	BOOL bWorking;
	HTREEITEM hSubItem;
	TV_INSERTSTRUCT tvInsertStruct;
	char path[_MAX_PATH];

	memset(&tvInsertStruct, 0, sizeof(TV_INSERTSTRUCT));
	bWorking=ff.FindFile();
	while(bWorking)
	{
		bWorking=ff.FindNextFile();
		if(ff.IsDirectory())
		{
			szFilePath=ff.GetFileName();
			
			tvInsertStruct.hParent=hTreeItem;
			tvInsertStruct.hInsertAfter=TVI_LAST;
			tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_STATE;
			tvInsertStruct.item.iImage=4;
			tvInsertStruct.item.iSelectedImage=4;
			tvInsertStruct.item.pszText=(LPSTR)(const char *)szFilePath;
			tvInsertStruct.item.stateMask|=TVIS_EXPANDED;
			tvInsertStruct.item.state|=TVIS_EXPANDED;

			hSubItem=GetTreeCtrl().InsertItem(&tvInsertStruct);
			ASSERT(hSubItem);

			if(!ff.IsDots())
			{
				if(_getcwd(path, _MAX_PATH) != NULL)
				{
					szCompare=m_szPath;
					szFilePath=ff.GetFilePath();
					if(szFilePath.GetLength() < szCompare.GetLength())
					{
						szCompare=szCompare.Left(szFilePath.GetLength());
						if(szFilePath.CompareNoCase((LPCSTR)szCompare) == 0)
						{
							_chdir(szFilePath);
							AddDirs(hSubItem);
							_chdir(path);
						}
					}
				}
			}
		}
	}
	ff.Close();
}

void CDirView::OnDestroy() 
{
	CImageList *pilCtrl;

	GetTreeCtrl().DeleteAllItems();
	pilCtrl=GetTreeCtrl().GetImageList(TVSIL_NORMAL);
	pilCtrl->DeleteImageList();
	delete pilCtrl;

	CTreeView::OnDestroy();
}

void CDirView::OnClick(NMHDR *pNMHDR, LRESULT *pResult) 
{
	CPoint pt;
	HTREEITEM hItem;
	UINT nFlags;
	CString szPath;
	char path[_MAX_PATH];

	::GetCursorPos(&pt);
	ScreenToClient(&pt);
	hItem=GetTreeCtrl().HitTest(pt, &nFlags);
	if(hItem != NULL)
	{
		szPath=GetTreeCtrl().GetItemText(hItem);
		if(szPath.Find('.') == -1)
		{
			szPath=GetDir(hItem);
			if(szPath.GetLength())
			{
				if(_getcwd(path, _MAX_PATH) != NULL)
				{
					if(stricmp((LPCSTR)szPath, path) != 0)
					{
						if(_chdir((LPCSTR)szPath) == 0)
						{
							((CExplorerDoc *)GetDocument())->ChangePath();
						}
					}
				}
			}
		}
	}
	*pResult=0;
}

void CDirView::OnDblClk(NMHDR *pNMHDR, LRESULT *pResult) 
{
	CPoint pt;
	HTREEITEM hItem;
	UINT nFlags;
	int nImage;
	int nSelImage;
	CString szFile;

	::GetCursorPos(&pt);
	ScreenToClient(&pt);
	hItem=GetTreeCtrl().HitTest(pt, &nFlags);
	if(hItem != NULL)
	{
		if(!GetTreeCtrl().ItemHasChildren(hItem))
		{
			szFile=GetTreeCtrl().GetItemText(hItem);
			if(szFile.Find('.') == -1)
			{
				AddDirs(hItem);
				GetTreeCtrl().GetItemImage(hItem, nImage, nSelImage);
				if(nImage == 4)GetTreeCtrl().SetItemImage(hItem, 5, 5);
				*pResult=TRUE;
			}
		}
	}
	else *pResult=0;
}

CString CDirView::GetDir(HTREEITEM hItem)
{
	CString szPath;
	CString szFile;

	if(hItem != NULL)
	{
		szFile=GetTreeCtrl().GetItemText(hItem);
		if(szFile.Find(':') == -1)
		{
			szPath=szFile;
			hItem=GetTreeCtrl().GetParentItem(hItem);
			while(hItem != NULL)
			{
				szFile=GetTreeCtrl().GetItemText(hItem);
				szPath=szFile+'\\'+szPath;
				if(szFile.Find(':') != -1)break;
				hItem=GetTreeCtrl().GetParentItem(hItem);
			}
		}
		else szPath=szFile;
	}
	return szPath;
}

void CDirView::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW *pNMTreeView=(NM_TREEVIEW *)pNMHDR;
	
	if
	(
		pNMTreeView->action == TVE_EXPAND &&
		pNMTreeView->itemNew.iImage == 4
	)
	{
		GetTreeCtrl().SetItemImage(pNMTreeView->itemNew.hItem, 5, 5);
	}
	if
	(
		pNMTreeView->action == TVE_COLLAPSE &&
		pNMTreeView->itemNew.iImage == 5
	)
	{
		GetTreeCtrl().SetItemImage(pNMTreeView->itemNew.hItem, 4, 4);
	}

	*pResult=0;
}
