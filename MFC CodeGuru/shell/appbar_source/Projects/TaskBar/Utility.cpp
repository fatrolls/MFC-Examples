// Utility.cpp: implementation of the CUtility class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Utility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtility::CUtility()
{
    m_iSlideHide = 400;
    m_iSlideShow = 200;
}

CUtility::~CUtility()
{

}

void CUtility::SlideWindow(HWND hwnd, LPRECT prc)
{
	RECT rcOld;
	RECT rcNew;
	int x, y, dx, dy, dt, t, t0;
	BOOL fShow;
	HANDLE hThreadMe;
	int priority;

	rcNew = *prc;

	if ((m_iSlideShow > 0) && (m_iSlideHide > 0))	
	{
		GetWindowRect(hwnd, &rcOld);

		fShow = (rcNew.bottom - rcNew.top) > (rcOld.bottom - rcOld.top) ||
				(rcNew.right - rcNew.left) > (rcOld.right - rcOld.left);

		dx = (rcNew.right - rcOld.right) + (rcNew.left - rcOld.left);
		dy = (rcNew.bottom - rcOld.bottom) + (rcNew.top - rcOld.top);

		if (fShow)
		{
			rcOld = rcNew;
			OffsetRect(&rcOld, -dx, -dy);
			SetWindowPos(hwnd, NULL, rcOld.left, rcOld.top,
					rcOld.right - rcOld.left, rcOld.bottom - rcOld.top,
					SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME);

			dt = m_iSlideShow;
		}
		else
		{
			dt = m_iSlideHide;
		}

		hThreadMe = GetCurrentThread();
		priority = GetThreadPriority(hThreadMe);
		SetThreadPriority(hThreadMe, THREAD_PRIORITY_HIGHEST);

		t0 = GetTickCount();
		while ((t = GetTickCount()) < t0 + dt)
		{
			x = rcOld.left + dx * (t - t0) / dt;
			y = rcOld.top + dy * (t - t0) / dt;

			SetWindowPos(hwnd, NULL, x, y, 0, 0,
						 SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
			if (fShow)
				UpdateWindow(hwnd);
			else
				UpdateWindow(GetDesktopWindow());
		}

		SetThreadPriority(hThreadMe, priority);
	}

	SetWindowPos(hwnd, NULL, rcNew.left, rcNew.top,
				 rcNew.right - rcNew.left, rcNew.bottom - rcNew.top,
				 SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME);

}
