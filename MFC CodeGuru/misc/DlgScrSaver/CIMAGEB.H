/*
 * File:	cimageb.h
 * Purpose:	Declaration of the Platform Independent Image Class
 * Author:	Alejandro Aguilar Sierra
 * Created:	1995
 * Description: This class adds drawing routines and color map management.
 *
 * Copyright:	(c) 1995, Alejandro Aguilar Sierra <asierra@servidor.unam.mx>
 */
#ifndef CIMAGEBH
#define CIMAGEBH

#include "stdafx.h"
#include "cmap.h"

#define CIMAGE_COLORS DIB_PAL_COLORS

#define CIMAGE_SUPPORT_BMP 1
#define CIMAGE_SUPPORT_GIF 1
#define CIMAGE_SUPPORT_JPEG 1
#define CIMAGE_SUPPORT_PNG  1
#define CIMAGE_SUPPORT_XPM  1

#ifndef byte
typedef unsigned char byte;
#endif

#ifdef WIN32
typedef byte* ImagePointerType;
#else
typedef byte huge* ImagePointerType;
#endif

typedef struct
{
	byte red;
	byte green;
	byte blue;
} rgb_color_struct;

#ifndef byte
typedef unsigned char byte;
#endif

#define COLORTYPE_PALETTE	1
#define COLORTYPE_COLOR		2
#define COLORTYPE_ALPHA		4

class CImageImpl
{
protected:
	ImagePointerType RawImage;  		//  Image data

	int Width, Height;   		//  Dimensions
	int Depth;	 				// (bits x pixel)
	int ColorType;				// Bit 1 = Palette used
									// Bit 2 = Color used
									// Bit 3 = Alpha used

	long EffWidth;	 			// Effective Width
	LPBITMAPINFOHEADER lpbi;
	int bgindex;
	CImagePalette* imagePalette;

friend class CImageIterator;
public:
	// Constructors
	CImageImpl();
	CImageImpl(int width, int height, int depth, int colortype=-1);
	CImageImpl( const CImageImpl* ima );

	// Destructor
	virtual ~CImageImpl();

	//  Image Information
	int  GetWidth() const     { return Width; };
	int  GetHeight() const    { return Height; };
	int  GetDepth() const     { return Depth; };
	int  GetColorType() const { return ColorType; };

	virtual BOOL Inside(int x, int y);

	virtual void Create(int width, int height, int deep, int colortype=-1);

	// Drawing routines
	BOOL Draw(CDC* dc, int x=0, int y=0, int dx=-1, int dy=-1, int xs=0, int ys=0);
	BOOL Stretch(CDC* dc, int xd=0, int yd=0, int dxd=-1, int dyd=-1,
		int xs=0, int ys=0, int dxs=-1, int dys=-1);

	virtual int  GetIndex(int x, int y);
	virtual BOOL GetRGB(int x, int y, byte* r, byte* g, byte* b);

	virtual BOOL SetIndex(int x, int y, int index);
	virtual BOOL SetRGB(int x, int y, byte r, byte g, byte b);

	// ColorMap settings
	BOOL SetPalette(CImagePalette* palette);
	BOOL SetPalette(int n, rgb_color_struct* rgb_struct);
	BOOL SetPalette(int n, byte* r, byte* g=0, byte* b=0);
	CImagePalette* GetPalette() const { return imagePalette; }
  
	inline ImagePointerType GetRawImage() { return RawImage; }
	inline LPBITMAPINFOHEADER GetBits() { return lpbi; }
	inline long GetEffWidth() { return EffWidth; }

	virtual BOOL ReadFile(const CString& /*imageFileName*/=_T("")) { return FALSE; }
	virtual BOOL SaveFile(const CString& /*imageFileName*/=_T("")) { return FALSE; }

	// 'Copy' the raw image data et. from 'from' to 'this'. NULLify these attributes
	// in 'from' so we can then delete it without deleting the raw image data.
	void TransferBits(CImageImpl* from);
};


inline
CImageImpl::CImageImpl() : /*ImaBase(),*/ imagePalette(0), lpbi(0)
{
	RawImage = 0; 
	Width = Height = 0;
	Depth = 0;
	ColorType = 0;
	bgindex = -1;
}

inline
CImageImpl::CImageImpl(int width, int height, int depth, int colortype) : imagePalette(0), lpbi(0)
{
	Width = Height = 0;
	Depth = 0;
	ColorType = 0;
	bgindex = -1;
	RawImage = 0;
	Create(width, height, depth, colortype);
}


inline
CImageImpl::CImageImpl( const CImageImpl *ima ) : imagePalette(0), lpbi(0)
{
	bgindex = -1;

	if (ima) 
	{
		Create(ima->GetWidth(), ima->GetHeight(), ima->GetDepth(), ima->GetColorType());
		if (ima->GetPalette())
			SetPalette(new CImagePalette(ima->GetPalette()));
	}
}

inline
BOOL CImageImpl::Inside(int x, int y)
{
	return (0<=y && y<Height && 0<=x && x<Width);
}

#endif
