
#include "StdAfx.h"
#include <process.h>
#include "gifanimation.h"
#include "DrawHelpers.h"

// 构造函数
CGifAnimation::CGifAnimation()
{
	m_hThread = NULL;
	m_hWnd = NULL;
	
	m_hBitmap = NULL;
	m_hMemDC = NULL;

	m_hDispMemDC = NULL;
	m_hDispMemBM = NULL;
	m_hDispOldBM = NULL;
	m_bIsInitialized = FALSE;
	m_clrBackground = RGB(255,255,255);

	m_bExitThread = FALSE;
	m_bIsPlaying = FALSE;
	m_ptDraw.x = 0;
	m_ptDraw.y = 0;

	m_hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

// 析构函数
CGifAnimation::~CGifAnimation()
{
	UnLoad();
	CloseHandle(m_hExitEvent);
}

// 设置初始信息
void CGifAnimation::SetAnimationInfo(HWND hWnd, CPoint& ptDraw, COLORREF clrBackground)
{
	if (m_hWnd != NULL) return;
	ASSERT(hWnd != NULL);
	m_hWnd = hWnd;
	m_ptDraw = ptDraw;
	m_clrBackground = clrBackground;
	if (!m_bIsInitialized) PrepareDC();
}

// 播放
void CGifAnimation::Play()
{
	ASSERT(m_hWnd != NULL);
	if (m_hWnd == NULL) return;
	ASSERT(m_GifImage.IsNull() == false);
	if (m_GifImage.IsNull()) return;

	if (m_GifImage.GetFrameCount() > 1)
	{
		unsigned int nDummy;
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, _ThreadAnimation, this,
			CREATE_SUSPENDED, &nDummy);
		if (!m_hThread)
		{
			return;
		} 
		else 
		{
			ResumeThread(m_hThread);
		}
	} 
	else
	{
		HDC hDC = GetDC(m_hWnd);
		if (hDC)
		{
			m_GifImage.DrawImageFrame(CDC::FromHandle(hDC), m_ptDraw.x, m_ptDraw.y, 0);
			ReleaseDC(m_hWnd, hDC);
		}
	}

	return;	
}

void CGifAnimation::Draw(CDC* pDC)
{
	ASSERT(pDC);
	if (pDC == NULL) return;
	if (m_GifImage.IsNull()) return;

	::BitBlt(pDC->m_hDC, m_ptDraw.x, m_ptDraw.y, m_GifImage.GetWidth(), m_GifImage.GetHeight(),
		m_hMemDC, 0, 0, SRCCOPY);
}

// 停止
void CGifAnimation::Stop()
{
	m_bIsPlaying = FALSE;
	m_bExitThread = TRUE;
	SetEvent(m_hExitEvent);
	if (m_hThread)
	{
		WaitForSingleObject(m_hThread, 5000);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	ResetEvent(m_hExitEvent);
	m_bExitThread = FALSE;
}
// 加载动画
bool CGifAnimation::LoadFromFile(LPCTSTR pszFileName)
{
	bool bSuccess = m_GifImage.LoadFromFile(pszFileName);
	if (bSuccess && !m_bIsInitialized) PrepareDC();
	return bSuccess;
}

// 加载动画
bool CGifAnimation::LoadFromMemroy(BYTE* pcbData, LONG lDataSize)
{
	bool bSuccess = m_GifImage.LoadFromMemroy(pcbData, lDataSize);
	if (bSuccess && !m_bIsInitialized) PrepareDC();
	return bSuccess;
}

// 加载动画
bool CGifAnimation::LoadFromResource(LPCTSTR pszResourceName, LPCTSTR pszResourceType)
{
	bool bSuccess = m_GifImage.LoadFromResource(pszResourceName, pszResourceType);
	if (bSuccess && !m_bIsInitialized) PrepareDC();
	return bSuccess;
}

// 停止动画同时删除资源
void CGifAnimation::UnLoad()
{
	Stop();
	m_GifImage.DestroyImage();
	
	if (m_hMemDC)
	{
		SelectObject(m_hMemDC, m_hOldBitmap);
		::DeleteDC(m_hMemDC);
		::DeleteObject(m_hBitmap);
		m_hMemDC = NULL;
		m_hBitmap = NULL;
	};

	if (m_hDispMemDC)
	{
		SelectObject(m_hDispMemDC, m_hDispOldBM);
		::DeleteDC(m_hDispMemDC);
		::DeleteObject(m_hDispMemBM);
		m_hDispMemDC = NULL;
		m_hDispMemBM = NULL;
	};

	m_hThread = NULL;
	m_bExitThread = FALSE;
	m_bIsInitialized = FALSE;
}

BOOL CGifAnimation::IsPlaying() const
{
	return m_bIsPlaying;
}

BOOL CGifAnimation::PrepareDC()
{
	if (m_hWnd == NULL) return FALSE;
	if (m_GifImage.IsNull()) return FALSE;

	HDC hWinDC = ::GetDC(m_hWnd);
	if (!hWinDC) return FALSE;

	m_hMemDC = CreateCompatibleDC(hWinDC);
	if (!m_hMemDC) 
	{
		::ReleaseDC(m_hWnd, hWinDC);
		return FALSE;
	}

	m_hBitmap = CreateCompatibleBitmap(hWinDC, m_GifImage.GetWidth(), m_GifImage.GetHeight());
	if (!m_hBitmap) 
	{
		::ReleaseDC(m_hWnd, hWinDC);
		::DeleteDC(m_hMemDC);
		return FALSE;
	}

	m_hOldBitmap = reinterpret_cast<HBITMAP>(SelectObject(m_hMemDC, m_hBitmap));

	HBRUSH hBrush = CreateSolidBrush(m_clrBackground);
	if (hBrush)
	{
		RECT rect = { 0, 0, m_GifImage.GetWidth(), m_GifImage.GetHeight() };
		FillRect(m_hMemDC, &rect, hBrush);
		DeleteObject(hBrush);
	}

	::ReleaseDC(m_hWnd, hWinDC);
	m_bIsInitialized = TRUE;
	return TRUE;
}

UINT WINAPI CGifAnimation::_ThreadAnimation(LPVOID pParam)
{
	ASSERT(pParam);
	CGifAnimation* pPic = reinterpret_cast<CGifAnimation*>(pParam);

	pPic->m_bIsPlaying = TRUE;
	pPic->ThreadAnimation();
	pPic->m_bIsPlaying = FALSE;

	CloseHandle(pPic->m_hThread); 
	pPic->m_hThread = NULL;

	return 0;
}

void CGifAnimation::ThreadAnimation()
{
	tagGIFFrameInfo* pGIFFrameInfo = m_GifImage.GetCurrentFrame();
	if (pGIFFrameInfo == NULL) return;
	if (pGIFFrameInfo->nDisposal == 2)
	{
		HBRUSH hBrush = CreateSolidBrush(m_clrBackground);
		if (hBrush)
		{
			RECT rect = { pGIFFrameInfo->wXExcursion,
				pGIFFrameInfo->wYExcursion,
				pGIFFrameInfo->wXExcursion + pGIFFrameInfo->wImageWidth,
				pGIFFrameInfo->wYExcursion + pGIFFrameInfo->wImageHeight };
			FillRect(m_hMemDC, &rect, hBrush);
			DeleteObject(hBrush);
		}
	} 
	else if (m_hDispMemDC && (pGIFFrameInfo->nDisposal == 3))
	{
		BitBlt(m_hMemDC,
			pGIFFrameInfo->wXExcursion,
			pGIFFrameInfo->wYExcursion,
			pGIFFrameInfo->wImageWidth,
			pGIFFrameInfo->wImageHeight,
			m_hDispMemDC, 0, 0, SRCCOPY);
		SelectObject(m_hDispMemDC, m_hDispOldBM);
		DeleteDC(m_hDispMemDC); m_hDispMemDC = NULL;
		DeleteObject(m_hDispMemBM); m_hDispMemBM = NULL;
	};

	while (!m_bExitThread)
	{
		pGIFFrameInfo = m_GifImage.GetCurrentFrame();
		if (pGIFFrameInfo != NULL)
		{
			if (pGIFFrameInfo->nDisposal == 3)
			{
				m_hDispMemDC = CreateCompatibleDC(m_hMemDC);
				m_hDispMemBM = CreateCompatibleBitmap(m_hMemDC, pGIFFrameInfo->wImageWidth, pGIFFrameInfo->wImageHeight);

				if (m_hDispMemDC && m_hDispMemBM)
				{
					m_hDispOldBM = reinterpret_cast<HBITMAP>(SelectObject(m_hDispMemDC, m_hDispMemBM));
					BitBlt(m_hDispMemDC, 0, 0,
						pGIFFrameInfo->wImageWidth,
						pGIFFrameInfo->wImageHeight,
						m_hMemDC,
						pGIFFrameInfo->wXExcursion,
						pGIFFrameInfo->wYExcursion,
						SRCCOPY);
				}
			}

			long hmWidth;
			long hmHeight;
			pGIFFrameInfo->pIFramePicture->get_Width(&hmWidth);
			pGIFFrameInfo->pIFramePicture->get_Height(&hmHeight);
			pGIFFrameInfo->pIFramePicture->Render(m_hMemDC, 
				pGIFFrameInfo->wXExcursion,
				pGIFFrameInfo->wYExcursion,
				pGIFFrameInfo->wImageWidth,
				pGIFFrameInfo->wImageHeight,
				0, hmHeight, hmWidth, -hmHeight, NULL);

			::InvalidateRect(m_hWnd, CRect(m_ptDraw.x, m_ptDraw.y, m_ptDraw.x + m_GifImage.GetWidth(), m_ptDraw.y + m_GifImage.GetHeight()), FALSE);

			if (m_bExitThread) break;

			if (pGIFFrameInfo->nDelay < 5) 
				WaitForSingleObject(m_hExitEvent, 100);
			else
				WaitForSingleObject(m_hExitEvent, 10 * pGIFFrameInfo->nDelay);

			if (m_bExitThread) break;

			if (pGIFFrameInfo->nDisposal == 2)
			{
				HBRUSH hBrush = CreateSolidBrush(m_clrBackground);
				if (hBrush)
				{
					RECT rect = { pGIFFrameInfo->wXExcursion,
						pGIFFrameInfo->wYExcursion,
						pGIFFrameInfo->wXExcursion + pGIFFrameInfo->wImageWidth,
						pGIFFrameInfo->wYExcursion + pGIFFrameInfo->wImageHeight };
					FillRect(m_hMemDC, &rect, hBrush);
					DeleteObject(hBrush);
				}
			} 
			else if (m_hDispMemDC && (pGIFFrameInfo->nDisposal == 3))
			{
				BitBlt(m_hMemDC,
					pGIFFrameInfo->wXExcursion,
					pGIFFrameInfo->wYExcursion,
					pGIFFrameInfo->wImageWidth,
					pGIFFrameInfo->wImageHeight,
					m_hDispMemDC, 0, 0, SRCCOPY);
				SelectObject(m_hDispMemDC, m_hDispOldBM);
				DeleteDC(m_hDispMemDC); m_hDispMemDC = NULL;
				DeleteObject(m_hDispMemBM); m_hDispMemBM = NULL;
			}
		}

		m_GifImage.SetFrameIndex(m_GifImage.GetCurrentIndex() + 1);
		if (m_GifImage.GetCurrentIndex() == 0)
		{
			HBRUSH hBrush = CreateSolidBrush(m_clrBackground);
			if (hBrush)
			{
				RECT rect = { 0, 0, m_GifImage.GetWidth(), m_GifImage.GetHeight() };
				FillRect(m_hMemDC, &rect, hBrush);
				DeleteObject(hBrush);
			}
		}
	}
}
