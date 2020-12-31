/*
 * File:	ImaMNG.h
 * Purpose:	Declaration of the MNG Image Class
 * Author:	ing.davide.pizzolato@libero.it
 * Created:	2001
 */
/* === C R E D I T S  &  D I S C L A I M E R S ==============
 * CxImageMNG (c) 07/Aug/2001 <ing.davide.pizzolato@libero.it>
 * Permission is given by the author to freely redistribute and include
 * this code in any program as long as this credit is given where due.
 *
 * version 1.20 15/Oct/2001
 * See the file history.htm for the complete bugfix and news report.
 *
 * Special thanks to Frank Haug <f.haug@jdm.de> for suggestions and code.
 *
 * original mng.cpp code created by Nikolaus Brennig, November 14th, 2000. <virtualnik@nol.at>
 *
 * LIBMNG Copyright (c) 2000,2001 Gerard Juyn (gerard@libmng.com)
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

#if !defined(__ximaMNG_h)
#define __ximaMNG_h

#include "ximage.h"

#if CXIMAGE_SUPPORT_MNG

//#define MNG_NO_CMS
#define MNG_SUPPORT_DISPLAY
#define MNG_SUPPORT_READ
#define	MNG_SUPPORT_WRITE
#define MNG_ACCESS_CHUNKS
#define MNG_STORE_CHUNKS

extern "C" {
#include "libmng.h"
#include "libmng_data.h"
}

//unsigned long _stdcall RunMNGThread(void *lpParam);

typedef struct 
{
	FILE		*file;
	BYTE		*image;
	HANDLE		thread;
	mng_uint32	delay;
	mng_uint32  width;
	mng_uint32  height;
	mng_uint32  effwdt;
	mng_int16	bpp;
	mng_bool	animation;
	mng_bool	animation_enabled;
	float		speed;
} mngstuff;

class CxImageMNG: public CxImage
{
public:
	CxImageMNG();
	~CxImageMNG();

	bool ReadFile(const char * imageFileName);
	bool SaveFile(const char * imageFileName){ return CxImage::SaveFile(imageFileName,CXIMAGE_FORMAT_MNG);}
	bool Decode(FILE * hFile);
	bool Encode(FILE * hFile);

	long Resume();
	void SetSpeed(float speed);
	
	mng_handle hmng;
	mngstuff mnginfo;
protected:
	void WritePNG(mng_handle hMNG, int Frame, int FrameCount );
	void SetCallbacks(mng_handle mng);
};

#endif

#endif

