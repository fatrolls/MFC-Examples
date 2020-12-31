
#ifndef DRAW_HELPERS_H_
#define DRAW_HELPERS_H_
#pragma once

#include "SkinControlsDefine.h"

// ÑÕÉ«
class CColor
{
public:
	CColor()
	{
		Argb = 0xFF000000;
	}

	CColor(BYTE r, BYTE g, BYTE b)
	{
		Argb = MakeARGB(255, r, g, b);
	}

	CColor(BYTE a, BYTE r, BYTE g, BYTE b)
	{
		Argb = MakeARGB(a, r, g, b);
	}

	CColor(DWORD argb)
	{
		Argb = argb;
	}

	BYTE GetAlpha() const
	{
		return (BYTE)(Argb >> AlphaShift);
	}

	BYTE GetA() const
	{
		return GetAlpha();
	}

	BYTE GetRed() const
	{
		return (BYTE)(Argb >> RedShift);
	}

	BYTE GetR() const
	{
		return GetRed();
	}

	BYTE GetGreen() const
	{
		return (BYTE)(Argb >> GreenShift);
	}

	BYTE GetG() const
	{
		return GetGreen();
	}

	BYTE GetBlue() const
	{
		return (BYTE)(Argb >> BlueShift);
	}

	BYTE GetB() const
	{
		return GetBlue();
	}

	DWORD GetValue() const
	{
		return Argb;
	}

	void SetValue(DWORD argb)
	{
		Argb = argb;
	}

	void SetFromCOLORREF(COLORREF rgb)
	{
		Argb = MakeARGB(255, GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
	}

	COLORREF ToCOLORREF() const
	{
		return RGB(GetRed(), GetGreen(), GetBlue());
	}

public:
	// Shift count and bit mask for A, R, G, B components
	enum
	{
		AlphaShift  = 24,
		RedShift    = 16,
		GreenShift  = 8,
		BlueShift   = 0
	};

	enum
	{
		AlphaMask   = 0xff000000,
		RedMask     = 0x00ff0000,
		GreenMask   = 0x0000ff00,
		BlueMask    = 0x000000ff
	};

	// Assemble A, R, G, B values into a 32-bit integer

	static DWORD MakeARGB(BYTE a, BYTE r, BYTE g, BYTE b)
	{
		return (((DWORD) (b) <<  BlueShift) |
			((DWORD) (g) << GreenShift) |
			((DWORD) (r) <<   RedShift) |
			((DWORD) (a) << AlphaShift));
	}

protected:
	DWORD Argb;
};


//===========================================================================
// Summary:
//     CTransparentBitmap is a helper class used to extract the
//     transparent color from a transparent BitMap.  Also, this class
//     is used to convert a transparent BitMap into a transparent icon.
//===========================================================================
class SKIN_CONTROLS_EXPORT CTransparentBitmap
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructor.  Construct a new CTransparentBitmap from a
	//     handle to an existing BitMap.
	// Parameters:
	//     hBitmap - Handle to an existing BitMap.
	//-----------------------------------------------------------------------
	CTransparentBitmap(HBITMAP hBitmap);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this function to get the transparent color of the BitMap.
	// Returns:
	//     -1 if the BitMap is NULL.
	//     Otherwise, a COLORREF that contains the transparent color of the BitMap.
	//-----------------------------------------------------------------------
	COLORREF GetTransparentColor() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this function to create an icon based on the BitMap.
	// Returns:
	//     NULL if the BitMap is NULL.
	//     NULL if the width or height of the BitMap is 0.
	//     Otherwise, a handle to the icon created from the BitMap.
	//-----------------------------------------------------------------------
	HICON ConvertToIcon() const;

protected:

	HBITMAP m_hBitmap;  // A handle to a BtiMap.
};

//===========================================================================
// Summary:
//     CWindowRect is a helper class used to retrieve the screen
//     size for a specified window.
//===========================================================================
class SKIN_CONTROLS_EXPORT CWindowRect : public CRect
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CWindowRect object used to retrieve the
	//     screen size for the specified window.
	// Parameters:
	//     hWnd - Handle to the window to retrieve the screen size for.
	//     pWnd - Points to the window to retrieve the screen size for.
	//-----------------------------------------------------------------------
	CWindowRect(HWND hWnd);
	CWindowRect(const CWnd* pWnd); // <combine CWindowRect::CWindowRect@HWND>
};

//===========================================================================
// Summary:
//     CClientRect is a helper class used to retrieve the client
//     area for a specified window.
//===========================================================================
class SKIN_CONTROLS_EXPORT CClientRect : public CRect
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CClientRect object used to retrieve the
	//     client area for the specified window.
	// Parameters:
	//     hWnd - Handle to the window to retrieve the client area for.
	//     pWnd - Points to the window to retrieve the client area for.
	//-----------------------------------------------------------------------
	CClientRect(HWND hWnd);
	CClientRect(const CWnd* pWnd); //<combine CClientRect::CClientRect@HWND>
};

//===========================================================================
// Summary:
//     CBufferDC is a helper class used to create a memory device
//     context used to draw to an off-screen bitmap.  When destroyed, the
//     class selects the previous bitmap back into the device context to
//     handle GDI resource cleanup.
//===========================================================================
class SKIN_CONTROLS_EXPORT CBufferDC : public CDC
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CBufferDC object used to create a memory
	//     device context used to draw to an off-screen bitmap.
	// Parameters:
	//     hDestDC - Handle to the destination device context the memory
	//               device is BitBlt to.
	//     rcPaint - Size of the area to paint.
	//     clrBack - Represents background color for fill, can be COLORREF or gradient values using CPaintManagerColorGradient.
	//     bHorz   - Used when drawing gradient background, TRUE to draw gradient from left to right, otherwise drawn top to bottom.
	//-----------------------------------------------------------------------
	CBufferDC(HDC hDestDC, const CRect& rcPaint);
	CBufferDC(HDC hDestDC, const CRect& rcPaint, const BOOL bHorz);

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CBufferDC object used to create a memory
	//     device context used to draw to an off-screen bitmap.
	// Parameters:
	//     paintDC - Handle to the destination device context the memory
	//-----------------------------------------------------------------------
	CBufferDC(CPaintDC& paintDC);

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CBufferDC object, handles cleanup and de-
	//     allocation.
	//-----------------------------------------------------------------------
	virtual ~CBufferDC();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is called to set the valid flag to false
	//     so that the off screen device context will not be drawn.
	//-----------------------------------------------------------------------
	void Discard();

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this method to retrieve a CDC pointer to the destination
	//     device context.
	//-----------------------------------------------------------------------
	CDC* GetDestDC();

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to take a snapshot of the screen underneath
	//     the area where the off screen bitmap is to be drawn.
	//-----------------------------------------------------------------------
	void TakeSnapshot();

protected:

	HDC     m_hDestDC;    // Handle to the destination device context.
	CBitmap m_bitmap;     // Bitmap in memory device context
	CRect   m_rect;       // Size of the area to paint.
	HGDIOBJ m_hOldBitmap; // Handle to the previously selected bitmap.
};

//===========================================================================
// Summary:
//     CBufferDCEx is a helper class used to create a memory device
//     context used to draw to an off-screen bitmap.  When destroyed, the
//     class selects the previous bitmap back into the device context to
//     handle GDI resource cleanup.
//===========================================================================
class SKIN_CONTROLS_EXPORT CBufferDCEx : public CDC
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CBufferDCEx object used to create a memory
	//     device context used to draw to an off-screen bitmap.
	// Parameters:
	//     hDestDC - Handle to the destination device context the memory
	//               device is BitBlt to.
	//     rcPaint - Size of the area to paint.
	//-----------------------------------------------------------------------
	CBufferDCEx(HDC hDestDC, const CRect rcPaint);

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CBufferDC object, handles cleanup and de-
	//     allocation.
	//-----------------------------------------------------------------------
	virtual ~CBufferDCEx();

protected:

	HDC     m_hDestDC;    // Handle to the destination device context.
	HBITMAP m_bitmap;     // Bitmap in memory device context
	CRect   m_rect;       // Size of the area to paint.
	HGDIOBJ m_hOldBitmap; // Handle to the previously selected bitmap.
};

//===========================================================================
// Summary:
//     CBitmapDC is a helper class used to select a bitmap into the
//     device context specified by hDC.  When destroyed, the class
//     selects the previous bitmap back into the device context to
//     handle GDI resource cleanup.
//===========================================================================
class SKIN_CONTROLS_EXPORT CBitmapDC
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CBitmapDC object and selects the specified bitmap
	//     into the device context specified by pDC.
	// Parameters:
	//     pDC     - Pointer to a valid device context.
	//     pBitmap - Pointer to a CBitmap object to select into the device
	//               context.
	//     hBitmap - Bitmap handle
	//-----------------------------------------------------------------------
	CBitmapDC(CDC* pDC, CBitmap* pBitmap);
	CBitmapDC(CDC* pDC, HBITMAP hBitmap);  // <combine CBitmapDC::CBitmapDC@CDC*@CBitmap*>

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CBitmapDC object, handles cleanup and de-
	//     allocation.
	//-----------------------------------------------------------------------
	virtual ~CBitmapDC();

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to change the bitmap selected by the
	//     device context.
	// Parameters:
	//     pBitmap - Pointer to a CBitmap object to select into the device
	//               context.
	//-----------------------------------------------------------------------
	void SetBitmap(CBitmap* pBitmap);

protected:

	HDC     m_hDC;        // Device context handle.
	HGDIOBJ m_hOldBitmap; // Handle to the previously selected bitmap.
};

//===========================================================================
// Summary:
//     CFontDC is a helper class used to select a font into the
//     device context specified by pDC.  When destroyed, the class
//     selects the previous font back into the device context to
//     handle GDI resource cleanup.
//===========================================================================
class SKIN_CONTROLS_EXPORT CFontDC
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CFontDC object and selects the specified font
	//     into the device context specified by pDC.
	// Parameters:
	//     pDC   - Pointer to a valid device context.
	//     pFont - Pointer to a CFont object to select into the device
	//             context.
	//     clrTextColor - Text color to set in the DC.
	//-----------------------------------------------------------------------
	CFontDC(CDC* pDC, CFont* pFont = NULL);
	CFontDC(CDC* pDC, CFont* pFont, COLORREF clrTextColor); // <combine CFontDC::CFontDC@CDC*@CFont*>

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CFontDC object, handles cleanup and de-
	//     allocation.
	//-----------------------------------------------------------------------
	virtual ~CFontDC();

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to change the font selected by the
	//     device context.
	// Parameters:
	//     pFont - Pointer to a CFont object to select into the device
	//             context.
	//-----------------------------------------------------------------------
	void SetFont(CFont* pFont);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to change the text color set in the
	//     device context.
	// Parameters:
	//     clrTextColor - Text color to set in the DC.
	//-----------------------------------------------------------------------
	void SetColor(COLORREF clrTextColor);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to change the font and color selected
	//     by the device context.
	// Parameters:
	//     pFont - Pointer to a CFont object to select into the device
	//             context.
	//     clrTextColor - Text color to set in the DC.
	//-----------------------------------------------------------------------
	void SetFontColor(CFont* pFont, COLORREF clrTextColor);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to select the initial font back into the
	//     device context.
	// Remarks:
	//     This method is also called from the destructor.
	//-----------------------------------------------------------------------
	void ReleaseFont();

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to set the initial text color back into the
	//     device context.
	// Remarks:
	//     This method is also called from the destructor.
	//-----------------------------------------------------------------------
	void ReleaseColor();

protected:
	CDC*     m_pDC;             // Stored pointer to a device context.
	CFont*   m_pOldFont;        // Stored pointer to an initial font from the device context.
	COLORREF m_clrOldTextColor; // Stored an initial text color from the device context.
};

//===========================================================================
// Summary:
//     CPenDC is a helper class used to create a pen using
//     the color specified by crColor.  The pen is then selected
//     into the device context specified by hDC.  When destroyed, the
//     class selects the previous pen back into the device context to
//     handle GDI resource cleanup.
//===========================================================================
class SKIN_CONTROLS_EXPORT CPenDC
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CPenDC object using an existing CPen object.  The
	//     pen is then selected into the device context specified by hDC.
	// Parameters:
	//     pDC  - Pointer to a valid device context.
	//     pPen - Pointer to a CPen object to select into the device
	//             context.
	//     hDC     - Handle to a valid device context.
	//     crColor - RGB value used to create pen.
	// Remarks:
	//     The crColor version constructs a CPenDC object and creates a pen using
	//     the color specified by crColor.  The pen is then selected
	//     into the device context specified by hDC.
	//-----------------------------------------------------------------------
	CPenDC(CDC* pDC, CPen* pPen);
	CPenDC(HDC hDC, COLORREF crColor); // <combine CPenDC::CPenDC@CDC*@CPen*>

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CPenDC object, handles cleanup and de-
	//     allocation.
	//-----------------------------------------------------------------------
	virtual ~CPenDC();

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to retrieve or change the color used by the
	//     device context pen.
	// Parameters:
	//     crColor - RGB value to change the pen color to.
	// Remarks:
	//     The No argument version is used to retrieve the color used by the
	//     device context pen.
	// Returns:
	//     The no argument version returns an RGB value that represents the selected pen color.
	//-----------------------------------------------------------------------
	COLORREF Color();
	void Color(COLORREF crColor); // <combine CPenDC::Color>

protected:

	CPen m_pen;     // Pen selected into device context.
	HDC  m_hDC;     // Device context handle.
	HPEN m_hOldPen; // Handle to the previously selected pen.
};

//===========================================================================
// Summary:
//     CBrushDC is a helper class used to create a  brush using
//     the color specified by crColor.  The brush is then selected
//     into the device context specified by hDC.  When destroyed, the
//     class selects the previous brush back into the device context to
//     handle GDI resource cleanup.
//===========================================================================
class SKIN_CONTROLS_EXPORT CBrushDC
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CBrushDC object and creates a brush using
	//     the color specified by crColor.  The brush is then selected
	//     into the device context specified by hDC.
	// Parameters:
	//     hDC     - Handle to a valid device context.
	//     crColor - RGB value used to create brush.
	//-----------------------------------------------------------------------
	CBrushDC(HDC hDC, COLORREF crColor);

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CBrushDC object, handles cleanup and de-
	//     allocation.
	//-----------------------------------------------------------------------
	virtual ~CBrushDC();

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to change the color used by the
	//     device context brush.
	// Parameters:
	//     crColor - RGB value to change the brush color to.
	//-----------------------------------------------------------------------
	void Color(COLORREF crColor);

protected:

	CBrush m_brush;     // Brush selected into device context.
	HDC    m_hDC;       // Device context handle.
	HBRUSH m_hOldBrush; // Handle to the previously selected brush.
};

//===========================================================================
// Summary:
//     CCompatibleDC is a helper class used to create a memory device
//     context (DC) compatible with the device specified by pDC.  When
//     destroyed, the class selects the previous bitmap back into the
//     device context to handle GDI resource cleanup.
//===========================================================================
class SKIN_CONTROLS_EXPORT CCompatibleDC : public CDC
{
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CCompatibleDC object and creates a memory
	//     device context (DC) compatible with the device specified by
	//     pDC.  The bitmap specified by pBitmap is then selected into
	//     the device context.
	// Parameters:
	//     pDC     - Points to a valid device context.
	//     pBitmap - Points to the previously selected bitmap.
	//     hBitmap - Points to the previously selected bitmap.
	//-----------------------------------------------------------------------
	CCompatibleDC(CDC* pDC, CBitmap* pBitmap);
	CCompatibleDC(CDC* pDC, HBITMAP hBitmap); // <combine CCompatibleDC::CCompatibleDC@CDC*@CBitmap*>

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CCompatibleDC object, handles cleanup and de-
	//     allocation.
	//-----------------------------------------------------------------------
	virtual ~CCompatibleDC();

protected:

	HBITMAP m_hOldBitmap; // Pointer to the previously selected bitmap.
};

//===========================================================================
// Summary:
//     CDrawHelpers is a helper class used to perform specialized
//     drawing tasks.  You can use this class to perform such tasks as
//     gradient fills and blending colors.
//===========================================================================
class SKIN_CONTROLS_EXPORT CDrawHelpers
{
public:
	typedef BOOL (__stdcall* PFNGRADIENTFILL)(HDC, PTRIVERTEX, ULONG, PVOID, ULONG, ULONG); // Function pointer used to access the Windows API GradientFill function.
	typedef BOOL (__stdcall* PFNALPHABLEND) (HDC, int, int, int, int, HDC, int, int, int, int, BLENDFUNCTION); // AlphaBlend function declaration
	typedef BOOL (WINAPI* PFNTRANSPARENTBLT)(HDC, int, int, int, int, HDC, int, int, int, int, UINT);

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CDrawHelpers object.
	//-----------------------------------------------------------------------
	CDrawHelpers();
	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXCSplitPath object, handles cleanup and de-
	//     allocation.
	//-----------------------------------------------------------------------
	virtual ~CDrawHelpers();

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to perform a gradient fill using
	//     the specified COLORREF values crFrom and crTo.
	// Parameters:
	//     pDC         - Points to the device context
	//     lpRect      - Size of area to fill
	//     crFrom      - RGB value to start from
	//     crTo        - RGB value to fill to
	//     grc         - CPaintManagerColorGradient struct containing start from and
	//                   fill to RGB color values.
	//     bHorz       - TRUE if fill is horizontal.
	//     lpRectClip  - Pointer to a RECT structure that contains a clipping rectangle.
	//                   This parameter is optional and may be set to NULL.
	//     hdc         - Handle to a device context.
	//     pVertex     - Pointer to an array of TRIVERTEX structures that
	//                   each define a triangle vertex.
	//     dwNumVertex - The number of vertices.
	//     pMesh       - Array of GRADIENT_TRIANGLE structures in triangle
	//                   mode, or an array of GRADIENT_RECT structures in
	//                   rectangle mode.
	//     dwNumMesh   - The number of elements (triangles or rectangles)
	//                   in pMesh.
	//     dwMode      - Specifies gradient fill mode. For a list of possible
	//                   values, see GradientFill in the Platform SDK.
	// Remarks:
	//     Call this member function to fill rectangle and triangle structures
	//     with color that smoothly fades from one side to the other.
	// Returns:
	//     The HDC version TRUE if successful; otherwise FALSE.
	//-----------------------------------------------------------------------
	void GradientFill(CDC* pDC, LPCRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);
	void GradientFill(CDC* pDC, LPCRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz, LPCRECT lpRectClip);
	BOOL GradientFill(HDC hdc, PTRIVERTEX pVertex, ULONG dwNumVertex, PVOID pMesh, ULONG dwNumMesh, ULONG dwMode);

	//
	void DrawAlphaRect(CDC* pDC, const CRect& rc, CColor& clr);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member to exclude the pixels for each corner of the
	//     area specified by rc.
	// Parameters:
	//     pDC - Points to the device context
	//     rc  - Area to exclude corners from
	//-----------------------------------------------------------------------
	void ExcludeCorners(CDC* pDC, CRect rc);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function will search a string, strip off the mnemonic
	//     '&', and reformat the string.
	// Parameters:
	//     strClear - Text needed to strip.
	//     lpszClear - Text needed to strip.
	//-----------------------------------------------------------------------
	static void StripMnemonics(CString& strClear);
	static void StripMnemonics(LPTSTR lpszClear); // <combine CDrawHelpers::StripMnemonics@CString&>

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to blur the color value for the
	//     points specified by pts
	// Parameters:
	//     pDC    - Points to the device context
	//     pts    - Array of points to blur
	//     nCount - Number of points in array.
	//-----------------------------------------------------------------------
	void BlurPoints(CDC* pDC, LPPOINT pts, int nCount);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to blend the colors specified by
	//     crA and crB.
	// Parameters:
	//     crA      - RGB value to blend
	//     crB      - RGB value to blend
	//     fAmountA - The amount that crA saturates crB.
	// Returns:
	//     An RGB value that represents the blended color.
	//-----------------------------------------------------------------------
	static COLORREF BlendColors(COLORREF crA, COLORREF crB, double fAmountA);

	//static BOOL GetIconLogFont(LOGFONT* plf);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to get dark color from specified by lColor
	// Parameters:
	//      lScale - Scale value
	//      lColor - RGB value to get
	// See Also: LightenColor
	//-----------------------------------------------------------------------
	static COLORREF DarkenColor(long lScale, COLORREF lColor);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to get light color from specified by lColor
	// Parameters:
	//      lScale - Scale value
	//      lColor - RGB value to get
	// See Also: DarkenColor
	//-----------------------------------------------------------------------
	static COLORREF LightenColor(long lScale, COLORREF lColor);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to convert a color from RGB to HSL color model.
	// Parameters:
	//      rgb - RGB color to convert
	// Returns:
	//     An HSL representation of the specified color.
	// See Also: HSLtoRGB
	//-----------------------------------------------------------------------
	static COLORREF RGBtoHSL(COLORREF rgb);
	static void RGBtoHSL(COLORREF clr, double& h, double& s, double& l);


	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to convert a color from HSL to RGB color model.
	// Parameters:
	//      hsl - HSL color to convert
	// Returns:
	//     An RGB representation of the specified color.
	// See Also: HueToRGB, RGBtoHSL
	//-----------------------------------------------------------------------
	static COLORREF HSLtoRGB(COLORREF hsl);
	static COLORREF HSLtoRGB(double h, double s, double l);


	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to determine if the specified font
	//     exists.
	// Parameters:
	//     lpszFaceName - A NULL terminated string that represents the
	//                   font face name.
	// Returns:
	//     TRUE if the font was found, otherwise FALSE.
	//-----------------------------------------------------------------------
	static BOOL FontExists(LPCTSTR lpszFaceName);

	//-----------------------------------------------------------------------
	// Summary:
	//     Retrieves DEFAULT_GUI_FONT font name.
	// Returns:
	//     Face name of DEFAULT_GUI_FONT font.
	//-----------------------------------------------------------------------
	static CString GetDefaultFontName();

	static CPoint Dlu2Pix(int dluX, int dluY);

	//-----------------------------------------------------------------------
	// Summary:
	//     Retrieves vertical font name
	// Parameters:
	//     bUseOfficeFont - TRUE to use "Tahoma" font if exists.
	// Returns:
	//     Face name of vertical font.
	//-----------------------------------------------------------------------
	static CString GetVerticalFontName(BOOL bUseOfficeFont);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to draw a vertical or horizontal line using
	//     the specified device context.
	// Parameters:
	//     pDC     - Points to the device context
	//     xPos    - Specifies the logical x-coordinate of the start position.
	//     yPos    - Specifies the logical y-coordinate of the start position.
	//     nLength - Specifies the length of the line to draw, for vertical lines set this value to 0.
	//     nHeight - Specifies the height of the line to draw, for horizontal lines set this value to 0.
	//     crLine  - Specifies the RGB color value used to draw the line.
	// Returns:
	//     TRUE if the specified device context is valid, otherwise FALSE.
	//-----------------------------------------------------------------------
	static BOOL DrawLine(CDC* pDC, int xPos, int yPos, int nLength, int nHeight, COLORREF crLine);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to determine if the system display
	//     is set to low resolution.
	// Parameters:
	//     hDC - Handle to a device context, if NULL the desktop window
	//           device context is used.
	// Returns:
	//     TRUE if the system display is set to low resolution,
	//     otherwise FALSE.
	//-----------------------------------------------------------------------
	static BOOL IsLowResolution(HDC hDC = 0);

	//-----------------------------------------------------------------------
	// Summary:
	//     Determines if GradientFill from msimg32.dll available.
	// Returns:
	//     TRUE if GradientFill can be used
	//-----------------------------------------------------------------------
	BOOL IsFastFillAvailable() const;

	//-----------------------------------------------------------------------
	// Summary:
	//      This member function is called by the Theme Manager to capture the
	//      area on the parent window underneath the specified owner window.
	//      This is then used for rendering the owner transparent.
	// Parameters:
	//      pWndOwner   - Pointer the child of the parent window to take a
	//                    snapshot for.
	//      bmpSnapshot - Bitmap used to store transparent background.
	// Returns:
	//      TRUE if the parent area was successfully captured, otherwise
	//      returns FALSE.
	// See Also:
	//      DrawTransparentBack
	//-----------------------------------------------------------------------
	BOOL TakeSnapShot(CWnd* pWndOwner, CBitmap& bmpSnapshot);

	//-----------------------------------------------------------------------
	// Summary:
	//      This member function is called to render the window specified
	//      by pWndOwner transparent displaying the parent windows background
	//      instead.
	// Parameters:
	//      pDC         - Pointer to pWndOwner device context.
	//      pWndOwner   - Pointer the child of the parent window to draw
	//                    transparent.
	//      bmpSnapshot - Bitmap used to store transparent background.
	// Returns:
	//      TRUE if the area was dran transparently, otherwise returns FALSE.
	// See Also:
	//      TakeSnapShot
	//-----------------------------------------------------------------------
	BOOL DrawTransparentBack(CDC* pDC, CWnd* pWndOwner, CBitmap& bmpSnapshot);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to switch Left and Right keys if window
	//     in Right To Left layout
	// Parameters:
	//     pWnd        - Window to test
	//     nChar       - Virtual key, passed to OnKeyDown member.
	//-----------------------------------------------------------------------
	static void KeyToLayout(CWnd* pWnd, UINT& nChar);

	//-----------------------------------------------------------------------
	// Summary:
	//    Converts the screen coordinates of a given point on the display to window coordinates.
	// Parameters:
	//     pWnd - window whose area is used for the conversion
	//     lpPoint - Points to a CPoint object or POINT structure that contains the screen coordinates to be converted.
	//-----------------------------------------------------------------------
	static void ScreenToWindow(CWnd* pWnd, LPPOINT lpPoint);

	//-----------------------------------------------------------------------
	// Summary:
	//     Determines if layout of a device context right to left.
	// Parameters:
	//     pDC - Device context to test
	//     hDC - Device context to test
	//-----------------------------------------------------------------------
	static BOOL IsContextRTL(CDC* pDC);
	static BOOL IsContextRTL(HDC hDC); // <combine CDrawHelpers::IsContextRTL@CDC*>

	//-----------------------------------------------------------------------
	// Summary:
	//     Cal this method to set right to left layout for device context
	// Parameters:
	//     pDC - Device context to set layout
	//     hDC - Device context to set layout
	//     bLayoutRTL - TRUE to set right to left layout
	//-----------------------------------------------------------------------
	static void SetContextRTL(CDC* pDC, BOOL bLayoutRTL);
	static void SetContextRTL(HDC hDC, BOOL bLayoutRTL); // <combine CDrawHelpers::SetContextRTL@CDC*@BOOL>

	//-----------------------------------------------------------------------
	// Summary:
	//     Register class helper.
	// Parameters:
	//     hInstance - Handle to the instance that contains the window procedure for the class.
	//     lpszClassName - Pointer to a null-terminated string or is an atom
	//     style - Specifies the class style(s).
	//     hIcon - Handle to the class icon
	//     hbrBackground - Handle to the class background brush.
	//-----------------------------------------------------------------------
	static BOOL RegisterWndClass(HINSTANCE hInstance, LPCTSTR lpszClassName, UINT style, HICON hIcon = 0, HBRUSH hbrBackground = 0);

	//-----------------------------------------------------------------------
	// Summary:
	//     Copies the CWnd caption title (if it has one) into the destination
	//     string strWindowText.
	// Parameters:
	//     hWnd          - Handle to the window or control containing the text.
	//     strWindowText - A CString object that is to receive the copied string
	//                     of the window's title.
	//-----------------------------------------------------------------------
	static void GetWindowCaption(HWND hWnd, CString& strWindowText);

private:
	//-----------------------------------------------------------------------
	// Summary:
	//     Auxiliary function for color convertion from HSL to RGB color model.
	// Parameters:
	//     m1 - Input value.
	//     m2 - Input value.
	//     h - Input value.
	// Returns:
	//     A converted value
	// See Also: RGBtoHSL
	//-----------------------------------------------------------------------
	static int HueToRGB(int m1, int m2, int h);
	static double HueToRGB(double temp1, double temp2, double temp3);

public:
	PFNALPHABLEND m_pfnAlphaBlend;
	PFNTRANSPARENTBLT m_pfnTransparentBlt;
	PFNGRADIENTFILL m_pfnFastGradientFill;

private:

	HMODULE m_hMsImgDll;  // Handle to MsImg32.dll.

	// private members used for draw routines.
	void GradientFillFast(CDC* pDC, LPCRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);
	void GradientFillSlow(CDC* pDC, LPCRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);

	// singleton
	friend SKIN_CONTROLS_EXPORT CDrawHelpers* DrawHelpers();   // Used to access the CDrawHelpers object.
};

SKIN_CONTROLS_EXPORT CDrawHelpers* DrawHelpers();

#endif // DRAW_HELPERS_H_
