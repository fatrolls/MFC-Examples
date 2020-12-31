/*
 * File:	ximatif.h
 * Purpose:	TIFF Image Class Loader and Writer
 */
/* === C R E D I T S  &  D I S C L A I M E R S ==============
 * CxImageTIF (c) 07/Aug/2001 <ing.davide.pizzolato@libero.it>
 * Permission is given by the author to freely redistribute and include
 * this code in any program as long as this credit is given where due.
 *
 * version 1.20 15/Oct/2001
 * See the file history.htm for the complete bugfix and news report.
 *
 * Special thanks to Troels Knakkergaard for new features, enhancements and bugfixes
 *
 * Parts of the code come from FreeImage 2
 * Design and implementation by 
 * - Floris van den Berg (flvdberg@wxs.nl)
 * - Hervé Drolon (drolon@iut.univ-lehavre.fr)
 * - Markus Loibl (markus.loibl@epost.de)
 * - Luca Piergentili (l.pierge@terra.es)
 *
 * LibTIFF is:
 * Copyright (c) 1988-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
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



#if !defined(__ximatif_h)
#define __ximatif_h

#include "ximage.h"

#if CXIMAGE_SUPPORT_TIF

class CxImageTIF: public CxImage
{
public:
	CxImageTIF(): CxImage(CXIMAGE_FORMAT_TIF) {}

//	bool ReadFile(const char * imageFileName){ return CxImage::ReadFile(imageFileName,CXIMAGE_FORMAT_TIF);}
//	bool SaveFile(const char * imageFileName){ return CxImage::SaveFile(imageFileName,CXIMAGE_FORMAT_TIF);}
	bool Decode(FILE * infile);
	bool Encode(FILE * infile);
};

#endif

#endif
