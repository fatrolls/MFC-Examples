#include "stdafx.h"
#include "Explorer.h"
#include "Doc.h"
#include "FormView.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDirFormView, CFormView)

CDirFormView::CDirFormView() : CFormView(CDirFormView::IDD)
{
	//{{AFX_DATA_INIT(CDirFormView)
	//}}AFX_DATA_INIT
}

CDirFormView::~CDirFormView()
{
}

void CDirFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirFormView)
	DDX_Control(pDX, IDC_TREECTRL, m_tcDir);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDirFormView, CFormView)
	//{{AFX_MSG_MAP(CDirFormView)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_TREECTRL, OnClickTreeCtrl)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREECTRL, OnItemExpandingTreeCtrl)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#ifdef _DEBUG
void CDirFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDirFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif

void CDirFormView::OnInitialUpdate() 
{
	TV_INSERTSTRUCT tvInsertStruct;
	HTREEITEM hTreeItem;
	CImageList *pilCtrl;
	CBitmap bmp;
	char buffer[MAX_COMPUTERNAME_LENGTH+1];
	DWORD dwSize=MAX_COMPUTERNAME_LENGTH+1;
	int drive, curdrive;
	CRect rect;

	CFormView::OnInitialUpdate();
	ResizeTreeView();
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
	m_tcDir.SetImageList(pilCtrl, TVSIL_NORMAL);

	tvInsertStruct.hParent=NULL;
	tvInsertStruct.hInsertAfter=TVI_LAST;
	tvInsertStruct.item.iImage=0;
	tvInsertStruct.item.iSelectedImage=0;
	tvInsertStruct.item.pszText="Desktop";
	tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_STATE;
	tvInsertStruct.item.stateMask|=TVIS_EXPANDED;
	tvInsertStruct.item.state|=TVIS_EXPANDED;

	hTreeItem=m_tcDir.InsertItem(&tvInsertStruct);
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

	hTreeItem=m_tcDir.InsertItem(&tvInsertStruct);
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

			hSubItem=m_tcDir.InsertItem(&tvInsertStruct);
			ASSERT(hSubItem);

			if(_getcwd(m_szPath, _MAX_PATH) != NULL)
			{
				_chdir("\\");
				AddDirs(hSubItem, TRUE);
				_chdir(m_szPath);
			}
		}
	}

	_chdrive(curdrive);
}

void CDirFormView::AddDirs(HTREEITEM hTreeItem, BOOL bFindChild)
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
			tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
			tvInsertStruct.item.iImage=4;
			tvInsertStruct.item.iSelectedImage=4;
			tvInsertStruct.item.pszText=(LPSTR)(const char *)szFilePath;

			hSubItem=m_tcDir.InsertItem(&tvInsertStruct);
			ASSERT(hSubItem);

			if(!ff.IsDots())
			{
				if(bFindChild == TRUE)
				{
					szFilePath=ff.GetFilePath();
					_getcwd(path, _MAX_PATH);
					_chdir((LPCSTR)szFilePath);
					AddDirs(hSubItem, FALSE);
					_chdir(path);
				}
			}
		}
	}
	ff.Close();
}

void CDirFormView::OnDestroy() 
{
	CImageList *pilCtrl;

	m_tcDir.DeleteAllItems();
	pilCtrl=m_tcDir.GetImageList(TVSIL_NORMAL);
	pilCtrl->DeleteImageList();
	delete pilCtrl;

	CFormView::OnDestroy();
}

void CDirFormView::OnClickTreeCtrl(NMHDR *pNMHDR, LRESULT *pResult) 
{
	CPoint pt;
	HTREEITEM hItem;
	UINT nFlags;
	CString szPath;
	char path[_MAX_PATH];

	::GetCursorPos(&pt);
	m_tcDir.ScreenToClient(&pt);
	hItem=m_tcDir.HitTest(pt, &nFlags);
	if(hItem != NULL)
	{
		szPath=m_tcDir.GetItemText(hItem);
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

	*pResult = 0;
}

void CDirFormView::AddChildrenChildren(HTREEITEM hItem)
{
	CString szPath;
	CString szDir;
	CString szText;
	char path[_MAX_PATH];
	HTREEITEM hItemChild;

	_getcwd(path, _MAX_PATH);
	if(hItem != NULL)
	{
		szPath=GetDir(hItem);
		hItemChild=m_tcDir.GetChildItem(hItem);
		while(hItemChild != NULL)
		{
			if(!m_tcDir.ItemHasChildren(hItemChild))
			{
				szText=m_tcDir.GetItemText(hItemChild);
				if(szText.Find('.') == -1)
				{
					szDir=szPath+'\\'+szText;
					_chdir((LPCSTR)szDir);
					AddDirs(hItemChild, FALSE);
				}
			}			
			hItemChild=m_tcDir.GetNextSiblingItem(hItemChild);
		}
	}
	_chdir(path);
}

CString CDirFormView::GetDir(HTREEITEM hItem)
{
	CString szPath;
	CString szFile;

	if(hItem != NULL)
	{
		szFile=m_tcDir.GetItemText(hItem);
		if(szFile.Find(':') == -1)
		{
			szPath=szFile;
			hItem=m_tcDir.GetParentItem(hItem);
			while(hItem != NULL)
			{
				szFile=m_tcDir.GetItemText(hItem);
				szPath=szFile+'\\'+szPath;
				if(szFile.Find(':') != -1)break;
				hItem=m_tcDir.GetParentItem(hItem);
			}
		}
		else szPath=szFile;
	}
	return szPath;
}

void CDirFormView::OnItemExpandingTreeCtrl(NMHDR *pNMHDR, LRESULT *pResult) 
{
	NM_TREEVIEW *pNMTreeView=(NM_TREEVIEW *)pNMHDR;
	
	CPoint pt;
	HTREEITEM hItem;
	UINT nFlags;
	CString szFile;

	if(pNMTreeView->action == TVE_EXPAND)
	{
		::GetCursorPos(&pt);
		ScreenToClient(&pt);
		hItem=m_tcDir.HitTest(pt, &nFlags);
		if(hItem != NULL)
		{
			AddChildrenChildren(hItem);
		}
	}
	if
	(
		pNMTreeView->action == TVE_EXPAND &&
		pNMTreeView->itemNew.iImage == 4
	)
	{
		m_tcDir.SetItemImage(pNMTreeView->itemNew.hItem, 5, 5);
	}
	if
	(
		pNMTreeView->action == TVE_COLLAPSE &&
		pNMTreeView->itemNew.iImage == 5
	)
	{
		m_tcDir.SetItemImage(pNMTreeView->itemNew.hItem, 4, 4);
	}

	*pResult = 0;
}

void CDirFormView::OnSize(UINT nType, int cx, int cy) 
{
	ResizeTreeView();
	CFormView::OnSize(nType, cx, cy);
}

void CDirFormView::ResizeTreeView()
{
	CRect rect;

	GetClientRect(rect);
	if(rect.Width() > 2*BORDER_WIDTH)
	{
		rect.left+=BORDER_WIDTH;
		rect.right-=BORDER_WIDTH;
	}
	if(rect.Height() > 2*BORDER_WIDTH)
	{
		rect.top+=BORDER_WIDTH;
		rect.bottom-=BORDER_WIDTH;
	}
	if(::IsWindow(m_tcDir.m_hWnd))m_tcDir.MoveWindow(rect);
}
