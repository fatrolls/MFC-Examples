#if !defined(AFX_CDIBSECTIONLITE_H__35D9F3D4_B960_11D2_A981_2C4476000000__INCLUDED_)
#define AFX_CDIBSECTIONLITE_H__35D9F3D4_B960_11D2_A981_2C4476000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DIBSectionLite.h : header file
//

// Copyright © Dundas Software Ltd. 1999, All Rights Reserved

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	NO	Derived from CWnd
//	NO	Is a CWnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO 	Needs a resource (template)
//	YES	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         

// DIBSection is DIBSection wrapper class for Win32 platforms.
// This class provides a simple interface to DIBSections including loading,
// saving and displaying DIBsections.
//

// Using DIBSection :

// This class is very simple to use. The bitmap can be set using either SetBitmap()
// (which accepts either a Device dependant or device independant bitmap, or a 
// resource ID) or by using Load(), which allows an image to be loaded from disk. 
// To display the bitmap simply use Draw or Stretch.
//
// eg. 
//
//      CDIBSectionLite dibsection;
//      dibsection.Load(_T("image.bmp"));
//      dibsection.Draw(pDC, CPoint(0,0));  // pDC is of type CDC*
//
//      CDIBSectionLite dibsection;
//      dibsection.SetBitmap(IDB_BITMAP); 
//      dibsection.Draw(pDC, CPoint(0,0));  // pDC is of type CDC*
//
// The CDIBSectionLite API includes many methods to extract information about the
// image, as well as palette options for getting and setting the current palette.
//
// Author: Chris Maunder (cmaunder@dundas.com)
// Date  : 12 April 1999
//#include <afx.h>
#include <afxctl.h>
#include <afxwin.h>
#include <vfw.h>
#pragma comment(lib, "vfw32")

/////////////////////////////////////////////////////////////////////////////
// defines

#define DS_BITMAP_FILEMARKER  ((WORD) ('M' << 8) | 'B')    // is always "BM" = 0x4D42
#define BMGRADIENT_DIRECTION_HORZ	0
#define BMGRADIENT_DIRECTION_VERT	1

/////////////////////////////////////////////////////////////////////////////
// BITMAPINFO wrapper

struct DIBINFO : public BITMAPINFO
{
	RGBQUAD	 arColors[255];    // Color table info - adds an extra 255 entries to palette

	operator LPBITMAPINFO()          { return (LPBITMAPINFO) this; }
	operator LPBITMAPINFOHEADER()    { return &bmiHeader;          }
	RGBQUAD* ColorTable()            { return bmiColors;           }
};

/////////////////////////////////////////////////////////////////////////////
// LOGPALETTE wrapper

struct PALETTEINFO : public LOGPALETTE
{
    PALETTEENTRY arPalEntries[255];               // Palette entries

    PALETTEINFO() { palVersion = (WORD) 0x300; }

    operator LPLOGPALETTE()   { return (LPLOGPALETTE) this;            }
    operator LPPALETTEENTRY() { return (LPPALETTEENTRY) (palPalEntry); }
};


/////////////////////////////////////////////////////////////////////////////
// CDIBSectionLite object

class CDIBSectionLite : public CObject
{
// Construction
public:
	CDIBSectionLite();
	virtual ~CDIBSectionLite();
    void DeleteObject();

// static helpers
public:
    static int BytesPerLine(int nWidth, int nBitsPerPixel);
    static int NumColorEntries(int nBitsPerPixel);

    static PALETTEENTRY ms_StdColours[];
    static BOOL UsesPalette(CDC* pDC) { return (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE); }
    static BOOL CreateHalftonePalette(CPalette& palette, int nNumColours);

// Attributes
public:
    HBITMAP      GetSafeHandle() const       { return (this)? m_hBitmap : NULL;        }
    CSize        GetSize() const             { return CSize(GetWidth(), GetHeight());  }
    int          GetHeight() const           { return m_DIBinfo.bmiHeader.biHeight;    } 
    int          GetWidth() const            { return m_DIBinfo.bmiHeader.biWidth;     }
    int          GetPlanes() const           { return m_DIBinfo.bmiHeader.biPlanes;    }
    int          GetBitCount() const         { return m_DIBinfo.bmiHeader.biBitCount;  }
    LPVOID       GetDIBits()                 { return m_ppvBits;                       }
    LPBITMAPINFO GetBitmapInfo()             { return  (BITMAPINFO*) m_DIBinfo;        }
    DWORD        GetImageSize() const        { return m_DIBinfo.bmiHeader.biSizeImage; }
    LPBITMAPINFOHEADER GetBitmapInfoHeader() { return (BITMAPINFOHEADER*) m_DIBinfo;   }
	
	void		 CreateGradientBmp	(COLORREF clrBack,
									 COLORREF clrStart,
									 COLORREF clrEnd,
									 int iWidth,
									 int iHeight,
									 int iDirection);
	void		 Create32BitFromPicture (CPictureHolder* pPicture,
										 int iWidth,
										 int iHeight);

	COLORREF	 FixColorRef		(COLORREF clr);


    BOOL SetBitmap(UINT nIDResource);
    BOOL SetBitmap(LPCTSTR lpszResourceName);
    BOOL SetBitmap(HBITMAP hBitmap, CPalette* pPalette = NULL);
    BOOL SetBitmap(LPBITMAPINFO lpBitmapInfo, LPVOID lpBits);   

    CPalette *GetPalette()  { return &m_Palette; }
    BOOL SetPalette(CPalette* pPalette);
    BOOL SetLogPalette(LOGPALETTE* pLogPalette);

    BOOL SetDither(BOOL bDither);
    BOOL GetDither();


// Operations
public:
    BOOL Load(LPCTSTR lpszFileName);
    BOOL Save(LPCTSTR lpszFileName);

    BOOL Draw(CDC* pDC, CPoint ptDest, BOOL bForceBackground = FALSE);
    BOOL Stretch(CDC* pDC, CPoint ptDest, CSize size, BOOL bForceBackground = FALSE);

// Overrideables

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation
protected:
    void _ShowLastError();
    BOOL CreatePalette();
    BOOL FillDIBColorTable(UINT nNumColours, RGBQUAD *pRGB);

protected:
    HBITMAP  m_hBitmap;          // Handle to DIBSECTION
    DIBINFO  m_DIBinfo;          // Bitmap header & color table info
    VOID    *m_ppvBits;          // Pointer to bitmap bits
    UINT     m_iColorDataType;   // color data type (palette or RGB values)
    UINT     m_iColorTableSize;  // Size of color table

    CPalette m_Palette;          // Color palette

    BOOL     m_bDither;          // Use DrawDib routines for dithering?
    HDRAWDIB m_hDrawDib;         // handle to a DrawDib DC 

private:
    HBITMAP  m_hOldBitmap;      // Storage for previous bitmap in Memory DC
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDIBSECTIONLITE_H__35D9F3D4_B960_11D2_A981_2C4476000000__INCLUDED_)
