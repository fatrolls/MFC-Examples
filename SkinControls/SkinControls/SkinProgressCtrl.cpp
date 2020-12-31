
#include "stdafx.h"
#include "SkinProgressCtrl.h"

IMPLEMENT_DYNAMIC(CSkinProgressCtrl, CProgressCtrl)

BEGIN_MESSAGE_MAP(CSkinProgressCtrl, CProgressCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

CSkinProgressCtrl::CSkinProgressCtrl()
{
}

CSkinProgressCtrl::~CSkinProgressCtrl()
{
}

// 设置背景图
void CSkinProgressCtrl::SetProgressBackImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	ASSERT(pszFileName != NULL);
	if (pszFileName == NULL) return;

	m_ImageBack.DestroyImage();
	m_ImageBack.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageBack.IsValid());
}

// 设置背景图
void CSkinProgressCtrl::SetProgressBackImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	m_ImageBack.DestroyImage();
	m_ImageBack.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageBack.IsValid());
}

// 设置背景图
void CSkinProgressCtrl::SetProgressBackImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	m_ImageBack.DestroyImage();
	m_ImageBack.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageBack.IsValid());
}

// 设置进度图
void CSkinProgressCtrl::SetProgressImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	ASSERT(pszFileName != NULL);
	if (pszFileName == NULL) return;

	m_ImageProgress.DestroyImage();
	m_ImageProgress.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageProgress.IsValid());
}

// 设置进度图
void CSkinProgressCtrl::SetProgressImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	m_ImageProgress.DestroyImage();
	m_ImageProgress.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageProgress.IsValid());
}

// 设置进度图
void CSkinProgressCtrl::SetProgressImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	m_ImageProgress.DestroyImage();
	m_ImageProgress.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageProgress.IsValid());
}

// 对象附加到现有窗口
void CSkinProgressCtrl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	SetWindowRgn(NULL, FALSE);

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	HRGN hRgn = CreateRoundRectRgn(0, 0, rcWnd.Width(), rcWnd.Height(), 9, 9);
	SetWindowRgn(hRgn, TRUE);
	::DeleteObject(hRgn);

	return;
}

// 建立消息
int CSkinProgressCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	SetWindowRgn(NULL, FALSE);

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	HRGN hRgn = CreateRoundRectRgn(0, 0, rcWnd.Width(), rcWnd.Height(), 9, 9);
	SetWindowRgn(hRgn, TRUE);
	::DeleteObject(hRgn);

	return 0;
}

void CSkinProgressCtrl::OnPaint()
{
	CPaintDC dc(this); 
	BOOL bVertical = GetStyle() & PBS_VERTICAL;

	CRect rcClient;
	GetClientRect(&rcClient);

	m_ImageBack.DrawImage(&dc, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),
		0, 0, m_ImageBack.GetWidth(), m_ImageBack.GetHeight(), MASK_COLOR);

	CRect rcProgress(rcClient);
	int nStart = 0, nEnd = 0;
	GetRange(nStart, nEnd);
	int nRange = nEnd - nStart;
	int nPos = GetPos();

	int nPrg = 0;	
	if (!bVertical)
	{
		nPrg = (rcClient.Width() * nPos) / nRange;
		rcProgress.right = rcProgress.left + nPrg;

	}
	else
	{
		nPrg = (rcClient.Height() * nPos) / nRange;
		rcProgress.top = rcProgress.bottom - nPrg;
	}

	m_ImageProgress.DrawImage(&dc, rcProgress.left, rcProgress.top, rcProgress.Width(), rcProgress.Height(),
		0, 0, m_ImageProgress.GetWidth(), m_ImageProgress.GetHeight(), MASK_COLOR);

}

BOOL CSkinProgressCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CSkinProgressCtrl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	SetWindowRgn(NULL, FALSE);

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	HRGN hRgn = CreateRoundRectRgn(0, 0, rcWnd.Width(), rcWnd.Height(), 9, 9);
	SetWindowRgn(hRgn, TRUE);
	::DeleteObject(hRgn);
}