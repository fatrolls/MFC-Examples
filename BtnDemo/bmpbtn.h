// BmpBtn.h

#pragma once

class CBmpBtn : public CBitmapButtonImpl<CBmpBtn>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_BmpBtn"), GetWndClassName())

	// added border style (auto3d_single)
	CBmpBtn(DWORD dwExtendedStyle = BMPBTN_AUTOSIZE | BMPBTN_AUTO3D_SINGLE, HIMAGELIST hImageList = NULL) : 
		CBitmapButtonImpl<CBmpBtn>(dwExtendedStyle, hImageList)
	{ }

	BEGIN_MSG_MAP(CBmpBtn)
		CHAIN_MSG_MAP(CBitmapButtonImpl<CBmpBtn>)
	END_MSG_MAP()

	// override of CBitmapButtonImpl DoPaint(). Adds fillrect
	void DoPaint(CDCHandle dc)
	{
		// added by SoftGee to resolve image artifacts
		RECT rc;
		GetClientRect(&rc);
		dc.FillRect(&rc, (HBRUSH)(COLOR_BTNFACE+1));

		// call ancestor DoPaint() method
		CBitmapButtonImpl<CBmpBtn>::DoPaint(dc);
	}
};
