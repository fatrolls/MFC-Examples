#include "stdafx.h"
#include "Explorer.h"
#include "MainFrm.h"
#include "Doc.h"
#include "View.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NUM_COLUMNS		4

static _TCHAR *g_szColumnLabel[NUM_COLUMNS] =
{
	_T("Name"), _T("Size"), _T("Type"), _T("Modified")
};

static int g_nColumnFmt[NUM_COLUMNS] = 
{
	LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT
};

static int g_nColumnWidth[NUM_COLUMNS] = 
{
	150, 150, 150, 150
};

IMPLEMENT_DYNCREATE(CExplorerView, CListView)

BEGIN_MESSAGE_MAP(CExplorerView, CListView)
	//{{AFX_MSG_MAP(CExplorerView)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

CExplorerView::CExplorerView()
{
}

CExplorerView::~CExplorerView()
{
}

BOOL CExplorerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

void CExplorerView::OnDraw(CDC* pDC)
{
	CExplorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CExplorerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CExplorerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CExplorerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CExplorerView::DestroyList()
{
	CImageList *pilCtrl;

	GetListCtrl().DeleteAllItems();
	pilCtrl=GetListCtrl().GetImageList(LVSIL_NORMAL);
	if(pilCtrl != NULL)
	{
		pilCtrl->DeleteImageList();
		delete pilCtrl;
	}
	pilCtrl=GetListCtrl().GetImageList(LVSIL_SMALL);
	if(pilCtrl != NULL)
	{
		pilCtrl->DeleteImageList();
		delete pilCtrl;
	}
}

HICON CExplorerView::GetIconFromFile(CString szFileName, UINT uFlags)
{
	SHFILEINFO shfi;

	::SHGetFileInfo(szFileName, 0, &shfi, sizeof(SHFILEINFO), SHGFI_ICON | uFlags);

	return shfi.hIcon;
}

void CExplorerView::ChangeDir()
{
	CFileFind ff;
	CString szFileName;
	CString szExt;
	CString szText;
	CStringArray szArray;
	BOOL bWorking;
	BOOL bUseDefaultSmallIcon;
	BOOL bUseDefaultNormalIcon;
	LV_COLUMN lvc;
	LV_ITEM lvi;
	CImageList *pilNormal;
	CImageList *pilSmall;
	int nNumImages;
	int nIndex;
	int i, j;
	CBitmap bmp;
	CTime time;
	HICON hIcon;

	DestroyList();
	
	pilNormal=new CImageList();
	pilSmall=new CImageList();

	nNumImages=0;
	bWorking=ff.FindFile();
	while(bWorking)
	{
		bWorking=ff.FindNextFile();
		if(!ff.IsDirectory())
		{
			szFileName=ff.GetFileName();
			nIndex=szFileName.ReverseFind('.');
			if(nIndex != -1)
			{
				szExt=szFileName.Right(szFileName.GetLength()-nIndex-1);
			}
			szExt.MakeLower();
			if(szExt == "exe" || szExt == "dll")nNumImages++;
		}
	}
	ff.Close();

	pilSmall->Create(BMP_SIZE_X, BMP_SIZE_Y, ILC_MASK, 2, nNumImages);
	bmp.LoadBitmap(IDB_BITMAP_CLOSEFOLDER);
	ASSERT(bmp.GetSafeHandle());
	pilSmall->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();
	bmp.LoadBitmap(IDB_BITMAP_FILE);
	ASSERT(bmp.GetSafeHandle());
	pilSmall->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	pilNormal->Create(BIGBMP_SIZE_X, BIGBMP_SIZE_Y, ILC_MASK, 2, nNumImages);
	bmp.LoadBitmap(IDB_BITMAP_CLOSEFOLDERBIG);
	ASSERT(bmp.GetSafeHandle());
	pilNormal->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();
	bmp.LoadBitmap(IDB_BITMAP_FILEBIG);
	ASSERT(bmp.GetSafeHandle());
	pilNormal->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	GetListCtrl().SetImageList(pilSmall, LVSIL_SMALL);
	GetListCtrl().SetImageList(pilNormal, LVSIL_NORMAL);

	lvc.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for(i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem=i;
		lvc.pszText=g_szColumnLabel[i];
		lvc.cx=g_nColumnWidth[i];
		lvc.fmt=g_nColumnFmt[i];
		GetListCtrl().InsertColumn(i,&lvc);
	}

	nNumImages=2;
	bWorking=ff.FindFile();
	i=0;
	while(bWorking)
	{
		bWorking=ff.FindNextFile();
		if(!ff.IsDots())
		{
			bUseDefaultNormalIcon=TRUE;
			bUseDefaultSmallIcon=TRUE;

			if(!ff.IsDirectory())
			{
				szFileName=ff.GetFilePath();
				hIcon=GetIconFromFile(szFileName, SHGFI_LARGEICON);
				if(hIcon != NULL)
				{
					pilNormal->Add(hIcon);
					bUseDefaultNormalIcon=FALSE;
					nNumImages++;
				}
				else
				{
					hIcon=GetIconFromFile(szFileName, SHGFI_SHELLICONSIZE);
					if(hIcon != NULL)
					{
						pilNormal->Add(hIcon);
						bUseDefaultNormalIcon=FALSE;
						nNumImages++;
					}
				}

				hIcon=GetIconFromFile(szFileName, SHGFI_SMALLICON);
				if(hIcon != NULL)
				{
					pilSmall->Add(hIcon);
					bUseDefaultSmallIcon=FALSE;
				}
				else
				{
					hIcon=GetIconFromFile(szFileName, SHGFI_SHELLICONSIZE | SHGFI_SMALLICON);
					if(hIcon != NULL)
					{
						pilSmall->Add(hIcon);
						bUseDefaultSmallIcon=FALSE;
					}
					else
					{
						if(bUseDefaultNormalIcon == FALSE)
						{
							bmp.LoadBitmap(IDB_BITMAP_FILE);
							ASSERT(bmp.GetSafeHandle());
							pilSmall->Add(&bmp, RGB(255, 255, 255));
							bmp.DeleteObject();
							bUseDefaultSmallIcon=FALSE;
						}
					}
				}

				if(bUseDefaultNormalIcon == TRUE && bUseDefaultSmallIcon == FALSE)
				{
					bmp.LoadBitmap(IDB_BITMAP_FILEBIG);
					ASSERT(bmp.GetSafeHandle());
					pilNormal->Add(&bmp, RGB(255, 255, 255));
					bmp.DeleteObject();
					bUseDefaultNormalIcon=FALSE;
					nNumImages++;
				}
			}

			szFileName=ff.GetFileName();
			
			lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
			lvi.iItem=i;
			lvi.iSubItem=0;
			lvi.pszText=(LPSTR)(const char *)szFileName;
			lvi.lParam=(LPARAM)i;

			if(ff.IsDirectory())
			{
				lvi.iImage=0;
			}
			else
			{
				if(bUseDefaultNormalIcon == TRUE)
				{
					lvi.iImage=1;
				}
				else
				{
					lvi.iImage=nNumImages-1;
				}
			}
			
			GetListCtrl().InsertItem(&lvi);

			if(!ff.IsDirectory())
			{
				szText.Empty();
				szText.Format("%lu Bytes", ff.GetLength());
				szArray.Add(szText);
				szText.Empty();
				szText="File";
			}
			else
			{
				szArray.Add("");
				szText="Folder";
			}
			szArray.Add(szText);

			ff.GetLastWriteTime(time);
			szText.Empty();
			szText=time.Format("%d/%m/%Y %I:%M%p");
			szArray.Add(szText);
		}
		i++;
	}

	for(i=0; i<GetListCtrl().GetItemCount(); i++)
	{
		for(j=1; j<NUM_COLUMNS; j++)
		{
			GetListCtrl().SetItemText(i, j, szArray[i*(NUM_COLUMNS-1)+j-1]);
		}
	}
	szArray.RemoveAll();
	ff.Close();
}

#ifdef _DEBUG
void CExplorerView::AssertValid() const
{
	CListView::AssertValid();
}

void CExplorerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CExplorerDoc* CExplorerView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExplorerDoc)));
	return (CExplorerDoc*)m_pDocument;
}
#endif

void CExplorerView::OnDestroy() 
{
	DestroyList();
	CListView::OnDestroy();
}

void CExplorerView::OnInitialUpdate() 
{
	int drive;

	CListView::OnInitialUpdate();
	
	for(drive=1; drive <= 26; drive++)
	{
		if(_chdrive(drive) != -1)
		{
			if(_chdir("\\") != -1)break;
		}
	}

	ChangeDir();
}

void CExplorerView::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW*)pNMHDR;

	GetListCtrl().SortItems(CompareFunc, pNMListView->iSubItem);

	*pResult=0;
}

int CALLBACK CExplorerView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl &lc=
	(
		(CExplorerDoc *)(((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetActiveDocument())
	)->GetCExplorerView()->GetListCtrl();

	switch((int)lParamSort)
	{
		case 0:
		{
			return CompareByName(lParam1, lParam2, lc);
			break;
		}
		case 1:
		{
			return CompareBySize(lParam1, lParam2, lc);
			break;
		}
		case 2:
		{
			return CompareByType(lParam1, lParam2, lc);
			break;
		}
		case 3:
		{
			return CompareByDate(lParam1, lParam2, lc);
			break;
		}
	}

	return 0;
}

int CExplorerView::CompareByName(LPARAM lParam1, LPARAM lParam2, CListCtrl &lc)
{
	CString szName1;
	CString szName2;
	LV_ITEM lvi1;
	LV_ITEM lvi2;
	int nSize;
	int i;
	int nItem1;
	int nItem2;

	nItem1=FindItem(lParam1, lc);
	nItem2=FindItem(lParam2, lc);

	memset(&lvi1, 0, sizeof(LV_ITEM));
	memset(&lvi2, 0, sizeof(LV_ITEM));
	lvi1.mask|=LVIF_IMAGE;
	lvi1.iItem=nItem1;
	lvi2.mask|=LVIF_IMAGE;
	lvi2.iItem=nItem2;
	lc.GetItem(&lvi1);
	lc.GetItem(&lvi2);
	szName1=lc.GetItemText(nItem1, 0);
	szName2=lc.GetItemText(nItem2, 0);
	if(lvi1.iImage == 0 && lvi2.iImage != 0)return -1;
	if(lvi1.iImage != 0 && lvi2.iImage == 0)return 1;

	nSize=min(szName1.GetLength(), szName2.GetLength());
	szName1.MakeLower();
	szName2.MakeLower();
	for(i=0; i<nSize; i++)
	{
		if(szName1[i] < szName2[i])return -1;
		if(szName1[i] > szName2[i])return 1;
	}
	if(i == nSize)
	{
		if(szName1.GetLength() < szName2.GetLength())return -1;
		if(szName1.GetLength() > szName2.GetLength())return 1;
	}

	return 0;
}

int CExplorerView::CompareBySize(LPARAM lParam1, LPARAM lParam2, CListCtrl &lc)
{
	CString szSize1;
	CString szSize2;
	LV_ITEM lvi1;
	LV_ITEM lvi2;
	int nItem1;
	int nItem2;
	int nSize1;
	int nSize2;

	nItem1=FindItem(lParam1, lc);
	nItem2=FindItem(lParam2, lc);

	memset(&lvi1, 0, sizeof(LV_ITEM));
	memset(&lvi2, 0, sizeof(LV_ITEM));
	lvi1.mask|=LVIF_IMAGE;
	lvi1.iItem=nItem1;
	lvi2.mask|=LVIF_IMAGE;
	lvi2.iItem=nItem2;
	lc.GetItem(&lvi1);
	lc.GetItem(&lvi2);
	szSize1=lc.GetItemText(nItem1, 1);
	szSize2=lc.GetItemText(nItem2, 1);
	if(lvi1.iImage == 0 && lvi2.iImage != 0)return -1;
	if(lvi1.iImage != 0 && lvi2.iImage == 0)return 1;

	szSize1=szSize1.Left(szSize1.GetLength()-6);
	nSize1=atoi((LPCSTR)szSize1);
	szSize2=szSize2.Left(szSize2.GetLength()-6);
	nSize2=atoi((LPCSTR)szSize2);

	if(nSize1 < nSize2)return -1;
	if(nSize1 > nSize2)return 1;

	return 0;
}

int CExplorerView::CompareByType(LPARAM lParam1, LPARAM lParam2, CListCtrl &lc)
{
	CString szName1;
	CString szName2;
	CString szExt1;
	CString szExt2;
	LV_ITEM lvi1;
	LV_ITEM lvi2;
	int nSize;
	int i;
	int nItem1;
	int nItem2;

	nItem1=FindItem(lParam1, lc);
	nItem2=FindItem(lParam2, lc);

	memset(&lvi1, 0, sizeof(LV_ITEM));
	memset(&lvi2, 0, sizeof(LV_ITEM));
	lvi1.mask|=LVIF_IMAGE;
	lvi1.iItem=nItem1;
	lvi2.mask|=LVIF_IMAGE;
	lvi2.iItem=nItem2;
	lc.GetItem(&lvi1);
	lc.GetItem(&lvi2);
	szName1=lc.GetItemText(nItem1, 0);
	szName2=lc.GetItemText(nItem2, 0);
	if(lvi1.iImage == 0 && lvi2.iImage != 0)return -1;
	if(lvi1.iImage != 0 && lvi2.iImage == 0)return 1;

	if(szName1.Find('.') == -1 && szName2.Find('.') != -1)return -1;
	if(szName1.Find('.') != -1 && szName2.Find('.') == -1)return 1;
	if(szName1.Find('.') == -1 && szName2.Find('.') == -1)
	{
		return CompareByName(lParam1, lParam2, lc);
	}

	szExt1=szName1.Right(szName1.GetLength()-szName1.Find('.')-1);
	szExt2=szName2.Right(szName2.GetLength()-szName2.Find('.')-1);

	nSize=min(szExt1.GetLength(), szExt2.GetLength());
	szExt1.MakeLower();
	szExt2.MakeLower();
	for(i=0; i<nSize; i++)
	{
		if(szExt1[i] < szExt2[i])return -1;
		if(szExt1[i] > szExt2[i])return 1;
	}
	if(i == nSize)
	{
		if(szExt1.GetLength() < szExt2.GetLength())return -1;
		if(szExt1.GetLength() > szExt2.GetLength())return 1;
	}

	return 0;
}

int CExplorerView::CompareByDate(LPARAM lParam1, LPARAM lParam2, CListCtrl &lc)
{
	CTime time1;
	CTime time2;
	CString szTime1;
	CString szTime2;
	int nItem1;
	int nItem2;
	int nYear;
	int nMonth;
	int nDay;
	int nHour;
	int nMin;
	BOOL bAM;

	nItem1=FindItem(lParam1, lc);
	nItem2=FindItem(lParam2, lc);

	szTime1=lc.GetItemText(nItem1, 3);
	if(szTime1.Find("AM") != -1)bAM=TRUE;
	else bAM=FALSE;
	sscanf((LPCSTR)szTime1, "%d/%d/%d %d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin);
	if(bAM == FALSE)nHour+=12;
	time1=CTime(nYear, nMonth, nDay, nHour, nMin, 0);

	szTime2=lc.GetItemText(nItem2, 3);
	if(szTime2.Find("AM") != -1)bAM=TRUE;
	else bAM=FALSE;
	sscanf((LPCSTR)szTime2, "%d/%d/%d %d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin);
	if(bAM == FALSE)nHour+=12;
	time2=CTime(nYear, nMonth, nDay, nHour, nMin, 0);

	if(time1 < time2)return -1;
	if(time1 > time2)return 1;

	return 0;
}

int CExplorerView::FindItem(LPARAM lParam, CListCtrl &lc)
{
	LV_FINDINFO lvfi;

	memset(&lvfi, 0, sizeof(LV_FINDINFO));
	lvfi.flags|=LVFI_PARAM;
	lvfi.lParam=lParam;

	return lc.FindItem(&lvfi);
}