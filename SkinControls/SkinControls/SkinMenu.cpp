
#include "stdafx.h"
#include "SkinMenu.h" 
#include "SkinHelper.h"
#include "DrawHelpers.h"
#include "SystemHelpers.h"

#pragma warning(disable : 4244)

#ifndef COLOR_MENUBAR
#define COLOR_MENUBAR       30
#endif

#ifndef SPI_GETDROPSHADOW
#define SPI_GETDROPSHADOW   0x1024
#endif

#ifndef SPI_GETFLATMENU
#define SPI_GETFLATMENU     0x1022
#endif

#ifndef ODS_NOACCEL
#define ODS_NOACCEL         0x0100
#endif

#ifndef DT_HIDEPREFIX
#define DT_HIDEPREFIX		0x00100000
#endif

#ifndef DT_PREFIXONLY
#define DT_PREFIXONLY		0x00200000
#endif

#ifndef SPI_GETKEYBOARDCUES
#define SPI_GETKEYBOARDCUES                 0x100A
#endif

#define MENU_ROUND_CX       5
#define MENU_ROUND_CY       5


// Count of menu icons normal gloomed and grayed
#define MENU_ICONS          3

BOOL bHighContrast = FALSE;

/////////////////////////////////////////////////////////////////////////////
// Helper datatypes
class CToolBarData
{
public:
	WORD wVersion;
	WORD wWidth;
	WORD wHeight;
	WORD wItemCount;
	//WORD aItems[wItemCount]
	WORD* items()
	{ return (WORD*)(this+1); }
};

class CSkinMenuIconInfo
{
public:
	WORD wBitmapID;
	WORD wWidth;
	WORD wHeight;

	WORD* ids(){ return (WORD*)(this+1); }
};

#ifdef _DEBUG
static void ShowLastError(LPCTSTR pErrorTitle=NULL)
{
	if(pErrorTitle==NULL)
	{
		pErrorTitle=_T("Error from Menu");
	}
	DWORD error = GetLastError();
	if(error)
	{
		LPVOID lpMsgBuf=NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL );
		if(lpMsgBuf)
		{
			// Display the string.
			MessageBox( NULL, (LPCTSTR)lpMsgBuf, pErrorTitle, MB_OK | MB_ICONINFORMATION );
			// Free the buffer.
			LocalFree( lpMsgBuf );
		}
		else
		{
			CString temp;
			temp.Format(_T("Error message 0x%lx not found"),error);
			// Display the string.
			MessageBox( NULL,temp, pErrorTitle, MB_OK | MB_ICONINFORMATION );
		}
	}
}
#else
#define ShowLastError(sz)
#endif

BOOL IsShadowEnabled()
{
	BOOL bEnabled = FALSE;
	if(SystemParametersInfo(SPI_GETDROPSHADOW,0,&bEnabled,0))
	{
		return bEnabled;
	}
	return FALSE;
}

BOOL IsLightColor(COLORREF crColor)
{
	return (((int)GetRValue(crColor)) + GetGValue(crColor) + GetBValue(crColor))>(3*128);
}

int NumScreenColors()
{
	static int nColors = 0;
	if (!nColors)
	{
		CClientDC myDC(NULL);
		nColors = myDC.GetDeviceCaps(NUMCOLORS);
		if (nColors == -1)
		{
			nColors = 64000;
		}
	}
	return nColors;
}

COLORREF MixedColor(COLORREF colorA, COLORREF colorB)
{
	// ( 86a + 14b ) / 100
	int red   = MulDiv(86,GetRValue(colorA),100) + MulDiv(14,GetRValue(colorB),100);
	int green = MulDiv(86,GetGValue(colorA),100) + MulDiv(14,GetGValue(colorB),100);
	int blue  = MulDiv(86,GetBValue(colorA),100) + MulDiv(14,GetBValue(colorB),100);

	return RGB(min(red, 0xff), min(green, 0xff), min(blue, 0xff));
}

COLORREF MidColor(COLORREF colorA, COLORREF colorB)
{
	// (7a + 3b)/10
	int red   = MulDiv(7,GetRValue(colorA),10) + MulDiv(3,GetRValue(colorB),10);
	int green = MulDiv(7,GetGValue(colorA),10) + MulDiv(3,GetGValue(colorB),10);
	int blue  = MulDiv(7,GetBValue(colorA),10) + MulDiv(3,GetBValue(colorB),10);

	return RGB( min(red,0xff),min(green,0xff), min(blue,0xff));
}

COLORREF DarkenColorXP(COLORREF clrColor)
{
	return RGB(MulDiv(GetRValue(clrColor), 7, 10),
		MulDiv(GetGValue(clrColor), 7, 10),
		MulDiv(GetBValue(clrColor) + 55, 7, 10));
}

COLORREF GetXpHighlightColor()
{
	if(bHighContrast)
	{
		return GetSysColor(COLOR_HIGHLIGHT);
	}

	if (NumScreenColors() > 256)
	{
		// May-05-2005 - Mark P. Peterson (mpp@rhinosoft.com) - Changed to use "MixedColor1()" instead when not using XP Theme mode.
		// It appears that using MidColor() in many non XP Themes cases returns the wrong color, this needs to be much more like the
		// highlight color as the user has selected in Windows.  If the highlight color is YELLOW, for example, and the COLOR_WINDOW
		// value is WHITE, using MidColor() the function returns a dark blue color making the menus too hard to read.
		if (IsLightColor(GetSysColor(COLOR_HIGHLIGHT)))
			return MixedColor(GetSysColor(COLOR_WINDOW),GetSysColor(COLOR_HIGHLIGHT));
		else
			return MidColor(GetSysColor(COLOR_WINDOW),GetSysColor(COLOR_HIGHLIGHT));
		// as released by Bruno
		//    return MidColor(GetSysColor(COLOR_WINDOW),GetSysColor(COLOR_HIGHLIGHT));
	}
	return GetSysColor(COLOR_WINDOW);
}


class CSkinMenuHook
{
public:
	class CMenuHookData
	{
	public:
		CMenuHookData(HWND hWnd,BOOL bSpecialWnd)
			: m_dwData(bSpecialWnd),m_bDrawBorder(FALSE),m_Point(0,0),
			m_hRgn((HRGN)1),m_bDoSubclass(TRUE)
			//, m_hRightShade(NULL),m_hBottomShade(NULL),m_TimerID(0)
		{
			// Safe actual menu
			SetMenu(CSkinMenuHook::m_hLastMenu);
			// Reset for the next menu
			CSkinMenuHook::m_hLastMenu = NULL;

			// Save actual border setting etc.
			m_dwStyle = GetWindowLongPtr(hWnd, GWL_STYLE);
			m_dwExStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);

			//if(pSetWindowTheme)pSetWindowTheme(hWnd,L" ",L" ");
		}

    ~CMenuHookData()
    {
      if(m_hRgn!=(HRGN)1)
      {
        DeleteObject(m_hRgn);
        m_hRgn = (HRGN)1;
      }
    }

    BOOL SetMenu(HMENU hMenu)
    {
      m_hMenu = hMenu;
      if(!CSkinMenu::GetNewMenuBorderAllMenu() &&
        !DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(hMenu)))
      {
        m_bDoSubclass = FALSE;
      }
      else
      {
        m_bDoSubclass = TRUE;
      }
      return m_bDoSubclass;
    }

    LONG_PTR m_dwStyle;
    LONG_PTR m_dwExStyle;

    CPoint m_Point;
    DWORD m_dwData; //  1=Sepcial WND, 2=Styles Changed,4=VK_ESCAPE, 8=in Print

    BOOL m_bDrawBorder;
    HMENU m_hMenu;

    CBitmap m_Screen;
    HRGN m_hRgn;

    BOOL m_bDoSubclass;
  };

public:
  CSkinMenuHook();
  ~CSkinMenuHook();

public:
	static CMenuHookData* GetMenuHookData(HWND hWnd);

private:
	static LRESULT CALLBACK SkinMenuHook(int code, WPARAM wParam, LPARAM lParam);
	static BOOL CheckSubclassing(HWND hWnd,BOOL bSpecialWnd);
	static LRESULT CALLBACK SubClassMenu(HWND hWnd,  UINT uMsg, WPARAM wParam,  LPARAM lParam );
	static void UnsubClassMenu(HWND hWnd);

	static BOOL SubClassMenu2(HWND hWnd,  UINT uMsg, WPARAM wParam,  LPARAM lParam, DWORD* pResult);

public:
	static HMENU m_hLastMenu;
	static DWORD m_dwMsgPos;
	static DWORD m_bSubclassFlag;

private:
	//static HMODULE m_hThemeLibrary;
	static HHOOK HookOldMenuCbtFilter;

	// an map of actual opened Menu and submenu
	static CTypedPtrMap<CMapPtrToPtr,HWND,CMenuHookData*> m_MenuHookData;
};

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuIconLock Helperclass for reference-counting !

class CSkinMenuIconLock
{
	CSkinMenuIcons* m_pIcons;

public:
	CSkinMenuIconLock(CSkinMenuIcons* pIcons):m_pIcons(pIcons)
	{
		m_pIcons->AddRef();
	}

	~CSkinMenuIconLock()
	{
		m_pIcons->Release();
	}
	operator CSkinMenuIcons*(){return m_pIcons;}
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinMenuIcons,CObject);

CSkinMenuIcons::CSkinMenuIcons()
: m_lpszResourceName(NULL),
m_hInst(NULL),
m_hBitmap(NULL),
m_nColors(0),
m_crTransparent(CLR_NONE),
m_dwRefCount(0)
{
}

CSkinMenuIcons::~CSkinMenuIcons()
{
	if(m_lpszResourceName && !IS_INTRESOURCE(m_lpszResourceName))
	{
		delete (LPTSTR)m_lpszResourceName;
	}
}

int CSkinMenuIcons::AddRef()
{
	if(this==NULL)
		return NULL;

	return ++m_dwRefCount;
}

int CSkinMenuIcons::Release()
{
	if(this==NULL)
		return NULL;

	DWORD dwCount = --m_dwRefCount;
	if(m_dwRefCount==0)
	{
		if(CSkinMenu::m_pSharedMenuIcons)
		{
			POSITION pos = CSkinMenu::m_pSharedMenuIcons->Find(this);
			if(pos)
			{
				CSkinMenu::m_pSharedMenuIcons->RemoveAt(pos);
			}
		}
		delete this;
	}
	return dwCount;
}

BOOL CSkinMenuIcons::DoMatch(LPCTSTR lpszResourceName, HMODULE hInst)
{
	if(hInst==m_hInst && lpszResourceName)
	{
		if(IS_INTRESOURCE(m_lpszResourceName))
		{
			return (lpszResourceName==m_lpszResourceName);
		}

		return (_tcscmp(lpszResourceName,m_lpszResourceName)==0);
	}
	return FALSE;
}

BOOL CSkinMenuIcons::DoMatch(HBITMAP hBitmap, CSize size, UINT* pID)
{
	if(pID && m_hBitmap==hBitmap)
	{
		CSize iconSize = GetIconSize();
		if(iconSize==size)
		{
			int nCount = (int)m_IDs.GetSize();
			for(int nIndex=0 ; nIndex<nCount ; nIndex++,pID++)
			{
				if( (*pID)==0 || m_IDs.GetAt(nIndex)!=(*pID) )
				{
					return FALSE;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CSkinMenuIcons::DoMatch(WORD* pIconInfo, COLORREF crTransparent)
{
	if(m_crTransparent==crTransparent && pIconInfo!=NULL)
	{
		CSkinMenuIconInfo* pInfo = (CSkinMenuIconInfo*)pIconInfo;

		// Check for the same resource ID
		if( pInfo->wBitmapID && IS_INTRESOURCE(m_lpszResourceName) &&
			((UINT)(UINT_PTR)m_lpszResourceName)==pInfo->wBitmapID)
		{
			int nCount = (int)m_IDs.GetSize();
			WORD* pID = pInfo->ids();
			for(int nIndex=0 ; nIndex<nCount ; nIndex++,pID++)
			{
				if( (*pID)==0 || m_IDs.GetAt(nIndex)!=(*pID) )
				{
					return FALSE;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}

int CSkinMenuIcons::FindIndex(UINT nID)
{
	int nIndex = (int)m_IDs.GetSize();
	while(nIndex--)
	{
		if(m_IDs.GetAt(nIndex)==nID)
		{
			return nIndex*MENU_ICONS;
		}
	}
	return -1;
}

BOOL CSkinMenuIcons::GetIconSize(int* cx, int* cy)
{
	return ::ImageList_GetIconSize(m_IconsList,cx,cy);
}

CSize CSkinMenuIcons::GetIconSize()
{
	int cx=0;
	int cy=0;
	if(::ImageList_GetIconSize(m_IconsList,&cx,&cy))
	{
		return CSize(cx,cy);
	}
	return CSize(0,0);
}

void CSkinMenuIcons::OnSysColorChange()
{
	if(m_lpszResourceName!=NULL)
	{
		int cx=16,cy=16;
		if(GetIconSize(&cx, &cy) && LoadBitmap(cx,cy,m_lpszResourceName,m_hInst))
		{
			MakeImages();
		}
	}
}

WORD NumBitmapColors(LPBITMAPINFOHEADER lpBitmap)
{
	if (lpBitmap->biClrUsed != 0)
		return (WORD)lpBitmap->biClrUsed;

	switch (lpBitmap->biBitCount)
	{
	case 1:
		return 2;
	case 4:
		return 16;
	case 8:
		return 256;
	}
	return 0;
}

HBITMAP LoadColorBitmap(LPCTSTR lpszResourceName, HMODULE hInst, int* pNumcol)
{
	if(hInst==0)
	{
		hInst = AfxFindResourceHandle(lpszResourceName, RT_BITMAP);
	}

	HRSRC hRsrc = ::FindResource(hInst,MAKEINTRESOURCE(lpszResourceName),RT_BITMAP);
	if (hRsrc == NULL)
		return NULL;

	HGLOBAL hglb;
	if ((hglb = LoadResource(hInst, hRsrc)) == NULL)
		return NULL;

	LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)LockResource(hglb);
	if (lpBitmap == NULL)
		return NULL;
	WORD numcol = NumBitmapColors(lpBitmap);
	if(pNumcol)
	{
		*pNumcol = numcol;
	}

	UnlockResource(hglb);
	FreeResource(hglb);

	return LoadBitmap(hInst,lpszResourceName);
}

BOOL CSkinMenuIcons::LoadBitmap(int nWidth, int nHeight, LPCTSTR lpszResourceName, HMODULE hInst)
{
	m_nColors = 0;
	HBITMAP hBitmap = LoadColorBitmap(lpszResourceName,hInst,&m_nColors);
	if(hBitmap!=NULL)
	{
		CBitmap bitmap;
		bitmap.Attach(hBitmap);
		if(m_IconsList.GetSafeHandle())
		{
			m_IconsList.DeleteImageList();
		}
		m_IconsList.Create(nWidth,nHeight,ILC_COLORDDB|ILC_MASK,0,10);
		m_IconsList.Add(&bitmap,m_crTransparent);

		return TRUE;
	}
	return FALSE;
}

BOOL CSkinMenuIcons::LoadToolBar(HBITMAP hBitmap, CSize size, UINT* pID, COLORREF crTransparent)
{
	BOOL bResult = FALSE;
	m_nColors = 0;
	if(hBitmap!=NULL)
	{
		BITMAP myInfo = {0};
		if(GetObject(hBitmap,sizeof(myInfo),&myInfo))
		{
			m_crTransparent = crTransparent;
			if(m_IconsList.GetSafeHandle())
			{
				m_IconsList.DeleteImageList();
			}
			m_IconsList.Create(size.cx,size.cy,ILC_COLORDDB|ILC_MASK,0,10);
			// Changed by Mehdy Bohlool(zy) ( December_28_2003 )
			//
			// CImageList::Add function change the background color ( color
			// specified as transparent ) to black, and this bitmap may use
			// after call to this function, It seem that Load functions do
			// not change their source data provider ( currently hBitmap ).
			// Old Code:
			// CBitmap* pBitmap = CBitmap::FromHandle(hBitmap);
			// m_IconsList.Add(pBitmap,m_crTransparent);
			// New Code:
			{
				HBITMAP hBitmapCopy;

				hBitmapCopy = (HBITMAP) CopyImage( hBitmap, IMAGE_BITMAP, 0,0,0);

				CBitmap* pBitmap = CBitmap::FromHandle(hBitmapCopy);
				m_IconsList.Add(pBitmap,m_crTransparent);

				DeleteObject( hBitmapCopy );
			}

			while(*pID)
			{
				UINT nID = *(pID++);
				m_IDs.Add(nID);
				bResult = TRUE;
			}
			MakeImages();
		}
	}
	return bResult;
}


BOOL CSkinMenuIcons::LoadToolBar(WORD* pIconInfo, COLORREF crTransparent)
{
	BOOL bResult = FALSE;
	m_crTransparent = crTransparent;
	CSkinMenuIconInfo* pInfo = (CSkinMenuIconInfo*)pIconInfo;

	if (LoadBitmap(pInfo->wWidth,pInfo->wHeight,MAKEINTRESOURCE(pInfo->wBitmapID)))
	{
		SetResourceName(MAKEINTRESOURCE(pInfo->wBitmapID));

		WORD* pID = pInfo->ids();
		while(*pID)
		{
			UINT nID = *(pID++);
			m_IDs.Add(nID);
			bResult = TRUE;
		}
		MakeImages();
	}
	return bResult;
}

void CSkinMenuIcons::SetResourceName(LPCTSTR lpszResourceName)
{
	ASSERT_VALID(this);
	ASSERT(lpszResourceName != NULL);

	if(m_lpszResourceName && !IS_INTRESOURCE(m_lpszResourceName))
	{
		delete [](LPTSTR)m_lpszResourceName;
	}
	if( lpszResourceName && !IS_INTRESOURCE(lpszResourceName))
	{
		int bufSizeTchar = lstrlen(lpszResourceName)+1;
		m_lpszResourceName = new TCHAR[bufSizeTchar];
		lstrcpyn((LPTSTR)m_lpszResourceName,lpszResourceName,bufSizeTchar);
	}
	else
	{
		m_lpszResourceName = lpszResourceName;
	}
}

BOOL CSkinMenuIcons::LoadToolBar(LPCTSTR lpszResourceName, HMODULE hInst)
{
	ASSERT_VALID(this);

	SetResourceName(lpszResourceName);

	m_hInst = hInst;

	// determine location of the bitmap in resource
	if(hInst==0)
	{
		hInst = AfxFindResourceHandle(lpszResourceName, RT_TOOLBAR);
	}
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);

	if (hRsrc == NULL)
	{ // Special purpose when you try to load it from a dll 30.05.2002
		if(AfxGetResourceHandle()!=hInst)
		{
			hInst = AfxGetResourceHandle();
			hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
		}
		if (hRsrc == NULL)
		{
			return FALSE;
		}
	}

	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
	{
		return FALSE;
	}

	CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
	if (pData == NULL)
	{
		return FALSE;
	}

	BOOL bResult = FALSE;
	ASSERT(pData->wVersion == 1);

	if(LoadBitmap(pData->wWidth,pData->wHeight,lpszResourceName,hInst))
	{
		// Remove all previous ID's
		m_IDs.RemoveAll();
		for (int i = 0; i < pData->wItemCount; i++)
		{
			UINT nID = pData->items()[i];
			if (nID)
			{
				m_IDs.Add(nID);
				bResult = TRUE;
			}
		}
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	MakeImages();

	return bResult;
}

int CSkinMenuIcons::AddGloomIcon(HICON hIcon, int nIndex)
{
	ICONINFO iconInfo = {0};
	if(!GetIconInfo(hIcon,&iconInfo))
	{
		return -1;
	}

	CSize size = GetIconSize();
	CDC myDC;
	myDC.CreateCompatibleDC(0);

	CBitmap bmColor;
	bmColor.Attach(iconInfo.hbmColor);
	CBitmap bmMask;
	bmMask.Attach(iconInfo.hbmMask);

	CBitmap* pOldBitmap = myDC.SelectObject(&bmColor);
	COLORREF crPixel;
	for(int i=0;i<size.cx;++i)
	{
		for(int j=0;j<size.cy;++j)
		{
			crPixel = myDC.GetPixel(i,j);
			// added so the gloom value can be adjusted, this was 50
			myDC.SetPixel(i,j,DrawHelpers()->DarkenColor(CSkinMenu::GetGloomFactor(), crPixel));
		}
	}
	myDC.SelectObject(pOldBitmap);
	if(nIndex==-1)
	{
		return m_IconsList.Add(&bmColor,&bmMask);
	}

	return (m_IconsList.Replace(nIndex,&bmColor,&bmMask)) ? nIndex: -1;
}

COLORREF MakeGrayAlphablend(CBitmap* pBitmap, int weighting, COLORREF blendcolor)
{
	CDC myDC;
	myDC.CreateCompatibleDC(0);
	CBitmap* pOldBitmap = myDC.SelectObject(pBitmap);

	BITMAP myInfo = { 0 };
	GetObject((HGDIOBJ)pBitmap->m_hObject,sizeof(myInfo),&myInfo);

	for (int nHIndex = 0; nHIndex < myInfo.bmHeight; nHIndex++)
	{
		for (int nWIndex = 0; nWIndex < myInfo.bmWidth; nWIndex++)
		{
			COLORREF ref = myDC.GetPixel(nWIndex,nHIndex);

			// make it gray
			DWORD nAvg =  (GetRValue(ref) + GetGValue(ref) + GetBValue(ref))/3;

			// Algorithme for alphablending
			//dest' = ((weighting * source) + ((255-weighting) * dest)) / 256
			DWORD refR = ((weighting * nAvg) + ((255-weighting) * GetRValue(blendcolor))) / 256;
			DWORD refG = ((weighting * nAvg) + ((255-weighting) * GetGValue(blendcolor))) / 256;
			DWORD refB = ((weighting * nAvg) + ((255-weighting) * GetBValue(blendcolor))) / 256;

			myDC.SetPixel(nWIndex,nHIndex,RGB(refR,refG,refB));
		}
	}
	COLORREF topLeftColor = myDC.GetPixel(0,0);
	myDC.SelectObject(pOldBitmap);
	return topLeftColor;
}

int CSkinMenuIcons::AddGrayIcon(HICON hIcon, int nIndex)
{
	ICONINFO iconInfo = {0};
	if(!GetIconInfo(hIcon,&iconInfo))
	{
		return -1;
	}

	CBitmap bmColor;
	bmColor.Attach(iconInfo.hbmColor);
	CBitmap bmMask;
	bmMask.Attach(iconInfo.hbmMask);

	COLORREF blendcolor = DrawHelpers()->LightenColor(115,CSkinMenu::GetMenuBarColorXP());
	MakeGrayAlphablend(&bmColor,110, blendcolor);

	if(nIndex==-1)
	{
		return m_IconsList.Add(&bmColor,&bmMask);
	}

	return (m_IconsList.Replace(nIndex,&bmColor,&bmMask)) ? nIndex: -1;
}

BOOL CSkinMenuIcons::MakeImages()
{
	int nCount = m_IconsList.GetImageCount();
	if(!nCount)
	{
		return FALSE;
	}

	CSize size = GetIconSize();
	CImageList ilTemp;
	ilTemp.Attach(m_IconsList.Detach());
	m_IconsList.Create(size.cx,size.cy,ILC_COLORDDB|ILC_MASK,0,10);

	for(int nIndex=0;nIndex<nCount;nIndex++)
	{
		HICON hIcon = ilTemp.ExtractIcon(nIndex);
		m_IconsList.Add(hIcon);
		AddGloomIcon(hIcon);
		AddGrayIcon(hIcon);

		DestroyIcon(hIcon);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinMenuBitmaps,CSkinMenuIcons);

CSkinMenuBitmaps::CSkinMenuBitmaps()
{
}

CSkinMenuBitmaps::~CSkinMenuBitmaps()
{
}

int CSkinMenuBitmaps::Add(UINT nID, COLORREF crTransparent)
{
	int nIndex = (int)m_IDs.GetSize();
	while(nIndex--)
	{
		if(m_IDs.GetAt(nIndex)==nID)
		{
			return nIndex*MENU_ICONS;
		}
	}
	// Try to load the bitmap for getting dimension
	HBITMAP hBitmap = LoadColorBitmap(MAKEINTRESOURCE(nID),0, NULL);
	if(hBitmap!=NULL)
	{
		CBitmap temp;
		temp.Attach(hBitmap);

		BITMAP bitmap = {0};
		if(!temp.GetBitmap(&bitmap))
		{
			return -1;
		}

		if(m_IconsList.GetSafeHandle()==NULL)
		{
			m_IconsList.Create(bitmap.bmWidth,bitmap.bmHeight,ILC_COLORDDB|ILC_MASK,0,10);
		}
		else
		{
			CSize size = GetIconSize();
			// Wrong size?
			if(size.cx!=bitmap.bmWidth || size.cy!=bitmap.bmHeight)
			{
				return -1;
			}
		}
		m_TranspColors.Add(crTransparent);
		m_IDs.Add(nID);

		nIndex = m_IconsList.Add(&temp,crTransparent);
		HICON hIcon = m_IconsList.ExtractIcon(nIndex);
		AddGloomIcon(hIcon);
		AddGrayIcon(hIcon);
		DestroyIcon(hIcon);

		//SetBlendImage();
		return nIndex;
	}
	return -1;
}

void CSkinMenuBitmaps::OnSysColorChange()
{
	int nCount = (int)m_IDs.GetSize();
	for(int nIndex=0;nIndex<nCount;nIndex+=MENU_ICONS)
	{
		//Todo reload icons
		HICON hIcon = m_IconsList.ExtractIcon(nIndex);
		AddGloomIcon(hIcon,nIndex+1);
		AddGrayIcon(hIcon,nIndex+2);

		DestroyIcon(hIcon);
	}
}

int CSkinMenuBitmaps::Add(HICON hIcon, UINT nID)
{
	ICONINFO iconInfo = {0};
	if(!GetIconInfo(hIcon,&iconInfo))
	{
		return -1;
	}

	CBitmap temp;
	temp.Attach(iconInfo.hbmColor);
	::DeleteObject(iconInfo.hbmMask);

	BITMAP bitmap = {0};
	if(!temp.GetBitmap(&bitmap))
	{
		return -1;
	}

	if(m_IconsList.GetSafeHandle()==NULL)
	{
		m_IconsList.Create(bitmap.bmWidth,bitmap.bmHeight,ILC_COLORDDB|ILC_MASK,0,10);
	}
	else
	{
		CSize size = GetIconSize();
		// Wrong size?
		if(size.cx!=bitmap.bmWidth || size.cy!=bitmap.bmHeight)
		{
			return -1;
		}
	}
	if(nID)
	{
		int nIndex = (int)m_IDs.GetSize();
		while(nIndex--)
		{
			if(m_IDs.GetAt(nIndex)==nID)
			{
				// We found the index also replace the icon
				nIndex = nIndex*MENU_ICONS;
				m_IconsList.Replace(nIndex,hIcon);
				AddGloomIcon(hIcon,nIndex+1);
				AddGrayIcon(hIcon,nIndex+2);
				return nIndex;
			}
		}
	}
	COLORREF clr = CLR_NONE;
	m_TranspColors.Add(clr);
	m_IDs.Add(nID);
	int nIndex = m_IconsList.Add(hIcon);
	AddGloomIcon(hIcon);
	AddGrayIcon(hIcon);

	return nIndex;
}

int CSkinMenuBitmaps::Add(CBitmap* pBitmap, COLORREF crTransparent)
{
	ASSERT(pBitmap);

	BITMAP bitmap = {0};
	if(!pBitmap->GetBitmap(&bitmap))
	{
		return -1;
	}

	if(m_IconsList.GetSafeHandle()==NULL)
	{
		m_IconsList.Create(bitmap.bmWidth,bitmap.bmHeight,ILC_COLORDDB|ILC_MASK,0,10);
	}
	else
	{
		CSize size = GetIconSize();
		// Wrong size?
		if(size.cx!=bitmap.bmWidth || size.cy!=bitmap.bmHeight)
		{
			return -1;
		}
	}
	UINT nID = 0;
	m_TranspColors.Add(crTransparent);
	m_IDs.Add(nID);
	int nIndex = m_IconsList.Add(pBitmap,crTransparent);
	HICON hIcon = m_IconsList.ExtractIcon(nIndex);
	AddGloomIcon(hIcon);
	AddGrayIcon(hIcon);
	DestroyIcon(hIcon);
	//SetBlendImage();
	return nIndex;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinMenuItemData,CObject);

CSkinMenuItemData::CSkinMenuItemData()
: m_nTitleFlags(0),
m_nFlags(0),
m_nID(0),
m_nSyncFlag(0),
m_pData(NULL),
m_pMenuIcon(NULL),
m_nMenuIconOffset(-1)
{
}

CSkinMenuItemData::~CSkinMenuItemData()
{
	// it's a safe release. Do not care for NULL pointers.
	m_pMenuIcon->Release();
}

// Get the string, along with (manufactured) accelerator text.
CString CSkinMenuItemData::GetString (HACCEL hAccel)
{
	if (m_nFlags & MF_POPUP )
	{ // No accelerators if we're the title of a popup menu. Otherwise we get spurious accels
		hAccel = NULL;
	}

	CString s = m_szMenuText;
	int iTabIndex = s.Find ('\t');
	if (!hAccel || iTabIndex>= 0) // Got one hard coded in, or we're a popup menu
	{
		if (!hAccel && iTabIndex>= 0)
		{
			s = s.Left (iTabIndex);
		}
		return s;
	}

	// OK, we've got to go hunting through the default accelerator.
	if (hAccel == INVALID_HANDLE_VALUE)
	{
		hAccel = NULL;
		CFrameWnd *pFrame = DYNAMIC_DOWNCAST(CFrameWnd, AfxGetMainWnd ());
		// No frame. Maybe we're part of a dialog app. etc.
		if (pFrame)
		{
			hAccel = pFrame->GetDefaultAccelerator ();
		}
	}
	// No default found, or we've turned accelerators off.
	if (hAccel == NULL)
	{
		return s;
	}
	// Get the number of entries
	int nEntries = ::CopyAcceleratorTable (hAccel, NULL, 0);
	if (nEntries)
	{
		ACCEL *pAccel = (ACCEL *)_alloca(nEntries*sizeof(ACCEL));
		if (::CopyAcceleratorTable (hAccel, pAccel, nEntries))
		{
			CString sAccel;
			for (int n = 0; n < nEntries; n++)
			{
				if (pAccel [n].cmd != (WORD) m_nID)
				{
					continue;
				}
				if (!sAccel.IsEmpty ())
				{
					sAccel += _T(", ");
				}
				// Translate the accelerator into more useful code.
				if (pAccel [n].fVirt & FALT)         sAccel += _T("Alt+");
				if (pAccel [n].fVirt & FCONTROL)     sAccel += _T("Ctrl+");
				if (pAccel [n].fVirt & FSHIFT)       sAccel += _T("Shift+");
				if (pAccel [n].fVirt & FVIRTKEY)
				{
					TCHAR keyname[64];
					UINT vkey = MapVirtualKey(pAccel [n].key, 0)<<16;
					GetKeyNameText(vkey, keyname, sizeof(keyname));
					sAccel += keyname;
				}
				else
				{
					sAccel += (TCHAR)pAccel [n].key;
				}
			}
			if (!sAccel.IsEmpty ()) // We found one!
			{
				s += '\t';
				s += sAccel;
			}
		}
	}
	return s;
}

void CSkinMenuItemData::SetString(LPCTSTR szMenuText)
{
	m_szMenuText = szMenuText;
}

//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinMenuItemDataTitle,CSkinMenuItemData);

CSkinMenuItemDataTitle::CSkinMenuItemDataTitle()
: m_clrTitle(CLR_DEFAULT),
m_clrLeft(CLR_DEFAULT),
m_clrRight(CLR_DEFAULT)
{
}

CSkinMenuItemDataTitle::~CSkinMenuItemDataTitle()
{
}

//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinMenu,CMenu);

// actual selectet menu-draw mode
//CSkinMenuTheme* CSkinMenu::m_pActMenuDrawing = NULL;
CTypedPtrList<CPtrList, CSkinMenuIcons*>* CSkinMenu::m_pSharedMenuIcons = NULL;

// Gloabal logfont for all menutitles
LOGFONT CSkinMenu::m_MenuTitleFont = {16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,_T("宋体") };


void CSkinMenu::SetMenuTitleFont(CFont* pFont)
{
	ASSERT(pFont);
	pFont->GetLogFont(&m_MenuTitleFont);
}

void CSkinMenu::SetMenuTitleFont(LOGFONT* pLogFont)
{
	ASSERT(pLogFont);
	m_MenuTitleFont = *pLogFont;
}

LOGFONT CSkinMenu::GetMenuTitleFont()
{
	return m_MenuTitleFont;
}

DWORD CSkinMenu::m_dwLastActiveItem = NULL;

// how the menu's are drawn in winXP
BOOL CSkinMenu::m_bEnableXpBlending = TRUE;
BOOL CSkinMenu::m_bNewMenuBorderAllMenu = TRUE;
BOOL CSkinMenu::m_bSelectDisable = TRUE;

// added so the gloom value can be adjusted
// 50 is the default, may be too high, 20 is subtle
int CSkinMenu::m_nGloomFactor = 50;

// one instance of the hook for menu-subclassing
static CSkinMenuHook SkinMenuHookInstance;

CSkinMenu::CSkinMenu(HMENU hParent)
: m_hTempOwner(NULL),
m_hParentMenu(hParent),
m_bIsPopupMenu(TRUE),
m_dwOpenMenu(NULL),
m_LastActiveMenuRect(0,0,0,0),
m_pData(NULL),
m_hAccelToDraw((HACCEL)INVALID_HANDLE_VALUE)
{
	// O.S. - no dynamic icons by default
	m_bDynIcons = FALSE;
	// Icon sizes default to 16 x 16
	m_iconX = 18;
	m_iconY = 16;
	m_selectcheck = -1;
	m_unselectcheck = -1;
	m_checkmaps=NULL;
	m_checkmapsshare=FALSE;

	// set the color used for the transparent background in all bitmaps
	m_bitmapBackground = CLR_DEFAULT;
}

CSkinMenu::~CSkinMenu()
{
	DestroyMenu();
}

COLORREF CSkinMenu::GetMenuColor(HMENU hMenu)
{
	if(hMenu!=NULL)
	{
		MENUINFO menuInfo={0};
		menuInfo.cbSize = sizeof(menuInfo);
		menuInfo.fMask = MIM_BACKGROUND;

		if(::GetMenuInfo(hMenu,&menuInfo) && menuInfo.hbrBack)
		{
			LOGBRUSH logBrush;
			if(GetObject(menuInfo.hbrBack,sizeof(LOGBRUSH),&logBrush))
			{
				return logBrush.lbColor;
			}
		}
	}

	if(SystemVersion()->IsWinXPOrGreater())
	{
		BOOL bFlatMenu = FALSE;
		// theme ist not checket, that must be so
		if( (SystemParametersInfo(SPI_GETFLATMENU,0,&bFlatMenu,0) && bFlatMenu==TRUE) )
		{
			return GetSysColor(COLOR_MENUBAR);
		}
	}
	return GetSysColor(COLOR_MENU);
}

COLORREF CSkinMenu::GetMenuBarColorXP()
{
	if(!SystemVersion()->IsWinXPOrGreater())
	{
		return GetSysColor(COLOR_MENU);
	}
	return GetSysColor(COLOR_3DFACE);
}

COLORREF CSkinMenu::GetMenuBarColor(HMENU hMenu)
{
  if(hMenu!=NULL)
  {
    MENUINFO menuInfo = {0};
    menuInfo.cbSize = sizeof(menuInfo);
    menuInfo.fMask = MIM_BACKGROUND;

    if(::GetMenuInfo(hMenu,&menuInfo) && menuInfo.hbrBack)
    {
      LOGBRUSH logBrush;
      if(GetObject(menuInfo.hbrBack,sizeof(LOGBRUSH),&logBrush))
      {
        return logBrush.lbColor;
      }
    }
  }
  if(SystemVersion()->IsWinXPOrGreater())
  {
    BOOL bFlatMenu = FALSE;
    if(SystemParametersInfo(SPI_GETFLATMENU,0,&bFlatMenu,0) && bFlatMenu==TRUE)
    {
      return GetSysColor(COLOR_MENUBAR);
    }
  }
  // May-05-2005 - Mark P. Peterson (mpp@rhinosoft.com) - Changed to use the menubar color, I could not find why COLOR_MENU should
  // be used when not flat and no XP Theme is active.  The problem is that using this shows the wrong color in any other theme, when
  // the background color of menus is something other than the same color of the menu bar.
  return (GetMenuBarColorXP());
//  return GetSysColor(COLOR_MENU);
}

void CSkinMenu::SetLastMenuRect(HDC hDC, LPRECT pRect)
{
  if(!m_bIsPopupMenu)
  {
    HWND hWnd = WindowFromDC(hDC);
    if(hWnd && pRect)
    {
      CRect Temp;
      GetWindowRect(hWnd,Temp);
      m_LastActiveMenuRect = *pRect;
      m_LastActiveMenuRect.OffsetRect(Temp.TopLeft());
    }
  }
}

void CSkinMenu::SetLastMenuRect(LPRECT pRect)
{
  ASSERT(pRect);
  m_LastActiveMenuRect = *pRect;
}

BOOL CSkinMenu::OnMeasureItem(const MSG* pMsg)
{
  if(pMsg->message==WM_MEASUREITEM)
  {
    LPMEASUREITEMSTRUCT lpMIS = (LPMEASUREITEMSTRUCT)pMsg->lParam;
    if(lpMIS->CtlType==ODT_MENU)
    {
      CMenu* pMenu=NULL;
      if(::IsMenu(HMENU(lpMIS->itemID)) )
      {
        pMenu = CMenu::FromHandlePermanent(HMENU(lpMIS->itemID) );
      }
      else
      {
        _AFX_THREAD_STATE* pThreadState = AfxGetThreadState ();
        if (pThreadState->m_hTrackingWindow == pMsg->hwnd)
        {
          // start from popup
          pMenu = FindPopupMenuFromIDData(pThreadState->m_hTrackingMenu,lpMIS->itemID,lpMIS->itemData);
        }
        if(pMenu==NULL)
        {
          // start from menubar
          pMenu = FindPopupMenuFromIDData(::GetMenu(pMsg->hwnd),lpMIS->itemID,lpMIS->itemData);
          if(pMenu==NULL)
          {
            // finaly start from system menu.
            pMenu = FindPopupMenuFromIDData(::GetSystemMenu(pMsg->hwnd,FALSE),lpMIS->itemID,lpMIS->itemData);
          }
        }
      }
      if(pMenu!=NULL)
      {
        pMenu->MeasureItem(lpMIS);

        return TRUE;
      }
    }
  }
  return FALSE;
}

CMenu* CSkinMenu::FindPopupMenuFromID(HMENU hMenu, UINT nID)
{
  // check for a valid menu-handle
  if ( ::IsMenu(hMenu))
  {
    CMenu *pMenu = CMenu::FromHandlePermanent(hMenu);
    if(pMenu)
    {
      return FindPopupMenuFromID(pMenu,nID);
    }
  }
  return NULL;
}

CMenu* CSkinMenu::FindPopupMenuFromIDData(HMENU hMenu, UINT nID, ULONG_PTR pData)
{
  // check for a valid menu-handle
  if ( ::IsMenu(hMenu))
  {
    CMenu *pMenu = CMenu::FromHandlePermanent(hMenu);
    if(pMenu)
    {
      return FindPopupMenuFromIDData(pMenu,nID,pData);
    }
  }
  return NULL;
}

CMenu* CSkinMenu::FindPopupMenuFromIDData(CMenu* pMenu, UINT nID, ULONG_PTR pData)
{
  if(!pMenu || !IsMenu(pMenu->m_hMenu))
  {
    return NULL;
  }
  ASSERT_VALID(pMenu);
  // walk through all items, looking for ID match
  UINT nItems = pMenu->GetMenuItemCount();
  for (int iItem = 0; iItem < (int)nItems; iItem++)
  {
    CMenu* pPopup = pMenu->GetSubMenu(iItem);
    if (pPopup!=NULL)
    {
      // recurse to child popup
      pPopup = FindPopupMenuFromIDData(pPopup, nID, pData);
      // check popups on this popup
      if (pPopup != NULL)
      {
        return pPopup;
      }
    }
    else if (pMenu->GetMenuItemID(iItem) == nID)
    {
      MENUITEMINFO MenuItemInfo = {0};
      MenuItemInfo.cbSize = sizeof(MenuItemInfo);
      MenuItemInfo.fMask = MIIM_DATA;

      if(pMenu->GetMenuItemInfo(iItem,&MenuItemInfo,TRUE))
      {
        if(MenuItemInfo.dwItemData==pData)
        {
          // it is a normal item inside our popup
          return pMenu;
        }
      }
    }
  }
  // not found
  return NULL;
}

CMenu* CSkinMenu::FindPopupMenuFromID(CMenu* pMenu, UINT nID)
{
  if(!pMenu || !IsMenu(pMenu->m_hMenu))
  {
    return NULL;
  }
  ASSERT_VALID(pMenu);
  // walk through all items, looking for ID match
  UINT nItems = pMenu->GetMenuItemCount();
  for (int iItem = 0; iItem < (int)nItems; iItem++)
  {
    CMenu* pPopup = pMenu->GetSubMenu(iItem);
    if (pPopup != NULL)
    {
      // recurse to child popup
      pPopup = FindPopupMenuFromID(pPopup, nID);
      // check popups on this popup
      if (pPopup != NULL)
      {
        return pPopup;
      }
    }
    else if (pMenu->GetMenuItemID(iItem) == nID)
    {
      // it is a normal item inside our popup
      return pMenu;
    }
  }
  // not found
  return NULL;
}

BOOL CSkinMenu::DestroyMenu()
{
  // Destroy Sub menus:
  int nIndex = (int)m_SubMenus.GetSize();
  while(nIndex--)
  {
    // Destroy only if we createt it!!!!!
    CSkinMenu* pMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(m_SubMenus[nIndex]));
    if(pMenu)
    {
      delete pMenu;
    }
  }
  m_SubMenus.RemoveAll();

  // Destroy menu data
  nIndex = (int)m_MenuItemList.GetSize();
  while(nIndex--)
  {
    delete(m_MenuItemList[nIndex]);
  }
  m_MenuItemList.RemoveAll();

  if(m_checkmaps&&!m_checkmapsshare)
  {
    delete m_checkmaps;
    m_checkmaps=NULL;
  }
  // Call base-class implementation last:
  return(CMenu::DestroyMenu());
}

HMENU CSkinMenu::GetParent()
{
  return m_hParentMenu;
}

BOOL CSkinMenu::IsPopup()
{
  return m_bIsPopupMenu;
}

BOOL CSkinMenu::SetPopup(BOOL bIsPopup)
{
  BOOL bOldFlag = m_bIsPopupMenu;
  m_bIsPopupMenu = bIsPopup;
  return bOldFlag;
}

BOOL CSkinMenu::SetSelectDisableMode(BOOL mode)
{
  BOOL bOldMode = m_bSelectDisable;
  m_bSelectDisable=mode;
  return bOldMode;
}

BOOL CSkinMenu::GetSelectDisableMode()
{
  return m_bSelectDisable;
}

BOOL CSkinMenu::SetXpBlending(BOOL bEnable)
{
  BOOL bOldMode = m_bEnableXpBlending;
  m_bEnableXpBlending = bEnable;
  return bOldMode;
}

BOOL CSkinMenu::GetXpBlending()
{
  return m_bEnableXpBlending;
}

// added SetGloomFactor() and GetGloomFactor() so that the glooming can be done in a more or less subtle way
int CSkinMenu::SetGloomFactor(int nGloomFactor)
{
  int nOldGloomFactor = m_nGloomFactor;

  // set the new gloom factor
  m_nGloomFactor = nGloomFactor;

  // return the previous gloom factor
  return (nOldGloomFactor);
} // SetGloomFactor


int CSkinMenu::GetGloomFactor()
{
  // return the current gloom factor
  return (m_nGloomFactor);
} // GetGloomFactor


// Function to set how default menu border were drawn
//(enable=TRUE means that all menu in the application has the same border)
BOOL CSkinMenu::SetNewMenuBorderAllMenu(BOOL bEnable /* =TRUE*/)
{
  BOOL bOldMode = m_bNewMenuBorderAllMenu;
  m_bNewMenuBorderAllMenu = bEnable;
  return bOldMode;
}

BOOL CSkinMenu::GetNewMenuBorderAllMenu()
{
  return m_bNewMenuBorderAllMenu;
}

void CSkinMenu::OnSysColorChange()
{
  static DWORD dwLastTicks = 0;
  DWORD dwAktTicks = GetTickCount();

  // Last Update 2 sec
  if((dwAktTicks-dwLastTicks)>2000)
  {
    dwLastTicks = dwAktTicks;
    if(m_pSharedMenuIcons)
    {
      POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
      while(pos)
      {
        CSkinMenuIcons* pMenuIcons = m_pSharedMenuIcons->GetNext(pos);
        pMenuIcons->OnSysColorChange();
      }
    }
  }
}

void CSkinMenu::MeasureItem( LPMEASUREITEMSTRUCT lpMIS )
{

	BOOL bIsMenuBar = IsMenuBar(HMENU(lpMIS->itemID));
	if(!bIsMenuBar && m_hParentMenu && !FindMenuItem(lpMIS->itemID)) //::IsMenu(HMENU(lpMIS->itemID)) )
	{
		CSkinMenu* pMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(m_hParentMenu));
		if(pMenu)
		{
			MeasureItem_WinXP(lpMIS,bIsMenuBar);
			return;
		}
	}
	MeasureItem_WinXP(lpMIS,bIsMenuBar);
}

void CSkinMenu::DrawItem (LPDRAWITEMSTRUCT lpDIS)
{
  BOOL bIsMenuBar = m_hParentMenu ? FALSE: ((m_bIsPopupMenu)?FALSE:TRUE);

  if(bIsMenuBar && m_dwLastActiveItem==lpDIS->itemData)
  {
    if(! (lpDIS->itemState&ODS_HOTLIGHT) )
    {
      // Mark for redraw helper for win 98
      m_dwLastActiveItem = NULL;
    }
  }

  DrawItem_WinXP(lpDIS,bIsMenuBar);
}

// Erase the Background of the menu
BOOL CSkinMenu::EraseBkgnd(HWND hWnd, HDC hDC)
{
  CDC* pDC = CDC::FromHandle (hDC);
  CRect Rect;
  //  Get the size of the menu...
  GetClientRect(hWnd, Rect );

  pDC->FillSolidRect (Rect,GetMenuColor());

  return TRUE;
}

void CSkinMenu::DrawTitle(LPDRAWITEMSTRUCT lpDIS,BOOL bIsMenuBar)
{
	DrawMenuTitle(lpDIS,bIsMenuBar);
}

void CSkinMenu::DrawMenuTitle(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  UNREFERENCED_PARAMETER(bIsMenuBar);

  CDC* pDC = CDC::FromHandle(lpDIS->hDC);

  CSkinMenuItemData* pMenuData = (CSkinMenuItemData*)(lpDIS->itemData);
  ASSERT(pMenuData);

  COLORREF colorWindow = GetSysColor(COLOR_WINDOW);
  COLORREF colorMenuBar = GetMenuColor();

  COLORREF colorLeft = MixedColor(colorWindow,colorMenuBar);
  COLORREF colorRight = ::GetSysColor(COLOR_ACTIVECAPTION);
  COLORREF colorText = ::GetSysColor(COLOR_CAPTIONTEXT);

  CSize iconSize(0,0);
  if(pMenuData->m_nMenuIconOffset!=(-1) && pMenuData->m_pMenuIcon)
  {
    iconSize = pMenuData->m_pMenuIcon->GetIconSize();
    if(iconSize!=CSize(0,0))
    {
      iconSize += CSize(4,4);
    }
  }

  CSkinMenuItemDataTitle* pItem = DYNAMIC_DOWNCAST(CSkinMenuItemDataTitle,pMenuData);
  if(pItem)
  {
    if(pItem->m_clrRight!=CLR_DEFAULT)
    {
      colorRight = pItem->m_clrRight;
    }
    if(pItem->m_clrLeft!=CLR_DEFAULT)
    {
      colorLeft = pItem->m_clrLeft;
    }
    if(pItem->m_clrTitle!=CLR_DEFAULT)
    {
      colorText = pItem->m_clrTitle;
    }
  }

  CRect rcClipBox;

  HWND hWnd = ::WindowFromDC(lpDIS->hDC);
  // try to get the real size of the client window
  if(hWnd==NULL || !GetClientRect(hWnd,rcClipBox) )
  {
    // when we have menu animation the DC is a memory DC
    pDC->GetClipBox(rcClipBox);
  }

  // draw the title bar
  CRect rect = lpDIS->rcItem;
  CPoint TextPoint;

  CFont Font;
  LOGFONT MyFont = m_MenuTitleFont;
  if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
  {
    rect.top = rcClipBox.top;
    rect.bottom = rcClipBox.bottom;
    rect.right += GetSystemMetrics(SM_CXMENUCHECK);
    MyFont.lfOrientation = 900;
    MyFont.lfEscapement = 900;
    TextPoint = CPoint(rect.left+2, rect.bottom-4-iconSize.cy);
  }
  else
  {
    MyFont.lfOrientation = 0;
    MyFont.lfEscapement = 0;

    TextPoint = CPoint(rect.left+2+iconSize.cx, rect.top);
  }
  Font.CreateFontIndirect(&MyFont);
  CFont *pOldFont = pDC->SelectObject(&Font);
  SIZE size = {0,0};
  VERIFY(::GetTextExtentPoint32(pDC->m_hDC,pMenuData->m_szMenuText,pMenuData->m_szMenuText.GetLength(),&size));
  COLORREF oldColor = pDC->SetTextColor(colorText);
  int OldMode = pDC->SetBkMode(TRANSPARENT);

  if(pMenuData->m_nTitleFlags&MFT_GRADIENT)
  {
    if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
		DrawHelpers()->GradientFill(pDC,rect,colorLeft,colorRight,false);
    }
    else
    {
      DrawHelpers()->GradientFill(pDC,rect,colorRight,colorLeft,true);
    }
  }
  else
  {
    if(pMenuData->m_nTitleFlags&MFT_ROUND)
    {
      if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
      {
        TextPoint.y-=2;
        rect.right = rect.left+size.cy+4;
      }
      else
      {
        int maxSpace = ((rect.Width()-size.cx)/2);
        TextPoint.x+=min(maxSpace,10);
      }

      CBrush brush(colorRight);
      CPen* pOldPen = (CPen*)pDC->SelectStockObject(WHITE_PEN);
      CBrush* pOldBrush = pDC->SelectObject(&brush);

      pDC->RoundRect(rect,CPoint(10,10));
      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen);
    }
    else
    {
      pDC->FillSolidRect(rect,colorRight);
    }
  }
  if (pMenuData->m_nTitleFlags&MFT_SUNKEN)
  {
    pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
  }

  if (pMenuData->m_nTitleFlags&MFT_CENTER)
  {
    if (pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
      TextPoint.y = rect.bottom - ((rect.Height()-size.cx-iconSize.cy)>>1)-iconSize.cy;
    }
    else
    {
      TextPoint.x = rect.left + ((rect.Width()-size.cx-iconSize.cx)>>1)+iconSize.cx;
    }
  }

  pDC->TextOut(TextPoint.x,TextPoint.y, pMenuData->GetString(m_bDrawAccelerators ? m_hAccelToDraw : NULL));

  if(pMenuData->m_nMenuIconOffset!=(-1) && pMenuData->m_pMenuIcon)
  {
    CPoint ptImage = TextPoint;
    if (pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
      ptImage.y += 2;
    }
    else
    {
      ptImage.x -= iconSize.cx;
      ptImage.y += 2;
    }
    // draws the icon
    HICON hDrawIcon2 = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset);
    pDC->DrawState(ptImage, iconSize-CSize(4,4), hDrawIcon2, DSS_NORMAL,(HBRUSH)NULL);
    DestroyIcon(hDrawIcon2);
  }

  if(pMenuData->m_nTitleFlags&MFT_LINE)
  {
    if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
      CRect rect2(rect.left+20,rect.top+5,rect.left+22,rect.bottom-5);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
      rect2.OffsetRect(3,0);
      rect2.InflateRect(0,-10);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
    }
    else
    {
      CRect rect2(rect.left+2,rect.bottom-7,rect.right-2,rect.bottom-5);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
      rect2.OffsetRect(0,3);
      rect2.InflateRect(-10,0);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
    }
  }
  pDC->SetBkMode(OldMode);
  pDC->SetTextColor(oldColor);
  pDC->SelectObject(pOldFont);
}

void CSkinMenu::DrawItem_WinXP(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
	ASSERT(lpDIS != NULL);

	CSkinMenuItemData* pMenuData = (CSkinMenuItemData*)(lpDIS->itemData);
	ASSERT(pMenuData);

	UINT nFlags = pMenuData->m_nFlags;

	CBufferDC memDC(lpDIS->hDC, CRect(lpDIS->rcItem));
	memDC.SetWindowOrg(lpDIS->rcItem.left, lpDIS->rcItem.top);

	BOOL bCancel = FALSE;
	CDC* pDC;
	if( nFlags & MF_SEPARATOR )
	{ // For title and menubardrawing disable memory painting
		//memDC.DoCancel();
		bCancel = TRUE;
		pDC = CDC::FromHandle(lpDIS->hDC);
	}
	else
	{
		pDC = &memDC;
	}

	COLORREF colorWindow = GetSysColor(COLOR_WINDOW);
	//  COLORREF colorMenuBar = bIsMenuBar?GetMenuBarColor(m_hMenu):GetMenuColor();
	COLORREF colorMenuBar = GetMenuBarColor(m_hMenu);
	COLORREF colorMenu = RGB(234,244,254);//MixedColor(colorWindow,colorMenuBar);
	COLORREF colorBitmap = RGB(196,229,251);//MixedColor(GetMenuBarColor(m_hMenu),colorWindow);
	COLORREF colorSel = RGB(0,172,227);//GetXpHighlightColor();
	COLORREF colorBorder = RGB(0,172,227); //GetSysColor(COLOR_HIGHLIGHT);//DarkenColor(128,colorMenuBar);

	if(bHighContrast)
	{
		colorBorder = GetSysColor(COLOR_BTNTEXT);
	}

	if (NumScreenColors() <= 256)
	{
		colorBitmap = GetSysColor(COLOR_BTNFACE);
	}

	// Better contrast when you have less than 256 colors
	if(pDC->GetNearestColor(colorMenu)==pDC->GetNearestColor(colorBitmap))
	{
		colorMenu = colorWindow;
		colorBitmap = colorMenuBar;
	}

	//CPen Pen(PS_SOLID,0,GetSysColor(COLOR_HIGHLIGHT));
	CPen Pen(PS_SOLID,0,colorBorder);

	CBrush m_brSel(colorSel);
	CBrush m_brBitmap(colorBitmap);

	CRect RectIcon(lpDIS->rcItem);
	CRect RectText(lpDIS->rcItem);
	CRect RectSel(lpDIS->rcItem);

	if(nFlags & MFT_RIGHTORDER)
	{
		RectIcon.left = RectIcon.right - (m_iconX + 8);
		RectText.right  = RectIcon.left;
	}
	else
	{
		RectIcon.right = RectIcon.left + m_iconX + 8;
		RectText.left  = RectIcon.right;
	}
	// Draw for Bitmap background
	pDC->FillSolidRect (RectIcon,colorBitmap);

	// Draw for Textbackground
	pDC->FillSolidRect (RectText,colorMenu);

	// Spacing for submenu only in popups
	if(nFlags & MFT_RIGHTORDER)
	{
		RectText.left += 15;
		RectText.right -= 4;
	}
	else
	{
		RectText.left += 4;
		RectText.right -= 15;
	}

	//  Flag for highlighted item
	if(lpDIS->itemState & (ODS_HOTLIGHT|ODS_INACTIVE) )
	{
		lpDIS->itemState |= ODS_SELECTED;
	}

	// For keyboard navigation only
	BOOL bDrawSmallSelection = FALSE;

	// remove the selected bit if it's grayed out
	if( (lpDIS->itemState&ODS_GRAYED) && !m_bSelectDisable)
	{
		if( lpDIS->itemState & ODS_SELECTED )
		{
			lpDIS->itemState = lpDIS->itemState & (~ODS_SELECTED);
			DWORD MsgPos = ::GetMessagePos();
			if( MsgPos==CSkinMenuHook::m_dwMsgPos )
			{
				bDrawSmallSelection = TRUE;
			}
			else
			{
				CSkinMenuHook::m_dwMsgPos = MsgPos;
			}
		}
	}

  // Draw the seperator
  if( nFlags & MF_SEPARATOR )
  {
	  if( pMenuData->m_nTitleFlags & MFT_TITLE )
	  {
		  DrawTitle(lpDIS,bIsMenuBar);
	  }
	  else
	  {
		  //绘制分隔线
		  CRect rect;
		  rect.top = RectText.CenterPoint().y;
		  rect.bottom = rect.top+1;

		  if(nFlags & MFT_RIGHTORDER)
		  {
			  rect.right = RectText.right;
			  rect.left = lpDIS->rcItem.left;
		  }
		  else
		  {
			  rect.right = lpDIS->rcItem.right;
			  rect.left = RectText.left;
		  }

		  CRect rc(rect.left, rect.top, rect.right-(rect.Width()/2), rect.bottom);

		  DrawHelpers()->GradientFill(pDC,rc,RGB(234,244,254), RGB(168,215,240), FALSE);
		  rc.OffsetRect(0,1);
		  DrawHelpers()->GradientFill(pDC,rc,RGB(234,244,254), RGB(255,255,255), FALSE);

		  rc.SetRect(rect.right-(rect.Width()/2), rect.top, rect.right, rect.bottom);
		  DrawHelpers()->GradientFill(pDC,rc,RGB(168,215,240), RGB(234,244,254), FALSE);
		  rc.OffsetRect(0,1);
		  DrawHelpers()->GradientFill(pDC,rc,RGB(255,255,255), RGB(234,244,254), FALSE);
	  }
  }
  else
  {
	  //绘制选区
	  if( (lpDIS->itemState & ODS_SELECTED) && !(lpDIS->itemState & ODS_INACTIVE) )
	  {
		  CRgn rgn;
		  CRect rcRegion = RectSel;
		  rcRegion.OffsetRect(-rcRegion.TopLeft());

		  //创建区域
		  rgn.CreateRoundRectRgn(rcRegion.left, rcRegion.top, rcRegion.right+1, rcRegion.bottom+1, 3, 3);
		  int nSaveDC = pDC->SaveDC();
		  pDC->SelectClipRgn(&rgn);

		  //梯度填充
		  DrawHelpers()->GradientFill(pDC, RectSel, RGB(63,152,217),RGB(48,134,198), TRUE);

		  pDC->RestoreDC(nSaveDC);
		  rgn.DeleteObject();
	  }
	  else if (bDrawSmallSelection)
	  {
		  pDC->FillSolidRect(RectSel,colorMenu);
		  // Draw the selection for keyboardnavigation
		  CPen* pOldPen = pDC->SelectObject(&Pen);
		  CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);
		  pDC->Rectangle(RectSel);
		  pDC->SelectObject(pOldBrush);
		  pDC->SelectObject(pOldPen);
	  }

	  UINT state = lpDIS->itemState;

	  BOOL standardflag=FALSE;
	  BOOL selectedflag=FALSE;
	  BOOL disableflag=FALSE;
	  BOOL checkflag=FALSE;

	  CString strText = pMenuData->GetString(m_bDrawAccelerators ? m_hAccelToDraw : NULL);

	  if( (state&ODS_CHECKED) && (pMenuData->m_nMenuIconOffset<0) )
	  {
		  if(state&ODS_SELECTED && m_selectcheck>0)
		  {
			  checkflag=TRUE;
		  }
		  else if(m_unselectcheck>0)
		  {
			  checkflag=TRUE;
		  }
	  }
	  else if(pMenuData->m_nMenuIconOffset != -1)
	  {
		  standardflag=TRUE;
		  if(state&ODS_SELECTED)
		  {
			  selectedflag=TRUE;
		  }
		  else if(state&ODS_GRAYED)
		  {
			  disableflag=TRUE;
		  }
	  }

	  // draw the menutext
	  if(!strText.IsEmpty())
	  {
		  LOGFONT logFontMenu;
		  CFont fontMenu;

		  NONCLIENTMETRICS nm = {0};
#if _MSC_VER >= 1500
		  nm.cbSize = sizeof (NONCLIENTMETRICS) - sizeof(nm.iPaddedBorderWidth);
#else
		  nm.cbSize = sizeof (NONCLIENTMETRICS);
#endif
		  VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0));
		  logFontMenu =  nm.lfMenuFont;

		  // Default selection?
		  if(state&ODS_DEFAULT)
		  {
			  // Make the font bold
			  logFontMenu.lfWeight = FW_BOLD;
		  }
		  if(state&ODS_DRAW_VERTICAL)
		  {
			  // rotate font 90?
			  logFontMenu.lfOrientation = -900;
			  logFontMenu.lfEscapement = -900;
		  }

		  fontMenu.CreateFontIndirect(&logFontMenu);

		  CString leftStr;
		  CString rightStr;
		  leftStr.Empty();
		  rightStr.Empty();

		  int tablocr=strText.ReverseFind(_T('\t'));
		  if(tablocr!=-1)
		  {
			  rightStr=strText.Mid(tablocr+1);
			  leftStr=strText.Left(strText.Find(_T('\t')));
		  }
		  else
		  {
			  leftStr = strText;
		  }

		  // Draw the text in the correct color:
		  UINT nFormat  = DT_LEFT| DT_SINGLELINE|DT_VCENTER;
		  UINT nFormatr = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;
		  if(nFlags&MFT_RIGHTORDER)
		  {
			  nFormat  = DT_RIGHT| DT_SINGLELINE|DT_VCENTER|DT_RTLREADING;
			  nFormatr = DT_LEFT|DT_SINGLELINE|DT_VCENTER;
		  }

		  int iOldMode = pDC->SetBkMode( TRANSPARENT);
		  CFont* pOldFont = pDC->SelectObject (&fontMenu);

		  COLORREF OldTextColor;
		  if( (lpDIS->itemState&ODS_GRAYED) ||
			  (bIsMenuBar && lpDIS->itemState&ODS_INACTIVE) )
		  {
			  // Draw the text disabled?
			  OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		  }
		  else
		  {
			  // Draw the text normal
			  if( bHighContrast && !bIsMenuBar && !(state&ODS_SELECTED) )
			  {
				  OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
			  }
			  else
			  {
				  OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_MENUTEXT));
			  }
		  }
		  UINT dt_Hide = (lpDIS->itemState & ODS_NOACCEL)?DT_HIDEPREFIX:0;
		  if(dt_Hide && SystemVersion()->IsWinXPOrGreater())
		  {
			  BOOL bMenuUnderlines = TRUE;
			  if(SystemParametersInfo( SPI_GETKEYBOARDCUES,0,&bMenuUnderlines,0)==TRUE && bMenuUnderlines==TRUE)
			  {
				  // do not hide
				  dt_Hide = 0;
			  }
		  }


		  pDC->DrawText(leftStr,RectText, nFormat|dt_Hide);
		  if(tablocr!=-1)
		  {
			  pDC->DrawText (rightStr,RectText,nFormatr|dt_Hide);
		  }

		  pDC->SetTextColor(OldTextColor);
		  pDC->SelectObject(pOldFont);
		  pDC->SetBkMode(iOldMode);
	  }

	  // Draw the bitmap or checkmarks

	  CRect rect2 = RectText;

	  if(checkflag||standardflag||selectedflag||disableflag)
	  {
		  if(checkflag && m_checkmaps)
		  {
			  CPoint ptImage(RectIcon.left+3,RectIcon.top+4);

			  if(state&ODS_SELECTED)
			  {
				  m_checkmaps->Draw(pDC,1,ptImage,ILD_TRANSPARENT);
			  }
			  else
			  {
				  m_checkmaps->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
			  }
		  }
		  else
		  {
			  CSize size = pMenuData->m_pMenuIcon->GetIconSize();
			  HICON hDrawIcon = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset);
			  //CPoint ptImage(RectIcon.left+3,RectIcon.top+ 4);
			  CPoint ptImage( RectIcon.left+3, RectIcon.top + ((RectIcon.Height()-size.cy)>>1) );

			  // Need to draw the checked state
			  if (state&ODS_CHECKED)
			  {
				  CRect rect = RectIcon;
				  if(nFlags&MFT_RIGHTORDER)
				  {
					  rect.InflateRect (-2,-1,-1,-1);
				  }
				  else
				  {
					  rect.InflateRect (-1,-1,-2,-1);
				  }
				  if(selectedflag)
				  {
					  if (NumScreenColors() > 256)
					  {
						  pDC->FillSolidRect(rect,MixedColor(colorSel,GetSysColor(COLOR_HIGHLIGHT)));
					  }
					  else
					  {
						  pDC->FillSolidRect(rect,colorSel); //GetSysColor(COLOR_HIGHLIGHT)
					  }
				  }
				  else
				  {
					  pDC->FillSolidRect(rect,MixedColor(colorBitmap,GetSysColor(COLOR_HIGHLIGHT)));
				  }

				  CPen* pOldPen = pDC->SelectObject(&Pen);
				  CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);

				  pDC->Rectangle(rect);

				  pDC->SelectObject(pOldBrush);
				  pDC->SelectObject(pOldPen);
			  }

			  // Correcting of a smaler icon
			  if(size.cx<m_iconX)
			  {
				  ptImage.x += (m_iconX-size.cx)>>1;
			  }

			  if(state & ODS_DISABLED)
			  {
				  if(m_bEnableXpBlending)
				  {
					  // draws the icon blended
					  HICON hDrawIcon2 = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset+2);
					  pDC->DrawState(ptImage, size, hDrawIcon2, DSS_NORMAL,(HBRUSH)NULL);
					  DestroyIcon(hDrawIcon2);
				  }
				  else
				  {
					  CBrush Brush;
					  Brush.CreateSolidBrush(pDC->GetNearestColor(DrawHelpers()->DarkenColor(70,colorBitmap)));
					  pDC->DrawState(ptImage, size, hDrawIcon, DSS_MONO, &Brush);
				  }
			  }
			  else
			  {
				  if(selectedflag)
				  {
					  CBrush Brush;
					  // Color of the shade
					  Brush.CreateSolidBrush(pDC->GetNearestColor(DarkenColorXP(colorSel)));
					  if(!(state & ODS_CHECKED))
					  {
						  ptImage.x++; ptImage.y++;
						  pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL | DSS_MONO, &Brush);
						  ptImage.x-=2; ptImage.y-=2;
					  }
					  pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL,(HBRUSH)NULL);
				  }
				  else
				  {
					  if(m_bEnableXpBlending)
					  {
						  // draws the icon blended
						  HICON hDrawIcon2 = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset+1);
						  pDC->DrawState(ptImage, size, hDrawIcon2, DSS_NORMAL,(HBRUSH)NULL);
						  DestroyIcon(hDrawIcon2);
					  }
					  else
					  {
						  // draws the icon with normal color
						  pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL,(HBRUSH)NULL);
					  }
				  }
			  }
			  DestroyIcon(hDrawIcon);
		  }
	  }

	  if(pMenuData->m_nMenuIconOffset<0 /*&& state&ODS_CHECKED */ && !checkflag)
	  {
		  MENUITEMINFO info = {0};
		  info.cbSize = sizeof(info);
		  info.fMask = MIIM_CHECKMARKS;

		  ::GetMenuItemInfo(HMENU(lpDIS->hwndItem),lpDIS->itemID,MF_BYCOMMAND, &info);

		  if(state&ODS_CHECKED || info.hbmpUnchecked)
		  {
			  CRect rect = RectIcon;
			  if(nFlags&MFT_RIGHTORDER)
			  {
				  rect.InflateRect (-2,-1,-1,-1);
			  }
			  else
			  {
				  rect.InflateRect (-1,-1,-2,-1);
			  }
			  // draw the color behind checkmarks
			  if(state&ODS_SELECTED)
			  {
				  if (NumScreenColors() > 256)
				  {
					  pDC->FillSolidRect(rect,MixedColor(colorSel,GetSysColor(COLOR_HIGHLIGHT)));
				  }
				  else
				  {
					  pDC->FillSolidRect(rect,colorSel);
				  }
			  }
			  else
			  {
				  pDC->FillSolidRect(rect,MixedColor(colorBitmap,GetSysColor(COLOR_HIGHLIGHT)));
			  }
			  CPen* pOldPen = pDC->SelectObject(&Pen);
			  CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);

			  pDC->Rectangle(rect);

			  pDC->SelectObject(pOldBrush);
			  pDC->SelectObject(pOldPen);
			  if (state&ODS_CHECKED)
			  {
				  CRect rect(RectIcon);
				  rect.InflateRect(2,((m_iconY-RectIcon.Height())>>1)+2);

				  if (!info.hbmpChecked)
				  { // Checkmark
					  DrawSpecialCharStyle(pDC,rect,98,state);
				  }
				  else if(!info.hbmpUnchecked)
				  { // Bullet
					  DrawSpecialCharStyle(pDC,rect,105,state);
				  }
				  else
				  { // Draw Bitmap
					  BITMAP myInfo = {0};
					  GetObject((HGDIOBJ)info.hbmpChecked,sizeof(myInfo),&myInfo);
					  CPoint Offset = RectIcon.TopLeft() + CPoint((RectIcon.Width()-myInfo.bmWidth)/2,(RectIcon.Height()-myInfo.bmHeight)/2);
					  pDC->DrawState(Offset,CSize(0,0),info.hbmpChecked,DST_BITMAP|DSS_MONO);
				  }
			  }
			  else if(info.hbmpUnchecked)
			  {
				  // Draw Bitmap
				  BITMAP myInfo = {0};
				  GetObject((HGDIOBJ)info.hbmpUnchecked,sizeof(myInfo),&myInfo);
				  CPoint Offset = RectIcon.TopLeft() + CPoint((RectIcon.Width()-myInfo.bmWidth)/2,(RectIcon.Height()-myInfo.bmHeight)/2);
				  if(state & ODS_DISABLED)
				  {
					  pDC->DrawState(Offset,CSize(0,0),info.hbmpUnchecked,DST_BITMAP|DSS_MONO|DSS_DISABLED);
				  }
				  else
				  {
					  pDC->DrawState(Offset,CSize(0,0),info.hbmpUnchecked,DST_BITMAP|DSS_MONO);
				  }
			  }
		  }
		  else if ((lpDIS->itemID&0xffff)>=SC_SIZE && (lpDIS->itemID&0xffff)<=SC_HOTKEY )
		  {
			  DrawSpecial_WinXP(pDC,RectIcon,lpDIS->itemID,state);
		  }
	  }
  }

  if (!bCancel)
  {
	  BitBlt(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top, lpDIS->rcItem.right-lpDIS->rcItem.left, lpDIS->rcItem.bottom-lpDIS->rcItem.top,
		  pDC->GetSafeHdc(), lpDIS->rcItem.left, lpDIS->rcItem.top, SRCCOPY);
  }
}

BOOL CSkinMenu::IsMenuBar(HMENU hMenu)
{
	BOOL bIsMenuBar = FALSE;
	if(!FindMenuItem((UINT)hMenu))
	{
		if(m_hParentMenu==NULL)
		{
			return m_bIsPopupMenu?FALSE:TRUE;
		}
		CSkinMenu* pMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(m_hParentMenu));
		if (pMenu!=NULL)
		{
			return pMenu->m_bIsPopupMenu?FALSE:TRUE;
		}
	}
	else
	{
		// Test for only one item not bar
		bIsMenuBar = m_hParentMenu ? FALSE: ((m_bIsPopupMenu)?FALSE:TRUE);
	}
	return bIsMenuBar;
}


void CSkinMenu::MeasureItem_WinXP( LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenuBar )
{
	ASSERT(lpMIS->itemData);
	CSkinMenuItemData* pMenuData = (CSkinMenuItemData*)(lpMIS->itemData);

	UINT nFlag = pMenuData->m_nFlags;
	if(nFlag & MF_SEPARATOR)
	{
		if(pMenuData->m_nTitleFlags&MFT_TITLE)
		{
			SIZE size = {0,0};
			{// We need this sub-block for releasing the dc
				// DC of the desktop
				CClientDC myDC(NULL);

				CFont font;
				LOGFONT MyFont = m_MenuTitleFont;
				MyFont.lfOrientation = 0;
				MyFont.lfEscapement = 0;
				font.CreateFontIndirect(&MyFont);

				CFont* pOldFont = myDC.SelectObject (&font);
				CString lpstrText = pMenuData->GetString(m_bDrawAccelerators ? m_hAccelToDraw : NULL);
				VERIFY(::GetTextExtentPoint32(myDC.m_hDC,lpstrText,(int)_tcslen(lpstrText),&size));
				// Select old font in
				myDC.SelectObject(pOldFont);
			}

			CSize iconSize(0,0);
			if(pMenuData->m_nMenuIconOffset!=(-1) && pMenuData->m_pMenuIcon)
			{
				iconSize = pMenuData->m_pMenuIcon->GetIconSize();
				if(iconSize!=CSize(0,0))
				{
					iconSize += CSize(2,2);
				}
			}

			if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
			{
				lpMIS->itemWidth = max(size.cy,iconSize.cx) - GetSystemMetrics(SM_CXMENUCHECK);
			
				// Don't make the menu higher than menuitems in it
				lpMIS->itemHeight = 0;
				if(pMenuData->m_nTitleFlags&MFT_LINE)
				{
					lpMIS->itemWidth += 8;
				}
				else if(pMenuData->m_nTitleFlags&MFT_ROUND)
				{
					lpMIS->itemWidth += 4;
				}
			}
			else
			{
				lpMIS->itemWidth = size.cx + iconSize.cx;
				lpMIS->itemHeight = max(size.cy,iconSize.cy);
				if(pMenuData->m_nTitleFlags&MFT_LINE)
				{
					lpMIS->itemHeight += 8;
				}
			}
		}
		else
		{
			lpMIS->itemHeight = 3;
			lpMIS->itemWidth = 3;
		}
	}
	else
	{
		SIZE size = {0,0};
		//Get pointer to text SK
		CString itemText = pMenuData->GetString(m_bDrawAccelerators ? m_hAccelToDraw : NULL);
		{ // We need this sub-block for releasing the dc
			CFont fontMenu;
			LOGFONT logFontMenu;

			NONCLIENTMETRICS nm = {0};
#if _MSC_VER >= 1500
			nm.cbSize = sizeof (NONCLIENTMETRICS) - sizeof(nm.iPaddedBorderWidth);
#else
			nm.cbSize = sizeof (NONCLIENTMETRICS);
#endif
			VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0));
			logFontMenu =  nm.lfMenuFont;

			// Default selection?
			if (GetDefaultItem(0, FALSE) == pMenuData->m_nID)
			{
				// Make the font bold
				logFontMenu.lfWeight = FW_BOLD;
			}

			fontMenu.CreateFontIndirect (&logFontMenu);

			// DC of the desktop
			CClientDC myDC(NULL);
			// Select menu font in...
			CFont* pOldFont = myDC.SelectObject (&fontMenu);
			// Check the Key-Shortcut replacing for japanise/chinese calculating space
			itemText.Replace(_T("\t"),_T("nnn"));
			VERIFY(::GetTextExtentPoint32(myDC.m_hDC,itemText,itemText.GetLength(),&size));
			// Select old font in
			myDC.SelectObject(pOldFont);
		}// We need this sub-block for releasing the dc

		int temp = GetSystemMetrics(SM_CYMENU);
		// Set width and height:
		if(nFlag & MF_POPUP)
		{
			lpMIS->itemWidth = 2 + m_iconX + 4 + size.cx + GetSystemMetrics(SM_CYMENU);
		}
		else
		{
			lpMIS->itemWidth = 2 + m_iconX + 4 + size.cx + GetSystemMetrics(SM_CYMENU) / 2;
		}
		lpMIS->itemHeight = temp>m_iconY+8 ? temp : m_iconY+7;


		if(lpMIS->itemHeight<((UINT)size.cy) )
		{
			lpMIS->itemHeight=((UINT)size.cy);
		}

		// set status bar as appropriate
		UINT nItemID = (lpMIS->itemID & 0xFFF0);
		// Special case for system menu
		if (nItemID>=SC_SIZE && nItemID<=SC_HOTKEY)
		{
			BOOL bGetNext = FALSE;
			// search the actual menu item
			for (int j=0;j<m_MenuItemList.GetUpperBound();++j)
			{
				CSkinMenuItemData* pTemp = m_MenuItemList[j];
				if(pTemp==pMenuData || bGetNext==TRUE)
				{
					bGetNext = TRUE;
					pTemp = m_MenuItemList[j+1];
					if(pTemp->m_nID)
					{
						lpMIS->itemData = (ULONG_PTR)pTemp;
						lpMIS->itemID = pTemp->m_nID;
						UINT nOrgWidth = lpMIS->itemWidth;
						MeasureItem_WinXP(lpMIS,bIsMenuBar);
						// Restore old values
						lpMIS->itemData = (ULONG_PTR)pMenuData;
						lpMIS->itemID = pMenuData->m_nID;
						lpMIS->itemWidth = max(lpMIS->itemWidth,nOrgWidth);
						break;
					}
				}
			}
			lpMIS->itemHeight = temp;
		}
	}
	//TRACE("IsMenuBar %ld, Height %2ld, width %3ld, ID 0x%08lX \r\n",int(bIsMenuBar),lpMIS->itemHeight,lpMIS->itemWidth,lpMIS->itemID);
}

void CSkinMenu::SetIconSize (int width, int height)
{
	m_iconX = width;
	m_iconY = height;
}

CSize CSkinMenu::GetIconSize()
{
	return CSize(m_iconX,m_iconY);
}

BOOL CSkinMenu::AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID, int nIconNormal)
{
	return CSkinMenu::AppendODMenu(lpstrText,nFlags,nID,(CImageList*)NULL,nIconNormal);
}

BOOL CSkinMenu::AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID,
							 CBitmap* pBmp)
{
	int nIndex = -1;
	CSkinMenuIconLock iconLock(GetMenuIcon(nIndex,pBmp));
	return AppendODMenu(lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CSkinMenu::AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID,
							 CImageList* pil, int xoffset)
{
	int nIndex = 0;
	// Helper for addref and release
	CSkinMenuIconLock iconLock(GetMenuIcon(nIndex,nID,pil,xoffset));
	return AppendODMenu(lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CSkinMenu::AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID,
							 CSkinMenuIcons* pIcons, int nIndex)
{
	// Add the MF_OWNERDRAW flag if not specified:

	if(!(nFlags & MF_OWNERDRAW))
	{
		nFlags |= MF_OWNERDRAW;
	}

	if(nFlags & MF_POPUP)
	{
		CSkinMenu* pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(HMENU(nID)));
		if(pSubMenu)
		{
			pSubMenu->m_hParentMenu = m_hMenu;
		}
	}

	CSkinMenuItemData* pItemData = new CSkinMenuItemData;
	m_MenuItemList.Add(pItemData);
	pItemData->SetString(lpstrText);

	pIcons->AddRef();
	pItemData->m_pMenuIcon->Release();
	pItemData->m_pMenuIcon = pIcons;
	pItemData->m_nFlags = nFlags;
	pItemData->m_nID = nID;

	if(pIcons && nIndex>=0)
	{
		pItemData->m_nMenuIconOffset = nIndex;
		CSize size = pIcons->GetIconSize();
		m_iconX = max(m_iconX,size.cx);
		m_iconY = max(m_iconY,size.cy);
	}
	else
	{
		pItemData->m_nMenuIconOffset = -1;
	}

	// for having automated shortcut handling, thank to Mehdy Bohlool
	if (CMenu::AppendMenu(nFlags&~MF_OWNERDRAW, nID, pItemData->m_szMenuText))
	{
		return CMenu::ModifyMenu( CMenu::GetMenuItemCount()-1, MF_BYPOSITION| nFlags, nID, (LPCTSTR)pItemData );
	}
	return FALSE;
}

BOOL CSkinMenu::InsertODMenu(UINT nPosition, LPCTSTR lpstrText, UINT nFlags, UINT nID,
							 int nIconNormal)
{
	int nIndex = -1;
	CSkinMenuIcons* pIcons=NULL;

	if(nIconNormal>=0)
	{
		if(LoadFromToolBar(nID,nIconNormal,nIndex))
		{
			// the nIconNormal is a toolbar
			pIcons = GetToolbarIcons(nIconNormal);
			if(pIcons)
			{
				nIndex = pIcons->FindIndex(nID);
			}
		}
		else
		{
			// the nIconNormal is a bitmap
			pIcons = GetMenuIcon(nIndex,nIconNormal);
		}
	}

	CSkinMenuIconLock iconLock(pIcons);
	return InsertODMenu(nPosition,lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CSkinMenu::InsertODMenu(UINT nPosition, LPCTSTR lpstrText, UINT nFlags, UINT nID,
							 CBitmap* pBmp)
{
	int nIndex = -1;
	CSkinMenuIconLock iconLock(GetMenuIcon(nIndex,pBmp));
	return InsertODMenu(nPosition,lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CSkinMenu::InsertODMenu(UINT nPosition, LPCTSTR lpstrText, UINT nFlags, UINT nID,
							 CImageList *pil, int xoffset)
{
	int nIndex = -1;
	CSkinMenuIconLock iconLock(GetMenuIcon(nIndex,nID,pil,xoffset));
	return InsertODMenu(nPosition,lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CSkinMenu::InsertODMenu(UINT nPosition, LPCTSTR lpstrText, UINT nFlags, UINT nID,
							 CSkinMenuIcons* pIcons, int nIndex)
{
	if(!(nFlags & MF_BYPOSITION))
	{
		int iPosition =0;
		CSkinMenu* pMenu = FindMenuOption(nPosition,iPosition);
		if(pMenu)
		{
			return(pMenu->InsertODMenu(iPosition,lpstrText,nFlags|MF_BYPOSITION,nID,pIcons,nIndex));
		}
		else
		{
			return(FALSE);
		}
	}

	if(!nID)
	{
		nFlags=MF_SEPARATOR|MF_OWNERDRAW|MF_BYPOSITION;
	}
	else if(!(nFlags & MF_OWNERDRAW))
	{
		nFlags |= MF_OWNERDRAW;
	}

	if(nFlags & MF_POPUP)
	{
		CSkinMenu* pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(HMENU(nID)));
		if(pSubMenu)
		{
			pSubMenu->m_hParentMenu = m_hMenu;
		}
	}

	//Stephane Clog suggested adding this, believe it or not it's in the help
	if(nPosition==(UINT)-1)
	{
		nPosition = GetMenuItemCount();
	}

	CSkinMenuItemData *pItemData = new CSkinMenuItemData;
	m_MenuItemList.InsertAt(nPosition,pItemData);
	pItemData->SetString(lpstrText);

	pIcons->AddRef();
	pItemData->m_pMenuIcon->Release();
	pItemData->m_pMenuIcon = pIcons;
	pItemData->m_nFlags = nFlags;
	pItemData->m_nID = nID;

	if(pIcons && nIndex>=0)
	{
		pItemData->m_nMenuIconOffset = nIndex;
		CSize size = pIcons->GetIconSize();
		m_iconX = max(m_iconX,size.cx);
		m_iconY = max(m_iconY,size.cy);
	}
	else
	{
		pItemData->m_nMenuIconOffset = -1;
	}
	// for having automated shortcut handling, thank to Mehdy Bohlool
	if (CMenu::InsertMenu(nPosition,nFlags&~MF_OWNERDRAW,nID,pItemData->m_szMenuText))
	{
		return CMenu::ModifyMenu(nPosition, MF_BYPOSITION| nFlags, nID, (LPCTSTR)pItemData );
	}
	return FALSE;
}

// Same as ModifyMenu but replacement for CSkinMenu
BOOL CSkinMenu::ModifyODMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem,LPCTSTR lpszNewItem)
{
	if(!(nFlags & MF_BYPOSITION))
	{
		int iPosition =0;
		CSkinMenu* pMenu = FindMenuOption(nPosition,iPosition);
		if(pMenu)
		{
			return(pMenu->ModifyODMenu(iPosition,nFlags|MF_BYPOSITION,nIDNewItem,lpszNewItem));
		}
		else
		{
			return(FALSE);
		}
	}
	UINT nMenuID = GetMenuItemID(nPosition);
	if(nMenuID==(UINT)-1)
	{
		nMenuID = (UINT)::GetSubMenu(m_hMenu,nPosition);
	}
	CSkinMenuItemData* pItemData = FindMenuItem(nMenuID);
	BOOL bRet = CMenu::ModifyMenu(nPosition, nFlags, nIDNewItem,lpszNewItem);
	if(pItemData)
	{
		pItemData->m_nID = nIDNewItem;
		GetMenuString(nPosition,pItemData->m_szMenuText,MF_BYPOSITION);
		CMenu::ModifyMenu(nPosition, nFlags|MF_OWNERDRAW, nIDNewItem,(LPCTSTR)pItemData);
	}
	if(bRet && (nFlags & MF_POPUP) )
	{
		CSkinMenu* pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(HMENU(nIDNewItem)));
		if(pSubMenu)
		{
			pSubMenu->m_hParentMenu = m_hMenu;
		}
	}
	return bRet;
}

BOOL CSkinMenu::ModifyODMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem, const CBitmap* pBmp)
{
	if(!(nFlags & MF_BYPOSITION))
	{
		int iPosition =0;
		CSkinMenu* pMenu = FindMenuOption(nPosition,iPosition);
		if(pMenu)
		{
			return(pMenu->ModifyODMenu(iPosition,nFlags|MF_BYPOSITION,nIDNewItem,pBmp));
		}
		else
		{
			return(FALSE);
		}
	}
	UINT nMenuID = GetMenuItemID(nPosition);
	if(nMenuID==(UINT)-1)
	{
		nMenuID = (UINT)::GetSubMenu(m_hMenu,nPosition);
	}
	CSkinMenuItemData* pItemData = FindMenuItem(nMenuID);
	BOOL bRet = CMenu::ModifyMenu(nPosition, nFlags, nIDNewItem,pBmp);
	if(pItemData)
	{
		pItemData->m_nID = nIDNewItem;
		pItemData->m_szMenuText.Empty();
		CMenu::ModifyMenu(nPosition, nFlags|MF_OWNERDRAW, nIDNewItem,(LPCTSTR)pItemData);
	}
	if(bRet && (nFlags & MF_POPUP) )
	{
		CSkinMenu* pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(HMENU(nIDNewItem)));
		if(pSubMenu)
		{
			pSubMenu->m_hParentMenu = m_hMenu;
		}
	}
	return bRet;
}

BOOL CSkinMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, int nIconNormal)
{
	int nLoc;
	CSkinMenuItemData* pItemData;
	CArray<CSkinMenu*,CSkinMenu*>newSubs;
	CArray<int,int&>newLocs;

	BOOL bModifyOK = TRUE;

	// Find the old CSkinMenuItemData structure:
	CSkinMenu* pSubMenu = FindMenuOption(nID,nLoc);
	do {
		if(pSubMenu && nLoc>=0)
		{
			pItemData = pSubMenu->m_MenuItemList[nLoc];
		}
		else
		{
			// Create a new CSkinMenuItemData structure:
			pItemData = new CSkinMenuItemData;
			m_MenuItemList.Add(pItemData);
		}

		BOOL bTextChanged = FALSE;
		ASSERT(pItemData);
		if(lpstrText && pItemData->m_szMenuText.Compare(lpstrText)!=NULL)
		{
			bTextChanged = TRUE;
			pItemData->SetString(lpstrText);
		}

		pItemData->m_nMenuIconOffset=-1;
		if(nIconNormal>=0)
		{
			int nxOffset = -1;
			CSkinMenuIcons* pIcons=NULL;
			if(LoadFromToolBar(nID,nIconNormal,nxOffset))
			{
				// the nIconNormal is a toolbar
				pIcons = GetToolbarIcons(nIconNormal);
				if(pIcons)
				{
					pItemData->m_nMenuIconOffset = pIcons->FindIndex(nID);
				}
			}
			else
			{
				// the nIconNormal is a bitmap
				pIcons = GetMenuIcon(pItemData->m_nMenuIconOffset,nIconNormal);
			}
			pIcons->AddRef();
			pItemData->m_pMenuIcon->Release();
			pItemData->m_pMenuIcon = pIcons;
			if(pIcons)
			{
				CSize size = pIcons->GetIconSize();
				pSubMenu->m_iconX = max(pSubMenu->m_iconX,size.cx);
				pSubMenu->m_iconY = max(pSubMenu->m_iconY,size.cy);
			}
		}
		pItemData->m_nFlags &= ~(MF_BYPOSITION);
		pItemData->m_nFlags |= MF_OWNERDRAW;
		pItemData->m_nID = nID;

		// for having automated shortcut handling
		if(pSubMenu && bTextChanged)
		{
			if(pSubMenu->ModifyMenu(nLoc, MF_BYPOSITION|(pItemData->m_nFlags&~MF_OWNERDRAW), nID,pItemData->m_szMenuText) )
			{
				if(!pSubMenu->ModifyMenu(nLoc, MF_BYPOSITION|pItemData->m_nFlags, nID,(LPCTSTR)pItemData))
					bModifyOK = FALSE;
			}
			else
			{
				bModifyOK = FALSE;
			}
		}

		newSubs.Add(pSubMenu);
		newLocs.Add(nLoc);

		if(pSubMenu && nLoc>=0)
			pSubMenu = FindAnotherMenuOption(nID,nLoc,newSubs,newLocs);
		else
			pSubMenu = NULL;

	}while(pSubMenu);

	return (CMenu::ModifyMenu(nID,pItemData->m_nFlags,nID,(LPCTSTR)pItemData)) && bModifyOK;
}

BOOL CSkinMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, CImageList *pil, int xoffset)
{
	int nIndex = 0;
	CSkinMenuIcons* pIcons = GetMenuIcon(nIndex,nID,pil,xoffset);
	pIcons->AddRef();

	BOOL bResult = ModifyODMenu(lpstrText,nID,pIcons,nIndex);
	pIcons->Release();

	return bResult;
}

BOOL CSkinMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, CSkinMenuIcons* pIcons, int xoffset)
{
	ASSERT(pIcons);
	int nLoc;
	CSkinMenuItemData *pItemData;
	CArray<CSkinMenu*,CSkinMenu*>newSubs;
	CArray<int,int&>newLocs;
	BOOL bModifyOK = TRUE;

	// Find the old CSkinMenuItemData structure:
	CSkinMenu *pSubMenu = FindMenuOption(nID,nLoc);
	do {
		if(pSubMenu && nLoc>=0)
		{
			pItemData = pSubMenu->m_MenuItemList[nLoc];
		}
		else
		{
			// Create a new CSkinMenuItemData structure:
			pItemData = new CSkinMenuItemData;
			m_MenuItemList.Add(pItemData);
		}

		BOOL bTextChanged = FALSE;
		ASSERT(pItemData);
		if(lpstrText && pItemData->m_szMenuText.Compare(lpstrText)!=NULL)
		{
			bTextChanged = TRUE;
			pItemData->SetString(lpstrText);
		}

		if(pIcons)
		{
			pIcons->AddRef();
			pItemData->m_pMenuIcon->Release();
			pItemData->m_pMenuIcon = pIcons;

			pItemData->m_nMenuIconOffset = xoffset;

			int x=0;
			int y=0;
			if(pSubMenu && pIcons->GetIconSize(&x,&y))
			{
				// Correct the size of the menuitem
				pSubMenu->m_iconX = max(pSubMenu->m_iconX,x);
				pSubMenu->m_iconY = max(pSubMenu->m_iconY,y);
			}
		}
		else
		{
			pItemData->m_nMenuIconOffset = -1;
		}
		pItemData->m_nFlags &= ~(MF_BYPOSITION);
		pItemData->m_nFlags |= MF_OWNERDRAW;
		pItemData->m_nID = nID;

		// for having automated shortcut handling
		if(pSubMenu && bTextChanged)
		{
			if(pSubMenu->ModifyMenu(nLoc, MF_BYPOSITION|(pItemData->m_nFlags&~MF_OWNERDRAW), nID,pItemData->m_szMenuText) )
			{
				if(!pSubMenu->ModifyMenu(nLoc, MF_BYPOSITION|pItemData->m_nFlags, nID,(LPCTSTR)pItemData))
					bModifyOK = FALSE;
			}
			else
			{
				bModifyOK = FALSE;
			}
		}

		newSubs.Add(pSubMenu);
		newLocs.Add(nLoc);
		if(pSubMenu && nLoc>=0)
			pSubMenu = FindAnotherMenuOption(nID,nLoc,newSubs,newLocs);
		else
			pSubMenu = NULL;
	} while(pSubMenu);

	return (CMenu::ModifyMenu(nID,pItemData->m_nFlags,nID,(LPCTSTR)pItemData)) && bModifyOK;
}

BOOL CSkinMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, CBitmap* bmp)
{
	if (bmp)
	{
		CImageList temp;
		temp.Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);

		temp.Add(bmp,GetBitmapBackground());

		return ModifyODMenu(lpstrText,nID,&temp,0);
	}
	return ModifyODMenu(lpstrText,nID,(CImageList*)NULL,0);
}

BOOL CSkinMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, COLORREF fill, COLORREF border, int hatchstyle)
{
	// Get device context
	CSize bitmap_size(m_iconX,m_iconY);
	CBitmap bmp;
	{
		CClientDC DC(0);
		ColorBitmap(&DC,bmp,bitmap_size,fill,border,hatchstyle);
	}
	return ModifyODMenu(lpstrText,nID,&bmp);
}

BOOL CSkinMenu::ModifyODMenu(LPCTSTR lpstrText, LPCTSTR OptionText, int nIconNormal)
{
	int nIndex = 0;
	CSkinMenu* pOptionMenu = FindMenuOption(OptionText,nIndex);

	if(pOptionMenu!=NULL && nIndex>=0)
	{
		CSkinMenuItemData* pItemData = pOptionMenu->m_MenuItemList[nIndex];

		BOOL bTextChanged = FALSE;
		ASSERT(pItemData);
		if(lpstrText && pItemData->m_szMenuText.Compare(lpstrText)!=NULL)
		{
			bTextChanged = TRUE;
			pItemData->SetString(lpstrText);
		}

		pItemData->m_nMenuIconOffset = nIconNormal;
		if(nIconNormal>=0)
		{
			CSkinMenuIcons* pIcons = GetMenuIcon(pItemData->m_nMenuIconOffset,nIconNormal);
			pIcons->AddRef();
			pItemData->m_pMenuIcon->Release();
			pItemData->m_pMenuIcon = pIcons;

			CSkinMenuBitmaps* pMenuIcon = DYNAMIC_DOWNCAST(CSkinMenuBitmaps,pItemData->m_pMenuIcon);
			if(pMenuIcon)
			{
				CSize size = pMenuIcon->GetIconSize();
				pOptionMenu->m_iconX = max(pOptionMenu->m_iconX,size.cx);
				pOptionMenu->m_iconY = max(pOptionMenu->m_iconY,size.cy);
			}
		}

		// for having automated shortcut handling
		if(pOptionMenu && bTextChanged)
		{
			if(!pOptionMenu->ModifyMenu(nIndex, MF_BYPOSITION|(pItemData->m_nFlags&~MF_OWNERDRAW), pItemData->m_nID,pItemData->m_szMenuText) ||
				!pOptionMenu->ModifyMenu(nIndex, MF_BYPOSITION|pItemData->m_nFlags, pItemData->m_nID,(LPCTSTR)pItemData))
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

CSkinMenuItemData* CSkinMenu::NewODMenu(UINT pos, UINT nFlags, UINT nID, LPCTSTR string)
{
	CSkinMenuItemData* pItemData;

	pItemData = new CSkinMenuItemData;
	pItemData->m_nFlags = nFlags;
	pItemData->m_nID = nID;
	if(!(nFlags&MF_BITMAP))
	{
		pItemData->SetString (string);
	}

	if(nFlags & MF_POPUP)
	{
		CSkinMenu* pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(HMENU(nID)));
		if(pSubMenu)
			pSubMenu->m_hParentMenu = m_hMenu;
	}

	BOOL bModified = FALSE;
	if (nFlags&MF_OWNERDRAW)
		bModified = ModifyMenu(pos,nFlags,nID,(LPCTSTR)pItemData);
	else if (nFlags&MF_BITMAP)
		bModified = ModifyMenu(pos,nFlags,nID,(CBitmap*)string);
	else if (nFlags&MF_SEPARATOR)
	{
		ASSERT(nFlags&MF_SEPARATOR);
		bModified = ModifyMenu(pos,nFlags,nID);
	}
	else // (nFlags&MF_STRING)
	{
		ASSERT(!(nFlags&MF_OWNERDRAW));
		bModified = ModifyMenu(pos,nFlags,nID,pItemData->GetString(m_bDrawAccelerators ? m_hAccelToDraw : NULL));
	}
	if(!bModified)
	{
		ShowLastError(_T("Error from Menu: ModifyMenu"));
	}
	return(pItemData);
};

BOOL CSkinMenu::LoadToolBars(const UINT* arID, int n, HMODULE hInst)
{
	ASSERT(arID);
	BOOL returnflag = TRUE;
	for(int i=0;i<n;++i)
	{
		if(!LoadToolBar(arID[i],hInst))
			returnflag = FALSE;
	}
	return(returnflag);
}

DWORD CSkinMenu::SetMenuIcons(CSkinMenuIcons* pMenuIcons)
{
	ASSERT(pMenuIcons);
	int nCount = (int)pMenuIcons->m_IDs.GetSize();
	while(nCount--)
	{
		ModifyODMenu(NULL,pMenuIcons->m_IDs[nCount],pMenuIcons,nCount*MENU_ICONS);
	}
	return pMenuIcons->m_dwRefCount;
}

CSkinMenuIcons* CSkinMenu::GetMenuIcon(int &nIndex, UINT nID, CImageList *pil, int xoffset)
{
	if(pil==NULL || xoffset<0)
	{
		nIndex=-1;
		return NULL;
	}

	HICON hIcon = pil->ExtractIcon(xoffset);

	if(m_pSharedMenuIcons!=NULL)
	{
		POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
		while(pos)
		{
			CSkinMenuBitmaps* pMenuIcon = DYNAMIC_DOWNCAST(CSkinMenuBitmaps,m_pSharedMenuIcons->GetNext(pos));
			if(pMenuIcon)
			{
				nIndex = pMenuIcon->Add(hIcon,nID);
				if(nIndex!=-1)
				{
					DestroyIcon(hIcon);
					return pMenuIcon;
				}
			}
		}
	}
	else
	{
		m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CSkinMenuIcons*>;
	}
	CSkinMenuBitmaps* pMenuIcon = new CSkinMenuBitmaps();
	pMenuIcon->m_crTransparent = m_bitmapBackground;
	nIndex = pMenuIcon->Add(hIcon,nID);
	DestroyIcon(hIcon);
	if(nIndex!=-1)
	{
		m_pSharedMenuIcons->AddTail(pMenuIcon);
		return pMenuIcon;
	}
	delete pMenuIcon;
	return NULL;
}

CSkinMenuIcons* CSkinMenu::GetMenuIcon(int &nIndex, int nID)
{
	if(m_pSharedMenuIcons!=NULL)
	{
		POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
		while(pos)
		{
			CSkinMenuBitmaps* pMenuIcon = DYNAMIC_DOWNCAST(CSkinMenuBitmaps,m_pSharedMenuIcons->GetNext(pos));
			if(pMenuIcon)
			{
				if(m_bDynIcons)
				{
					nIndex = pMenuIcon->Add((HICON)(INT_PTR)nID);
				}
				else
				{
					nIndex = pMenuIcon->Add(nID,m_bitmapBackground);
				}
				if(nIndex!=-1)
				{
					return pMenuIcon;
				}
			}
		}
	}
	else
	{
		m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CSkinMenuIcons*>;
	}
	CSkinMenuBitmaps* pMenuIcon = new CSkinMenuBitmaps();
	pMenuIcon->m_crTransparent = m_bitmapBackground;
	nIndex = pMenuIcon->Add(nID,m_bitmapBackground);
	if(nIndex!=-1)
	{
		m_pSharedMenuIcons->AddTail(pMenuIcon);
		return pMenuIcon;
	}
	delete pMenuIcon;
	return NULL;
}

CSkinMenuIcons* CSkinMenu::GetMenuIcon(int &nIndex, CBitmap* pBmp)
{
	if(pBmp==NULL)
	{
		nIndex=-1;
		return NULL;
	}

	if(m_pSharedMenuIcons!=NULL)
	{
		POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
		while(pos)
		{
			CSkinMenuBitmaps* pMenuIcon = DYNAMIC_DOWNCAST(CSkinMenuBitmaps,m_pSharedMenuIcons->GetNext(pos));
			if(pMenuIcon)
			{
				nIndex = pMenuIcon->Add(pBmp,m_bitmapBackground);
				if(nIndex!=-1)
				{
					return pMenuIcon;
				}
			}
		}
	}
	else
	{
		m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CSkinMenuIcons*>;
	}
	CSkinMenuBitmaps* pMenuIcon = new CSkinMenuBitmaps();
	pMenuIcon->m_crTransparent = m_bitmapBackground;
	nIndex = pMenuIcon->Add(pBmp,m_bitmapBackground);
	if(nIndex!=-1)
	{
		m_pSharedMenuIcons->AddTail(pMenuIcon);
		return pMenuIcon;
	}
	delete pMenuIcon;
	return NULL;
}


CSkinMenuIcons* CSkinMenu::GetToolbarIcons(UINT nToolBar, HMODULE hInst)
{
	ASSERT_VALID(this);
	ASSERT(nToolBar != NULL);

	if(m_pSharedMenuIcons!=NULL)
	{
		POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
		while(pos)
		{
			CSkinMenuIcons* pMenuIcon = m_pSharedMenuIcons->GetNext(pos);
			if(pMenuIcon->DoMatch(MAKEINTRESOURCE(nToolBar),hInst))
			{
				return pMenuIcon;
			}
		}
	}
	else
	{
		m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CSkinMenuIcons*>;
	}
	CSkinMenuIcons* pMenuIcon = new CSkinMenuIcons();
	pMenuIcon->m_crTransparent = m_bitmapBackground;
	if(pMenuIcon->LoadToolBar(MAKEINTRESOURCE(nToolBar),hInst))
	{
		m_pSharedMenuIcons->AddTail(pMenuIcon);
		return pMenuIcon;
	}
	delete pMenuIcon;
	return NULL;
}


BOOL CSkinMenu::LoadToolBar(LPCTSTR lpszResourceName, HMODULE hInst)
{
	CSkinMenuIcons* pMenuIcon = GetToolbarIcons((UINT)(UINT_PTR)lpszResourceName,hInst);
	if(pMenuIcon)
	{
		SetMenuIcons(pMenuIcon);
		return TRUE;
	}
	return FALSE;
}

BOOL CSkinMenu::LoadToolBar(HBITMAP hBitmap, CSize size, UINT* pID, COLORREF crTransparent)
{
	ASSERT_VALID(this);
	ASSERT(pID);

	if(crTransparent==CLR_NONE)
	{
		crTransparent = m_bitmapBackground;
	}
	if(m_pSharedMenuIcons!=NULL)
	{
		POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
		while(pos)
		{
			CSkinMenuIcons* pMenuIcon = m_pSharedMenuIcons->GetNext(pos);
			if(pMenuIcon->DoMatch(hBitmap,size,pID))
			{
				SetMenuIcons(pMenuIcon);
				return TRUE;
			}
		}
	}
	else
	{
		m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CSkinMenuIcons*>;
	}
	CSkinMenuIcons* pMenuIcon = new CSkinMenuIcons();
	if(pMenuIcon->LoadToolBar(hBitmap,size,pID,crTransparent))
	{
		m_pSharedMenuIcons->AddTail(pMenuIcon);
		SetMenuIcons(pMenuIcon);
		return TRUE;
	}
	delete pMenuIcon;
	return FALSE;
}

BOOL CSkinMenu::LoadToolBar(WORD* pToolInfo, COLORREF crTransparent)
{
	ASSERT_VALID(this);
	ASSERT(pToolInfo);

	if(crTransparent==CLR_NONE)
	{
		crTransparent = m_bitmapBackground;
	}

	if(m_pSharedMenuIcons!=NULL)
	{
		POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
		while(pos)
		{
			CSkinMenuIcons* pMenuIcon = m_pSharedMenuIcons->GetNext(pos);
			if(pMenuIcon->DoMatch(pToolInfo,crTransparent))
			{
				SetMenuIcons(pMenuIcon);
				return TRUE;
			}
		}
	}
	else
	{
		m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CSkinMenuIcons*>;
	}
	CSkinMenuIcons* pMenuIcon = new CSkinMenuIcons();
	if(pMenuIcon->LoadToolBar(pToolInfo,crTransparent))
	{
		m_pSharedMenuIcons->AddTail(pMenuIcon);
		SetMenuIcons(pMenuIcon);
		return TRUE;
	}
	delete pMenuIcon;
	return FALSE;
}

// added this function as a helper to LoadToolBar(WORD* pToolInfo, COLORREF crTransparent), the purpose of this function
// is to easily load a high color toolbar to the menu, instead of creating and maintaining a command map.  this function
// simply reads an existing 16 bit toolbar, and builds the word map based on that toolbar, using the 256 color bitmap.
BOOL CSkinMenu::LoadToolBar(UINT n16ToolBarID, UINT n256BitmapID, COLORREF transparentColor, HMODULE hInst)
{
	BOOL bRet = FALSE;
	// determine location of the bitmap in resource
	if(hInst==0)
	{
		hInst = AfxFindResourceHandle(MAKEINTRESOURCE(n16ToolBarID), RT_TOOLBAR);
	}
	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(n16ToolBarID), RT_TOOLBAR);

	if (hRsrc == NULL)
	{ // Special purpose when you try to load it from a dll 30.05.2002
		if(AfxGetResourceHandle()!=hInst)
		{
			hInst = AfxGetResourceHandle();
			hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(n16ToolBarID), RT_TOOLBAR);
		}
		if (hRsrc == NULL)
		{
			return FALSE;
		}
	}

	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	if (hGlobal)
	{
		CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
		if (pData)
		{
			int nSize = sizeof(WORD)*(pData->wItemCount+4);
			// no need for delete
			WORD* pToolId = (WORD*)_alloca(nSize);
			// sets also the last entry to zero
			ZeroMemory(pToolId,nSize);

			pToolId[0] = (WORD)n256BitmapID;
			pToolId[1] = pData->wWidth;
			pToolId[2] = pData->wHeight;

			WORD* pTemp = pToolId+3;
			for (int nIndex = 0; nIndex < pData->wItemCount; nIndex++)
			{ // not a seperator?
				if( (pData->items()[nIndex]) )
				{
					*pTemp++ = pData->items()[nIndex];
				}
			}
			// load the toolbar images into the menu
			bRet = LoadToolBar(pToolId, transparentColor);
			UnlockResource(hGlobal);
		}
		FreeResource(hGlobal);
	}
	// return TRUE for success, FALSE for failure
	return (bRet);
} // LoadHiColor


BOOL CSkinMenu::LoadToolBar(UINT nToolBar, HMODULE hInst)
{
	return LoadToolBar((LPCTSTR)(UINT_PTR)nToolBar,hInst);
}

BOOL CSkinMenu::LoadFromToolBar(UINT nID, UINT nToolBar, int& xoffset)
{
	int xset,offset;
	UINT nStyle;
	BOOL returnflag=FALSE;
	CToolBar bar;

	CWnd* pWnd = AfxGetMainWnd();
	if (pWnd == NULL)
		pWnd = CWnd::GetDesktopWindow();
	bar.Create(pWnd);

	if(bar.LoadToolBar(nToolBar))
	{
		offset=bar.CommandToIndex(nID);
		if(offset>=0)
		{
			bar.GetButtonInfo(offset,nID,nStyle,xset);
			if(xset>0) xoffset = xset;
			returnflag=TRUE;
		}
	}
	return returnflag;
}

// O.S.
CSkinMenuItemData* CSkinMenu::FindMenuItem(UINT nID)
{
	CSkinMenuItemData *pData = NULL;
	int i;

	for(i = 0; i < m_MenuItemList.GetSize(); i++)
	{
		if (m_MenuItemList[i]->m_nID == nID)
		{
			pData = m_MenuItemList[i];
			break;
		}
	}
	if (!pData)
	{
		int loc;
		CSkinMenu *pMenu = FindMenuOption(nID, loc);
		ASSERT(pMenu != this);
		if (loc >= 0)
		{
			return pMenu->FindMenuItem(nID);
		}
	}
	return pData;
}


CSkinMenu* CSkinMenu::FindAnotherMenuOption(int nId, int& nLoc,
											CArray<CSkinMenu*,CSkinMenu*>&newSubs,
											CArray<int,int&>&newLocs)
{
	int i,numsubs,j;
	CSkinMenu *pSubMenu,*pgoodmenu;
	BOOL foundflag;

	for(i=0;i<(int)(GetMenuItemCount());++i)
	{
		pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,GetSubMenu(i));
		if(pSubMenu)
		{
			pgoodmenu = pSubMenu->FindAnotherMenuOption(nId,nLoc,newSubs,newLocs);
			if(pgoodmenu)
			{
				return pgoodmenu;
			}
		}
		else if(nId==(int)GetMenuItemID(i))
		{
			numsubs = (int)newSubs.GetSize();
			foundflag = TRUE;
			for(j=0;j<numsubs;++j)
			{
				if(newSubs[j]==this && newLocs[j]==i)
				{
					foundflag = FALSE;
					break;
				}
			}
			if(foundflag)
			{
				nLoc = i;
				return this;
			}
		}
	}
	nLoc = -1;

	return NULL;
}

CSkinMenu* CSkinMenu::FindMenuOption(int nId, int& nLoc)
{
	int i;
	CSkinMenu *pSubMenu,*pgoodmenu;

	for(i=0;i<(int)(GetMenuItemCount());++i)
	{
		pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,GetSubMenu(i));
		if(pSubMenu)
		{
			pgoodmenu = pSubMenu->FindMenuOption(nId,nLoc);
			if(pgoodmenu)
			{
				return pgoodmenu;
			}
		}
		else if(nId==(int)GetMenuItemID(i))
		{
			nLoc = i;
			return(this);
		}
	}
	nLoc = -1;
	return NULL;
}

CSkinMenu* CSkinMenu::FindMenuOption(LPCTSTR lpstrText, int& nLoc)
{
	int i;
	// First look for all item text.
	for(i=0;i<(int)m_MenuItemList.GetSize();++i)
	{
		if(m_MenuItemList[i]->m_szMenuText.Compare(lpstrText)==NULL)
		{
			nLoc = i;
			return this;
		}
	}
	CSkinMenu* pSubMenu;
	// next, look in all submenus
	for(i=0; i<(int)(GetMenuItemCount());++i)
	{
		pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,GetSubMenu(i));
		if(pSubMenu)
		{
			pSubMenu = pSubMenu->FindMenuOption(lpstrText,nLoc);
			if(pSubMenu)
			{
				return pSubMenu;
			}
		}
	}
	nLoc = -1;
	return NULL;
}

BOOL CSkinMenu::LoadMenu(HMENU hMenu)
{
	if(!::IsMenu(hMenu) || !Attach(hMenu))
	{
		return FALSE;
	}
	m_bIsPopupMenu = FALSE;
	for(int i=0;i<(int)(GetMenuItemCount());++i)
	{
		HMENU hSubMenu = ::GetSubMenu(m_hMenu,i);
		if(hSubMenu)
		{
			CSkinMenu* pMenu = new CSkinMenu(m_hMenu);
			m_SubMenus.Add(hSubMenu);
			pMenu->LoadMenu(hSubMenu);
			pMenu->m_bIsPopupMenu = TRUE;
		}
	}
	SynchronizeMenu();
	return TRUE;
}

BOOL CSkinMenu::LoadMenu(int nResource)
{
	return(CSkinMenu::LoadMenu(MAKEINTRESOURCE(nResource)));
}

BOOL CSkinMenu::LoadMenu(LPCTSTR lpszResourceName)
{
	ASSERT(this);
	HMENU hMenu = ::LoadMenu(AfxFindResourceHandle(lpszResourceName,RT_MENU), lpszResourceName);
#ifdef _DEBUG
	ShowLastError(_T("Error from Menu: LoadMenu"));
#endif
	return LoadMenu(hMenu);
}

BOOL CSkinMenu::SetItemData(UINT uiId, DWORD_PTR dwItemData, BOOL fByPos)
{
	MENUITEMINFO MenuItemInfo = {0};
	MenuItemInfo.cbSize = sizeof(MenuItemInfo);
	MenuItemInfo.fMask = MIIM_DATA;
	if(::GetMenuItemInfo(m_hMenu,uiId,fByPos,&MenuItemInfo))
	{
		CSkinMenuItemData* pItem = CheckMenuItemData(MenuItemInfo.dwItemData);
		if(pItem)
		{
			pItem->m_pData = (void*)dwItemData;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CSkinMenu::SetItemDataPtr(UINT uiId, void* pItemData, BOOL fByPos )
{
	return SetItemData(uiId, (DWORD_PTR) pItemData, fByPos);
}

DWORD_PTR CSkinMenu::GetItemData(UINT uiId, BOOL fByPos) const
{
	MENUITEMINFO MenuItemInfo = {0};
	MenuItemInfo.cbSize = sizeof(MenuItemInfo);
	MenuItemInfo.fMask = MIIM_DATA;
	if(::GetMenuItemInfo(m_hMenu,uiId,fByPos,&MenuItemInfo))
	{
		CSkinMenuItemData* pItem = CheckMenuItemData(MenuItemInfo.dwItemData);
		if(pItem)
		{
			return (DWORD_PTR)pItem->m_pData;
		}
	}
	return DWORD_PTR(-1);
}

void* CSkinMenu::GetItemDataPtr(UINT uiId, BOOL fByPos) const
{
	return (void*)GetItemData(uiId,fByPos);
}

BOOL CSkinMenu::SetMenuData(DWORD_PTR dwMenuData)
{
	m_pData = (void*)dwMenuData;
	return TRUE;
}

BOOL CSkinMenu::SetMenuDataPtr(void* pMenuData)
{
	m_pData = (void*)pMenuData;
	return TRUE;
}

DWORD_PTR CSkinMenu::GetMenuData() const
{
	return (DWORD_PTR)m_pData;
}

void* CSkinMenu::GetMenuDataPtr() const
{
	return m_pData;
}

BOOL CSkinMenu::m_bDrawAccelerators = TRUE;

BOOL CSkinMenu::SetAcceleratorsDraw (BOOL bDraw)
{
	BOOL bOld = m_bDrawAccelerators;
	m_bDrawAccelerators = bDraw;
	return bOld;
}
BOOL CSkinMenu::GetAcceleratorsDraw()
{
	return m_bDrawAccelerators;
}

BYTE CSkinMenu::m_bAlpha = 255;

BYTE CSkinMenu::SetAlpha(BYTE bAlpha)
{
	BYTE oldAlpha = m_bAlpha;
	m_bAlpha = bAlpha;
	return oldAlpha;
}

BYTE CSkinMenu::GetAlpha()
{
	return m_bAlpha;
}

// INVALID_HANDLE_VALUE = Draw default frame's accel. NULL = Off
HACCEL  CSkinMenu::SetAccelerator (HACCEL hAccel)
{
	HACCEL hOld = m_hAccelToDraw;
	m_hAccelToDraw = hAccel;
	return hOld;
}

HACCEL  CSkinMenu::GetAccelerator ()
{
	return m_hAccelToDraw;
}

void CSkinMenu::LoadCheckmarkBitmap(int unselect, int select)
{
	if(unselect>0 && select>0)
	{
		m_selectcheck = select;
		m_unselectcheck = unselect;
		if(m_checkmaps)
			m_checkmaps->DeleteImageList();
		else
			m_checkmaps = new CImageList();

		m_checkmaps->Create(m_iconX,m_iconY,ILC_MASK,2,1);
		BOOL flag1 = AddBitmapToImageList(m_checkmaps,unselect);
		BOOL flag2 = AddBitmapToImageList(m_checkmaps,select);

		if(!flag1||!flag2)
		{
			m_checkmaps->DeleteImageList();
			delete m_checkmaps;
			m_checkmaps = NULL;
		}
	}
}

BOOL CSkinMenu::GetMenuText(UINT id, CString& string, UINT nFlags/*= MF_BYPOSITION*/)
{
	if(MF_BYPOSITION&nFlags)
	{
		UINT numMenuItems = (int)m_MenuItemList.GetSize();
		if(id<numMenuItems)
		{
			string = m_MenuItemList[id]->GetString(m_bDrawAccelerators ? m_hAccelToDraw : NULL);
			return TRUE;
		}
	}
	else
	{
		int uiLoc;
		CSkinMenu* pMenu = FindMenuOption(id,uiLoc);
		if(NULL!=pMenu)
		{
			return pMenu->GetMenuText(uiLoc,string);
		}
	}
	return FALSE;
}

CSkinMenuItemData* CSkinMenu::CheckMenuItemData(ULONG_PTR nItemData) const
{
	for(int i=0;i<m_MenuItemList.GetSize();++i)
	{
		CSkinMenuItemData* pItem = m_MenuItemList[i];
		if ( ((ULONG_PTR)pItem)==nItemData )
		{
			return pItem;
		}
	}
	return NULL;
}


CSkinMenuItemData* CSkinMenu::FindMenuList(UINT nID)
{
	for(int i=0;i<m_MenuItemList.GetSize();++i)
	{
		CSkinMenuItemData* pMenuItem = m_MenuItemList[i];
		if(pMenuItem->m_nID==nID && !pMenuItem->m_nSyncFlag)
		{
			pMenuItem->m_nSyncFlag = 1;
			return pMenuItem;
		}
	}
	return NULL;
}

void CSkinMenu::InitializeMenuList(int value)
{
	for(int i=0;i<m_MenuItemList.GetSize();++i)
	{
		m_MenuItemList[i]->m_nSyncFlag = value;
	}
}

void CSkinMenu::DeleteMenuList()
{
	for(int i=0;i<m_MenuItemList.GetSize();++i)
	{
		if(!m_MenuItemList[i]->m_nSyncFlag)
		{
			delete m_MenuItemList[i];
		}
	}
}

void CSkinMenu::SynchronizeMenu()
{
	CTypedPtrArray<CPtrArray, CSkinMenuItemData*> temp;
	CSkinMenuItemData *pItemData;
	CString string;
	UINT submenu,state,j;

	InitializeMenuList(0);
	for(j=0;j<GetMenuItemCount();++j)
	{
		MENUITEMINFO menuInfo = {0};
		menuInfo.cbSize = sizeof(menuInfo);
		// we get a wrong state for seperators
		menuInfo.fMask = MIIM_TYPE|MIIM_ID|MIIM_STATE;
		// item doesn't exist
		if(!GetMenuItemInfo(j,&menuInfo,TRUE))
		{
			break;
		}
		state = GetMenuState(j,MF_BYPOSITION);
		if(state!=menuInfo.fState)
		{
			state|=0;
		}
		pItemData=NULL;
		if(state==UINT_PTR(-1))
		{
			break;
		}
		if(!(state&MF_SYSMENU))
		{
			if(menuInfo.fType&MFT_RIGHTJUSTIFY)
			{
				state |= MF_RIGHTJUSTIFY;
			}
			// MFT_RIGHTORDER is the same value as MFT_SYSMENU.
			// We distinguish between the two by also looking for MFT_BITMAP.
			if(!(state&MF_BITMAP) && (menuInfo.fType&MFT_RIGHTORDER) )
			{
				state |= MFT_RIGHTORDER;
			}
		}

		// Special purpose for Windows NT 4.0
		if(state&MF_BITMAP)
		{
			// Bitmap-button like system menu, maximize, minimize and close
			// just ignore.
			UINT nID = GetMenuItemID(j);
			pItemData = FindMenuList(nID);
			if(!pItemData)
			{
				pItemData = new CSkinMenuItemData;
				pItemData->m_nFlags = state;
				pItemData->m_nID = nID;
			}
		}
		else if(state&MF_POPUP)
		{
			HMENU hSubMenu = GetSubMenu(j)->m_hMenu;
			submenu = (UINT)hSubMenu;
			pItemData = FindMenuList(submenu);
			GetMenuString(j,string,MF_BYPOSITION);

			if(!pItemData)
			{
				state &= ~(MF_USECHECKBITMAPS|MF_SEPARATOR);
				pItemData = NewODMenu(j,state|MF_BYPOSITION|MF_POPUP|MF_OWNERDRAW,submenu,string);
			}
			else if(!string.IsEmpty ())
			{
				pItemData->SetString(string);
			}

			CSkinMenu* pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(hSubMenu));
			if(pSubMenu && pSubMenu->m_hParentMenu!=m_hMenu)
			{ // Sets again the parent to this one
				pSubMenu->m_hParentMenu = m_hMenu;
			}
		}
		else if(state&MF_SEPARATOR)
		{
			pItemData = FindMenuList(0);
			if(!pItemData)
			{
				pItemData = NewODMenu(j,state|MF_BYPOSITION|MF_OWNERDRAW,0,_T(""));
			}
			else
			{
				pItemData->m_nFlags = state|MF_BYPOSITION|MF_OWNERDRAW;
				ModifyMenu(j,pItemData->m_nFlags,0,(LPCTSTR)pItemData);
			}
		}
		else
		{
			UINT nID = GetMenuItemID(j);
			pItemData = FindMenuList(nID);
			GetMenuString(j,string,MF_BYPOSITION);

			if(!pItemData)
			{
				pItemData = NewODMenu(j,state|MF_BYPOSITION|MF_OWNERDRAW,nID,string);
			}
			else
			{
				pItemData->m_nFlags = state|MF_BYPOSITION|MF_OWNERDRAW;
				if(string.GetLength()>0)
					pItemData->SetString(string);
	
				ModifyMenu(j,pItemData->m_nFlags,nID,(LPCTSTR)pItemData);
			}
		}
		if(pItemData)
			temp.Add(pItemData);
	}
	DeleteMenuList();
	m_MenuItemList.RemoveAll();
	m_MenuItemList.Append(temp);
	temp.RemoveAll();
}

void CSkinMenu::OnInitMenuPopup(HWND hWnd, CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	UNREFERENCED_PARAMETER(nIndex);
	UNREFERENCED_PARAMETER(bSysMenu);

	CSkinMenuHook::m_hLastMenu = pPopupMenu->m_hMenu;

	if(IsMenu(pPopupMenu->m_hMenu))
	{
		CSkinMenu* pSubMenu = DYNAMIC_DOWNCAST(CSkinMenu,pPopupMenu);
		if(pSubMenu)
		{
			pSubMenu->m_hTempOwner = hWnd;
			pSubMenu->OnInitMenuPopup();
			HMENU hMenu = pSubMenu->GetParent();
			CSkinMenu* pParent = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(hMenu));
			if(pParent)
			{
				pParent->m_dwOpenMenu += 1;
				if(pParent->m_dwOpenMenu==1 && !pParent->m_bIsPopupMenu)
				{
					// Redraw the menubar for the shade
					CRect rect = pParent->GetLastActiveMenuRect();
					if(!rect.IsRectEmpty())
					{
						rect.InflateRect(0,0,10,10);
						CPoint Point(0,0);
						ClientToScreen(hWnd,&Point);
						rect.OffsetRect(-Point);
						RedrawWindow(hWnd,rect,0,RDW_FRAME|RDW_INVALIDATE);
					}
				}
			}
		}
	}
}

BOOL CSkinMenu::Replace(UINT nID, UINT nNewID)
{
	int nLoc=0;
	CSkinMenu* pTempMenu = FindMenuOption(nID,nLoc);
	if(pTempMenu && nLoc >= 0)
	{
		CSkinMenuItemData* pData = pTempMenu->m_MenuItemList[nLoc];
		UINT nFlags = pData->m_nFlags|MF_OWNERDRAW|MF_BYPOSITION;
		pData->m_nID = nNewID;
		return pTempMenu->ModifyMenu(nLoc,nFlags,nNewID,(LPCTSTR)pData);
	}
	return FALSE;
}

void CSkinMenu::OnInitMenuPopup()
{
	m_bIsPopupMenu = true;
	SynchronizeMenu();
	// Special purpose for windows XP with themes!!!
	if(SystemVersion()->IsWinXPOrGreater())
	{
		Replace(SC_RESTORE,SC_RESTORE+1);
		Replace(SC_CLOSE,SC_CLOSE+1);
		Replace(SC_MINIMIZE,SC_MINIMIZE+1);
	}
}

BOOL CSkinMenu::OnUnInitPopupMenu()
{
	if(SystemVersion()->IsWinXPOrGreater())
	{
		// Special purpose for windows XP with themes!!!
		// Restore old values otherwise you have disabled windowbuttons
		Replace(SC_MINIMIZE+1,SC_MINIMIZE);
		Replace(SC_RESTORE+1,SC_RESTORE);
		if(Replace(SC_CLOSE+1,SC_CLOSE))
		{
			//EnableMenuItem(SC_CLOSE, MF_BYCOMMAND|MF_ENABLED);
			SetWindowPos(m_hTempOwner,0,0,0,0,0,SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
		}
		//Replace(SC_RESTORE+1,SC_RESTORE);
		//Replace(SC_MINIMIZE+1,SC_MINIMIZE);
	}

	HMENU hMenu = GetParent();
	CSkinMenu* pParent = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(hMenu));
	if(pParent)
	{
		pParent->m_dwOpenMenu -= 1;
		if(pParent->m_dwOpenMenu>=NULL && !pParent->m_bIsPopupMenu)
		{
			pParent->m_dwOpenMenu = 0;
			// Redraw the menubar for the shade
			CRect rect = pParent->GetLastActiveMenuRect();
			if(!rect.IsRectEmpty())
			{
				rect.InflateRect(0,0,10,10);
				CPoint Point(0,0);
				ClientToScreen(m_hTempOwner,&Point);
				rect.OffsetRect(-Point);
				RedrawWindow(m_hTempOwner,rect,0,RDW_FRAME|RDW_INVALIDATE);
			}
			return TRUE;
		}
	}
	return FALSE;
}

LRESULT CSkinMenu::FindKeyboardShortcut(UINT nChar, UINT nFlags, CMenu* pMenu)
{
	UNREFERENCED_PARAMETER(nFlags);

	CSkinMenu* pNewMenu = DYNAMIC_DOWNCAST(CSkinMenu,pMenu);
	if(pNewMenu)
	{
		//SK: modified for Unicode correctness
		CString key(_T('&'),2);
		key.SetAt(1,(TCHAR)nChar);
		key.MakeLower();
		CString menutext;
		int menusize = (int)pNewMenu->GetMenuItemCount();
		if(menusize!=(pNewMenu->m_MenuItemList.GetSize()))
			pNewMenu->SynchronizeMenu();

		for(int i=0;i<menusize;++i)
		{
			if(pNewMenu->GetMenuText(i,menutext))
			{
				menutext.MakeLower();
				if(menutext.Find(key)>=0)
				{
					return(MAKELRESULT(i,2));
				}
			}
		}
	}
	return NULL;
}

BOOL CSkinMenu::AddBitmapToImageList(CImageList* bmplist,UINT nResourceID)
{
	// O.S.
	if (m_bDynIcons)
	{
		bmplist->Add((HICON)(UINT_PTR)nResourceID);
		return TRUE;
	}

	CBitmap mybmp;
	HBITMAP hbmp = LoadSysColorBitmap(nResourceID);
	if(hbmp)
		// Object will be destroyd by destructor of CBitmap
		mybmp.Attach(hbmp);
	else
		mybmp.LoadBitmap(nResourceID);


	if (mybmp.m_hObject && bmplist->Add(&mybmp,GetBitmapBackground())>=0 )
		return TRUE;

	return FALSE;
}

COLORREF CSkinMenu::SetBitmapBackground(COLORREF newColor)
{
	COLORREF oldColor = m_bitmapBackground;
	m_bitmapBackground = newColor;
	return oldColor;
}

COLORREF CSkinMenu::GetBitmapBackground()
{
	if(m_bitmapBackground==CLR_DEFAULT)
		return GetSysColor(COLOR_3DFACE);

	return m_bitmapBackground;
}

HBITMAP CSkinMenu::LoadSysColorBitmap(int nResourceId)
{
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(nResourceId),RT_BITMAP);
	HRSRC hRsrc = ::FindResource(hInst,MAKEINTRESOURCE(nResourceId),RT_BITMAP);
	if (hRsrc == NULL)
		return NULL;

	// determine how many colors in the bitmap
	HGLOBAL hglb;
	if ((hglb = LoadResource(hInst, hRsrc)) == NULL)
		return NULL;

	LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)LockResource(hglb);
	if (lpBitmap == NULL)
	{
		return NULL;
	}
	WORD numcol = NumBitmapColors(lpBitmap);
	::FreeResource(hglb);

	if(numcol!=16)
		return(NULL);

	return AfxLoadSysColorBitmap(hInst, hRsrc, FALSE);
}

// sPos means Seperator's position, since we have no way to find the
// seperator's position in the menu we have to specify them when we call the
// RemoveMenu to make sure the unused seperators are removed;
// sPos  = None no seperator removal;
//       = Head  seperator in front of this menu item;
//       = Tail  seperator right after this menu item;
//       = Both  seperators at both ends;
// remove the menu item based on their text, return -1 if not found, otherwise
// return the menu position;
int CSkinMenu::RemoveMenu(LPCTSTR pText, ESeperator sPos)
{
	int nPos = GetMenuPosition(pText);
	if(nPos != -1)
	{
		switch (sPos)
		{
		case CSkinMenu::NONE:
			RemoveMenu(nPos, MF_BYPOSITION);
			break;

		case CSkinMenu::HEAD:
			ASSERT(nPos - 1 >= 0);
			RemoveMenu(nPos-1, MF_BYPOSITION);
			break;

		case CSkinMenu::TAIL:
			RemoveMenu(nPos+1, MF_BYPOSITION);
			break;

		case CSkinMenu::BOTH:
			// remove the end first;
			RemoveMenu(nPos+1, MF_BYPOSITION);
			// remove the head;
			ASSERT(nPos - 1 >= 0);
			RemoveMenu(nPos-1, MF_BYPOSITION);
			break;
		}
	}
	return nPos;
}

BOOL CSkinMenu::RemoveMenu(UINT uiId, UINT nFlags)
{
	if(MF_BYPOSITION&nFlags)
	{
		UINT nItemState = GetMenuState(uiId,MF_BYPOSITION);
		if((nItemState&MF_SEPARATOR) && !(nItemState&MF_POPUP))
		{
			CSkinMenuItemData* pData =  m_MenuItemList.GetAt(uiId);
			m_MenuItemList.RemoveAt(uiId);
			delete pData;
		}
		else
		{
			CMenu* pSubMenu = GetSubMenu(uiId);
			if(NULL==pSubMenu)
			{
				UINT uiCommandId = GetMenuItemID(uiId);
				for(int i=0;i<m_MenuItemList.GetSize(); i++)
				{
					if(m_MenuItemList[i]->m_nID==uiCommandId)
					{
						CSkinMenuItemData* pData = m_MenuItemList.GetAt(i);
						m_MenuItemList.RemoveAt(i);
						delete pData;
						break;
					}
				}
			}
			else
			{
				// Only remove the menu.
				int numSubMenus = (int)m_SubMenus.GetSize();
				while(numSubMenus--)
				{
					if(m_SubMenus[numSubMenus]==pSubMenu->m_hMenu)
					{
						m_SubMenus.RemoveAt(numSubMenus);
					}
				}
				numSubMenus = (int)m_MenuItemList.GetSize();
				while(numSubMenus--)
				{
					if(m_MenuItemList[numSubMenus]->m_nID==(UINT)pSubMenu->m_hMenu )
					{
						CSkinMenuItemData* pData = m_MenuItemList.GetAt(numSubMenus);
						m_MenuItemList.RemoveAt(numSubMenus);
						delete pData;
						break;
					}
				}
				// Don't delete it's only remove
				//delete pSubMenu;
			}
		}
	}
	else
	{
		int iPosition =0;
		CSkinMenu* pMenu = FindMenuOption(uiId,iPosition);
		if(pMenu)
			return pMenu->RemoveMenu(iPosition,MF_BYPOSITION);
	}
	return CMenu::RemoveMenu(uiId,nFlags);
}

BOOL CSkinMenu::DeleteMenu(UINT uiId, UINT nFlags)
{
	if(MF_BYPOSITION&nFlags)
	{
		UINT nItemState = GetMenuState(uiId,MF_BYPOSITION);
		if( (nItemState&MF_SEPARATOR) && !(nItemState&MF_POPUP))
		{
			CSkinMenuItemData* pData = m_MenuItemList.GetAt(uiId);
			m_MenuItemList.RemoveAt(uiId);
			delete pData;
		}
		else
		{
			CMenu* pSubMenu = GetSubMenu(uiId);
			if(NULL==pSubMenu)
			{
				UINT uiCommandId = GetMenuItemID(uiId);
				for(int i=0;i<m_MenuItemList.GetSize(); i++)
				{
					if(m_MenuItemList[i]->m_nID==uiCommandId)
					{
						CSkinMenuItemData* pData = m_MenuItemList.GetAt(i);
						m_MenuItemList.RemoveAt(i);
						delete pData;
					}
				}
			}
			else
			{
				BOOL bCanDelete = FALSE;
				int numSubMenus = (int)m_SubMenus.GetSize();
				while(numSubMenus--)
				{
					if(m_SubMenus[numSubMenus]==pSubMenu->m_hMenu)
					{
						m_SubMenus.RemoveAt(numSubMenus);
						bCanDelete = TRUE;
					}
				}

				numSubMenus = (int)m_MenuItemList.GetSize();
				while(numSubMenus--)
				{
					if(m_MenuItemList[numSubMenus]->m_nID==(UINT)pSubMenu->m_hMenu )
					{
						CSkinMenuItemData* pData = m_MenuItemList.GetAt(numSubMenus);
						m_MenuItemList.RemoveAt(numSubMenus);
						delete pData;
						break;
					}
				}
				// Did we created the menu
				if(bCanDelete)
				{ // Oh yes so we can destroy it
					delete pSubMenu;
				}
			}
		}
	}
	else
	{
		int iPosition =0;
		CSkinMenu* pMenu = FindMenuOption(uiId,iPosition);
		if(pMenu)
			return pMenu->DeleteMenu(iPosition,MF_BYPOSITION);
	}
	return CMenu::DeleteMenu(uiId,nFlags);
}

BOOL CSkinMenu::AppendMenu(UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, int nIconNormal)
{
	return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,nIconNormal);
}

BOOL CSkinMenu::AppendMenu(UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, CImageList* il, int xoffset)
{
	return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,il,xoffset);
}

BOOL CSkinMenu::AppendMenu(UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, CBitmap* bmp)
{
	return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,bmp);
}

BOOL CSkinMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, int nIconNormal)
{
	return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,nIconNormal);
}

BOOL CSkinMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, CImageList* il, int xoffset)
{
	return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,il,xoffset);
}

BOOL CSkinMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, CBitmap* bmp)
{
	return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,bmp);
}

CSkinMenu* CSkinMenu::AppendODPopupMenu(LPCTSTR lpstrText)
{
	CSkinMenu* pSubMenu = new CSkinMenu(m_hMenu);
	pSubMenu->m_unselectcheck=m_unselectcheck;
	pSubMenu->m_selectcheck=m_selectcheck;
	pSubMenu->m_checkmaps=m_checkmaps;
	pSubMenu->m_checkmapsshare=TRUE;
	pSubMenu->CreatePopupMenu();
	if(AppendODMenu(lpstrText,MF_POPUP,(UINT)pSubMenu->m_hMenu, -1))
	{
		m_SubMenus.Add(pSubMenu->m_hMenu);
		return pSubMenu;
	}
	delete pSubMenu;
	return NULL;
}

CMenu* CSkinMenu::GetSubMenu(int nPos) const
{
	return CMenu::GetSubMenu (nPos);
}

CMenu* CSkinMenu::GetSubMenu(LPCTSTR lpszSubMenuName) const
{
	int num = GetMenuItemCount ();
	CString name;
	MENUITEMINFO info = {0};

	for (int i=0; i<num; i++)
	{
		GetMenuString (i, name, MF_BYPOSITION);
		// fix from George Menhorn
		if(name.IsEmpty())
		{
			info.cbSize = sizeof (MENUITEMINFO);
			info.fMask = MIIM_DATA;
			::GetMenuItemInfo(m_hMenu, i, TRUE, &info);

			CSkinMenuItemData* pItemData = CheckMenuItemData(info.dwItemData);
			if (pItemData)
				name = pItemData->GetString(m_bDrawAccelerators ? m_hAccelToDraw : NULL);
		}

		if (name.Compare (lpszSubMenuName) == 0)
			return CMenu::GetSubMenu (i);

	}
	return NULL;
}

// Tongzhe Cui, Functions to remove a popup menu based on its name. Seperators
// before and after the popup menu can also be removed if they exist.
int CSkinMenu::GetMenuPosition(LPCTSTR pText)
{
	for(int i=0;i<(int)(GetMenuItemCount());++i)
	{
		if(!GetSubMenu(i))
		{
			for(int j=0;j<m_MenuItemList.GetSize();++j)
			{
				if(m_MenuItemList[j]->m_szMenuText.Compare(pText)==NULL)
					return j;
			}
		}
	}
	// means no found;
	return -1;
}

BOOL CSkinMenu::RemoveMenuTitle()
{
	int numMenuItems = (int)m_MenuItemList.GetSize();

	// We need a seperator at the beginning of the menu
	if(!numMenuItems || !((m_MenuItemList[0]->m_nFlags)&MF_SEPARATOR) )
		return FALSE;

	CSkinMenuItemData* pMenuData = m_MenuItemList[0];
	// Check for title
	if(pMenuData->m_nTitleFlags&MFT_TITLE)
	{
		if(numMenuItems>0)
		{
			CSkinMenuItemData* pMenuNextData = m_MenuItemList[1];
			if((pMenuNextData->m_nFlags&MF_MENUBREAK))
			{
				pMenuNextData->m_nFlags &= ~MF_MENUBREAK;
				CMenu::ModifyMenu(1,MF_BYPOSITION|pMenuNextData->m_nFlags,pMenuNextData->m_nID,(LPCTSTR)pMenuNextData);
			}
		}
		// Now remove the title
		RemoveMenu(0,MF_BYPOSITION);
		return TRUE;
	}
	return FALSE;
}

BOOL CSkinMenu::SetMenuTitle(LPCTSTR pTitle, UINT nTitleFlags, int nIconNormal)
{
	int nIndex = -1;
	CSkinMenuIconLock iconLock(GetMenuIcon(nIndex,nIconNormal));
	return SetMenuTitle(pTitle,nTitleFlags,iconLock,nIndex);
}

BOOL CSkinMenu::SetMenuTitle(LPCTSTR pTitle, UINT nTitleFlags, CBitmap* pBmp)
{
	int nIndex = -1;
	CSkinMenuIconLock iconLock(GetMenuIcon(nIndex,pBmp));
	return SetMenuTitle(pTitle,nTitleFlags,iconLock,nIndex);
}

BOOL CSkinMenu::SetMenuTitle(LPCTSTR pTitle, UINT nTitleFlags, CImageList *pil, int xoffset)
{
	int nIndex = -1;
	CSkinMenuIconLock iconLock(GetMenuIcon(nIndex,0,pil,xoffset));
	return SetMenuTitle(pTitle,nTitleFlags,iconLock,nIndex);
}

BOOL CSkinMenu::SetMenuTitle(LPCTSTR pTitle, UINT nTitleFlags, CSkinMenuIcons* pIcons, int nIndex)
{
	return TRUE; // 不使用

	// Check if menu is valid
	if(!::IsMenu(m_hMenu))
		return FALSE;

	// Check the menu integrity
	if((int)GetMenuItemCount()!=(int)m_MenuItemList.GetSize())
		SynchronizeMenu();
	int numMenuItems = (int)m_MenuItemList.GetSize();
	// We need a seperator at the beginning of the menu
	if(!numMenuItems || !((m_MenuItemList[0]->m_nFlags)&MF_SEPARATOR) )
	{
		// We add the special menu item for title
		CSkinMenuItemData *pItemData = new CSkinMenuItemDataTitle;
		m_MenuItemList.InsertAt(0,pItemData);
		pItemData->SetString(pTitle);
		pItemData->m_nFlags = MF_BYPOSITION|MF_SEPARATOR|MF_OWNERDRAW;

		VERIFY(CMenu::InsertMenu(0,MF_SEPARATOR|MF_BYPOSITION,0,pItemData->m_szMenuText));
		VERIFY(CMenu::ModifyMenu(0, MF_BYPOSITION|MF_SEPARATOR|MF_OWNERDRAW, 0, (LPCTSTR)pItemData ));

		//InsertMenu(0,MF_SEPARATOR|MF_BYPOSITION);
	}

	numMenuItems = (int)m_MenuItemList.GetSize();
	if(numMenuItems)
	{
		CSkinMenuItemData* pMenuData = m_MenuItemList[0];
		if(pMenuData->m_nFlags&MF_SEPARATOR)
		{
			pIcons->AddRef();
			pMenuData->m_pMenuIcon->Release();
			pMenuData->m_pMenuIcon = pIcons;
			if(pIcons && nIndex>=0)
			{
				pMenuData->m_nMenuIconOffset = nIndex;
				//CSize size = pIcons->GetIconSize();
				//m_iconX = max(m_iconX,size.cx);
				//m_iconY = max(m_iconY,size.cy);
			}
			else
				pMenuData->m_nMenuIconOffset = -1;

			pMenuData->SetString(pTitle);
			pMenuData->m_nTitleFlags = nTitleFlags|MFT_TITLE;

			if(numMenuItems>1)
			{
				CSkinMenuItemData* pMenuData = m_MenuItemList[1];

				if(nTitleFlags&MFT_SIDE_TITLE)
				{
					if(!(pMenuData->m_nFlags&MF_MENUBREAK))
					{
						pMenuData->m_nFlags |= MF_MENUBREAK;
						CMenu::ModifyMenu(1,MF_BYPOSITION|pMenuData->m_nFlags,pMenuData->m_nID,(LPCTSTR)pMenuData);
					}
				}
				else
				{
					if((pMenuData->m_nFlags&MF_MENUBREAK))
					{
						pMenuData->m_nFlags &= ~MF_MENUBREAK;
						CMenu::ModifyMenu(1,MF_BYPOSITION|pMenuData->m_nFlags,pMenuData->m_nID,(LPCTSTR)pMenuData);
					}
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

CSkinMenuItemDataTitle* CSkinMenu::GetMemuItemDataTitle()
{
	// Check if menu is valid
	if(!this || !::IsMenu(m_hMenu))
		return NULL;

	// Check the menu integrity
	if((int)GetMenuItemCount()!=(int)m_MenuItemList.GetSize())
		SynchronizeMenu();

	if(m_MenuItemList.GetSize()>0)
		return DYNAMIC_DOWNCAST(CSkinMenuItemDataTitle,m_MenuItemList[0]);

	return NULL;
}


BOOL CSkinMenu::SetMenuTitleColor(COLORREF clrTitle, COLORREF clrLeft, COLORREF clrRight)
{
	CSkinMenuItemDataTitle* pItem = GetMemuItemDataTitle();
	if(pItem)
	{
		pItem->m_clrTitle = clrTitle;
		pItem->m_clrLeft = clrLeft;
		pItem->m_clrRight = clrRight;
		return TRUE;
	}
	return FALSE;
}

BOOL CSkinMenu::SetMenuText(UINT id, CString string, UINT nFlags/*= MF_BYPOSITION*/ )
{
	if(MF_BYPOSITION&nFlags)
	{
		int numMenuItems = (int)m_MenuItemList.GetSize();
		if(id<UINT(numMenuItems))
		{
			// get current menu state so it doesn't change
			UINT nState = GetMenuState(id, MF_BYPOSITION);
			nState &= ~(MF_BITMAP|MF_OWNERDRAW|MF_SEPARATOR);
			// change the menutext
			CSkinMenuItemData* pItemData = m_MenuItemList[id];
			pItemData->SetString(string);

			if(CMenu::ModifyMenu(id,MF_BYPOSITION|MF_STRING | nState, pItemData->m_nID, string))
			{
				return ModifyMenu(id,MF_BYPOSITION | MF_OWNERDRAW,pItemData->m_nID,(LPCTSTR)pItemData);
			}
		}
	}
	else
	{
		int uiLoc;
		CSkinMenu* pMenu = FindMenuOption(id,uiLoc);
		if(NULL!=pMenu)
			return pMenu->SetMenuText(uiLoc,string);
	}
	return FALSE;
}

// courtesy of Warren Stevens
void CSkinMenu::ColorBitmap(CDC* pDC, CBitmap& bmp, CSize size, COLORREF fill, COLORREF border, int hatchstyle)
{
	// Create a memory DC
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, size.cx, size.cy);
	CPen border_pen(PS_SOLID, 1, border);

	CBrush fill_brush;
	if(hatchstyle!=-1)
		fill_brush.CreateHatchBrush(hatchstyle, fill);
	else
		fill_brush.CreateSolidBrush(fill);

	CBitmap* pOldBitmap = MemDC.SelectObject(&bmp);
	CPen*    pOldPen    = MemDC.SelectObject(&border_pen);
	CBrush*  pOldBrush  = MemDC.SelectObject(&fill_brush);

	MemDC.Rectangle(0,0, size.cx, size.cy);

	if(NULL!=pOldBrush)  { MemDC.SelectObject(pOldBrush);  }
	if(NULL!=pOldPen)    { MemDC.SelectObject(pOldPen);    }
	if(NULL!=pOldBitmap) { MemDC.SelectObject(pOldBitmap); }
}

BOOL CSkinMenu::OnInitMenuWnd(HWND hWnd)
{
	CSkinMenuHook::CMenuHookData* pData = CSkinMenuHook::GetMenuHookData(hWnd);
	ASSERT(pData);
	if( pData->m_bDoSubclass)
	{
		// Flag for changing styles
		pData->m_dwData |= 2;

		SetWindowLongPtr (hWnd, GWL_STYLE, pData->m_dwStyle & (~WS_BORDER) );

		if(SystemVersion()->IsWinXPOrGreater() && CSkinMenu::GetAlpha()!=255)
		{
			SetWindowLongPtr (hWnd, GWL_EXSTYLE,(pData->m_dwExStyle| WS_EX_LAYERED) & ~(WS_EX_WINDOWEDGE|WS_EX_DLGMODALFRAME));
			SetLayeredWindowAttributes(hWnd, 0, CSkinMenu::GetAlpha(), LWA_ALPHA);
			pData->m_dwData |= 4;
			RedrawWindow(hWnd,NULL,NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);  
		}
		else
		{
			SetWindowLongPtr (hWnd, GWL_EXSTYLE,pData->m_dwExStyle & ~(WS_EX_WINDOWEDGE|WS_EX_DLGMODALFRAME));
		}

		return TRUE;
	}
	return FALSE;
}

BOOL CSkinMenu::OnUninitMenuWnd(HWND hWnd)
{
	CSkinMenuHook::CMenuHookData* pData = CSkinMenuHook::GetMenuHookData(hWnd);
	if(pData)
	{
		if(pData->m_dwData&4)
		{
			//KillTimer(hWnd,MENU_TIMER_ID);
			pData->m_dwData &= ~4;
		}
		HMENU hMenu = pData->m_hMenu;
		if(IsMenu(hMenu))
		{
			CSkinMenu* pNewMenu = DYNAMIC_DOWNCAST(CSkinMenu,CMenu::FromHandlePermanent(hMenu));

			if(pNewMenu)
			{
				// Redraw menubar on place.
				pNewMenu->OnUnInitPopupMenu();
			}
		}


		// were windows-style changed?
		if(pData->m_dwData&2)
		{
			SetLastError(0);
			if(!(pData->m_dwData&1))
			{
				SetWindowLongPtr (hWnd, GWL_STYLE,pData->m_dwStyle);
				ShowLastError(_T("Error from Menu: SetWindowLongPtr I"));
			}
			else
			{
				// Restore old Styles for special menu!!
				// (Menu 0x10012!!!) special VISIBLE flag must be set
				SetWindowLongPtr (hWnd, GWL_STYLE,pData->m_dwStyle|WS_VISIBLE);
				ShowLastError(_T("Error from Menu: SetWindowLongPtr I, Special"));
			}

			SetWindowLongPtr (hWnd, GWL_EXSTYLE, pData->m_dwExStyle);
			ShowLastError(_T("Error from Menu: SetWindowLongPtr II"));
			// Normaly when you change the style you shold call next function
			// but in this case you would lose the focus for the menu!!
			//SetWindowPos(hWnd,0,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED|SWP_HIDEWINDOW);
		}
	}
	return TRUE;
}

BOOL CSkinMenu::OnDrawBorder(HWND hWnd, HDC hDC, BOOL bOnlyBorder)
{
	CSkinMenuHook::CMenuHookData* pData = (CSkinMenuHook::CMenuHookData*)SetScreenBitmap(hWnd,hDC);
	if( pData)
	{
		//UINT nMenuDrawMode = CSkinMenu::GetMenuDrawMode();

		CRect rect;
		CRect client;
		CDC* pDC = CDC::FromHandle (hDC);

		// Get the size of the menu...
		GetWindowRect(hWnd, rect );
		GetClientRect(hWnd,client);
		CPoint offset(0,0);
		ClientToScreen(hWnd,&offset);
		client.OffsetRect(offset-rect.TopLeft());

		long winW = rect.Width();
		long winH = rect.Height();

		// Same Color as in DrawItem_WinXP
		COLORREF crMenuBar = CSkinMenu::GetMenuColor(pData->m_hMenu);
		COLORREF crWindow = GetSysColor(COLOR_WINDOW);
		COLORREF crThinBorder = MixedColor(crWindow,crMenuBar); //RGB(25,85,95);
		COLORREF clrBorder = RGB(25,85,95);//DarkenColor(128,crMenuBar);
		COLORREF colorBitmap;

		if (NumScreenColors() > 256)
		{
			colorBitmap = MixedColor(crMenuBar,crWindow);
		}
		else
		{
			colorBitmap = GetSysColor(COLOR_BTNFACE);
		}

		// Better contrast when you have less than 256 colors
		if(pDC->GetNearestColor(crThinBorder)==pDC->GetNearestColor(colorBitmap))
		{
			crThinBorder = crWindow;
			colorBitmap = crMenuBar;
		}

		if(!IsShadowEnabled())
		{
			if(!bOnlyBorder)
			{
				DrawFrame(pDC,CRect(CPoint(1,1),CSize(winW-6,winH-6)),client,crThinBorder);
			}

			if(bHighContrast)
			{
				pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-4,winH-4)),GetSysColor(COLOR_BTNTEXT),GetSysColor(COLOR_BTNTEXT));
			}
			else
			{
				pDC->Draw3dRect(CRect(CPoint(1,1),CSize(winW-6,winH-6)),crThinBorder,crThinBorder);
				pDC->FillSolidRect(1,2,1,winH-8,colorBitmap);
				pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-4,winH-4)),clrBorder,clrBorder);

				DrawShade(hWnd,pDC->m_hDC,pData->m_Point);
			}
		}
		else
		{
			if(!bOnlyBorder)
			{
				DrawFrame(pDC,CRect(CPoint(1,1),CSize(winW-2,winH-2)),client,crThinBorder);
			}

			if(bHighContrast)
			{
				pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-0,winH-0)),GetSysColor(COLOR_BTNTEXT ),GetSysColor(COLOR_BTNTEXT ));
			}
			else
			{
				CRgn rgn;
				CBrush brush;
				rgn.CreateRectRgn(0, 0, 0, 0);
				GetWindowRgn(hWnd, rgn);

				brush.CreateSolidBrush(clrBorder);
				pDC->FrameRgn(&rgn, &brush, 1, 1);
				brush.DeleteObject();
				rgn.DeleteObject();

				//pDC->Draw3dRect(CRect(CPoint(1,1),CSize(winW-2,winH-2)),crThinBorder,crThinBorder);
				//if(nMenuDrawMode==CSkinMenu::STYLE_XP_2003 || nMenuDrawMode==CSkinMenu::STYLE_XP_2003_NOBORDER)
				//{
				//	pDC->FillSolidRect(1,2,1,winH-4,crWindow);
				//}
				//else
				//{
				//	pDC->FillSolidRect(1,2,1,winH-4,colorBitmap);
				//}
				//pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-0,winH-0)),clrBorder,clrBorder);
			}
		}
		//DrawSmalBorder(hWnd,pDC->m_hDC);

		return TRUE;
	}
	return FALSE;
}

void* CSkinMenu::SetScreenBitmap(HWND hWnd, HDC hDC)
{
	UNREFERENCED_PARAMETER(hDC);

	CSkinMenuHook::CMenuHookData* pData = CSkinMenuHook::GetMenuHookData(hWnd);
	if(pData->m_Screen.m_hObject==NULL)
	{
		// Get the desktop hDC...
		HDC hDcDsk = GetWindowDC(0);
		CDC* pDcDsk = CDC::FromHandle(hDcDsk);

		CDC dc;
		dc.CreateCompatibleDC(pDcDsk);

		CRect rect;
		GetWindowRect(hWnd,rect);
		pData->m_Screen.CreateCompatibleBitmap(pDcDsk,rect.Width()+10,rect.Height()+10);
		CBitmap* pOldBitmap = dc.SelectObject(&pData->m_Screen);
		dc.BitBlt(0,0,rect.Width()+10,rect.Height()+10,pDcDsk,pData->m_Point.x,pData->m_Point.y,SRCCOPY);

		dc.SelectObject(pOldBitmap);
		// Release the desktop hDC...
		ReleaseDC(0,hDcDsk);
	}
	return pData;
}

void CSkinMenu::DrawFrame(CDC* pDC, CRect rectOuter, CRect rectInner, COLORREF crBorder)
{
	CRect Temp;
	rectInner.right -= 1;
	// Border top
	Temp.SetRect(rectOuter.TopLeft(),CPoint(rectOuter.right,rectInner.top));
	pDC->FillSolidRect(Temp,crBorder);
	// Border bottom
	Temp.SetRect(CPoint(rectOuter.left,rectInner.bottom),rectOuter.BottomRight());
	pDC->FillSolidRect(Temp,crBorder);

	// Border left
	Temp.SetRect(rectOuter.TopLeft(),CPoint(rectInner.left,rectOuter.bottom));
	pDC->FillSolidRect(Temp,crBorder);
	// Border right
	Temp.SetRect(CPoint(rectInner.right,rectOuter.top),rectOuter.BottomRight());
	pDC->FillSolidRect(Temp,crBorder);
}

void CSkinMenu::DrawShade(HWND hWnd, HDC hDC, CPoint screen)
{
	if(IsShadowEnabled())
		return;

	// Get the size of the menu...
	CRect Rect;
	GetWindowRect(hWnd, Rect );

	long winW = Rect.Width();
	long winH = Rect.Height();
	long xOrg = screen.x;
	long yOrg = screen.y;

	CSkinMenuHook::CMenuHookData* pData = CSkinMenuHook::GetMenuHookData(hWnd);

	CDC* pDC = CDC::FromHandle(hDC);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(&pData->m_Screen);

	HDC hDcDsk = memDC.m_hDC;
	xOrg = 0;
	yOrg = 0;

	//// Get the desktop hDC...
	//HDC hDcDsk = GetWindowDC(0);

	int X,Y;
	// Simulate a shadow on right edge...
	if (NumScreenColors() <= 256)
	{
		DWORD rgb = ::GetSysColor(COLOR_BTNSHADOW);
		BitBlt(hDC,winW-2,0,    2,winH,hDcDsk,xOrg+winW-2,0,SRCCOPY);
		BitBlt(hDC,0,winH-2,winW,2,hDcDsk,0,yOrg+winH-2,SRCCOPY);
		for (X=3; X<=4 ;X++)
		{
			for (Y=0; Y<4 ;Y++)
			{
				SetPixel(hDC,winW-X,Y,GetPixel(hDcDsk,xOrg+winW-X,yOrg+Y));
			}
			for (Y=4; Y<8 ;Y++)
			{
				SetPixel(hDC,winW-X,Y,rgb);
			}
			for (Y=8; Y<=(winH-5) ;Y++)
			{
				SetPixel( hDC, winW - X, Y, rgb);
			}
			for (Y=(winH-4); Y<=(winH-3) ;Y++)
			{
				SetPixel( hDC, winW - X, Y, rgb);
			}
		}
		// Simulate a shadow on the bottom edge...
		for(Y=3; Y<=4 ;Y++)
		{
			for(X=0; X<=3 ;X++)
			{
				SetPixel(hDC,X,winH-Y, GetPixel(hDcDsk,xOrg+X,yOrg+winH-Y));
			}
			for(X=4; X<=7 ;X++)
			{
				SetPixel( hDC, X, winH - Y, rgb);
			}
			for(X=8; X<=(winW-5) ;X++)
			{
				SetPixel( hDC, X, winH - Y, rgb);
			}
		}
	}
	else
	{
		for (X=1; X<=4 ;X++)
		{
			for (Y=0; Y<4 ;Y++)
			{
				SetPixel(hDC,winW-X,Y, GetPixel(hDcDsk,xOrg+winW-X,yOrg+Y) );
			}
			for (Y=4; Y<8 ;Y++)
			{
				COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y);
				SetPixel(hDC,winW-X,Y,DrawHelpers()->DarkenColor(2* 3 * X * (Y - 3), c));
			}
			for (Y=8; Y<=(winH-5) ;Y++)
			{
				COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y);
				SetPixel( hDC, winW - X, Y, DrawHelpers()->DarkenColor(2* 15 * X, c) );
			}
			for (Y=(winH-4); Y<=(winH-1) ;Y++)
			{
				COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y);
				SetPixel( hDC, winW - X, Y, DrawHelpers()->DarkenColor(2* 3 * X * -(Y - winH), c));
			}
		}

		// Simulate a shadow on the bottom edge...
		for(Y=1; Y<=4 ;Y++)
		{
			for(X=0; X<=3 ;X++)
			{
				SetPixel(hDC,X,winH-Y, GetPixel(hDcDsk,xOrg+X,yOrg+winH-Y));
			}
			for(X=4; X<=7 ;X++)
			{
				COLORREF c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y);
				SetPixel( hDC, X, winH - Y, DrawHelpers()->DarkenColor(2*3 * (X - 3) * Y, c));
			}
			for(X=8; X<=(winW-5) ;X++)
			{
				COLORREF  c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y);
				SetPixel( hDC, X, winH - Y, DrawHelpers()->DarkenColor(2* 15 * Y, c));
			}
		}
	}

	memDC.SelectObject(pOldBitmap);

	//// Release the desktop hDC...
	//ReleaseDC(0,hDcDsk);
}

BOOL CSkinMenu::OnCalcFrameRect(HWND hWnd,LPRECT pRect)
{
	GetWindowRect(hWnd,pRect);

	pRect->top += 2;
	pRect->left += 2;
	if(!IsShadowEnabled())
	{
		pRect->bottom -= 7;
		pRect->right -= 7;
	}
	else
	{
		pRect->bottom -= 3;
		pRect->right -= 3;
	}
	return TRUE;
}

void CSkinMenu::DrawSpecial_WinXP(CDC* pDC, LPCRECT pRect, UINT nID, DWORD dwStyle)
{
	TCHAR cSign = 0;
	switch(nID&0xfff0)
	{
	case SC_MINIMIZE:
		cSign = 48; // Min
		break;
	case SC_MAXIMIZE:
		cSign = 49;// Max
		break;
	case SC_CLOSE:
		cSign = 114;// Close
		break;
	case SC_RESTORE:
		cSign = 50;// Restore
		break;
	}
	if(cSign)
	{
		COLORREF oldColor;
		BOOL bBold = (dwStyle&ODS_DEFAULT) ? TRUE : FALSE;
		CRect rect(pRect);
		rect.InflateRect(0,(m_iconY-rect.Height())>>1);


		if( (dwStyle&ODS_GRAYED) || (dwStyle&ODS_INACTIVE))
		{
			oldColor = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
		}
		else if(dwStyle&ODS_SELECTED)
		{
			oldColor = pDC->SetTextColor(DarkenColorXP(GetXpHighlightColor()));
			rect.OffsetRect(1,1);
			DrawSpecialChar(pDC,rect,cSign,bBold);
			pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
			rect.OffsetRect(-2,-2);
		}
		else
		{
			oldColor = pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
		}
		DrawSpecialChar(pDC,rect,cSign,bBold);

		pDC->SetTextColor(oldColor);
	}
}

CRect CSkinMenu::GetLastActiveMenuRect()
{
	return m_LastActiveMenuRect;
}

void CSkinMenu::DrawSpecialCharStyle(CDC* pDC, LPCRECT pRect, TCHAR Sign, DWORD dwStyle)
{
	COLORREF oldColor;
	if( (dwStyle&ODS_GRAYED) || (dwStyle&ODS_INACTIVE))
	{
		oldColor = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
	}
	else
	{
		oldColor = pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
	}

	DrawSpecialChar(pDC,pRect,Sign,(dwStyle&ODS_DEFAULT) ? TRUE : FALSE);

	pDC->SetTextColor(oldColor);
}

void CSkinMenu::DrawSpecialChar(CDC* pDC, LPCRECT pRect, TCHAR Sign, BOOL bBold)
{
	//  48 Min
	//  49 Max
	//  50 Restore
	//  98 Checkmark
	// 105 Bullet
	// 114 Close

	CFont MyFont;
	LOGFONT logfont;

	CRect rect(pRect);
	rect.DeflateRect(2,2);

	logfont.lfHeight = -rect.Height();
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = (bBold) ? FW_BOLD:FW_NORMAL;
	logfont.lfItalic = FALSE;
	logfont.lfUnderline = FALSE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = DEFAULT_CHARSET;
	logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = DEFAULT_QUALITY;
	logfont.lfPitchAndFamily = DEFAULT_PITCH;

	lstrcpyn(logfont.lfFaceName,_T("Marlett"),CountArray(logfont.lfFaceName));

	MyFont.CreateFontIndirect (&logfont);

	CFont* pOldFont = pDC->SelectObject (&MyFont);
	int OldMode = pDC->SetBkMode(TRANSPARENT);

	pDC->DrawText (&Sign,1,rect,DT_CENTER|DT_SINGLELINE);

	pDC->SetBkMode(OldMode);
	pDC->SelectObject(pOldFont);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const TCHAR _OldMenuProc[] = _T("OldMenuProc");

//HMODULE CSkinMenuHook::m_hThemeLibrary = NULL;
HHOOK 	CSkinMenuHook::HookOldMenuCbtFilter = NULL;
HMENU 	CSkinMenuHook::m_hLastMenu = NULL;
DWORD 	CSkinMenuHook::m_dwMsgPos = 0;
//DWORD 	CSkinMenuHook::m_bSubclassFlag = SKIN_MENU_DIALOG_SUBCLASS | SKIN_MENU_DIALOG_SYSTEM_MENU;
DWORD 	CSkinMenuHook::m_bSubclassFlag = 0;

CTypedPtrMap<CMapPtrToPtr,HWND,CSkinMenuHook::CMenuHookData*> CSkinMenuHook::m_MenuHookData;

#ifndef SM_REMOTESESSION
#define SM_REMOTESESSION     0x1000
#endif

CSkinMenuHook::CSkinMenuHook()
{
	HIGHCONTRAST highcontrast = {0};
	highcontrast.cbSize = sizeof(highcontrast);
	if(SystemParametersInfo(SPI_GETHIGHCONTRAST,sizeof(highcontrast),&highcontrast,0) )
	{
		bHighContrast = ((highcontrast.dwFlags & HCF_HIGHCONTRASTON)!=0);
	}

	if (HookOldMenuCbtFilter == NULL)
	{
		HookOldMenuCbtFilter = ::SetWindowsHookEx(WH_CALLWNDPROC, SkinMenuHook, NULL, ::GetCurrentThreadId());
		if (HookOldMenuCbtFilter == NULL)
		{
			ShowLastError(_T("Error from Menu: SetWindowsHookEx"));
			AfxThrowMemoryException();
		}
	}
}

CSkinMenuHook::~CSkinMenuHook()
{
	if (HookOldMenuCbtFilter != NULL)
	{
		if(!::UnhookWindowsHookEx(HookOldMenuCbtFilter))
		{
			ShowLastError(_T("Error from Menu: UnhookWindowsHookEx"));
		}
		HookOldMenuCbtFilter = NULL;
	}

	//pIsThemeActive = NULL;

	// Cleanup for shared menu icons
	if(CSkinMenu::m_pSharedMenuIcons)
	{
		delete CSkinMenu::m_pSharedMenuIcons;
		CSkinMenu::m_pSharedMenuIcons = NULL;
	}
}

CSkinMenuHook::CMenuHookData* CSkinMenuHook::GetMenuHookData(HWND hWnd)
{
	CMenuHookData* pData=NULL;
	if(m_MenuHookData.Lookup(hWnd,pData))
	{
		return pData;
	}
	return NULL;
}

void CSkinMenuHook::UnsubClassMenu(HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetModuleState());

	WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, _OldMenuProc);
	ASSERT(oldWndProc != NULL);

	SetLastError(0);
	if(!SetWindowLongPtr(hWnd, GWLP_WNDPROC, (INT_PTR)oldWndProc))
	{
		ShowLastError(_T("Error from Menu: SetWindowLongPtr III"));
	}
	RemoveProp(hWnd, _OldMenuProc);
	GlobalDeleteAtom(GlobalFindAtom(_OldMenuProc));

	// now Clean up
	HMENU hMenu = NULL;
	// Restore old Styles for special menu!! (Menu 0x10012!!!)
	CMenuHookData* pData = GetMenuHookData(hWnd);
	if(pData)
	{
		hMenu = pData->m_hMenu;
		CSkinMenu::OnUninitMenuWnd(hWnd);

		m_MenuHookData.RemoveKey(hWnd);

		delete pData;
	}
}

LRESULT CALLBACK CSkinMenuHook::SubClassMenu(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetModuleState());

	WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, _OldMenuProc);
	LRESULT result = NULL;
	BOOL bCallDefault = TRUE;

	CMenuHookData* pData = GetMenuHookData(hWnd);
	if(NULL == pData)
	{
		ASSERT(oldWndProc!=NULL);
		return ::CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
	}
	ASSERT(pData);

	switch(uMsg)
	{
	case WM_NCPAINT:
		ASSERT(pData);

		if(pData->m_bDoSubclass)
		{
			if(!pData->m_bDrawBorder)
			{
				if(pData->m_hRgn!=(HRGN)wParam)
				{
					if(pData->m_hRgn!=(HRGN)1)
					{
						DeleteObject(pData->m_hRgn);
						pData->m_hRgn=(HRGN)1;
					}
					if(wParam!=1)
					{
						CRgn dest;
						dest.CreateRectRgn( 0, 0, 1, 1);
						dest.CopyRgn(CRgn::FromHandle((HRGN)wParam));
						pData->m_hRgn = (HRGN)dest.Detach();
					}
				}
			}

			if(pData->m_dwData & 8)
			{
				// do not call default!!!
				bCallDefault=FALSE;
			}

			if(pData->m_bDrawBorder)
			{
				HDC hDC = GetWindowDC (hWnd);
				if(CSkinMenu::OnDrawBorder(hWnd,hDC))
				{
					CRect rect;
					if(CSkinMenu::OnCalcFrameRect(hWnd,rect))
					{
						CRgn rgn;
						rect.InflateRect(-1,-1);
						rgn.CreateRectRgnIndirect(rect);
						// do we need a combination of the regions?
						//if(wParam!=1)
						//{
						//  rgn.CombineRgn(&rgn,CRgn::FromHandle((HRGN)wParam),RGN_AND);
						//}
						ASSERT(oldWndProc);

						bCallDefault=FALSE;
						result = CallWindowProc(oldWndProc, hWnd, uMsg, (WPARAM)rgn.m_hObject, lParam);
						//result = CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
						// Redraw the border and shade
						CSkinMenu::OnDrawBorder(hWnd,hDC,true);
					}
				}
				ReleaseDC(hWnd,hDC);

			}
			if(bCallDefault)
			{
				// Save the background
				HDC hDC = GetWindowDC (hWnd);
				CSkinMenu::SetScreenBitmap(hWnd,hDC);
				ReleaseDC(hWnd,hDC);
			}
		}

		break;

	case WM_PRINT:
		if(pData && pData->m_bDoSubclass)
		{

			// Mark for WM_PRINT
			pData->m_dwData |= 8;

			//      pData->m_bDrawBorder = FALSE;
			// We need to create a bitmap for drawing
			// We can't clipp or make a offset to the DC because NT2000 (blue-screen!!)
			CRect rect;
			GetWindowRect(hWnd, rect);
			CDC dc;
			CBitmap bitmap;

			CDC* pDC = CDC::FromHandle((HDC)wParam);
			dc.CreateCompatibleDC(pDC);

			bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			CBitmap* pOldBitmap = dc.SelectObject(&bitmap);

			// new
			//       dc.FillSolidRect(0,0,rect.Width(), rect.Height(),CSkinMenu::GetMenuBarColor(pData->m_hMenu));

			CSkinMenu::OnDrawBorder(hWnd,dc.m_hDC);

			CRect rectClient;
			if(CSkinMenu::OnCalcFrameRect(hWnd,rectClient))
			{
				// might as well clip to the same rectangle
				CRect clipRect = rectClient;
				clipRect.OffsetRect(rectClient.TopLeft()-rect.TopLeft());
				clipRect.InflateRect(-1,-1);
				dc.IntersectClipRect(clipRect);
				result = CallWindowProc(oldWndProc, hWnd, uMsg, (WPARAM)dc.m_hDC, lParam&~PRF_CLIENT);

				pDC->BitBlt(0,0, rect.Width(), rect.Height(), &dc,0,0, SRCCOPY);

				GetClientRect(hWnd,clipRect);
				SelectClipRgn(dc.m_hDC,NULL);
				dc.IntersectClipRect(clipRect);

				SendMessage(hWnd,WM_ERASEBKGND,(WPARAM)dc.m_hDC,0);
				SendMessage(hWnd,WM_PRINTCLIENT,(WPARAM)dc.m_hDC,lParam);

				CPoint wndOffset(0,0);
				ClientToScreen(hWnd,&wndOffset);
				wndOffset -= rect.TopLeft();
				pDC->BitBlt(wndOffset.x,wndOffset.y, clipRect.Width()-1, clipRect.Height(), &dc, 0, 0, SRCCOPY);
				//pDC->BitBlt(wndOffset.x,wndOffset.y, clipRect.Width(), clipRect.Height(), &dc, 0, 0, SRCCOPY);
			}
			//
			dc.SelectObject(pOldBitmap);
			bCallDefault=FALSE;

			// Clear for WM_PRINT
			pData->m_dwData &= ~8;
		}
		break;

	//case WM_ERASEBKGND:
	//	ASSERT(pData);
	//	if(pData->m_bDoSubclass)
	//	{
	//		if(CSkinMenu::m_pActMenuDrawing->DoDrawBorder())
	//		{
	//			if(!(pData->m_dwData&8) && !pData->m_bDrawBorder )
	//			{
	//				pData->m_bDrawBorder = true;
	//				//SendMessage(hWnd,WM_NCPAINT,(WPARAM)pData->m_hRgn,0);
	//				SendMessage(hWnd,WM_NCPAINT,(WPARAM)1,0);
	//			}
	//		}

	//		if(CSkinMenu::m_pActMenuDrawing->OnEraseBkgnd(hWnd,(HDC)wParam))
	//		{
	//			bCallDefault=FALSE;
	//			result = TRUE;
	//		}
	//	}
	//	break;

	case WM_WINDOWPOSCHANGED:
	case WM_WINDOWPOSCHANGING:
		{
			ASSERT(pData);

			LPWINDOWPOS pPos = (LPWINDOWPOS)lParam;
			if(uMsg==WM_WINDOWPOSCHANGING)
			{
				if(!IsShadowEnabled())
				{
					pPos->cx +=2;
					pPos->cy +=2;
				}
				else
				{
					pPos->cx -=2;
					pPos->cy -=2;
				}
				pPos->y -=1;
			}

			if(!(pPos->flags&SWP_NOMOVE) )
			{
				if(pData->m_Point==CPoint(0,0))
				{
					pData->m_Point = CPoint(pPos->x,pPos->y);
				}
				else if(pData->m_Point!=CPoint(pPos->x,pPos->y))
				{
					if(!(pPos->flags&SWP_NOSIZE))
					{
						UnsubClassMenu(hWnd);
					}
					else
					{
						pData->m_Point=CPoint(pPos->x,pPos->y);
						pData->m_Screen.DeleteObject();
					}
				}
			}
		}
		break;

	case WM_KEYDOWN:
		if(wParam==VK_ESCAPE)
		{
			if(pData)
			{
				pData->m_dwData |= 4;
			}
		}
		m_dwMsgPos = GetMessagePos();
		break;

	case WM_NCCALCSIZE:
		if(pData->m_bDoSubclass)
		{
			NCCALCSIZE_PARAMS* pCalc = (NCCALCSIZE_PARAMS*)lParam;
			int cx=0,cy=0;
			if(!IsShadowEnabled())
			{
				cx = 5;
				cy = 6;
			}
			else
			{
				cx = 1;
				cy = 2;
			}

			pCalc->rgrc->top  += 2;
			pCalc->rgrc->left += 2;
			pCalc->rgrc->bottom -= cy;
			pCalc->rgrc->right  -= cx;
		}
		break;

	case WM_SHOWWINDOW:
		// Hide the window ? Test for 98 and 2000
		if(wParam==NULL)
		{
			// Special handling for NT 2000 and WND 0x10012.
			UnsubClassMenu(hWnd);
		}
		break;

	case WM_NCDESTROY:
		{
			UnsubClassMenu (hWnd);
			break;
		}
	case WM_SIZE:
		{
			CRect rcWindow;
			CRgn rgn;
			GetWindowRect(hWnd, &rcWindow);
			rcWindow.OffsetRect(-rcWindow.TopLeft());
			rgn.CreateRoundRectRgn(rcWindow.left, rcWindow.top, 
				rcWindow.right+1, rcWindow.bottom+1, MENU_ROUND_CX, MENU_ROUND_CY);
			SetWindowRgn(hWnd, rgn, TRUE);
			break;
		}
	}

	if( bCallDefault )
	{
		ASSERT(oldWndProc != NULL);
		// call original wndproc for default handling
		result = CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
	}

	return result;
}
 
BOOL CSkinMenuHook::CheckSubclassing(HWND hWnd, BOOL bSpecialWnd)
{
	TCHAR Name[32];
	int Count = GetClassName (hWnd,Name,CountArray(Name));
	// Check for the menu-class
	if(Count!=6 || _tcscmp(Name,_T("#32768"))!=0)
	{
		// does not match to menuclass
		return FALSE;
	}
	BOOL bDoNewSubclass = FALSE;
	CMenuHookData* pData=GetMenuHookData(hWnd);
	// check if we have allready some data
	if(pData==NULL)
	{
		// a way for get the menu-handle not documented
		m_hLastMenu = (HMENU)SendMessage(hWnd,MN_GETHMENU,0,0);

		if (m_hLastMenu==NULL)
			return FALSE;

		CMenu *pMenu = CMenu::FromHandlePermanent(m_hLastMenu);
		// now we support only new menu
		if( !DYNAMIC_DOWNCAST(CSkinMenu,pMenu) )
			return FALSE;

		WNDPROC oldWndProc;
		// subclass the window with the proc which does gray backgrounds
		oldWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC);
		if (oldWndProc != NULL && GetProp(hWnd, _OldMenuProc) == NULL)
		{
			ASSERT(oldWndProc!=SubClassMenu);

			if(!SetProp(hWnd, _OldMenuProc, oldWndProc))
			{
				ShowLastError(_T("Error from Menu: SetProp"));
			}
			if ((WNDPROC)GetProp(hWnd, _OldMenuProc) == oldWndProc)
			{
				GlobalAddAtom(_OldMenuProc);

				CMenuHookData* pData=GetMenuHookData(hWnd);
				ASSERT(pData==NULL);
				if(pData==NULL)
				{
					pData = new CMenuHookData(hWnd,bSpecialWnd);
					m_MenuHookData.SetAt (hWnd,pData);

					SetLastError(0);
					if(!SetWindowLongPtr(hWnd, GWLP_WNDPROC,(INT_PTR)SubClassMenu))
					{
						ShowLastError(_T("Error from Menu: SetWindowLongPtr IV"));
					}
					bDoNewSubclass = TRUE;

					//
					CSkinMenu::OnInitMenuWnd(hWnd);
				}
			}
			else
			{
				ASSERT(0);
			}
		}
	}

	// Menu was set also assign it to this menu.
	if(m_hLastMenu)
	{
		CMenuHookData* pData = GetMenuHookData(hWnd);
		if(pData)
		{
			// Safe actual menu
			pData->SetMenu(m_hLastMenu);
			// Reset for the next menu
			m_hLastMenu = NULL;
			CSkinMenu::OnInitMenuWnd(hWnd);
		}
	}
	return bDoNewSubclass;
}

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuTempHandler class used to add NewMenu to system dialog
class CSkinMenuTempHandler : public CObject
{
	CSkinMenu m_SystemNewMenu;
	WNDPROC m_oldWndProc;
	HWND m_hWnd;

public:
	CSkinMenuTempHandler(HWND hWnd)
	{
		m_hWnd = hWnd;
		VERIFY(SetProp(hWnd,_T("CSkinMenuTempHandler"),this));
		// Subclass the dialog control.
		m_oldWndProc = (WNDPROC)(LONG_PTR)SetWindowLongPtr(hWnd, GWLP_WNDPROC,(INT_PTR)TempSubclass);
	}

	~CSkinMenuTempHandler()
	{
		SetWindowLongPtr(m_hWnd, GWLP_WNDPROC,(INT_PTR)m_oldWndProc);
		VERIFY(RemoveProp(m_hWnd,_T("CSkinMenuTempHandler")));
	}

	LRESULT Default(UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		// call original wndproc for default handling
		return CallWindowProc(m_oldWndProc, m_hWnd, uMsg, wParam, lParam);
	}

	LRESULT OnCmd(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		MSG msg = {m_hWnd,uMsg,wParam,lParam,0,0,0};
		switch(uMsg)
		{
		case WM_DRAWITEM:
			{
				if(m_SystemNewMenu.m_hMenu)
				{
					DRAWITEMSTRUCT* lpDrawItemStruct = (DRAWITEMSTRUCT*)lParam;
					if (lpDrawItemStruct->CtlType == ODT_MENU)
					{
						CMenu* pMenu = CMenu::FromHandlePermanent((HMENU)lpDrawItemStruct->hwndItem);
						if (DYNAMIC_DOWNCAST(CSkinMenu,pMenu))
						{
							pMenu->DrawItem(lpDrawItemStruct);
							return true; // eat it
						}
					}
				}
				return Default(uMsg, wParam, lParam);
			}

		case WM_MEASUREITEM:
			if(CSkinMenu::OnMeasureItem(&msg))
			{
				return TRUE;
			}
			break;

		case WM_MENUCHAR:
			{
				CMenu* pMenu = CMenu::FromHandle(HMENU((UINT)lParam));
				LRESULT lresult;
				if( DYNAMIC_DOWNCAST(CSkinMenu,pMenu) )
					lresult=CSkinMenu::FindKeyboardShortcut(LOWORD(wParam), HIWORD(wParam),pMenu );
				else
					lresult=Default(uMsg, wParam, lParam);
				return lresult;
			}
			break;

		case WM_INITMENUPOPUP:
			{
				CMenu* pMenu = CMenu::FromHandle(HMENU((UINT)wParam));
				LRESULT result = Default(uMsg, wParam, lParam);
				CSkinMenu::OnInitMenuPopup(m_hWnd, pMenu, LOWORD(lParam), HIWORD(lParam));
				
				return result;
			}

		case WM_INITDIALOG:
			if(CSkinMenuHook::m_bSubclassFlag & SKIN_MENU_DIALOG_SYSTEM_MENU)
			{
				LRESULT bRetval = Default(uMsg, wParam, lParam);
				VERIFY(m_SystemNewMenu.m_hMenu==0);

				HMENU hMenu = ::GetSystemMenu(m_hWnd,FALSE);
				if(IsMenu(hMenu))
				{
					CMenu* pMenu = CMenu::FromHandlePermanent(hMenu);
					// Only attach to CSkinMenu once
					if (DYNAMIC_DOWNCAST(CSkinMenu,pMenu)==NULL )
					{
						m_SystemNewMenu.Attach(hMenu);
					}
				}
				return bRetval;
			}
			break;

		case WM_DESTROY:
			LRESULT result = Default(uMsg, wParam, lParam);
			delete this;
			return result;
		}

		return Default(uMsg, wParam, lParam);
	}

	// Subclass procedure
	static LRESULT APIENTRY TempSubclass(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		AFX_MANAGE_STATE(AfxGetModuleState());

		CSkinMenuTempHandler* pTemp = (CSkinMenuTempHandler*)GetProp(hwnd,_T("CSkinMenuTempHandler"));
		ASSERT(pTemp);
		return pTemp->OnCmd(uMsg, wParam, lParam);
	}

};

LRESULT CALLBACK CSkinMenuHook::SkinMenuHook(int code, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetModuleState());

	CWPSTRUCT* pTemp = (CWPSTRUCT*)lParam;
	if(code == HC_ACTION )
	{
		HWND hWnd = pTemp->hwnd;

		// Normal and special handling for menu 0x10012
		if(pTemp->message==WM_CREATE || pTemp->message==0x01E2)
		{
			if(!CheckSubclassing(hWnd,pTemp->message==0x01E2))
			{
				if( (m_bSubclassFlag & SKIN_MENU_DIALOG_SUBCLASS) && pTemp->message==WM_CREATE)
				{
					TCHAR Name[20];
					int Count = GetClassName (hWnd,Name,CountArray(Name));
					// Check for the Dialog-class
					if(Count==6 && _tcscmp(Name,_T("#32770"))==0 )
					{
						// Only first dialog
						// m_bSubclassFlag &= ~SKIN_MENU_DIALOG_SUBCLASS;
						// Freed by WM_DESTROY
						new CSkinMenuTempHandler(hWnd);
					}
				}
			}
		}
	}
	return CallNextHookEx(HookOldMenuCbtFilter, code,wParam, lParam);
}
