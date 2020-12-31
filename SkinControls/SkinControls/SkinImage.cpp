
#include "stdafx.h"
#include "SkinImage.h"
#include "BitmapPng.h"
#include "DrawHelpers.h"
#include "SystemHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSkinImage::CSkinImage()
{
	m_bAlpha = FALSE;

	m_szExtent = CSize(0, 0);

	m_pBits = NULL;
	m_hBitmap = NULL;
}

CSkinImage::~CSkinImage()
{
	DestroyImage();
}

// 创建位图
BOOL CSkinImage::Create(int nWidth, int nHeight, HDC hDc)
{
	m_bAlpha = FALSE;

	if (m_hBitmap)
	{
		DeleteObject(m_hBitmap);
	}
	m_hBitmap = NULL;
	m_pBits = NULL;

	m_hBitmap = Create32BPPDIBSection(hDc, nWidth, nHeight, NULL);

	if (!m_hBitmap)
		return FALSE;

	m_szExtent = CSize(nWidth, nHeight);
	m_bAlpha = TRUE;

	return TRUE;
}

BOOL CSkinImage::LoadFromFile(LPCTSTR pszFileName, BitmapFormat bf)
{
	m_bAlpha = FALSE;

	if (m_hBitmap)
	{
		DeleteObject(m_hBitmap);
	}
	m_hBitmap = NULL;
	m_pBits = NULL;

	if (pszFileName == NULL)
		return FALSE;

	BOOL bAlpha = FALSE;

	m_hBitmap = LoadBitmapFromFile(pszFileName, &bAlpha, bf);

	if (!m_hBitmap)
		return FALSE;

	m_szExtent = GetExtent();
	m_bAlpha = bAlpha;

	return TRUE;
}

BOOL CSkinImage::LoadFromResource(HMODULE hModule, LPCTSTR lpszResource, BitmapFormat bf)
{
	m_bAlpha = FALSE;

	if (m_hBitmap)
	{
		DeleteObject(m_hBitmap);
	}
	m_hBitmap = NULL;
	m_pBits = NULL;

	if (!hModule)
		return FALSE;

	BOOL bAlpha = FALSE;

	m_hBitmap = LoadBitmapFromResource(hModule, lpszResource, &bAlpha, bf);

	if (!m_hBitmap)
		return FALSE;

	m_szExtent = GetExtent();
	m_bAlpha = bAlpha;

	return TRUE;
}

// 从内存加载位图
BOOL CSkinImage::LoadFromMemory(BYTE* pBuffer, DWORD dwSize, BitmapFormat bf)
{
	m_bAlpha = FALSE;

	if (m_hBitmap)
	{
		DeleteObject(m_hBitmap);
	}
	m_hBitmap = NULL;
	m_pBits = NULL;

	if (!pBuffer || dwSize == 0)
		return FALSE;

	BOOL bAlpha = FALSE;

	m_hBitmap = LoadBitmapFromMemory(pBuffer, dwSize, &bAlpha, bf);

	if (!m_hBitmap)
		return FALSE;

	m_szExtent = GetExtent();
	m_bAlpha = bAlpha;

	return TRUE;
}

void CSkinImage::DestroyImage()
{
	if (m_hBitmap)
	{
		DeleteObject(m_hBitmap);
	}
	m_hBitmap = NULL;
	m_pBits = NULL;
	m_szExtent.SetSize(0, 0);
}

// 绘画位图
void CSkinImage::DrawImage(CDC* pDC, int nXPos, int nYPos, COLORREF clrTransparent)
{
	DrawImage(pDC, CRect(nXPos, nYPos, nXPos + m_szExtent.cx, nYPos + m_szExtent.cy),
		CRect(0, 0, m_szExtent.cx, m_szExtent.cy), clrTransparent);

	return;
}

// 绘画位图
void CSkinImage::DrawImage(CDC* pDC, int nXDest, int nYDest, int nDestWidth, int nDestHeight, COLORREF clrTransparent)
{
	DrawImage(pDC, CRect(nXDest, nYDest, nXDest + nDestWidth, nYDest + nDestHeight),
		CRect(0, 0, m_szExtent.cx, m_szExtent.cy), clrTransparent);

	return;
}

// 绘画位图
void CSkinImage::DrawImage(CDC* pDC, int nXDest, int nYDest, int nDestWidth, int nDestHeight, int nXScr, int nYSrc, int nSrcWidth, int nSrcHeight, COLORREF clrTransparent)
{
	DrawImage(pDC, CRect(nXDest, nYDest, nXDest + nDestWidth, nYDest + nDestHeight),
		CRect(nXScr, nYSrc, nXScr + nSrcWidth, nYSrc + nSrcHeight), clrTransparent);

	return;
}

// 绘画位图 
void CSkinImage::DrawImage(CDC* pDC, const CRect& rcDest, CRect rcSrc, COLORREF clrTransparent)
{
	if (clrTransparent == CLR_NONE || m_bAlpha)
	{
		DrawImage(pDC, rcDest, rcSrc);
		return;
	}

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rcDest.Width(), rcDest.Height());

	CCompatibleDC dc(pDC, &bmp);

	CRect rcDestOrig(0, 0, rcDest.Width(), rcDest.Height());

	dc.FillSolidRect(rcDestOrig, clrTransparent);
	DrawImage(&dc, rcDestOrig, rcSrc);

	TransparentBlt(*pDC, rcDest, dc, rcDestOrig, clrTransparent);
}

// 绘画位图
void CSkinImage::DrawImage(CDC* pDC, int nXPos, int nYPos)
{
	DrawImage(pDC, CRect(nXPos, nYPos, nXPos + m_szExtent.cx, nYPos + m_szExtent.cy),
		CRect(0, 0, m_szExtent.cx, m_szExtent.cy));

	return;
}

// 绘画位图
void CSkinImage::DrawImage(CDC* pDC, int nXDest, int nYDest, int nDestWidth, int nDestHeight)
{
	DrawImage(pDC, CRect(nXDest, nYDest, nXDest + nDestWidth, nYDest + nDestHeight),
		CRect(0, 0, m_szExtent.cx, m_szExtent.cy));

	return;
}

// 绘画位图
void CSkinImage::DrawImage(CDC* pDC, int nXDest, int nYDest, int nDestWidth, int nDestHeight, int nXScr, int nYSrc, int nSrcWidth, int nSrcHeight)
{
	DrawImage(pDC, CRect(nXDest, nYDest, nXDest + nDestWidth, nYDest + nDestHeight),
		CRect(nXScr, nYSrc, nXScr + nSrcWidth, nYSrc + nSrcHeight));

	return;
}

// 绘画位图
void CSkinImage::DrawImage(CDC* pDC, const CRect& rcDest, CRect rcSrc)
{
	if (rcDest.left >= rcDest.right || rcDest.top >= rcDest.bottom)
		return;

	pDC->SetStretchBltMode(COLORONCOLOR);

	CDC BitmapDC;
	BitmapDC.CreateCompatibleDC(pDC);

	if (m_bAlpha)
	{
		if (PreMultiply())
		{
			BitmapDC.SelectObject(m_hBitmap);
			AlphaBlend(pDC->GetSafeHdc(), rcDest, BitmapDC, rcSrc);
		}
	}
	else if ((rcSrc.Width() == rcDest.Width()) && (rcSrc.Height() == rcDest.Height()))
	{
		BitmapDC.SelectObject(m_hBitmap);
		pDC->BitBlt(rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
			&BitmapDC, rcSrc.left, rcSrc.top, SRCCOPY);
	}
	else
	{
		BitmapDC.SelectObject(m_hBitmap);
		pDC->StretchBlt(rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
			&BitmapDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), SRCCOPY);
	}

	BitmapDC.DeleteDC();
}

BOOL CSkinImage::IsValid() const
{
	return (m_hBitmap != NULL);
}

BOOL CSkinImage::IsAlphaImage() const
{
	return m_bAlpha;
}

int CSkinImage::GetHeight() const
{
	return m_szExtent.cy;
}

int CSkinImage::GetWidth() const
{
	return m_szExtent.cx;
}

CSize CSkinImage::GetExtent() const
{
	if (m_hBitmap)
	{
		BITMAP bmpinfo;
		if (::GetObject(m_hBitmap, sizeof(bmpinfo), &bmpinfo))
		{
			return CSize((int)bmpinfo.bmWidth, (int)bmpinfo.bmHeight);
		}
	}
	return 0;
}

HBITMAP CSkinImage::GetBitmap() const
{
	return m_hBitmap;
}

BOOL CSkinImage::GetBitmapPixel(CPoint pt, COLORREF& clrPixel)
{
	if (pt.x < 0 || pt.x >= m_szExtent.cx ||
		pt.y < 0 || pt.y >= m_szExtent.cy)
		return FALSE;

	PreMultiply();

	LPDWORD lprgbBitmap = (LPDWORD)m_pBits + m_szExtent.cx * (m_szExtent.cy - pt.y - 1);
	clrPixel = lprgbBitmap[pt.x];

	return TRUE;
}

// 创建区域
bool CSkinImage::CreateBitmapRegion(CRgn& BitmapRgn, COLORREF crTransColor)
{
	// 创建区域
	CreateBitmapRegion(BitmapRgn, 0, 0, GetWidth(), GetHeight(), crTransColor);

	return true;
}

// 创建区域
bool CSkinImage::CreateBitmapRegion(CRgn& BitmapRgn, int nXSrcPos, int nYSrcPos, int nSrcWidth, int nSrcHeight, COLORREF crTransColor)
{
	// 判断状态
	ASSERT(IsValid());
	if (IsValid() == false) return false;

	// 参数调整
	int nImageWidht = GetWidth();
	int nImageHeight = GetHeight();
	if ((nXSrcPos + nSrcWidth) > nImageWidht) nSrcWidth = nImageWidht - nXSrcPos;
	if ((nYSrcPos + nSrcHeight) > nImageHeight) nSrcHeight = nImageHeight - nYSrcPos;

	// 创建对象
	CDC MemDC;
	MemDC.CreateCompatibleDC(NULL);
	BitmapRgn.DeleteObject();
	BitmapRgn.CreateRectRgn(0, 0, 0, 0);

	// 创建位图
	HBITMAP hBitmapConsult = Create32BPPDIBSection(NULL, nSrcWidth, nSrcHeight);

	// 调整位图
	BITMAP ImageInfo;
	GetObject(hBitmapConsult, sizeof(ImageInfo), &ImageInfo);

	// 绘画位图
	MemDC.SelectObject(hBitmapConsult);
	DrawImage(&MemDC, 0, 0, nSrcWidth, nSrcHeight, nXSrcPos, nYSrcPos, nSrcWidth, nSrcHeight);

	if (m_bAlpha)
	{
		BYTE* psrc = (BYTE*)ImageInfo.bmBits;
		for (int nYPos = 0; nYPos < abs(ImageInfo.bmHeight); nYPos++)
		{
			int nLastEmpty = -1;
			int nLastSolid = -1;

			for (int nXPos = 0; nXPos < ImageInfo.bmWidth;)
			{
				while ((nXPos < ImageInfo.bmWidth) && (psrc[3] == 0))
				{
					nXPos ++, psrc += 4;
				}
				int nLeft = nXPos;
				if (nXPos < ImageInfo.bmWidth)
				{
					while ((nXPos < ImageInfo.bmWidth) && (psrc[3] > 0))
					{
						nXPos ++, psrc += 4;
					}
					int nRight = nXPos;
					// 找到一个RECT
					int nTop = ImageInfo.bmHeight - nYPos-1;
					int nBottom = nTop+1;

					CRgn RgnUnite;
					RgnUnite.CreateRectRgn(nLeft, nTop, nRight, nBottom);
					// 合并区域
					CombineRgn(BitmapRgn, RgnUnite, BitmapRgn, RGN_OR);
				}
			}
		}
	}
	else
	{
		while ((ImageInfo.bmWidthBytes % 4) != 0) ImageInfo.bmWidthBytes++;

		// 获取属性
		BYTE cbRTranColor = GetRValue(crTransColor);
		BYTE cbGTranColor = GetGValue(crTransColor);
		BYTE cbBTranColor = GetBValue(crTransColor);
		BYTE* pcbImageBitIndex = (BYTE*)ImageInfo.bmBits + (ImageInfo.bmHeight - 1) * ImageInfo.bmWidthBytes;

		// 创建区域
		for (int nYPos = 0; nYPos < ImageInfo.bmHeight; nYPos++)
		{
			for (int nXPos = 0; nXPos < ImageInfo.bmWidth; nXPos++)
			{
				// 变量定义
				int nXStartPos = nXPos;

				// 透明判断
				do
				{
					COLORREF crImageColor = *(((LONG*)pcbImageBitIndex) + nXPos);
					if ((cbRTranColor == GetRValue(crImageColor)) && (cbGTranColor == GetGValue(crImageColor)) && (cbBTranColor == GetBValue(crImageColor))) break;
				} while ((++nXPos) < ImageInfo.bmWidth);

				// 创建区域
				if ((nXPos - nXStartPos) > 0)
				{
					// 创建区域
					CRgn RgnUnite;
					RgnUnite.CreateRectRgn(nXStartPos, nYPos, nXPos, nYPos + 1);

					// 合并区域
					CombineRgn(BitmapRgn, RgnUnite, BitmapRgn, RGN_OR);
				}
			}

			// 设置位置
			pcbImageBitIndex -= ImageInfo.bmWidthBytes;
		}
	}

	::DeleteObject(hBitmapConsult);
	return true;
}

BOOL CSkinImage::IsPngBitmapFile(LPCTSTR pszFileName)
{
	HANDLE hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	DWORD dwBytesRead;

	BYTE fileHeader[4];
	BYTE png_signature[4] = {137, 80, 78, 71};

	if (!ReadFile(hFile, &fileHeader, sizeof(fileHeader), &dwBytesRead, 0) || dwBytesRead != sizeof(fileHeader))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	BOOL bResult = memcmp(&fileHeader, &png_signature, 4) == 0;

	CloseHandle(hFile);

	return bResult;
}

BOOL CSkinImage::IsPngBitmapResource(HMODULE hModule, LPCTSTR lpBitmapName)
{
	BYTE png_signature[4] = {137, 80, 78, 71};

	HRSRC hResource = ::FindResource(hModule, lpBitmapName, _T("PNG"));

	if (hResource == NULL)
		return FALSE;

	HGLOBAL hGlobal = LoadResource(hModule, hResource);
	if (hGlobal == NULL)
		return FALSE;

	LPBYTE pBitmapInfoHeader = (LPBYTE)::LockResource(hGlobal);
	BOOL bPngBitmap = memcmp(pBitmapInfoHeader, &png_signature, 4) == 0;

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return (bPngBitmap);
}

BOOL CSkinImage::IsPngBitmapMemory(BYTE* pBuffer, DWORD dwSize)
{
	if (pBuffer == NULL || dwSize == 0)
		return FALSE;

	BYTE png_signature[4] = {137, 80, 78, 71};

	BOOL bPngBitmap = memcmp(pBuffer, &png_signature, 4) == 0;

	return (bPngBitmap);
}

BOOL CSkinImage::IsAlphaBitmapFile(LPCTSTR pszFileName)
{
	HANDLE hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	DWORD dwBytesRead;

	BITMAPFILEHEADER fileHeader;

	if (!ReadFile(hFile, &fileHeader, sizeof(BITMAPFILEHEADER), &dwBytesRead, 0) || dwBytesRead != sizeof(BITMAPFILEHEADER))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	BITMAPINFOHEADER infoHeader;

	if (!ReadFile(hFile, &infoHeader, sizeof(BITMAPINFOHEADER), &dwBytesRead, 0) || dwBytesRead != sizeof(BITMAPINFOHEADER))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	BOOL bResult = infoHeader.biBitCount == 32;

	CloseHandle(hFile);

	return bResult;
}

BOOL CSkinImage::IsAlphaBitmapResource(HMODULE hModule, LPCTSTR lpBitmapName)
{
	HRSRC hResource = ::FindResource(hModule, lpBitmapName, RT_BITMAP);

	if (hResource == NULL)
		return FALSE;

	HGLOBAL hGlobal = LoadResource(hModule, hResource);
	if (hGlobal == NULL)
		return FALSE;

	LPBITMAPINFOHEADER pBitmapInfoHeader = (LPBITMAPINFOHEADER)::LockResource(hGlobal);
	ASSERT(pBitmapInfoHeader != NULL);
	if (!pBitmapInfoHeader)
		return FALSE;

	BOOL bAlpahBitmap = pBitmapInfoHeader->biBitCount == 32;
	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return (bAlpahBitmap);
}

BOOL CSkinImage::IsAlphaBitmapMemory(BYTE* pBuffer, DWORD dwSize)
{
	if (pBuffer == NULL || dwSize == 0)
		return FALSE;

	LPBITMAPINFOHEADER pBitmapInfoHeader = (LPBITMAPINFOHEADER)pBuffer;
	ASSERT(pBitmapInfoHeader != NULL);
	if (!pBitmapInfoHeader)
		return FALSE;

	BOOL bAlpahBitmap = pBitmapInfoHeader->biBitCount == 32;

	return (bAlpahBitmap);
}

BOOL CSkinImage::GetBitmapBits(CDC& dcSrc, HBITMAP hBitmap, PBITMAPINFO& pBitmapInfo, LPVOID& pBits, UINT& nSize)
{
	if (hBitmap == 0)
		return FALSE;

	BITMAPINFO  bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);


	if (GetDIBits(dcSrc, hBitmap, 0, 0, NULL, (BITMAPINFO*)&bmi, DIB_RGB_COLORS) == 0)
		return FALSE;

	if (bmi.bmiHeader.biBitCount != 32)
		return FALSE;

	nSize = bmi.bmiHeader.biHeight * bmi.bmiHeader.biWidth * 4;
	pBits = (PBYTE)malloc(nSize);
	if (pBits == NULL)
		return FALSE;

	if ((pBitmapInfo = (PBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER) + 3 * sizeof(COLORREF))) == NULL)
	{
		free(pBits);
		return FALSE;
	}

	memcpy(pBitmapInfo, &bmi, sizeof(BITMAPINFOHEADER));

	if (GetDIBits(dcSrc, hBitmap, 0, bmi.bmiHeader.biHeight, pBits, pBitmapInfo, DIB_RGB_COLORS) == NULL)
	{
		free(pBits);
		free(pBitmapInfo);
		return FALSE;
	}
	return TRUE;
}

HBITMAP CSkinImage::PreMultiplyAlphaBitmap(HBITMAP hBitmap, BOOL* pbAlpha, LPBYTE* lpBits)
{
	if (lpBits) *lpBits = NULL;

	CDC dcSrc;
	dcSrc.CreateCompatibleDC(NULL);

	PBYTE pBitsSrc = 0;
	PBITMAPINFO pBitmapInfo = 0;

	HBITMAP hBitmapAlpha = 0;

	TRY
	{
		UINT nSize;
		if (!GetBitmapBits(dcSrc, hBitmap, pBitmapInfo, (LPVOID&)pBitsSrc, nSize))
			return 0;

		BYTE* pBitsDest = NULL;

		hBitmapAlpha = CreateDIBSection(dcSrc, pBitmapInfo, DIB_RGB_COLORS, (void**)&pBitsDest, NULL, 0);
		if (pBitsDest == NULL || hBitmapAlpha == NULL)
			AfxThrowMemoryException();

		memcpy(pBitsDest, pBitsSrc, nSize);

		BOOL bAlpha0Found = FALSE;

		BYTE* pBitsI = pBitsDest;
		UINT nCount = nSize / 4;

		for (UINT i = 0; i < nCount; i++)
		{
			int nAlpha = pBitsI[3];
			pBitsI[0] = BYTE(pBitsI[0] * nAlpha / 255);
			pBitsI[1] = BYTE(pBitsI[1] * nAlpha / 255);
			pBitsI[2] = BYTE(pBitsI[2] * nAlpha / 255);

			if (pbAlpha)
			{
				if (nAlpha == 0)
					bAlpha0Found = TRUE;

				if ((nAlpha != 255 && nAlpha != 0) || (nAlpha == 255 && bAlpha0Found) || (nAlpha == 255 && *pbAlpha == -1))
					*pbAlpha = TRUE;
			}
			pBitsI += 4;
		}

		if (pbAlpha && (*pbAlpha == FALSE))
		{
			memcpy(pBitsDest, pBitsSrc, nSize);
		}

		if (lpBits)
		{
			*lpBits = pBitsDest;
		}

	}
	CATCH (CMemoryException, e)
	{
		TRACE(_T("Failed -- Memory exception thrown."));
	}
	END_CATCH

	if (pBitsSrc)
	{
		free(pBitsSrc);
		pBitsSrc = NULL;
	}
	if (pBitmapInfo)
	{
		free(pBitmapInfo);
		pBitmapInfo = NULL;
	}

	return hBitmapAlpha;
}

HBITMAP CSkinImage::LoadAlphaBitmap(UINT nIDResource)
{
	return LoadAlphaBitmap(AfxFindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_BITMAP), MAKEINTRESOURCE(nIDResource));
}

HBITMAP CSkinImage::LoadAlphaBitmap(HMODULE hModule, LPCTSTR lpszResource)
{
	HRSRC hResource = ::FindResource(hModule, lpszResource, RT_BITMAP);
	if (hResource == NULL)
		return NULL;

	HGLOBAL hGlobal = LoadResource(hModule, hResource);
	if (hGlobal == NULL)
		return NULL;

	LPBITMAPINFO pResourceInfo = (LPBITMAPINFO)::LockResource(hGlobal);
	ASSERT(pResourceInfo != NULL);
	if (!pResourceInfo)
		return NULL;

	int biSizeImage = pResourceInfo->bmiHeader.biHeight * pResourceInfo->bmiHeader.biWidth * 4;

	HBITMAP hbmResult = NULL;

	if (pResourceInfo->bmiHeader.biBitCount == 32 &&
		SizeofResource(hModule, hResource) >= int(biSizeImage + sizeof(BITMAPINFOHEADER)))
	{
		CDC dcSrc;
		dcSrc.CreateCompatibleDC(NULL);

		PBITMAPINFO pBitmapInfo = (PBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER) + sizeof(COLORREF) * 3);
		ASSERT(pBitmapInfo != NULL);
		if (!pBitmapInfo)
			return NULL;

		memcpy(pBitmapInfo, &pResourceInfo->bmiHeader, sizeof(BITMAPINFOHEADER));
		pBitmapInfo->bmiHeader.biSizeImage = biSizeImage;

		BYTE* pDestBits = NULL;
		HBITMAP hBmp = CreateDIBSection(dcSrc, pBitmapInfo, DIB_RGB_COLORS, (void**)&pDestBits, NULL, 0);

		if (hBmp && pDestBits)
		{
			memcpy(pDestBits, &pResourceInfo->bmiColors, biSizeImage);
			hbmResult = hBmp;
		}
		if (pBitmapInfo)
		{
			free(pBitmapInfo);
			pBitmapInfo = NULL;
		}
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return hbmResult;

}

HBITMAP CSkinImage::LoadBitmapFromFile(LPCTSTR lpszFileName, BOOL* lbAlphaBitmap, BitmapFormat bf)
{
	switch (bf)
	{
	case BF_BMP:
		{
			BOOL bAlphaBitmap = IsAlphaBitmapFile(lpszFileName);

			HBITMAP hBmp = (HBITMAP)LoadImage(0, lpszFileName,
				IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | (bAlphaBitmap ? LR_CREATEDIBSECTION : 0) | LR_LOADFROMFILE);

			if (hBmp)
			{
				if (lbAlphaBitmap)
				{
					*lbAlphaBitmap = bAlphaBitmap;
				}
				return hBmp;
			}
			break;
		}
	case BF_PNG:
		{
			CBitmapPng bmp;
			if (!bmp.LoadFromFile(lpszFileName))
				goto load1;

			if (lbAlphaBitmap)
			{
				*lbAlphaBitmap = bmp.IsAlpha();
			}
			return (HBITMAP)bmp.Detach();
			break;
		}
	case BF_OTHER:
		{
			goto load2;
		}
	}

	BOOL bPngBitmap = IsPngBitmapFile(lpszFileName);

	if (bPngBitmap)
	{
		CBitmapPng bmp;
		if (!bmp.LoadFromFile(lpszFileName))
			return NULL;

		if (lbAlphaBitmap)
		{
			*lbAlphaBitmap = bmp.IsAlpha();
		}
		return (HBITMAP)bmp.Detach();
	}

load1:
	BOOL bAlphaBitmap = IsAlphaBitmapFile(lpszFileName);

	HBITMAP hBmp = (HBITMAP)LoadImage(0, lpszFileName,
		IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | (bAlphaBitmap ? LR_CREATEDIBSECTION : 0) | LR_LOADFROMFILE);

	if (hBmp)
	{
		if (lbAlphaBitmap)
		{
			*lbAlphaBitmap = bAlphaBitmap;
		}
		return hBmp;
	}

load2:
	LPPICTURE pPict = NULL;

	if (OleLoadPicturePath((LPOLESTR)CT2W(lpszFileName), NULL, 0, 0, IID_IPicture, (LPVOID*)&pPict) == S_OK)
	{
		CDC dc;
		dc.CreateCompatibleDC(NULL);

		long hmWidth;
		long hmHeight;

		pPict->get_Width(&hmWidth);
		pPict->get_Height(&hmHeight);

		int cx = MulDiv(dc.GetDeviceCaps(LOGPIXELSX), (int)hmWidth, 2540);
		int cy = MulDiv(dc.GetDeviceCaps(LOGPIXELSY), (int)hmHeight, 2540);

		HBITMAP hbmpImage = Create32BPPDIBSection(NULL, cx, cy);

		HGDIOBJ hOldBitmap = ::SelectObject(dc, hbmpImage);
		dc.FillSolidRect(0, 0, cx, cy, GetSysColor(COLOR_3DFACE));

		pPict->Render(dc, 0, 0, cx, cy, 0, hmHeight-1, hmWidth, -hmHeight, 0);

		::SelectObject(dc, hOldBitmap);

		pPict->Release();

		return hbmpImage;
	}

	return NULL;
}

HBITMAP CSkinImage::LoadBitmapFromResource(HMODULE hModule, LPCTSTR lpszResource, BOOL* lbAlphaBitmap, BitmapFormat bf)
{
	switch (bf)
	{
	case BF_BMP:
		{
			CBitmap bmpIcons;
			BOOL bAlphaBitmap = IsAlphaBitmapResource(hModule, lpszResource);

			if (lbAlphaBitmap)
			{
				*lbAlphaBitmap = bAlphaBitmap;
			}

			if (bAlphaBitmap)
			{
				return LoadAlphaBitmap(hModule, lpszResource);
			}

			return (HBITMAP)LoadImage(hModule, lpszResource, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
			break;
		}
	case BF_PNG:
		{
			CBitmapPng bmpIcons;

			HRSRC hResource = ::FindResource(hModule, lpszResource, _T("PNG"));

			if (!bmpIcons.LoadFromResource(hModule, hResource))
				goto load1;

			if (lbAlphaBitmap)
			{
				*lbAlphaBitmap = bmpIcons.IsAlpha();
			}

			return (HBITMAP)bmpIcons.Detach();
			break;
		}
	case BF_OTHER:
		{
			// 暂不支持
			return NULL;
		}
	}

	BOOL bPngBitmap = IsPngBitmapResource(hModule, lpszResource);
	if (bPngBitmap)
	{
		CBitmapPng bmpIcons;

		HRSRC hResource = ::FindResource(hModule, lpszResource, _T("PNG"));

		if (!bmpIcons.LoadFromResource(hModule, hResource))
			return NULL;

		if (lbAlphaBitmap)
		{
			*lbAlphaBitmap = bmpIcons.IsAlpha();
		}

		return (HBITMAP)bmpIcons.Detach();
	}

load1:
	CBitmap bmpIcons;
	BOOL bAlphaBitmap = IsAlphaBitmapResource(hModule, lpszResource);

	if (lbAlphaBitmap)
	{
		*lbAlphaBitmap = bAlphaBitmap;
	}

	if (bAlphaBitmap)
	{
		return LoadAlphaBitmap(hModule, lpszResource);
	}

	return (HBITMAP)LoadImage(hModule, lpszResource, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
}

HBITMAP CSkinImage::ConvertToBitmap(BYTE* pBuffer, DWORD dwSize)
{
	LPBITMAPINFO pResourceInfo = (LPBITMAPINFO)pBuffer;
	ASSERT(pResourceInfo != NULL);
	if (!pResourceInfo)
		return NULL;

	int biSizeImage = pResourceInfo->bmiHeader.biHeight * pResourceInfo->bmiHeader.biWidth * 4;

	HBITMAP hbmResult = NULL;

	if (pResourceInfo->bmiHeader.biBitCount == 32 &&
		dwSize >= int(biSizeImage + sizeof(BITMAPINFOHEADER)))
	{
		CDC dcSrc;
		dcSrc.CreateCompatibleDC(NULL);

		PBITMAPINFO pBitmapInfo = (PBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER) + sizeof(COLORREF) * 3);
		ASSERT(pBitmapInfo != NULL);
		if (!pBitmapInfo)
			return NULL;

		memcpy(pBitmapInfo, &pResourceInfo->bmiHeader, sizeof(BITMAPINFOHEADER));
		pBitmapInfo->bmiHeader.biSizeImage = biSizeImage;

		BYTE* pDestBits = NULL;
		HBITMAP hBmp = CreateDIBSection(dcSrc, pBitmapInfo, DIB_RGB_COLORS, (void**)&pDestBits, NULL, 0);

		if (hBmp && pDestBits)
		{
			memcpy(pDestBits, &pResourceInfo->bmiColors, biSizeImage);
			hbmResult = hBmp;
		}
		if (pBitmapInfo)
		{
			free(pBitmapInfo);
			pBitmapInfo = NULL;
		}
	}

	return hbmResult;
}

HBITMAP CSkinImage::LoadBitmapFromMemory(BYTE* pBuffer, DWORD dwSize, BOOL* lbAlphaBitmap, BitmapFormat bf)
{
	switch (bf)
	{
	case BF_BMP:
		{
			HBITMAP hBmpResult = ConvertToBitmap(pBuffer, dwSize);

			if (lbAlphaBitmap && hBmpResult)
			{
				*lbAlphaBitmap = TRUE;
			}

			return hBmpResult;
			break;
		}
	case BF_PNG:
		{
			CBitmapPng bmpIcons;

			if (!bmpIcons.LoadFromMemory(pBuffer, dwSize))
				goto load1;

			if (lbAlphaBitmap)
			{
				*lbAlphaBitmap = bmpIcons.IsAlpha();
			}

			return (HBITMAP)bmpIcons.Detach();
			break;
		}
	case BF_OTHER:
		{
			// 暂不支持
			return NULL;
		}
	}

	BOOL bPngBitmap = IsPngBitmapMemory(pBuffer, dwSize);
	if (bPngBitmap)
	{
		CBitmapPng bmpIcons;

		if (!bmpIcons.LoadFromMemory(pBuffer, dwSize))
			return NULL;

		if (lbAlphaBitmap)
		{
			*lbAlphaBitmap = bmpIcons.IsAlpha();
		}

		return (HBITMAP)bmpIcons.Detach();
	}

load1:

	HBITMAP hBmpResult = ConvertToBitmap(pBuffer, dwSize);

	if (lbAlphaBitmap && hBmpResult)
	{
		*lbAlphaBitmap = TRUE;
	}

	return hBmpResult;
}

BOOL CSkinImage::TransparentBlt(HDC hdcDest, const CRect& rcDest,HDC hdcSrc,
								const CRect& rcSrc, UINT crTransparent)
{
	if (SystemVersion()->IsWin2KOrGreater() && DrawHelpers()->m_pfnTransparentBlt)
	{
		return DrawHelpers()->m_pfnTransparentBlt(hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
			hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), crTransparent);
	}

	return McTransparentBlt(hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
		hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), crTransparent);
}

BOOL CSkinImage::AlphaBlend(HDC hdcDest, const CRect& rcDest, HDC hdcSrc, const CRect& rcSrc)
{
	if (DrawHelpers()->IsContextRTL(hdcDest) && SystemVersion()->IsWin9x())
	{
		return DoAlphaBlend(hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
			hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height());
	}

	if (DrawHelpers()->m_pfnAlphaBlend && (SystemVersion()->IsWin2KOrGreater() || (rcSrc.top == 0 && rcSrc.left == 0 && rcDest.top >= 0)))
	{
		BLENDFUNCTION bf;
		ZeroMemory(&bf, sizeof(BLENDFUNCTION));

		bf.AlphaFormat  = 0x01;
		bf.SourceConstantAlpha = 255;
		bf.BlendOp = AC_SRC_OVER;

		return DrawHelpers()->m_pfnAlphaBlend(hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
			hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), bf);

	}
	return DoAlphaBlend(hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
		hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height());
}

BOOL CSkinImage::AlphaBlend2(HDC hdcDest, const CRect& rcDest, HDC hdcSrc, const CRect& rcSrc, BYTE Transparency)
{
	if (DrawHelpers()->IsContextRTL(hdcDest) && SystemVersion()->IsWin9x())
	{
		return DoAlphaBlend(hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
			hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height());
	}

	if (DrawHelpers()->m_pfnAlphaBlend && (SystemVersion()->IsWin2KOrGreater() || (rcSrc.top == 0 && rcSrc.left == 0)))
	{
		BLENDFUNCTION bf;
		ZeroMemory(&bf, sizeof(BLENDFUNCTION));

		bf.AlphaFormat  = 0;
		bf.SourceConstantAlpha = Transparency;
		bf.BlendOp = AC_SRC_OVER;

		return DrawHelpers()->m_pfnAlphaBlend(hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
			hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), bf);

	}
	return DoAlphaBlend(hdcDest, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(),
		hdcSrc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height());
}

// Based on http://support.microsoft.com/kb/303916/en-us
HBITMAP CSkinImage::Create32BPPDIBSection(HDC hDC, int iWidth, int iHeight, LPBYTE* lpBits)
{
	BITMAPINFO bmi;
	HBITMAP hbm;
	LPBYTE pBits;

	// Initialize header to 0s.
	ZeroMemory(&bmi, sizeof(bmi));

	// Fill out the fields you care about.
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = iWidth;
	bmi.bmiHeader.biHeight = iHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	// Create the surface.
	hbm = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (LPVOID*)&pBits, NULL, 0);

	if (lpBits)
	{
		*lpBits = pBits;
	}

	return(hbm);
}

// Based on http://www.rsdn.ru/article/files/Functions/mctranspblt.xml
BOOL CSkinImage::McTransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest,
										int nWidthDest, int nHeightDest, HDC hdcSrc,
										int nXOriginSrc, int nYOriginSrc, int nWidthSrc,
										int nHeightSrc, UINT crTransparent)
{

	BOOL bResult = FALSE;

	if (!hdcDest || !hdcSrc)
		return FALSE;

	HDC hdcMask = NULL;
	HDC hdcTmpSrc = NULL;
	HBITMAP hbmTransMask = NULL;
	HBITMAP oldhbmTransMask = NULL;
	HBITMAP hbmTmpSrc = NULL;
	HBITMAP oldhbmTmpSrc = NULL;


	COLORREF OldBkColor = ::SetBkColor(hdcDest, RGB(255, 255, 255));
	COLORREF OldTextColor = ::SetTextColor(hdcDest, RGB(0, 0, 0));

	if ((hdcMask = ::CreateCompatibleDC(hdcDest)) == NULL)
	{
		goto ClearUp;
	}

	if ((hdcTmpSrc = ::CreateCompatibleDC(hdcSrc))==NULL)
	{
		goto ClearUp;
	}

	if ((hbmTmpSrc = ::CreateCompatibleBitmap(hdcDest,nWidthSrc,nHeightSrc))==NULL)
	{
		goto ClearUp;
	}

	oldhbmTmpSrc = (HBITMAP)::SelectObject(hdcTmpSrc,hbmTmpSrc);

	if (!::BitBlt(hdcTmpSrc, 0, 0, nWidthSrc, nHeightSrc, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY))
	{
		goto ClearUp;
	}

	if ((hbmTransMask = ::CreateBitmap(nWidthSrc, nHeightSrc, 1, 1, NULL)) == NULL)
	{
		goto ClearUp;
	}

	oldhbmTransMask = (HBITMAP)::SelectObject(hdcMask,hbmTransMask);

	::SetBkColor(hdcTmpSrc,crTransparent);
	if (!::BitBlt(hdcMask, 0, 0, nWidthSrc, nHeightSrc, hdcTmpSrc, 0, 0, SRCCOPY))
	{
		goto ClearUp;
	}

	if (crTransparent != RGB(0, 0, 0))
	{
		::SetBkColor(hdcTmpSrc, RGB(0, 0, 0));
		::SetTextColor(hdcTmpSrc, RGB(255, 255, 255));

		if (!::BitBlt(hdcTmpSrc, 0, 0, nWidthSrc, nHeightSrc, hdcMask, 0, 0, SRCAND))
		{
			goto ClearUp;
		}
	}

	if ((nWidthDest == nWidthSrc) && (nHeightDest == nHeightSrc))
	{
		if (!::BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthSrc, nHeightSrc, hdcMask, 0, 0, SRCAND))
		{
			goto ClearUp;
		}
		if (!::BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthSrc, nHeightSrc, hdcTmpSrc, 0, 0, SRCPAINT))
		{
			goto ClearUp;
		}
	}
	else
	{
		if (!::StretchBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcMask, 0, 0, nWidthSrc, nHeightSrc,SRCAND))
		{
			goto ClearUp;
		}
		if (!::StretchBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcTmpSrc, 0, 0,  nWidthSrc, nHeightSrc,SRCPAINT))
		{
			goto ClearUp;
		}
	}
	bResult = TRUE;

ClearUp:
	if (hdcMask)
	{
		if (oldhbmTransMask)
			::SelectObject(hdcMask,oldhbmTransMask);
		::DeleteDC(hdcMask);
	}

	if (hbmTmpSrc)
	{
		if (oldhbmTmpSrc)
			::SelectObject(hdcTmpSrc,oldhbmTmpSrc);
		::DeleteObject(hbmTmpSrc);
	}

	if (hdcTmpSrc)
		::DeleteDC(hdcTmpSrc);

	if (hbmTransMask)
		::DeleteObject(hbmTransMask);

	::SetBkColor(hdcDest, OldBkColor);
	::SetTextColor(hdcDest,OldTextColor);

	return bResult;
}

LPBYTE CSkinImage::PreMultiply()
{
	if (m_pBits != NULL)
		return m_pBits;

	if (m_hBitmap == 0)
		return NULL;

	LPBYTE pBits = NULL;

	HBITMAP hBitmapAlpha = PreMultiplyAlphaBitmap(m_hBitmap, NULL, &pBits);
	if (!hBitmapAlpha || (pBits == NULL))
		return NULL;

	if (m_hBitmap)
	{
		DeleteObject(m_hBitmap);
	}

	m_hBitmap = hBitmapAlpha;
	m_pBits = pBits;
	m_szExtent = GetExtent();

	return m_pBits;
}

// Based on http://support.microsoft.com/kb/303916/en-us
BOOL CSkinImage::BitmapsCompatible(LPBITMAP lpbm1, LPBITMAP lpbm2)
{
	if (lpbm1->bmBitsPixel != lpbm2->bmBitsPixel)
		return FALSE;

	if (lpbm1->bmPlanes != lpbm2->bmPlanes)
		return FALSE;

	if (lpbm1->bmWidth != lpbm2->bmWidth)
		return FALSE;

	if (lpbm1->bmHeight != lpbm2->bmHeight)
		return FALSE;

	return TRUE;
}

// Based on http://support.microsoft.com/kb/303916/en-us
BOOL CSkinImage::BlendImages(HBITMAP hbmSrc1, BOOL bRTL1, HBITMAP hbmSrc2, BOOL bRTL2, HBITMAP hbmDst)
{
	BITMAP bmSrc1, bmSrc2, bmDst;
	RGBQUAD *lprgbSrc1, *lprgbSrc2, *lprgbDst;
	DWORD dwWidthBytes;
	int x, y;

	// Get weighting value for second source image.

	// Get information about the surfaces you were passed.
	if (!GetObject(hbmSrc1, sizeof(BITMAP), &bmSrc1)) return FALSE;
	if (!GetObject(hbmSrc2, sizeof(BITMAP), &bmSrc2)) return FALSE;
	if (!GetObject(hbmDst,  sizeof(BITMAP), &bmDst))  return FALSE;

	// Make sure you have data that meets your requirements.
	if (!BitmapsCompatible(&bmSrc1, &bmSrc2)) return FALSE;
	if (!BitmapsCompatible(&bmSrc1, &bmDst))  return FALSE;
	if (bmSrc1.bmBitsPixel != 32) return FALSE;
	if (bmSrc1.bmPlanes != 1) return FALSE;
	if (!bmSrc1.bmBits || !bmSrc2.bmBits || !bmDst.bmBits) return FALSE;

	dwWidthBytes = bmDst.bmWidthBytes;

	// Initialize the surface pointers.
	lprgbSrc1 = (RGBQUAD*)bmSrc1.bmBits;
	lprgbSrc2 = (RGBQUAD*)bmSrc2.bmBits;
	lprgbDst  = (RGBQUAD*)bmDst.bmBits;

#define F(a)  BYTE(gbSrc1.##a + (255 - gbSrc1.rgbReserved) * gbSrc2.##a / 255)

	for (y = 0; y < bmDst.bmHeight; y++)
	{
		for (x = 0; x < bmDst.bmWidth; x++)
		{
			RGBQUAD& gbSrc1 = bRTL1 ? lprgbSrc1[bmDst.bmWidth - 1 - x] : lprgbSrc1[x];
			RGBQUAD& gbSrc2 = bRTL2 ? lprgbSrc2[bmDst.bmWidth - 1 - x] : lprgbSrc2[x];

			lprgbDst[x].rgbRed   = F(rgbRed);
			lprgbDst[x].rgbGreen = F(rgbGreen);
			lprgbDst[x].rgbBlue  = F(rgbBlue);
		}

		// Move to next scan line.
		lprgbSrc1 = (RGBQUAD *)((LPBYTE)lprgbSrc1 + dwWidthBytes);
		lprgbSrc2 = (RGBQUAD *)((LPBYTE)lprgbSrc2 + dwWidthBytes);
		lprgbDst  = (RGBQUAD *)((LPBYTE)lprgbDst  + dwWidthBytes);
	}

	return TRUE;
}

// Based on http://support.microsoft.com/kb/303916/en-us
BOOL CSkinImage::DoAlphaBlend(HDC hdcDest,                 // Handle to destination DC.
									int nXOriginDest,            // X-coord of upper-left corner.
									int nYOriginDest,            // Y-coord of upper-left corner.
									int nWidthDest,              // Destination width.
									int nHeightDest,             // Destination height.
									HDC hdcSrc,                  // Handle to source DC.
									int nXOriginSrc,             // X-coord of upper-left corner.
									int nYOriginSrc,             // Y-coord of upper-left corner.
									int nWidthSrc,               // Source width.
									int nHeightSrc              // Source height.
									)
{
	HDC      hdcSrc1 = NULL;
	HDC      hdcSrc2 = NULL;
	HBITMAP  hbmSrc1 = NULL, hbmOldSrc1 = NULL;
	HBITMAP  hbmSrc2 = NULL, hbmOldSrc2 = NULL;
	HBITMAP  hbmDst  = NULL;
	BOOL     bReturn = FALSE;
	BOOL     bRTLSrc    = DrawHelpers()->IsContextRTL(hdcSrc);
	BOOL     bRTLDest   = DrawHelpers()->IsContextRTL(hdcDest);

	// Create surfaces for sources and destination images.
	hbmSrc1 = CSkinImage::Create32BPPDIBSection(hdcDest, nWidthDest,nHeightDest);
	if (!hbmSrc1) goto HANDLEERROR;

	hbmSrc2 = CSkinImage::Create32BPPDIBSection(hdcDest, nWidthDest,nHeightDest);
	if (!hbmSrc2) goto HANDLEERROR;

	hbmDst  = CSkinImage::Create32BPPDIBSection(hdcDest, nWidthDest,nHeightDest);
	if (!hbmDst) goto HANDLEERROR;

	// Create HDCs to hold our surfaces.
	hdcSrc1 = CreateCompatibleDC(hdcSrc);
	if (!hdcSrc1) goto HANDLEERROR;

	hdcSrc2 = CreateCompatibleDC(hdcSrc);
	if (!hdcSrc2) goto HANDLEERROR;

	DrawHelpers()->SetContextRTL(hdcSrc2, FALSE);
	DrawHelpers()->SetContextRTL(hdcSrc1, FALSE);

	// Prepare the surfaces for drawing.
	hbmOldSrc1 = (HBITMAP)SelectObject(hdcSrc1, hbmSrc1);
	hbmOldSrc2 = (HBITMAP)SelectObject(hdcSrc2, hbmSrc2);
	SetStretchBltMode(hdcSrc1, COLORONCOLOR);
	SetStretchBltMode(hdcSrc2, COLORONCOLOR);


	// Capture a copy of the source area.
	if (!StretchBlt(hdcSrc1, 0,0,nWidthDest,nHeightDest,
		hdcSrc,  nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc,
		SRCCOPY))
		goto HANDLEERROR;


	// Capture a copy of the destination area.
	if (!BitBlt(hdcSrc2, 0, 0, nWidthDest, nHeightDest,
		hdcDest, nXOriginDest, nYOriginDest, SRCCOPY))
		goto HANDLEERROR;



	SelectObject(hdcSrc1, hbmOldSrc1); hbmOldSrc1 = NULL;
	SelectObject(hdcSrc2, hbmOldSrc2); hbmOldSrc2 = NULL;

	// Blend the two source areas to create the destination image.
	bReturn = BlendImages(hbmSrc1, bRTLSrc, hbmSrc2, bRTLDest, hbmDst);


	// Display the blended (destination) image to the target HDC.
	if (bReturn)
	{
		hbmOldSrc1 = (HBITMAP)SelectObject(hdcSrc1, hbmDst);

		BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
			hdcSrc1, 0,0, SRCCOPY | (bRTLDest ? NOMIRRORBITMAP : 0));

		SelectObject(hdcSrc1, hbmOldSrc1);
		hbmOldSrc1 = NULL;
	}

	// Clean up the rest of the objects you created.

HANDLEERROR:

	if (hbmOldSrc1) SelectObject(hdcSrc1, hbmOldSrc1);
	if (hbmOldSrc2) SelectObject(hdcSrc2, hbmOldSrc2);
	if (hdcSrc1) DeleteDC(hdcSrc1);
	if (hdcSrc2) DeleteDC(hdcSrc2);
	if (hbmSrc1) DeleteObject(hbmSrc1);
	if (hbmSrc2) DeleteObject(hbmSrc2);
	if (hbmDst) DeleteObject(hbmDst);

	return bReturn;
}