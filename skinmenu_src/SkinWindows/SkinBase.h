// SkinBase.h: interface for the CSkinBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINBASE_H__D53DE9FD_C2BF_49DB_8B16_4F7874CA2579__INCLUDED_)
#define AFX_SKINBASE_H__D53DE9FD_C2BF_49DB_8B16_4F7874CA2579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Mmsystem.h>

#pragma comment(lib, "winmm.lib") // for PlaySound

// os
enum
{
	SBOS_95,
	SBOS_98,
	SBOS_ME,
	SBOS_NT4,
	SBOS_2K,
	SBOS_XP,
	SBOS_XPP, // after xp
};

// for transparency
typedef WINGDIAPI BOOL (WINAPI *PFNTRANSPARENTBLT)(HDC,int,int,int,int,HDC,int,int,int,int,UINT);

// for gradient fill
typedef WINGDIAPI BOOL (WINAPI *PFNGRADIENTFILL)(HDC,PTRIVERTEX,ULONG,PVOID,ULONG,ULONG);

class CSkinBase
{
public:
	CSkinBase();
	virtual ~CSkinBase();

	// helper methods
	static BOOL FontIsPresent(LPCTSTR szFaceName);
	static int GetOS();
	static HRGN BitmapToRegion(CBitmap* pBmp, COLORREF cTransparentColor);
	static HMENU MakeMenuCopy(const CMenu* pSrc);
	static BOOL CopyBitmap(const CBitmap* pSrc, CBitmap* pDest);
	static BOOL CopyMenu(const CMenu* pSrc, CMenu* pDest);
	static BOOL ExtractResource(UINT nID, LPCTSTR szType, CString& sTempFilePath, HINSTANCE hInst = NULL);
	static CWnd* GetChildWnd(CWnd* pParent, LPCTSTR szClass, int nID = -1);
	static CString GetTipText(LPCTSTR szText, BOOL bToolbar);
	static BOOL ConvertToGrayScale(CBitmap* pBitmap, COLORREF crMask);
	static BOOL DoSysMenu(CWnd* pWnd, CPoint ptCursor, LPRECT prExclude = NULL, BOOL bCopy = FALSE);
	static void InitSysMenu(CMenu* pMenu, CWnd* pWnd);
	static HICON GetWindowIcon(CWnd* pWnd);
	static COLORREF BlendColors(COLORREF crA, COLORREF crB, float fAmountA = 0.5f);
	static COLORREF VaryColor(COLORREF crColor, float fFactor);

	// special blt functions which handle transparency
	static BOOL BitBlt(CDC* pDCDest, 
							int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest,
							CDC* pDCSrc, int nXOriginSrc, int nYOriginSrc, 
							UINT uROP = SRCCOPY,     
							COLORREF crTransparent = -1);

	static BOOL StretchBlt(CDC* pDCDest, 
							int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest,
							CDC* pDCSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,     
							UINT uROP = SRCCOPY,     
							COLORREF crTransparent = -1);

	// gradient fill from top->bottom or left->right
	static BOOL GradientFill(CDC* pDCDest, LPRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);

	// returns the actual text height
	static int FormatText(CDC* pDC, CString& sText, CRect& rect, UINT uDTFlags);
	static CSize GetTextExtent(CDC* pDC, LPCTSTR szText); // takes & into account

	static void EnableTheming(BOOL bEnable); // under xp
	static BOOL IsThemingEnabled() { return s_bThemingEnabled; }
	static BOOL CreateThemeManifest(LPCTSTR szName, LPCTSTR szDescription);

private:
	static int s_nOSVer;
	static BOOL s_bSupportsFastTransparentBlt;
	static PFNTRANSPARENTBLT s_pfnFastTransparentBlt;
	static BOOL s_bSupportsFastGradientFill;
	static PFNGRADIENTFILL s_pfnFastGradientFill;
	static BOOL s_bThemingEnabled;

	static BOOL SupportsFastTransparentBlt();
	static BOOL TransparentBltFast(CDC* pDCDest, 
									int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest,
									CDC* pDCSrc, 
									int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,     
									UINT crTransparent);

	static BOOL SupportsFastGradientFill();
	static BOOL GradientFillFast(CDC* pDCDest, LPRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);

	// fallbacks for win9x
	static BOOL TransparentBltSlow(CDC* pDCDest, 
									int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest,
									CDC* pDCSrc, 
									int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,     
									UINT crTransparent);
	static BOOL GradientFillSlow(CDC* pDCDest, LPRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);

	static BOOL TransparentBlt(CDC* pDCDest, 
								int nXOriginDest, int nYOriginDest, int nWidthDest, int hHeightDest,
								CDC* pDCSrc, 
								int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,     
								UINT crTransparent);
};

// helper structs
enum
{
	IM_HOT,
	IM_COLD,
	IM_DOWN,
	IM_DISABLED,

	IM_LAST
};


struct ImageInfo
{
	ImageInfo()
	{ 
		Reset();
	}

	ImageInfo(int nIm)
	{ 
		Reset();
		nImage[IM_HOT] = nIm; 
	}

	int GetImage(int nType, BOOL bWrap = TRUE)
	{
		if (nType < IM_HOT || nType >= IM_LAST)
			return -1;

		switch (nType)
		{
		case IM_HOT:
			return nImage[IM_HOT];

		default:
			return (!bWrap || nImage[nType] != -1) ? nImage[nType] : nImage[IM_HOT];
		}
	}

	void Reset()
	{
		for (int nIm = 0; nIm < IM_LAST; nIm++) 
			nImage[nIm] = -1; 
	}

	int nImage[IM_LAST];
};

enum
{
	SND_ON,
	SND_OFF,
	SND_CLICK,

	SND_LAST
};

struct SoundInfo
{
	SoundInfo()
	{ 
		Reset();
	}

	void SetSounds(UINT uSoundIDs[SND_LAST])
	{
		Reset();

		for (int nSnd = 0; nSnd < SND_LAST; nSnd++) 
			uSoundID[nSnd] = uSoundIDs[nSnd]; 
	}

	void SetSounds(CString sSoundPaths[SND_LAST])
	{
		Reset();

		for (int nSnd = 0; nSnd < SND_LAST; nSnd++) 
			sSoundPath[nSnd] = sSoundPaths[nSnd]; 
	}
	
	BOOL PlaySound(int nType)
	{
#ifdef _USRDLL
		// If this is a DLL, need to set up MFC state
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

		UINT uFlags = SND_ASYNC | SND_NODEFAULT;

		// try to play the filename
		if (!sSoundPath[nType].IsEmpty() && sndPlaySound(sSoundPath[nType], uFlags))
			return TRUE;

		// else try to play an embedded sound
		CString sSoundFile;

		if (uSoundID[nType] && 
			(CSkinBase::ExtractResource(uSoundID[nType], "WAVE", sSoundFile) ||
			CSkinBase::ExtractResource(uSoundID[nType], "WAV", sSoundFile)))
		{
			if (sndPlaySound(sSoundFile, uFlags))
			{
				// cache pathname 
				sSoundPath[nType] = sSoundFile;
				uSoundID[nType] = 0;
				return TRUE;
			}
		}

		return FALSE;
	}

	BOOL PlaySoundWrap(int nType)
	{
		if (!PlaySound(nType))
		{
			// try the others
			switch (nType)
			{
			case SND_ON:
				return (PlaySound(SND_OFF) || PlaySound(SND_CLICK));

			case SND_OFF:
				return (PlaySound(SND_ON) || PlaySound(SND_CLICK));

			case SND_CLICK:
				return (PlaySound(SND_ON) || PlaySound(SND_OFF));

			default:
				return FALSE;
			}
		}

		return TRUE;
	}

	void Reset()
	{
		for (int nSnd = 0; nSnd < SND_LAST; nSnd++) 
		{
			uSoundID[nSnd] = 0; 
			sSoundPath[nSnd].Empty(); 
		}
	}

	UINT uSoundID[SND_LAST];
	CString sSoundPath[SND_LAST];
};

struct FontInfo
{
	FontInfo(LPCTSTR szName = NULL, int nSize = 0, LPCTSTR szPath = NULL)
		{ sFaceName = szName; sFilePath = szPath; nPointSize = nSize; 
			nHeight = 0; bBold = bItalic = bUnderline = FALSE; }

	CString sFaceName;
	CString sFilePath; // ttf file
	int nPointSize; // point sizes may be different for different fonts
	int nHeight; // in pixels
	BOOL bBold;
	BOOL bItalic;
	BOOL bUnderline;
};


#endif // !defined(AFX_SKINBASE_H__D53DE9FD_C2BF_49DB_8B16_4F7874CA2579__INCLUDED_)
