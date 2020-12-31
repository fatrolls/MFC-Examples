// cimage.h : interface of the CImage class

// Purpose:	Declaration of the Platform Independent Image Class
// Author:	Alejandro Aguilar Sierra
// Created:	1995
// Copyright:	(c) 1995, Alejandro Aguilar Sierra <asierra@servidor.unam.mx>
// This software is based in part on the work of the Independent JPEG Group.
// Modifications by Troels K. aug. 2001
// Modifications by ing.davide.pizzolato@libero.it

#ifndef __CIMAGE_H__
#define __CIMAGE_H__

#include <windows.h>
#include <tchar.h>
#include <stdio.h> // FILE

#ifndef _countof
   #define _countof(array) (sizeof(array)/sizeof((array)[0]))
#endif

#ifdef CIMAGE_EXPORTS
   #define CIMAGE_API __declspec(dllexport)
#else
   #ifdef _IMAGEDLL
      #define CIMAGE_API __declspec(dllimport)
   #else
      #define CIMAGE_API 
   #endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageBase - virtual base class

class CIMAGE_API CImageBase
{
// Attributes
public:
   void*	m_handle; //contains the header, the palette, the bits

// Construction
public:
   CImageBase(void);

// Operations
public:
   BOOL IsOpen(void) const { return (m_handle != NULL) ; }

// New virtuals
public:
	virtual ~CImageBase();
   virtual void Close(void);
	
   virtual BOOL DrawImplementation(HDC hdc, int xDst, int yDst, int cxDst, int cyDst, 
                                            int xSrc, int ySrc, int cxSrc, int cySrc) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CImage formats enumerator
enum cximage_type
{
   ENUM_cimage_format_bmp,
   ENUM_cimage_format_gif,
   ENUM_cimage_format_jpeg,
   ENUM_cimage_format_png,
   ENUM_cimage_format_icon,
   ENUM_cimage_format_tiff,
   ENUM_cimage_format_enumcount,
   ENUM_cimage_format_empty = -1,
};

// needed for png & gif
#pragma pack(1)
struct rgb_color_struct { BYTE r,g,b; };
#pragma pack()

// needed for png & mng
#define COLORTYPE_PALETTE	1
#define COLORTYPE_COLOR		2
#define COLORTYPE_ALPHA		4

/////////////////////////////////////////////////////////////////////////////
// CImage

class CIMAGE_API CImage : public CImageBase
{
public:
//extensible information collector
typedef struct tagCImageInfo 
{
	DWORD	dwEffWidth;			//DWORD aligned scan line width
	BYTE*	pImage;				//THE IMAGE BITS
	void*	pGhost;				//if this is a ghost, pGhost point to the body
//	char	szFileName[_MAX_PATH];
	enum cximage_type dwFileType;			//original image format
	BYTE	bColorType;			//used for PNG, MNG
	char	szLastError[256];	//debugging
	int	nBkgndIndex;		//used for GIF, PNG, MNG
	BYTE	nQuality;			//used for JPEG
	int	nFrame;				//used for TIF, GIF, MNG : actual frame
	int	nNumFrames;			//used for TIF, GIF, MNG : total number of frames
	DWORD	dwFrameDelay;		//used for GIF, MNG
} CXIMAGEINFO;
protected:
   BITMAPINFOHEADER  m_header; //standard header
	CXIMAGEINFO			m_info; //extended information

public:
	CImage();
   CImage(enum cximage_type);
   CImage(DWORD dwWidth, DWORD dwHeight, WORD wBPP);
	CImage(const CImage&);
	CImage(HBITMAP, int BPP = -1); //Windows resource
	CImage(HICON);		//Windows resource
	CImage(HANDLE hMem);		//Windows objects (clipboard)
	CImage(LPCSTR  filename, enum cximage_type);
	CImage(LPCWSTR filename, enum cximage_type);
	CImage(FILE*, DWORD imagetype=0);
	CImage& operator=(const CImage&);

   BOOL Attach(const CImage&);
   BOOL Detach(CImage* dst);

	void*	Create(DWORD dwWidth, DWORD dwHeight, WORD wBPP);
	void	Clear(BYTE bval=0);
	BOOL  Copy(const CImage& src);
	HANDLE CopyToHandle(HANDLE hMem);
	void	Transfer(CImage* src);
	BOOL	IsInside(int x, int y);

   int	GetLength();
	LPBYTE GetBits();

   void EnableTransparency(BOOL bEnable = TRUE);
   BOOL HasTransparency(void) const;
	BOOL SetBkColor(COLORREF crTransparent);

   DWORD	GetWidth (void) const;
   DWORD	GetHeight(void) const;
   SIZE  GetSize  (void) const;

   DWORD	GetEffWidth() const;
	DWORD	GetColorCount() const;
	BYTE	GetColorType() const;
	WORD	GetBPP() const;
	enum cximage_type GetFileType();
	void SetFileType(enum cximage_type type);
	LPCSTR GetLastError();

	DWORD	GetPaletteSize();
	int   GetPixelIndex(int x,int y);
	RGBQUAD* GetPalette() const;
	RGBQUAD GetPaletteIndex(int idx) const;
	RGBQUAD GetPixelColor(int x,int y);
	int   FindPaletteIndex(COLORREF) const;
	BOOL	GetRGB(int i, BYTE* r, BYTE* g, BYTE* b);
	BYTE	GetNearestIndex(RGBQUAD);
	BOOL  Draw(HDC hdc, int xDst = 0, int yDst = 0, int cxDst = -1, int cyDst = -1, 
                       int xSrc = 0, int ySrc = 0, int cxSrc = -1, int cySrc = -1);
   BOOL  Draw(HDC hdc, const POINT&);
   BOOL  Draw(HDC hdc, const RECT&);
   BOOL  Draw(HDC hdc, const RECT& dst, const RECT& src);
	BOOL  Tile(HDC hdc, LPCRECT rc);

   void	BlendPalette(COLORREF cr,int perc);
	void	SetPalette(DWORD n, BYTE *r, BYTE *g, BYTE *b);
	void	SetPalette(const RGBQUAD* pPal,DWORD nColors=256);
	void	SetPalette(const rgb_color_struct *rgb,DWORD nColors=256);
	BOOL  SetPaletteIndex(int idx, BYTE r, BYTE g, BYTE b);
	BOOL  SetPaletteIndex(int idx, RGBQUAD);
	BOOL  SetPaletteIndex(int idx, COLORREF);
	void	SetPixelColor(int x,int y,RGBQUAD);
	void	SetPixelColor(int x,int y,COLORREF);
	void	SetPixelIndex(int x,int y,BYTE i);
	void	SetGreyPalette();

   RGBQUAD  HSLtoRGB(COLORREF cHSLColor);
	RGBQUAD  RGB2RGBQUAD(COLORREF);
	COLORREF RGBQUAD2RGB (RGBQUAD);
	RGBQUAD  RGBtoHSL(RGBQUAD lRGBColor);
	RGBQUAD  HSLtoRGB(RGBQUAD lHSLColor);
	void	   RGB2BGR(BYTE *buffer, int length);

   BOOL CreateFromFile(LPCSTR  filename, enum cximage_type);
	BOOL CreateFromFile(LPCWSTR filename, enum cximage_type);
	BOOL Save(LPCSTR  filename, enum cximage_type);
	BOOL Save(LPCWSTR filename, enum cximage_type);

// New virtuals
public:
	virtual BOOL Read (FILE*, enum cximage_type);
   virtual BOOL Write(FILE*, enum cximage_type);

   BOOL LoadResource(HRSRC hRes, enum cximage_type, HMODULE hModule = NULL);
   HBITMAP MakeBitmap();

// Operations - special effects
public:
   BOOL Flip();
	BOOL Mirror();
	BOOL Negative();
	BOOL GreyScale();
   BOOL Rotate(double angle);
	BOOL Exchange(COLORREF, COLORREF);
	BOOL WalkColors(COLORREF(*manipulate)(BYTE r, BYTE g, BYTE b, LPVOID), LPVOID lpUser = NULL);

   const CXIMAGEINFO* GetInfo      (void) { return &m_info; }
   const BITMAPINFO * GetBitmapInfo(void) { return (const BITMAPINFO*)m_handle; }

// Implementation
public:
   virtual void Close(void);
	virtual ~CImage();
	virtual BOOL DrawImplementation(HDC hdc, int xDst, int yDst, int cxDst, int cyDst, 
                                            int xSrc, int ySrc, int cxSrc, int cySrc);

protected:
	void Startup();
	void Ghost(CImage *src);
	WORD HueToRGB(WORD n1,WORD n2,WORD hue);
};

#include "cimage.inl"

#endif // __CIMAGE_H__
