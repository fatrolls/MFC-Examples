/*
 * File:	cimage.h
 * Purpose:	Declaration of the Platform Independent Image Class
 * Author:	Alejandro Aguilar Sierra
 * Created:	1995
 * Copyright:	(c) 1995, Alejandro Aguilar Sierra <asierra@servidor.unam.mx>
 *
 * This software is based in part on the work of the Independent JPEG Group.
 *
 */
#if !defined(__Image_h)
#define __Image_h

#include "cimageb.h"

enum {
CIMAGE_FORMAT_BMP,
CIMAGE_FORMAT_JPEG,
CIMAGE_FORMAT_GIF,
CIMAGE_FORMAT_XPM,
CIMAGE_FORMAT_PNG,
CMAX_IMAGE_FORMATS
};

class CImage: public CObject
{
protected:
	int filetype;
	CString filename;
public:
	CImageImpl* implementation;
	CImage(void);
	CImage(const CBitmap* bitmap);
	CImage (const CString& fileName, int imageType = -1);     // Read an image file
	CImage(const CImage* img);
	virtual ~CImage ();

	BOOL ReadFile(const CString& fileName="", int imageType = -1);
	BOOL SaveFile(const CString& fileName="", int imageType = -1);

	int GetFileType()     { return filetype; }
	CString GetFilename() { return filename; }
  
	virtual int GetEffWidth() { return implementation->GetEffWidth(); }

	//  Image Information
	virtual int  GetWidth()     const { return implementation->GetWidth(); };
	virtual int  GetHeight()    const { return implementation->GetHeight(); };
	virtual int  GetDepth()     const { return implementation->GetDepth(); };
	virtual int  GetColorType() const { return implementation->GetColorType(); };

	virtual BOOL Inside(int x, int y) { return implementation->Inside(x, y); };

	virtual void Create(int width, int height, int deep, int colortype=-1);
	virtual BOOL CreateImplementation(const CString& imageFileName, int& imageType);

	// Drawing routines
	virtual BOOL Draw(CDC* dc, int x=0, int y=0, int dx=-1, int dy=-1, int xs=0, int ys=0)
	{
		return implementation->Draw(dc, x, y, dx, dy, xs, ys);
	}
  
	virtual BOOL Stretch(CDC* dc, int xd=0, int yd=0, int dxd=-1, int dyd=-1,
		int xs=0, int ys=0, int dxs=-1, int dys=-1)
	{
		return implementation->Stretch(dc, xd, yd, dxd, dyd, xs, ys, dxs, dys);
	}

	virtual int  GetIndex(int x, int y) { return implementation->GetIndex(x, y); }
	virtual BOOL GetRGB(int x, int y, byte* r, byte* g, byte* b)
	{ return implementation->GetRGB(x, y, r, g, b); }

	virtual BOOL SetIndex(int x, int y, int index) { return implementation->SetIndex(x, y, index); }
	virtual BOOL SetRGB(int x, int y, byte r, byte g, byte b) { return implementation->SetRGB(x, y, r, g, b); }

	// ColorMap settings
	virtual BOOL SetPalette(CImagePalette* pal) { return implementation->SetPalette(pal); }
	virtual BOOL SetPalette(int n, rgb_color_struct* rgb_struct)
	{ return implementation->SetPalette(n, rgb_struct); }
	virtual BOOL SetPalette(int n, byte* r, byte* g=0, byte* b=0)
	{ return implementation->SetPalette(n, r, g, b); }
	virtual CImagePalette* GetPalette() const { return implementation->GetPalette(); }
  
	virtual BOOL IsOK() { return (implementation != NULL && implementation->GetBits()); }
  
	virtual CImageImpl* GetImplementation() { return implementation; }
	virtual ImagePointerType GetRawImage() { return implementation->GetRawImage(); }
  
	CBitmap* MakeBitmap();
};

#endif
