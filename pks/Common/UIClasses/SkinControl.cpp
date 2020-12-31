// SkinControl.cpp: implementation of the CSkinControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkinControl.h"
#include "..\CImage\src\ImgObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSkinControl::CSkinControl()
{
	m_pParentWnd		= NULL;

	m_nCurrentState		= BUTTON_STATE_UNPRESSED;
	m_bEnabled			= TRUE;
	m_bShape			= FALSE;

	m_csDLLFileName		= DLLFILENAME;
	m_csText			= "";

	m_nUnPressedID		= -1;
	m_nHoverID			= -1;
	m_nPressedID		= -1;
	m_nDisabledID		= -1;
	m_nCommandID		= 0;
	m_nControlID		= 0;

	m_lPaddingLeft		= 0;
	m_lPaddingTop		= 0;
	m_nLeft				= 0;
	m_nTop				= 0;
	m_nWidth			= 0;
	m_nHeight			= 0;
	m_lImageWidth		= 0;
	m_lImageHeight		= 0;

	m_nFontSize			= 16;
	m_csFontName		= "Arial";
	m_nFontStyle		= -1;
	m_lTextAlign		= -1;
	memset(&m_lfFontStruct, 0, sizeof(m_lfFontStruct));

	m_crBackgroundColorUnPressed	= RGB(0,0,0);
	m_crBackgroundColorPressed		= RGB(0,0,0);
	m_crBackgroundColorHover		= RGB(0,0,0);
	m_crForegroundColor				= RGB(0,0,0);
	m_crBackgroundColorDisabled		= RGB(0,0,0);
	m_crTextColor					= WHITE;

	m_nReserved	= 0;

	m_hbmpDisabled	= NULL;
	m_hbmpDown		= NULL;
	m_hbmpHover		= NULL;
	m_hbmpNormal	= NULL;
}

CSkinControl::~CSkinControl()
{
	m_bmpMemory.Detach();

	if(m_hbmpDisabled != NULL)
	{
		::DeleteObject(m_hbmpDisabled);
		m_hbmpDisabled = NULL;
	}

	if(m_hbmpDown != NULL)
	{
		::DeleteObject(m_hbmpDown);
		m_hbmpDown = NULL;
	}

	if(m_hbmpHover != NULL)
	{
		::DeleteObject(m_hbmpHover);
		m_hbmpHover = NULL;
	}

	if(m_hbmpNormal != NULL)
	{
		::DeleteObject(m_hbmpNormal);
		m_hbmpNormal = NULL;
	}
}

void CSkinControl::SetCurrentState(int nState)
{
	m_nCurrentState = nState;
}

int CSkinControl::GetCurrentState() const
{
	return m_nCurrentState;
}

void CSkinControl::SetImageResource(INT nUnPressedID, INT nHoverID, INT nPressedID, INT nDisabledID)
{
	m_nUnPressedID	= nUnPressedID;
	m_nHoverID		= nHoverID;
	m_nPressedID	= nPressedID;
	m_nDisabledID	= nDisabledID;

	if(m_nUnPressedID != -1)
	{
		if(m_hbmpNormal != NULL)
		{
			::DeleteObject(m_hbmpNormal);
			m_hbmpNormal = NULL;
		}
		m_hbmpNormal = LoadGIF(GetDllInstance(DLLFILENAME), MAKEINTRESOURCE(m_nUnPressedID));
	}
	else
	{
		if(m_hbmpNormal != NULL)
		{
			::DeleteObject(m_hbmpNormal);
			m_hbmpNormal = NULL;
		}
	}

	if(m_nHoverID != -1)
	{
		if(m_hbmpHover != NULL)
		{
			::DeleteObject(m_hbmpHover);
			m_hbmpHover = NULL;
		}
		m_hbmpHover	= LoadGIF(GetDllInstance(DLLFILENAME), MAKEINTRESOURCE(m_nHoverID));
	}
	else
	{
		if(m_hbmpHover != NULL)
		{
			::DeleteObject(m_hbmpHover);
			m_hbmpHover = NULL;
		}
	}

	if(m_nPressedID != -1)
	{
		if(m_hbmpDown != NULL)
		{
			::DeleteObject(m_hbmpDown);
			m_hbmpDown = NULL;
		}
		m_hbmpDown = LoadGIF(GetDllInstance(DLLFILENAME), MAKEINTRESOURCE(m_nPressedID));
	}
	else
	{
		if(m_hbmpDown != NULL)
		{
			::DeleteObject(m_hbmpDown);
			m_hbmpDown = NULL;
		}
	}

	if(m_nDisabledID != -1)
	{
		if(m_hbmpDisabled != NULL)
		{
			::DeleteObject(m_hbmpDisabled);
			m_hbmpDisabled = NULL;
		}
		m_hbmpDisabled = LoadGIF(GetDllInstance(DLLFILENAME), MAKEINTRESOURCE(m_nDisabledID));
	}
	else
	{
		if(m_hbmpDisabled != NULL)
		{
			::DeleteObject(m_hbmpDisabled);
			m_hbmpDisabled = NULL;
		}
	}
}

UINT CSkinControl::GetID() const
{
	UINT nRetID = -1;//GetUnPressedID();

	switch(GetCurrentState())
	{
		case BUTTON_STATE_UNPRESSED:
			nRetID = GetUnPressedID();
			break;

		case BUTTON_STATE_HOVER:
			nRetID = GetHoverID();
			break;

		case BUTTON_STATE_PRESSED:
			nRetID = GetPressedID();
			break;

		case BUTTON_STATE_DISABLED:
			nRetID = GetDisabledID();
			break;

		default:
			break;
	}

	return nRetID;
}

int CSkinControl::GetUnPressedID() const
{
	return m_nUnPressedID;
}

int CSkinControl::GetHoverID() const
{
	return m_nHoverID;
}

int CSkinControl::GetPressedID() const
{
	return m_nPressedID;
}

void CSkinControl::SetDimensions(int nWidth, int nHeight)
{
	m_nWidth	= nWidth;
	m_nHeight	= nHeight;
}

void CSkinControl::SetCoordinates(int nLeft, int nTop)
{
	m_nLeft = nLeft;
	m_nTop	= nTop;
}

int CSkinControl::GetLeft() const
{
	return m_nLeft;
}

int CSkinControl::GetTop() const
{
	return m_nTop;
}

int CSkinControl::GetWidth() const
{
	return m_nWidth;
}

int CSkinControl::GetHeight() const
{
	return m_nHeight;
}

void CSkinControl::SetCommandID(int nID)
{
	m_nCommandID = nID;
}

int CSkinControl::GetCommandID() const
{
	return m_nCommandID;
}

void CSkinControl::SetEnabled(BOOL bEnabled)
{
	m_bEnabled = bEnabled;

	if(bEnabled)
	{
		m_nCurrentState = BUTTON_STATE_UNPRESSED;
	}
	else
	{
		m_nCurrentState = BUTTON_STATE_DISABLED;
	}
}

BOOL CSkinControl::IsEnabled()
{
	return m_bEnabled;
}

LPCTSTR CSkinControl::SetFontName(LPCTSTR lpszFontFaceName)
{
	CString csOldFontName = m_csFontName;
	m_csFontName = lpszFontFaceName;

	PrepareFont();

	return (LPCTSTR)csOldFontName;
}

LPCTSTR CSkinControl::GetFontName()
{	
	return (LPCTSTR)m_csFontName;
}

int CSkinControl::SetFontSize(int nFontSize)
{
	int nOldfontSize = m_nFontSize;

	m_nFontSize = nFontSize;

	PrepareFont();

	return nOldfontSize;
}

int CSkinControl::GetFontSize()
{
	return m_nFontSize;
}

int CSkinControl::SetFontStyle(int nFontStyle)
{
	int nOldFontStyle = m_nFontStyle;

	m_nFontStyle = nFontStyle;

	PrepareFont();

	return nOldFontStyle;
}

int CSkinControl::GetFontStyle()
{
	return m_nFontStyle;
}

BOOL CSkinControl::PrepareFont()
{	
	memset(&m_lfFontStruct, 0, sizeof(m_lfFontStruct));

	lstrcpy(m_lfFontStruct.lfFaceName, m_csFontName);

	m_lfFontStruct.lfHeight = m_nFontSize;

	if(m_nFontStyle & FONT_BOLD)
	{
		m_lfFontStruct.lfWeight = FW_BOLD;
	}
	else
	{
		m_lfFontStruct.lfWeight = FW_NORMAL;
	}

	if(m_nFontStyle & FONT_ITALIC)
	{
		m_lfFontStruct.lfItalic = TRUE;
	}

	if(m_nFontStyle & FONT_UNDERLINE)
	{
		m_lfFontStruct.lfUnderline = TRUE;
	}

	if(m_nFontStyle & FONT_STRIKEOUT)
	{
		m_lfFontStruct.lfStrikeOut = TRUE;
	}

	m_cfFaceTextFont.DeleteObject();

	if(m_cfFaceTextFont.CreateFontIndirect(&m_lfFontStruct) != 0)
	{
		return TRUE;
	}

	return FALSE;
}

int CSkinControl::UpdateMemoryDC()
{
	HBITMAP hBitmap = NULL;
	BITMAP bmpTemp;

	memset(&bmpTemp, 0, sizeof(BITMAP));

#ifdef	USE_GIF_IMAGES
	hBitmap = LoadGIF(GetDllInstance((LPCTSTR)m_csDLLFileName),MAKEINTRESOURCE(GetID()));
#else
	hBitmap = LoadBitmap(GetDllInstance((LPTSTR)(LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(GetID()));
#endif
	if(hBitmap != NULL)
	{
		::GetObject(hBitmap, sizeof(BITMAP), &bmpTemp);
		m_lImageWidth = bmpTemp.bmWidth;
		m_lImageHeight = bmpTemp.bmHeight;
		::SelectObject(m_dcMemory.GetSafeHdc(),hBitmap);
	}
	else if(m_nPressedID == -1 && m_nUnPressedID == -1 && m_nHoverID == -1)
	{		
		m_dcMemory.SetTextColor(m_crTextColor);
		m_dcMemory.DrawText(m_csText, CRect(0, 0, m_nWidth, m_nHeight), DT_CENTER);
	}
	return 0;
}

void CSkinControl::SetControlText(LPCTSTR lpszFaceText)
{
	CString csText = lpszFaceText;
	m_csText = csText;
}

void CSkinControl::SetForegroundColor(COLORREF crForeColor)
{
	m_crForegroundColor = crForeColor;
}

CString CSkinControl::GetControlText()
{
	return m_csText;
}

int CSkinControl::GetControlID()
{
	return m_nControlID;
}

void CSkinControl::SetBackgroundColor(int nBackgroundState, COLORREF crColor)
{
	switch(nBackgroundState)
	{
		case BACKGROUND_STATE_HOVER:
			m_crBackgroundColorHover = crColor;
			break;

		case BACKGROUND_STATE_UNPRESSED:
			m_crBackgroundColorUnPressed = crColor;
			break;

		case BACKGROUND_STATE_PRESSED:
			m_crBackgroundColorPressed = crColor;
			break;

		case BACKGROUND_STATE_DISABLED:
			m_crBackgroundColorDisabled = crColor;
			break;

		default:
			m_crBackgroundColorHover = crColor;
			m_crBackgroundColorUnPressed = crColor;
			m_crBackgroundColorPressed = crColor;
			break;
	}
}

COLORREF CSkinControl::GetBackgroundColor(int nBackgroundState)
{
	COLORREF crBack = RGB(0,0,0);

	switch(nBackgroundState)
	{
		case BACKGROUND_STATE_HOVER:
			crBack = m_crBackgroundColorHover;
			break;

		case BACKGROUND_STATE_UNPRESSED:
			crBack = m_crBackgroundColorUnPressed;
			break;

		case BACKGROUND_STATE_PRESSED:
			crBack = m_crBackgroundColorPressed;
			break;

		case BACKGROUND_STATE_DISABLED:
			crBack = m_crBackgroundColorDisabled;
			break;

		default:
			crBack = m_crBackgroundColorUnPressed;
			break;
	}

	return crBack;
}

COLORREF CSkinControl::GetCurrentBackgroundColor()
{
	COLORREF crColor = RGB(0,0,0);

	switch(GetCurrentState())
	{
		case BUTTON_STATE_PRESSED:
			crColor = m_crBackgroundColorPressed;
			break;

		case BUTTON_STATE_UNPRESSED:
			crColor = m_crBackgroundColorUnPressed;
			break;

		case BUTTON_STATE_HOVER:
			crColor = m_crBackgroundColorHover;
			break;

		case BUTTON_STATE_DISABLED:
			crColor = m_crBackgroundColorDisabled;
			break;

		default:
			crColor = m_crBackgroundColorUnPressed;
			break;
	}

	return crColor;
}

int CSkinControl::GetDisabledID() const
{
	return m_nDisabledID;
}

HMODULE CSkinControl::GetDllInstance(LPCTSTR lpModuleName)
{
	return GetModuleHandle(lpModuleName);
}

void CSkinControl::SetPadding(long lLeft, long lTop)
{
	m_lPaddingLeft = lLeft;
	m_lPaddingTop = lTop;
}

HBITMAP CSkinControl::LoadGIF(HINSTANCE hInstance, LPCTSTR lpGIFName)
{
	HBITMAP hBmp=NULL;
	CImageObject *pImageObj;

	pImageObj = new CImageObject;

	HRSRC hRes = FindResource(hInstance, lpGIFName, "RT_RCDATA");
	
	if(hRes != NULL)
	{
		if(pImageObj->LoadResource(hRes, ENUM_cimage_format_gif, hInstance))
		{
			m_bmpMemory.Detach();

			pImageObj->MakeBitmap(&m_bmpMemory);

			hBmp = (HBITMAP)m_bmpMemory;
		}
	}

	if(pImageObj != NULL)
	{
		delete pImageObj;
		pImageObj = 0;
	}

	return hBmp;
}

HBITMAP CSkinControl::GetCurrentStateBitmap()
{
	switch(m_nCurrentState)
	{
	case BUTTON_STATE_UNPRESSED:
		return m_hbmpNormal;

	case BUTTON_STATE_PRESSED:
		return m_hbmpDown;

	case BUTTON_STATE_HOVER:
		return m_hbmpHover;
		
	case BUTTON_STATE_DISABLED:
		return m_hbmpDisabled;

	default:
		return m_hbmpNormal;
		
	}

	return m_hbmpNormal;
}

void CSkinControl::SetTextColor(COLORREF crTextColor/*=BLACK*/)
{
	m_crTextColor = crTextColor;
}

