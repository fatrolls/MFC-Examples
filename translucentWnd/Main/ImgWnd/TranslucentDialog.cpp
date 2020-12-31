#include "stdafx.h"
#include "TranslucentDialog.h"
#include <algorithm>



CTranslucentDialog::CTranslucentDialog(UINT nID, const wchar_t* wszFile, CImgWnd* pImgWnd, CWnd* pParent/*=NULL*/)
: CDialog(nID, pParent)
{
	assert(pImgWnd != NULL);

	m_pImage = Gdiplus::Image::FromFile(wszFile);
	m_pImgWnd = pImgWnd;
	m_bEnableDrag = true;
	m_bCenterAligned = true;
}

CTranslucentDialog::~CTranslucentDialog()
{
	Gdiplus::DllExports::GdipFree(m_pImage);
	m_pImage = NULL;
}

BEGIN_MESSAGE_MAP(CTranslucentDialog, CDialog)
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
//	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void CTranslucentDialog::SetEnableDrag(bool bEnableDrag)
{
	m_bEnableDrag = bEnableDrag;
}

void CTranslucentDialog::SetCenterAligned(bool bCenterAligned)
{
	m_bCenterAligned = bCenterAligned;
}

void CTranslucentDialog::RegisterTranslucentWnd(CTranslucentWnd* translucentWnd)
{
	translucentWnd->SetRenderListener(this);
	m_translucentWndList.push_back(translucentWnd);
}

void CTranslucentDialog::UnregisterTranslucentWnd(CTranslucentWnd* translucentWnd)
{
	translucentWnd->SetRenderListener(NULL);

	TranslucentWndList::iterator it = std::find(m_translucentWndList.begin(), m_translucentWndList.end(), translucentWnd);
	if (it != m_translucentWndList.end())
		m_translucentWndList.erase(it);
}

BOOL CTranslucentDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//RECT rc;
	//GetWindowRect(&rc);

	// must be WS_POPUP
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	VERIFY(dwStyle & WS_POPUP);
	VERIFY(!(dwStyle & WS_CHILD));

	m_BlendInfo.BlendOp = 0;
	m_BlendInfo.BlendFlags = 0;
	m_BlendInfo.AlphaFormat = 1;
	m_BlendInfo.SourceConstantAlpha = 255;//AC_SRC_ALPHA

	UpdateView();

	return TRUE;
}

BOOL CTranslucentDialog::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CTranslucentDialog::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	if (m_pImgWnd != NULL)
		::SetWindowPos(m_pImgWnd->GetSafeHwnd(), NULL, x, y, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
}

void CTranslucentDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (m_pImgWnd != NULL)
		::SetWindowPos(m_pImgWnd->GetSafeHwnd(), NULL, 0, 0, cx, cy, SWP_NOZORDER|SWP_NOMOVE);
}

int CTranslucentDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Must be overlapped
//	VERIFY((lpCreateStruct->style & WS_POPUP) == 0);
//	VERIFY((lpCreateStruct->style & WS_CHILD) == 0);
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, WS_EX_LAYERED);

	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pImgWnd->DoCreate();

	ModifyStyle(WS_CAPTION, WS_POPUP, 0);

	return 0;
}

void CTranslucentDialog::UpdateView()
{
	SIZE sizeWindow = { m_pImage->GetWidth(), m_pImage->GetHeight()};

	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if ((dwExStyle & 0x80000) != 0x80000)
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle | 0x80000);

	HDC hDC = ::GetDC(m_hWnd);
	HDC hdcMemory = CreateCompatibleDC(hDC);

	HBITMAP hBitMap = CreateCompatibleBitmap(hDC, sizeWindow.cx, sizeWindow.cy);
	::SelectObject(hdcMemory, hBitMap);

	RECT rcWindow;
	GetWindowRect(&rcWindow);

	BITMAPINFOHEADER stBmpInfoHeader = { 0 };   
	int nBytesPerLine = ((sizeWindow.cx * 32 + 31) & (~31)) >> 3;
	stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
	stBmpInfoHeader.biWidth = sizeWindow.cx;   
	stBmpInfoHeader.biHeight = sizeWindow.cy;   
	stBmpInfoHeader.biPlanes = 1;   
	stBmpInfoHeader.biBitCount = 32;   
	stBmpInfoHeader.biCompression = BI_RGB;   
	stBmpInfoHeader.biClrUsed = 0;   
	stBmpInfoHeader.biSizeImage = nBytesPerLine * sizeWindow.cy;   

	PVOID pvBits = NULL;   
	HBITMAP hbmpMem = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, &pvBits, NULL, 0);
	ASSERT(hbmpMem != NULL);
	memset( pvBits, 0, sizeWindow.cx * 4 * sizeWindow.cy);
	if(hbmpMem)   
	{   
		HGDIOBJ hbmpOld = ::SelectObject( hdcMemory, hbmpMem);

		//POINT ptWinPos = { m_rcWindow.left, m_rcWindow.top };
		POINT ptWinPos = { rcWindow.left, rcWindow.top };
		Gdiplus::Graphics graph(hdcMemory);
		graph.SetSmoothingMode(Gdiplus::SmoothingModeNone);

		graph.DrawImage(m_pImage, 0, 0, sizeWindow.cx, sizeWindow.cy);

		TranslucentWndList::const_iterator it;
		for (it = m_translucentWndList.begin(); it != m_translucentWndList.end(); ++it)
		{
			CTranslucentWnd* translucentWnd = *it;
			if (translucentWnd->IsVisible())
				translucentWnd->Render(graph);
		}

		HMODULE hFuncInst = LoadLibrary(_T("User32.DLL"));
		typedef BOOL (WINAPI *MYFUNC)(HWND, HDC, POINT*, SIZE*, HDC, POINT*, COLORREF, BLENDFUNCTION*, DWORD);          
		MYFUNC UpdateLayeredWindow;
		UpdateLayeredWindow = (MYFUNC)::GetProcAddress(hFuncInst, "UpdateLayeredWindow");
		POINT ptSrc = { 0, 0};
		UpdateLayeredWindow(m_hWnd, hDC, &ptWinPos, &sizeWindow, hdcMemory, &ptSrc, 0, &m_BlendInfo, 2);

		graph.ReleaseHDC(hdcMemory);
		::SelectObject( hdcMemory, hbmpOld);   
		::DeleteObject(hbmpMem); 
	}

	::DeleteDC(hdcMemory);
	::DeleteDC(hDC);
}

void CTranslucentDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bEnableDrag)
	{
		::SendMessage( GetSafeHwnd(), WM_SYSCOMMAND, 0xF012, 0);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CTranslucentDialog::OnRenderEvent(CTranslucentWnd* translucentWnd)
{
	UpdateView();
}
