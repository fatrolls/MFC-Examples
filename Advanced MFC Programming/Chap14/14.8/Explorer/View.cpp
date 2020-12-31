#include "stdafx.h"
#include "Explorer.h"
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
			nNumImages++;
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
			
			lvi.mask=LVIF_TEXT | LVIF_IMAGE;
			lvi.iItem=i;
			lvi.iSubItem=0;
			lvi.pszText=(LPSTR)(const char *)szFileName;

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
