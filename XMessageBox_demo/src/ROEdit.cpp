// ROEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ROEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable : 4996)			// disable bogus deprecation warning

/////////////////////////////////////////////////////////////////////////////
// CROEdit

BEGIN_MESSAGE_MAP(CROEdit, CEdit)
	//{{AFX_MSG_MAP(CROEdit)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CROEdit::CROEdit()
{
	m_brush.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
}

CROEdit::~CROEdit()
{
	if (m_brush.GetSafeHandle())
		m_brush.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CROEdit message handlers

HBRUSH CROEdit::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/) 
{
	return (HBRUSH)m_brush; //GetStockObject(WHITE_BRUSH);
	//return NULL;
}

void CROEdit::SetWindowText(LPCTSTR lpszString)
{
	CRect rect;
	GetClientRect(&rect);

	if (GetStyle() & WS_HSCROLL)
	{
		// not wrapped, so see if we can dispense with horz scroll bar

		CDC *pDC = GetDC();

		if (pDC)
		{
			CFont *pFont = GetParent()->GetFont();
			CFont *pOldFont = pDC->SelectObject(pFont);
			int nMaxExtent = 0;
			TCHAR *cp = (TCHAR *) lpszString;
			TCHAR buf[500];
			CString s = _T("");
			while (cp)
			{
				TCHAR *cp1 = cp;
				if (*cp1 == _T('\n'))
					cp1 += 1;
				cp = _tcschr(cp, _T('\r'));
				if (cp)
				{
					int len = cp - cp1;
					cp += 1;
					int n = sizeof(buf)/sizeof(TCHAR);
					if (len >= n)
						len = n-1;
					_tcsncpy(buf, cp1, len);
					buf[len] = 0;
					s = buf;
					s.Replace(_T("\t"), _T("  "));
					CSize size = pDC->GetTextExtent(buf);
					if (size.cx > nMaxExtent)
						nMaxExtent = size.cx;
					//TRACE(_T("size.cx=%d  buf=<%s>\n"), size.cx, buf);
				}
			}

			//TRACE(_T("nMaxExtent=%d\n"), nMaxExtent);

			int w = rect.Width();

			if (GetStyle() & WS_VSCROLL)
				w -= ::GetSystemMetrics(SM_CXVSCROLL);
			//TRACE(_T("w=%d\n"), w);

			if (nMaxExtent < w)
			{
				// ok to remove horz scrollbar
				ModifyStyle(WS_HSCROLL, 0);
			}

			if (pOldFont)
				pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
		}
	}

	CEdit::SetWindowText(lpszString);

	SetWindowPos(0, 0, 0, 0, 0, 
		SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE/*|SWP_FRAMECHANGED*/|SWP_DRAWFRAME);
}
