/*
 * Colour map (palette) class
 */

#ifndef CMAPH
#define CMAPH

class CImagePalette: public CPalette
{
public:
	CImagePalette() {}
	CImagePalette(const CImagePalette* pal);
	CImagePalette(const int n, const unsigned char* red, const unsigned char* green, const unsigned char* blue);
	~CImagePalette(void);
	BOOL Create(const int n, const unsigned char* red, const unsigned char* green, const unsigned char* blue);
	int GetPixel(const unsigned char red, const unsigned char green, const unsigned char blue);
	BOOL GetRGB(const int pixel, unsigned char* red, unsigned char* green, unsigned char* blue);
};

#endif
