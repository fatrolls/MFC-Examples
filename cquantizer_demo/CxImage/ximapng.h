/*
 * File:	ximatif.h
 * Purpose:	PNG Image Class Loader and Writer
 */
/* === C R E D I T S  &  D I S C L A I M E R S ==============
 * CxImagePNG (c) 07/Aug/2001 <ing.davide.pizzolato@libero.it>
 * Permission is given by the author to freely redistribute and include
 * this code in any program as long as this credit is given where due.
 *
 * version 1.20 15/Oct/2001
 * See the file history.htm for the complete bugfix and news report.
 *
 * Special thanks to Troels Knakkergaard for new features, enhancements and bugfixes
 *
 * original CImagePNG  and CImageIterator implementation are:
 * Copyright:	(c) 1995, Alejandro Aguilar Sierra <asierra@servidor.unam.mx>
 *
 * libpng version 1.0.12 - June 8, 2001 is:
 * Copyright (c) 1998-2001 Glenn Randers-Pehrson
 *
 * COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
 * THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
 * OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
 * CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
 * THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
 * SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
 * PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
 * THIS DISCLAIMER.
 *
 * Use at your own risk!
 * ==========================================================
 */
#if !defined(__ximaPNG_h)
#define __ximaPNG_h

#include "ximage.h"

#if CXIMAGE_SUPPORT_PNG

extern "C" {
#include "png.h"
}

class CxImagePNG: public CxImage
{
public:
	CxImagePNG(): CxImage(CXIMAGE_FORMAT_PNG) {}

//	bool ReadFile(const char * imageFileName){ return CxImage::ReadFile(imageFileName,CXIMAGE_FORMAT_PNG);}
//	bool SaveFile(const char * imageFileName){ return CxImage::SaveFile(imageFileName,CXIMAGE_FORMAT_PNG);}
	bool Decode(FILE * fp);
	bool Encode(FILE * hFile);
protected:
	void ima_png_error(png_struct *png_ptr, char *message);
};

#endif

#endif

