// GridCell.cpp: implementation of the CGridCell class.
//
//////////////////////////////////////////////////////////////////////
// Written by Mario Zucca 
//        mailto:mario@GenoaValley.org
//        http://www.GenoaValley.org
//
// Copyright (c) 2000.
//
// The code contained in this file is based on the original
// Grid control written by Chris Maunder,
//        mailto:chris@codeproject.com
//        http://www.codeproject.com

#include "stdafx.h"

#include "atlcontrols.h"
#include "MyWindow.h"
//#include "NewGridT1.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridCell::CGridCell() : _pGrid(NULL) ,
					 m_pFont(NULL),
					 _Picture(NULL),
					 _PictOrientation(grPictOrientationLeft)
{
        state = 0;
        nFormat = 0;
        szText=_T("");
        iImage = -1;
		crBkClr = CLR_DEFAULT;
		crFgClr = CLR_DEFAULT;
        lParam = 0;

}
STDMETHODIMP CGridCell::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGridCell
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CGridCell::~CGridCell()
{
	// All the cleanup code in the dtor
	if(m_pFont)
		m_pFont = 0;
//	szText=_T("");
	state=0;
}
COLORREF CGridCell::GetCRBkClr()
{
	return crBkClr;
}
COLORREF CGridCell::GetCRFgClr()
{
	return crFgClr;
}

BOOL CGridCell::DrawCell(HDC hDC,
						 HIMAGELIST hImage,
						 RECT rect,
						 COLORREF BkClr,
						 COLORREF FgClr,
						 int nMargin,
						 BOOL bEraseBk)
{

    COLORREF TextBkClr = (crBkClr == CLR_DEFAULT)? BkClr : crBkClr;
    COLORREF TextClr   = (crFgClr == CLR_DEFAULT)? FgClr : crFgClr;

    // Force redraw of background if custom colour
    //if (Item.crBkClr != CLR_DEFAULT)
        bEraseBk = TRUE;

    int nSavedDC = SaveDC(hDC);

   SetBkMode(hDC,TRANSPARENT);

    if (state & GVIS_FOCUSED ) 
    {
        rect.right++; rect.bottom++;    // FillRect doesn't draw RHS or bottom
        if (bEraseBk) 
        {
            HBRUSH brush;
			brush = CreateSolidBrush(TextBkClr);
            FillRect(hDC,&rect, brush);
        }
        rect.right--; rect.bottom--;    
        SelectObject(hDC,
			GetStockObject(BLACK_PEN));

        SelectObject(hDC,
			GetStockObject(NULL_BRUSH));

        Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
        ::SetTextColor(hDC,TextClr);

        ::InflateRect(&rect,-1,-1);

    }
    else if (state & GVIS_SELECTED ) 
    {
        rect.right++; rect.bottom++;    // FillRect doesn't draw RHS or bottom
        // DIVENTA FillSolidRect(hDC,&rect, ::GetSysColor(COLOR_HIGHLIGHT));
		::SetBkColor(hDC, ::GetSysColor(COLOR_HIGHLIGHT));
		::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);

        rect.right--; rect.bottom--;
        ::SetTextColor(hDC,::GetSysColor(COLOR_HIGHLIGHTTEXT));
    } else {
        rect.right++; rect.bottom++;    // FillRect doesn't draw RHS or bottom
        if (bEraseBk) 
        {
            HBRUSH brush;
			brush = CreateSolidBrush(TextBkClr);
            FillRect(hDC,&rect, brush);
			DeleteObject(brush);
        }
        rect.right--; rect.bottom--;
        ::SetTextColor(hDC,TextClr);
    }

    if (state & GVIS_DROPHILITED)
    {
        SelectObject(hDC,
			GetStockObject(BLACK_PEN));

        SelectObject(hDC,
			GetStockObject(NULL_BRUSH));
        Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
    }

    //CCellID FocusCell = GetFocusCell();
    //if (IsCellFixed(nRow, nCol) && (FocusCell.row == nRow || FocusCell.col == nCol))
    //{
    //    static LOGFONT lf;
    //    memcpy(&lf, pLF, sizeof(LOGFONT));
    //    lf.lfWeight = SELECTED_CELL_FONT_WEIGHT;
    //    pLF = &lf;
    //}
	HFONT font = CreateFontIndirect(&m_lfFont);;

   
    SelectObject(hDC,font);

    InflateRect(&rect,-nMargin, 0);

	if (_Picture)
	{
		CComQIPtr<IPicture,&IID_IPicture> pPic(_Picture);
		if(pPic)
		{
			//calculation of coord.
			SIZE szPic, crPic, szPicHM;

			pPic->get_Width (&szPicHM.cx);
			pPic->get_Height(&szPicHM.cy);				
			AtlHiMetricToPixel(&szPicHM, &szPic);

			int height = rect.bottom - rect.top;
			int width  = rect.right - rect.left;
			int x = max(rect.left, (rect.left + (width - szPic.cx ) / 2));
			int y = max(rect.top, (rect.top + (height  - szPic.cy ) / 2));
			switch (_PictOrientation)
			{
			case grPictOrientationLeft:		// Left ;
				crPic.cx = rect.left;
				crPic.cy = rect.top;
				rect.left += szPic.cx+nMargin;
				break;
			case grPictOrientationCenter:		// Center
				crPic.cx = x;
				crPic.cy = max(rect.top, (rect.top +  (height - szPic.cy) / 2));
				rect.left += szPic.cx+nMargin;
				break;
			case grPictOrientationRight:
				crPic.cx = max(rect.left, (rect.right - szPic.cx));
				crPic.cy = rect.top;
				break;
			default: // Left
				crPic.cx = rect.left;
				crPic.cy = rect.top;
				rect.left = nMargin;
				break;
			}
			int id = SaveDC(hDC); 

			SetMapMode(hDC, MM_ISOTROPIC);
			SetWindowExtEx(hDC, rect.right, rect.bottom, 0);
			SetViewportExtEx(hDC, rect.right, -rect.bottom, 0);
			SetViewportOrgEx(hDC, 0, (rect.bottom - rect.top), 0);
			HRESULT hresDraw = pPic->Render(hDC, crPic.cx, -crPic.cy, szPic.cx, szPic.cy, 0, 20, szPicHM.cx, szPicHM.cy, 0); 	
/*			HRESULT hresDraw = pPic->Render(hDC,
				rect.left,
				-rect.top, szPic.cx, szPic.cy, 0, 20, szPicHM.cx, szPicHM.cy, 0); 	
*/

			RestoreDC(hDC, id); 				
//			return TRUE;
		}
	}
	else
		if (hImage && iImage >= 0)
		{
			IMAGEINFO Info;
			if (ImageList_GetImageInfo(hImage,iImage, &Info))
			{
				//CRgn rgn;
				//rgn.CreateRectRgnIndirect(rect);
				//pDC->SelectClipRgn(&rgn);
				//rgn.DeleteObject();

				int nImageWidth = Info.rcImage.right-Info.rcImage.left+1;
				
				IMAGELISTDRAWPARAMS iDP;
				iDP.cbSize = sizeof(iDP);
				iDP.cx = 0;
				iDP.cy = 0;
				iDP.dwRop = SRCCOPY ;
				iDP.fStyle = ILD_NORMAL;
				iDP.hdcDst = hDC;
				iDP.himl = hImage;
				iDP.i = iImage;
				iDP.rgbBk = CLR_DEFAULT;
				iDP.rgbFg = CLR_DEFAULT;
				iDP.x = rect.left;
				iDP.y = rect.top;
				iDP.xBitmap = 0;
				iDP.yBitmap = 0;

				ImageList_DrawIndirect(&iDP);
				rect.left += nImageWidth+nMargin;
			}
		}

    DrawText(hDC, szText, -1, &rect, nFormat);

    RestoreDC(hDC,nSavedDC);

	DeleteObject(font);
    return TRUE;


}

BOOL CGridCell::SetBkColour(COLORREF cr)
{
	// Imposta il colore di backgroud
	crBkClr = cr;
	return TRUE;
}

UINT CGridCell::GetFormat()
{
	return nFormat;
}

BOOL CGridCell::Edit(HWND hwnd, RECT* rect,
					 int row,
					 int col)
{
	VARIANT_BOOL cancel = VARIANT_FALSE;

	_pGrid->Fire_BeforeEdit(row,col,&cancel);
	if (cancel == VARIANT_TRUE) // Cancel Editing
		return FALSE;
    // InPlaceEdit auto-deletes itself
	_edit1 = new CMyWindow;

    DWORD dwStyle = ES_LEFT;
	dwStyle &= ~WS_CAPTION;
    if (nFormat & DT_RIGHT) dwStyle = ES_RIGHT;
    else if (nFormat & DT_CENTER) dwStyle = ES_CENTER;

	dwStyle |= WS_CHILD | ES_AUTOHSCROLL;

	_edit1->Create(hwnd,*rect,NULL,dwStyle);
	_edit1->SetParent(hwnd);
	_edit1->SetWindowText(szText);//, nChar);
	_edit1->SetWindowPos(HWND_TOP,rect,SWP_SHOWWINDOW);
	_edit1->SetSel(0,strlen(szText));
	_edit1->SetCell(this,row,col);
	_edit1->SetFocus();

//	edit1->Detach();
//	delete edit1;

	return TRUE;
}

int CGridCell::GetImage()
{
	return iImage;
}

BOOL CGridCell::SetImage(int image)
{
	iImage = image;
	return TRUE;

}

BOOL CGridCell::SetState(UINT ustate)
{
	state = ustate;
	return TRUE;
}

UINT CGridCell::GetState()
{
	return state;
}

_bstr_t CGridCell::GetText()
{

	return szText;
}

LPARAM CGridCell::GetData()
{
    return lParam;

}

void CGridCell::SetFormat(UINT format)
{
	nFormat = format;
}

void CGridCell::SetFgColour(COLORREF cr)
{
	crFgClr = cr;
}

LPLOGFONT CGridCell::GetFont()
{

	return &m_lfFont;

}

STDMETHODIMP CGridCell::get_Text(BSTR *pVal)
{
	*pVal = szText;
	return S_OK;
}

STDMETHODIMP CGridCell::put_Text(BSTR newVal)
{
	szText = newVal;

	if(_pGrid)
		_pGrid->FireViewChange();
	return S_OK;
}

STDMETHODIMP CGridCell::get_Font(IFontDisp **pVal)
{
	ATLTRACE2(atlTraceControls,2,_T("CGridCell::get_Font\n"));

	*pVal = m_pFont;
	if (*pVal != NULL)
		(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CGridCell::put_Font(IFontDisp *pFont)
{
	ATLTRACE2(atlTraceControls,2,_T("CGridCell::put_Font\n"));

	if(m_pFont)
		m_pFont = NULL;

	if (pFont)
	{
		CComQIPtr<IFont, &IID_IFont> p(pFont);
		if (p)
		{
			CComPtr<IFont> pFont;
			p->Clone(&pFont);
			if (pFont)
			{
				HFONT hf;
				LOGFONT lf;
				pFont->get_hFont(&hf);
				pFont->AddRefHfont(hf);
				pFont->QueryInterface(IID_IFontDisp, (void**) &m_pFont);
				memset(&lf,0,sizeof(LOGFONT));
				int bytes;
				DWORD err;
				if(hf)
					bytes = GetObject(hf, sizeof(LOGFONT), &m_lfFont);
				if(bytes == 0)
				{
					err = GetLastError();
				}
				if(_pGrid)
					if (_pGrid->m_hWnd)
						_pGrid->FireViewChange();
			}
		}
	}
	return S_OK;
}

void CGridCell::SetParent(CGrid *parent)
{
	_pGrid = parent;
}

STDMETHODIMP CGridCell::get_HorizontalAlignment(grOrizontalAlignment *pVal)
{

	return S_OK;
}

STDMETHODIMP CGridCell::put_HorizontalAlignment(grOrizontalAlignment newVal)
{
	UINT format = nFormat;

	nFormat &= ~ DT_LEFT;
	nFormat &= ~ DT_RIGHT;
	nFormat &= ~ DT_CENTER;
	switch(newVal)
	{
	case grOrizAlignLeft:
		nFormat |= DT_LEFT;
		break;
	case grOrizAlignRight:
		nFormat |= DT_RIGHT;
		break;
	case grOrizAlignCenter:
		nFormat |= DT_CENTER;
		break;
	default:
		nFormat = format; // Restore previous value
	}

	_pGrid->FireViewChange();
	return S_OK;
}

STDMETHODIMP CGridCell::get_VerticalAlignment(grVerticalAlignment *pVal)
{

	return S_OK;
}

STDMETHODIMP CGridCell::put_VerticalAlignment(grVerticalAlignment newVal)
{
	UINT format = nFormat;

	nFormat &= ~ DT_BOTTOM;
	nFormat &= ~ DT_TOP;
	nFormat &= ~ DT_VCENTER;
	nFormat &= ~ DT_SINGLELINE;
	switch(newVal)
	{
	case grVertAlignBottom:
		nFormat |= DT_BOTTOM | DT_SINGLELINE ;
		break;
	case grVertAlignTop:
		nFormat |= DT_TOP;
		break;
	case grVertAlignCenter:
		nFormat |= DT_VCENTER | DT_SINGLELINE ;
		break;
	default:
		nFormat = format; // Restore previous value
	}

	_pGrid->FireViewChange();
	return S_OK;
}

STDMETHODIMP CGridCell::get_BreakingTextWords(grBreakingTextWords *pVal)
{
	return S_OK;
}

STDMETHODIMP CGridCell::put_BreakingTextWords(grBreakingTextWords newVal)
{
	UINT format = nFormat;

	nFormat &= ~ DT_WORDBREAK;
	nFormat &= ~ DT_END_ELLIPSIS;

	switch(newVal)
	{
	case grBreakingTWNormal:
		break;
	case grBreakingTWWordBreak:
		nFormat |= DT_WORDBREAK;
		break;
	case grBreakingTWEndEllipsis:
		nFormat |= DT_END_ELLIPSIS;
		break;
	default:
		nFormat = format; // Restore previous value
		return S_OK;
	}

	_pGrid->FireViewChange();
	return S_OK;
}

STDMETHODIMP CGridCell::get_Picture(IPictureDisp **pVal)
{

	if(_Picture)
		_Picture->AddRef();

	*pVal = _Picture;

	return S_OK;
}

STDMETHODIMP CGridCell::put_Picture(IPictureDisp *newVal)
{
	if(_Picture)
	{
		_Picture->Release();
		_Picture = NULL;
	}

	if (newVal)
	{
		_Picture = newVal;
		_Picture->AddRef();
	}
	_pGrid->FireViewChange();
	return S_OK;
}

STDMETHODIMP CGridCell::get_PictureOrientation(grPictOrientation *pVal)
{
	*pVal = _PictOrientation;
	return S_OK;
}

STDMETHODIMP CGridCell::put_PictureOrientation(grPictOrientation newVal)
{
	_PictOrientation = newVal;
	_pGrid->FireViewChange();
	return S_OK;
}

void CGridCell::StopEdit()
{
	// This function stop the edit on a cell 
	// and set the cell text to text
	if (_edit1)
	{
		int row=_edit1->m_nRow,col=_edit1->m_nCol;
		::DestroyWindow(_edit1->m_hWnd);
		delete _edit1;
		_edit1 = NULL;
		_pGrid->Fire_AfterEdit(row,col);

	}
}

SIZE CGridCell::GetPictureSize()
{
	SIZE szPic = {0,0};
	if (_Picture)
	{
		CComQIPtr<IPicture,&IID_IPicture> pPic(_Picture);
		if(pPic)
		{
			//calculation of coord.
			SIZE szPicHM;

			pPic->get_Width (&szPicHM.cx);
			pPic->get_Height(&szPicHM.cy);				
			AtlHiMetricToPixel(&szPicHM, &szPic);
		}
	}
	return szPic;
}

HWND CGridCell::GetHWNDGrid()
{
	return _pGrid->m_hWnd;
}
