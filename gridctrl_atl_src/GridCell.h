// GridCell.h: interface for the CGridCell class.
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
#if !defined(AFX_GRIDCELL_H__DE63D710_5B02_11D3_B223_006097FEBF00__INCLUDED_)
#define AFX_GRIDCELL_H__DE63D710_5B02_11D3_B223_006097FEBF00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols
class CMyWindow;

class CGrid;
/////////////////////////////////////////////////////////////////////////////

class ATL_NO_VTABLE CGridCell :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGridCell, &CLSID_GridCell>,
	public ISupportErrorInfo,
	public IGridCell
{
public:
	HWND GetHWNDGrid();
	SIZE GetPictureSize();
	void StopEdit();
	STDMETHOD(get_PictureOrientation)(/*[out, retval]*/ grPictOrientation *pVal);
	STDMETHOD(put_PictureOrientation)(/*[in]*/ grPictOrientation newVal);
	STDMETHOD(get_Picture)(/*[out, retval]*/ IPictureDisp* *pVal);
	STDMETHOD(put_Picture)(/*[in]*/ IPictureDisp* newVal);
	void SetParent(CGrid* parent);
	STDMETHOD(get_Font)(/*[out, retval]*/ IFontDisp* *pVal);
	STDMETHOD(put_Font)(/*[in]*/ IFontDisp* newVal);
	STDMETHOD(get_Text)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Text)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_HorizontalAlignment)(grOrizontalAlignment *pVal);
	STDMETHOD(put_HorizontalAlignment)(grOrizontalAlignment newVal);
	STDMETHOD(get_VerticalAlignment)(grVerticalAlignment *pVal);
	STDMETHOD(put_VerticalAlignment)(grVerticalAlignment newVal);
	STDMETHOD(get_BreakingTextWords)(grBreakingTextWords *pVal);
	STDMETHOD(put_BreakingTextWords)(grBreakingTextWords newVal);

DECLARE_REGISTRY_RESOURCEID(IDR_GRIDCELL)
DECLARE_NOT_AGGREGATABLE(CGridCell)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGridCell)
	COM_INTERFACE_ENTRY(IGridCell)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	LPLOGFONT GetFont();
	void SetFgColour(COLORREF cr);
	void SetFormat(UINT format);
	LPARAM GetData();
	_bstr_t GetText();
	UINT GetState();
	BOOL SetState(UINT ustate);
	BOOL SetImage(int image);
	int GetImage();
	BOOL Edit(HWND hwnd,RECT* rect,
					 int row,
					 int col);
	UINT GetFormat();
	CGridCell();
	virtual ~CGridCell();

	BOOL SetBkColour(COLORREF cr);
	BOOL DrawCell(HDC hDC,
						 HIMAGELIST hImage,
						 RECT rect,
						 COLORREF BkClr,
						 COLORREF FgClr,
						 int nMargin,
						 BOOL bEraseBk);
	COLORREF GetCRBkClr();
	COLORREF GetCRFgClr();
	LOGFONT GetLogFont()
	{
		return m_lfFont;
	};


private:
	CMyWindow* _edit1;
	CGrid*	_pGrid;			// Pointer to parent grid
	IPictureDisp* _Picture; // Pointer to picture
	grPictOrientation _PictOrientation;	// 0 Left
    UINT     state;       // Cell state (selected/focus etc)
    UINT     nFormat;     // Cell format
    _bstr_t  szText;      // Cell text (or binary data if you wish...)
    int      iImage;      // Index of the list view item’s icon 
    COLORREF crBkClr;     // Background colour (or CLR_DEFAULT)
    COLORREF crFgClr;     // Forground colour (or CLR_DEFAULT)

    
	LOGFONT	 m_lfFont;      // Cell font
	CComPtr<IFontDisp> m_pFont;

    LPARAM   lParam;      // 32-bit value to associate with item
};

#endif // !defined(AFX_GRIDCELL_H__DE63D710_5B02_11D3_B223_006097FEBF00__INCLUDED_)
