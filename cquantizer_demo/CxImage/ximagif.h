/*
 * File:	ximagif.h
 * Purpose:	GIF Image Class Loader and Writer
 */
/* === C R E D I T S  &  D I S C L A I M E R S ==============
 * CxImageICO (c) 07/Aug/2001 <ing.davide.pizzolato@libero.it>
 * Permission is given by the author to freely redistribute and include
 * this code in any program as long as this credit is given where due.
 *
 * version 1.20 15/Oct/2001
 * See the file history.htm for the complete bugfix and news report.
 *
 * Special thanks to Troels Knakkergaard for new features, enhancements and bugfixes
 *
 * original CImageGIF  and CImageIterator implementation are:
 * Copyright:	(c) 1995, Alejandro Aguilar Sierra <asierra@servidor.unam.mx>
 *
 * 6/15/97 Randy Spann: Added GIF87a writing support
 *         R.Spann@ConnRiver.net
 *
 * DECODE.C - An LZW decoder for GIF
 * Copyright (C) 1987, by Steven A. Bennett
 * Copyright (C) 1994, C++ version by Alejandro Aguilar Sierra
 *
 * In accordance with the above, I want to credit Steve Wilhite who wrote
 * the code which this is heavily inspired by...
 *
 * GIF and 'Graphics Interchange Format' are trademarks (tm) of
 * Compuserve, Incorporated, an H&R Block Company.
 *
 * Release Notes: This file contains a decoder routine for GIF images
 * which is similar, structurally, to the original routine by Steve Wilhite.
 * It is, however, somewhat noticably faster in most cases.
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

#if !defined(__ximaGIF_h)
#define __ximaGIF_h

#include "ximage.h"

#if CXIMAGE_SUPPORT_GIF

typedef short int       code_int;   
typedef long int        count_int;
typedef unsigned char   pixval;

/* Various error codes used by decoder */
#define OUT_OF_MEMORY -10
#define BAD_CODE_SIZE -20
#define READ_ERROR -1
#define WRITE_ERROR -2
#define OPEN_ERROR -3
#define CREATE_ERROR -4
#define MAX_CODES   4095
#define GIFBUFTAM 16384
#define TRANSPARENCY_CODE 0xF9

class CImageIterator;
class CxImageGIF: public CxImage
{
public:
	CxImageGIF(): CxImage(CXIMAGE_FORMAT_GIF) {}

//	bool ReadFile(const char * imageFileName){ return CxImage::ReadFile(imageFileName,CXIMAGE_FORMAT_GIF);}
//	bool SaveFile(const char * imageFileName){ return CxImage::SaveFile(imageFileName,CXIMAGE_FORMAT_GIF);}
	bool Decode(FILE *f);
	bool Encode(FILE * fp);
protected:
	int          Width, Height;
	int             curx, cury;
	int           BitsPerPixel;
	long             CountDown;
	unsigned long    cur_accum;
	int              cur_bits;
	unsigned char    *buffer;
	int interlaced, iypos, istep, iheight, ipass;
	int ibf; // = GIFBUFTAM+1;
	BYTE buf[GIFBUFTAM];
// Implementation
	void BumpPixel ();
	int GIFNextPixel ();
	void Putword (int w, FILE* fp );
	void compress (int init_bits, FILE* outfile);
	void output (code_int code );
	void cl_block ();
	void cl_hash (count_int hsize);
	void writeerr ();
	void char_init ();
	void char_out (int c);
	void flush_char ();
	short init_exp(short size);
	short get_next_code(FILE*);
	short decoder(FILE*, CImageIterator* iter, short linewidth, INT& bad_code_count);
	int get_byte(FILE*);
	int out_line(CImageIterator* iter, unsigned char *pixels, int linelen);

	short curr_size;                     /* The current code size */
	short clear;                         /* Value for a clear code */
	short ending;                        /* Value for a ending code */
	short newcodes;                      /* First available code */
	short top_slot;                      /* Highest code for current size */
	short slot;                          /* Last read code */

	/* The following static variables are used
	* for seperating out codes */
	short navail_bytes;              /* # bytes left in block */
	short nbits_left;                /* # bits left in current BYTE */
	BYTE b1;                           /* Current BYTE */
	BYTE byte_buff[257];               /* Current block */
	BYTE *pbytes;                      /* Pointer to next BYTE in block */
	/* The reason we have these seperated like this instead of using
	* a structure like the original Wilhite code did, is because this
	* stuff generally produces significantly faster code when compiled...
	* This code is full of similar speedups...  (For a good book on writing
	* C for speed or for space optomisation, see Efficient C by Tom Plum,
	* published by Plum-Hall Associates...)
	*/
	BYTE stack[MAX_CODES + 1];            /* Stack for storing pixels */
	BYTE suffix[MAX_CODES + 1];           /* Suffix table */
	USHORT prefix[MAX_CODES + 1];           /* Prefix linked list */
};

#endif

#endif
